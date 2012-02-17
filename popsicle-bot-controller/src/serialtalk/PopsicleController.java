package serialtalk;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class PopsicleController {
	private InputStream input;
	private OutputStream output;

	public PopsicleController() {
		try {
			String serialPort="/dev/ttyUSB0";
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

	public void printReceivedData() {
		try {
			if (input.available() > 0)
				System.out.print("There is data");
			while(input.available()>0) {
				char data = (char) input.read();
				System.out.print((char)data);
				if (data == '\0')
					break;
	        }
			System.out.println("");
		}catch(IOException e) {
			throw new RuntimeException(e);
		}
	}

	public void write(byte value) {
		try {
			output.write(value);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}		
	}
	
	public void write(String value) {
		try {
			output.write(value.getBytes(), 0, value.length());
		} catch (IOException e) {
			throw new RuntimeException(e);
		}		
	}
}
