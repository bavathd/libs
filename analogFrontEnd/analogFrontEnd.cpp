#include "Arduino.h"
#include <Wire.h>

#include <analogFrontEnd.h>

#define SLOTA_OFFSET (0)
#define SLOTB_OFFSET (4)



analogFrontEnd::ADI_DCFG_t dcfg_ADPD188BI[] = 
{
  { 0x01, 0xC0, 0xFF },
  { 0x02, 0x00,0x05 },
  { 0x06, 0x00, 0x01 },
  { 0x0C, 0x00, 0x0F },
  { 0x10, 0x00, 0x01 },
  { 0x11, 0x30, 0xA9 },
  { 0x27, 0x08, 0x00 },
  { 0x29, 0xA0, 0x0A },
  { 0x13, 0x01, 0x90 },
  { 0x2A, 0x90, 0x00 },
  { 0x2B, 0x8F, 0x00 },
  { 0x2C, 0x94, 0x00 },
  { 0x2D, 0x92, 0x00 },
  { 0x33, 0x01, 0x13 },
  { 0x3A, 0x22, 0xD4 },
  { 0x12, 0x02, 0x00 },
  { 0x15, 0x00, 0x00 },
  { 0x14, 0x01, 0x1D },
  { 0x18, 0x00, 0x00 },
  { 0x19, 0x3F, 0xFF },
  { 0x1A, 0x3F, 0xFF },
  { 0x1B, 0x3F, 0xFF },
  { 0x31, 0x04, 0x0E },
  { 0x39, 0x22, 0xE0 },
  { 0x42, 0x1C, 0x34 },
  { 0x17, 0x00, 0x09 },
  { 0x1E, 0x00, 0x00 },
  { 0x1F, 0x3F, 0xFF },
  { 0x20, 0x3F, 0xFF },
  { 0x21, 0x3F, 0xFF },
  { 0x36, 0x04, 0x0E },
  { 0x3B, 0x22, 0xE0 },
  { 0x44, 0x1C, 0x34 },
  { 0x1D, 0x00, 0x09 },
  { 0x58, 0x05, 0x44 },
  { 0x22, 0x35, 0x39 },
  { 0x23, 0x35, 0x36 },
  { 0x24, 0x15, 0x30 },
  { 0x4B, 0x26, 0x9A },
  { 0x4D, 0x00, 0x90 },
  { 0xFF, 0xFF, 0xFF } // Terminator
};


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
        //powerState(true);
        SoftReset();
        return true;
    }
    else {
        //powerState(false);
        return false;
        
    }
    
}


/*void analogFrontEnd::powerState(bool power) {
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
*/
void analogFrontEnd::modeSelection(uint8_t mode) {
        resetBitPosition(MODE, 0);
        resetBitPosition(MODE, 1);
      switch(mode) {
        case 0:
            if(!isRegisterReset(SAMPLE_CLK, 7)){ 
            resetBitPosition(SAMPLE_CLK, 7);
            }
            resetBitPosition(MODE, 0);
            resetBitPosition(MODE, 1);
            Serial.println("MODE 0");
            break;
        case 1:
        /*
            setBitPosition(SAMPLE_CLK, 7);
            setBitPosition(MODE, 0);
            if(isRegisterSet(MODE, 0)==true) {
            setBitPosition(SLOT_EN,0);
            if(isRegisterSet(SLOT_EN,0)== true) {
                Serial.println("SlotA Enabled");
            }
            else {
                Serial.println("Slot A Failed");
            }
            }
            else{
                Serial.println("MODE P Failed");
            }
            */
            SoftReset();
            setBitPosition(MODE, 0);
            if(isRegisterSet(MODE, 0)==true) {
                uint8_t clear[] = {0x00, 0xFF};
                writeRegister(INT_STATUS, clear);
                uint8_t clear1[] = {0x80, 0xFF};
                writeRegister(INT_STATUS, clear1);
               
                
                uint8_t* data = readRegister(INT_STATUS);
                
                Serial.println(data[0]);
                Serial.println(data[1]);
                uint8_t f = load_DCfg(dcfg_ADPD188BI);
                Serial.print("config = ");
                Serial.println(f);
                Serial.println("MODE 1 completed");
               
            

            }

           
        
            break;

        case 2:
            
            setBitPosition(MODE, 1);
            uint8_t* data = readRegister(MODE);
            Serial.println("MODE 2");
            Serial.println("MODE DTA NORMAL====");
            Serial.println(data[0]);
            Serial.println(data[1]);


            break;

            

      }
}

