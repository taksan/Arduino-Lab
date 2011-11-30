package serialtalk;
 
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
 
public class ServoSlider extends JPanel {
	private static final long serialVersionUID = 1L;
	private Serial arduinoSerial;
 
    public static void main(String[] args) throws Exception{
    	ServoSlider servoSlider = new ServoSlider();
    	JFrame jFrame = new JFrame();
    	jFrame.add(servoSlider);
    	jFrame.pack();
    	jFrame.setVisible(true);
    }
    
	public ServoSlider() {
		arduinoSerial = new Serial();
		
		JLabel lblTurnTheServo = new JLabel("Turn the servo");
		add(lblTurnTheServo);
		
		final JSlider slider = new JSlider();
		slider.setValue(90);
		slider.setMaximum(180);
		slider.addChangeListener(new ChangeListener() {
			
			@Override
			public void stateChanged(ChangeEvent e) {
				byte value = (byte) slider.getValue();
				arduinoSerial.write(value);
				arduinoSerial.printReceivedData();
			}
		});
		add(slider);
	}

}