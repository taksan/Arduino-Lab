class ArticulatedJoint;

class RotateTask {
	int from, to, inc;
public:
	RotateTask(int from, int to) {
		this->from = from;
		this->to = to;
		inc = from < to? 
			1:
			-1;
	}
	bool perform(ArticulatedJoint * servo); 
};

class ArticulatedJoint : public Servo, public Tickable {
private:
	RotateTask * task;
public:
	const int lowerBound;
	const int upperBound;
	ArticulatedJoint(FeedbackCallback * feedback, int lower, int upper):
		lowerBound(lower),upperBound(upper), 
		feedback(feedback)
	{
		task = NULL;
		write(90);
	}

	void tick() {
		if (task == NULL)
			return;
		if (task->perform(this)) {
			delete task;
			task = NULL;
		}
	}

	bool accept(int value) {
		return (value >= lowerBound && value <= upperBound);
	}

	bool rotate(int value) {
		if (!accept(value)) {
			feedback->printf("[error] %d rejected. Value out of bounds[%d,%d]\n", value, lowerBound, upperBound);
			return false;
		}

		feedback->printf("(%d accepted. Will start ticking. )", value);
		task = new RotateTask(read(),value);
		return true;
	}

	void writeInc(int value) {
		feedback->printf("processing tick: %d\n", value);
		write(value);
	}

	void write(int value) {
		if (accept(value)) 
			Servo::write(value);
	}

private:
	FeedbackCallback * feedback;
};

bool RotateTask::perform(ArticulatedJoint * servo) {
	from+=inc;
	servo->writeInc(from);
	return from == to;
}


