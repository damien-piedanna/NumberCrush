#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

ifstream ifs;
ofstream ofs;


typedef vector <string> CVString;
void RetrieveData(CVString & VString)
{
    bool check=true;
    while(check)
    {
        string FichierSource;
        unsigned Cpt(3);
        while(Cpt != 0)
        {
            cout << "Nom du fichier source : " << endl;
            getline(cin,FichierSource);
            ifs.open(FichierSource);
            if(!ifs.fail()) break;
            --Cpt;
        }
        if(Cpt==0)
        {
            cout << "3 échecs d'ouverture de fichier en lecture" << endl;
            break;
        }
        while(true)
        {
            string Str;
            getline(ifs,Str);
            if(ifs.eof())break;
            VString.push_back(Str);
        }
        check=false;
    }
}//RetrieveData

typedef vector <string> CVString;
void WriteData(CVString & VString)
{
    bool check=true;
    while(check)
    {
        string FichierDest;
        unsigned Cpt(3);
        while(Cpt != 0)
        {
            cout << "Nom du fichier de destination : " << endl;
            getline(cin,FichierDest);
            ofs.open(FichierDest);
            if(!ofs.fail()) break;
            --Cpt;
        }
        if(Cpt==0)
        {
            cout << "3 échecs d'ouverture de fichier en ecriture" << endl;
            break;
        }

        for(unsigned i(0);i<VString.size();++i)
            ofs << VString[i] << endl;

        check=false;
    }
}//FonctionGet

int main()
{
    vector <string> VecInput;
    RetrieveData(VecInput);
    //for(unsigned i(0); i<FileInput.size();++i)
    //    cout << FileInput[i];
    WriteData(VecInput);

    return 0;
}
