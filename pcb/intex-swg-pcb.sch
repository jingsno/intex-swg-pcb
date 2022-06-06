EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Intex SWG with jumpers"
Date "2022-06-06"
Rev "3.1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Converter_ACDC:HLK-PM03 PS1
U 1 1 6189BD04
P 2350 3400
F 0 "PS1" H 2350 3725 50  0000 C CNN
F 1 "HLK-PM03" H 2350 3634 50  0000 C CNN
F 2 "Converter_ACDC:Converter_ACDC_HiLink_HLK-PMxx" H 2350 3100 50  0001 C CNN
F 3 "http://www.hlktech.net/product_detail.php?ProId=59" H 2750 3050 50  0001 C CNN
	1    2350 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:Fuse F1
U 1 1 618A12A7
P 1450 3300
F 0 "F1" V 1647 3300 50  0000 C CNN
F 1 "3A/250V" V 1556 3300 50  0000 C CNN
F 2 "Fuse:Fuse_Littelfuse-LVR100" V 1380 3300 50  0001 C CNN
F 3 "~" H 1450 3300 50  0001 C CNN
	1    1450 3300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6700 3300 6350 3300
Wire Wire Line
	6350 3300 6350 5050
Wire Wire Line
	6350 5050 8400 5050
Wire Wire Line
	8400 3300 8000 3300
Wire Wire Line
	8000 3000 9100 3000
Wire Wire Line
	9100 3000 9100 2600
Wire Wire Line
	8000 3100 9200 3100
Wire Wire Line
	9200 3100 9200 2700
Wire Wire Line
	5300 4300 10150 4300
Wire Wire Line
	6700 3200 6150 3200
Wire Wire Line
	4700 2900 6000 2900
Wire Wire Line
	6000 2900 6000 3000
Wire Wire Line
	6000 3000 6700 3000
Wire Wire Line
	8400 5050 9850 5050
Wire Wire Line
	9850 5050 9850 4400
Connection ~ 8400 5050
Wire Wire Line
	6150 3200 6150 4500
Wire Wire Line
	10150 4400 9850 4400
Connection ~ 6350 5050
Wire Wire Line
	10150 4500 6150 4500
Wire Wire Line
	4700 3000 5900 3000
Wire Wire Line
	5900 3000 5900 3100
Wire Wire Line
	5900 3100 6700 3100
Wire Wire Line
	6700 3400 5800 3400
Wire Wire Line
	5800 3400 5800 3100
Wire Wire Line
	5800 3100 4700 3100
Wire Wire Line
	6700 3500 5700 3500
Wire Wire Line
	5700 3500 5700 3200
Wire Wire Line
	5700 3200 4700 3200
Wire Wire Line
	4700 4500 4850 4500
Wire Wire Line
	4850 4500 4850 4600
Connection ~ 4850 5050
Wire Wire Line
	4850 5050 6350 5050
Wire Wire Line
	2750 3500 2750 5050
Wire Wire Line
	2750 5050 4850 5050
Wire Wire Line
	6150 1650 6150 3200
Connection ~ 6150 3200
$Comp
L SparkFun-Boards:SPARKFUN_LOGIC_LEVEL_CONVERTER B1
U 1 1 6189B1AB
P 7350 3300
F 0 "B1" H 7350 3960 45  0000 C CNN
F 1 "Sparkfun BOB-12009" H 7350 3876 45  0000 C CNN
F 2 "Boards:SPARKFUN_LOGIC_LEVEL_CONVERTER" H 7350 3750 20  0001 C CNN
F 3 "https://learn.sparkfun.com/tutorials/bi-directional-logic-level-conter-hookup-guide" H 7350 3300 50  0001 C CNN
F 4 "BOB-12009" H 7350 3781 60  0001 C CNN "Field4"
F 5 "1568-1209-ND" H 7350 3300 50  0001 C CNN "digi-key part number"
	1    7350 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 3200 9550 3200
