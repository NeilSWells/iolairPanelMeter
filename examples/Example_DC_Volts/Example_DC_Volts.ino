#include <IolairPanelMeter.h>

IolairPanelMeter Panel;

int32_t result = 0;

void setup()
{
    Panel.begin();
    Panel.SetCalibration(800); //The calibration for DC volts should always be 800
}


void loop()
{
     result = Panel.GetDcVolts();
     Panel.DisplayInteger(result, true); //The second parameter is set to true to show a decimal point. All numbers are integers, so DisplayInteger(128,true) displays 12.8
     if ((result > 122) && (result < 148)) Panel.SetBrightness(1); //Set standard brightness if greater than 12.2v and less than 14.8v
     else Panel.SetBrightness(15);
}
