package serialtalk;
 
import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
 
public class PopsicleBotControlPanel extends JPanel {
	private static final long serialVersionUID = 1L;
	private PopsicleController arduinoSerial;
 
    public static void main(String[] args) throws Exception{
    	PopsicleBotControlPanel servoSlider = new PopsicleBotControlPanel();
    	JFrame jFrame = new JFrame();
    	jFrame.add(servoSlider);
    	jFrame.pack();
    	jFrame.setVisible(true);
    }
    
	public PopsicleBotControlPanel() {
		setLayout(new GridLayout(2, 2));
		arduinoSerial = new PopsicleController();
		
		add(new JLabel("Left Leg"));
		add(new JLabel("Right Leg"));
		
		final Leg left = new Leg("l", arduinoSerial);
		final Leg right = new Leg("r", arduinoSerial);
		add(left);
		add(right);
	}

}