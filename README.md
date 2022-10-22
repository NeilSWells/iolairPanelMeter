# iolairPanelMeter
Voltmeter and ammeter design that fits inside a Chi Tai case. As used on Nordhavn boats.
## Basic code for a voltmeter
```sh
#include <IolairPanelMeter.h>

IolairPanelMeter Panel;

int32_t result = 0;

void setup()
{
    Panel.begin();
    Panel.SetCalibration(800);
}


void loop()
{
     result = Panel.GetDcVolts();
     Panel.DisplayInteger(result, true); 
     if ((result > 122) && (result < 148)) Panel.SetBrightness(1);
     else Panel.SetBrightness(15);
}
```

## Basic code for a 50mV - 500A ammeter
```sh
#include <IolairPanelMeter.h>

IolairPanelMeter Panel;

int32_t result = 0;

void setup()
{
    Panel.begin();
    Panel.SetCalibration(400);
}


void loop()
{
     
     result = Panel.GetDcAmps();
     Panel.DisplayInteger(result, false);
     if ((result > -20) && (result < 50)) Panel.SetBrightness(1);
     else Panel.SetBrightness(15);
}
```

## Functions
    begin()
    SetCalibration(uint16_t);
    Clear()
    SetBrightness(uint8_t)
    DisplayInteger(int32_t, bool)
    DisplayError()
    int32_t = GetDcVolts()
    int32_t = GetDcAmps()

## Notes

### SetCalibration(uint16_t);
Calibrate the reading

For DC volts the calibration should be 800

For AC amps the calibration should be (200,000 / shunt capacity)
so for a 50mV - 300A shunt the calibration is 666
for a 50mV - 500A shunt the calibration is 400

Calibrations can be tweaked if needed.

Using a Fluke 325 clamp meter to calibrate, my 500A shunt has a calibration number of 406


### Clear()
Clear the display.

### SetBrightness(uint8_t)
Set the brightness level of the display.
The range is 0 to 15.
A level of 1 matches my existing displays.


### DisplayInteger(int32_t, bool)
int32_t is the integer to display. If the number is outside of the range -999 to 999
then ERR is shown.

bool is for the decimal point.

All values are integers so to display 12.8 the command is DisplayInteger(128, true)
To display 128 the command is DisplayInteger(128, false)


### DisplayError()
Show ERR on the display


### GetDcVolts()
Return the measured voltage multiplied by 10. 12.8v is returned as 128


### GetDcAmps()
Return the shunt measurment as an integer.


# Programming
Programming of the board is done with a FT232 USB to TTL Serial adapter set to 5v.

Using 3.3v will not work!

Note that the CTS pin of the TF232 is not used.


## Contact
https://github.com/NeilSWells

## License

MIT
