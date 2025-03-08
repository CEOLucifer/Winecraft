#include "../include/App.h"
//#include "Test/BerlinTest.h"

using namespace std;

int main()
{
    App::LoadInstance();
    App::Instance()->Run();

//    BerlinTest t;
//    t.Run();
    return 0;
}