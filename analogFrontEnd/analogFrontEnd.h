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
#define FLT_CONFIG_b                    0X5A
