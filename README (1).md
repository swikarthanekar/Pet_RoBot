# Pet_Robot

## Introduction

This project aims to simulate a quadruped robot in Gazebo and control it with keyboard/Joypad commands using ROS2 Humble.

<img src="images/bruno_gazebo.png" width="533"> <img src="images/bruno_rviz.png" width="533">

## Features

- [x] URDF model of a quadruped robot
- [x] ROS2 package for simulation and teleoperation
- [x] Teleoperation node for Virtual Joypad Control
- [ ] Teleoperation node for keyboard control
- [x] Launch files for Gazebo simulation and teleoperation :tada:


## Dependencies

- OS: Ubuntu Linux 22.04 Jammy Jellyfish
- ROS Version: ROS2 Humble
- Python3

## Instruction to run the simulation

Follow the steps below to setup the repository:

```bash
# source ROS2 and Build the workspace
source /opt/ros/galactic/setup.bash
# Create a workspace
mkdir -p ~/petbot_ws/src
cd petbot_ws/src
# Clone the repository in the workspace
git clone https://github.com/swikarthanekar/Pet_RoBot.git
# Install the dependencies
cd ~/petbot_ws
rosdep install -i --from-path src --rosdistro humble -y
# build the workspace
colcon build --symlink-install
```
To run the simulation open the terminal and follow the below steps:

```bash
# source ROS2
source /opt/ros/galactic/setup.bash
# Source the workspace
cd ~/petbot_ws
source install/setup.bash
# Run the launch file
ros2 launch petbot debug.launch.py
```
Open another terminal to launch the virtual Joypad Node for teleoperation:

```bash
# source ROS2
source /opt/ros/galactic/setup.bash
# Launch the Joypad
cd ~/petbot_ws/src/UI
python3 controller.py
```
