#include <stdint.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "ArduinoMock.h"
#include "../MoveQueue.h"

class MoveQueueTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( MoveQueueTest );

	CPPUNIT_TEST( addAction_shouldAddToQueueEnd );

	CPPUNIT_TEST_SUITE_END();
public:
	void addAction_shouldAddToQueueEnd();
private:
	MoveQueue subject;
};
