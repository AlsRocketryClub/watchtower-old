// ---------------------------------------------------- //
// LoRa.h
// ---------------------------------------------------- //
// Data: 04/09/2024
// Author: Kiryl Alsheuski
// ---------------------------------------------------- //

#define LORA_H

#include "spiRPI.h"

#define LORA_DEFAULT_SPI_FLAGS      (1<<m0)
#define LORA_DEFAULT_SPI_FREQUENCY  8E6 
#define LORA_DEFAULT_RESET_PIN      14
#define LORA_DEFAULT_DIO0_PIN       13
#define LORA_DEFAULT_SPI_CHANNEL    0

class LoRaClass
{
    private:
        int resetPin = LORA_DEFAULT_RESET_PIN;
        int dio0Pin = LORA_DEFAULT_DIO0_PIN;
        long frequency = LORA_DEFAULT_SPI_FREQUENCY;
        unsigned int spiFlags = LORA_DEFAULT_SPI_FLAGS;
        unsigned int spiChannel = LORA_DEFAULT_SPI_CHANNEL;

    public:
        LoRaClass();

};


