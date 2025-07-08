# 🐾 Pet Bot Controller with micro-ROS and ESP32

A simple quadruped pet bot control system built using **ESP32**, **micro-ROS**, and **servo motors**. The bot connects to a Wi-Fi network, subscribes to ROS messages on the `/cmd_vel` topic, and responds with basic movements like **forward trot**, **left turn**, and **right turn** based on Twist message commands.

---

## 📜 Project Overview

This project implements a ROS-integrated quadruped robot (pet bot) controller using ESP32. It receives velocity commands from a ROS system and controls eight servos (four hip and four knee joints) to perform basic gait movements.

---

## 📦 Features

- 📡 Connects to Wi-Fi for ROS communication via micro-ROS.
- 📥 Subscribes to `/cmd_vel` topic (geometry_msgs/Twist).
- 🦿 Controls 8 servos: 4 hip joints and 4 knee joints.
- 🏃‍♂️ Implements basic gaits:
  - Trot forward
  - Move left
  - Move right
  - Neutral stop position
- 🔄 Adjustable gait speed (via `setSpeed()` function).

---

## 🖥️ Tech Stack

- **ESP32**
- **Arduino IDE**
- **micro-ROS**
- **geometry_msgs/Twist**
- **ESP32Servo Library**

---

## 📌 Wiring Overview

| Servo | Function          | Pin |
|:-------|:------------------|:-----|
| 0-3     | Hip joints (FL, RR, FR, RL) | 25, 26, 27, 14 |
| 4-7     | Knee joints (FL, RR, FR, RL) | 33, 32, 15, 4 |

---

## 🚀 How It Works

1. ESP32 connects to the Wi-Fi network using credentials.
2. micro-ROS initializes and subscribes to `/cmd_vel`.
3. When a Twist message arrives:
   - `linear.x > 0`: Trot forward.
   - `linear.y > 0`: Move left.
   - `linear.y < 0`: Move right.
   - Else: Set all servos to neutral (90°).
4. Movements are executed via servo position adjustments.

---

## 📶 Wi-Fi & micro-ROS Setup

Update these credentials inside `pet_bot_4.cpp`:

```cpp
char wifi_ssid[] = "Your_SSID";
char wifi_password[] = "Your_Password";
char wifi_ip[] = "192.168.0.10";
uint16_t wifi_port = 8888;
