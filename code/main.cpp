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
        cerr << "ca c'est mal passe quelque part" << endl;
        return 1;
    }

} // main()
