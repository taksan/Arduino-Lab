package serialtalk;
 
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;
 
public class PopsicleBotControlPanel extends JPanel {
	private static final long serialVersionUID = 1L;
    
	public PopsicleBotControlPanel(final PopsicleController controller) {
		setLayout(new GridBagLayout());
		GridBagConstraints c = new GridBagConstraints();
		c.gridx = 0;
		c.gridy = 0;
		add(new JLabel("Right Leg"), c);
		
		c.gridx = 1;
		c.gridy = 0;
		add(new JLabel("Left Leg"), c);
		
		final Leg right = new Leg("r", controller, 90, 135, 90, 90);
		final Leg left = new Leg("l", controller, 90, 135, 90, 90);
		c.gridx = 0;
		c.gridy = 1;
		add(right, c);
		
		c.gridx = 1;
		c.gridy = 1;
		add(left, c);
		
		UpdateButton updateRobot = new UpdateButton(controller);
		
		c.gridx = 0;
		c.gridy = 2;
		c.gridwidth = 2;
		add(updateRobot, c);
	}

}