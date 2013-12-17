#include <stdio.h>
#include <highgui.h>
#include <fcntl.h>    
#include <termios.h> 
#include <cv.h>
#include <unistd.h>

#define HEIGHT 440
#define WIDTH 600

int getSerialFd()
{
    struct termios toptions;
    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)  {
        perror("init_serialport: Unable to open port ");
        return -1;
    }

    if (tcgetattr(fd, &toptions) < 0) {
        perror("init_serialport: Couldn't get term attributes");
        return -1;
    }
    speed_t brate=B9600;
    cfsetispeed(&toptions, brate);
    cfsetospeed(&toptions, brate);
	// 8N1
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    // no flow control
    toptions.c_cflag &= ~CRTSCTS;

    toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl

    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    toptions.c_oflag &= ~OPOST; // make raw

    // see: http://unixwiz.net/techtips/termios-vmin-vtime.html
    toptions.c_cc[VMIN]  = 0;
    toptions.c_cc[VTIME] = 20;

    if( tcsetattr(fd, TCSANOW, &toptions) < 0) {
        perror("init_serialport: Couldn't set term attributes");
        return -1;
    }
}

IplImage* GetThresholdedImage(IplImage* img)
{
	// Convert the image into an HSV image
	IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
	cvCvtColor(img, imgHSV, CV_BGR2HSV);

	IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);

	// Values 20,100,100 to 30,255,255 working perfect for yellow at around 6pm
	cvInRangeS(imgHSV, cvScalar(20, 100, 100), cvScalar(30, 255, 255), imgThreshed);

	cvReleaseImage(&imgHSV);

	return imgThreshed;
}

void updateCameraDirection(int arduinoFd, int offset, int width)
{
	char angle = 0;
	if (fabs(offset) > 20) {
		angle = -(20* ((double)offset/width));

		/*
		if (offset > 0)
			angle = -2;
		else
			angle = 2;
			*/
		printf("pos: %d angle: %d\n", offset, angle);
	}
	write(arduinoFd, &angle, 1);
}

int main()
{
	// Initialize capturing live feed from the camera
	CvCapture* capture = 0;
	capture = cvCaptureFromCAM(0);

	// Couldn't get a device? Throw an error and quit
	if(!capture)
    {
        printf("Could not initialize capturing...\n");
        return -1;
    }

	// The two windows we'll be using
    cvNamedWindow("video");
	cvNamedWindow("thresh");

	// This image holds the "scribble" data...
	// the tracked positions of the ball
	IplImage* imgScribble = NULL;

	// An infinite loop
	while(true)
    {
		// Will hold a frame captured from the camera
		IplImage* frame = 0;
		frame = cvQueryFrame(capture);

		// If we couldn't grab a frame... quit
        if(!frame)
            break;
		
		// If this is the first frame, we need to initialize it
		if(imgScribble == NULL)
		{
			imgScribble = cvCreateImage(cvGetSize(frame), 8, 3);
		}

		// Holds the yellow thresholded image (yellow = white, rest = black)
		IplImage* imgYellowThresh = GetThresholdedImage(frame);

		// Calculate the moments to estimate the position of the ball
		CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
		cvMoments(imgYellowThresh, moments, 1);

		// The actual moment values
		double moment10 = cvGetSpatialMoment(moments, 1, 0);
		double moment01 = cvGetSpatialMoment(moments, 0, 1);
		double area = cvGetCentralMoment(moments, 0, 0);

		// Holding the last and current ball positions
		static int posX = 0;
		static int posY = 0;

		int lastX = posX;
		int lastY = posY;

		posX = moment10/area;
		posY = moment01/area;

		int arduinoFd = getSerialFd();

		if (area > 200) {
			if(lastX>0 && lastY>0 && posX>0 && posY>0)
			{
				int offsetX = posX-WIDTH/2;
				updateCameraDirection(arduinoFd, offsetX, WIDTH);

				int offsetY = posY - HEIGHT/2;
				updateCameraDirection(arduinoFd, offsetY, HEIGHT);
			}
		}

		// Add the scribbling image and the frame... and we get a combination of the two
		cvAdd(frame, imgScribble, frame);
		cvShowImage("thresh", imgYellowThresh);
		cvShowImage("video", frame);

		// Wait for a keypress
		int c = cvWaitKey(10);
		if(c!=-1)
		{
			// If pressed, break out of the loop
            break;
		}

		close(arduinoFd);

		// Release the thresholded image... we need no memory leaks.. please
		cvReleaseImage(&imgYellowThresh);

		delete moments;
    }

	// We're done using the camera. Other applications can now use it
	cvReleaseCapture(&capture);
//	CvCapture *capture2 = 
//	    cvCreateFileCapture_FFMPEG("http://axis-cam/mjpg/video.mjpg?resolution=640x480&req_fps=10&.mjpg");

    return 0;
}
