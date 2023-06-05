#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TDD10_DD/DeviceDriver.cpp"
#include "../TDD10_DD/app.cpp"

using namespace std;
using namespace testing;

class MockDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestCaseName, TestNameFiveRead) {

	MockDevice mock_device;
	EXPECT_CALL(mock_device, read)
		.Times(5);

	DeviceDriver driver(&mock_device);
	driver.read(0xA);
}

TEST(TestCaseName, RaiseReadFailException) {
	MockDevice mock_device;
	//스터빙 4번은 잘 읽히는데 5번째 다른값이 읽힐 때
	EXPECT_CALL(mock_device, read(0x2))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x3));

	DeviceDriver driver(&mock_device);
	EXPECT_THROW(driver.read(0x2), ReadFailException);
}

TEST(TestCaseName, ReadTest) {
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(0x2))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7));

	DeviceDriver driver(&mock_device);
	EXPECT_EQ(0x7, driver.read(0x2));
}

TEST(TestCaseName, WhenWriteThenReadeOneTime) {
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(0xC))
		.Times(1)
		.WillOnce(Return(0xFF));

	DeviceDriver driver(&mock_device);
	driver.write(0xC, 787);
}

TEST(TestCaseName, WhenWriteThen0xFE) {
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(0xC))
		.WillOnce(Return(0xFE));

	DeviceDriver driver(&mock_device);
	EXPECT_THROW(driver.write(0xC, 777), WriteFailException);
}

TEST(TestCaseName, Application_read) {
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(_))
		.Times(25);

	DeviceDriver driver(&mock_device);
	Application app(&driver);

	app.ReadAndPrint(0x00, 0x04);
}


TEST(TestCaseName, Application_write) {
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(_))
		.Times(5)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mock_device, write(_, _))
		.Times(5);

	DeviceDriver driver(&mock_device);
	Application app(&driver);

	app.WriteAll(0x7);
}