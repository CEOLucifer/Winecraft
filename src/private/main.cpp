#include "App.h"

using namespace std;

int main()
{
    App::LoadInstance();
    App::Instance()->Run();
    return 0;
}