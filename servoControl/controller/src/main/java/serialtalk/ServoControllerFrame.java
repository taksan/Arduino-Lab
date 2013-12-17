package serialtalk;

import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.Window;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JFrame;

@SuppressWarnings("serial")
public class ServoControllerFrame extends JFrame {

	private ServoController spyController;

	public ServoControllerFrame(ServoController aSpyController) {
		this.spyController = aSpyController;
		
		addKeyListener(new KeyListener() {
			
			public void keyTyped(KeyEvent e) {
			}
			
			public void keyReleased(KeyEvent e) {
			}
			
			public void keyPressed(KeyEvent e) {
				switch(e.getKeyCode()) {
				case KeyEvent.VK_LEFT:
					spyController.putCommand("L");
					break;
				case KeyEvent.VK_RIGHT:
					spyController.putCommand("R");
					break;
				}
			}
		});
		centreWindow(this);
	}
	
	public static void centreWindow(Window frame) {
	    Dimension dimension = Toolkit.getDefaultToolkit().getScreenSize();
	    int x = (int) ((dimension.getWidth() - frame.getWidth()) / 2);
	    frame.setLocation(x, 100);
	}
}
