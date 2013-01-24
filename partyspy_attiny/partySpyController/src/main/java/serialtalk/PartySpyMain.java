package serialtalk;

import javax.swing.JFrame;

public class PartySpyMain {
	public static void main(String[] args) {
		String serialPort="/dev/rfcomm0";
//		String serialPort="/dev/ttyUSB0";
		
		PartySpyController spyController = new PartySpyController(serialPort);

		PartySpyControlPanel botControlPanel = new PartySpyControlPanel();
    	JFrame jFrame = new PartSpyFrame(spyController);
    	jFrame.add(botControlPanel);
    	jFrame.pack();
    	jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	jFrame.setVisible(true);
	}
}
