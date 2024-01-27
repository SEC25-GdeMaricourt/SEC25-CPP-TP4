#include "tests.hpp"

void testPolygone()
{
     cout << endl
          << "********* Test des polygones *********" << endl;
     Point2D<int> pointA(2, 2);
     Point2D<int> pointB;
     Point2D<int> pointC(4, 4);

     // Polygone creation
     cout << "--> Construction de polygones" << endl;
     Polygone<float> polygoneA;
     cout << "Polygone A : " << polygoneA << endl;
     Polygone<int> polygoneB(vector<Point2D<int>>{pointA, pointB, pointC});
     cout << "Polygone B : " << polygoneB << endl;
     Polygone<int> polygoneRegex("[-47;-158] [-72;-239] [0;-275] [25; -208] ");
     cout << "--> Construction par regex" << endl;
     cout << "Jeux de données [-47;-158] [-72;-239] [0;-275] [25; -208] " << endl
          << "Polygone par regex avec ajout de points : " << polygoneRegex << endl;

     // Add point
     Point2D<float> pointD(10, 10);
     polygoneA.addPoint(pointD);
     polygoneA.addPoint(Point2D<float>(1.2, 3.0));
     polygoneA.addPoint(Point2D<float>(3.7, 2.0));
     cout << "--> Construction par ajout de points" << endl;
     cout << "Polygone A avec ajout de points : " << polygoneA << endl;

     // Deep copy
     Polygone<float> polygoneC(polygoneA);
     cout << "--> Construction par recopie" << endl;
     cout << "Polygone C construit par recopie de A : " << polygoneC << endl;

     // Move
     cout << endl
          << "--> Translations" << endl;
     polygoneA.translate(pointD);
     cout << "Polygone A translaté par le point D : " << polygoneA << endl;
     cout << "Polygone C non translaté par l'opération précédente : " << polygoneC << endl;

     // Update of peaks
     cout << endl
          << "--> Redéfinition des sommets" << endl;
     polygoneA.setSommets(vector<Point2D<float>>{pointD, Point2D<float>(1.0, 3.0), Point2D<float>(10.0, 10.0)});
     cout << "Polygone A redéfinition des sommets : " << polygoneA << endl;

     cout << endl
          << "--> Calcul de la surface d'une rectangle" << endl;
     vector<Point2D<float>> pointRect = vector<Point2D<float>>{Point2D<float>(0, 0), Point2D<float>(0, 10.5), Point2D<float>(10.5, 10.5), Point2D<float>(10.5, 0)};
     Polygone<float> rect(pointRect);
     cout << "Rectangle : " << rect << endl;
     cout << "La surface de ce rectangle vaut : " << rect.getSurface() << endl;

     cout << endl
          << "--> Génération d'une chaine pour la sauvegarde" << endl;
     cout << rect.save();
}