#include "Arduino.h"
#include <Wire.h>

#include <analogFrontEnd.h>

analogFrontEnd::analogFrontEnd(void)
{
}

analogFrontEnd::~analogFrontEnd(void)
{
}

bool analogFrontEnd::begin(uint8_t i2c_address, TwoWire *wire, int32_t sensor_id) {
    if(i2c_dev) {
        delete i2c_dev;
    }
    
    i2c_dev = new Adafruit_I2CDevice(i2c_address, wire);

    if(! i2c_dev -> begin()) {
        return false;
    }

    return _init(sensor_id);
}

bool analogFrontEnd::_init(int32_t sensor_id) {
    Adafruit_BusIO_Register chip_id = Adafruit_BusIO_Register(i2c_dev, MY_NAME_IS);
    
    if (chip_id.read() & 0xFC != MY_NAME_IS << 7) {
    return false;
  }
    Serial.println("data read");

    powerState(true);
    return true;
}

void analogFrontEnd::powerState(bool power){
    bool _power = power;
    if(_power == true) {
        
        writeRegister(SAMPLE_CLK, 0x12 | 0x0>>6 | 0x01>>7 |0x0>>8 & 0xFF);

    }
}

void analogFrontEnd::writeRegister(byte addr, byte data) {
    Adafruit_BusIO_Register reg = Adafruit_BusIO_Register(i2c_dev, addr);
    reg.write(data);
}

