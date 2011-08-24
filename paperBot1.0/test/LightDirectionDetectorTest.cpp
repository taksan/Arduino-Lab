#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

#include "LightDirectionDetectorTest.h"

using namespace std;

static const string directionNames[] = { "goAhead", "turnLeft", "turnRight" };

CPPUNIT_TEST_SUITE_REGISTRATION( LightDirectionDetectorTest );

void LightDirectionDetectorTest::updateWithRightStronger_shouldReturnTurnRight() 
{
	mock->setNextAnalogValueToReturn(0, 80);
	mock->setNextAnalogValueToReturn(1, 60);

	subject->update();

	assertDirection( dvTurnRight);
}

void LightDirectionDetectorTest::updateWithRightProportionallyStronger_shouldReturnTurnRight()
{
	mock->setNextAnalogValueToReturn(0, 80 + strongLeftThreshold );
	mock->setNextAnalogValueToReturn(1, 40 + strongRightThreshold + 1);

	subject->update();

	assertDirection( dvTurnRight);
}

void LightDirectionDetectorTest::updateWithLeftStronger_shouldReturnTurnLeft() 
{
	mock->setNextAnalogValueToReturn(0, 80 + strongLeftThreshold - 1 );
	mock->setNextAnalogValueToReturn(1, 40);

	subject->update();

	assertDirection( dvTurnLeft );
}

void LightDirectionDetectorTest::updateWithLeftProportionallyStronger_shouldReturnTurnLeft()
{
	mock->setNextAnalogValueToReturn(0, 90);
	mock->setNextAnalogValueToReturn(1, 43);

	subject->update();

	assertDirection( dvTurnLeft );
}


void LightDirectionDetectorTest::updateWithWeakStrenghAndWeakPrevious_shouldReturnTurnRight()
{
	mock->setNextAnalogValueToReturn(0, 80);
	mock->setNextAnalogValueToReturn(1, 40);

	subject->update();

	assertDirection( dvTurnRight );
}

void LightDirectionDetectorTest::updateWithBothWeak_FirstTime_shouldReturnRight()
{
	mock->setNextAnalogValueToReturn(0, 80);
	mock->setNextAnalogValueToReturn(1, 39);

	subject->update();

	assertDirection( dvTurnRight );
}

void LightDirectionDetectorTest::updateWithBothWeak_PreviousStrongWasRight_shouldReturnRight()
{
	mock->setNextAnalogValueToReturn(0, 80 + strongLeftThreshold + 1);
	mock->setNextAnalogValueToReturn(1, 40);
	subject->update();

	mock->setNextAnalogValueToReturn(0, 80);
	mock->setNextAnalogValueToReturn(1, 40 + strongRightThreshold + 1);
	subject->update();


	assertDirection( dvTurnRight );

	mock->setNextAnalogValueToReturn(0, 80); 
	mock->setNextAnalogValueToReturn(1, 40);
	subject->update();

	assertDirection( dvTurnRight );

	mock->setNextAnalogValueToReturn(0, 80); 
	mock->setNextAnalogValueToReturn(1, 40);
	subject->update();

	assertDirection( dvTurnRight );
}

void LightDirectionDetectorTest::updateWithBothWeak_PreviousStrongWasLeft_shouldReturnLeft()
{
	mock->setNextAnalogValueToReturn(0, 80 + strongLeftThreshold + 1);
	mock->setNextAnalogValueToReturn(1, 40);
	subject->update();

	mock->setNextAnalogValueToReturn(0, 80); 
	mock->setNextAnalogValueToReturn(1, 40);
	subject->update();

	assertDirection( dvTurnLeft );

	mock->setNextAnalogValueToReturn(0, 80); 
	mock->setNextAnalogValueToReturn(1, 40);
	subject->update();

	assertDirection( dvTurnLeft );
}


void LightDirectionDetectorTest::updateWithBothEyeStrong_shouldReturnGoAhead()
{
	mock->setNextAnalogValueToReturn(0, 122);
	mock->setNextAnalogValueToReturn(1, 52);

	subject->update();
	assertDirection( dvGoAhead );
}


void LightDirectionDetectorTest::setUp(void) 
{
	mock = new ArduinoMockApi(2);
	mock->setNextAnalogValueToReturn(0, 80);
	mock->setNextAnalogValueToReturn(1, 40);

	strongLeftThreshold = STRENGH_THRESHOLD * (80/40);
	strongRightThreshold = STRENGH_THRESHOLD;

	int leftPin  = 0;
	int rightPin = 1;
	Eye * left  = new Eye(mock, leftPin);
	Eye * right = new Eye(mock, rightPin);
	
	subject = new LightDirectionDetector(left,right);
}

void LightDirectionDetectorTest::tearDown(void) 
{
	delete mock;
}

void LightDirectionDetectorTest::assertDirection(Direction expectedDirection)
{
	Direction directionToGo = subject->getDirectionToGo();
	CPPUNIT_ASSERT_EQUAL( directionNames[expectedDirection], directionNames[directionToGo] );
}
