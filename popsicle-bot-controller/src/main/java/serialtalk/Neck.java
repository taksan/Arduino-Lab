package serialtalk;

import javax.swing.JLabel;
import javax.swing.JPanel;

public class Neck extends JPanel {
	private static final long serialVersionUID = 1L;

	public Neck(PopsicleController controller, InitialStatus initialStatus) {
		createComponents(controller, initialStatus);
	}

	private void createComponents(PopsicleController controller, InitialStatus initialStatus) {
		ArticulatedJointSlider neckSlider = new ArticulatedJointSlider("n", controller);
		neckSlider.withAngle(initialStatus.neck);
		add(new JLabel("Neck"));
		add(neckSlider);
	}

}
