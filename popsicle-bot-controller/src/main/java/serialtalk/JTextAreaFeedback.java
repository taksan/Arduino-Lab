package serialtalk;

import java.awt.Color;

import javax.swing.JTextArea;
import javax.swing.border.LineBorder;
import javax.swing.text.DefaultCaret;

public class JTextAreaFeedback
	extends JTextArea
	implements UserFeedback {
	private static final long serialVersionUID = 1L;
	private RobotErrorListener el = new RobotErrorListener() { @Override public void onError(String str) { } };
	
	public JTextAreaFeedback() {
		super(10,80);
		setBorder(new LineBorder(Color.BLACK));
		DefaultCaret caret = (DefaultCaret)getCaret();
		caret.setUpdatePolicy(DefaultCaret.ALWAYS_UPDATE);
	}

	@Override
	public void print(final String str) {
		this.append(str);
		if (str.contains("[error]")) {
			new Thread(new Runnable() {
				
				@Override
				public void run() {
					el.onError(str);
				}
			}, "Handler Error").start();
		}
	}

	@Override
	public void print(char data) {
		this.append(""+data);
	}

	@Override
	public void println(String str) {
		this.print(str+"\n");
	}

	public void setErrorListener(RobotErrorListener el) {
		this.el = el;
	}
}
