EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "quadcopter"
Date "2021-04-06"
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L quadcopter_symbol:weact_stm32f411ceu6 U??
U 1 1 606BC977
P 8150 2650
F 0 "U??" H 8150 3715 50  0000 C CNN
F 1 "weact_stm32f411ceu6" H 8150 3624 50  0000 C CNN
F 2 "" H 8250 3750 50  0001 C CNN
F 3 "" H 8250 3750 50  0001 C CNN
	1    8150 2650
	1    0    0    -1  
$EndComp
Text GLabel 8150 4300 3    50   Input ~ 0
SWDIO
Text GLabel 8250 4300 3    50   Input ~ 0
SWCLK
Wire Wire Line
	8150 4050 8150 4300
Wire Wire Line
	8250 4050 8250 4300
$Comp
L power:+3.3V #PWR?
U 1 1 606C092E
P 7850 4200
F 0 "#PWR?" H 7850 4050 50  0001 C CNN
F 1 "+3.3V" H 7865 4373 50  0000 C CNN
F 2 "" H 7850 4200 50  0001 C CNN
F 3 "" H 7850 4200 50  0001 C CNN
	1    7850 4200
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 606C144E
P 8500 4200
F 0 "#PWR?" H 8500 3950 50  0001 C CNN
F 1 "GND" H 8505 4027 50  0000 C CNN
F 2 "" H 8500 4200 50  0001 C CNN
F 3 "" H 8500 4200 50  0001 C CNN
	1    8500 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 4050 8050 4200
Wire Wire Line
	8050 4200 7850 4200
Wire Wire Line
	8350 4050 8350 4200
Wire Wire Line
	8350 4200 8500 4200
$EndSCHEMATC
