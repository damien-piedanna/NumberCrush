#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

ifstream ifsScore;
ofstream ofsScore;


typedef vector <string> CVString;
void RetrieveData(CVString & VString)
{
    bool check=true;
    while(check)
    {
        string FichierSource="scores";
        unsigned Cpt(3);
        while(Cpt != 0)
        {
            ifsScore.open(FichierSource);
            if(!ifsScore.fail()) break;
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
            getline(ifsScore,Str);
            if(ifsScore.eof())break;
            VString.push_back(Str);
        }
        check=false;
    }
}//RetrieveData

void WriteData(CVString & VString)
{
    bool check=true;
    while(check)
    {
        string FichierDest="scores";
        unsigned Cpt(3);
        while(Cpt != 0)
        {
            ofsScore.open(FichierDest);
            if(!ofsScore.fail()) break;
            --Cpt;
        }
        if(Cpt==0)
        {
            cout << "3 échecs d'ouverture de fichier en ecriture" << endl;
            break;
        }

        for(unsigned i(0);i<VString.size();++i)
            ofsScore << VString[i] << endl;

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
    for(unsigned i(2); i < 11; ++i)
        VScores[i][1]=char((i-1)+48);
}//AjustementLignes

void ModifScores (CVString & VScores,const unsigned & Score,const string & Name)
{
    if(Score > GetScore(VScores,10))
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
        unsigned TailleVec=VScores[CptLigne].size();
        for(unsigned i(0) ; i < SScore.size() ; ++i)
            VScores[CptLigne][TailleVec-(i+3)]=SScore[SScore.size()-(i+1)];

        AjustementLignes(VScores);
    }
}//ModifScores

void ChiffreCesar(string & Ligne,const unsigned Key)
{
    for(unsigned i(0); i < Ligne.size() ; ++i)
        Ligne[i]=char(int(Ligne[i])-Key);
}//ChiffreCesar

void DeChiffreCesar(string & Ligne,const unsigned Key)
{
    for(unsigned i(0); i < Ligne.size() ; ++i)
        Ligne[i]=char(int(Ligne[i])+Key);
}//DeChiffreCesar

void MScores(string & Name, unsigned & Score)
{
    CVString Vec;
    RetrieveData(Vec);

    const unsigned Key = 58;

    cout << endl;

    ModifScores(Vec,Score,Name);

    for(unsigned i(0);i<Vec.size();++i)
        cout << Vec[i] << endl;

    cout << endl;

    WriteData(Vec);
}
