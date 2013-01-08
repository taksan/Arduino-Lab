package serialtalk;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;

@SuppressWarnings("serial")
public class UpdateButton extends JButton implements ChangeListener{
	public UpdateButton(final PopsicleController controller) {
		super("Update robot");
		this.setEnabled(false);
		
		controller.addChangeListener(this);
		addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				controller.sendAccumulatedData();
			}
		});
	}

	@Override
	public void commandAdded() {
		this.setEnabled(true);
	}

	@Override
	public void commandsSent() {
		this.setEnabled(false);
	}
}
