package serialtalk;

import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class LegSlider extends JSlider {
	private static final long serialVersionUID = 1L;

	public LegSlider(final String id, final Serial arduinoSerial) {
		setValue(90);
		setMaximum(180);
		addChangeListener(new ChangeListener() {
			
			@Override
			public void stateChanged(ChangeEvent e) {
				byte value = (byte) getValue();
				String data = String.format("%s %c\n", id, value);
				arduinoSerial.write(data );
				arduinoSerial.printReceivedData();
			}
		});
	}
}
