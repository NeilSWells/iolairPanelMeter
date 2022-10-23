# iolairPanelMeter
Voltmeter and ammeter design that fits inside a Chi Tai case. As used on Nordhavn boats.

### Top
![Top](https://user-images.githubusercontent.com/24658072/197359806-8b2dcee5-0783-47a6-9445-05b5e5f142cf.jpeg)

### Front
![Front](https://user-images.githubusercontent.com/24658072/197359959-ebc9c957-7db6-4506-979e-60a78f7a8a27.jpeg)

### Back
![Back](https://user-images.githubusercontent.com/24658072/197359964-4637b575-6289-4332-b7ec-6d419240cf4f.jpeg)

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

Programming1 are the ICSP pins used to put the initial bootloader onto the ATmega328. Either solder on pins or use PogoPins. Uploading a bootloader only needs to happen once.

Once the boatloader is uploaded, the board is programmed as an Arduino Uno using a FT232 USB to TTL Serial adapter set to 5v.

Using 3.3v will not work!

Note that the CTS pin of the TF232 is not used.

![Programming](https://user-images.githubusercontent.com/24658072/197359772-437d15f7-9625-44b8-aa52-71ec670c641e.jpeg)

# Manufacture
There are two PCBs that make up the panel meter, the main panel and a carrier for the 7 segment display,

Board Manufacture.zip contains the Gerber files to have the boards made. The files are formatted to match the requirements of JLC https://jlcpcb.com/

Drag the gerber zip into the JLC website. Almost all the defaults that they use are good. The boards should be 1.6mm thick, my preference is for ENIG gold finish. 

The main panel zip includes the CSV files needed to have the smd components added at source.

Unfortunately no manufacturer can supply the IC used on the display board so it needs to be hand soldered along with it's associated capacitor. Not too hard if you order a solder stencil at the same time.

![Boards](https://user-images.githubusercontent.com/24658072/197359983-6b79fd06-d3c4-4280-88e6-9469cef94759.jpeg)

# Parts
## Main Board

Connector - MSTBA 2.5/ 6-G-5.08

Serial connector - 5 Pin Single Row Right Angle Female Pin Header 2.54MM

C1 - 10uF, 50v, 5mm diameter, 2mm lead pitch

PSU1 - Recom R.785.0-0.5

Crystal 1 - 16Mhz crystal

DisplayConnector - JST XH 2.54 4-Pin

https://www.aliexpress.com/item/32815799485.html?spm=a2g0o.order_list.0.0.1d831802rd1Fas

Display Connector Cable - 5cm 24 AWG XH2.54 4P Same Direction 

https://www.aliexpress.com/item/4000599744729.html?spm=a2g0o.order_list.0.0.1d831802rd1Fas

## Seven Segment Display Carrier

C1 - 0805 10uF

https://www.aliexpress.com/item/32964553793.html?spm=a2g0o.order_list.0.0.1d831802rd1Fas

U1 - Holtek HT16k33-24SOP

or Vinka VK16K33B-24SOP . They are available on AliExpress, be careful not to buy the more common SOP28 version

https://www.aliexpress.com/item/1005004738423851.html?spm=a2g0o.order_list.0.0.1d831802rd1Fas

7 Segment display - 4 Digit, 0.56 inch, Common Cathode, 12 pin

https://www.aliexpress.com/item/4000279476347.html?spm=a2g0o.order_list.0.0.1d831802rd1Fas

Don't add the 7 segment display until all the other components are soldered on the other side.


## PCB Design Files

The design files can be edited using KiCad V6, an excellent free design package.

https://www.kicad.org/


## Contact
https://github.com/NeilSWells

## License

MIT
