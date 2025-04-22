#pragma once

#include "Std/Basic.h"

class KeySignal
{
private:
    i32 key;
    i32 action;

public:
    KeySignal(i32 _key, i32 _action) : key(_key), action(_action) {}

    i32 GetKey() { return key; }

    i32 GetAction() { return action; }
};