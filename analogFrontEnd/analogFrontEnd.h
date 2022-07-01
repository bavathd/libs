#include<Wire.h>
#include<Arduino.h>

//LED TIMING AND SAMPLE PARAMETERS
#define INT_STATUS                      0X00
#define INT_MASK                        0X01
#define GPIO_DRV                        0X02
#define BG_STATUS                       0X04
#define FIFO_THRESH                     0X06
#define DEVID                           0X08
#define I2CS_ID                         0X09
#define CLK_RATIO                       0X0A

#define GPIO_CTRL                       0X0B
#define SW_RESET                        0X0F
#define MODE                            0X10


#define SLOT_EN                         0X11
#define FSAMPLE                         0X12
#define PD_LED_SELECT                   0X14
#define NUM_AVG                         0X15



#define BG_MEAS_A                       0X16
#define INT_SEQ_A                       0X17
#define SLOTA_CH1_OFFSET                0X18
#define SLOTA_CH2_OFFSET                0X19
#define SLOTA_CH3_OFFSET                0X1A
#define SLOTA_CH4_OFFSET                0X1B


#define BG_MEAS_B                       0X1C
#define INT_SEQ_B                       0X1D
#define SLOTB_CH1_OFFSET                0X1E
#define SLOTB_CH2_OFFSET                0X1F
#define SLOTB_CH3_OFFSET                0X20
#define SLOTB_CH4_OFFSET                0X21


#define ILED3_COARSE                    0X22
#define ILED1_COARSE                    0X23
#define ILED2_COARSE                    0X24
#define ILED_FINE                       0X25



#define SLOTA_LED_PULSE                 0X30
#define SLOTA_NUMPULSES                 0X31
#define LED_DISABLE                     0X34
#define SLOTB_LED_PULSE                 0X35
#define SLOTB_NUMPULSES                 0X36
#define ALT_PWR_DN                      0X37
#define EXT_SYNC_STARTUP                0X38
#define SLOTA_AFE_WINDOW                0X39
#define SLOTB_AFE_WINDOW                0X3B
#define AFE_PWR_CFG1                    0X3C
#define SLOTA_FLOAT_LED                 0X3E
#define SLOTB_FLOAT_LED                 0X3F
#define SLOTA_TIA_CFG                   0X42
#define SLOTA_AFE_CFG                   0X43
#define SLOTB_TIA_CFG                   0X44
#define SLOTB_AFE_CFG                   0X45

#define SAMPLE_CLK                      0X4B
#define CLK32_ADJUST                    0X4D
#define EXT_SYNC_SEL                    0X4F
#define CLK32M_CAL_EN                   0X50
#define AFE_PWR_CFG2                    0X54
#define TIA_INDEP_GAIN                  0X55
#define MATH                            0X58


#define FLT_CONFIG_B                    0X59
#define FLT_LED_FIRE                    0X5A
#define FLT_CONFIG_A                    0X5E


#define DATA_ACCESSS_CTL                0X5F
#define FIFO_ACCESS                     0X60


#define SLOTA_PD1_16BIT                 0X64
#define SLOTA_PD2_16BIT                 0X65
#define SLOTA_PD3_16BIT                 0X66
#define SLOTA_PD4_16BIT                 0X67
#define SLOTB_PD1_16BIT                 0X68
#define SLOTB_PD2_16BIT                 0X69
#define SLOTB_PD3_16BIT                 0X6A
#define SLOTB_PD4_16BIT                 0X6B

#define A_PD1_LOW                       0X70
#define A_PD2_LOW                       0X71
#define A_PD3_LOW                       0X72
#define A_PD4_LOW                       0X73
#define A_PD1_HIGH                      0X74
#define A_PD2_HIGH                      0X75
#define A_PD3_HIGH                      0X76
#define A_PD4_HIGH                      0X77

#define B_PD1_LOW                       0X78
#define B_PD2_LOW                       0X79
#define B_PD3_LOW                       0X7A
#define B_PD4_LOW                       0X7B
#define B_PD1_HIGH                      0X7C
#define B_PD2_HIGH                      0X7D
#define B_PD3_HIGH                      0X7E
#define B_PD4_HIGH                      0X7F
