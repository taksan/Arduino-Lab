package serialtalk;
 
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
 
public class PopsicleBotControlPanel extends JPanel {
	private static final long serialVersionUID = 1L;
    
	public PopsicleBotControlPanel(
			final JTextAreaFeedback userFeedback, 
			final PopsicleController controller,
			final InitialStatus initialStatus) 
	{
		setLayout(new GridBagLayout());
		GridBagConstraints c = new GridBagConstraints();
		c.insets = new Insets(8,8,8,8);
		c.gridx = 0;
		c.gridy = 0;
		add(new JLabel("Right Leg"), c);
		
		c.gridx = 1;
		c.gridy = 0;
		add(new JLabel("Left Leg"), c);
		
		final Leg right = new Leg("r", controller, initialStatus.right);
		final Leg left = new Leg("l", controller, initialStatus.left);
		
		c.gridx = 0;
		c.gridy = 1;
		add(right, c);
		
		c.gridy = 1;
		c.gridx = 1;
		add(left, c);
		
		Neck neck = new Neck(controller, initialStatus);
		c.gridx = 0;
		c.gridy = 2;
		c.gridwidth = 2;
		add(neck, c);
		
		UpdateButton updateRobot = new UpdateButton(controller);
		
		c.gridx = 0;
		c.gridy = 3;
		c.gridwidth = 2;
		add(updateRobot, c);
		c.gridx = 0;
		c.gridy = 4;
		c.gridwidth = 2;
		c.fill = GridBagConstraints.BOTH;
		
		JScrollPane comp = new JScrollPane(userFeedback);
		comp.setFocusable(false);
		add(comp, c);
		userFeedback.setErrorListener(new RobotErrorListener() {
			@Override
			public void onError(String str) {
				userFeedback.println("Resynching angles with robot because of error");
				String reply = controller.sendCommand("s");
				InitialStatus status = new InitialStatus(reply);
				right.setAngles(status.right);
				left.setAngles(status.left);
			}
		});
	}
}