#ifndef DVO_CLASS_H
#define DVO_CLASS_H

#include "ros/ros.h"
#include "opencv2/opencv.hpp"
#include "cv_bridge/cv_bridge.h"
#include "image_alignment.h"
#include "sensor_msgs/Image.h"
#include "sensor_msgs/CameraInfo.h"
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_ros/transforms.h>
#include <pcl/common/transforms.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>
#include <Eigen/Geometry>

/**
 * @class DVO
 * @brief Class for Direct Visual Odometry
 */
class DVO {
    private:
        ros::NodeHandle nh;
        Eigen::Matrix4f accumulated_transform = Eigen::Matrix4f::Identity();
        cv::Mat img_prev, depth_prev;
        Eigen::Matrix3f K;
        ros::Publisher pub_pointcloud;
        tf::TransformBroadcaster br;

    public:
        DVO(ros::NodeHandle nh_input){
            nh = nh_input;
        }

        void makePointCloud( const cv::Mat& img_rgb, const cv::Mat& img_depth, pcl::PointCloud< pcl::PointXYZRGB >::Ptr& cloud);

        void callback(const sensor_msgs::ImageConstPtr& image_rgb, const sensor_msgs::ImageConstPtr& image_depth, const sensor_msgs::CameraInfoConstPtr& info);
};

#endif //DVO_CLASS_H
