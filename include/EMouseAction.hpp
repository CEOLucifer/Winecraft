#pragma once

/// @brief 鼠标按键的状态，表示是刚按下还是刚松开
enum class EMouseAction
{
    // 刚松开
    Up,
    // 刚按下
    Down,
    None,
};