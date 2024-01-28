#include "Constructible.hpp"

/*
============================
Constructors
============================
*/
Constructible::Constructible(float sConstruite, float sConstructible, bool isConstructible) : _isConstructible(isConstructible)
{
    _sConstruite = sConstruite;
    _sConstructible = sConstructible;
}

/*
============================
Getters
============================
*/
float Constructible::getSurfaceConstructible(void)
{
    return this->_sConstructible;
}

float Constructible::getSurfaceConstruite(void)
{
    return this->_sConstruite;
}