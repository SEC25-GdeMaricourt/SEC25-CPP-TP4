#pragma once

#include <string>

using namespace std;

class Cubit
{
protected:
    virtual void load(string data) = 0;
    virtual string save(void) const = 0;
};
