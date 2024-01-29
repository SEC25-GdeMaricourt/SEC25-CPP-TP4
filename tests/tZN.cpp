#include "tests.hpp"

void testZN()
{
    cout << endl
         << "********* Test des ZN *********" << endl;
    vector<Point2D<float>> pointRect = vector<Point2D<float>>{Point2D<float>(0, 0), Point2D<float>(0, 10.5), Point2D<float>(10.5, 10.5), Point2D<float>(10.5, 0)};
    Polygone<float> rect(pointRect);

    cout << "--> Construction d\'une ZN" << endl;
    ZN<float> zn(1, "Henry", rect);
    cout << zn << endl;

    ZN<float> zn2(zn);
    cout
        << endl
        << "--> Construction par recopie" << endl;
    cout << zn2 << endl;

    cout
        << endl
        << "--> Construction par regex" << endl;
    string znData("ZN 6 MANAC'H \n[300; -200][195; -60][150; -100][150; -200][150; -261]");
    ZN<float> znReg(znData);
    cout << znReg << endl;

    vector<Point2D<float>>
        pointsCarre = vector<Point2D<float>>{Point2D<float>(0, 0), Point2D<float>(0, 1), Point2D<float>(1, 1), Point2D<float>(1, 0)};
    Polygone<float> carre(pointsCarre);
    zn.setNumero(10);
    zn.setProprietaire("Paul");
    zn.setForme(carre);
    cout
        << endl
        << "--> Modification des attributs" << endl;

    cout
        << "Nouvel original:" << endl
        << zn << endl;

    cout << "Copie (non modifié):" << endl
         << zn2 << endl;

    cout
        << endl
        << "--> Sauvegarde" << endl;
    cout << znReg.save() << endl;
}