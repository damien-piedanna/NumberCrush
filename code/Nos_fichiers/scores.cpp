#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include "Nos_fichiers/scores.h"
#include "Nos_fichiers/consolemanagement.h"

using namespace std;

void RetrieveData(CVString & VString, const string & FichierSource)
{
    ifstream ifsScore;
    bool check=true;
    while(check)
    {
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
} // RetrieveData()
  //Remplit VString par FichierSource


void WriteData(CVString & VString, const string & FichierDest)
{
    ofstream ofsScore;
    bool check=true;
    while(check)
    {
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
} // WriteData()
    // //Remplit FicSource par VString

unsigned GetScore (CVString & VScores, const unsigned & Ligne)
{
    unsigned M=(VScores[Ligne][18])-48;
    unsigned C=(VScores[Ligne][19])-48;
    unsigned D=(VScores[Ligne][20])-48;
    unsigned U=(VScores[Ligne][21])-48;
    unsigned Score=(M*1000)+(C*100)+(D*10)+U;
    return Score;
} // GetScore()
  // RecupScore

string GetName(CVString & VScores, const unsigned & Ligne)
{
    string Name="";
    for(unsigned i(4);i<15;++i)
    {
        Name+=VScores[Ligne][i];
    }
    return Name;
} // GetName()
  //RecupererNom

void DescendreLignes(CVString & VScores,const unsigned & Ligne)
{
    for(unsigned i(10) ; i > Ligne ; --i )
        VScores[i] = VScores[i-1];
} // DescendreLignes()
  // CLasser les scores

void AjustementLignes(CVString & VScores)
{
    for(unsigned i(2); i < 11; ++i)
        VScores[i][1]=char((i-1)+48);
} // AjustementLignes()
  // Ajuste position classement

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
} // ModifScores()
  // Modif vect score

void ChiffreCesar(string & Ligne,const unsigned Key)
{
    for(unsigned i(0); i < Ligne.size() ; ++i)
        Ligne[i]=char(int(Ligne[i])-Key);
} // ChiffreCesar()

void DeChiffreCesar(string & Ligne,const unsigned Key)
{
    for(unsigned i(0); i < Ligne.size() ; ++i)
        Ligne[i]=char(int(Ligne[i])+Key);
} // DeChiffreCesar()

void DisplayFile2 (const string & File)
{
    ifstream ifsScore;
    ifsScore.open (File);
    while(true)
    {
        string Str;
        getline(ifsScore,Str);
        if(ifsScore.eof())break;
        cout << Str << endl;
    }
} // DisplayFile()

void AfficheScores(const unsigned Key, string & File)
{
    CVString Vec;
    File = "../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/scores/" + File ;
    RetrieveData(Vec, File);
    DisplayFile2("../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/menus_txt/classement.txt");
    cout << " 	    **	                                        **" << endl;
    for(unsigned i(0); i < Vec.size() ; ++i)
    {
        cout << "            **         ";
        DeChiffreCesar(Vec[i],Key);
        cout << Vec[i] << "         **" << endl;
    }
    cout << " 	    **********************************************" << endl << endl;
} // AfficheScores()

void MScores(string & Name, unsigned & Score, const unsigned Key, string & File)
{
    CVString Vec;
    RetrieveData(Vec, File);
    for(unsigned i(0);i<Vec.size();++i)
        DeChiffreCesar(Vec[i],Key);

    cout << endl;

    ModifScores(Vec,Score,Name);

    for(unsigned i(0);i<Vec.size();++i)
        cout << Vec[i] << endl;

    cout << endl;

    for(unsigned i(0);i<Vec.size();++i)
        ChiffreCesar(Vec[i],Key);

    WriteData(Vec, File);
} // MScores()
  // Modifie fichier score

string GetStringName(const unsigned & MaxSize)
{
    string Name="";
    bool NoAccent = true;

    while (true)
    {
        cin >> Name;
        NoAccent=true;
        for(unsigned i(0); i < Name.size() ; ++i)
        {
            if(!isalpha(Name[i]))
                NoAccent = false;
        }

        if (cin.fail() || Name.size() > MaxSize || !NoAccent)
        {
            cout << "Votre nom comporte des accents, des caractères non alphabétiques, ou est trop long ( Max : "<< MaxSize << ')' << endl << endl;
            ClearBuf();
            continue;
        }
        break;
    }
    return Name;
} // GetStringName()
  // Condition / protection entrer de nom

void SaveScores(unsigned & Score, const unsigned & Key, string & File)
{
    if(File=="perso" || File=="facile" || File=="normal")
        cout << "Pas d'enregistrement des scores dans ce mode de jeu !" << endl;
    else
    {
        cout << "Pour sauvegarder votre score, entrez votre nom : " << endl;
        string Name=GetStringName(11);
        File="../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/scores/"+File;
        if(Score > 9999)
            Score=9999;
        MScores(Name,Score, Key, File);
    }
} // SaveScores()
  // Demande enregistrement score
