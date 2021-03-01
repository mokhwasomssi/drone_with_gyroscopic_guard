# stm32f4_hal_quadcopter (now working)

My goal is writing all code needed for flight.

![20210219_130214](https://user-images.githubusercontent.com/48342925/109497628-af251d80-7ad5-11eb-8354-0117b9716f45.jpg)


## 0. Development environment

* IDE
    * STM32Cubeide 1.5.0 (STM32Cube HAL)

* Debugging
    * ST-LINK V2
    * Oscilloscope
    * Multimeter

* Part 

|No.|Part|Name|
|:---:|:---:|:---:|
|1|FC|[WeAct Black Pill <br> (STM32F411CEU6)](https://github.com/WeActTC/MiniF4-STM32F4x1)|
|2|Frame|Mini QAV 210mm|
|3|PDB|MATEK PDB 3-4S 5V 12V|
|4|ESC|HAKRC BLHeli_32 Bit 35A 2-5S ESC |
|5|Motor|iFlight XING E 2207 2450KV|
|6|Props|5045 3 blades CW, CWW|
|7|IMU|SparkFun 9DoF IMU Breakout - ICM-20948 (Qwiic)|
|8|Transmitter|FS-i6|
|9|Receiver|FS-A8S|
|10|Battery|ZOP Power 14.8V 1800mAh 65C 4S|
|11|Lipo Alarm|Voltage Buzzer Alarm|

## 1. FEATURE

* MCU
* ICM20948
* DSHOT600
* IBUS
* PID
