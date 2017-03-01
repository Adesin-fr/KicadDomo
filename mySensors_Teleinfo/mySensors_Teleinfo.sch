EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:mysensors_radios
LIBS:myLibrary
LIBS:mySensors_Teleinfo-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 3250 4300 0    60   ~ 0
GND
Text Label 9750 4150 0    60   ~ 0
GND
Text Label 9600 2750 0    60   ~ 0
3V3
Text Label 8650 3200 0    60   ~ 0
CS
Text Label 8650 3500 0    60   ~ 0
SCK
Text Label 8650 3400 0    60   ~ 0
MISO
Text Label 8650 3300 0    60   ~ 0
MOSI
Text Label 5750 2200 0    60   ~ 0
CS
Text Label 5750 2300 0    60   ~ 0
MOSI
Text Label 5750 2400 0    60   ~ 0
MISO
Text Label 5750 2500 0    60   ~ 0
SCK
Wire Wire Line
	3700 2100 3550 2100
Wire Wire Line
	3550 2100 3550 2000
Wire Wire Line
	3050 2000 3700 2000
Connection ~ 3550 2000
Wire Wire Line
	3700 4300 3200 4300
Wire Wire Line
	3700 4200 3550 4200
Wire Wire Line
	3550 4100 3550 4300
Connection ~ 3550 4300
Wire Wire Line
	9350 4150 10000 4150
Wire Wire Line
	8550 3200 8900 3200
Wire Wire Line
	8550 3500 8900 3500
Wire Wire Line
	8550 3400 8900 3400
Wire Wire Line
	9450 2750 9850 2750
Wire Wire Line
	8600 3300 8900 3300
Wire Wire Line
	5600 2200 6050 2200
Wire Wire Line
	5600 2300 6050 2300
Wire Wire Line
	5600 2400 6050 2400
Wire Wire Line
	5600 2500 6050 2500
Wire Wire Line
	9000 5750 8550 5750
Wire Wire Line
	9300 6000 9300 6250
Text Label 9500 6250 0    60   ~ 0
GND
Text Label 9800 5750 0    60   ~ 0
3V3
Text Label 8700 5750 0    60   ~ 0
VIN
$Comp
L C C3
U 1 1 57E3DA4C
P 10250 6000
F 0 "C3" H 10275 6100 50  0000 L CNN
F 1 "1u" H 10275 5900 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 10288 5850 50  0001 C CNN
F 3 "" H 10250 6000 50  0000 C CNN
	1    10250 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 6250 10250 6150
Connection ~ 10250 6250
Wire Wire Line
	10250 5850 10250 5750
Connection ~ 10250 5750
Wire Wire Line
	8750 6250 10250 6250
Wire Wire Line
	10250 5750 9600 5750
Text Label 3100 2000 0    60   ~ 0
3V3
$Comp
L RFM69HW U4
U 1 1 5875DDB7
P 9450 3150
F 0 "U4" H 9100 3400 40  0000 C CNN
F 1 "RFM69HW" H 9700 2400 40  0000 C CNN
F 2 "Mysensors_Radio:RFM69HW_SMD_Handsoldering" H 9450 3150 30  0001 C CIN
F 3 "" H 9450 3150 60  0000 C CNN
	1    9450 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 2800 9450 2750
Wire Wire Line
	9350 4150 9350 4000
Wire Wire Line
	9550 4000 9550 4150
Connection ~ 9550 4150
Wire Wire Line
	10000 3150 10300 3150
Text Label 10050 3150 0    60   ~ 0
IRQ
Wire Wire Line
	5600 3800 6100 3800
Text Label 5800 3800 0    60   ~ 0
IRQ
$Comp
L ATMEGA328-A IC1
U 1 1 5875E19C
P 4600 3100
F 0 "IC1" H 3850 4350 50  0000 L BNN
F 1 "ATMEGA328-A" H 5000 1700 50  0000 L BNN
F 2 "Housings_QFP:TQFP-32_7x7mm_Pitch0.8mm" H 4600 3100 50  0000 C CIN
F 3 "" H 4600 3100 50  0000 C CNN
	1    4600 3100
	1    0    0    -1  
$EndComp
$Comp
L AMS1117 U3
U 1 1 5875E219
P 9400 5750
F 0 "U3" H 9500 5500 50  0000 R BNN
F 1 "AMS1117" H 9300 6000 50  0000 C TNN
F 2 "TO_SOT_Packages_SMD:SOT-223" H 9300 5800 60  0001 C CNN
F 3 "" H 9300 5800 60  0000 C CNN
	1    9400 5750
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X03 P2
U 1 1 5875E472
P 4600 5200
F 0 "P2" H 4600 5400 50  0000 C CNN
F 1 "ICSP" H 4600 5000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03_Pitch2.54mm" H 4600 4000 50  0001 C CNN
F 3 "" H 4600 4000 50  0000 C CNN
	1    4600 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 5100 4350 5100
Wire Wire Line
	3950 5200 4350 5200
Wire Wire Line
	3950 5300 4350 5300
Wire Wire Line
	5200 5300 4850 5300
Wire Wire Line
	5200 5200 4850 5200
Wire Wire Line
	5200 5100 4850 5100
