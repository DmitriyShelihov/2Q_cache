#include <iostream>
#include <list>
#include <unordered_map>
#include "include/2Q_cache.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	::testing::InitGoogleMock(&argc, argv);


	return RUN_ALL_TESTS();
}
