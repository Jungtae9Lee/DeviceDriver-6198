#include "DeviceDriver.h"
#include <exception>
using namespace std;

const int MAX_CNT =  4;
DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int result = (int)(m_hardware->read(address));

    for (int i = 0; i < MAX_CNT; ++i)   {
        int nextResult = (int)(m_hardware->read(address));
        if (result == nextResult) continue;
        throw exception("Exception!!");
    }

    return result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}