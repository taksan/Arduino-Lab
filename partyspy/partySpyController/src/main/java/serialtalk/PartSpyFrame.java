package serialtalk;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JFrame;

@SuppressWarnings("serial")
public class PartSpyFrame extends JFrame {

	private PartySpyController spyController;

	public PartSpyFrame(PartySpyController aSpyController) {
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
				case KeyEvent.VK_UP:
					spyController.putCommand("F");
					break;
				case KeyEvent.VK_DOWN:
					spyController.putCommand("B");
					break;
				case KeyEvent.VK_W:
					spyController.putCommand("U");
					break;
				case KeyEvent.VK_S:
					spyController.putCommand("D");
					break;
				}
			}
		});
	}
	
}
