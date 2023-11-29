import os
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.conditions import IfCondition

def generate_launch_description():
    bag_record = LaunchConfiguration('bag_record')
    simple_walker_package_dir = get_package_share_directory('simple_walker')
    gazebo_world_path = simple_walker_package_dir + '/worlds/simple_walker_world.world'

    return LaunchDescription([
        DeclareLaunchArgument(
            'bag_record',
            default_value= 'False'
        ),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([
                os.path.join(get_package_share_directory(
                    'turtlebot3_gazebo'), 'launch'), '/turtlebot3_world.launch.py'
            ])
        ),
        # Launch Gazebo with the specified world file
        # Node(
        #     package='gazebo_ros',
        #     executable='gazebo',
        #     name='gazebo',
        #     output='screen',
        #     arguments=['--verbose', '-s', 'libgazebo_ros_init.so', gazebo_world_path]
        # ),
        # Launch the simple_walker_node
        Node(
            package='simple_walker',
            executable='simple_walker',
            output='screen',
        ),
        ExecuteProcess(
            condition=IfCondition(bag_record),
            cmd=['ros2', 'bag', 'record', '-a', '-x /camera.+'],
            shell=True
        )
    ])
