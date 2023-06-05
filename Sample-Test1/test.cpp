#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TDD10_DD/DeviceDriver.cpp"

using namespace testing;
using namespace std;

class MockDevice : public FlashMemoryDevice{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address,unsigned char data), (override));
};

TEST(TestCaseName, TestnameFiveRead) {
	
	// 대역
	MockDevice mock_device;

	EXPECT_CALL(mock_device, read).Times(5);
	DeviceDriver driver(&mock_device);
	driver.read(0xA);

  //EXPECT_THAT(1, Eq(1));
}

TEST(TestCaseName, Exception) {
	MockDevice mock_device;
	// 스터빙 4버은 잘 읽히는데 5번째는 다른값이 읽힐때

	EXPECT_CALL(mock_device, read(0x2))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x3));

	DeviceDriver driver(&mock_device);
	EXPECT_THROW(driver.read(0x2), exception);
	

	//EXPECT_THAT(1, Eq(1));
}