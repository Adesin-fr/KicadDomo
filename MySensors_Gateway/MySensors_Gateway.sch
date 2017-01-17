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
LIBS:arduino
LIBS:mysensors_radios
LIBS:MySensors_Gateway-cache
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
$Comp
L arduino_mini U2
U 1 1 587E3552
P 3950 3550
F 0 "U2" H 4450 2600 70  0000 C CNN
F 1 "arduino_mini" H 4700 2500 70  0000 C CNN
F 2 "arduino:arduino_mini" H 3950 3500 60  0001 C CNN
F 3 "" H 3950 3550 60  0001 C CNN
	1    3950 3550
	1    0    0    -1  
$EndComp
$Comp
L RFM69HW U3
U 1 1 587E35B6
P 7450 4500
F 0 "U3" H 7100 4750 40  0000 C CNN
F 1 "RFM69HW" H 7700 3750 40  0000 C CNN
F 2 "Mysensors_Radio:RFM69HW_SMD_Handsoldering" H 7450 4500 30  0001 C CIN
F 3 "" H 7450 4500 60  0000 C CNN
	1    7450 4500
	1    0    0    -1  
$EndComp
$Comp
L AP111733 U1
U 1 1 587E35F9
P 1550 1050
F 0 "U1" H 1650 800 50  0000 C CNN
F 1 "AP111733" H 1550 1300 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-223" H 1550 700 50  0001 C CNN
F 3 "" H 1650 800 50  0000 C CNN
	1    1550 1050
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 587E3694
P 7350 2150
F 0 "D1" H 7350 2250 50  0000 C CNN
F 1 "LED" H 7350 2050 50  0000 C CNN
F 2 "LEDs:LED-3MM" H 7350 2150 50  0001 C CNN
F 3 "" H 7350 2150 50  0000 C CNN
	1    7350 2150
	-1   0    0    1   
$EndComp
$Comp
L R R1
U 1 1 587E373F
P 6950 2150
F 0 "R1" V 7030 2150 50  0000 C CNN
F 1 "R" V 6950 2150 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 6880 2150 50  0001 C CNN
F 3 "" H 6950 2150 50  0000 C CNN
	1    6950 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	7200 2150 7100 2150
Wire Wire Line
	6800 2150 6450 2150
Text Label 6450 2150 0    60   ~ 0
LED_TX
$Comp
L LED D2
U 1 1 587E37F8
P 7350 2450
F 0 "D2" H 7350 2550 50  0000 C CNN
F 1 "LED" H 7350 2350 50  0000 C CNN
F 2 "LEDs:LED-3MM" H 7350 2450 50  0001 C CNN
F 3 "" H 7350 2450 50  0000 C CNN
	1    7350 2450
	-1   0    0    1   
$EndComp
$Comp
L R R2
U 1 1 587E37FE
P 6950 2450
F 0 "R2" V 7030 2450 50  0000 C CNN
F 1 "R" V 6950 2450 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 6880 2450 50  0001 C CNN
F 3 "" H 6950 2450 50  0000 C CNN
	1    6950 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	7200 2450 7100 2450
Wire Wire Line
	6800 2450 6450 2450
Text Label 6450 2450 0    60   ~ 0
LED_RX
$Comp
L LED D3
U 1 1 587E384F
P 7350 2750
F 0 "D3" H 7350 2850 50  0000 C CNN
F 1 "LED" H 7350 2650 50  0000 C CNN
F 2 "LEDs:LED-3MM" H 7350 2750 50  0001 C CNN
F 3 "" H 7350 2750 50  0000 C CNN
	1    7350 2750
	-1   0    0    1   
$EndComp
$Comp
L R R3
U 1 1 587E3855
P 6950 2750
F 0 "R3" V 7030 2750 50  0000 C CNN
F 1 "R" V 6950 2750 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 6880 2750 50  0001 C CNN
F 3 "" H 6950 2750 50  0000 C CNN
	1    6950 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	7200 2750 7100 2750
Wire Wire Line
	6800 2750 6450 2750
Text Label 6450 2750 0    60   ~ 0
LED_ERR
Wire Wire Line
	7500 2150 7650 2150
Wire Wire Line
	7650 2150 7650 2850
Wire Wire Line
	7650 2850 7950 2850
Wire Wire Line
	7500 2450 7650 2450
