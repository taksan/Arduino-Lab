package serialtalk;

import com.google.gson.Gson;

public class InitialStatus {
	int [] right = {90, 90, 135, 92};
	int [] left = {90, 90, 135, 85};
	
	public static class Robot {
		public static class Leg {
			int s;
			int u;
			int k;
			int f;
		}
		Leg left;
		Leg right;
	}
	
	public InitialStatus(String fromRobot) {
		//l- s:90 u:96 k:135 f:92 r- s:90 u:90 k:45 f:95
		Gson gson = new Gson();
		Robot robot = gson.fromJson(fromRobot, Robot.class);
		right[0] = robot.right.s;
		right[1] = robot.right.u;
		right[2] = robot.right.k;
		right[3] = robot.right.f;
		
		left[0] = robot.left.s;
		left[1] = robot.left.u;
		left[2] = robot.left.k;
		left[3] = robot.left.f;
	}
	
	public InitialStatus() {
	}

	public int [] rightLegAngles() {
		return right;
	}

	public int [] leftLegAngles() {
		return left;
	}
}
