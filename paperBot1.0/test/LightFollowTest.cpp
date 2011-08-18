#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "LightFollowTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( LightFollowTest );

void LightFollowTest::updateWithRightStronger_wentRightShouldReturnTrue() 
{
	mock->setNextAnalogValueToReturn(0, 80);
	mock->setNextAnalogValueToReturn(1, 60);

	subject->update();

	CPPUNIT_ASSERT( subject->wentRight() );
}

void LightFollowTest::updateWithRightProportionallyStronger_wentRightShouldReturnTrue()
{
	mock->setNextAnalogValueToReturn(0, 102);
	mock->setNextAnalogValueToReturn(1, 60);

	subject->update();

	CPPUNIT_ASSERT( subject->wentRight() );
}

void LightFollowTest::updateWithLeftStronger_wentLeftShouldReturnTrue() 
{
	mock->setNextAnalogValueToReturn(0, 85);
	mock->setNextAnalogValueToReturn(1, 40);

	subject->update();

	CPPUNIT_ASSERT( subject->wentLeft() );

}

void LightFollowTest::updateWithLeftProportionallyStronger_wentLeftShouldReturnTrue()
{
	mock->setNextAnalogValueToReturn(0, 122);
	mock->setNextAnalogValueToReturn(1, 60);

	subject->update();

	CPPUNIT_ASSERT( subject->wentLeft() );
}


void LightFollowTest::updateWithEqualStrenght_wentRightAndWentLeftShouldReturnFalse()
{
	mock->setNextAnalogValueToReturn(0, 80);
	mock->setNextAnalogValueToReturn(1, 40);

	subject->update();

	CPPUNIT_ASSERT( !subject->wentRight() );
	CPPUNIT_ASSERT( !subject->wentLeft() );
}

void LightFollowTest::setUp(void) 
{
	mock = new ArduinoMockApi(2);
	mock->setNextAnalogValueToReturn(0, 80);
	mock->setNextAnalogValueToReturn(1, 40);

	int leftPin  = 0;
	int rightPin = 1;
	subject = new LightFollow(leftPin,rightPin,mock);
}

void LightFollowTest::tearDown(void) 
{
	delete mock;
}

