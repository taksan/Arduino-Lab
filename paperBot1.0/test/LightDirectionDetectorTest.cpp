#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "LightDirectionDetectorTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( LightDirectionDetectorTest );

void LightDirectionDetectorTest::updateWithRightStronger_wentRightShouldReturnTrue() 
{
	mock->setNextAnalogValueToReturn(0, 80);
	mock->setNextAnalogValueToReturn(1, 60);

	subject->update();

	CPPUNIT_ASSERT( subject->wentRight() );
}

void LightDirectionDetectorTest::updateWithRightProportionallyStronger_wentRightShouldReturnTrue()
{
	mock->setNextAnalogValueToReturn(0, 102);
	mock->setNextAnalogValueToReturn(1, 60);

	subject->update();

	CPPUNIT_ASSERT( subject->wentRight() );
}

void LightDirectionDetectorTest::updateWithLeftStronger_wentLeftShouldReturnTrue() 
{
	mock->setNextAnalogValueToReturn(0, 85);
	mock->setNextAnalogValueToReturn(1, 40);

	subject->update();

	CPPUNIT_ASSERT( subject->wentLeft() );

}

void LightDirectionDetectorTest::updateWithLeftProportionallyStronger_wentLeftShouldReturnTrue()
{
	mock->setNextAnalogValueToReturn(0, 122);
	mock->setNextAnalogValueToReturn(1, 60);

	subject->update();

	CPPUNIT_ASSERT( subject->wentLeft() );
}


void LightDirectionDetectorTest::updateWithEqualStrength_wentRightAndWentLeftShouldReturnFalse()
{
	mock->setNextAnalogValueToReturn(0, 80);
	mock->setNextAnalogValueToReturn(1, 40);

	subject->update();

	CPPUNIT_ASSERT( !subject->wentRight() );
	CPPUNIT_ASSERT( !subject->wentLeft() );
}


void LightDirectionDetectorTest::updateWithAlmostEqualStrength_wentRightAndWentLeftShouldReturnFalse()
{
	mock->setNextAnalogValueToReturn(0, 86);
	mock->setNextAnalogValueToReturn(1, 41);

	subject->update();

	CPPUNIT_ASSERT( !subject->wentRight() );
	CPPUNIT_ASSERT( !subject->wentLeft() );
}

void LightDirectionDetectorTest::setUp(void) 
{
	mock = new ArduinoMockApi(2);
	mock->setNextAnalogValueToReturn(0, 80);
	mock->setNextAnalogValueToReturn(1, 40);

	int leftPin  = 0;
	int rightPin = 1;
	subject = new LightDirectionDetector(leftPin,rightPin,mock);
}

void LightDirectionDetectorTest::tearDown(void) 
{
	delete mock;
}

