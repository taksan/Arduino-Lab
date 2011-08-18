#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "ArduinoMockApi.h"
#include "../LightFollow.h"

class LightFollowTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( LightFollowTest );
	CPPUNIT_TEST( updateWithRightStronger_wentRightShouldReturnTrue );
	CPPUNIT_TEST( updateWithRightProportionallyStronger_wentRightShouldReturnTrue );
	CPPUNIT_TEST( updateWithLeftStronger_wentLeftShouldReturnTrue );
	CPPUNIT_TEST( updateWithLeftProportionallyStronger_wentLeftShouldReturnTrue );
	CPPUNIT_TEST( updateWithEqualStrenght_wentRightAndWentLeftShouldReturnFalse );

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(void);
	void tearDown(void); 

	void updateWithRightStronger_wentRightShouldReturnTrue(); 
	void updateWithRightProportionallyStronger_wentRightShouldReturnTrue();
	void updateWithLeftStronger_wentLeftShouldReturnTrue();
	void updateWithLeftProportionallyStronger_wentLeftShouldReturnTrue();
	void updateWithEqualStrenght_wentRightAndWentLeftShouldReturnFalse();
private:	
	ArduinoMockApi * mock; 
	LightFollow * subject;
};


