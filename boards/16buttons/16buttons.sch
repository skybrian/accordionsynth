EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "16 Button Board for Accordion Synthesizer Prototype 4"
Date "2020-01-30"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x05_Male J1
U 1 1 5E2D03BC
P 950 3050
F 0 "J1" H 1050 3400 50  0000 C CNN
F 1 "i2c connector" H 1058 3240 50  0001 C CNN
F 2 "16buttons:PinHeader_i2c" H 950 3050 50  0001 C CNN
F 3 "~" H 950 3050 50  0001 C CNN
	1    950  3050
	1    0    0    -1  
$EndComp
$Comp
L Interface_Expansion:MCP23017_SP U1
U 1 1 5E2D1AA5
P 4050 3700
F 0 "U1" H 4050 4981 50  0000 C CNN
F 1 "MCP23017_SP" H 4050 4890 50  0000 C CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 4250 2700 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001952C.pdf" H 4250 2600 50  0001 L CNN
	1    4050 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 2850 1150 2850
Wire Wire Line
	1150 2950 1750 2950
Wire Wire Line
	1750 2950 1750 2600
Wire Wire Line
	1150 3050 1950 3050
Wire Wire Line
	3050 3050 3050 2900
Wire Wire Line
	3050 2900 3350 2900
Wire Wire Line
	1150 3150 2150 3150
Wire Wire Line
	3150 3150 3150 3000
Wire Wire Line
	3150 3000 3350 3000
$Comp
L 16buttons:SolderJumper JP2
U 1 1 5E2E25E2
P 1950 4300
F 0 "JP2" V 1950 4367 50  0000 L CNN
F 1 "SolderJumper" V 1905 4368 50  0001 L CNN
F 2 "16buttons:SolderJumper_Bridged12" H 1950 4300 50  0001 C CNN
F 3 "~" H 1950 4300 50  0001 C CNN
	1    1950 4300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1500 2850 1500 3600
$Comp
L 16buttons:SolderJumper JP1
U 1 1 5E2E6B7C
P 2350 4400
F 0 "JP1" V 2350 4467 50  0000 L CNN
F 1 "SolderJumper" V 2305 4468 50  0001 L CNN
F 2 "16buttons:SolderJumper_Bridged12" H 2350 4400 50  0001 C CNN
F 3 "~" H 2350 4400 50  0001 C CNN
	1    2350 4400
	0    -1   -1   0   
$EndComp
$Comp
L 16buttons:SolderJumper JP0
U 1 1 5E2E8DC6
P 2750 4500
F 0 "JP0" V 2750 4567 50  0000 L CNN
F 1 "SolderJumper" V 2705 4568 50  0001 L CNN
F 2 "16buttons:SolderJumper_Bridged12" H 2750 4500 50  0001 C CNN
F 3 "~" H 2750 4500 50  0001 C CNN
	1    2750 4500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3350 4500 2900 4500
Wire Wire Line
	3350 4400 2500 4400
Wire Wire Line
	1750 2950 1750 3700
Wire Wire Line
	1750 4100 1950 4100
Connection ~ 1750 2950
Wire Wire Line
	1950 4100 2350 4100
Wire Wire Line
	2350 4100 2350 4200
Connection ~ 1950 4100
Wire Wire Line
	2350 4100 2750 4100
Wire Wire Line
	2750 4100 2750 4300
Connection ~ 2350 4100
Wire Wire Line
	2100 4300 3350 4300
Wire Wire Line
	2750 4100 3350 4100
Wire Wire Line
	3350 4100 3350 3800
Connection ~ 2750 4100
$Comp
L Switch:SW_Push SW1
U 1 1 5E2F7175
P 4950 2150
F 0 "SW1" H 4950 2435 50  0000 C CNN
F 1 "SW_Push" H 4950 2344 50  0000 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 4950 2350 50  0001 C CNN
F 3 "~" H 4950 2350 50  0001 C CNN
	1    4950 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 2900 4750 2150
$Comp
L Switch:SW_Push SW2
U 1 1 5E2F9543
P 5500 2350
F 0 "SW2" H 5500 2635 50  0000 C CNN
F 1 "SW_Push" H 5500 2544 50  0000 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 5500 2550 50  0001 C CNN
F 3 "~" H 5500 2550 50  0001 C CNN
	1    5500 2350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW3
U 1 1 5E2FA478
P 6050 2550
F 0 "SW3" H 6050 2835 50  0000 C CNN
F 1 "SW_Push" H 6050 2744 50  0000 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 6050 2750 50  0001 C CNN
F 3 "~" H 6050 2750 50  0001 C CNN
	1    6050 2550
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW4
U 1 1 5E2FADCA
P 6550 2850
F 0 "SW4" H 6550 3135 50  0000 C CNN
F 1 "SW_Push" H 6550 3044 50  0000 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 6550 3050 50  0001 C CNN
F 3 "~" H 6550 3050 50  0001 C CNN
	1    6550 2850
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW5
U 1 1 5E2FB3ED
P 7100 3100
F 0 "SW5" H 7100 3385 50  0000 C CNN
F 1 "SW_Push" H 7100 3294 50  0000 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 7100 3300 50  0001 C CNN
F 3 "~" H 7100 3300 50  0001 C CNN
	1    7100 3100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW6
