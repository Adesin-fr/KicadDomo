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
LIBS:mySensors_8RelaisReed-cache
EELAYER 26 0
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
$Comp
L ATMEGA328-A IC1
U 1 1 5876469C
P 2300 3100
F 0 "IC1" H 1550 4350 50  0000 L BNN
F 1 "ATMEGA328-A" H 2700 1700 50  0000 L BNN
F 2 "Housings_QFP:TQFP-32_7x7mm_Pitch0.8mm" H 2300 3100 50  0000 C CIN
F 3 "" H 2300 3100 50  0000 C CNN
	1    2300 3100
	1    0    0    -1  
$EndComp
$Comp
L RFM69HW U2
U 1 1 587646FD
P 2350 5350
F 0 "U2" H 2000 5600 40  0000 C CNN
F 1 "RFM69HW" H 2600 4600 40  0000 C CNN
F 2 "Mysensors_Radio:RFM69HW_SMD_Handsoldering" H 2350 5350 30  0001 C CIN
F 3 "" H 2350 5350 60  0000 C CNN
	1    2350 5350
	1    0    0    -1  
$EndComp
$Comp
L AMS1117 U1
U 1 1 58764782
P 1950 950
F 0 "U1" H 2050 700 50  0000 R BNN
F 1 "AMS1117" H 1850 1200 50  0000 C TNN
F 2 "TO_SOT_Packages_SMD:SOT-223" H 1850 1000 60  0001 C CNN
F 3 "" H 1850 1000 60  0000 C CNN
	1    1950 950 
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P1
U 1 1 58764921
P 800 1000
F 0 "P1" H 800 1150 50  0000 C CNN
F 1 "5VIN" V 900 1000 50  0000 C CNN
F 2 "Connectors:bornier2" H 800 1000 50  0001 C CNN
F 3 "" H 800 1000 50  0000 C CNN
	1    800  1000
	-1   0    0    1   
$EndComp
Text Label 2700 950  0    60   ~ 0
3V3
$Comp
L 74HC595 U3
U 1 1 58764AC4
P 4950 5700
F 0 "U3" H 5100 6300 50  0000 C CNN
F 1 "74HC595" H 4950 5100 50  0000 C CNN
F 2 "SMD_Packages:SO-16-N" H 4950 5700 50  0001 C CNN
F 3 "" H 4950 5700 50  0000 C CNN
	1    4950 5700
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 58764C44
P 2400 1100
F 0 "C2" H 2425 1200 50  0000 L CNN
F 1 "10uF" H 2425 1000 50  0000 L CNN
F 2 "Capacitors_THT:C_Radial_D5_L6_P2.5" H 2438 950 50  0001 C CNN
F 3 "" H 2400 1100 50  0000 C CNN
	1    2400 1100
	1    0    0    -1  
$EndComp
Text Label 1200 900  0    60   ~ 0
VCC
$Comp
L CONN_02X03 P3
U 1 1 58764DB3
P 2300 7250
F 0 "P3" H 2300 7450 50  0000 C CNN
F 1 "CONN_02X03" H 2300 7050 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03_Pitch2.54mm" H 2300 6050 50  0001 C CNN
F 3 "" H 2300 6050 50  0000 C CNN
	1    2300 7250
	1    0    0    -1  
$EndComp
Text Label 1750 7150 0    60   ~ 0
MISO
Text Label 1750 7250 0    60   ~ 0
SCK
Text Label 1750 7350 0    60   ~ 0
RESET
Text Label 2600 7150 0    60   ~ 0
3V3
Text Label 2600 7250 0    60   ~ 0
MOSI
Text Label 2600 7350 0    60   ~ 0
GND
$Comp
L C C1
U 1 1 587650E8
P 1350 1100
F 0 "C1" H 1375 1200 50  0000 L CNN
F 1 "10uF" H 1375 1000 50  0000 L CNN
F 2 "Capacitors_THT:C_Radial_D5_L6_P2.5" H 1388 950 50  0001 C CNN
F 3 "" H 1350 1100 50  0000 C CNN
	1    1350 1100
	1    0    0    -1  
