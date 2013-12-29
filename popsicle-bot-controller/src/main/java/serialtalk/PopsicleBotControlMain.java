package serialtalk;

import javax.swing.JFrame;

public class PopsicleBotControlMain {

    public static void main(String[] args) throws Exception{
    	JTextAreaFeedback userFeedback = new JTextAreaFeedback(); 
		PopsicleController arduinoSerial = new PopsicleController(userFeedback);
		
		String currentAngles = arduinoSerial.sendCommand("s");
		userFeedback.println("Robot is online. Current stats: " + currentAngles);
		
    	InitialStatus stats = new InitialStatus(currentAngles);
    	
		PopsicleBotControlPanel botControlPanel = new PopsicleBotControlPanel(userFeedback, arduinoSerial, stats);
    	
    	JFrame jFrame = new JFrame();
    	jFrame.add(botControlPanel);
    	jFrame.pack();
    	jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	jFrame.setVisible(true);
    	/*
    	 Upper Right Leg: 75 (initial)
    	 	lower numbers : make leg come to front/head lowers
    	 	higher numbers: make leg go back
		 Right Knee: 
		 	higher numbers raise the lower leg
    	 Right Foot: higher numbers lift, lower number lowers (92)
    	 Left Foot: lower numbers lift, higher lowers (85)
    	 
    	 Left leg:
    	 Upper: (looking at the left side)
    	 	lower numbers: rotates motor clockwise 
    	 Knee:
    	 	lower numbers: rotates motor clockwise
    	 Foot: motor can't move
    	  	lower numbers: rotates arm ccw
    	 */
    }
}