U 1 1 5E2FBCCE
P 7600 3350
F 0 "SW6" H 7600 3635 50  0000 C CNN
F 1 "SW_Push" H 7600 3544 50  0000 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 7600 3550 50  0001 C CNN
F 3 "~" H 7600 3550 50  0001 C CNN
	1    7600 3350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW7
U 1 1 5E2FC322
P 8100 3600
F 0 "SW7" H 8100 3885 50  0000 C CNN
F 1 "SW_Push" H 8100 3794 50  0000 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 8100 3800 50  0001 C CNN
F 3 "~" H 8100 3800 50  0001 C CNN
	1    8100 3600
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW8
U 1 1 5E2FC71F
P 8600 3850
F 0 "SW8" H 8600 4135 50  0000 C CNN
F 1 "SW_Push" H 8600 4044 50  0000 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 8600 4050 50  0001 C CNN
F 3 "~" H 8600 4050 50  0001 C CNN
	1    8600 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 3000 5300 2350
Wire Wire Line
	4750 3100 5850 2550
Wire Wire Line
	4750 3200 6350 2850
Wire Wire Line
	4750 3500 7900 3600
Wire Wire Line
	4750 3600 8400 3850
Wire Wire Line
	4750 3400 7400 3350
Wire Wire Line
	6900 3100 4750 3300
$Comp
L Connector:Conn_01x05_Male J2
U 1 1 5E317D99
P 950 3800
F 0 "J2" H 1050 4150 50  0000 C CNN
F 1 "i2c connector" H 1058 3990 50  0001 C CNN
F 2 "16buttons:PinHeader_i2c" H 950 3800 50  0001 C CNN
F 3 "~" H 950 3800 50  0001 C CNN
	1    950  3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 3600 1500 3600
Connection ~ 1500 3600
Wire Wire Line
	1500 3600 1500 4400
Wire Wire Line
	1150 3700 1750 3700
Connection ~ 1750 3700
Wire Wire Line
	1750 3700 1750 4100
Wire Wire Line
	1150 3800 1950 3800
Wire Wire Line
	1950 3800 1950 3050
Connection ~ 1950 3050
Wire Wire Line
	1950 3050 3050 3050
Wire Wire Line
	1150 3900 2150 3900
Wire Wire Line
	2150 3900 2150 3150
Connection ~ 2150 3150
Wire Wire Line
	2150 3150 3150 3150
$Comp
L Switch:SW_Push SW16
U 1 1 5E3246B9
P 5500 3900
F 0 "SW16" H 5500 4093 50  0000 C CNN
F 1 "SW_Push" H 5500 4094 50  0001 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 5500 4100 50  0001 C CNN
F 3 "~" H 5500 4100 50  0001 C CNN
	1    5500 3900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW15
U 1 1 5E325368
P 6000 4150
F 0 "SW15" H 6000 4343 50  0000 C CNN
F 1 "SW_Push" H 6000 4344 50  0001 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 6000 4350 50  0001 C CNN
F 3 "~" H 6000 4350 50  0001 C CNN
	1    6000 4150
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW14
U 1 1 5E3258EF
P 6450 4450
F 0 "SW14" H 6450 4643 50  0000 C CNN
F 1 "SW_Push" H 6450 4644 50  0001 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 6450 4650 50  0001 C CNN
F 3 "~" H 6450 4650 50  0001 C CNN
	1    6450 4450
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW13
U 1 1 5E326474
P 6900 4750
F 0 "SW13" H 6900 4943 50  0000 C CNN
F 1 "SW_Push" H 6900 4944 50  0001 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 6900 4950 50  0001 C CNN
F 3 "~" H 6900 4950 50  0001 C CNN
	1    6900 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3900 4750 3800
Wire Wire Line
	5800 4150 4750 3900
Wire Wire Line
	6250 4450 4750 4000
Wire Wire Line
	6700 4750 4750 4100
$Comp
L Switch:SW_Push SW12
U 1 1 5E32C82B
P 7350 5100
F 0 "SW12" H 7350 5293 50  0000 C CNN
F 1 "SW_Push" H 7350 5294 50  0001 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 7350 5300 50  0001 C CNN
F 3 "~" H 7350 5300 50  0001 C CNN
	1    7350 5100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW11