$EndComp
Text Label 3350 3450 0    60   ~ 0
RESET
Text Label 3350 2500 0    60   ~ 0
SCK
Text Label 3350 2400 0    60   ~ 0
MISO
Text Label 3350 2300 0    60   ~ 0
MOSI
Text Label 2450 5000 0    60   ~ 0
3V3
Text Label 3000 5350 0    60   ~ 0
IRQ
Text Label 1550 5400 0    60   ~ 0
CS
Text Label 1550 5500 0    60   ~ 0
MOSI
Text Label 1550 5600 0    60   ~ 0
MISO
Text Label 1550 5700 0    60   ~ 0
SCK
$Comp
L CONN_01X01 P2
U 1 1 58765535
P 950 5200
F 0 "P2" H 950 5300 50  0000 C CNN
F 1 "ANT" H 950 5100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 950 5200 50  0001 C CNN
F 3 "" H 950 5200 50  0000 C CNN
	1    950  5200
	-1   0    0    1   
$EndComp
Text Label 3350 2200 0    60   ~ 0
CS
Text Label 1100 2000 0    60   ~ 0
3V3
Text Label 1150 4100 0    60   ~ 0
GND
Text Label 3350 3800 0    60   ~ 0
IRQ
Text Label 5800 5250 0    60   ~ 0
S7
Text Label 5800 5350 0    60   ~ 0
S6
Text Label 5800 5450 0    60   ~ 0
S5
Text Label 5800 5550 0    60   ~ 0
S4
Text Label 5800 5650 0    60   ~ 0
S3
Text Label 5800 5750 0    60   ~ 0
S2
Text Label 5800 5850 0    60   ~ 0
S1
Text Label 5800 5950 0    60   ~ 0
S0
Text Label 3950 5550 0    60   ~ 0
VCC
Text Label 3950 5750 0    60   ~ 0
RCLK
Text Label 3900 5250 0    60   ~ 0
SER
Text Label 3900 5450 0    60   ~ 0
SRCLK
Text Label 3950 5850 0    60   ~ 0
GND
Text Label 3450 2850 0    60   ~ 0
SER
Text Label 3450 3050 0    60   ~ 0
SRCLK
Text Label 3450 2950 0    60   ~ 0
RCLK
$Comp
L RELAY_SIP-1A05 R1
U 1 1 58766F32
P 8150 1150
F 0 "R1" H 8150 1150 60  0000 C CNN
F 1 "RELAY_SIP-1A05" H 8150 1650 60  0000 C CNN
F 2 "MyLibrary:SIP4_5.08" H 8150 1150 60  0001 C CNN
F 3 "" H 8150 1150 60  0001 C CNN
	1    8150 1150
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P4
U 1 1 5876743C
P 8900 900
F 0 "P4" H 8900 1050 50  0000 C CNN
F 1 "CONN_01X02" V 9000 900 50  0000 C CNN
F 2 "Connectors:bornier2" H 8900 900 50  0001 C CNN
F 3 "" H 8900 900 50  0000 C CNN
	1    8900 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 1050 1100 1050
Wire Wire Line
	1700 7150 2050 7150
Wire Wire Line
	1700 7250 2050 7250
Wire Wire Line
	1700 7350 2050 7350
Wire Wire Line
	2850 7150 2550 7150
Wire Wire Line
	2850 7250 2550 7250
Wire Wire Line
	2850 7350 2550 7350
Wire Wire Line
	1100 1050 1100 1250
Wire Wire Line
	1100 1250 2950 1250
Wire Wire Line
	1850 1250 1850 1200
Connection ~ 1350 1250
Connection ~ 1850 1250
Wire Wire Line
	3300 2300 3600 2300
Wire Wire Line
	3300 2400 3600 2400
Wire Wire Line
	3300 2500 3600 2500
Wire Wire Line
	3300 3450 3600 3450
Wire Wire Line
	3300 3800 3600 3800
Wire Wire Line
	1800 5400 1450 5400
Wire Wire Line
	1450 5500 1800 5500
Wire Wire Line
	1450 5600 1800 5600
Wire Wire Line
	1450 5700 1800 5700
Wire Wire Line
	2250 6200 2250 6300
Wire Wire Line
	2250 6300 2700 6300
Wire Wire Line
	2450 6200 2450 6300
Connection ~ 2450 6300
Wire Wire Line
	2900 5350 3300 5350
Wire Wire Line
	1800 5200 1150 5200
Wire Wire Line
	2350 5000 2700 5000
Wire Wire Line
	3300 2200 3750 2200
Wire Wire Line
	1400 2000 1000 2000
Wire Wire Line
	1250 2000 1250 2100
Wire Wire Line
	1250 2100 1400 2100
Connection ~ 1250 2000
Wire Wire Line
	1400 4300 1100 4300
Wire Wire Line
	1100 4300 1100 4100
Wire Wire Line
	1100 4100 1400 4100
