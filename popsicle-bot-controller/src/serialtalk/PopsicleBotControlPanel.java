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
    	jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	jFrame.setVisible(true);
    }
    
	public PopsicleBotControlPanel() {
		setLayout(new GridLayout(2, 2));
		arduinoSerial = new PopsicleController();
		
		add(new JLabel("Right Leg"));
		add(new JLabel("Left Leg"));
		
		final Leg right = new Leg("r", arduinoSerial, 90, 135, 90);
		final Leg left = new Leg("l", arduinoSerial, 90, 135, 90);
		add(right);
		add(left);
	}

}