U 1 1 5E32CF02
P 7800 5500
F 0 "SW11" H 7800 5693 50  0000 C CNN
F 1 "SW_Push" H 7800 5694 50  0001 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 7800 5700 50  0001 C CNN
F 3 "~" H 7800 5700 50  0001 C CNN
	1    7800 5500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW10
U 1 1 5E32D877
P 8250 5900
F 0 "SW10" H 8250 6093 50  0000 C CNN
F 1 "SW_Push" H 8250 6094 50  0001 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 8250 6100 50  0001 C CNN
F 3 "~" H 8250 6100 50  0001 C CNN
	1    8250 5900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW9
U 1 1 5E32DF44
P 8650 6300
F 0 "SW9" H 8650 6493 50  0000 C CNN
F 1 "SW_Push" H 8650 6494 50  0001 C CNN
F 2 "16buttons:SW_Gateron_Trim" H 8650 6500 50  0001 C CNN
F 3 "~" H 8650 6500 50  0001 C CNN
	1    8650 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 5100 4750 4200
Wire Wire Line
	4750 4300 7600 5500
Wire Wire Line
	4750 4400 8050 5900
Wire Wire Line
	4750 4500 8450 6300
Wire Wire Line
	1150 3250 2300 3250
Wire Wire Line
	2300 3250 2300 3600
Wire Wire Line
	2300 3600 3350 3600
Wire Wire Line
	1150 4000 2300 4000
Wire Wire Line
	2300 4000 2300 3600
Connection ~ 2300 3600
NoConn ~ 3350 3500
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5E360884
P 1800 7250
F 0 "#FLG0101" H 1800 7325 50  0001 C CNN
F 1 "PWR_FLAG" H 1800 7423 50  0000 C CNN
F 2 "" H 1800 7250 50  0001 C CNN
F 3 "~" H 1800 7250 50  0001 C CNN
	1    1800 7250
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5E36435C
P 2600 7250
F 0 "#FLG0102" H 2600 7325 50  0001 C CNN
F 1 "PWR_FLAG" H 2600 7423 50  0000 C CNN
F 2 "" H 2600 7250 50  0001 C CNN
F 3 "~" H 2600 7250 50  0001 C CNN
	1    2600 7250
	1    0    0    -1  
$EndComp
Text Label 1200 2850 0    50   ~ 0
GND
Text Label 1200 2950 0    50   ~ 0
Vin
Text Label 1200 3050 0    50   ~ 0
SDA
Text Label 1200 3150 0    50   ~ 0
SCK
Text Label 1200 3250 0    50   ~ 0
INT
Text Label 1800 7400 0    50   ~ 0
Vin
Wire Wire Line
	1800 7250 1800 7400
Wire Wire Line
	1750 2600 4050 2600
Text Label 2600 7400 0    50   ~ 0
GND
Wire Wire Line
	2600 7250 2600 7400
Text Label 2100 4300 0    50   ~ 0
Addr2
Text Label 2500 4400 0    50   ~ 0
Addr1
Text Label 2900 4500 0    50   ~ 0
Addr0
$Comp
L power:GND #PWR0101
U 1 1 5E304375
P 4050 4800
F 0 "#PWR0101" H 4050 4550 50  0001 C CNN
F 1 "GND" H 4055 4627 50  0000 C CNN
F 2 "" H 4050 4800 50  0001 C CNN
F 3 "" H 4050 4800 50  0001 C CNN
	1    4050 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5E304A04
P 2750 4700
F 0 "#PWR0102" H 2750 4450 50  0001 C CNN
F 1 "GND" H 2755 4527 50  0000 C CNN
F 2 "" H 2750 4700 50  0001 C CNN
F 3 "" H 2750 4700 50  0001 C CNN
	1    2750 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5E304F9E
P 2350 4600
F 0 "#PWR0103" H 2350 4350 50  0001 C CNN
F 1 "GND" H 2355 4427 50  0000 C CNN
F 2 "" H 2350 4600 50  0001 C CNN
F 3 "" H 2350 4600 50  0001 C CNN
	1    2350 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5E305406
P 1950 4500
F 0 "#PWR0104" H 1950 4250 50  0001 C CNN
F 1 "GND" H 1955 4327 50  0000 C CNN
F 2 "" H 1950 4500 50  0001 C CNN
F 3 "" H 1950 4500 50  0001 C CNN
	1    1950 4500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5E305709
P 1500 4400
F 0 "#PWR0105" H 1500 4150 50  0001 C CNN
F 1 "GND" H 1505 4227 50  0000 C CNN
F 2 "" H 1500 4400 50  0001 C CNN
F 3 "" H 1500 4400 50  0001 C CNN
	1    1500 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5E30D561
P 8800 3850
F 0 "#PWR0106" H 8800 3600 50  0001 C CNN
F 1 "GND" H 8805 3677 50  0000 C CNN
F 2 "" H 8800 3850 50  0001 C CNN
F 3 "" H 8800 3850 50  0001 C CNN
	1    8800 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5E30F773
