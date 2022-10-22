#include <IolairPanelMeter.h>

IolairPanelMeter Panel;

int32_t result = 0;

void setup()
{
    Panel.begin();
    Panel.SetCalibration(666); //50mv-500A = 400   50mv-300A = 666
    //50mV is returned as 200000 so if 50mV = 300A then the calibration is 200000/300=666
}


void loop()
{
     
     result = Panel.GetDcAmps();
     Panel.DisplayInteger(result, false);
     if ((result > -20) && (result < 50)) Panel.SetBrightness(1); //Set standard brightness if less than 50A
     else Panel.SetBrightness(15);
}
