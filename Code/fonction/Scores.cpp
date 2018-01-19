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



void DescendreLignes(CVString & VScores,const unsigned & Ligne)
{
    for(unsigned i(10) ; i > Ligne ; --i )
        VScores[i] = VScores[i-1];
}//DescendreLignes

void AjustementLignes(CVString & VScores)
{
    for(unsigned i(2); i < 10; ++i)
        VScores[i][1]=char((i-1)+48);
}//AjustementLignes

void ModifScores (CVString & VScores,const unsigned & Score,const string & Name)
{
    unsigned CptLigne(2);
    for(;CptLigne<12;++CptLigne)
        if(Score>GetScore(VScores,CptLigne))
        {
            DescendreLignes(VScores,CptLigne);
            break;
        }

    //Change le nom
    for(unsigned i(0) ; i < Name.size() ; ++i)
        VScores[CptLigne][i+4]=Name[i];
    for(unsigned i(Name.size()+4) ; i < 11 ; ++i)
       VScores[CptLigne][i]=' ';

    //Change le score
    string SScore=to_string(int(Score));
    for(unsigned i(0) ; i < SScore.size() ; ++i)
        VScores[CptLigne][i+18]=SScore[i];
    for(unsigned i(SScore.size()+4) ; i < 11 ; ++i)
        VScores[CptLigne][i]=' ';



    AjustementLignes(VScores);
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

    for(unsigned i(0);i<Vec.size();++i)
        cout << Vec[i] << endl;

    cout << endl;

    ModifScores(Vec,500,"Leo");

    for(unsigned i(0);i<Vec.size();++i)
        cout << Vec[i] << endl;

    return 0;
}
