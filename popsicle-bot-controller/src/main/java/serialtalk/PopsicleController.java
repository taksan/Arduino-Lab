package serialtalk;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;
import java.util.concurrent.TimeUnit;

public class PopsicleController {
	private InputStream input;
	private OutputStream output;
	LinkedHashMap<Object, String> cmdFromSource = new LinkedHashMap<>();
	List<ChangeListener> listeners = new LinkedList<ChangeListener>();
	private UserFeedback feedback;
	BlockingQueue<String> lineQueue = new LinkedBlockingDeque<>();

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
		lineQueue.clear();
		write(val);
		try {
			return lineQueue.poll(1, TimeUnit.SECONDS);
		} catch (InterruptedException e) {
			throw new RuntimeException(e);
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
	
	private void write(String val) {
		String value = val.contains("$")?val:val+"$\n";
		try {
			output.write(value.getBytes(), 0, value.length());
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}
	
	private void  receiveIncomingData() {
		StringBuffer sb = new StringBuffer();
		char data;
		do {
			try {
				if (input.available()==0) continue;
				data = (char) input.read();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
			sb.append(data);
			if (data == '\n') {
				lineQueue.add(sb.toString());
				feedback.print("< " + sb.toString());
				sb = new StringBuffer();
			}
		} while(true);
	}

	public void start() {
		Thread dataReceiverThread = new Thread(new Runnable() {
			@Override
			public void run() {
				receiveIncomingData();
			}
		}, "Data Receiver");
		dataReceiverThread.setDaemon(true);
		dataReceiverThread.start();
	}
}
