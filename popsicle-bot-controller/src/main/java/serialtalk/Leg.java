package serialtalk;

import java.awt.GridLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;

public class Leg extends JPanel {
	private static final long serialVersionUID = 1L;
	public final ArticulatedJointSlider shoulder;
	public final ArticulatedJointSlider upper;
	public final ArticulatedJointSlider knee;
	public final ArticulatedJointSlider foot;

	public Leg(String idPrefix, PopsicleController controller, int... angles) {
		shoulder = new ArticulatedJointSlider(idPrefix + "s", controller);
		upper = new ArticulatedJointSlider(idPrefix + "u", controller);
		knee = new ArticulatedJointSlider(idPrefix + "k", controller);
		foot = new ArticulatedJointSlider(idPrefix + "f", controller);
		setAngles(angles);
		
		setLayout(new GridLayout(6, 1));
		add(new JLabel("Shoulder Motor"));
		add(shoulder);

		add(new JLabel("Upper Leg Motor"));
		add(upper);

		add(new JLabel("Knee Motor"));
		add(knee);

		add(new JLabel("Foot Motor"));
		add(foot);
	}
	
	public void setAngles(int... angles) {
		shoulder.withAngle(angles[0]);
		upper.withAngle(angles[1]);
		knee.withAngle(angles[2]);
		foot.withAngle(angles[3]);
	}
}
