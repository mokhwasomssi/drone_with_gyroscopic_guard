# Drone_with_Gyroscopic_Guard

### Develop drone firmware and Design gyroscopic guard

This concept is same as [flyability drone](https://www.flyability.com/).  
I'm a student and making it personally.

- Drone - STM32F4
- GCS - Rasberry Pi
- Gyroscopic guard

---

## Drone

### Hardware Configuration

- STM32F4CEU6   
- 210mm frame  
- 2207 2450KV BLDC  
- 5045 props  
- PDB  
- ESC  
- IMU  
- RF module - UAV control and Telemetry both   
- Buzzer  
- 4S Lipo Battery  
- Battery Monitor  
- SWD (st-link)  

### Software Features

- OS x
- 1Khz control loop  

---
## GCS

### Hardware Configuration 

- Rasberry Pi  
- LCD  
- RF module - UAV control and Telemetry both   
- Joy Stick  
- Control Button
- Battery

### Software Features

- Linux OS
- Control Drone
- Monitor Flight Status - ESC, IMU, Battery Voltage

--- 

## Gyroscopic Guard

### Hardwre Configuration

- 3mm Carbon Rod
- Bearing
- Shaft
- 3D Printer Output

### Feature

- Roll-axis Gyroscope Ring
- Pitch-axis Gyroscope Ring
- Yaw-axis 2V Geomesic Sphere
