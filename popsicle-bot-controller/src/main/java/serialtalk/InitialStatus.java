package serialtalk;

import com.google.gson.Gson;

public class InitialStatus {
	public int [] right = {90, 90, 135, 92};
	public int [] left = {90, 90, 135, 85};
	public int neck;
	
	public static class Robot {
		public static class Leg {
			int s;
			int u;
			int k;
			int f;
		}
		Leg left;
		Leg right;
		Integer neck;
	}
	
	public InitialStatus(String fromRobot) {
		Gson gson = new Gson();
		Robot robot = fromJson(fromRobot, gson);
		right[0] = robot.right.s;
		right[1] = robot.right.u;
		right[2] = robot.right.k;
		right[3] = robot.right.f;
		
		left[0] = robot.left.s;
		left[1] = robot.left.u;
		left[2] = robot.left.k;
		left[3] = robot.left.f;
		
		neck = robot.neck;
	}

	private Robot fromJson(String fromRobot, Gson gson) {
		try {
			return gson.fromJson(fromRobot, Robot.class);
		}catch (Exception e) {
			System.err.println("Failed to parse : " + fromRobot);
			throw new RuntimeException(e);
		}
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
