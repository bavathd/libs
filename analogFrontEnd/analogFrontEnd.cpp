#include "Arduino.h"
#include <Wire.h>

#include <analogFrontEnd.h>

analogFrontEnd::analogFrontEnd(void)
{
}

analogFrontEnd::~analogFrontEnd(void)
{
}

bool analogFrontEnd::begin(uint8_t i2c_address, TwoWire *wire, uint8_t sensor_id) {
    if(i2c_dev) {
        delete i2c_dev
    }
    
    i2c_dev = new AdafruitI2CDevice(i2c_address, wire );

    if(!i2c_dev->begin()) {
        return false;
    }

    return _init(sensor_id);
}

bool analogFrontEnd::_init(int32_t sensor_id) {
    Adafruit_BusIO_Register(i2c_dev, MY_NAME_IS);

    if(chip_id.read() & 0xFC != DEV_ID << 7) {
        return false;
    }
    Serial.println("data read");
    return true;
}