#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
typedef vector <string> CVString;
bool TestFichier()
{
    ifstream ifsFichier;
    string FichierSource;
    unsigned Cpt(3);
    while(Cpt != 0)
    {
        getline(cin, FichierSource);
        ifsFichier.open(FichierSource);
        if(!ifsFichier.fail()) return true;
        --Cpt;
    }
    if(Cpt==0)
    {
        return false;
    }
    return false;
}//TestFichier

int main()
{
    cout << "Hello World!" << endl;
    cout << TestFichier() << endl;
    return 0;
}
