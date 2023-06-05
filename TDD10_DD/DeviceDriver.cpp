#include "DeviceDriver.h"

#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

class ReadFailException : public std::exception {
};

class WriteFailException : public std::exception {
};

int DeviceDriver::read(long address)
{
    int firstReadTryValue = (int)(m_hardware->read(address));
    for (int tryCount = 2; tryCount <= 5; tryCount++) {
        int nextReadTryValue = (int)(m_hardware->read(address));
        if (firstReadTryValue == nextReadTryValue) continue;

        throw ReadFailException();
    }

    return firstReadTryValue;
}

void DeviceDriver::write(long address, int data)
{
    if ((int)m_hardware->read(address) != 0xFF) {
        throw WriteFailException();
    }
    m_hardware->write(address, (unsigned char)data);
}