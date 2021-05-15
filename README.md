# Drone_with_Gyroscopic_Guard

## 프로젝트 주제
- 쿼드콥터 비행 펌웨어 개발 및 자이로스코프 형태의 가드 설계  
(Develop Drone Firmware and Design Gyroscopic Guard)

---

## 프로젝트 취지
- 자체적인 비행 펌웨어 개발

---

## 진행 과정
- 블로그의 Drone With Gyroscopic Guard라는 카테고리에 기록 중.
- 삽질한거 창피하니까 자세히 안봤으면 좋겠다.
- https://mokhwasomssi.tistory.com/category/Drone%20With%20Gyroscopic%20Guard

---

## 개발 환경
### 사용 툴
- STM32CubeIDE
- Solidworks
- Kicad
- VS code

### 디버깅 방법
- ST-LINK (SWD)
- UART
- 부저 & LED
- 멀티미터
- 오실로스코프
 
---
## 전체 구성 
- `쿼드콥터` - 5 inches, 210mm
- `간단한 GCS` (Ground Control System) - 닌텐도 스위치 크기
- `자이로스코픽 가드` - 최외각 지름 480mm

---
## `쿼드콥터`

### 사진 
![20210508_100119](https://user-images.githubusercontent.com/48342925/118347508-db9df100-b57e-11eb-9086-51e84728b067.jpg)


### 블록 다이어그램 (수정 필요)

![FMU Block Diagram](https://user-images.githubusercontent.com/48342925/117300001-197e8380-aeb4-11eb-9904-a98ef876119a.png)

### 하드웨어 구성 
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

### 소프트웨어 특징
- 운영체제 미탑재
- Dshot ESC 프로토콜
- 1Khz 제어 주기  

---
## `간단한 GCS` - 드론 조종 & 비행 상태 모니터

### 하드웨어 구성  
- Rasberry Pi  
- LCD  
- RF module - Drone control and Telemetry both   
- Joy Stick  
- Control Button
- Battery

### 소프트웨어 특징 
- 리눅스 운영체제 기반
- 드론 조종 - Roll, Pitch, Yaw, Throttle
- 비행 상태 모니터 - ESC와 IMU에서 얻은 데이터, 배터리 방전 상태

--- 

## `자이로스코픽 가드`

### 3D 모델링 이미지
![image](https://user-images.githubusercontent.com/48342925/117300397-7843fd00-aeb4-11eb-91a1-5b9b1473b542.png)


### 구성 부품들

- 지름 3mm 카본 로드
- 두께 3mm 카본 플레이트
- 소형 베어링
- 샤프트 (평행핀)
- 3D 프린터 출력물

### 특징
- 장애물에 충돌시 충격을 완화 시키는 구조
- x축 회전 자이로스코프 링
- y축 회전 자이로스코프 링
- z축 회전 2V 지오데식 구

---

아직 구체적인 부분은 정해지지 않은게 많다.   
차차 업데이트 할 예정.