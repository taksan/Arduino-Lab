package serialtalk;

import javax.swing.JLabel;
import javax.swing.JPanel;
import net.miginfocom.swing.MigLayout;

@SuppressWarnings("serial")
public class ServoControlPanel extends JPanel {

	public ServoControlPanel() {
		setLayout(new MigLayout("", "[206px]", "[15px][][]"));
		JLabel label = new JLabel("Control using the arrow keys");
		add(label, "cell 0 1,alignx left,aligny top");
		
		JLabel lblArrows = new JLabel("Arrows < >");
		add(lblArrows, "cell 0 2");
	}
}
