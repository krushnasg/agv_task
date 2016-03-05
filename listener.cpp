#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "geometry_msgs/Point.h"
#include <cv_bridge/cv_bridge.h>
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
Mat image=imread("/home/krushna/catkin_ws/src/agv_task/src/pic3.png",CV_LOAD_IMAGE_COLOR);
void chatterCallback(const geometry_msgs::Point::ConstPtr& pnt)
{
image.at<Vec3b>(pnt->x,pnt->y)[0]=220;
imwrite( "/home/krushna/catkin_ws/src/agv_task/src/pic3.png");

  if(pnt->x==28.0 && pnt->y==32.0)
  {
    namedWindow("path",CV_WINDOW_NORMAL);
    imshow("path", img);
    waitKey(0);
  
}

int main(int argc, char **argv)
{
 /*  ros::init(argc, argv, "listener");

  
  ros::NodeHandle n;

 
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);


  ros::spin();

  return 0;
*/
Mat img;}
