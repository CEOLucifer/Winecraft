#include "App.h"

int main()
{
    App::LoadInstance();
    App::Instance()->Run();
    return 0;
}