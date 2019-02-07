#include "Correc_prof/gridmanagement.h"
#include "Nos_fichiers/consolemanagement.h"
#include "Nos_fichiers/menu.h"
#include "Nos_fichiers/move.h"
#include "Nos_fichiers/gridmanage.h"
#include "Nos_fichiers/scores.h"
#include "Nos_fichiers/useractions.h"
#include "Nos_fichiers/creator.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>



void DisplayFile (const string & File)
{
    ifstream ifsFile;
    ifsFile.open (File);
    if (!(ifsFile.is_open ())) //si le fichier n'a pas pu être ouvert
    {
        if (File == "../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/menus_txt/menu.txt")
        {
            cout << "Menu" << endl
                 << "1 - Jouer" << endl
                 << "2 - Options" << endl
                 << "3 - Règles" << endl
                 << "4 - Crédits" << endl
                 << "5 - Quitter" << endl;
            return;
        }
        if (File == "../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/menus_txt/jouer.txt")
        {
            cout << "Jouer" << endl
                 << "1 - Classique" << endl
                 << "2 - Perso" << endl
                 << "3 - Histoire" << endl
                 << "4 - Retour" << endl;
            return;
        }
        if (File == "../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/menus_txt/histoire.txt")
        {
            cout << "Histoire" << endl
                 << "1 - Niveau 1" << endl
                 << "2 - Niveau 2" << endl
                 << "3 - Niveau 3" << endl
                 << "4 - Niveau 4" << endl
                 << "5 - Niveau 5" << endl
                 << "6 - Retour" << endl;
            return;
        }
        if (File == "../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/menus_txt/classique.txt")
        {
            cout << "Classique" << endl
                 << "1 - Facile" << endl
                 << "2 - Moyen" << endl
                 << "3 - Difficile" << endl
                 << "4 - Retour" << endl;
            return;
        }
        if (File == "../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/menus_txt/menuscore.txt")
        {
            cout << "Scores" << endl
                 << "1 - Classique" << endl
                 << "2 - Niveau 1" << endl
                 << "3 - Niveau 2" << endl
                 << "4 - Niveau 3" << endl
                 << "5 - Niveau 4" << endl
                 << "6 - Niveau 5" << endl;
            return;
        }
        if ( File == "../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/menus_txt/credits.txt")
        {
            cout << "Conçu et réalisé par : " << endl
                 << " - Nicolas TROUIN " << endl
                 << " - Sylvain PRAT " << endl
                 << " - Clément ROBBE " << endl
                 << " - Benjamin LEGRAND " << endl
                 << " - Damien PIEDANNA " << endl;
            return;
        }
    }
    string str;
    while (!(ifsFile.eof()))
    {
        getline (ifsFile, str);
        cout << str << endl;
    }
}// DisplayFile()


void PartiePerso (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup)
{
    cout << "Nombre de colonne (5 - 30) : ";
    Size_col = GetUnsigned (5,30);

    cout << "Nombre de ligne (5 - 30) : ";
    Size_lin = GetUnsigned (5,30);

    cout << "Numero de bonbon max (4 - 8) : ";
    NbCandies = GetUnsigned (4,8);

    cout << "Nombre de coup max (1 - 100) : ";
    Coup = GetUnsigned (1,100);

    InitGrid2 (Grid, Size_col, Size_lin, NbCandies);
}// PartiePerso()

