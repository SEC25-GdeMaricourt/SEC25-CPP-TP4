#include "tests.hpp"

void testZA()
{
    cout << endl
         << "********* Test des ZA *********" << endl;
    vector<Point2D<float>> pointRect = vector<Point2D<float>>{Point2D<float>(0, 0), Point2D<float>(0, 10.5), Point2D<float>(10.5, 10.5), Point2D<float>(10.5, 0)};
    Polygone<float> rect(pointRect);

    cout << "--> Construction d\'une ZN" << endl;
    ZA<float> za(1, "Henry", rect, "ble", 100);
    cout << za << endl;

    ZA<float> za2(za);
    cout
        << endl
        << "--> Construction par recopie" << endl;
    cout << za2 << endl;

    cout
        << endl
        << "--> Construction par regex" << endl;
    string zaData("ZA 20 SAUVIGNON Blé \n[300; -200][195; -60][150; -100][150; -200][150; -261]");
    ZA<float> zaReg(zaData);
    cout << zaReg << endl;

    vector<Point2D<float>>
        pointsCarre = vector<Point2D<float>>{Point2D<float>(0, 0), Point2D<float>(0, 1), Point2D<float>(1, 1), Point2D<float>(1, 0)};
    Polygone<float> carre(pointsCarre);
    za.setNumero(10);
    za.setProprietaire("Paul");
    za.setForme(carre);
    za.setCulture("Froment");
    za.setSurfaceConstruite(0.01);
    cout
        << endl
        << "--> Modification des attributs" << endl;

    cout
        << "Nouvel original:" << endl
        << za << endl;

    cout << "Copie (non modifié):" << endl
         << za2 << endl;

    cout
        << endl
        << "--> Sauvegarde" << endl;
    cout << zaReg.save() << endl;
}