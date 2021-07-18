# drone with gyroscopic guard

**Develop drone firmware and Design gyroscopic guard**

![깃헙 소셜 프리뷰 사진](https://user-images.githubusercontent.com/48342925/123043646-90a3b300-d433-11eb-99dd-8545261a8c11.png)


---

## Dev Environment
### Tools
- STM32CubeIDE
- Solidworks
- Kicad
 
---
## System Architecture

![drone with my controller](https://user-images.githubusercontent.com/48342925/123049019-07dc4580-d43a-11eb-8df2-dd53fbee2753.png)

---

## Parts

### 1. Gyroscopic Guard

<img src = https://user-images.githubusercontent.com/48342925/120675984-8a738400-c4d0-11eb-9ec6-cfb9434c2b29.png width = "400" height = "400"><img src = https://user-images.githubusercontent.com/48342925/120676528-15ed1500-c4d1-11eb-9458-e0ceaea3dd1e.jpg width = "400" height = "400">

#### Configuration

- 3mm carbon rod
- 3mm carbon plate
- Small bearing
- Shaft
- 3d printed parts

#### Feature

- Protect drones and Respond flexibly to collisions.
- x-axis drone mounter
- x-axis gyroscope ring
- y-axis gyroscope ring
- z-axis 2V geodesic sphere

### 2. Quadcopter

<img src = https://user-images.githubusercontent.com/48342925/120677179-c78c4600-c4d1-11eb-9ebb-3a9b6eed6eae.jpg width = "400" height = "400"><img src = https://user-images.githubusercontent.com/48342925/120677044-a1ff3c80-c4d1-11eb-8f65-7ed28fb8ffee.jpg width = "400" height = "400">

#### Configuration

- STM32F4CEU6 core board
- 210mm frame  
- 2207 2450KV BLDC  
- 5045 props  
- 3S-4S PDB  
- BLHeli_32 35A ESC  
- IMU (ICM20948)
- RF Transceiver (nrf24l01+pa+lna)
- Buzzer  
- 4S Lipo Battery  
- Battery Monitor Circuit
- SWD (st-link)  

#### Schematic

![image](https://user-images.githubusercontent.com/48342925/123548490-e794e980-d79f-11eb-9ca8-57bd8c56f42c.png)


#### Feature

- 1 Khz PID loop
- Battery Monitor
- [ICM20948 library](https://github.com/mokhwasomssi/stm32_hal_icm20948.git)
- [Dshot protocol library](https://github.com/mokhwasomssi/stm32_hal_dshot.git)

### 3. Controller

![image](https://user-images.githubusercontent.com/48342925/123052020-550de680-d43d-11eb-83be-033c09cbf3f6.png)


#### Configuration

- STM32F4CEU6 core board
- Joy Stick X 2
- OLED LCD
- RF Transceiver (nrf24l01+pa+lna)
- Switch X 2 (with led)
- Buzzer
- 18650 battery X 2

#### Schematic
![image](https://user-images.githubusercontent.com/48342925/123548329-4e65d300-d79f-11eb-9d46-454876b15ad7.png)


