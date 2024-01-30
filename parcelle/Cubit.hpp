#pragma once

#include <string>

using namespace std;

class Cubit
{
public:
    virtual void load(string data) = 0;
    virtual string save(void) const = 0;
};
