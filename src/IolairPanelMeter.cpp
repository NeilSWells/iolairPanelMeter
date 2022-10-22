#include "IolairPanelMeter.h"

//Public
void IolairPanelMeter::begin()
{
    Wire.begin();
    delay(50);
    SendCommand(ADDRESS_DISPLAY, 0b00100001); //Turn on the display system oscillator
    SendCommand(ADDRESS_DISPLAY, 0b10000001); //Set display on, blinking off
    Clear();
    SetBrightness(BRIGHTNESS_LOW);
}


void IolairPanelMeter::SetCalibration(uint16_t calibration)
{
    calibrationFactor = calibration;
}


void IolairPanelMeter::Clear()
{
    for (uint8_t b = 0; b < 4; b++) displayCharacter[b] = 0;
    SendCharacters();
}


void IolairPanelMeter::SetBrightness(uint8_t brightness)
{
    if (brightness != displayBrightness)
    {
        if (brightness > 15) brightness = 15;
        SendCommand(ADDRESS_DISPLAY, DISPLAY_COMMAND_BRIGHTNESS | brightness);
        displayBrightness = brightness;
    }
}


void IolairPanelMeter::DisplayInteger(int32_t number, bool showDecimalPoint)
{
    //Ensure the number is within bounds
    if ((number < -999) || (number > 999))
    {
        DisplayError();
        return;
    }
    //If the number is less than zero, set the first display character to the minus sign and invert the number for further calculations
    if (number < 0)
    {
        displayCharacter[0] = displaySegmentMap[11]; //Minus
        number *= -1;
    }
    else
    {
        displayCharacter[0] = displaySegmentMap[10]; //Space
    }
    //Split out the digits of the number
    displayDigit[0] = (number / 100);
    displayDigit[1] = (number / 10) % 10;
    displayDigit[2] = (number % 10);
    //Set each character to the corresponding value in the character map
    displayCharacter[1] = displaySegmentMap[displayDigit[0]];
    if (showDecimalPoint)
    {
        displayCharacter[2] = displaySegmentMap[displayDigit[1]] | 0b10000000;
    }
    else
    {
        displayCharacter[2] = displaySegmentMap[displayDigit[1]];
    }
    displayCharacter[3] = displaySegmentMap[displayDigit[2]];
    SendCharacters();
}


void IolairPanelMeter::DisplayError()
{
    displayCharacter[0] = displaySegmentMap[10]; //Space
    displayCharacter[1] = displaySegmentMap[12]; //E
    displayCharacter[2] = displaySegmentMap[13]; //r
    displayCharacter[3] = displaySegmentMap[13]; //r
    SendCharacters();
}


int32_t IolairPanelMeter::GetDcVolts()
{
    int32_t r = 0;
    SendConfigCommand(ADDRESS_INA226, 0x00, 0b01000110, 0b00110110);  //https://www.ti.com/lit/ds/symlink/ina226.pdf Averages = 64, Shunt Voltage Conversion Time = 4.156ms, Operating Mode = Bus Voltage Continuous
    delay(328);
    SendCommand(ADDRESS_INA226, 0x02); //Get the voltage reading
    delay(5);
    r = ReceiveResult(ADDRESS_INA226);
    r = CalibrateReading(r);
    return (r);
}


int32_t IolairPanelMeter::GetDcAmps()
{
    float r = 0; //Result from the ADC

    SendConfigCommand(ADDRESS_INA226, 0x00, 0b01000110, 0b00110101);  //https://www.ti.com/lit/ds/symlink/ina226.pdf Averages = 64, Shunt Voltage Conversion Time = 4.156ms, Operating Mode = Shunt Voltage Continuous
    delay(328);
    SendCommand(ADDRESS_INA226, 0x01); //Deliver the Shunt Voltage Register reading
    delay(5);
    r = ReceiveResult(ADDRESS_INA226);
    r = CalibrateReading(r);
    return ((int32_t)r);
}


//Private
void IolairPanelMeter::SendCommand (uint8_t address, uint8_t command)
{
    Wire.beginTransmission(address);
    Wire.write(command);
    Wire.endTransmission();
}


void IolairPanelMeter::SendConfigCommand (uint8_t address, uint8_t registerAddress, uint8_t valueA, uint8_t valueB)
{
    Wire.beginTransmission(address);
    Wire.write(registerAddress);
    Wire.write(valueA);
    Wire.write(valueB);
    Wire.endTransmission();
}


int16_t IolairPanelMeter::ReceiveResult(uint8_t address)
{
    Wire.requestFrom(address, (uint8_t)2); //Read the two byte result
    return ((Wire.read() << 8) | Wire.read()); //Get the two byte reading
}


int16_t IolairPanelMeter::CalibrateReading(int32_t reading)
{
    reading *= 10; //Multiply the reading by 10 to allow the calibration factor to be more precise
    reading /= calibrationFactor;
    return (reading);
}


void IolairPanelMeter::SendCharacters()
{
    //Send all the characters to the display
    Wire.beginTransmission(ADDRESS_DISPLAY);
    for (uint8_t b = 0; b < 4; b++)
    {
        Wire.write(b * 2);
        Wire.write(displayCharacter[b]);
    }
    Wire.endTransmission();
}
