# Drone_with_Gyroscopic_Guard

### Develop Drone Firmware and Design Gyroscopic Guard

Gyroscopic Guard is similar to [flyability drone](https://www.flyability.com/).  
I'm a student and making it personally.
 
---

## Size
- Drone - 5 inches, 210mm
- GCS - hand-held
- Gyroscopic guard - Diameter 480mm

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
- RF module - Drone control and Telemetry both   
- Buzzer  
- 4S Lipo Battery  
- Battery Monitor  
- SWD (st-link)  

### Software Features

- OS x
- 1Khz Control Loop  

---
## GCS

### Hardware Configuration 

- Rasberry Pi  
- LCD  
- RF module - Drone control and Telemetry both   
- Joy Stick  
- Control Button
- Battery

### Software Features

- Linux OS
- Control Drone - Roll, Pitch, Yaw, Throttle
- Monitor Flight Status - Data from ESC and IMU, Battery Voltage

--- 

## Gyroscopic Guard

### Hardwre Configuration

- 3mm Carbon Rod
- 3mm Carbon Plate
- Bearing
- Shaft
- 3D Printer Output

### Feature

- Roll-axis Gyroscope Ring
- Pitch-axis Gyroscope Ring
- Yaw-axis 2V Geomesic Sphere

---