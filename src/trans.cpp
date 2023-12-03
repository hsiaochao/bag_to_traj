#include "trans.h"
#include <iostream>
#include <fstream>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
using namespace std;

ros::Subscriber odom_sub, path_sub,pose_sub;
string format;
string topic_type;
string topic_name;
std::string filename;

void odomCallback(const nav_msgs::OdometryConstPtr& odom_msg)
{
    //cout<<"writing to file"<<endl;
    if(format=="TUM")
    {
        ofstream outfile(filename,ios::app);
        
        outfile << to_string(odom_msg->header.stamp.toSec()) <<" "
                << odom_msg->pose.pose.position.x <<" "
                << odom_msg->pose.pose.position.y <<" "
                << odom_msg->pose.pose.position.z <<" "
                << odom_msg->pose.pose.orientation.x <<" "
                << odom_msg->pose.pose.orientation.y <<" "
                << odom_msg->pose.pose.orientation.z <<" "
                << odom_msg->pose.pose.orientation.w <<endl;
        cout<<"writing to TUM file, timestamp is "<<to_string(odom_msg->header.stamp.toSec())<<endl;
        outfile.close();
    }
    else if(format=="KITTI")
    {
        ofstream outfile(filename,ios::app);
      
        Eigen::Matrix3d R = Eigen::Quaterniond(odom_msg->pose.pose.orientation.w,odom_msg->pose.pose.orientation.x,
        odom_msg->pose.pose.orientation.y,odom_msg->pose.pose.orientation.z).matrix();
        outfile << R(0,0)<<" "<<R(0,1)<<" "<<R(0,2)<<" "<<odom_msg->pose.pose.position.x<<" "
                << R(1,0)<<" "<<R(1,1)<<" "<<R(1,2)<<" "<<odom_msg->pose.pose.position.y<<" "
                << R(2,0)<<" "<<R(2,1)<<" "<<R(2,2)<<" "<<odom_msg->pose.pose.position.z<<endl;

        cout<<"writing to KITTI file, timestamp is "<<to_string(odom_msg->header.stamp.toSec())<<endl;
        outfile.close();
    }
    
}

void pathCallback(const nav_msgs::PathConstPtr& path_msg)
{
    if(format=="TUM")
    {
        ofstream outfile(filename);
        // outfile.open(filename,ios::trunc);
        for(unsigned int i=0;i<path_msg->poses.size();++i)
        {
            outfile << to_string(path_msg->poses[i].header.stamp.toSec()) <<" "
                    << path_msg->poses[i].pose.position.x <<" "
                    << path_msg->poses[i].pose.position.y <<" "
                    << path_msg->poses[i].pose.position.z <<" "
                    << path_msg->poses[i].pose.orientation.x <<" "
                    << path_msg->poses[i].pose.orientation.y <<" "
                    << path_msg->poses[i].pose.orientation.z <<" "
                    << path_msg->poses[i].pose.orientation.w <<endl;
        }
        outfile.close();
        cout<<"writing to TUM file, timestamp is "<<to_string(path_msg->header.stamp.toSec())<<endl;
    }
    else if(format=="KITTI")
    {
        ofstream outfile(filename);
        for(unsigned int i=0;i<path_msg->poses.size();++i)
        {
            Eigen::Matrix3d R = Eigen::Quaterniond(path_msg->poses[i].pose.orientation.w,path_msg->poses[i].pose.orientation.x,
            path_msg->poses[i].pose.orientation.y,path_msg->poses[i].pose.orientation.z).matrix();
            outfile << R(0,0)<<" "<<R(0,1)<<" "<<R(0,2)<<" "<<path_msg->poses[i].pose.position.x<<" "
                    << R(1,0)<<" "<<R(1,1)<<" "<<R(1,2)<<" "<<path_msg->poses[i].pose.position.y<<" "
                    << R(2,0)<<" "<<R(2,1)<<" "<<R(2,2)<<" "<<path_msg->poses[i].pose.position.z<<endl;
        }
        outfile.close();
        cout<<"writing to KITTI file, timestamp is "<<to_string(path_msg->header.stamp.toSec())<<endl;
    }
    
}

void poseCallback(const geometry_msgs::PoseStampedConstPtr& pose_msg) 
{
    if(format=="TUM")
    {
      ofstream outfile(filename, ios::app);
      outfile << to_string(pose_msg->header.stamp.toSec()) << " "
          << setprecision(9) << pose_msg->pose.position.x << " "
          << setprecision(9) << pose_msg->pose.position.y << " "
          << setprecision(9) << pose_msg->pose.position.z << " "
          << setprecision(9) << pose_msg->pose.orientation.x << " "
          << setprecision(9) << pose_msg->pose.orientation.y << " "
          << setprecision(9) << pose_msg->pose.orientation.z << " "
          << setprecision(9) << pose_msg->pose.orientation.w << endl;
      cout << "Writing to TUM file, timestamp is " << to_string(pose_msg->header.stamp.toSec()) << endl;
      outfile.close();
    }
    else if(format=="KITTI")
    {
  ofstream outfile(filename, ios::app);

  Eigen::Matrix3d R = Eigen::Quaterniond(pose_msg->pose.orientation.w,
                                         pose_msg->pose.orientation.x,
                                         pose_msg->pose.orientation.y,
                                         pose_msg->pose.orientation.z).matrix();

  outfile << setprecision(9) << R(0, 0) << " " << setprecision(9) << R(0, 1) << " " << setprecision(9) << R(0, 2) << " " << setprecision(9) << pose_msg->pose.position.x << " "
          << setprecision(9) << R(1, 0) << " " << setprecision(9) << R(1, 1) << " " << setprecision(9) << R(1, 2) << " " << setprecision(9) << pose_msg->pose.position.y << " "
          << setprecision(9) << R(2, 0) << " " << setprecision(9) << R(2, 1) << " " << setprecision(9) << R(2, 2) << " " << setprecision(9) << pose_msg->pose.position.z << endl;

  cout << "Writing to KITTI file, timestamp is " << to_string(pose_msg->header.stamp.toSec()) << endl;
  outfile.close();
    }
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"trans");
    ros::NodeHandle nh;
/*
    cout<<"<<<<<<<<<<<<<<<<"<<"Please follow format: rosrun bag_to_traj bag_to_traj [path/odom/pose] [TOPIC_NAME] [TUM/KITTI]"<<">>>>>>>>>>>>>>>>"<<endl;
    topic_type = argv[1];
    topic_name = argv[2];
    format = argv[3];
    cout<<argv[1]<<endl;
*/

  if (!nh.getParam("outfile_path", filename)){
    ROS_ERROR("Failed to retrieve 'outfile_path' parameter");
    return 1;
  }
    nh.getParam("topic_type", topic_type);
    nh.getParam("topic_name", topic_name);
    nh.getParam("save_format", format);

    if(topic_type=="path")
    {
        path_sub = nh.subscribe(topic_name, 1000, pathCallback);
    }
    else if(topic_type=="odom")
    {
        odom_sub = nh.subscribe(topic_name, 1000, odomCallback);
    }
    else if(topic_type=="pose")
    {
        pose_sub = nh.subscribe(topic_name, 1000, poseCallback);
    }
    else{
        cout<<"please input right format"<<endl;
        ros::shutdown();
    }
    
    
    ros::Rate loop_rate(20);
    loop_rate.sleep();
    ros::spin();
    
    return 0;
}