Connection ~ 7650 2450
Wire Wire Line
	7500 2750 7650 2750
Connection ~ 7650 2750
Text Label 7750 2850 0    60   ~ 0
GND
$Comp
L CONN_01X01 P1
U 1 1 587E3906
P 6350 4350
F 0 "P1" H 6350 4450 50  0000 C CNN
F 1 "CONN_01X01" V 6450 4350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 6350 4350 50  0001 C CNN
F 3 "" H 6350 4350 50  0000 C CNN
	1    6350 4350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6550 4350 6900 4350
Wire Wire Line
	7450 4150 7450 4050
Wire Wire Line
	7450 4050 7800 4050
Text Label 7600 4050 0    60   ~ 0
3V3
Wire Wire Line
	7350 5350 7350 5450
Wire Wire Line
	7350 5450 8050 5450
Wire Wire Line
	7550 5350 7550 5450
Connection ~ 7550 5450
Wire Wire Line
	6900 4550 6500 4550
Wire Wire Line
	6900 4650 6500 4650
Wire Wire Line
	6900 4750 6500 4750
Wire Wire Line
	6900 4850 6500 4850
Wire Wire Line
	8000 4500 8400 4500
Text Label 8100 4500 0    60   ~ 0
IRQ
Text Label 7800 5450 0    60   ~ 0
GND
$Comp
L C C2
U 1 1 587E3B8A
P 2150 1200
F 0 "C2" H 2175 1300 50  0000 L CNN
F 1 "C" H 2175 1100 50  0000 L CNN
F 2 "Capacitors_THT:C_Radial_D5_L6_P2.5" H 2188 1050 50  0001 C CNN
F 3 "" H 2150 1200 50  0000 C CNN
	1    2150 1200
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 587E3C08
P 900 1200
F 0 "C1" H 925 1300 50  0000 L CNN
F 1 "C" H 925 1100 50  0000 L CNN
F 2 "Capacitors_THT:C_Radial_D5_L6_P2.5" H 938 1050 50  0001 C CNN
F 3 "" H 900 1200 50  0000 C CNN
	1    900  1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	650  1050 1250 1050
Connection ~ 900  1050
Wire Wire Line
	900  1350 900  1400
Wire Wire Line
	900  1400 2550 1400
Wire Wire Line
	1550 1400 1550 1350
Wire Wire Line
	2150 1400 2150 1350
Connection ~ 1550 1400
Connection ~ 2150 1400
Wire Wire Line
	1850 1050 2550 1050
Connection ~ 2150 1050
Text Label 2450 1050 0    60   ~ 0
3V3
Text Label 2450 1400 0    60   ~ 0
GND
Text Label 750  1050 0    60   ~ 0
VUSB
Wire Wire Line
	3950 2400 3950 2250
Wire Wire Line
	3950 2250 4750 2250
Text Label 4250 2250 0    60   ~ 0
VUSB
Wire Wire Line
	3950 5100 3950 5150
Wire Wire Line
	3950 5150 4550 5150
Text Label 4300 5150 0    60   ~ 0
GND
Text Label 6550 4550 0    60   ~ 0
CS
Text Label 6550 4650 0    60   ~ 0
MOSI
Text Label 6550 4750 0    60   ~ 0
MISO
Text Label 6550 4850 0    60   ~ 0
SCK
Wire Wire Line
	4650 2900 5150 2900
Wire Wire Line
	4650 3000 5150 3000
Wire Wire Line
	4650 3100 5150 3100
Wire Wire Line
	4650 3200 5150 3200
Text Label 4950 3200 0    60   ~ 0
CS
Text Label 4950 3100 0    60   ~ 0
MOSI
Text Label 4950 3000 0    60   ~ 0
MISO
Text Label 4950 2900 0    60   ~ 0
SCK
Wire Wire Line
	3250 3350 2850 3350
Wire Wire Line
	3250 3450 2850 3450
Wire Wire Line
	3250 3550 2850 3550
Text Label 2850 3350 0    60   ~ 0
LED_TX
Text Label 2850 3450 0    60   ~ 0
LED_RX
Text Label 2850 3550 0    60   ~ 0
LED_ERR
Wire Wire Line
	4650 4150 5150 4150
Text Label 4950 4150 0    60   ~ 0
IRQ
$EndSCHEMATC