Wire Wire Line
	1400 4200 1100 4200
Connection ~ 1100 4200
Wire Wire Line
	5650 5250 6000 5250
Wire Wire Line
	5650 5350 6000 5350
Wire Wire Line
	6000 5450 5650 5450
Wire Wire Line
	6000 5550 5650 5550
Wire Wire Line
	6000 5650 5650 5650
Wire Wire Line
	6000 5750 5650 5750
Wire Wire Line
	6000 5850 5650 5850
Wire Wire Line
	6000 5950 5650 5950
Wire Wire Line
	4250 5550 3900 5550
Wire Wire Line
	4250 5750 3900 5750
Wire Wire Line
	4250 5250 3900 5250
Wire Wire Line
	4250 5450 3900 5450
Wire Wire Line
	4250 5850 3900 5850
Wire Wire Line
	3300 2850 3750 2850
Wire Wire Line
	3300 2950 3750 2950
Wire Wire Line
	3300 3050 3750 3050
Wire Wire Line
	8700 850  8400 850 
Wire Wire Line
	8400 950  8700 950 
Wire Wire Line
	7350 1050 7800 1050
Text Label 7550 1050 0    60   ~ 0
GND
Wire Wire Line
	7350 750  7800 750 
Text Label 7550 750  0    60   ~ 0
S0
$Comp
L RELAY_SIP-1A05 R2
U 1 1 587679A2
P 8150 1750
F 0 "R2" H 8150 1750 60  0000 C CNN
F 1 "RELAY_SIP-1A05" H 8150 2250 60  0000 C CNN
F 2 "MyLibrary:SIP4_5.08" H 8150 1750 60  0001 C CNN
F 3 "" H 8150 1750 60  0001 C CNN
	1    8150 1750
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P5
U 1 1 587679A8
P 8900 1500
F 0 "P5" H 8900 1650 50  0000 C CNN
F 1 "CONN_01X02" V 9000 1500 50  0000 C CNN
F 2 "Connectors:bornier2" H 8900 1500 50  0001 C CNN
F 3 "" H 8900 1500 50  0000 C CNN
	1    8900 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 1450 8400 1450
Wire Wire Line
	8400 1550 8700 1550
Wire Wire Line
	7350 1650 7800 1650
Text Label 7550 1650 0    60   ~ 0
GND
Wire Wire Line
	7350 1350 7800 1350
Text Label 7550 1350 0    60   ~ 0
S1
$Comp
L RELAY_SIP-1A05 R3
U 1 1 58767BEA
P 8150 2350
F 0 "R3" H 8150 2350 60  0000 C CNN
F 1 "RELAY_SIP-1A05" H 8150 2850 60  0000 C CNN
F 2 "MyLibrary:SIP4_5.08" H 8150 2350 60  0001 C CNN
F 3 "" H 8150 2350 60  0001 C CNN
	1    8150 2350
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P6
U 1 1 58767BF0
P 8900 2100
F 0 "P6" H 8900 2250 50  0000 C CNN
F 1 "CONN_01X02" V 9000 2100 50  0000 C CNN
F 2 "Connectors:bornier2" H 8900 2100 50  0001 C CNN
F 3 "" H 8900 2100 50  0000 C CNN
	1    8900 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 2050 8400 2050
Wire Wire Line
	8400 2150 8700 2150
Wire Wire Line
	7350 2250 7800 2250
Text Label 7550 2250 0    60   ~ 0
GND
Wire Wire Line
	7350 1950 7800 1950
Text Label 7550 1950 0    60   ~ 0
S2
$Comp
L RELAY_SIP-1A05 R4
U 1 1 58767BFC
P 8150 2950
F 0 "R4" H 8150 2950 60  0000 C CNN
F 1 "RELAY_SIP-1A05" H 8150 3450 60  0000 C CNN
F 2 "MyLibrary:SIP4_5.08" H 8150 2950 60  0001 C CNN
F 3 "" H 8150 2950 60  0001 C CNN
	1    8150 2950
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P7
U 1 1 58767C02
P 8900 2700
F 0 "P7" H 8900 2850 50  0000 C CNN
F 1 "CONN_01X02" V 9000 2700 50  0000 C CNN
F 2 "Connectors:bornier2" H 8900 2700 50  0001 C CNN
F 3 "" H 8900 2700 50  0000 C CNN
	1    8900 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 2650 8400 2650
Wire Wire Line
	8400 2750 8700 2750
Wire Wire Line
	7350 2850 7800 2850
