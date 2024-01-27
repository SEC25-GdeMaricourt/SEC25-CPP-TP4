#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

#include "Point2D.hpp"
#include "../parcelle/Cubit.hpp"

using namespace std;

#define REG_POINT "\\[(-?\\d+);(-?\\d+)\\]"

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
  vector<Point2D<T>> serialize(string data);

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
  T x_i = _sommets.back().getX();
  T y_i = _sommets.back().getY();
  T x_i_1 = _sommets.front().getX();
  T y_i_1 = _sommets.front().getY();

  float sum = ((x_i * y_i_1) - (y_i * x_i_1));

  for (auto it = begin(_sommets); it != prev(end(_sommets)); it++)
  {
    T x_i = it->getX();
    T y_i = it->getY();
    T x_i_1 = (next(it))->getX();
    T y_i_1 = (next(it))->getY();

    sum += ((x_i * y_i_1) - (y_i * x_i_1));
  }

  return abs(sum / 2);
}

template <typename T>
void Polygone<T>::translate(Point2D<T> &point)
{
  for (auto it = begin(_sommets); it != end(_sommets); it++)
  {
    it->translate(point);
  }
}

template <typename T>
void Polygone<T>::translate(T x, T y)
{
  for (auto it = begin(_sommets); it != end(_sommets); it++)
  {
    it->translate(x, y);
  }
}

template <typename T>
string Polygone<T>::toString() const
{
  stringstream ret;
  for (auto point = begin(_sommets); point != end(_sommets); point++)
  {
    ret << point->toString() << " ";
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
  _sommets = serialize(data);
}

template <typename T>
vector<Point2D<T>> Polygone<T>::serialize(string data)
{
  // Pattern
  regex regex(REG_POINT);

  // Match handling
  smatch match;
  string::const_iterator searchStart(data.cbegin());
  vector<Point2D<T>> ret = vector<Point2D<T>>();

  while (regex_search(searchStart, data.cend(), match, regex))
  {
    // Add point to the vector
    Point2D<T> point(stoi(match[1]), stoi(match[2]));
    ret.push_back(point);

    // Update of starting point for the next seek
    searchStart = match.suffix().first;
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
