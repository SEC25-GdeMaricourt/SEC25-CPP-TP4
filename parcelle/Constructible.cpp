#include "Constructible.hpp"

/*
============================
Constructors
============================
*/
Constructible::Constructible(float sConstruite, bool isConstructible) : _isConstructible(isConstructible)
{
    _sConstruite = sConstruite;
}

/*
============================
Getters
============================
*/
float Constructible::getSurfaceConstructible(void)
{
    return _sConstructible;
}

float Constructible::getSurfaceConstruite(void)
{
    return _sConstruite;
}

bool Constructible::isConstructible(void)
{
    return _isConstructible;
}

/*
============================
Setters
============================
*/
void Constructible::setSurfaceConstruite(float sConstruite)
{
    _sConstruite = sConstruite;
}