$Comp
L Espressif_ESP32-DevKitC:ESP32-DevKitC_V4 MD1
U 1 1 6191644A
P 3200 2100
F 0 "MD1" H 3950 2365 50  0000 C CNN
F 1 "ESP32-DevKitC" H 3950 2274 50  0000 C CNN
F 2 "Espressif_ESP32-DevKitC:Espressif-ESP32-DevKitC_V4-0-0-MFG" H 3200 2500 50  0001 L CNN
F 3 "https://docs.espressif.com/projects/esp-idf/en/latest/get-started/get-started-devkitc.html" H 3200 2600 50  0001 L CNN
F 4 "No" H 3200 2700 50  0001 L CNN "automotive"
F 5 "2.4-2.5GHz" H 3200 2800 50  0001 L CNN "bandwidth"
F 6 "UNK" H 3200 2900 50  0001 L CNN "category"
F 7 "Integrated Circuits (ICs)" H 3200 3000 50  0001 L CNN "device class L1"
F 8 "RF Semiconductors and Devices" H 3200 3100 50  0001 L CNN "device class L2"
F 9 "Transceivers" H 3200 3200 50  0001 L CNN "device class L3"
F 10 "I2C,SPI,UART,I2S" H 3200 3300 50  0001 L CNN "interface"
F 11 "Yes" H 3200 3400 50  0001 L CNN "lead free"
F 12 "0f6b35fd4d8e66ba" H 3200 3500 50  0001 L CNN "library id"
F 13 "Espressif" H 3200 3600 50  0001 L CNN "manufacturer"
F 14 "2.5GHz" H 3200 3700 50  0001 L CNN "max frequency"
F 15 "5V" H 3200 3800 50  0001 L CNN "max supply voltage"
F 16 "2.7V" H 3200 3900 50  0001 L CNN "min supply voltage"
F 17 "356-ESP32-DEVKITC" H 3200 4000 50  0001 L CNN "mouser part number"
F 18 "16" H 3200 4100 50  0001 L CNN "number of ADC channels"
F 19 "22" H 3200 4200 50  0001 L CNN "number of GPIO"
F 20 "PTH_WIFI-MODULE" H 3200 4300 50  0001 L CNN "package"
F 21 "Yes" H 3200 4400 50  0001 L CNN "rohs"
F 22 "-40°C" H 3200 4500 50  0001 L CNN "temperature range low"
F 23 "1965-1000-ND" H 3200 2100 50  0001 C CNN "digi-key part number"
	1    3200 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 1650 3050 2100
Wire Wire Line
	3050 2100 3200 2100
Wire Wire Line
	3050 1650 6150 1650
$Comp
L power:+3.3V #PWR0101
U 1 1 61961129
P 3050 1650
F 0 "#PWR0101" H 3050 1500 50  0001 C CNN
F 1 "+3.3V" H 3065 1823 50  0000 C CNN
F 2 "" H 3050 1650 50  0001 C CNN
F 3 "" H 3050 1650 50  0001 C CNN
	1    3050 1650
	1    0    0    -1  
$EndComp
Connection ~ 3050 1650
$Comp
L power:+5V #PWR0102
U 1 1 61961BE1
P 2750 1650
F 0 "#PWR0102" H 2750 1500 50  0001 C CNN
F 1 "+5V" H 2765 1823 50  0000 C CNN
F 2 "" H 2750 1650 50  0001 C CNN
F 3 "" H 2750 1650 50  0001 C CNN
	1    2750 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 61966751
P 2750 5050
F 0 "#PWR0105" H 2750 4800 50  0001 C CNN
F 1 "GND" H 2755 4877 50  0000 C CNN
F 2 "" H 2750 5050 50  0001 C CNN
F 3 "" H 2750 5050 50  0001 C CNN
	1    2750 5050
	1    0    0    -1  
$EndComp
Connection ~ 2750 5050
Wire Wire Line
	1100 3400 1100 3300
NoConn ~ 4700 2300
NoConn ~ 4700 2400
NoConn ~ 4700 2500
NoConn ~ 4700 2600
NoConn ~ 4700 2700
NoConn ~ 4700 2800
NoConn ~ 4700 3300
NoConn ~ 4700 3400
NoConn ~ 4700 3500
NoConn ~ 4700 3600
NoConn ~ 4700 3700
NoConn ~ 4700 3800
NoConn ~ 4700 3900
NoConn ~ 4700 4000
NoConn ~ 4700 4100
NoConn ~ 4700 4200
NoConn ~ 3200 2400
NoConn ~ 3200 2500
NoConn ~ 3200 2700
NoConn ~ 3200 2900
NoConn ~ 3200 3100
NoConn ~ 3200 3300
NoConn ~ 3200 3400
NoConn ~ 3200 4400
NoConn ~ 3200 4500
NoConn ~ 3200 4600
NoConn ~ 3200 4700
Wire Wire Line
	4700 4600 4850 4600
Connection ~ 4850 4600
Wire Wire Line
	4850 4600 4850 4700
Wire Wire Line
	4700 4700 4850 4700
Connection ~ 4850 4700
Wire Wire Line
	4850 4700 4850 5050
Wire Wire Line
	1300 3300 1100 3300
