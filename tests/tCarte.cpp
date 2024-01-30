#include "tests.hpp"

void tCarte()
{
    // string test("ZN 6 MANAC'H \n[300; -200][195; -60][150; -100][150; -200][150; -261]\n");

    cout
        << endl
        << "********* Test des cartes *********" << endl;

    cout << "--> Construction par regex" << endl;
    Carte<float> carte("t.txt");
    cout << "-->Affichage" << endl;
    cout << carte << endl;
    cout << "--> Sauvegarde" << endl;
    string save(carte.save());
    cout << save << endl;
}