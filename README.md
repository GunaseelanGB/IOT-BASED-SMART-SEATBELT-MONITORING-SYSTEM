# IoT-Based Smart Seatbelt Monitoring System

This project uses an ESP32, an HX711 load-cell amplifier, and a proximity sensor to monitor whether a vehicle seat is occupied and whether its seatbelt is fastened. The ESP32 sounds a buzzer when an occupied seat has an unfastened belt and serves a simple status page over Wi-Fi.

## Hardware

- ESP32 development board
- HX711 load-cell amplifier and load cell
- Proximity sensor positioned to detect the seatbelt buckle
- Buzzer

### Pin connections

| Component | ESP32 pin |
| --- | --- |
| HX711 DT | GPIO 4 |
| HX711 SCK | GPIO 5 |
| Proximity sensor output | GPIO 18 |
| Buzzer | GPIO 19 |

Connect all components to a common ground and use voltage levels compatible with the ESP32.

## Firmware setup

1. Open `IOT-BASED-SMART-SEATBELT-MONITORING-SYSTEM.ino` in the Arduino IDE.
2. Install the `HX711` library and select an ESP32 board and its serial port.
3. Replace `YOUR_WIFI_NAME` and `YOUR_WIFI_PASSWORD` in the sketch with your Wi-Fi credentials.
4. Upload the sketch. Open the serial monitor at 115200 baud to see the ESP32's IP address and sensor readings.
5. Visit that IP address from a device on the same Wi-Fi network to view the seat, belt, buzzer, and weight status.
6. Calibrate the load cell for your hardware and adjust `calibration_factor` and the occupied-seat threshold as needed.

The proximity sensor logic assumes `HIGH` means the belt is not fixed. Adjust the sketch if your sensor has the opposite output behavior. This prototype is for demonstration and is not a certified vehicle safety system.
