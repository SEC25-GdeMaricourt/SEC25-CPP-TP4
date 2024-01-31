#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>

#include "../parcelle/ZXX/ZN.hpp"
#include "../parcelle/ZXX/ZA.hpp"
#include "../parcelle/Parcelle.hpp"

const std::regex re_carte("^(ZN|ZA|ZU|ZAU).*\n.*\n?");

template <typename T>
class Carte;
template <typename T>
ostream &operator<<(ostream &os, Carte<T> const &obj);

using namespace std;

template <typename T>
class Carte : public Cubit
{
private:
    std::vector<std::unique_ptr<Parcelle<T>>> _v;

    string serialize(void) const;
    void deserialize(string data);
    string readStrFromF(string path);

    void addZN(string data);
    void addZA(string data);

public:
    /* Constructors */
    Carte(string fileName);

    /* Methods */
    bool add(Parcelle<T> const &p);
    bool remove(Parcelle<T> const &p) const;

    string toString(void) const;

    void load(string data);
    string save(void) const;

    /* Friends (operator overloarding) */
    friend ostream &
    operator<< <T>(ostream &os, Carte<T> const &obj);
};

/*
============================
Constructors
============================
*/
template <typename T>
Carte<T>::Carte(string fileName)
{
    load(fileName);
}

template <typename T>
void Carte<T>::load(string data)
{
    string fileContent(readStrFromF(data));
    deserialize(fileContent);
}

template <typename T>
void Carte<T>::deserialize(string data)
{
    smatch m;
    string::const_iterator searchStart(data.cbegin());

    while (regex_search(searchStart, data.cend(), m, re_carte))
    {
        if (m[1] == "ZN")
        {
            addZN(m[0]);
        }
        else if (m[1] == "ZA")
        {
            addZA(m[0]);
        }
        searchStart = m.suffix().first;
    }
}

// From: https://stackoverflow.com/questions/20902945/reading-a-string-from-file-c
template <typename T>
string Carte<T>::readStrFromF(string filePath)
{
    ifstream f(filePath); // taking file as inputstream
    string str;
    if (f)
    {
        ostringstream ss;
        ss << f.rdbuf(); // reading data
        str = ss.str();
    }
    return str;
}

template <typename T>
void Carte<T>::addZN(string data)
{
    _v.push_back(std::make_unique<ZN<T>>(data));
}

template <typename T>
void Carte<T>::addZA(string data)
{
    _v.push_back(std::make_unique<ZA<T>>(data));
}

template <typename T>
string Carte<T>::save(void) const
{
    return serialize();
}

template <typename T>
string Carte<T>::serialize(void) const
{
    stringstream ret;
    for (auto i = begin(_v); i != end(_v); i++)
    {
        ret << (*i)->save() << endl;
    }
    return ret.str();
}

template <typename T>
string Carte<T>::toString() const
{
    stringstream ret;
    for (auto i = begin(_v); i != end(_v); i++)
    {
        ret << (*i)->toString() << endl;
    }
    return ret.str();
}

template <typename T>
ostream &operator<<(ostream &os, Carte<T> const &c)
{
    os << c.toString();
    return os;
}