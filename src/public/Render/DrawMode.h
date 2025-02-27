#pragma once

/// @brief 网格的绘制模式。表示网格顶点数据的格式。
/// 
enum DrawMode
{
    /// @brief DrawArray方式
    Normal,
    /// @brief DrawElements方式（索引）
    Indices,
};