uint8_t analogFrontEnd::load_DCfg(ADI_DCFG_t *pnCfg) {
   Serial.println("LOADING DATA.....");
    uint8_t nRegAddr;
    uint8_t nRegData[2];
    uint8_t nRet = 0;
    uint8_t nvalue = 0;
    nRegData[0] = 0x29;
    nRegData[1] = 0x95;
    writeRegister(0x4B, nRegData);
    delay(100);
    uint8_t* newData = readRegister(0x4B);
    Serial.println((newData[0]<<8|newData[1]), HEX);
    delay(100);
    nRegData[0] = 0x42;
    nRegData[1] = 0x72;
    writeRegister(0x4D, nRegData);
    delay(100);
    uint8_t* newData_1 = readRegister(0x4D);
    Serial.println("next data is");
    Serial.println((newData_1[0]<<8|newData_1[1]), HEX);
    delay(100);
    if(pnCfg==0) {
        return -1;
    }

    int8_t idx =0;
    while(1) {
        nRegAddr = pnCfg[idx].addr;
        nRegData[0] = pnCfg[idx].value_1;
        nRegData[1] = pnCfg[idx].value_2;
        Serial.println(idx);
        idx++;
        Serial.println(idx);
        if(nRegAddr == 0xFF)
            break;
        writeRegister(nRegAddr, nRegData);
        delay(100);
        uint8_t* newData = readRegister(nRegAddr);
        Serial.println((newData[0]<<8|newData[1]), HEX);
        delay(500);
    }

    

    return 0;

}

