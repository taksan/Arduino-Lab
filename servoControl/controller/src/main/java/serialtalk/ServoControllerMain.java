package serialtalk;

import javax.swing.JFrame;

public class ServoControllerMain {
	public static void main(String[] args) {
		String serialPort="/dev/ttyACM0";
		
		ServoController spyController = new ServoController(serialPort);

		ServoControlPanel botControlPanel = new ServoControlPanel();
    	JFrame jFrame = new ServoControllerFrame(spyController);
    	jFrame.add(botControlPanel);
    	jFrame.pack();
    	jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	jFrame.setVisible(true);
	}
}
