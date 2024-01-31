#pragma once

#include <sstream>
#include <string>
#include <iostream>
#include <regex>

#include "../Parcelle.hpp"
#include "../Constructible.hpp"

const float MAX_ZA_PCONSTRUCTIBLE = 10;
const float MAX_ZA_SIZE = 200;

// Type/Number/Owner/CropType/Points_list
const std::regex re_za("(ZA) (\\d+) ([\\w']+) ([\\wéï']+) *\n(\\[[ \\d;\\-\\]\\[]+\\])\n?", std::regex::optimize);

using namespace std;

template <typename T>
class ZA;
template <typename T>
ostream &operator<<(ostream &os, ZA<T> const &obj);

template <typename T>
class ZA : public Parcelle<T>, public Constructible
{
private:
    string serialize(void) const;
    void deserialize(string data);

    string _culture = "";

public:
    /* Constructors */
    ZA(int num, string prop, Polygone<T> shape, string culture, float sConstruite);
    ZA(const ZA<T> &other);
    ZA(string data);

    /* Setter (override) */
    void setSurfaceConstructible(void) override;

    /* Setters */
    void setSurfaceConstruite(float sConstruite);
    void setCulture(string culture);

    /* Getters */
    string getCulture() const;

    /* Methods */
    string toString(void) const;

    string save(void) const override;
    void load(string data) override;

    /* Friends */
    friend ostream &operator<< <T>(ostream &os, ZA<T> const &obj);
};

/*
============================
Constructors
============================
*/
template <typename T>
ZA<T>::ZA(int num, string prop, Polygone<T> shape, string culture, float sConstruite) : Parcelle<T>(num, prop, shape), Constructible(sConstruite, true)
{
    _culture = culture;
    setSurfaceConstructible();
}

template <typename T>
ZA<T>::ZA(const ZA<T> &other) : Parcelle<T>(other), Constructible(other._sConstruite, true)
{
    _culture = other.getCulture();
    setSurfaceConstructible();
}

template <typename T>
ZA<T>::ZA(string data) : Parcelle<T>(), Constructible(0, true)
{
    load(data);
    setSurfaceConstructible();
}
/*
============================
Setters (override)
============================
*/
template <typename T>
void ZA<T>::setSurfaceConstructible(void)
{
    float pConstruite = ((this->getSurfaceConstruite() * 100) / this->getSurface());
    // Size is already out of bound
    // We might want to raise an error (not obvious though)
    if ((pConstruite > MAX_ZA_PCONSTRUCTIBLE) || (this->getSurfaceConstruite() > MAX_ZA_SIZE))
    {
        _sConstructible = 0;
    }
    else
    {
        _sConstructible = (((this->getSurface()) * MAX_ZA_PCONSTRUCTIBLE / 100) - this->getSurfaceConstruite());
    }
}

/*
============================
Setters
============================
*/
template <typename T>
void ZA<T>::setSurfaceConstruite(float sConstruite)
{
    Constructible::setSurfaceConstruite(sConstruite);
    setSurfaceConstructible();
}

template <typename T>
void ZA<T>::setCulture(string culture)
{
    _culture = culture;
}

/*
============================
Getters
============================
*/
template <typename T>
string ZA<T>::getCulture() const
{
    return _culture;
}

/*
============================
Methods
============================
*/
template <typename T>
void ZA<T>::load(string data)
{
    deserialize(data);
}

template <typename T>
string ZA<T>::save(void) const
{
    return serialize();
}

template <typename T>
void ZA<T>::deserialize(string data)
{
    if (std::regex_match(data, re_za))
    {
        std::smatch m;
        std::regex_search(data, m, re_za);
        // std::cout << m[0] << endl;
        // std::cout << m[1] << " " << m[2] << " " << m[3] << " " << m[4] << " " << m[5] << std::endl;

        this->setNumero(stoi(m[2].str().c_str()));
        this->setProprietaire(m[3].str());
        this->setCulture(m[4].str());
        Polygone<T> newPoly(m[5].str());
        this->setForme(newPoly);
    }
}

template <typename T>
string ZA<T>::serialize(void) const
{
    stringstream ret;
    ret << "ZA "
        << this->getNumero() << " "
        << this->getProprietaire() << " "
        << this->getCulture() << "\n"
        << this->getForme().toString();
    return ret.str();
}

template <typename T>
string ZA<T>::toString(void) const
{
    stringstream ret;
    ret << Parcelle<T>::toString()
        << "   Type                 : ZA" << endl
        << "   Culture              : " << this->getCulture() << endl
        << "   sConstruite          : " << this->_sConstruite << endl
        // Question prof
        // Impossible d'appeler la méthode Constructible::getSurfaceConstruite()
        // Il faut récupérer la variable directement... sinon erreur de compilation
        // << "   sConstruite          : " << Constructible::getSurfaceConstruite() << endl
        << "   sConstructible       : " << this->_sConstructible;
    return ret.str();
}

/*
============================
Friends (operator overloarding)
Print the point properties
============================
*/
template <typename T>
ostream &operator<<(ostream &os, ZA<T> const &obj)
{
    os << obj.toString();
    return os;
}