#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

template <typename T>
class Point2D;
template <typename T>
ostream &operator<<(ostream &os, Point2D<T> const &p);

/*
============================
Point2D
============================
*/
template <typename T>
class Point2D
{
protected:
    T _x;
    T _y;

public:
    /* Constructors */
    Point2D(const T &x, const T &y);
    Point2D(const Point2D<T> &p);
    Point2D();

    /* Getters */
    T getX() const;
    T getY() const;

    /* Setters */
    void setX(const T &x);
    void setY(const T &y);

    /* Methods */
    // Two ways of moving a point
    void translate(const Point2D<T> &p);
    void translate(const T &x, const T &y);
    string toString() const;

    /* Friends (operator overloarding) */
    friend ostream &operator<< <T>(ostream &os, Point2D<T> const &p);
};

/*
============================
Constructors
============================
*/
template <typename T>
Point2D<T>::Point2D(const T &x, const T &y)
{
    _x = x;
    _y = y;
}

template <typename T>
Point2D<T>::Point2D(const Point2D &p)
{
    _x = p.getX();
    _y = p.getY();
}

template <typename T>
Point2D<T>::Point2D()
{
    _x = 0;
    _y = 0;
}

/*
============================
Getters
============================
*/
template <typename T>
T Point2D<T>::getX() const
{
    return _x;
}

template <typename T>
T Point2D<T>::getY() const
{
    return _y;
}

/*
============================
Setters
============================
*/
template <typename T>
void Point2D<T>::setX(const T &x)
{
    _x = x;
}

template <typename T>
void Point2D<T>::setY(const T &y)
{
    _y = y;
}

/*
============================
Methods
============================
*/
template <typename T>
void Point2D<T>::translate(const T &x, const T &y)
{
    _x += x;
    _y += y;
}

template <typename T>
void Point2D<T>::translate(const Point2D &p)
{
    _x += p.getX();
    _y += p.getY();
}

template <typename T>
string Point2D<T>::toString() const
{
    stringstream ret;
    ret << "[";
    ret << fixed << setprecision(2) << _x;
    ret << ";";
    ret << fixed << setprecision(2) << _y;
    ret << "]";
    return ret.str();
}

/*
============================
Friends (operator overloarding)
Print the point properties
============================
*/
template <typename T>
ostream &operator<<(ostream &os, Point2D<T> const &p)
{
    os << p.toString();
    return os;
}