package serialtalk;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;

public class ResetButton extends JButton {
	private static final long serialVersionUID = 1L;

	public ResetButton(final PopsicleController controller, final InitialStatus status, final Leg right, final Leg left, final Neck neck) {
		super("Reset robot");
		setFocusable(false);
		
		addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				right.setAngles(status.right);
				left.setAngles(status.left);
				neck.setAngle(status.neck);
				controller.sendAccumulatedData();
			}
		});
	}
}
