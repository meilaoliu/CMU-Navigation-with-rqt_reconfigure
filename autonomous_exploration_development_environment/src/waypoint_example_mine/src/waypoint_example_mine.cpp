// always_track

#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <tf/transform_listener.h>
#include <rs_yolo/Info.h> 
#include <cstdlib> // 包含abs函数
#include <cmath> // 包含fabs函数
#include <geometry_msgs/Pose2D.h>

tf::TransformListener* tfListenerPtr;

void targetPositionCallback(const rs_yolo::Info::ConstPtr& msg, ros::Publisher& waypointPub) {

    double waypoint_circle = 5;
    double circle = 0.8; //target point expansion radius

    
    // double waypoint_x=msg->x-circle; //target_point_x
    // double waypoint_y=msg->y;
    double waypoint_z=msg->z;


    double forward_offset = 0.8; // 目标车辆前方的偏移量
    double target_x = msg->x; // 目标车辆位置
    double target_y = msg->y;


    if (msg->classification != "blue_car_v1" && msg->classification != "blue_car_v2") {
        return; // 如果分类不是 "blue_car_v2"，则不执行任何操作
    }

    // 尝试从/vehicle坐标系转换到/map坐标系
    tf::StampedTransform transform;
    try {
        tfListenerPtr->waitForTransform("/map", "/vehicle", ros::Time(0), ros::Duration(3.0));
        tfListenerPtr->lookupTransform("/map", "/vehicle", ros::Time(0), transform);
    } catch (tf::TransformException &ex) {
        ROS_ERROR("%s", ex.what());
        ros::Duration(1.0).sleep(); // 延迟，等待TF变得可用
        return;
    }
    
    // 获取车辆在/map坐标系下的位置和姿态
    double vehicleX = transform.getOrigin().x();
    double vehicleY = transform.getOrigin().y();
    double vehicleZ = transform.getOrigin().z();

    if (fabs(msg->x-vehicleX)>waypoint_circle or fabs(msg->y-vehicleY)>waypoint_circle ){
        return ; //Prevent waypoint from being too far away
    }

    // 计算目标车辆相对于当前车辆的方位角
    double angle = atan2(target_y - vehicleY, target_x - vehicleX);

    // 计算 waypoint 的位置
    double waypoint_x = target_x - forward_offset * cos(angle);
    double waypoint_y = target_y - forward_offset * sin(angle);

    // 创建并发布航点
    //geometry_msgs::PointStamped waypoint;
    geometry_msgs::Pose2D waypoint;
    // waypoint.header.frame_id = "map";
    // waypoint.header.stamp = ros::Time::now();
    // waypoint.point.x = waypoint_x;
    // waypoint.point.y = waypoint_y;
    waypoint.x = waypoint_x;
    waypoint.y = waypoint_y;
    waypoint.theta = angle;

    waypointPub.publish(waypoint);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "target_waypoint_publisher");
    ros::NodeHandle nh;

    tf::TransformListener tfListener;
    tfListenerPtr = &tfListener;
    
    ros::Publisher waypointPub = nh.advertise<geometry_msgs::Pose2D>("/behaviortree/Nav_optimization", 5);
    //ros::Publisher waypointPub = nh.advertise<geometry_msgs::PointStamped>("/way_point", 5);
    ros::Subscriber targetSub = nh.subscribe<rs_yolo::Info>("/detect_result_out", 5, boost::bind(targetPositionCallback, _1, boost::ref(waypointPub)));

    ros::spin();

    return 0;
}
