#include <stdint.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "ArduinoMock.h"
#include "../PaperBot.h"

class PaperBotExtended : public PaperBot {
public:
	PaperBotExtended():PaperBot(1,2) { }
	MoveQueue * getQueue()  {
		return &(this->moveQueue);
	}

	void setThrustCallback(void (*callback)(int)) {
		this->thrustMotor->writecallback = callback;
	}
	void setDirectionCallback(void (*callback)(int)) {
		this->directionMotor->writecallback = callback;
	}

};

class PaperBotTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( PaperBotTest );

	CPPUNIT_TEST( go_happyDay );

	CPPUNIT_TEST_SUITE_END();
	public:
	void go_happyDay();

	private:
	PaperBotExtended * subject;
};
