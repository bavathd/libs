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
    
    uint8_t data[2];
    chip_id.read((uint8_t*)data, 2);
    Serial.print("data read=  ");
    Serial.print(data[0]);
    Serial.print(" / ");
    Serial.print(data[1]);
    Serial.println(data[0]<<8 | (data[1] & 0xff));
    
    
    

    return true;
}

void analogFrontEnd::powerState(bool power) {
    bool _power = power;
    if(_power == true) {
        
        uint16_t data =  readRegister(SAMPLE_CLK);
        Serial.println(data);

    }
    else{}
}

uint16_t analogFrontEnd::readRegister(uint8_t addr) {

     Adafruit_BusIO_Register reg = Adafruit_BusIO_Register(i2c_dev, addr);
     
     uint16_t data = reg.read();
     uint16_t data_1 = reg.read();
     
     return data;
}

    




