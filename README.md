# iolairPanelMeter
Voltmeter and ammeter design that fits inside a Chi Tai case.

```
Supply - 7-32v DC
Voltmeter range - 0 - 36v DC
Ammeter - any shunt with a +-50mV output (max +-80mV)
Protection - 100mA fuses on power supply and both sense inputs.
Power consuption - 0.18w at standard brightness,0.36w when super bright.
```

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
// For a 24v boat, the 122 and 148 above should be 244 and 296 assuming you want to alarm at or below 24.4v and at or above 29.6v
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

## Test code to cycle the display
```sh
#include <IolairPanelMeter.h>

IolairPanelMeter Panel;

void setup()
{
    Panel.begin();
}


void loop()
{
    for (int8_t i = 0; i < 10; i++)
    {
        Panel.DisplayInteger(i * 111, false);
        Panel.SetBrightness(i);
        delay(1000);
    }
    for (int8_t i = -9; i < 1; i++)
    {
        Panel.DisplayInteger(i * 111, true);
        Panel.SetBrightness(15);
        delay(1000);
    }
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

``` SetCalibration(uint16_t)```
Calibrate the reading. For DC volts the calibration should be 800.
For AC amps the calibration should be (200,000 / shunt capacity)
so for a 50mV - 300A shunt the calibration is 666
for a 50mV - 500A shunt the calibration is 400
Calibrations can be tweaked if needed.
Using a Fluke 325 clamp meter to calibrate, my 500A shunt has a calibration number of 406


``` Clear()```
Clear the display.

``` SetBrightness(uint8_t)```
Set the brightness level of the display.
The range is 0 to 15.
A level of 1 matches my existing displays.


``` DisplayInteger(int32_t, bool)```
int32_t is the integer to display. If the number is outside of the range -999 to 999
then ERR is shown.
bool is for the decimal point.
All values are integers so to display 12.8 the command is DisplayInteger(128, true)
To display 128 the command is DisplayInteger(128, false)


``` DisplayError()```
Show ERR on the display


``` GetDcVolts()```
Return the measured voltage multiplied by 10. 12.8v is returned as 128

``` GetDcAmps()```
Return the shunt measurment as an integer.


# Programming

Programming1 are the ICSP pins used to put the initial bootloader onto the ATmega328. Either solder on pins or use PogoPins. Uploading a bootloader only needs to happen once.

https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP

Once the boatloader is uploaded, the board is programmed as an Arduino Uno using a FT232 USB to TTL Serial adapter set to 5v.

Using 3.3v will not work!

Note that the CTS pin of the TF232 is not used.

![Programming](https://user-images.githubusercontent.com/24658072/197359772-437d15f7-9625-44b8-aa52-71ec670c641e.jpeg)

# Manufacture
There are two PCBs that make up the panel meter, the main panel and a carrier for the 7 segment display,

Board Manufacture.zip contains the Gerber files to have the boards made. The files are formatted to match the requirements of JLC https://jlcpcb.com/

Drag the gerber zip into the JLC website. Almost all the defaults that they use are good. The boards should be 1.6mm thick, my preference is for ENIG gold finish. 

The main panel zip includes the CSV files needed to have the smd components added at source.

This PDF shows the JLC website settings to order the main board. Note that the JLC website can be a bit flaky. If something doesn't work, you may need to close the browser and start again. Sometimes the Gerbers don't upload properly and often the page that shows after the SMDs have been rendered throws a System Error.

[PCB Order & Online PCB Quote & PCB Assembly Quote - JLCPCB.pdf](https://github.com/NeilSWells/iolairPanelMeter/files/9863375/PCB.Order.Online.PCB.Quote.PCB.Assembly.Quote.-.JLCPCB.pdf)

Unfortunately no manufacturer can supply the IC used on the display board so it needs to be hand soldered along with it's associated capacitor. Not too hard if you order a solder stencil at the same time. You will need SMD solder, I used ChipQuik SMD291SNLT4. Remember to keep it in the fridge to extend the shelf life.

![Boards](https://user-images.githubusercontent.com/24658072/197359983-6b79fd06-d3c4-4280-88e6-9469cef94759.jpeg)

# Parts

As well as the parts that come on the partially populated board, you will also need:

## Main Board

Connector - MSTBA 2.5/ 6-G-5.08

https://www.digikey.com/en/products/detail/phoenix-contact/1757284/260478

Serial connector - 5 Pin Single Row Right Angle Female Pin Header 2.54MM

https://www.aliexpress.com/item/1005004359055976.html?spm=a2g0o.productlist.main.57.7bfb11b0XPKc1e&algo_pvid=265b342e-a6a2-4457-8f7a-e0cb992ca9f1&algo_exp_id=265b342e-a6a2-4457-8f7a-e0cb992ca9f1-28&pdp_ext_f=%7B%22sku_id%22%3A%2212000028895783815%22%7D&pdp_npi=2%40dis%21GBP%211.06%211.05%21%21%211.58%21%21%40210212c016666425916368740d077f%2112000028895783815%21sea&curPageLogUid=G6dt4OWggIbB

Programming1 - 2x3P 2.54mm Double Row Straight Female 6 Pin Header Socket. On the pictures I used male pins but on reflection female is probably better.

https://www.aliexpress.com/item/1005004209994934.html?spm=a2g0o.productlist.main.53.572e2043zlW8sw&algo_pvid=a05b52f4-6a6d-4096-9989-64749e905f37&aem_p4p_detail=20221024132210682855019617080000820094&algo_exp_id=a05b52f4-6a6d-4096-9989-64749e905f37-26&pdp_ext_f=%7B%22sku_id%22%3A%2212000028484862390%22%7D&pdp_npi=2%40dis%21GBP%210.75%210.75%21%21%211.87%21%21%4021227d8316666429301275168d074f%2112000028484862390%21sea&curPageLogUid=yDPEOnpsfxnA&ad_pvid=20221024132210682855019617080000820094_27&ad_pvid=20221024132210682855019617080000820094_27

C1 - 10uF, 50v, 5mm diameter, 2mm lead pitch

https://www.digikey.com/en/products/detail/panasonic-electronic-components/EEU-EB1H100S/512997

PSU1 - Recom R-785.0-0.5

https://www.digikey.com/en/products/detail/recom-power/R-785-0-0-5/2256217

Crystal 1 - 16Mhz crystal

https://www.digikey.com/en/products/detail/iqd-frequency-products/LFXTAL027945BULK/10106622?s=N4IgTCBcDaIDIDEAaAVAgnADGA7ATgBYBWAIQFcAbAaxAF0BfIA

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

## Assembly

### Display board

Start by carefully snapping the mousebite perforations that hold the two support legs to the display board. Using needle nose (long nose) pliers helps. If there are rough edges on the bottom of the display board these can be removed with a sharp knife. Otherwise they will stop the board from seating properly on the main pcb.

Solder the two SMD components U1 and C1.

Add the display connector on the same side. Make sure it's the right way up. Snip off any excess on the connector pins.

Add the 7 segment display to the other side. The decimal points should be adjacent to the little tab sticking out from the base of the board. Make sure that the display is parallel to the white rectangle on the PCB. I lightly solder one central pin to tack the part in place. You can then hold the board and align the part by briefly re-melting the soldered pin. Only once you're happy with the alignment, solder the rest of the pins. This technique works well for the rest of the multi pin components.

### Main board

Start with the crystal. There is no correct way around.

Add the five pin angled socket for Serial1.

Add the six pin socket for Programming1. If you're making a lot of boards, the alternative is to leave Programming1 empty and use one of these to make the contacts while you put the bootloader on: (6 pin, double row, 2.54mm)

https://www.aliexpress.com/item/1005002713845793.html?spm=a2g0o.order_list.0.0.42b618023tyW8I

Add the display connector. Again make sure that it's the correct way around.

At this point the board can be bootloaded and programmed. You may want to do that now before adding C1 and PSU1 since they are expensive parts and only used when the board is powered from the boat or test battery. During programming, the board is powered by the bootloading Arduino or by the FT232 programmer. 

Temporarily connect the display.

Add the bootloader.

Add the test program. Don't forget to add the IolairPanelMeter library to your Arduino environment before uploading. If you're new to Arduino I can walk you through this. Finding the right COM port can be tricky. In Arduino, take a note of the available ports before plugging in the FT232.

If everything works, the display will cycle from 000 to 999 getting brighter as it goes. It then cycles from -99.9 to 00.0 at full brightness.

Add C1 - the orientation matters. The negative stripe on the side of the capacitor should line up with the white marked half of C1 on the board (Opposite side to the Iolair logo)

Add PSU1 - again, orientation matters. It should fit within the white rectangle.

Test again.

If everything works, use hot melt glue to assemble the display panel to the main panel using the two supports that were removed from the display board at the start.

## PCB Design Files

The design files can be edited using KiCad V6, an excellent free design package.

https://www.kicad.org/


## Contact
If you have any questions or suggestions, email NeilSWells@gmail.com

The use of this design is entirely at your own risk.

## License

MIT

![image](https://user-images.githubusercontent.com/24658072/197385055-576c071d-7609-4a10-96d0-5cf6296e2c80.png)

![image](https://user-images.githubusercontent.com/24658072/197385121-8fc22529-fee2-410b-8cf7-33bfc2d290cb.png)


