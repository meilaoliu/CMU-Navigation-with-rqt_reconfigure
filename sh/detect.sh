



gnome-terminal -t "behavior_tree" -- bash -c " source workspace/perception_ws/devel/setup.bash; roslaunch behavior_tree launchtest.launch "

sleep 6s
 
#gnome-terminal --wait -t "yolo" -- bash -c "source workspace/perception_ws/devel/setup.bash;cd workspace/perception_ws/src/rs_yolov5-lite_ws/src/rs_yolo/scripts;conda activate torch;python rstest_aim.py;"

#gnome-terminal -t "yolo" -- bash -c "source ~/.bashrc;source workspace/perception_ws/devel/setup.bash; cd workspace/perception_ws/src/rs_yolov5-lite_ws/src/rs_yolo/scripts; conda activate torch; python rstest_aim.py > ~/yolo_output.txt 2>&1"

#sleep 5s

#gnome-terminal -t "rostopic" -- bash -c " cd ~/workspace/perception_ws; source devel/setup.bash; rostopic echo /detect_result_out"


