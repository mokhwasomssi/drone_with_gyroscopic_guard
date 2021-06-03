# drone_with_gyroscopic_guard

## 프로젝트 주제
- 쿼드콥터 비행 펌웨어 개발 및 자이로스코프 형태의 가드 설계  
(Develop Drone Firmware and Design Gyroscopic Guard)

---

## 프로젝트 취지
- 자체적인 비행 펌웨어 개발

---

## 진행 과정
- 블로그에서 [Drone With Gyroscopic Guard](https://mokhwasomssi.tistory.com/category/Drone%20With%20Gyroscopic%20Guard) 카테고리에 기록 중

---

## 개발 환경
### 사용 툴
- STM32CubeIDE
- Solidworks
- Kicad
- VS code

### 디버깅
- ST-LINK (SWD)
- UART
- 부저 & LED
- 멀티미터
- 오실로스코프
 
---
## 전체 구성 

<img src = https://user-images.githubusercontent.com/48342925/120675093-bd694800-c4cf-11eb-8fd9-1b790a0e0a16.png width = "80%" height = "80%">

- `자이로스코픽 가드` - 480mm
- `쿼드콥터` - 5 inches, 210mm

---

## `자이로스코픽 가드`

<img src = https://user-images.githubusercontent.com/48342925/120675984-8a738400-c4d0-11eb-9ec6-cfb9434c2b29.png width = "400" height = "400">

<img src = https://user-images.githubusercontent.com/48342925/120676528-15ed1500-c4d1-11eb-9458-e0ceaea3dd1e.jpg width = "400" height = "400">

### 구성

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

## `쿼드콥터`

<img src = https://user-images.githubusercontent.com/48342925/120677179-c78c4600-c4d1-11eb-9ebb-3a9b6eed6eae.jpg width = "400" height = "400">
<img src = https://user-images.githubusercontent.com/48342925/120677044-a1ff3c80-c4d1-11eb-8f65-7ed28fb8ffee.jpg width = "400" height = "400">

(rf 모듈은 안쓰는 겁니다...)

### 구성 

- 기체
    - STM32F4CEU6   
    - 210mm frame  
    - 2207 2450KV BLDC  
    - 5045 props  
    - PDB  
    - ESC  
    - IMU  
    - Buzzer  
    - 4S Lipo Battery  
    - Battery Monitor  
    - SWD (st-link)  
- 조종기
    - 송신기 : FS-i6
    - 수신기 : FS-A8S

### 특징
- 1 Khz 제어주기
- Dshot 프로토콜 사용
- i-bus 프로토콜 사용
