package serialtalk;

import javax.swing.JFrame;

public class PopsicleBotControlMain {

    public static void main(String[] args) throws Exception{
		PopsicleController arduinoSerial = new PopsicleController();
		
    	PopsicleBotControlPanel botControlPanel = new PopsicleBotControlPanel(arduinoSerial);
    	JFrame jFrame = new JFrame();
    	jFrame.add(botControlPanel);
    	jFrame.pack();
    	jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	jFrame.setVisible(true);
    	/*
    	 Upper Right Leg: 75 (initial)
    	 	lower numbers : make leg come to front
    	 	higher numbers: make leg go back
		 Right Knee: 
		 	higher numbers raise the lower leg
    	 Right Foot: higher numbers lift, lower number lowers (92)
    	 Left Foot: lower numbers lift, higher lowers (85)
    	 
    	 Upper Left Leg:
    	 	lower: raises leg
    	 */
    }
}
