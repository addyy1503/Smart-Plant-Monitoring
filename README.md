# 🌱 Smart Plant Monitoring System (ESP32 + IoT)
A Smart Plant Monitoring System built using an ESP32 microcontroller that monitors environmental conditions around a plant and allows remote monitoring and control through the Blynk IoT platform. The system measures temperature, humidity, soil moisture, and motion detection, and displays the data on an OLED screen while also sending it to a mobile dashboard.

This project demonstrates a complete IoT-based plant monitoring and control system, integrating sensors, cloud connectivity, and a user interface.

# 📌 Features
* 🌡 Temperature & Humidity Monitoring using DHT11 sensor<br>
* 🌱 Soil Moisture Detection to check plant water needs<br>
* 📟 OLED Display Interface for real-time data visualization<br>
* 📱 Blynk IoT Dashboard for remote monitoring and control<br>
* 🚰 Relay Controlled Water Pump for plant watering<br>
* 🔘 Manual Button Control for pump activation<br>
* 👀 PIR Motion Detection for motion alerts<br>
* ☁️ Cloud Connectivity via WiFi and Blynk<br>

# 🧰 Hardware Components
- ESP32 Development Board<br>
- DHT11 Temperature & Humidity Sensor<br>
- Soil Moisture Sensor<br>
- PIR Motion Sensor<br>
- Relay Module<br>
- OLED Display (128x64 I2C)<br>
- Push Button<br>
- Water Pump / Motor<br>
- Jumper Wires & Breadboard<br>

⚙️ How It Works
1. Sensors collect environmental data around the plant.<br>
2. ESP32 processes the sensor readings.<br>
3. Data is displayed on the OLED screen.<br>
4. Sensor values are sent to the Blynk IoT dashboard.<br>
5. Users can monitor the plant remotely via smartphone.<br>
6. The relay can activate a water pump for irrigation.<br>

# 📷 Project Demonstration

## Circuit Diagram

![Circuit](Images/Circuit.png)

## Blynk Dashboard

![Dashboard](Images/Dashboard.png)

## Mobile UI
<p align="center">
  <img src="Images/Mobile-UI.png" width="300">
</p>
