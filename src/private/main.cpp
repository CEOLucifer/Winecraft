#include "App.h"
#include <exception>
#include "Debug/Debug.h"

using namespace std;

int main()
{
    try
    {
        App::LoadInstance();
        App::Instance()->Run();
    }
    catch (exception e)
    {
        Debug::LogError(e.what());
    }
    return 0;
}