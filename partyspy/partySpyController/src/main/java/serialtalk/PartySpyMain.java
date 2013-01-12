package serialtalk;

import javax.swing.JFrame;

public class PartySpyMain {
	public static void main(String[] args) {
		PartySpyController spyController = new PartySpyController();

		PartySpyControlPanel botControlPanel = new PartySpyControlPanel();
    	JFrame jFrame = new PartSpyFrame(spyController);
    	jFrame.add(botControlPanel);
    	jFrame.pack();
    	jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	jFrame.setVisible(true);
	}
}
