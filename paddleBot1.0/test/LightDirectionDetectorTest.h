#include <stdint.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "ArduinoMockApi.h"
#include "../LightDirectionDetector.h"
#include "LightFollowerMock.h"

class LightDirectionDetectorTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( LightDirectionDetectorTest );
	CPPUNIT_TEST( updateWithRightStronger_shouldReturnTurnRight );
	CPPUNIT_TEST( updateWithRightProportionallyStronger_shouldReturnTurnRight );
	CPPUNIT_TEST( updateWithBothWeakButLeftStronger_ShouldReturnLeft );
	CPPUNIT_TEST( updateWithLeftProportionallyStronger_shouldReturnTurnLeft );
	CPPUNIT_TEST( updateWithWeakStrenghAndWeakPrevious_shouldReturnTurnRight );
	CPPUNIT_TEST( updateWithBothEyeStrong_shouldReturnGoAhead );
	CPPUNIT_TEST( updateWithBothWeak_FirstTime_shouldReturnRight );
	CPPUNIT_TEST( updateWithBothWeak_PreviousStrongWasLeft_shouldReturnLeft );
	CPPUNIT_TEST( updateWithBothWeak_PreviousStrongWasRight_shouldReturnRight );
	CPPUNIT_TEST( updateWithLeftStrong_ShouldRaiseStrongThresholdLevel );
	CPPUNIT_TEST( updateWithBothStrongAndThenWeakFewTimes_ShouldGoAhead );
	CPPUNIT_TEST( updateWithFollowerUnableToMoveNow_ShouldeepLastMoveButWillStoreLastDirection );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(void);
	void tearDown(void); 

	void updateWithRightStronger_shouldReturnTurnRight();
	void updateWithRightProportionallyStronger_shouldReturnTurnRight();
	void updateWithBothWeakButLeftStronger_ShouldReturnLeft();
	void updateWithLeftProportionallyStronger_shouldReturnTurnLeft();
	void updateWithWeakStrenghAndWeakPrevious_shouldReturnTurnRight();
	void updateWithBothEyeStrong_shouldReturnGoAhead();

	void updateWithBothWeak_FirstTime_shouldReturnRight();
	void updateWithBothWeak_PreviousStrongWasLeft_shouldReturnLeft();
	void updateWithBothWeak_PreviousStrongWasRight_shouldReturnRight();
	void updateWithLeftStrong_ShouldRaiseStrongThresholdLevel();
	void updateWithBothStrongAndThenWeakFewTimes_ShouldGoAhead();

	void updateWithFollowerUnableToMoveNow_ShouldeepLastMoveButWillStoreLastDirection();

private:	
	void assertDirection(Direction expectedDirection);

	int getStrongLeft();
	int getStrongRight();

	ArduinoMockApi * mock; 
	LightDirectionDetector * subject;
	LightFollowerMock mockFollower;
	int strongLeftThreshold;
	int strongRightThreshold;
};
