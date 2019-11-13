#include <iostream>
#include "Nos_fichiers/jeu.h"

using namespace std;

int main()
{
    try
    {
        return jeu ();
    }
    catch (...)
    {
        cerr << "something went wrong" << endl;
        return 1;
    }

} // main()
