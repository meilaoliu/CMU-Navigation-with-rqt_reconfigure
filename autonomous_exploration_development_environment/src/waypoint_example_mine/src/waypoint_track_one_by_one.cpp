// track one by one
#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <tf/transform_listener.h>
#include <rs_yolo/Info.h> 
#include <cstdlib> // 包含abs函数
#include <cmath> // 包含fabs函数

tf::TransformListener* tfListenerPtr;
geometry_msgs::PointStamped lastPublishedWaypoint;//上一次发布的导航点
bool isWaypointPublished = false ; // 标记是否发布导航点

void targetPositionCallback(const rs_yolo::Info::ConstPtr& msg, ros::Publisher& waypointPub) {

    double waypoint_circle = 5;
    double circle = 0.8; //target point expansion radius
    double approachThreshold = 0.5; // 接近阈值

    double waypoint_x=msg->x-circle; //target_point_x
    double waypoint_y=msg->y;
    double waypoint_z=msg->z;

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

      // 检查是否已接近上一个发布的导航点
    if (isWaypointPublished) {
        double distToLastWaypoint = sqrt(pow(vehicleX - lastPublishedWaypoint.point.x, 2) + pow(vehicleY - lastPublishedWaypoint.point.y, 2));
        if (distToLastWaypoint > approachThreshold) {
            return; // 如果还没接近上一个点，不发布新的导航点
        }
    }


    // 创建并发布航点
    geometry_msgs::PointStamped waypoint;
    waypoint.header.frame_id = "map";
    waypoint.header.stamp = ros::Time::now();
    waypoint.point.x = waypoint_x;
    waypoint.point.y = waypoint_y;
    waypoint.point.z = waypoint_z;

    waypointPub.publish(waypoint);

    lastPublishedWaypoint = waypoint;
    isWaypointPublished = true;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "target_waypoint_publisher");
    ros::NodeHandle nh;

    tf::TransformListener tfListener;
    tfListenerPtr = &tfListener;

    ros::Publisher waypointPub = nh.advertise<geometry_msgs::PointStamped>("/way_point", 5);
    ros::Subscriber targetSub = nh.subscribe<rs_yolo::Info>("/detect_result_out", 5, boost::bind(targetPositionCallback, _1, boost::ref(waypointPub)));

    ros::spin();

    return 0;
}
