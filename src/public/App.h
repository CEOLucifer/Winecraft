#pragma once

#include "Singleton.h"

class App : public Singleton<App>
{
public:
    void Run();
};