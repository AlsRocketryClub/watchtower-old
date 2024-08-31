#include <pigpio.h>
#include <iostream>
#include <fmt/core.h> // For improved string formatting
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    // LED is connected to GPIO26 (physical pin 37)
    static const unsigned int LED_GPIO_PIN = 26; 
    static const unsigned int SpiChanel = 0;
    static const unsigned int SpiBaud = 40000;
    static const unsigned int SpiFlag = 0b0000000000000000000001;
    
    int gpioResult = 0;

    // Initialize the pigpio library
    cout << "Initializing pigpio... " << endl;
    gpioResult = gpioInitialise();
    if (gpioResult == PI_INIT_FAILED)
    {
        cout << "ERROR" << endl;
        cout << "Error value = " << gpioResult << endl;
        return -1;    
    }
    cout << "SUCCESS" << endl;

    cout << "Configuring LED on " << LED_GPIO_PIN << endl;

    // Configure the GPIO pin attached to the LED as a output pin
    // PI_OUTPUT is defined within the pigpio library
    gpioResult = gpioSetMode(LED_GPIO_PIN, PI_OUTPUT);

    // Check the result to ensure the GPIO pin could be properly configured
    if (gpioResult != 0) // A value of 0 = OK
    {
        switch (gpioResult)
        {
            case PI_BAD_GPIO:
            {
                cout << LED_GPIO_PIN << "is a bad gpio pin" << endl;
                return -1;
            }

            case PI_BAD_MODE:
            {
                cout << "Bad mode specified for gpio pin " << LED_GPIO_PIN << endl;
                return -1; 
            }

            default:
            {
                cout << "Unexpected error encountered when setting mode specified for gpio pin " << LED_GPIO_PIN << endl;
                cout << "Result = " << gpioResult << endl;
                return -1;
            }
        }
    }
    
    int SpiResult = spiOpen(SpiChanel, SpiBaud, SpiFlag);
    
    if(SpiResult != 0)
    {
        switch(SpiResult)
        {
            case PI_BAD_SPI_CHANNEL:
            {
                cout << "BAD SPI CHANNEL" << endl;
            }
            case PI_BAD_SPI_SPEED:
            {
                cout << "BAD SPI SPEED" << endl;
            }
            case PI_BAD_FLAGS:
            {
                cout << "BAD SPI FLAGS" << endl;
            }
            default:
            {
                cout << "Unexpectted spi error" << endl;
            }
        }
    }
    else
    {
        cout << "SPI SUCCES" << endl; 
    }
    
    int mode = 0;
    char buf[8];
    int length;
    int ibuf;
    unsigned int count = 1;
    int WriteResult;
    while (true)
    {
        cout << "Input length (max 8):";
        cin >> length;
        cout << "Input buf: ";
        for(int i=0; i<length; i++)
        {
            cin >> buf[i];  
        }
        //cin >> buf;
        //buf = ibuf;
        cout << "Send (1) or close (2): ";
        cin >> mode;
        
        
        if(mode == 1)
        {
            cout << "Buf: " << buf << " addr buf: " << &buf << endl;
            WriteResult = spiWrite(SpiResult, buf, length);
            switch(WriteResult)
            {
                case PI_BAD_HANDLE:
                {
                    cout << "Bad handle" << endl;
                }
                case PI_BAD_SPI_COUNT:
                {
                    cout << "Bad count" << endl;
                }
                case PI_SPI_XFER_FAILED:
                {
                    cout << "Transfer fail" << endl;
                }
                default:
                {
                    cout << "Ok" << endl; 
                }
            }
        }
        if(mode == 2)
        {
            spiClose(SpiResult);
            cout << "SPI closed" << endl;
            gpioTerminate();
            cout << "GPIO terminated" << endl;
            return 0;
        }
    }
    spiClose(SpiResult);
    // Terminate the pigpio library to clean up
    gpioTerminate();

    return 0;    
}
