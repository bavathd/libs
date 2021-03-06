#ifndef _ANALOGFRONEND_h
#define _ANALOGFRONEND_h




#include"Arduino.h"
#include <Adafruit_BusIO_Register.h>
#include<Adafruit_I2CDevice.h>
#include<Wire.h>



//LED TIMING AND SAMPLE PARAMETERS
#define INT_STATUS                      0x00
#define INT_MASK                        0x01
#define GPIO_DRV                        0x02
#define BG_STATUS                       0x04
#define FIFO_THRESH                     0x06
#define MY_NAME_IS                      0x08
#define I2CS_ID                         0x09
#define CLK_RATIO                       0x0A

#define GPIO_CTRL                       0x0B
#define SW_RESET                        0x0F
#define MODE                            0x10


#define SLOT_EN                         0x11
#define FSAMPLE                         0x12
#define PD_LED_SELECT                   0x14
#define NUM_AVG                         0x15



#define BG_MEAS_A                       0x16
#define INT_SEQ_A                       0x17
#define SLOTA_CH1_OFFSET                0x18
#define SLOTA_CH2_OFFSET                0x19
#define SLOTA_CH3_OFFSET                0x1A
#define SLOTA_CH4_OFFSET                0x1B


#define BG_MEAS_B                       0x1C
#define INT_SEQ_B                       0x1D
#define SLOTB_CH1_OFFSET                0x1E
#define SLOTB_CH2_OFFSET                0x1F
#define SLOTB_CH3_OFFSET                0x20
#define SLOTB_CH4_OFFSET                0x21


#define ILED3_COARSE                    0x22
#define ILED1_COARSE                    0x23
#define ILED2_COARSE                    0x24
#define ILED_FINE                       0x25



#define SLOTA_LED_PULSE                 0x30
#define SLOTA_NUMPULSES                 0x31
#define LED_DISABLE                     0x34
#define SLOTB_LED_PULSE                 0x35
#define SLOTB_NUMPULSES                 0x36
#define ALT_PWR_DN                      0x37
#define EXT_SYNC_STARTUP                0x38
#define SLOTA_AFE_WINDOW                0x39
#define SLOTB_AFE_WINDOW                0x3B
#define AFE_PWR_CFG1                    0x3C
#define SLOTA_FLOAT_LED                 0x3E
#define SLOTB_FLOAT_LED                 0x3F
#define SLOTA_TIA_CFG                   0x42
#define SLOTA_AFE_CFG                   0x43
#define SLOTB_TIA_CFG                   0x44
#define SLOTB_AFE_CFG                   0x45

#define SAMPLE_CLK                      0x4B
#define CLK32_ADJUST                    0x4D
#define EXT_SYNC_SEL                    0x4F
#define CLK32M_CAL_EN                   0x50
#define AFE_PWR_CFG2                    0x54
#define TIA_INDEP_GAIN                  0x55
#define MATH                            0x58


#define FLT_CONFIG_B                    0x59
#define FLT_LED_FIRE                    0x5A
#define FLT_CONFIG_A                    0x5E


#define DATA_ACCESSS_CTL                0x5F
#define FIFO_ACCESS                     0x60


#define SLOTA_PD1_16BIT                 0x64
#define SLOTA_PD2_16BIT                 0x65
#define SLOTA_PD3_16BIT                 0x66
#define SLOTA_PD4_16BIT                 0x67
#define SLOTB_PD1_16BIT                 0x68
#define SLOTB_PD2_16BIT                 0x69
#define SLOTB_PD3_16BIT                 0x6A
#define SLOTB_PD4_16BIT                 0x6B

#define A_PD1_LOW                       0x70
#define A_PD2_LOW                       0x71
#define A_PD3_LOW                       0x72
#define A_PD4_LOW                       0x73
#define A_PD1_HIGH                      0x74
#define A_PD2_HIGH                      0x75
#define A_PD3_HIGH                      0x76
#define A_PD4_HIGH                      0x77

#define B_PD1_LOW                       0x78
#define B_PD2_LOW                       0x79
#define B_PD3_LOW                       0x7A
#define B_PD4_LOW                       0x7B
#define B_PD1_HIGH                      0x7C
#define B_PD2_HIGH                      0x7D
#define B_PD3_HIGH                      0x7E
#define B_PD4_HIGH                      0x7F



#define SLAVE_ADDRESS                   0x64
#define DEV_ID                          0x16
#define REV_NUM                         0x0A
typedef enum {
    STANDBY_MODE,
    PROGRAM_MODE,
    NORMAL_MODE,
}analogFrontEnd_device_state;

class analogFrontEnd;

class analogFrontEnd
{
protected:
    virtual bool _init(int32_t sensor_id);
    Adafruit_I2CDevice *i2c_dev = NULL;
    
private:
    void writeRegister(byte addr, byte data);
  /* 
  condition
  */
public:
    analogFrontEnd();
    ~analogFrontEnd();
    bool begin(uint8_t i2c_addr = SLAVE_ADDRESS, TwoWire *wire = &Wire, 
            int32_t Sensor_id = 0);
    
    analogFrontEnd_device_state deviceState();

    void powerState(bool power);
    




};


#endif