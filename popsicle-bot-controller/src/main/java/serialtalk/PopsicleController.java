package serialtalk;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;

import org.apache.commons.lang.UnhandledException;

public class PopsicleController {
	private InputStream input;
	private OutputStream output;
	LinkedHashMap<Object, String> cmdFromSource = new LinkedHashMap<>();
	List<ChangeListener> listeners = new LinkedList<ChangeListener>();
	private UserFeedback feedback;

	public PopsicleController(UserFeedback feedback) {
		this.feedback = feedback;
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
	
	public void sendAccumulatedData() {
		for (String value : cmdFromSource.values()) 
			write(value);
		cmdFromSource.clear();
		fireCommandsSent();
	}

	public void putCommand(Object object, String value) {
		fireCommandAdded();
		cmdFromSource.put(object, value);
	}
	
	public String sendCommand(final String val) {
		try {
			String value = val.contains("$")?val:val+"$\n";
			output.write(value.getBytes(), 0, value.length());
			while(input.available() == 0);
			
			StringBuffer sb = new StringBuffer();
			char data;
			do {
				data = (char) input.read();
				sb.append(data);
			} while(data != '\n');
			return sb.toString();
		}catch(Exception e) {
			throw new UnhandledException(e);
		}
	}
	
	private void fireCommandsSent() {
		for (ChangeListener listener : listeners) {
			listener.commandsSent();
		}
	}
	
	private void fireCommandAdded() {
		for (ChangeListener listener : listeners) {
			listener.commandAdded();
		}
	}

	public void addChangeListener(ChangeListener listener) {
		listeners.add(listener);
	}
	
	private void write(String value) {
		feedback.println("> "+value.trim());
		String reply = sendCommand(value);
		feedback.print(reply);
	}
}
