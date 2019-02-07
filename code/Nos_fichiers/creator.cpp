#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <unistd.h>
#include <stdlib.h>
#include "Nos_fichiers/consolemanagement.h"
#include "Correc_prof/gridmanagement.h"


using namespace std;


void DisplayGridCreator(unsigned &  Compteur, vector <string> & StockDeVar, unsigned & GridSize)
{
    ClearScreen();
    cout << "Entrez la ligne " <<  Compteur+1 << " sur "<< GridSize <<" chiffres avec un 0 pour les cases ordinaires et" << endl << "un 1 pour les murs (ils peuvent tomber)" << endl << endl;
    if( Compteur != 0)
    {
        for(unsigned j = 0; j <  Compteur ; ++j)
        {
            for(unsigned k = 0; k < StockDeVar.size() ; ++k)
            {
                cout << StockDeVar[4+j][k];
            }
            cout << endl;
        }
        cout << endl;
    }
}

bool TestValeurDansString(string & Str, unsigned & GridSize)
{
    if(Str.size() != GridSize) return false;
    for(unsigned i=0;i < Str.size(); ++i)
    {
        if(Str[i] != '0' && Str[i] != '1')
        {
                return false;
        }
    }
    return true;
}// TestValeurDansString ()


string UserImputNomLevel()
{
    cout << "Choisissez un nom pour votre niveau / mettre a jour un niveau (max 20 caracteres et champs obligatoire)" << endl << endl;
    string NomLevel; // rajouter le test d'existence du fichier
    while(true) {
        bool NoSlash=true;
        NomLevel="reset";
        getline(cin,NomLevel);
        if(NomLevel.size() > 20 || NomLevel.size() == 0) {
            ClearScreen();
            cout << "Choisissez un nom pour votre niveau / mettre a jour un niveau (max 20 caracteres et champs obligatoire)" << endl << endl;
            cout << "Respectez les consignes !!!" << endl << endl;
            continue;
        }
        for(unsigned i=0; i < NomLevel.size(); ++i) {
            if(NomLevel[i]=='/') {
                ClearScreen();
                cout << "Choisissez un nom pour votre niveau / mettre a jour un niveau (max 20 caracteres et champs obligatoire)" << endl << endl;
                cout << "Les / sont interdits dans les noms de fichier sous linux" << endl << endl;
                NoSlash=false;
                break;
            }
        }
        if(NoSlash)break;
    }

    NomLevel = "../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/niveaux_cree/" + NomLevel;
    return NomLevel;
}

unsigned UserImputTailleGrille()
{
    cout << "Entrez la taille de la grille" << endl << endl;
    unsigned GridSize;
    while(true) {
        cin >> GridSize;
        if(cin.fail() || GridSize >= 20 || GridSize < 3) {
            ClearBuf();
            ClearScreen();
            cout << "Entrez la taille de la grille" << endl << endl;
            cout << "Entrez un nombre positif strictement inferieur a 20 et superieur a 3 (faut pas abuser quand meme)" << endl << endl;
            continue;
        }
        break;
    }
    return GridSize;
}

unsigned UserImputScoreToWin()
{
    cout << "Entrez le score a atteindre pour reussir le niveau (max 9998)" << endl << endl;
    unsigned ScoreToWin = 0;
    while(true) {
        cin >> ScoreToWin;
        if(cin.fail() || ScoreToWin > 9998) {
            ClearBuf();
            ClearScreen();
            cout << "Entrez le score a atteindre pour reussir le niveau (max 9998)" << endl << endl;
            cout << "Entrez un nombre positif inferieur a 9998" << endl << endl;
            continue;
        }
        break;
    }

    return ScoreToWin;
}

unsigned UserImputNbCandies()
{
    cout << "Entrez le nombre de valeurs que les cases de la grille peuvent adopter" << endl << endl;
    unsigned NbCandies;
    while(true) {
        cin >> NbCandies;
        if(cin.fail() || NbCandies > 7 || NbCandies < 2) {
            ClearBuf();
            ClearScreen();
            cout << "Entrez le nombre de valeurs que les cases de la grille peuvent adopter" << endl << endl;
            cout << "Entrez un nombre strictement positif entre 2 et 7 car le terminal ne nous donne acces qu'a 8 couleurs et qu'il y a des murs ! ;{" << endl << endl;
            continue;
        }
        break;
    }
    return NbCandies;
}

unsigned UserImputCoups()
{
    cout << "Entrez le nombre de coups possibles" << endl << endl;
    unsigned Coups;
    while(true) {
        cin >> Coups;
        if(cin.fail()) {
            ClearBuf();
            ClearScreen();
            cout << "Entrez le nombre de coups possibles" << endl << endl;
            cout << "Entrez un nombre positif !" << endl << endl;
            continue;
        }
        break;
    }
    return Coups;
}

vector <string> UserImputNiveau(vector <string> & StockDeVar, unsigned & GridSize)
{
    string LigneTmp;
    ClearBuf();
    for(unsigned i=0; i < GridSize; ++i) {
        DisplayGridCreator(i,StockDeVar,GridSize);
        while(true) {
            getline(cin, LigneTmp);
            if(!TestValeurDansString(LigneTmp, GridSize)) {
                ClearScreen();
                DisplayGridCreator(i,StockDeVar,GridSize);
                cout << "Veuillez respecter les indications donnees !" << endl << endl;
                continue;
            }
            ClearScreen();
            break;
        }
        StockDeVar[i+4]=LigneTmp;
    }
    return StockDeVar;
}

void LevelCreator()
{
    string NomLevel = UserImputNomLevel();
    ClearScreen();
    unsigned GridSize = UserImputTailleGrille();
    ClearScreen();
    unsigned ScoreToWin = UserImputScoreToWin();
    ClearScreen();
    unsigned NbCandies = UserImputNbCandies();
    ClearScreen();
    unsigned Coups = UserImputCoups();

    vector <string> StockDeVar;
    StockDeVar.resize(GridSize+4);
    StockDeVar[0]=to_string(GridSize);
    StockDeVar[1]=to_string(NbCandies);
    StockDeVar[2]=to_string(Coups);
    StockDeVar[3]=to_string(ScoreToWin);

    StockDeVar = UserImputNiveau(StockDeVar,GridSize);

    ofstream ofs(NomLevel);
    for(unsigned i=0; i < StockDeVar.size(); ++i) {
        ofs << StockDeVar[i] << endl;
    }
    cout << "Bravo, votre niveau a ete cree avec succes !" << endl;
} // LevelCreator ()
