#include "../include/TimeSystem.h"

std::chrono::system_clock::time_point Time::initStack = {};
std::chrono::system_clock::time_point Time::lastStack = {};
float Time::deltaTime = 0;
float Time::runTime = 0;