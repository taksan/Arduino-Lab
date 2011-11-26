package serialtalk;
 
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
 
public class ServoSlider extends JPanel {
	private static final long serialVersionUID = 1L;
	static InputStream input;
    static OutputStream output;
 
    public static void main(String[] args) throws Exception{
    	ServoSlider servoSlider = new ServoSlider();
    	JFrame jFrame = new JFrame();
    	jFrame.add(servoSlider);
    	jFrame.pack();
    	jFrame.setVisible(true);
    }
    
	public ServoSlider() {
		
		JLabel lblTurnTheServo = new JLabel("Turn the servo");
		add(lblTurnTheServo);
		
		final JSlider slider = new JSlider();
		slider.setValue(90);
		slider.setMaximum(180);
		slider.addChangeListener(new ChangeListener() {
			
			@Override
			public void stateChanged(ChangeEvent e) {
				byte value = (byte) slider.getValue();
				try {
					output.write(value);
				} catch (IOException e1) {
					throw new RuntimeException(e1);
				}
				printReceivedData();
			}
		});
		add(slider);
		
		initSerial();
	}

	private void initSerial() {
		try {
			String serialPort="/dev/ttyUSB0";
			System.out.println("Using port: " + serialPort);
	        CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier(
	        		serialPort);
	 
	        SerialPort port = (SerialPort)portId.open("serial talk", 4000);
	        input = port.getInputStream();
	        output = port.getOutputStream();
	        port.setSerialPortParams(9600,
	                SerialPort.DATABITS_8,
	                SerialPort.STOPBITS_1,
	                SerialPort.PARITY_NONE);
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

	private void printReceivedData() {
		try {
			while(input.available()>0) {
				char data = (char) input.read();
				System.out.print((char)data);
				if (data == '=')
					break;
	        }
			System.out.println("");
		}catch(IOException e) {
			throw new RuntimeException(e);
		}
	}
}