class LegJoint;

class MoveTask {
	int from, to, inc;
public:
	MoveTask(int from, int to) {
		this->from = from;
		this->to = to;
		inc = from < to? 
			1:
			-1;
	}
	bool perform(LegJoint * servo); 
};

class LegJoint : public Servo, public Tickable {
private:
	MoveTask * m;
public:
	const int lowerBound;
	const int upperBound;
	LegJoint(FeedbackCallback * feedback, int lower, int upper):
		lowerBound(lower),upperBound(upper), 
		feedback(feedback)
	{
	}

	void tick() {
		if (m == NULL)
			return;
		if (m->perform(this)) {
			delete m;
			m = NULL;
		}
	}

	bool accept(int value) {
		return (value >= lowerBound && value <= upperBound);
	}

	bool write(int value) {
		if (!accept(value)) {
			feedback->printf("[error] %d rejected. Value out of bounds[%d,%d]\n", value, lowerBound, upperBound);
			return false;
		}

		//Servo::write(value);
		m = new MoveTask(read(),value);
		return true;
	}

	void writeNow(int value) {
		Servo::write(value);
	}

private:
	FeedbackCallback * feedback;
};

bool MoveTask::perform(LegJoint * servo) {
	from+=inc;
	servo->writeNow(from);
	return from == to;
}


