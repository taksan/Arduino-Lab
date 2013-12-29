package serialtalk;

import java.awt.Color;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class LegSlider extends JPanel {
	private static final long serialVersionUID = 1L;
	private JSlider jointSlider;
	private JTextField jointTextField;
	private boolean ignoreUpdate;
	
	public LegSlider(final String id, final PopsicleController arduinoSerial) {
		createComponents(id, arduinoSerial, 0);
	}

	void createComponents(final String id, final PopsicleController arduinoSerial, int initialAngle) {
		jointSlider = new JSlider();
		jointSlider.setMaximum(180);
		withAngle(initialAngle);
		
		jointTextField = new JTextField(""+jointSlider.getValue());
		this.add(jointSlider);
		this.add(jointTextField);
		jointTextField.setColumns(4);
		jointSlider.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent e) {
				String t = "" + jointSlider.getValue();
				if (!ignoreUpdate) {
					String data = String.format("%s %d$\n", id, jointSlider.getValue());
					arduinoSerial.putCommand(e.getSource(), data);
					setDirty();
				}
				ignoreUpdate = false;
				
				if (jointTextField.getText().equals(t))
					return;
				jointTextField.setText(t);
			}
		});
		jointTextField.addKeyListener(new KeyListener() {
			@Override
			public void keyReleased(KeyEvent e) {
				try {
					Integer intValue = Integer.valueOf(jointTextField.getText());
					if (jointSlider.getValue() == intValue)
						return;
					jointSlider.setValue(intValue);
				}catch(NumberFormatException ex){
				}
			}
			
			@Override public void keyTyped(KeyEvent e) {  }
			@Override public void keyPressed(KeyEvent e) { }
		});
		arduinoSerial.addChangeListener(new serialtalk.ChangeListener() {
			@Override
			public void commandsSent() {
				clearDirty();
			}
			
			@Override
			public void commandAdded() {
			}
		});
	}

	public LegSlider withAngle(int initialAngle) {
		ignoreUpdate = true;
		jointSlider.setValue(initialAngle);
		return this;
	}

	protected void setDirty() {
		jointTextField.setBackground(Color.YELLOW);
	}
	
	protected void clearDirty() {
		jointTextField.setBackground(Color.WHITE);
	}

}
