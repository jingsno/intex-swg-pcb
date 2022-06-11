# Intex SWG automaton

This is a PCB for Intex SWG Automation at
https://github.com/tonyflores1006/intex-swg-iot

Discussion here
https://www.troublefreepool.com/threads/automation-of-intex-swg.228606/

This PCB is suitable for both the TM1650 and the PIC16F88 version of the display board.

Software for the "non TM1650" (18 pin) version of the display board is under development.
(Current status of non released development version of the software, allows for fullt control of the Intex SWG from a web interface.)

Known models without the TM1650 chip:
* Intex Krystal Clear salt water system� ECO 6220 / CG-26670 (7-led/5 buttons), Max 56800 Liters

*PCB for Intex SWG automation*
![](docs/poster.png)


## Schematic

Link to [PDF Schematic](docs/intex-swg-pcb.pdf)

![Schematic](docs/schematic.png)


## Parts list

| Part            |             |
|-----------------|-------------|
| ESP32-DevkitC ext antenna |  https://www.digikey.com/en/products/detail/espressif-systems/ESP32-DEVKITC-32U/9357002 | $1600 |
| IRM-03-5 | https://www.digikey.com/en/products/detail/mean-well-usa-inc/IRM-03-5/7704640 |
| Level shifter to/from 5V/3.3V | https://www.aliexpress.com/item/1005001621978054.html | 
| 3.3V Relay module | https://www.aliexpress.com/item/32884967707.html | 
| 2x Female and 1x Male XH2.54 4pin connectors | https://www.aliexpress.com/item/4000126563819.html | 
| Stepper Motor cables/wire XH2.54 4pin | https://www.aliexpress.com/item/1005001361294507.html |
| Fuse 3A / 250V | https://www.aliexpress.com/item/32702176964.html | 
| 2-pin screw terminal | https://www.aliexpress.com/item/1005002971443405.html  | 
| 3-pin screw terminal | https://www.aliexpress.com/item/1005002971443405.html  | 
| 2x 3-pin header with jumper (or wire) | https://www.aliexpress.com/item/32873263301.html  | 


