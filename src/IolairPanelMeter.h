// IolairPanelMeter - Panel meter code for custom PCB
// Copyright Neil Wells 2022  https://github.com/NeilSWells
// MIT License

#ifndef IOLAIR_PANEL_METER_h
#define IOLAIR_PANEL_METER_h

#include <Arduino.h>
#include <Wire.h>

//I2C constants
#define ADDRESS_DISPLAY 0x70
#define ADDRESS_INA226 0x40
#define DISPLAY_COMMAND_BRIGHTNESS 0xE0

#define BRIGHTNESS_LOW 1 //Min 0
#define BRIGHTNESS_HIGH 15 //Max 15


static const uint8_t displaySegmentMap[] =
{
    //The bits refer to the LEDs of a seven segment display.
    //Decimal point, middle bar, top left, bottlom left,  bottom bar, bottom right, top right, top bar
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111100, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01100111, // 9
    0b00000000, // Blank
    0b01000000, // Minus
    0b01111001, //E
    0b01010000  //r
};


class IolairPanelMeter
 {
    public:
    void begin();
    void SetCalibration(uint16_t calibration);
    void Clear();
    void SetBrightness(uint8_t brightness);
    void DisplayInteger(int32_t number, bool showDecimalPoint);
    void DisplayError();
    int32_t GetDcVolts();
    int32_t GetDcAmps();

    private:
    void SendCommand (uint8_t address, uint8_t command);
    void SendConfigCommand (uint8_t address, uint8_t registerAddress, uint8_t valueA, uint8_t valueB);
    int16_t ReceiveResult(uint8_t address);
    int16_t CalibrateReading(int32_t reading);
    void SendCharacters();
    uint8_t displayCharacter[4];
    uint8_t displayDigit[3];
    uint8_t displayBrightness;
    uint16_t calibrationFactor;
 };

#endif
