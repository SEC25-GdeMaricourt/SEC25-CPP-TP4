#pragma once

class Constructible
{
protected:
    float _sConstructible;
    float _sConstruite;
    const bool _isConstructible;

public:
    /* Constructors */
    Constructible(float sConstruite = 0, bool isConstructible = false);

    /* Getters */
    float getSurfaceConstructible(void);
    float getSurfaceConstruite(void);
    bool isConstructible(void);

    /*
    Setters
    */
    void setSurfaceConstruite(float sConstruite);

    /*
    Setters
    To defined when inherited from
    */
    virtual void setSurfaceConstructible(void) = 0;
};