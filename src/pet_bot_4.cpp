#include <ESP32Servo.h>
#include <micro_ros_arduino.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <geometry_msgs/msg/twist.h>

// Define Wi-Fi credentials
char wifi_ssid[] = "Rabindra_WiFi";
char wifi_password[] = "SecurePassword123";
char wifi_ip[] = "192.168.0.10";
uint16_t wifi_port = 8888;

// Servo pins
int servo_hip_pins[4] = {25, 26, 27, 14};
int servo_knee_pins[4] = {33, 32, 15, 4};
Servo servos[8]; // 4 hip and 4 knee servos

// Speed settings
int gait_speed = 1000; // Predefined speed, adjustable later

// ROS setup
rcl_subscription_t subscriber_cmd_vel;
geometry_msgs__msg__Twist cmd_vel_msg;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;

// Error checking macros
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if ((temp_rc != RCL_RET_OK)) { errorLoop(); } }
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if ((temp_rc != RCL_RET_OK)) {} }

// Error handling
void errorLoop() {
  while (1) {
    delay(100);
  }
}

// ROS callback for user commands
void userControlCallback(const void* msgin) {
  const geometry_msgs__msg__Twist* msg = (const geometry_msgs__msg__Twist*)msgin;
  float x = msg->linear.x;  // Forward/backward
  float y = msg->linear.y;  // Left/right

  if (x > 0) {
    trotGait();
  } else if (y > 0) {
    moveLeft();
  } else if (y < 0) {
    moveRight();
  } else {
    // Stop all servos
    for (int i = 0; i < 8; i++) {
      servos[i].write(90); // Neutral position
    }
  }
}

// Trot gait movement
void trotGait() {
  servos[0].write(45); // Front-left hip forward
  servos[1].write(135); // Rear-right hip forward
  delay(gait_speed);
  servos[2].write(135); // Front-right hip backward
  servos[3].write(45); // Rear-left hip backward
  delay(gait_speed);
}

// Move leftwards
void moveLeft() {
  servos[0].write(70); // Front-left hip
  servos[1].write(110); // Rear-right hip
  servos[2].write(110); // Front-right hip
  servos[3].write(70); // Rear-left hip
  delay(gait_speed);
}

// Move rightwards
void moveRight() {
  servos[0].write(110); // Front-left hip
  servos[1].write(70); // Rear-right hip
  servos[2].write(70); // Front-right hip
  servos[3].write(110); // Rear-left hip
  delay(gait_speed);
}

// Speed adjustment (placeholder for user speed control)
void setSpeed(int speed) {
  gait_speed = speed;
}

// Setup function
void setup() {
  set_microros_wifi_transports(wifi_ssid, wifi_password, wifi_ip, wifi_port);
  Serial.begin(115200);

  // Attach servos
  for (int i = 0; i < 4; i++) {
    servos[i].attach(servo_hip_pins[i]);
    servos[i + 4].attach(servo_knee_pins[i]);
  }

  // Initialize ROS node and subscription
  allocator = rcl_get_default_allocator();
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
  RCCHECK(rclc_node_init_default(&node, "pet_robot_node", "", &support));
  RCCHECK(rclc_subscription_init_default(&subscriber_cmd_vel, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist), "/cmd_vel"));

  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_subscription(&executor, &subscriber_cmd_vel, &cmd_vel_msg, &userControlCallback, ON_NEW_DATA));
}

// Main loop
void loop() {
  RCCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}

