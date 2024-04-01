
gnome-terminal -t "base" -- bash -c "./cmu_launch.sh"

sleep 10s

gnome-terminal -t "detect" -- bash -c " source workspace/perception_ws/devel/setup.bash; roslaunch behavior_tree launchtest.launch "

sleep 2s

gnome-terminal -t "detect" -- bash -c " ./tare_launch.sh  "

sleep 5s

gnome-terminal -t "detect" -- bash -c " ./tracking_navigation.sh "

sleep 3s

gnome-terminal --wait -t "yolo" -- bash -c "source workspace/perception_ws/devel/setup.bash;cd workspace/perception_ws/src/rs_yolov5-lite_ws/src/rs_yolo/scripts;conda activate torch;python rstest_aim.py;"

sleep 6s

gnome-terminal -t "detect" -- bash -c "   source workspace/perception_ws/devel/setup.bash;roslaunch py_trees_ros tutorial_two.launch  "


sleep 6s

gnome-terminal -t "detect" -- bash -c "  rostopic pub /behaviortree/ground_station behavior_tree/ground_message "last_time: 0.0
isCombatStart: true 
win: false
other:
- name: ''
  pose:
    position:
      x: 0.0
      y: 0.0
      z: 0.0
    orientation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 0.0"

  "