Text Label 3950 5100 0    60   ~ 0
MISO
Text Label 3950 5200 0    60   ~ 0
SCK
Text Label 3950 5300 0    60   ~ 0
RESET
Text Label 4950 5100 0    60   ~ 0
3V3
Text Label 4950 5200 0    60   ~ 0
MOSI
Text Label 4950 5300 0    60   ~ 0
GND
Wire Wire Line
	5600 3450 6100 3450
Text Label 5750 3450 0    60   ~ 0
RESET
Wire Wire Line
	8450 3000 8900 3000
Wire Wire Line
	3700 4100 3550 4100
Connection ~ 3550 4200
$Comp
L CONN_01X02 P1
U 1 1 5899B94F
P 1100 1000
F 0 "P1" H 1100 1150 50  0000 C CNN
F 1 "CONN_01X02" V 1200 1000 50  0000 C CNN
F 2 "Connectors:bornier2" H 1100 1000 50  0001 C CNN
F 3 "" H 1100 1000 50  0000 C CNN
	1    1100 1000
	-1   0    0    1   
$EndComp
Wire Wire Line
	2250 750  2250 650 
Wire Wire Line
	2250 650  1700 650 
Wire Wire Line
	1700 650  1700 950 
Wire Wire Line
	1700 950  1300 950 
Wire Wire Line
	1300 1050 1700 1050
Wire Wire Line
	1700 1050 1700 1500
Wire Wire Line
	1700 1500 2250 1500
Wire Wire Line
	2250 1500 2250 1350
Wire Wire Line
	1950 1050 1850 1050
Wire Wire Line
	1850 1050 1850 1400
Wire Wire Line
	1850 1400 2100 1400
Wire Wire Line
	2550 1050 3000 1050
Text Label 2750 1050 0    60   ~ 0
VIN
Text Label 1900 1400 0    60   ~ 0
GND
Text Label 1900 650  0    60   ~ 0
T+
Text Label 1800 1500 0    60   ~ 0
T-
$Comp
L C C1
U 1 1 5899BBE0
P 8750 5950
F 0 "C1" H 8775 6050 50  0000 L CNN
F 1 "2200u" H 8775 5850 50  0000 L CNN
F 2 "Capacitors_THT:C_Radial_D10_L20_P5" H 8788 5800 50  0001 C CNN
F 3 "" H 8750 5950 50  0000 C CNN
	1    8750 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 6100 8750 6250
Connection ~ 9300 6250
Wire Wire Line
	8750 5800 8750 5750
Connection ~ 8750 5750
$Comp
L PC817 U1
U 1 1 5899BD67
P 1700 2150
F 0 "U1" H 1500 2350 50  0000 L CNN
F 1 "SFH620" H 1700 2350 50  0000 L CNN
F 2 "Housings_DIP:DIP-4_W7.62mm_SMD" H 1500 1950 50  0001 L CIN
F 3 "" H 1700 2150 50  0000 L CNN
	1    1700 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 2250 2250 2250
Wire Wire Line
	2000 2050 2450 2050
$Comp
L R R2
U 1 1 5899C022
P 2200 1850
F 0 "R2" V 2280 1850 50  0000 C CNN
F 1 "4k7" V 2200 1850 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 2130 1850 50  0001 C CNN
F 3 "" H 2200 1850 50  0000 C CNN
	1    2200 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 2000 2200 2050
Connection ~ 2200 2050
Wire Wire Line
	2200 1700 2200 1650
Wire Wire Line
	2200 1650 2400 1650
Text Label 2150 2250 0    60   ~ 0
GND
Text Label 2250 1650 0    60   ~ 0
3V3
Text Label 2300 2050 0    60   ~ 0
T_IN
$Comp
L R R1
U 1 1 5899C1B5
P 1100 2050
F 0 "R1" V 1180 2050 50  0000 C CNN
F 1 "1k2" V 1100 2050 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 1030 2050 50  0001 C CNN
F 3 "" H 1100 2050 50  0000 C CNN
	1    1100 2050
	0    1    1    0   
$EndComp
Wire Wire Line
	1250 2050 1400 2050
Wire Wire Line
	1400 2250 700  2250
Wire Wire Line
	700  2050 950  2050
Text Label 750  2050 0    60   ~ 0
T+
Text Label 750  2250 0    60   ~ 0
T-
Wire Wire Line
	5600 3600 6100 3600
Text Label 5800 3600 0    60   ~ 0
T_IN
$Comp
L MB6S D1
U 1 1 5899C1F4
P 2250 1050
F 0 "D1" H 2300 1325 50  0000 L CNN
F 1 "MB6S" H 2300 1250 50  0000 L CNN
F 2 "MyLibrary:TO-269AA" H 2250 1050 50  0001 C CNN
F 3 "" H 2250 1050 50  0000 C CNN
	1    2250 1050
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P3
U 1 1 5899C541
P 8250 3050
F 0 "P3" H 8250 3200 50  0000 C CNN
F 1 "ANT" V 8350 3050 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 8250 3050 50  0001 C CNN
F 3 "" H 8250 3050 50  0000 C CNN
	1    8250 3050
	-1   0    0    1   
$EndComp
Wire Wire Line
	8450 3100 8850 3100
Text Label 8550 3100 0    60   ~ 0
GND
$EndSCHEMATC