$Comp
L Connector:Screw_Terminal_01x03 J2
U 1 1 618A0962
P 10350 4400
F 0 "J2" H 10430 4442 50  0000 L CNN
F 1 "Relay Board" H 10430 4351 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-3_1x03_P5.00mm_Horizontal" H 10350 4400 50  0001 C CNN
F 3 "~" H 10350 4400 50  0001 C CNN
	1    10350 4400
	1    0    0    -1  
$EndComp
Text Label 9900 2600 0    50   ~ 0
DIO_DB
Text Label 9900 2700 0    50   ~ 0
CLK_DB
Text Label 9900 2800 0    50   ~ 0
PIN_2
Text Label 9900 3700 0    50   ~ 0
PIN_1
Text Label 9900 3400 0    50   ~ 0
DIO_MB
Text Label 9900 3500 0    50   ~ 0
CLK_MB
Text Label 9900 3600 0    50   ~ 0
PIN_2
Text Label 9900 4400 0    50   ~ 0
GND
Text Label 9900 4500 0    50   ~ 0
+3.3V
Text Label 9900 4300 0    50   ~ 0
RELAY
Text Label 4800 2900 0    50   ~ 0
DIO_LV_DB
Text Label 4800 3000 0    50   ~ 0
CLK_LV_DB
Text Label 4800 3100 0    50   ~ 0
DIO_LV_MB
Text Label 4800 3200 0    50   ~ 0
CLK_LV_MB
$Comp
L power:LINE #PWR0103
U 1 1 6195BEEC
P 1250 4200
F 0 "#PWR0103" H 1250 4050 50  0001 C CNN
F 1 "LINE" H 1265 4373 50  0000 C CNN
F 2 "" H 1250 4200 50  0001 C CNN
F 3 "" H 1250 4200 50  0001 C CNN
	1    1250 4200
	1    0    0    -1  
$EndComp
$Comp
L power:NEUT #PWR0104
U 1 1 6195C4C9
P 1700 4200
F 0 "#PWR0104" H 1700 4050 50  0001 C CNN
F 1 "NEUT" H 1715 4373 50  0000 C CNN
F 2 "" H 1700 4200 50  0001 C CNN
F 3 "" H 1700 4200 50  0001 C CNN
	1    1700 4200
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 6195CC4C
P 1250 4300
F 0 "#FLG0103" H 1250 4375 50  0001 C CNN
F 1 "PWR_FLAG" H 1250 4473 50  0000 C CNN
F 2 "" H 1250 4300 50  0001 C CNN
F 3 "~" H 1250 4300 50  0001 C CNN
	1    1250 4300
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0104
U 1 1 6195DBEA
P 1700 4300
F 0 "#FLG0104" H 1700 4375 50  0001 C CNN
F 1 "PWR_FLAG" H 1700 4473 50  0000 C CNN
F 2 "" H 1700 4300 50  0001 C CNN
F 3 "~" H 1700 4300 50  0001 C CNN
	1    1700 4300
	-1   0    0    1   
$EndComp
Wire Wire Line
	1250 4200 1250 4300
Wire Wire Line
	1700 4200 1700 4300
Wire Wire Line
	1100 3500 1950 3500
Wire Wire Line
	1600 3300 1950 3300
Text Label 1750 3300 0    50   ~ 0
LINE
Text Label 1750 3500 0    50   ~ 0
NEUT
$Comp
L power:+3.3V #PWR0106
U 1 1 6196A3C8
P 1250 1650
F 0 "#PWR0106" H 1250 1500 50  0001 C CNN
F 1 "+3.3V" H 1265 1823 50  0000 C CNN
F 2 "" H 1250 1650 50  0001 C CNN
F 3 "" H 1250 1650 50  0001 C CNN
	1    1250 1650
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 6196AE30
P 1250 1800
F 0 "#FLG0101" H 1250 1875 50  0001 C CNN
F 1 "PWR_FLAG" H 1250 1973 50  0000 C CNN
F 2 "" H 1250 1800 50  0001 C CNN
F 3 "~" H 1250 1800 50  0001 C CNN
	1    1250 1800
	-1   0    0    1   
$EndComp
Wire Wire Line
	1250 1650 1250 1800
Text Label 1800 1550 0    50   ~ 0
5V_INTEX
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 6196FB13
P 1800 1800
F 0 "#FLG0102" H 1800 1875 50  0001 C CNN
F 1 "PWR_FLAG" H 1800 1973 50  0000 C CNN
F 2 "" H 1800 1800 50  0001 C CNN
F 3 "~" H 1800 1800 50  0001 C CNN
	1    1800 1800
	-1   0    0    1   
