
# CMU Navigation with rqt_reconfigure

在CMU导航框架的基础上增加了rqt动态调参功能,同时将TwistStamped消息类型改为Twist消息类型，因为我所用的底盘的速度消息cmd_vel都是Twist类型的（大部分底盘也是），而源码中是TwistStamped类型的，比Twist多一个时间戳。

## 功能介绍

在运行完导航框架后，只需运行以下命令即可弹出可视化调参界面：

```
rosrun rqt_reconfigure rqt_reconfigure
```

![cmu-rqt](https://github.com/meilaoliu/CMU-Navigation-with-rqt_reconfigure/assets/77963185/f65f9210-8349-4bad-b059-3f281bb26a97)

## 参数适配

目前只适配了`localPlanner`、`pathFollower`、`terrianAnalysis`、`farplanner`中的参数。想要增加参数，只要仿照现有的代码格式在`cfg`与`src`下的代码中增加相应的参数语句即可。

## 注意事项

此外，我发现对于目前CMU团队开源的源码中的参数，有的虽然名字一样但功能却不一样。例如，在`localPlanner`中`maxSpeed`这个参数代表手柄控制车体的最大速度，但是在`pathFollower`中则代表局部路径规划所规划的最大速度。因此，想要修改导航的最大速度需要调整`pathFollower`中`maxSpeed`的参数。
