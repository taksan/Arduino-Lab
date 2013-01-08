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
    }
}
