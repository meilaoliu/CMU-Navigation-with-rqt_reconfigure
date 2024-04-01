

gnome-terminal -t "lingao_base" -- bash -c "roscore "


sleep 2

# 打开第一个终端启动底盘
gnome-terminal -t "lingao_base" -- bash -c "roslaunch lingao_startup startup.launch "


# 等待2秒
# sleep 5

# 打开第三个终端运行相机驱动节点
# gnome-terminal -t "camera" -- bash -c " roslaunch lingao_visual lingao_depthcamera.launch"


# 打开第四个终端显示图像
# gnome-terminal -t "camera_show" -- bash -c "rosrun rqt_image_view rqt_image_view"


sleep 2

# fastlio
gnome-terminal -t "fastlio" -- bash -c "roslaunch dx_fast_lio mapping_mid360.launch "


# sleep 2

 #打开第二个终端运行键盘控制节点
 gnome-terminal -t "lingao_control" -- bash -c " rosrun teleop_twist_keyboard teleop_twist_keyboard.py"
 

 
# 打开第五个终端继续输入指令
# gnome-terminal -t "lingao_control" -- bash -c " rosnode kill /localization /move_base /nvilidar_rear_node /lingao_robot_manager /lingao_global_localization"
