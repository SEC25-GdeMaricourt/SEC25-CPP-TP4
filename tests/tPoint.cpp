#include "tests.hpp"

void testPoint()
{
     cout << endl
          << "********* Test des points *********" << endl;
     // Point creation
     Point2D<int> pointA(2, 2);
     Point2D<float> pointB(2.5, 0.5);
     Point2D<int> pointC;
     cout << "--> Création de 3 points" << endl;
     cout << "Point A : " << pointA << endl
          << "Point B : " << pointB << endl
          << "Point C : " << pointC << endl;

     // Point copy (deep copy)
     Point2D<int> pointD(pointA);

     cout << endl
          << "--> Construction par recopie" << endl;
     cout << "Point D construit par recopie du point A" << endl
          << "Point D : " << pointD << endl;

     // Point transfer
     cout << endl
          << "--> Translations" << endl;
     pointA.translate(pointB.getX(), pointB.getY());
     cout << "Point A translaté par les coordonnées du point B" << endl
          << "Point A : " << pointA << endl;
     pointA.translate(pointD);
     cout << "Point A translaté par le point D" << endl
          << "Point A : " << pointA << endl;
     cout << "Point D non translaté par les opérations précédentes" << endl
          << "Point D : " << pointD << endl;
}