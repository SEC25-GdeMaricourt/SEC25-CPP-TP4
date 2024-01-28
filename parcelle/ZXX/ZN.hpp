#pragma once

#include <sstream>
#include <string>
#include <iostream>
#include <regex>

#include "../Parcelle.hpp"
#include "../Constructible.hpp"

// Type/Number/Owner/Points_list
#define REG_ZN "(ZN) ([0-9]+) ([\\w']+) *\n(\\[[[\\d\\W ]+\\])[\n]?"

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
    ZN(int num, string prop, Polygone<T> shape, const string data);

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
ZN<T>::ZN(int num, string prop, Polygone<T> shape, const string data) : Parcelle<T>(num, prop, shape), Constructible()
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
    // Pattern
    regex regex(REG_ZN);

    // Match handling
    smatch match;
    regex_search(data.cbegin(), data.cend(), match, regex);

    // cout << "type:" << match[1].str() << endl;
    // cout << "num:" << match[2].str() << endl;
    // cout << "prop:" << match[3].str() << endl;
    // cout << "points:" << match[4].str() << endl;
    // Update the properties
    this->setNumero(stoi(match[2]));
    cout << "numero is: " << this->getNumero() << endl;
    this->setProprietaire(match[3].str());
    cout << "propri is: " << this->getProprietaire() << endl;

    Polygone<T> newPoly(match[4].str());
    cout << "string is " << match[4].str() << endl;
    this->setForme(newPoly);
    cout << "NewPlygone is: " << newPoly << endl;
    cout << "getforme is: " << this->getForme() << endl;
}

template <typename T>
string ZN<T>::serialize(void) const
{
    stringstream ret;
    ret << "ZN "
        << this->getNumero() << " "
        << this->getProprietaire();
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