void Perso (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned &ScoreToWin)
{
    LvlScores="perso";
    ClearScreen();
    DisplayFile  ("../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/menus_txt/perso.txt");
    unsigned choix = GetUnsigned (1,4);
    ClearScreen();
    ClearBuf();
    switch (choix)
    {
    case 1:
        PartiePerso(Grid,Size_col,Size_lin,NbCandies,Coup);
        break;
    case 2:
        LevelCreator();
        Menu2(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    case 3:
        LoadLevelCreated(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    case 4:
        Jouer(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    }

} // Perso()

void Histoire(CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned & ScoreToWin)
{
    ClearScreen();
    DisplayFile  ("../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/menus_txt/histoire.txt");
    unsigned choix = GetUnsigned (1,6);

    switch (choix)
    {
    case 1:
        LvlScores="lvl1.score";
        LoadLevel ("../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/niveaux/level1", Grid, NbCandies, Coup, Size_col, Size_lin, ScoreToWin);
        break;
    case 2:
        LvlScores="lvl2.score";
        LoadLevel ("../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/niveaux/level2", Grid, NbCandies, Coup, Size_col, Size_lin, ScoreToWin);
        break;
    case 3:
        LvlScores="lvl3.score";
        LoadLevel ("../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/niveaux/level3", Grid, NbCandies, Coup, Size_col, Size_lin, ScoreToWin);
        break;
    case 4:
        LvlScores="lvl4.score";
        LoadLevel ("../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/niveaux/level4", Grid, NbCandies, Coup, Size_col, Size_lin, ScoreToWin);
        break;
    case 5:
        LvlScores="lvl5.score";
        LoadLevel ("../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/niveaux/level5", Grid, NbCandies, Coup, Size_col, Size_lin, ScoreToWin);
        break;
    case 6:
        ClearScreen();
        ClearBuf ();
        Jouer(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    }
} // Histoire()

void Jouer (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned & ScoreToWin)
{
    ClearScreen();
    DisplayFile  ("../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/menus_txt/jouer.txt");
    unsigned choix = GetUnsigned (1,4);
    ClearScreen();
    ClearBuf();
    switch (choix)
    {
    case 1:
        Classique(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    case 2:
        Perso(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores,ScoreToWin);
        break;
    case 3:
        Histoire(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    case 4:;
        Menu2(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    }
} // MenuJouer()

void Classique (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned & ScoreToWin)
{
    ClearScreen();
    DisplayFile  ("../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/menus_txt/classique.txt");
    unsigned choix = GetUnsigned (1,4);
    switch (choix)
    {
    case 1: //facile
        Size_col = 10;
        Size_lin = 10;
        NbCandies = 5;
        Coup = 20;
        LvlScores="facile";
        InitGrid2(Grid, Size_col, Size_lin, NbCandies);
        break;
    case 2: //normal
        Size_col = 8;
        Size_lin = 8;
        NbCandies = 6;
        Coup = 15;
        LvlScores="normal";
        InitGrid2(Grid, Size_col, Size_lin, NbCandies);
        break;
    case 3: //difficile
        Size_col = 6;
        Size_lin = 6;
        NbCandies = 8;
        Coup = 10;
        LvlScores="difficile.score";
        InitGrid2(Grid, Size_col, Size_lin, NbCandies);
        break;
    case 4: //retour
        ClearBuf();
        ClearScreen();
        Jouer(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    }
} // Classique()

/*!
 * \fn void MenuScore(CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores)
 * \brief MenuScore permet de se rentrer au menu des scores pour les différents niveaux
 * \param Grid[out] la grille dans laquelle on va jouer
 * \param Size_col[out] la taille de colonne de la grille
 * \param Size_lin[out] la taille des ligne de la grille
 * \param NbCandies[out] le nombre de chiffre différent max
 * \param Coup[out] le nombre de coup qu'aura l'utilisateur
 * \param LvlScores[out] Fichier score associé au mode de jeu
 */
void MenuScore(CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned & ScoreToWin)
{
    ClearScreen();
    DisplayFile  ("../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/menus_txt/menuscore.txt");
    unsigned choix = GetUnsigned (1,7);
    ClearScreen();
    string File;
    switch (choix)
    {
    case 1:
        File="difficile.score";
        AfficheScores(Key,File);       //Tableau des scores Classique Difficile
        RetourMenu(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    case 2:
        File="lvl1.score";
        AfficheScores(Key,File);            //Tableau des scores Niveau 1
        RetourMenu(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    case 3:
        File="lvl2.score";
        AfficheScores(Key,File);            //Tableau des scores Niveau 2
        RetourMenu(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    case 4:
        File="lvl3.score";
        AfficheScores(Key,File);            //Tableau des scores Niveau 3
        RetourMenu(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    case 5:
        File="lvl4.score";
        AfficheScores(Key,File);            //Tableau des scores Niveau 4
        RetourMenu(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    case 6:
        File="lvl5.score";
        AfficheScores(Key,File);            //Tableau des scores Niveau 5
        RetourMenu(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    case 7:
        Menu2(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    }

} // MenuScore()

void Menu2 (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned & ScoreToWin)
{
    ClearScreen();
    DisplayFile  ("../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/menus_txt/menu.txt");
    unsigned choix = GetUnsigned (1,5);
    ClearScreen();
    ClearBuf();
    switch (choix)
    {
    case 1:
        Jouer(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    case 2:
        DisplayFile("../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/menus_txt/regles.txt");
        RetourMenu(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    case 3:
        MenuScore(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    case 4:
        DisplayFile("../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/menus_txt/credits.txt");
        RetourMenu(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
        break;
    case 5:
        exit(0);
        break;
    }
} // Menu2()

void RetourMenu (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned & ScoreToWin)
{
    char retour;
    cout <<"Entrez Q pour retourner au menu" << endl;
    while (true)
    {
        cin >> retour;
        ClearBuf ();
        if (toupper(retour) == 'Q')
        {
            Menu2(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);
            break;
        }
    }
} // RetourMenu()

void RetrieveDataLevel(const string & NameLevel, vector <vector <unsigned>> & Grid, unsigned  & NbCandies, unsigned & Coup, unsigned & ScoreToWin)
{
    ifstream ifs;
    bool check=true;
    while(check)
    {
        string FichierSource=NameLevel;
        unsigned Cpt(3);
        while(Cpt != 0)
        {
            ifs.open(FichierSource);
            if(!ifs.fail()) break;
            --Cpt;
        }
        if(Cpt==0)
        {
            cout << "3 échecs d'ouverture de fichier en lecture" << endl;
            break;
        }
        unsigned Instance = 0;
        int cpt = -1;
        while(!ifs.eof())
        {
            string Str;
            getline(ifs,Str);

            if(Instance == 0)
            {
                int Size = stoi(Str);
                Grid.resize(Size);
                for(unsigned i = 0; i < Grid.size() ; ++i)
                {
                    Grid[i].resize(Size);
                }
                Instance = 1;
            }
            else if(Instance == 1)
            {
                NbCandies = stoi(Str);
                Instance = 2;
            }
            else if(Instance == 2)
            {
                Coup = stoi(Str);
                Instance = 3;
            }
            else if(Instance == 3)
            {
                ScoreToWin = stoi(Str);
                Instance = 4;
            }
            else
            {
                ++cpt;
                for(unsigned i = 0; i < Str.size() ; ++i)
                {

                    if(Str[i] == '1')
                    {
                        Grid[cpt][i] = 12;
                    }
                    else
                    {
                        Grid[cpt][i]=0;
                    }
                }
            }

        }
        check=false;
    }
} // RetrieveDataLevel()
  // CreerNiveauAPartirTxt

void LoadLevel (const string & NameLevel, CMat & Grid, unsigned & NbCandies, unsigned & Coup, unsigned & Size_col, unsigned & Size_lin, unsigned & ScoreToWin)
{
    ClearScreen();
    RetrieveDataLevel (NameLevel, Grid, NbCandies, Coup, ScoreToWin);
    Size_col = Grid.size();
    Size_lin = Grid.size();
    ReplaceEmpty (Grid, NbCandies, false);
    ClearAssociation (Grid, NbCandies);

} // LoadLevel()


void LoadLevelCreated(CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned & ScoreToWin)
{
        ifstream ifsFichier;
        string FichierSource;
        unsigned Cpt(3);
        while(Cpt != 0)
        {
            cout << "Entrez le nom de votre level" << endl << endl;
            getline(cin, FichierSource);
            FichierSource = "../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/niveaux_cree/" + FichierSource;
            ifsFichier.open(FichierSource);
            if(!ifsFichier.fail()) break;
            {
                --Cpt;
            }
        }
        if(Cpt==0)
        {
            cout << "Le fichier n'a pas été trouvé" << endl;
            RetourMenu(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);

        }
        else
        {
            cout << FichierSource;
            cout << "chargement du niveau";
            LoadLevel(FichierSource, Grid, NbCandies, Coup, Size_col, Size_lin, ScoreToWin);
            cout << "apres load level";
        }
}// LoadLevelCreated()