void analogFrontEnd::readData(void) {

   uint8_t* Int = readRegister(INT_STATUS);
   Serial.println(Int[0],HEX);
   Serial.println((Int[0]<<8|Int[1]),HEX);
   Serial.println(Int[0]);
   uint8_t* Data_11 = readRegister(0x11);
   
   Serial.println((Data_11[0]<<8|Data_11[1]),HEX);
   Serial.println();
   uint8_t SlotAB[8];
    
   if(Int[0]!=0) {
            if((Int[0] & 0xFF)<=64) 
            {
                 Adafruit_BusIO_Register reg = Adafruit_BusIO_Register(i2c_dev, FIFO_ACCESS);
    
    
                reg.read(SlotAB, 8);
                delay(1000);
                
            }

            Serial.println(SlotAB[0]);
            Serial.println(SlotAB[1]);
            Serial.println(SlotAB[2]);
            Serial.println(SlotAB[3]);
            Serial.println(SlotAB[4]);
            Serial.println(SlotAB[5]);
            Serial.println(SlotAB[6]);
            Serial.println(SlotAB[7]);
            delay(1000);
   }

   
    /*
    setBitPosition(DATA_ACCESSS_CTL, 1);
    if(isRegisterSet(DATA_ACCESSS_CTL, 1)==true) {
        static uint8_t* buff = readRegister(FIFO_ACCESS);
        Serial.println(buff[0]);
        Serial.println(buff[1]);
        Serial.println("successs");
        resetBitPosition(DATA_ACCESSS_CTL, 1);
        if(isRegisterReset(DATA_ACCESSS_CTL,1)==true) {
            Serial.println("Succesfull reset");
        }

        

    }

    else {
        Serial.println("FAiled");
    }
   
*/
/*
uint8_t slotAB[8];
uint32_t slotA;
uint32_t slotB;
uint8_t int_data[2];


while(true)
{    int_data = readRegister(0x00);  
    while(int_data != 0) {
        delay(100);
    if(((int_data[0] & 0xFF) >= sizeof(slotAB))) {
        int cy = readFIFO((uint8_t *)slotAB, sizeof(slotAB));
        slotA = (slotAB[SLOTA_OFFSET + 2] << 24) | 
              (slotAB[SLOTA_OFFSET + 3] << 16) |
              (slotAB[SLOTA_OFFSET + 0] << 8)  | 
              (slotAB[SLOTA_OFFSET + 1]);
      
      slotB = (slotAB[SLOTB_OFFSET + 2] << 24) | 
              (slotAB[SLOTB_OFFSET + 3] << 16) |
              (slotAB[SLOTB_OFFSET + 0] << 8)  | 
                (slotAB[SLOTB_OFFSET + 1]);

    Serial.println(slotA);
    Serial.println(slotB);

    }
    }
}
 */
    // uint8_t* SlotAB;
    // uint8_t* int_data;
    // int_data =  readRegister(INT_STATUS);
    // SlotAB = readFIFO(8);
    //             Serial.println(SlotAB[0]);
    //             Serial.println(SlotAB[1]);
    //             Serial.println(SlotAB[2]);
    //             Serial.println(SlotAB[3]);
    //             Serial.println(SlotAB[4]);
    //             Serial.println(SlotAB[5]);
    //             Serial.println(SlotAB[6]);
    //             Serial.println(SlotAB[7]);
    /*            Serial.println("The Data is above");
    if(int_data[0]!=0) {
            if((int_data[0] & 0xFF)<=8) 
            {
                SlotAB = readFIFO(8);
                Serial.println(SlotAB[0]);
                Serial.println(SlotAB[1]);
                Serial.println(SlotAB[2]);
                Serial.println(SlotAB[3]);
                Serial.println(SlotAB[4]);
                Serial.println(SlotAB[5]);
                Serial.println(SlotAB[6]);
                Serial.println(SlotAB[7]);
            }
            */
        }


        
    
    





uint8_t* analogFrontEnd::readFIFO(uint8_t nDataSetSize) {
    uint8_t nAddr = FIFO_ACCESS;
    uint8_t* data;
    readRegisterLong(nAddr, data, nDataSetSize);
    return data;

    
}
/*
int16_t analogFrontEnd::readFIFO(uint16_t *pnData, uint16_t nDataSetSize) {
    uint8_t nAddr = FIFO_ACCESS;

    if(nDataSetSize==0) {
        return -1;
    }
    
    readRegisterLong((uint8_t *) &nAddr, pnData, nDataSetSize);

    return 0;
}

*/
void analogFrontEnd::terminateData() {
    modeSelection(1);
    uint8_t clear[] = {0x00, 0xFF};
    writeRegister(INT_STATUS, clear);
    uint8_t clear1[] = {0x80, 0xFF};
    writeRegister(INT_STATUS, clear1);
    modeSelection(0);
    Serial.println("dataTerminated");

}

void analogFrontEnd::SoftReset() {   
    setBitPosition(SW_RESET,0);
}


/*   I2C settings */
void analogFrontEnd::writeRegister(uint8_t addr, uint8_t* byte16) {
    Adafruit_BusIO_Register reg = Adafruit_BusIO_Register(i2c_dev, addr);
    reg.write(byte16, 2);


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
        if((data[1] & mask) != 0)
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
int16_t analogFrontEnd::readRegisterLong(uint8_t addr, uint8_t* data, uint8_t size) {
    
    Adafruit_BusIO_Register reg = Adafruit_BusIO_Register(i2c_dev, addr);
    
    
    reg.read(data, size);
    return 0;

}