P 8850 6300
F 0 "#PWR0107" H 8850 6050 50  0001 C CNN
F 1 "GND" H 8855 6127 50  0000 C CNN
F 2 "" H 8850 6300 50  0001 C CNN
F 3 "" H 8850 6300 50  0001 C CNN
	1    8850 6300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5E324977
P 8300 3600
F 0 "#PWR0108" H 8300 3350 50  0001 C CNN
F 1 "GND" H 8305 3427 50  0000 C CNN
F 2 "" H 8300 3600 50  0001 C CNN
F 3 "" H 8300 3600 50  0001 C CNN
	1    8300 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5E325044
P 7800 3350
F 0 "#PWR0109" H 7800 3100 50  0001 C CNN
F 1 "GND" H 7805 3177 50  0000 C CNN
F 2 "" H 7800 3350 50  0001 C CNN
F 3 "" H 7800 3350 50  0001 C CNN
	1    7800 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5E32548B
P 7300 3100
F 0 "#PWR0110" H 7300 2850 50  0001 C CNN
F 1 "GND" H 7305 2927 50  0000 C CNN
F 2 "" H 7300 3100 50  0001 C CNN
F 3 "" H 7300 3100 50  0001 C CNN
	1    7300 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5E32589F
P 6750 2850
F 0 "#PWR0111" H 6750 2600 50  0001 C CNN
F 1 "GND" H 6755 2677 50  0000 C CNN
F 2 "" H 6750 2850 50  0001 C CNN
F 3 "" H 6750 2850 50  0001 C CNN
	1    6750 2850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5E325D2A
P 6250 2550
F 0 "#PWR0112" H 6250 2300 50  0001 C CNN
F 1 "GND" H 6255 2377 50  0000 C CNN
F 2 "" H 6250 2550 50  0001 C CNN
F 3 "" H 6250 2550 50  0001 C CNN
	1    6250 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5E32621B
P 5700 2350
F 0 "#PWR0113" H 5700 2100 50  0001 C CNN
F 1 "GND" H 5705 2177 50  0000 C CNN
F 2 "" H 5700 2350 50  0001 C CNN
F 3 "" H 5700 2350 50  0001 C CNN
	1    5700 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5E326552
P 5150 2150
F 0 "#PWR0114" H 5150 1900 50  0001 C CNN
F 1 "GND" H 5155 1977 50  0000 C CNN
F 2 "" H 5150 2150 50  0001 C CNN
F 3 "" H 5150 2150 50  0001 C CNN
	1    5150 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 5E333D92
P 8450 5900
F 0 "#PWR0115" H 8450 5650 50  0001 C CNN
F 1 "GND" H 8455 5727 50  0000 C CNN
F 2 "" H 8450 5900 50  0001 C CNN
F 3 "" H 8450 5900 50  0001 C CNN
	1    8450 5900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 5E33410C
P 8000 5500
F 0 "#PWR0116" H 8000 5250 50  0001 C CNN
F 1 "GND" H 8005 5327 50  0000 C CNN
F 2 "" H 8000 5500 50  0001 C CNN
F 3 "" H 8000 5500 50  0001 C CNN
	1    8000 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 5E3342BB
P 7550 5100
F 0 "#PWR0117" H 7550 4850 50  0001 C CNN
F 1 "GND" H 7555 4927 50  0000 C CNN
F 2 "" H 7550 5100 50  0001 C CNN
F 3 "" H 7550 5100 50  0001 C CNN
	1    7550 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 5E334679
P 7100 4750
F 0 "#PWR0118" H 7100 4500 50  0001 C CNN
F 1 "GND" H 7105 4577 50  0000 C CNN
F 2 "" H 7100 4750 50  0001 C CNN
F 3 "" H 7100 4750 50  0001 C CNN
	1    7100 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 5E33484A
P 6650 4450
F 0 "#PWR0119" H 6650 4200 50  0001 C CNN
F 1 "GND" H 6655 4277 50  0000 C CNN
F 2 "" H 6650 4450 50  0001 C CNN
F 3 "" H 6650 4450 50  0001 C CNN
	1    6650 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 5E334AD6
P 6200 4150
F 0 "#PWR0120" H 6200 3900 50  0001 C CNN
F 1 "GND" H 6205 3977 50  0000 C CNN
F 2 "" H 6200 4150 50  0001 C CNN
F 3 "" H 6200 4150 50  0001 C CNN
	1    6200 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 5E334E72
P 5700 3900
F 0 "#PWR0121" H 5700 3650 50  0001 C CNN
F 1 "GND" H 5705 3727 50  0000 C CNN
F 2 "" H 5700 3900 50  0001 C CNN
F 3 "" H 5700 3900 50  0001 C CNN
	1    5700 3900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
