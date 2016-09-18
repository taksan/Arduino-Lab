#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "MoveQueueTest.h"
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( MoveQueueTest );

int lastAngle = -1;
void writehook(int angle)
{
	lastAngle = angle;
}

void MoveQueueTest::addAction_shouldAddToQueueEnd()
{
	Servo * servo1 = new Servo();
	servo1->writecallback = writehook;
	subject.add("motor", servo1, 10, 10);

	Servo * servo2 = new Servo();
	subject.add("motor2", servo2, 11, 11);
	servo2->writecallback = writehook;

	CPPUNIT_ASSERT_EQUAL( string("motor"),  string(subject.head()->name) );
	CPPUNIT_ASSERT_EQUAL( subject.head()->isExpired(), false);
	subject.head()->execute();
	CPPUNIT_ASSERT_EQUAL( 10, lastAngle);

	subject.dequeue();

	CPPUNIT_ASSERT_EQUAL( string("motor2"),  string(subject.head()->name) );
	subject.head()->execute();
	CPPUNIT_ASSERT_EQUAL( 11, lastAngle);
}
