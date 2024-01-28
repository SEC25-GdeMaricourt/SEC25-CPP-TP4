#pragma once

class Constructible
{
protected:
    float _sConstructible;
    float _sConstruite;
    const bool _isConstructible;

public:
    /* Constructors */
    Constructible(float sConstruite = 0, float sConstructible = 0, bool isConstructible = false);

    /* Getters */
    float getSurfaceConstructible(void);
    float getSurfaceConstruite(void);

    /*
    Setters
    To defined when inherited from
    */
    virtual float setSurfaceConstructible(void) const = 0;
    virtual float setSurfaceConstruite(void) const = 0;
};