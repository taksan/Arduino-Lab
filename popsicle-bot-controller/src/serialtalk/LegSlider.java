package serialtalk;

import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class LegSlider extends JSlider {
	private static final long serialVersionUID = 1L;

	public LegSlider(final String id, final PopsicleController arduinoSerial) {
		setValue(90);
		setMaximum(180);
		addChangeListener(new ChangeListener() {
			
			@Override
			public void stateChanged(ChangeEvent e) {
				String data = String.format("%s %d\n", id, getValue());
				arduinoSerial.write(data );	
				arduinoSerial.printReceivedData();
			}
		});
	}
}
