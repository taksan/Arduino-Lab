#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "ArduinoMock.h"
#include "LightDirectionDetectorTest.h"

#define LEFT_EYE_PIN  0
#define RIGHT_EYE_PIN 1
#define INITIAL_LEFT_LEVEL 80
#define INITIAL_RIGHT_LEVEL 40

using namespace std;

static const string directionNames[] = { "goNowhere", "goAhead", "turnLeft", "turnRight" };

CPPUNIT_TEST_SUITE_REGISTRATION( LightDirectionDetectorTest );

void LightDirectionDetectorTest::updateWithRightStronger_shouldReturnTurnRight() 
{
	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL);
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, 60);

	subject->update();

	assertDirection( dvTurnRight);

	CPPUNIT_ASSERT_EQUAL( 20,  subject->getIntensity() );
}

void LightDirectionDetectorTest::updateWithRightProportionallyStronger_shouldReturnTurnRight()
{
	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL + strongLeftThreshold );
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL + strongRightThreshold + 1);

	subject->update();

	assertDirection( dvTurnRight);

	CPPUNIT_ASSERT_EQUAL( 20,  subject->getIntensity() );
}

void LightDirectionDetectorTest::updateWithBothWeakButLeftStronger_ShouldReturnLeft() 
{
	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL + strongLeftThreshold - 1 );
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL);

	subject->update();

	assertDirection( dvTurnLeft );

	CPPUNIT_ASSERT_EQUAL( 40,  subject->getIntensity() );
}

void LightDirectionDetectorTest::updateWithLeftProportionallyStronger_shouldReturnTurnLeft()
{
	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, 90);
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, 43);

	subject->update();

	assertDirection( dvTurnLeft );

	CPPUNIT_ASSERT_EQUAL( 20,  subject->getIntensity() );
}


void LightDirectionDetectorTest::updateWithWeakStrenghAndWeakPrevious_shouldReturnTurnRight()
{
	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL);
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL);

	subject->update();

	assertDirection( dvTurnRight );

	CPPUNIT_ASSERT_EQUAL( 40,  subject->getIntensity() );
}

void LightDirectionDetectorTest::updateWithBothWeak_FirstTime_shouldReturnRight()
{
	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL);
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL-1);

	subject->update();

	assertDirection( dvTurnRight );

	CPPUNIT_ASSERT_EQUAL( 40,  subject->getIntensity() );
}

void LightDirectionDetectorTest::updateWithBothWeak_PreviousStrongWasRight_shouldReturnRight()
{
	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, getStrongLeft());
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL);
	subject->update();

	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL);
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, getStrongRight());
	subject->update();


	assertDirection( dvTurnRight );

	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL); 
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL);
	subject->update();

	assertDirection( dvTurnRight );

	CPPUNIT_ASSERT_EQUAL( 40,  subject->getIntensity() );

	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL); 
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL);
	subject->update();

	assertDirection( dvTurnRight );

	CPPUNIT_ASSERT_EQUAL( 40,  subject->getIntensity() );
}

void LightDirectionDetectorTest::updateWithBothWeak_PreviousStrongWasLeft_shouldReturnLeft()
{
	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL + strongLeftThreshold + 1);
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL);
	subject->update();

	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL); 
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL);
	subject->update();

	assertDirection( dvTurnLeft );

	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL); 
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL);
	subject->update();

	assertDirection( dvTurnLeft );
}


void LightDirectionDetectorTest::updateWithLeftStrong_ShouldRaiseStrongThresholdLevel()
{
	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL + strongLeftThreshold + 6);
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL + strongRightThreshold + 4);
	subject->update();

	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL+ strongLeftThreshold + 17); 
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL);
	subject->update();
	subject->update();
	subject->update();
	subject->update();

	assertDirection( dvTurnLeft );


	CPPUNIT_ASSERT_EQUAL( 20,  subject->getIntensity() );

	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL); 
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL + strongRightThreshold + 1);
	subject->update();

	assertDirection( dvTurnLeft );

	CPPUNIT_ASSERT_EQUAL( 40,  subject->getIntensity() );

	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL); 
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL + strongRightThreshold + 3);
	subject->update();

	assertDirection( dvTurnRight );

	CPPUNIT_ASSERT_EQUAL( 20,  subject->getIntensity() );
}


void LightDirectionDetectorTest::updateWithBothEyeStrong_shouldReturnGoAhead()
{
	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, 122);
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, 52);

	subject->update();
	assertDirection( dvGoAhead );

	CPPUNIT_ASSERT_EQUAL( 100,  subject->getIntensity() );
}

void LightDirectionDetectorTest::updateWithBothStrongAndThenWeakFewTimes_ShouldGoAhead()
{
	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, 122);
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, 52);

	subject->update();
	assertDirection( dvGoAhead );

	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL);
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL+strongRightThreshold*10);

	subject->update();
	subject->update();
	subject->update();

	CPPUNIT_ASSERT_EQUAL( 80,  subject->getIntensity() );
	assertDirection( dvGoAhead );

	subject->update();

	assertDirection( dvTurnRight );

}

void LightDirectionDetectorTest::updateWithFollowerUnableToMoveNow_ShouldeepLastMoveButWillStoreLastDirection()
{
	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, 122);
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, 52);

	subject->update();
	assertDirection( dvGoAhead );

	mockFollower.setCantChangeDirection();

	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL);
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL+strongRightThreshold*10);

	subject->update();
	subject->update();
	subject->update();
	subject->update();

	assertDirection( dvGoAhead );
	mockFollower.setCanChangeDirection();

	subject->update();

	assertDirection( dvTurnRight );
}


int LightDirectionDetectorTest::getStrongLeft()
{
	return INITIAL_LEFT_LEVEL + strongLeftThreshold + 1;
}

int LightDirectionDetectorTest::getStrongRight()
{
	return INITIAL_RIGHT_LEVEL + strongRightThreshold + 1;
}



void LightDirectionDetectorTest::setUp(void) 
{
	mock = new ArduinoMockApi(2);
	mock->setNextAnalogValueToReturn(LEFT_EYE_PIN, INITIAL_LEFT_LEVEL);
	mock->setNextAnalogValueToReturn(RIGHT_EYE_PIN, INITIAL_RIGHT_LEVEL);

	strongLeftThreshold = STRENGH_THRESHOLD * (INITIAL_LEFT_LEVEL/INITIAL_RIGHT_LEVEL);
	strongRightThreshold = STRENGH_THRESHOLD;

	int leftPin  = LEFT_EYE_PIN;
	int rightPin = RIGHT_EYE_PIN;
	Eye * left  = new Eye(mock, leftPin);
	Eye * right = new Eye(mock, rightPin);
	
	subject = new LightDirectionDetector(&mockFollower, left,right);
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
