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
    uint8_t* chipId = readRegister(MY_NAME_IS);
    if(chipId[0] != 0) {
        Serial.print("Data_0: ");
        Serial.print(chipId[0]);
    
        Serial.print("Data_1: ");
        Serial.println(chipId[1]);
        powerState(true);
        return true;
    }
    else {
        powerState(true);
        return false;
        
    }
    
}


void analogFrontEnd::powerState(bool power) {
    bool _power = power;
    if(_power == true) {
        
        uint8_t* data =  readRegister(SAMPLE_CLK);
        Serial.print(data[0]);
        Serial.print("   ");
        Serial.println(data[1]);
        setBitPosition(SAMPLE_CLK, 7);
        data = readRegister(SAMPLE_CLK);
        Serial.print("after bit position= ");
        Serial.print(data[0]);
        Serial.print("   ");
        Serial.println(data[1]);
        resetBitPosition(SAMPLE_CLK, 7);
        data = readRegister(SAMPLE_CLK);
        Serial.print("after re bit position= ");
        Serial.print(data[0]);
        Serial.print("   ");
        Serial.println(data[1]);



    }
    else{}
}

uint8_t* analogFrontEnd::readRegister(uint8_t addr) {
    
    Adafruit_BusIO_Register reg = Adafruit_BusIO_Register(i2c_dev, addr);
    
    static uint8_t _buff[2];
    reg.read(_buff, 2);
    return _buff;    
}

// void analogFrontEnd::writeRegister(uint8_t addr, uint8_t buff, uint8_t const len ) {
//     Adafruit_BusIO_Register reg = Adafruit_BusIO_Register(i2c_dev, addr);
//     if(len == 0) {
//         reg.write(buff);
//     }
//     else {
//         for(int i=0; i<len; i++) {
//             reg.write(buff[i]);
//         }
//     }
// }

void analogFrontEnd::setBitPosition(uint8_t addr, uint8_t bitPosition) {
    uint8_t* data = readRegister(addr);
    Adafruit_BusIO_Register reg = Adafruit_BusIO_Register(i2c_dev, addr);
    if(bitPosition >7) {

        data[0] |= 1<<(bitPosition-8);
        reg.write(data, 2);
    }
    else {
    
        data[1] |= 1<<bitPosition;
        reg.write(data, 2);

    }
}

void analogFrontEnd::resetBitPosition(uint8_t addr, uint8_t bitPosition) {
    uint8_t* data = readRegister(addr);
    Adafruit_BusIO_Register reg = Adafruit_BusIO_Register(i2c_dev, addr);
    if(bitPosition >7) {
        
        
        data[0] &= ~(1<<(bitPosition-8));
        reg.write(data, 2);
        
    }
    else {
        
        data[1] &= ~(1<<bitPosition);
        reg.write(data, 2);
        
    }
}
    
bool analogFrontEnd::isRegisterSet(uint8_t addr, uint8_t bitPosition) 
{
    uint8_t* data = readRegister(addr);
    if(bitPosition > 7) {
        uint8_t mask = 1 << (bitPosition-8);
        if((data[0] & mask) != 0)
                return true;
        else
                return false;
    }
    else {
        
        uint8_t mask = 1 << bitPosition;
        if((value & mask) != 0)
                return true;
        else
                return false;

    }

}

bool analogFrontEnd::isRegisterReset(uint8_t addr, uint8_t bitPosition) 
{
    uint8_t* data = readRegister(addr);
    if(bitPosition > 7) {
        uint8_t mask = 1 << (bitPosition-8);
        if((data[0] & mask) == 0)
                return true;
        else
                return false;
    }
    else {
        
        uint8_t mask = 1 << bitPosition;
        if((data[1] & mask) == 0)
                return true;
        else
                return false;

    }

}



