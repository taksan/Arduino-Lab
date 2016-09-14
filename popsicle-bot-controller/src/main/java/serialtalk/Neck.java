package serialtalk;

import javax.swing.JLabel;
import javax.swing.JPanel;

public class Neck extends JPanel {
	private static final long serialVersionUID = 1L;
	private ArticulatedJointSlider neckSlider;

	public Neck(PopsicleController controller, InitialStatus initialStatus) {
		createComponents(controller, initialStatus);
	}

	private void createComponents(PopsicleController controller, InitialStatus initialStatus) {
		neckSlider = new ArticulatedJointSlider("n", controller);
		neckSlider.withAngle(initialStatus.neck);
		add(new JLabel("Neck"));
		add(neckSlider);
	}

	public void setAngle(int neck) {
		neckSlider.withAngle(neck);
	}

}
