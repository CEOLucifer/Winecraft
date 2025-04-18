#pragma once

#include "Singleton.h"

class App : public Singleton<App>
{
public:
    void Run();

    /// @brief 处理用户初始化逻辑 
    /// 
    void StartUser();
};
