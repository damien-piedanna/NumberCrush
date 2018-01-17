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

unsigned GetScore (CVString & VScores,const unsigned & Ligne)
{
    unsigned M=(VScores[Ligne][18])-48;
    unsigned C=(VScores[Ligne][19])-48;
    unsigned D=(VScores[Ligne][20])-48;
    unsigned U=(VScores[Ligne][21])-48;
    unsigned Score=(M*1000)+(C*100)+(D*10)+U;
    return Score;
}//GetScore

string GetName(CVString & VScores, const unsigned & Ligne)
{
    string Name="";
    for(unsigned i(4);i<15;++i)
    {
        Name+=VScores[Ligne][i];
    }
    return Name;
}//GetName

void DescendreLignes (CVString & VScores, unsigned & Ligne)
{
    for(unsigned i(VScores.size()-1);i>Ligne;--i)
    {

    }
}//DescendreLignes

unsigned FindRow (CVString & VScores,unsigned & Score)
{
    unsigned CptLigne=2;
    if(Score>GetScore(VScores,CptLigne))
        cout << 'l';

}//FindRow

int main()
{
    /*
    CVString VecInput;
    RetrieveData(VecInput);
    //for(unsigned i(0); i<FileInput.size();++i)
    //    cout << FileInput[i];
    WriteData(VecInput);
    */

    CVString Vec;
    RetrieveData(Vec);
    cout << GetScore(Vec, 2) << endl;

    cout << GetName(Vec,2) << endl;
    return 0;
}
