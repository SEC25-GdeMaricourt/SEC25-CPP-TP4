#pragma once

#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Cubit.hpp"
#include "../polygone/Polygone.hpp"

using namespace std;

template <typename T>
class Parcelle;
template <typename T>
ostream &operator<<(ostream &os, Parcelle<T> const &p);

/*
============================
Parcelle
============================
*/
template <typename T>
class Parcelle : public Cubit
{
private:
    int _num;
    string _prop;
    Polygone<T> _shape;

public:
    /* Constructors */
    Parcelle(int num, string prop, Polygone<T> shape);
    Parcelle(const Parcelle<T> &p);

    /* Getters */
    int getNumero(void) const;
    string getProprietaire(void) const;
    Polygone<T> getForme(void) const;

    /* Setters */
    void setNumero(int num);
    void setProprietaire(string prop);
    void setForme(Polygone<T> shape);

    /* Methods */
    float getSurface(void) const;
    string toString(void) const;

    virtual void load(string data) = 0;
    virtual string save(void) const = 0;

    /* Friends (operator overloarding) */
    friend ostream &operator<< <T>(ostream &os, Parcelle<T> const &p);
};

/*
============================
Constructors
============================
*/
template <typename T>
Parcelle<T>::Parcelle(int num, string prop, Polygone<T> forme) : Cubit()
{
    _num = num;
    _prop = prop;
    _shape = forme;
}

template <typename T>
Parcelle<T>::Parcelle(const Parcelle &p) : Cubit()
{
    _num = p.getNumero();
    _prop = p.getProprietaire();
    _shape = p.getForme();
}

/*
============================
Getters
============================
*/
template <typename T>
int Parcelle<T>::getNumero(void) const
{
    return _num;
}

template <typename T>
string Parcelle<T>::getProprietaire(void) const
{
    return _prop;
}

template <typename T>
Polygone<T> Parcelle<T>::getForme(void) const
{
    return _shape;
}

/*
============================
Methods
============================
*/
template <typename T>
float Parcelle<T>::getSurface(void) const
{
    return _shape.getSurface();
}

template <typename T>
string Parcelle<T>::toString(void) const
{
    stringstream ret;
    ret << "Parcelle n°" << fixed << setprecision(0) << getNumero() << endl;
    ret << "   Polygone             : " << getForme() << endl;
    ret << "   Propriétaire         : " << getProprietaire() << endl;
    ret << "   Surface              : " << fixed << setprecision(2) << getSurface() << endl;
    return ret.str();
}

/*
============================
Setters
============================
*/
template <typename T>
void Parcelle<T>::setNumero(int num)
{
    _num = num;
}

template <typename T>
void Parcelle<T>::setProprietaire(string prop)
{
    _prop = prop;
}

template <typename T>
void Parcelle<T>::setForme(Polygone<T> shape)
{
    _shape = shape;
}

/*
============================
Friends (operator overloarding)
Print the point properties
============================
*/
template <typename T>
ostream &operator<<(ostream &os, Parcelle<T> const &p)
{
    os << p.toString();
    return os;
}