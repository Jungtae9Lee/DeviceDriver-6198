#include <cstdio>

#include "DeviceDriver.h"

class Application {
public:
	explicit Application(DeviceDriver* driver)
		: driver(driver) {
	}

	void ReadAndPrint(int start, int end) {
		for (int addr = start; addr <= end; addr++) {
			int ret = driver->read(addr);
			printf("%d\n", ret);
		}
	}

	void WriteAll(int value) {
		for (int addr = 0x0; addr <= 0x4; addr++) {
			driver->write(addr, value);
		}
	}

private:
	DeviceDriver* driver;
};