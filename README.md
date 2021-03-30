# gyroscope-drone

## 0. Intro

### 3D modeling image
![다운로드](https://user-images.githubusercontent.com/48342925/111861476-de6ed200-8991-11eb-9798-e63ba10da68a.png)  
( drone size = 210mm, sphere diameter = 480mm )  

### Overview
![드론 개관](https://user-images.githubusercontent.com/48342925/113011908-389f3c80-91b5-11eb-9d83-049acfd645b0.png)


* Why this project name is gyroscope-drone?  
    * because, it has sphere-shaped guard with gyroscope structure.

* Why do you put a guard like this on a normal quadcopter?  
    1. prop gurad
    2. flight tester
    3. cushion the impact
    4. rolling motion on a plane

* What kind of open-source do you use for flight firmware?  
    * there are drone open-sources like betaflight, ardupilot, px4 and so on.
    * but I'm trying to write my own code for flight.

---

## 1. Development environment

* Software tools
    * STM32Cubeide (STM32Cube HAL)
    * SOLIDWORKS 2020

* Debugging
    * ST-LINK V2
    * Oscilloscope
    * Multimeter

* Drone parts

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

---

## 1. FEATURE

* ICM-20948 - https://github.com/mokhwasomssi/icm20948.git
* DSHOT600 - https://github.com/mokhwasomssi/dshot.git
* IBUS - https://github.com/mokhwasomssi/flysky_ibus.git



---

## Reference

https://eurekadynamics.com/  
https://www.flyability.com/
