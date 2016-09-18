#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "PaperBotTest.h"
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( PaperBotTest );

int invokeCount = 0;
void writeCallback(int angle){
	invokeCount++;
}

void PaperBotTest::go_happyDay()
{
	subject = new PaperBotExtended();
	subject->setThrustCallback(writeCallback);

	auto theQueue = subject->getQueue();

	subject->go(mdLeft, 127);

	CPPUNIT_ASSERT_EQUAL( string("thrust"),  string(theQueue->head()->name) );

	subject->go(mdLeft, 127);
	subject->go(mdLeft, 127);

	CPPUNIT_ASSERT_EQUAL(1, invokeCount);
}
