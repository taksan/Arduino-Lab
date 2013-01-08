package serialtalk;

import java.awt.GridLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;


public class Leg extends JPanel{
	private static final long serialVersionUID = 1L;
		public final LegSlider shoulder;
		public final LegSlider upper;
		public final LegSlider knee;
		public final LegSlider foot;
		
		public Leg(String idPrefix, PopsicleController serial, int ... angles) {
			shoulder = new LegSlider(idPrefix+"s", serial, angles[0]);
			upper = new LegSlider(idPrefix+"u", serial, angles[1]);
			knee = new LegSlider(idPrefix+"k", serial, angles[2]);
			foot = new LegSlider(idPrefix+"f", serial, angles[3]);
			setLayout(new GridLayout(6, 1));
			add(new JLabel("Shoulder Motor"));
			addSlider(shoulder);
			
			
			add(new JLabel("Upper Leg Motor"));
			addSlider(upper);
			
			add(new JLabel("Knee Motor"));
			addSlider(knee);
			
			add(new JLabel("Foot Motor"));
			addSlider(foot);
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