$EndComp
Wire Wire Line
	1800 1800 1800 1550
Wire Wire Line
	3200 2200 2750 2200
Wire Wire Line
	2750 1650 2750 2200
Connection ~ 2750 2200
Wire Wire Line
	2750 2200 2750 3300
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 618A0045
P 900 3400
F 0 "J1" H 818 3617 50  0000 C CNN
F 1 "230V" H 818 3526 50  0000 C CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2_1x02_P5.00mm_Horizontal" H 900 3400 50  0001 C CNN
F 3 "~" H 900 3400 50  0001 C CNN
	1    900  3400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9200 2700 10150 2700
Wire Wire Line
	9100 2600 10150 2600
Text Label 9900 2900 0    50   ~ 0
PIN_1
Wire Wire Line
	10150 3700 9850 3700
Wire Wire Line
	9850 3700 9850 4000
$Comp
L SparkFun-Connectors:CONN_04JST-PTH J3
U 1 1 6189EC82
P 10250 2900
F 0 "J3" H 10022 2955 45  0000 R CNN
F 1 "Display Board" H 10022 3039 45  0000 R CNN
F 2 "Connector_JST:JST_XH_B4B-XH-A_1x04_P2.50mm_Vertical" H 10250 3400 20  0001 C CNN
F 3 "https://www.jst-mfg.com/product/pdf/eng/eXH.pdf" H 10250 2900 50  0001 C CNN
F 4 "CONN_04JST-XH" H 10022 3134 45  0000 R CNN "Field4"
F 5 "455-2249-ND" H 10250 2900 50  0001 C CNN "digi-key part number"
	1    10250 2900
	-1   0    0    -1  
$EndComp
$Comp
L SparkFun-Connectors:CONN_04JST-PTH J4
U 1 1 618C5D92
P 10250 3700
F 0 "J4" H 10022 3755 45  0000 R CNN
F 1 "Main Board" H 10022 3839 45  0000 R CNN
F 2 "Connector_JST:JST_XH_B4B-XH-A_1x04_P2.50mm_Vertical" H 10250 4200 20  0001 C CNN
F 3 "https://www.jst-mfg.com/product/pdf/eng/eXH.pdf" H 10250 3700 50  0001 C CNN
F 4 "CONN_04JST-XH" H 10022 3934 45  0000 R CNN "Field4"
F 5 "455-2249-ND" H 10250 3700 50  0001 C CNN "digi-key part number"
	1    10250 3700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9550 3300 9650 3300
Wire Wire Line
	9650 3300 9650 2900
Wire Wire Line
	9650 2900 9850 2900
Wire Wire Line
	9550 3600 9550 3800
Wire Wire Line
	9550 4000 9850 4000
Wire Wire Line
	9550 2800 9550 3100
Wire Wire Line
	9850 3700 9850 2900
Connection ~ 9850 3700
Connection ~ 9850 2900
Wire Wire Line
	9850 2900 10150 2900
Connection ~ 9750 2800
Connection ~ 9750 3600
Wire Wire Line
	9750 2800 9750 3600
Wire Wire Line
	9750 2800 10150 2800
Wire Wire Line
	9750 3600 10150 3600
Wire Wire Line
	9550 2800 9750 2800
Wire Wire Line
	9550 3600 9750 3600
Text Label 9000 3200 0    50   ~ 0
5V_INTEX
Wire Wire Line
	8000 3500 10150 3500
Wire Wire Line
	8000 3400 10150 3400
Text Label 9000 3900 0    50   ~ 0
GND
$Comp
L Connector:Conn_01x03_Male J6
U 1 1 61B74AD2
P 9350 3900
F 0 "J6" H 9458 4181 50  0000 C CNN
F 1 "GND Pin Select" H 9350 3750 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 9350 3900 50  0001 C CNN
F 3 "~" H 9350 3900 50  0001 C CNN
	1    9350 3900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J5
U 1 1 61B738BE
P 9350 3200
F 0 "J5" H 9458 3481 50  0000 C CNN
F 1 "5V_INTEX Pin Select" H 9450 3050 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 9350 3200 50  0001 C CNN
F 3 "~" H 9350 3200 50  0001 C CNN
	1    9350 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 3300 8400 3900
Wire Wire Line
	9550 3900 8400 3900
Connection ~ 8400 3900
Wire Wire Line
	8400 3900 8400 5050
Text Label 4800 2200 0    50   ~ 0
RELAY
Wire Wire Line
	5300 2200 4700 2200
Wire Wire Line
	5300 2200 5300 4300
NoConn ~ 4700 2100
$EndSCHEMATC
