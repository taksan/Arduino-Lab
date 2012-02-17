package serialtalk;

import java.awt.GridLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;


public class Leg extends JPanel{
	private static final long serialVersionUID = 1L;
		public final LegSlider upper;
		public final LegSlider middle;
		public final LegSlider knee;
		
		public Leg(String idPrefix, PopsicleController serial, int ... angles) {
			upper = new LegSlider(idPrefix+"u", serial, angles[0]);
			middle = new LegSlider(idPrefix+"m", serial, angles[1]);
			knee = new LegSlider(idPrefix+"k", serial, angles[2]);
			setLayout(new GridLayout(6, 1));
			add(new JLabel("Top Motor"));
			addSlider(upper);
			
			
			add(new JLabel("Leg Motor"));
			addSlider(middle);
			
			add(new JLabel("Knee Motor"));
			addSlider(knee);
		}

		private void addSlider(final LegSlider joint) {
			JPanel jointPanel = new JPanel();
			final JLabel jointAngleLabel = new JLabel(""+joint.getValue());
			jointPanel.add(joint);
			jointPanel.add(jointAngleLabel);
			joint.addChangeListener(new ChangeListener() {
				
				@Override
				public void stateChanged(ChangeEvent e) {
					jointAngleLabel.setText("" + joint.getValue());
					
				}
			});
			add(jointPanel);
			
		}
}