Text Label 7550 2850 0    60   ~ 0
GND
Wire Wire Line
	7350 2550 7800 2550
Text Label 7550 2550 0    60   ~ 0
S3
$Comp
L RELAY_SIP-1A05 R5
U 1 1 58767E7A
P 8150 3550
F 0 "R5" H 8150 3550 60  0000 C CNN
F 1 "RELAY_SIP-1A05" H 8150 4050 60  0000 C CNN
F 2 "MyLibrary:SIP4_5.08" H 8150 3550 60  0001 C CNN
F 3 "" H 8150 3550 60  0001 C CNN
	1    8150 3550
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P8
U 1 1 58767E80
P 8900 3300
F 0 "P8" H 8900 3450 50  0000 C CNN
F 1 "CONN_01X02" V 9000 3300 50  0000 C CNN
F 2 "Connectors:bornier2" H 8900 3300 50  0001 C CNN
F 3 "" H 8900 3300 50  0000 C CNN
	1    8900 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 3250 8400 3250
Wire Wire Line
	8400 3350 8700 3350
Wire Wire Line
	7350 3450 7800 3450
Text Label 7550 3450 0    60   ~ 0
GND
Wire Wire Line
	7350 3150 7800 3150
Text Label 7550 3150 0    60   ~ 0
S4
$Comp
L RELAY_SIP-1A05 R6
U 1 1 58767E8C
P 8150 4150
F 0 "R6" H 8150 4150 60  0000 C CNN
F 1 "RELAY_SIP-1A05" H 8150 4650 60  0000 C CNN
F 2 "MyLibrary:SIP4_5.08" H 8150 4150 60  0001 C CNN
F 3 "" H 8150 4150 60  0001 C CNN
	1    8150 4150
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P9
U 1 1 58767E92
P 8900 3900
F 0 "P9" H 8900 4050 50  0000 C CNN
F 1 "CONN_01X02" V 9000 3900 50  0000 C CNN
F 2 "Connectors:bornier2" H 8900 3900 50  0001 C CNN
F 3 "" H 8900 3900 50  0000 C CNN
	1    8900 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 3850 8400 3850
Wire Wire Line
	8400 3950 8700 3950
Wire Wire Line
	7350 4050 7800 4050
Text Label 7550 4050 0    60   ~ 0
GND
Wire Wire Line
	7350 3750 7800 3750
Text Label 7550 3750 0    60   ~ 0
S5
$Comp
L RELAY_SIP-1A05 R7
U 1 1 58767E9E
P 8150 4750
F 0 "R7" H 8150 4750 60  0000 C CNN
F 1 "RELAY_SIP-1A05" H 8150 5250 60  0000 C CNN
F 2 "MyLibrary:SIP4_5.08" H 8150 4750 60  0001 C CNN
F 3 "" H 8150 4750 60  0001 C CNN
	1    8150 4750
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P10
U 1 1 58767EA4
P 8900 4500
F 0 "P10" H 8900 4650 50  0000 C CNN
F 1 "CONN_01X02" V 9000 4500 50  0000 C CNN
F 2 "Connectors:bornier2" H 8900 4500 50  0001 C CNN
F 3 "" H 8900 4500 50  0000 C CNN
	1    8900 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 4450 8400 4450
Wire Wire Line
	8400 4550 8700 4550
Wire Wire Line
	7350 4650 7800 4650
Text Label 7550 4650 0    60   ~ 0
GND
Wire Wire Line
	7350 4350 7800 4350
Text Label 7550 4350 0    60   ~ 0
S6
$Comp
L RELAY_SIP-1A05 R8
U 1 1 58767EB0
P 8150 5350
F 0 "R8" H 8150 5350 60  0000 C CNN
F 1 "RELAY_SIP-1A05" H 8150 5850 60  0000 C CNN
F 2 "MyLibrary:SIP4_5.08" H 8150 5350 60  0001 C CNN
F 3 "" H 8150 5350 60  0001 C CNN
	1    8150 5350
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P11
U 1 1 58767EB6
P 8900 5100
F 0 "P11" H 8900 5250 50  0000 C CNN
F 1 "CONN_01X02" V 9000 5100 50  0000 C CNN
F 2 "Connectors:bornier2" H 8900 5100 50  0001 C CNN
F 3 "" H 8900 5100 50  0000 C CNN
	1    8900 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 5050 8400 5050
Wire Wire Line
	8400 5150 8700 5150
Wire Wire Line
	7350 5250 7800 5250
Text Label 7550 5250 0    60   ~ 0
GND
Wire Wire Line
	7350 4950 7800 4950
