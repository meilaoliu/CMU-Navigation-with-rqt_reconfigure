
gnome-terminal -t "base" -- bash -c "./driver.sh"

sleep 3s

gnome-terminal -t "cmu" -- bash -c "cd /home/lingao/cmu_car_ws/autonomous_exploration_development_environment; source devel/setup.bash; roslaunch vehicle_simulator system_real_robot.launch "

sleep 3s

#打开第二个终端运行far_planner路径规划算法
#gnome-terminal -t "far-planner" -- bash -c "cd /home/lingao/cmu_car_ws/far_planner_ws; source devel/setup.bash; roslaunch far_planner far_planner.launch; exec bash"

sleep 3s

gnome-terminal -t "rqt_reconfigure" -- bash -c " rosrun rqt_reconfigure rqt_reconfigure"
