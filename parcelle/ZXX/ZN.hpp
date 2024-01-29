#pragma once

#include <sstream>
#include <string>
#include <iostream>
#include <regex>

#include "../Parcelle.hpp"
#include "../Constructible.hpp"

// Type/Number/Owner/Points_list
const std::regex re_zn("(ZN) (\\d+) ([\\w']+) *\n(\\[[ \\d;\\-\\]\\[]+\\])\n?", std::regex::optimize);

using namespace std;

template <typename T>
class ZN;
template <typename T>
ostream &operator<<(ostream &os, ZN<T> const &obj);

template <typename T>
class ZN : public Parcelle<T>, public Constructible
{
private:
    string serialize(void) const;
    void deserialize(string data);

public:
    /* Constructors */
    ZN(int num, string prop, Polygone<T> shape);
    ZN(const ZN<T> &other);
    ZN(string data);

    /* Setter (override) */
    float setSurfaceConstructible(void) const override;
    float setSurfaceConstruite(void) const override;

    /* Methods */
    string toString(void) const;

    string save(void) const override;
    void load(string data) override;

    /* Friends */
    friend ostream &operator<< <T>(ostream &os, ZN<T> const &obj);
};

/*
============================
Constructors
============================
*/
template <typename T>
ZN<T>::ZN(int num, string prop, Polygone<T> shape) : Parcelle<T>(num, prop, shape), Constructible() {}

template <typename T>
ZN<T>::ZN(const ZN<T> &other) : Parcelle<T>(other), Constructible() {}

template <typename T>
ZN<T>::ZN(string data) : Parcelle<T>(), Constructible()
{
    load(data);
}
/*
============================
Setters (override)
============================
*/
template <typename T>
float ZN<T>::setSurfaceConstructible(void) const
{
    throw runtime_error("Une ZN n'est pas constructible.");
}

template <typename T>
float ZN<T>::setSurfaceConstruite(void) const
{
    throw runtime_error("Une ZN n'a pas de surface construite.");
}

/*
============================
Methods
============================
*/
template <typename T>
void ZN<T>::load(string data)
{
    deserialize(data);
}

template <typename T>
string ZN<T>::save(void) const
{
    return serialize();
}

template <typename T>
void ZN<T>::deserialize(string data)
{
    if (std::regex_match(data, re_zn))
    {
        std::smatch m;
        std::regex_search(data, m, re_zn);
        std::cout << m[1] << " " << m[2] << " " << m[3] << " " << m[4] << std::endl;

        this->setNumero(stoi(m[2].str().c_str()));
        this->setProprietaire(m[3].str());
        Polygone<T> newPoly(m[4].str());
        this->setForme(newPoly);
    }
}

template <typename T>
string ZN<T>::serialize(void) const
{
    stringstream ret;
    ret << "ZN "
        << this->getNumero() << " "
        << this->getProprietaire() << "\n"
        << this->getForme();
    return ret.str();
}

template <typename T>
string ZN<T>::toString(void) const
{
    stringstream ret;
    ret << Parcelle<T>::toString()
        << "   Type                 : ZN";
    return ret.str();
}

/*
============================
Friends (operator overloarding)
Print the point properties
============================
*/
template <typename T>
ostream &operator<<(ostream &os, ZN<T> const &obj)
{
    os << obj.toString();
    return os;
}