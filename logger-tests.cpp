#include <gtest/gtest.h>
#include "logger.h"

TEST( LoggerTest, InitializationTest )
{
	log::logger<log::log_DEBUG> logger;
	logger.log<log::log_NOTICE>("Hello. Printing a message of level NOTICE");	
	logger.log<log::log_WARNING>("Hello. Printing a message of level WARNING");	
}

int main( int argc, char *argv[] )	{
	::testing::InitGoogleTest( &argc, argv);
	return RUN_ALL_TESTS();
}
