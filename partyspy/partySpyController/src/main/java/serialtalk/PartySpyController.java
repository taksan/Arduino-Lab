package serialtalk;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.LinkedList;
import java.util.List;

import javax.swing.event.ChangeListener;

@SuppressWarnings("restriction")
public class PartySpyController {
	private InputStream input;
	private OutputStream output;
	List<String> commands = new LinkedList<String>();
	List<ChangeListener> listeners = new LinkedList<ChangeListener>();

	/* http://zizzle-brewbot.blogspot.com.br/2011/04/ttl-bluetooth-transceiver-with-linux.html
	 * hcitool scan 
	 * THE NUMBER CAN CHANGE!
	 * sudo rfcomm bind /dev/rfcomm0 00:19:5D:24:B7:63
	 */
	public PartySpyController(String serialPort) {
		try {
	        CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier(
	        		serialPort);
	 
	        Thread.sleep(1000);
	        
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
			if (input.available() <= 0)
				return;
			
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
	
	
	public void putCommand(String value) {
		write(value); 
	}

	private void write(String value) {
		try {
			output.write(value.getBytes(), 0, value.length());
//			printReceivedData();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}		
	}
}