Text Label 7550 4950 0    60   ~ 0
S7
$Comp
L D D1
U 1 1 58768BBC
P 7350 900
F 0 "D1" H 7350 1000 50  0000 C CNN
F 1 "D" H 7350 800 50  0000 C CNN
F 2 "Diodes_SMD:SOD-123" H 7350 900 50  0001 C CNN
F 3 "" H 7350 900 50  0000 C CNN
	1    7350 900 
	0    1    1    0   
$EndComp
$Comp
L D D2
U 1 1 58768C8C
P 7350 1500
F 0 "D2" H 7350 1600 50  0000 C CNN
F 1 "D" H 7350 1400 50  0000 C CNN
F 2 "Diodes_SMD:SOD-123" H 7350 1500 50  0001 C CNN
F 3 "" H 7350 1500 50  0000 C CNN
	1    7350 1500
	0    1    1    0   
$EndComp
$Comp
L D D3
U 1 1 58768D34
P 7350 2100
F 0 "D3" H 7350 2200 50  0000 C CNN
F 1 "D" H 7350 2000 50  0000 C CNN
F 2 "Diodes_SMD:SOD-123" H 7350 2100 50  0001 C CNN
F 3 "" H 7350 2100 50  0000 C CNN
	1    7350 2100
	0    1    1    0   
$EndComp
$Comp
L D D4
U 1 1 58768E5D
P 7350 2700
F 0 "D4" H 7350 2800 50  0000 C CNN
F 1 "D" H 7350 2600 50  0000 C CNN
F 2 "Diodes_SMD:SOD-123" H 7350 2700 50  0001 C CNN
F 3 "" H 7350 2700 50  0000 C CNN
	1    7350 2700
	0    1    1    0   
$EndComp
$Comp
L D D5
U 1 1 58768F13
P 7350 3300
F 0 "D5" H 7350 3400 50  0000 C CNN
F 1 "D" H 7350 3200 50  0000 C CNN
F 2 "Diodes_SMD:SOD-123" H 7350 3300 50  0001 C CNN
F 3 "" H 7350 3300 50  0000 C CNN
	1    7350 3300
	0    1    1    0   
$EndComp
$Comp
L D D6
U 1 1 5876905D
P 7350 3900
F 0 "D6" H 7350 4000 50  0000 C CNN
F 1 "D" H 7350 3800 50  0000 C CNN
F 2 "Diodes_SMD:SOD-123" H 7350 3900 50  0001 C CNN
F 3 "" H 7350 3900 50  0000 C CNN
	1    7350 3900
	0    1    1    0   
$EndComp
$Comp
L D D7
U 1 1 58769113
P 7350 4500
F 0 "D7" H 7350 4600 50  0000 C CNN
F 1 "D" H 7350 4400 50  0000 C CNN
F 2 "Diodes_SMD:SOD-123" H 7350 4500 50  0001 C CNN
F 3 "" H 7350 4500 50  0000 C CNN
	1    7350 4500
	0    1    1    0   
$EndComp
$Comp
L D D8
U 1 1 587691CE
P 7350 5100
F 0 "D8" H 7350 5200 50  0000 C CNN
F 1 "D" H 7350 5000 50  0000 C CNN
F 2 "Diodes_SMD:SOD-123" H 7350 5100 50  0001 C CNN
F 3 "" H 7350 5100 50  0000 C CNN
	1    7350 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	1000 950  1200 950 
Wire Wire Line
	1200 950  1200 900 
Wire Wire Line
	1200 900  1500 900 
Wire Wire Line
	1500 900  1500 950 
Wire Wire Line
	1500 950  1550 950 
Wire Wire Line
	1350 950  1350 900 
Connection ~ 1350 900 
Connection ~ 2400 1250
Text Label 2700 1250 0    60   ~ 0
GND
Wire Wire Line
	2150 950  2950 950 
Connection ~ 2400 950 
Text Label 2550 6300 0    60   ~ 0
GND
$Comp
L R R9
U 1 1 58B2DB4E
P 3750 2000
F 0 "R9" H 3820 2046 50  0000 L CNN
F 1 "10k" H 3820 1955 50  0000 L CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V -120 50  50  0001 C CNN
F 3 "" H -50 50  50  0001 C CNN
	1    3750 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 2200 3750 2150
Wire Wire Line
	3750 1850 3750 1800
Wire Wire Line
	3750 1800 4000 1800
Text Label 3800 1800 0    60   ~ 0
3V3
$EndSCHEMATC
