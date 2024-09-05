// ---------------------------------------------------- //
// LoRa.c
// ---------------------------------------------------- //
// Data: 04/09/2024
// Author: Kiryl Alsheuski
// ---------------------------------------------------- //

#include "LoRa.h"
#include <pigpio.h>

// registers
#define REG_FIFO                 0x00
#define REG_OP_MODE              0x01
#define REG_FRF_MSB              0x06
#define REG_FRF_MID              0x07
#define REG_FRF_LSB              0x08
#define REG_PA_CONFIG            0x09
#define REG_OCP                  0x0b
#define REG_LNA                  0x0c
#define REG_FIFO_ADDR_PTR        0x0d
#define REG_FIFO_TX_BASE_ADDR    0x0e
#define REG_FIFO_RX_BASE_ADDR    0x0f
#define REG_FIFO_RX_CURRENT_ADDR 0x10
#define REG_IRQ_FLAGS_MASK       0x11 //add
#define REG_IRQ_FLAGS            0x12
#define REG_RX_NB_BYTES          0x13
#define REG_PKT_SNR_VALUE        0x19
#define REG_PKT_RSSI_VALUE       0x1a
#define REG_RSSI                 0x1b //add
#define REG_MODEM_CONFIG_1       0x1d
#define REG_MODEM_CONFIG_2       0x1e
#define REG_PREAMBLE_MSB         0x20
#define REG_PREAMBLE_LSB         0x21
#define REG_PAYLOAD_LENGTH       0x22
#define REG_MODEM_CONFIG_3       0x26
#define REG_FREQ_ERROR_MSB       0x28
#define REG_FREQ_ERROR_MID       0x29
#define REG_FREQ_ERROR_LSB       0x2a
#define REG_RSSI_WIDEBAND        0x2c
#define REG_DETECTION_OPTIMIZE   0x31
#define REG_INVERTIQ             0x33
#define REG_DETECTION_THRESHOLD  0x37
#define REG_SYNC_WORD            0x39
#define REG_INVERTIQ2            0x3b
#define REG_DIO_MAPPING_1        0x40
#define REG_VERSION              0x42
#define REG_PA_DAC               0x4d

// modes
#define MODE_LONG_RANGE_MODE     0x80
#define MODE_SLEEP               0x00
#define MODE_STDBY               0x01
#define MODE_TX                  0x03
#define MODE_RX_CONTINUOUS       0x05
#define MODE_RX_SINGLE           0x06
#define MODE_CAD                 0x07 //add

// PA config
#define PA_BOOST                 0x80

// IRQ masks
#define IRQ_CAD_END_MASK           0x01
#define IRQ_CAD_DONE_MASK          0x04
#define IRQ_TX_DONE_MASK           0x08
#define IRQ_HEADER_MASK            0x10
#define IRQ_PAYLOAD_CRC_ERROR_MASK 0x20
#define IRQ_RX_DONE_MASK           0x40
#define IRQ_RX_TOUT_MASK           0x80

#define MAX_PKT_LENGTH           255

#define MAP_DIO0_LORA_RXDONE    0x00
#define MAP_DIO0_LORA_TXDONE    0x40
#define MAP_DIO0_LORA_CADDONE   0x80
#define MAP_DIO0_LORA_NOP       0xC0

#define MAP_DIO1_LORA_RXTOUT    0x00
#define MAP_DIO1_LORA_FCC       0x10
#define MAP_DIO1_LORA_CADDETECT 0x20
#define MAP_DIO1_LORA_NOP       0x30

#define MAP_DIO2_LORA_FCC0      0x00
#define MAP_DIO2_LORA_FCC1      0x04
#define MAP_DIO2_LORA_FCC2      0x08
#define MAP_DIO2_LORA_NOP       0x0C

#define MAP_DIO3_LORA_CADDONE   0x00
#define MAP_DIO3_LORA_HEADER    0x01
#define MAP_DIO3_LORA_CRC       0x02
#define MAP_DIO3_LORA_NOP       0x03

int LoRaClass::begin()
{
    int _gpioResult;

    //set up reset pin 
    _gpioResult = gpioSetMode(LoRaClass::resetPin, PI_OUTPUT);
    if(_gpioResult != 0)
    {
        return _gpioResult;
    }

    //perform reset
    gpioWrite(LoRaClass::resetPin, PI_LOW);
    gpioDelay(10000);
    gpioWrite(LoRaClass::resetPin, PI_HIGH);
    gpioDelay(10000);

    int _spiResult;
    _spiResult = spiOpen(LoRaClass::spiChannel, LoRaClass::spiFrequency, LoRaClass::spiFlags);
    
    if(_spiResult != 0)
    {
        return _spiResult;
    }
    
}
