# bag_to_traj 

#### 介绍
把bag文件中nav_msgs/Odometry、nav_msgs/Path、geometry_msgs/PoseStamped类型的话题数据，按照TUM/KITTI 格式保存到本地文本文件中。
save nav_msgs/Odometry or nav_msgs/Path or geometry_msgs/PoseStamped message to TUM/KITTI format.

#### 软件架构
软件架构说明
使用ROS系统和C++语言，配置参考CMakeLists.txt，通常只需要安装ROS和cmake。

#### 安装教程

下载源码到工作空间的src文件夹：
```
cd catkin_ws/src
git clone https://gitee.com/hsiaochao/bag_to_traj
```
编译项目：
```
cd catkin_ws
source devel/setup.bash
catkin_make
```
#### 使用说明

1. 根据提示修改launch文件中的参数，包括outfile_path输出文件名、topic_type话题数据类型、topic_name话题名、save_format保存格式、rosbag播放bag文件名
```
  <!-- topic_type is [path/odom/pose] which are selected based on nav_msgs/Path or nav_msgs/Odometry or geometry_msgs/PoseStamped -->
  <!-- topic_name is TOPIC_NAME of .bag file -->
  <!-- save_format is [TUM/KITTI] which is you want to save as-->
```
2.运行程序
```
roslaunch bag_to_traj bag_to_traj.launch 
```
等待bag文件播放完，其中数据即保存至本地文本文件。

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
