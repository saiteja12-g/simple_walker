# Walker algorithm for Turtlebot3 using ROS2

Beginner tutorial for Gazebo 

## Dependencies

- rclcpp
- sensor_msgs
- geometry_msgs
- OS: Ubuntu Linux 22.04
- ROS Version: ROS2 Humble Hawksbill

## Build Instructions

Navigate to the src folder of the ROS2 workspace

```sh
cd ~/<your workspace>/src
```

Clone the GitHub repository

```sh
git clone https://github.com/saiteja12-g/simple_walker.git
```

Now to build the package go to the root of the ROS2 workspace

```sh
cd ..
# check the dependencies
rosdep install -i --from-path src --rosdistro humble -y
# Building the package
colcon build --packages-select simple_walker
```

## Run Instructions
Sourcing the package
```
source install/setup.bash
```

### Using the launch file

To run the launch file and start the ros bag file recording,

```sh
cd src/simple_walker/bag\ files
```
```sh
ros2 launch simple_walker walker_launch.py bag_record:=True
```

## References

[1] <http://docs.ros.org/en/humble/index.html>