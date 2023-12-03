# bag_to_traj 

#### introduce
save nav_msgs/Odometry or nav_msgs/Path or geometry_msgs/PoseStamped message of .bag file  to TUM/KITTI format.

#### Software architecture
Description Using ROS system and C++language, refer to CMakeLists.txt for configuration, usually only ROS and cmake need to be installed.

#### Installation and Compilation
Download this source code into the src folder of your catkin worksapce:
```
cd catkin_ws/src
git clone https://github.com/hsiaochao/bag_to_traj
```
Compile the project:
```
cd catkin_ws
source devel/setup.bash
catkin_make
```
#### How to use it
1. According to the prompts, modify the parameters in the launch file, including outfile_path, topic_type, topic_name, save_format, rosbag.
```
  <!-- topic_type is [path/odom/pose] which are selected based on nav_msgs/Path or nav_msgs/Odometry or geometry_msgs/PoseStamped -->
  <!-- topic_name is TOPIC_NAME of .bag file -->
  <!-- save_format is [TUM/KITTI] which is you want to save as-->
```
2.run it
```
roslaunch bag_to_traj bag_to_traj.launch 
```
Wait for the bag file to finish playing, and the data will be saved to a local text file.

#### Participate in contributions
```
Fork warehouse
Create a new Feature_ Xxx branch
Submit code
Create a new Pull Request
```
