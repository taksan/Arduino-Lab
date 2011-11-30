package serialtalk;

import java.awt.GridLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;


public class Leg extends JPanel{
	private static final long serialVersionUID = 1L;
		public final LegSlider upper;
		public final LegSlider middle;
		public final LegSlider knee;
		
		public Leg(String idPrefix, PopsicleController serial) {
			upper = new LegSlider(idPrefix+"u", serial);
			middle = new LegSlider(idPrefix+"m", serial);
			knee = new LegSlider(idPrefix+"k", serial);
			setLayout(new GridLayout(6, 1));
			add(new JLabel("Top Motor"));
			add(upper);
			
			add(new JLabel("Leg Motor"));
			add(middle);
			
			add(new JLabel("Knee Motor"));
			add(knee);
		}
}
