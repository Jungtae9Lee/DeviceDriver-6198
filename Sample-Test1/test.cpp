#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TDD10_DD/DeviceDriver.cpp"

using namespace testing;
using namespace std;

TEST(TestCaseName, TestFiveRead) {
	// �����ϴ� �׽�Ʈ

  EXPECT_THAT(1, Eq(1));
}