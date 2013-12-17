package serialtalk;

import java.awt.GridLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;

public class Leg extends JPanel {
	private static final long serialVersionUID = 1L;
	public final LegSlider shoulder;
	public final LegSlider upper;
	public final LegSlider knee;
	public final LegSlider foot;

	public Leg(String idPrefix, PopsicleController serial, int... angles) {
		shoulder = new LegSlider(idPrefix + "s", serial, angles[0]);
		upper = new LegSlider(idPrefix + "u", serial, angles[1]);
		knee = new LegSlider(idPrefix + "k", serial, angles[2]);
		foot = new LegSlider(idPrefix + "f", serial, angles[3]);
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
}
