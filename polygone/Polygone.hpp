#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

#include "Point2D.hpp"
#include "../parcelle/Cubit.hpp"

const std::regex reg_poly("\\[( *-?\\d+);( *-?\\d+)\\]");

using namespace std;

template <typename T>
class Polygone;
template <typename T>
ostream &operator<<(ostream &os, Polygone<T> const &p);

template <typename T>
class Polygone : public Cubit
{
protected:
  vector<Point2D<T>> _sommets;

public:
  /* Constructors */
  Polygone();
  Polygone(string data);
  Polygone(vector<Point2D<T>> points);
  Polygone(Polygone<T> const &poly);

  /* Getters */
  vector<Point2D<T>> getSommets() const;
  float getSurface() const;

  /* Setters */
  void setSommets(vector<Point2D<T>> listeSommets);

  /* Methods */
  void addPoint(Point2D<T>);
  void translate(T x, T y);
  void translate(Point2D<T> &point);
  string toString() const;

  void load(string data) override;
  string save(void) const override;
  vector<Point2D<T>> deserialize(string data);

  /* Friends (operator overloarding) */
  friend ostream &operator<< <T>(ostream &os, Polygone const &p);
};

/*
============================
Constructors
============================
*/
template <typename T>
Polygone<T>::Polygone() : Cubit()
{
  _sommets = vector<Point2D<T>>();
}

template <typename T>
Polygone<T>::Polygone(vector<Point2D<T>> points) : Cubit()
{
  _sommets = points;
}

template <typename T>
Polygone<T>::Polygone(Polygone<T> const &poly) : Cubit()
{
  _sommets = poly.getSommets();
}

template <typename T>
Polygone<T>::Polygone(string data) : Cubit()
{
  load(data);
}

/*
============================
Getters
============================
*/
template <typename T>
vector<Point2D<T>> Polygone<T>::getSommets() const
{
  return _sommets;
}

/*
============================
Setters
============================
*/
template <typename T>
void Polygone<T>::setSommets(vector<Point2D<T>> points)
{
  _sommets = points;
}

/*
============================
Methods
============================
*/
template <typename T>
void Polygone<T>::addPoint(Point2D<T> point)
{

  _sommets.push_back(point);
}

template <typename T>
float Polygone<T>::getSurface() const
{
  // Special case (should have used a circular buffer...)
  T x_pi = _sommets.back().getX();
  T y_pi = _sommets.back().getY();
  T x_pi_1 = _sommets.front().getX();
  T y_pi_1 = _sommets.front().getY();

  float sum = ((x_pi * y_pi_1) - (y_pi * x_pi_1));

  for (auto p = begin(_sommets); p != prev(end(_sommets)); p++)
  {
    x_pi = p->getX();
    y_pi = p->getY();
    x_pi_1 = (next(p))->getX();
    y_pi_1 = (next(p))->getY();

    sum += ((x_pi * y_pi_1) - (y_pi * x_pi_1));
  }

  return abs(sum / 2);
}

template <typename T>
void Polygone<T>::translate(Point2D<T> &point)
{
  for (auto p = begin(_sommets); p != end(_sommets); p++)
  {
    p->translate(point);
  }
}

template <typename T>
void Polygone<T>::translate(T x, T y)
{
  for (auto p = begin(_sommets); p != end(_sommets); p++)
  {
    p->translate(x, y);
  }
}

template <typename T>
string Polygone<T>::toString() const
{
  stringstream ret;
  for (auto p = begin(_sommets); p != end(_sommets); p++)
  {
    ret << p->toString() << " ";
  }
  return ret.str();
}

template <typename T>
string Polygone<T>::save(void) const
{
  return this->toString();
}

template <typename T>
void Polygone<T>::load(string data)
{
  _sommets = deserialize(data);
}

template <typename T>
vector<Point2D<T>> Polygone<T>::deserialize(string data)
{
  vector<Point2D<T>> ret = vector<Point2D<T>>();

  smatch m;
  string::const_iterator searchStart(data.cbegin());

  while (regex_search(searchStart, data.cend(), m, reg_poly))
  {
    // cout << m[1];
    // cout << m[2];

    Point2D<T> point(stoi(m[1].str().c_str()), stoi(m[2].str().c_str()));
    ret.push_back(point);

    searchStart = m.suffix().first;
  }

  return ret;
}

/*
============================
Friends (operator overloarding)
Print the point properties
============================
*/
template <typename T>
ostream &operator<<(ostream &os, Polygone<T> const &p)
{
  vector<Point2D<T>> sommets = p.getSommets();
  if (sommets.size() == 0)
    os << "Le polygone ne contient aucun point";
  else if (sommets.size() == 1)
    os << "Le polygone contient un seul point : " << sommets[0];
  else
    os << p.toString();

  return os;
}
