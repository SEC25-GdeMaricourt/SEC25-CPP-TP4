#include <iostream>

#ifdef TEST
#include "tests/tests.hpp"
#endif

using namespace std;

/*
Set this flag when compiling ("-D TEST")
to trigger the "test mode display"
*/

int main(void)
{
#ifdef TEST
    testPoint();
    cout << endl;
    testPolygone();
    cout << endl;
    // testParcelle();
    testZN();
    tCarte();
#else

#endif
    return 0;
}