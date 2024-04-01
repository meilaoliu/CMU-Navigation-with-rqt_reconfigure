#!/usr/bin/env bash

# 获取所有终端窗口的ID
terminal_windows=$(xdotool search --class "terminal")

# 遍历每个终端窗口ID
for window_id in $terminal_windows; do
    # 尝试将焦点切换到该终端，忽略错误
    xdotool windowfocus $window_id 2>/dev/null || continue
    # 等待一小段时间确保焦点切换成功
    sleep 0.1
    # 模拟按下 Ctrl+C
    xdotool key --clearmodifiers ctrl+c
    # 稍等一下再继续
    sleep 0.1
done

