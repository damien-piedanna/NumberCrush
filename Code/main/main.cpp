#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <limits>
#include <Scores.h>

using namespace std;

typedef vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMat; // un type représentant la grille
typedef pair <unsigned, unsigned> CPosition; // une position dans la girlle

const string CReset   ("0");

//ATTENTION !!!!!!!!
const unsigned Key(5); // Clé de chiffrement/déchiffrement par César
//AAAAAHHHH !!!!!!!!

void Couleur (const string & coul);                                                     //Permet d'afficher des couleurs sur la console
void ClearScreen ();                                                                    //Vide la console
void ClearBuf ();                                                                       //Vide le tampon de cin
void InitGrid (CMat & Grid, unsigned Size, unsigned NbCandies);                        //Initialise la grille sans combinaison

void DisplayGrid (const CMat & Grid);                                                   //Affiche la grille
void MakeAMove (CMat & Grid, unsigned & Score);                                         //Donne la possibilité au joueur de faire un move
void Move (CMat & Grid, unsigned & Score, const CPosition & Pos, const CPosition & PosToMove);                          //

bool AtLeastThreeInAColumn  (const CMat & Grid, CPosition & Pos, unsigned & Howmany);   //Permet de trouver une combinaison de Howmany en colonnes
bool AtLeastThreeInARow  (const CMat & Grid, CPosition & Pos, unsigned & Howmany);      //Permet de trouver une combinaison de Howmany en lignes
void RemovalInColumn (CMat & Grid, const CPosition & Pos, unsigned  Howmany);           //Remplace les combinaisons en colonne par des 0
void RemovalInRow (CMat & Grid, const CPosition & Pos, unsigned  Howmany);              //Remplace les combinaisons en ligne par des 0
void DeleteAllNumber(CMat & Grid, unsigned nbtodelete, unsigned & Score);               //Supprime tout les nbtodelete de la grille
void UpdateGrid (CMat & Grid, CPosition & Pos, unsigned & Score, unsigned NbCandies);  //Mets à jour la grille en cherchant les combinaisons, remontant les 0 et replacer des cases

void ClearAssociation (CMat & Grid, unsigned NbCandies);                               //Supprime les combinaisons de la grille sans ajouter de score
bool ReplaceEmpty (CMat & Grid, unsigned NbCandies);                                   //Remplace les 0 par des nombres aléatoires
void DownGrid (CMat & Grid);                                                            //Fait tomber les cases quand il y a un trou en dessous d'eux

unsigned GetUnsigned (unsigned min, unsigned max);                                      //Recupération d'un unsigned
CPosition GetPos (CPosition & Pos, unsigned Size);                                      //Récupération positions
char GetDirection (char Direction);                                                     //Récupération direction
void Menu (CMat & Grid, unsigned & Size, unsigned & NbCandies, unsigned & Coup);       //Menu principal
void Jouer (CMat & Grid, unsigned & Size, unsigned & NbCandies, unsigned & Coup);      //Menu pour choisir son mode de jeu
void Classique (CMat & Grid, unsigned & Size, unsigned & NbCandies, unsigned & Coup);  //Mode de jeu classique, 3 Levelx de difficultés.
void Perso( CMat & Grid, unsigned & Size, unsigned & NbCandies, unsigned & Coup);      //Mode de jeu personnalisé, le joueur peut choisir les options de la partie.

void RetrieveDataLevel(const string & NameLevel, vector <vector <unsigned>> & Grid, unsigned & NbCandies, unsigned & Coup);
void LoadLevel (const string & NameLevel, CMat & Grid, unsigned & NbCandies, unsigned & Coup, unsigned & Size);
void Histoire( CMat & Grid, unsigned & Size, unsigned & NbCandies, unsigned & Coup);   //Mode histoire avec Level

void PlayGame (CMat & Grid, CPosition Pos, unsigned & Score, unsigned & NbCandies, unsigned & Coup);  //Lance la partie jusqu'à qu'il n'y ai plus de coups

void Couleur (const string & coul)
{
    cout << "\033[7;" << coul <<"m";
} // Couleur()

void ClearScreen ()
{
    cout << "\033[H\033[2J";
} // ClearScreen ()

void InitGrid (CMat & Grid, unsigned Size, unsigned NbCandies)
{
    Grid.resize (Size, vector <unsigned> (Size));
    srand(time(NULL));
    for (unsigned i (0); i < Grid.size(); ++i)
    {
        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            Grid [i][j] = rand()%NbCandies+1;
        }
    }
    ClearAssociation (Grid, NbCandies);
} // InitGrid ()

void ClearAssociation (CMat & Grid, unsigned NbCandies)
{
    CPosition Pos;
    unsigned Howmany;
    do
    {
        while (AtLeastThreeInAColumn (Grid, Pos, Howmany))
        {
            RemovalInColumn (Grid, Pos, Howmany);
        }
        while (AtLeastThreeInARow  (Grid, Pos, Howmany))
        {
            RemovalInRow (Grid, Pos, Howmany);
        }
    } while (ReplaceEmpty(Grid, NbCandies));
}

bool ReplaceEmpty (CMat & Grid, unsigned NbCandies)
{
    srand(time(NULL));
    bool check = false;
    for (unsigned i (0); i < Grid.size(); ++i)
    {
        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            if (Grid [i][j] == 0)
            {
                Grid [i][j] = rand()%NbCandies+1;
                //cout << "remplacement de la case" << i+1 << j+1 << endl;
                check = true;
            }

        }
    }
    return check;
} // ReplaceEmpty ()

void DisplayGrid (const CMat & Grid)
{
    ClearScreen ();
    Couleur(CReset);
    unsigned line = 1;
    unsigned columns = 1;
    cout << "  ";
    while (columns <= Grid.size())
    {
        cout << columns;
        if (columns <= 9)
            cout << ' ';
        ++columns;
    }
    cout << endl;
    for (unsigned i (0); i < Grid.size(); ++i)
    {
        Couleur(CReset);
        cout << line;
        if (line <= 9)
            cout << ' ';
        ++line;
        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            Couleur (to_string(Grid [i][j] + 29));
            if (Grid [i][j] == 0) //cases vides
                Couleur(CReset);
            if (Grid [i][j] == 11) //boules spéciales
            {
                Couleur(CReset);
                cout << "()";
            }
            if (Grid [i][j] == 12) //Mur
            {
                Couleur(CReset);
                cout << "[]";
            }
            if (Grid [i][j] <= 9)
                cout << Grid [i][j] << ' ';
        }
        cout << endl;
    }
    Couleur(CReset);
    cout << endl;
} // DisplayGrid ()

void DownGrid (CMat & Grid)
{
    for (unsigned i (0); i < Grid.size(); ++i)
    {
        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            unsigned ibis = i;
            if (Grid [i][j] == 0)
            {
                while (ibis > 0)
                {
                    swap (Grid[ibis-1][j], Grid[ibis][j]);
                    //cout << "echange de la case" << j+1 << ibis+1 << " avec " <<  j+1 << ibis << endl;
                    ibis--;
                }
            }
        }
    }
} //DownGrid ()

void MakeAMove (CMat & Grid, unsigned & Score)
{
    bool check = false;
    CPosition Pos;
    CPosition PosToMove;
    unsigned Size;
    char Direction;
    Size = Grid.size();
    while (true)
    {
        Pos = GetPos (Pos, Size); //Récupération position
        cout << endl;
        Direction = GetDirection (Direction); //Récupération direction
        switch (Direction)
        {
            case 'Z' :
                if(Pos.first != 0)
                {
                   check = true;
                   PosToMove.first = Pos.first-1;
                   PosToMove.second = Pos.second;
                   Move (Grid, Score, Pos, PosToMove);
                }
            break;
            case 'S' :
                if(Pos.first != Grid.size()-1)
                {
                   check = true;
                   PosToMove.first = Pos.first+1;
                   PosToMove.second = Pos.second;
                   Move (Grid, Score, Pos, PosToMove);
                }

            break;
            case 'D' :
                if(Pos.second != Grid.size()-1)
                {
                   check = true;
                   PosToMove.first = Pos.first;
                   PosToMove.second = Pos.second+1;
                   Move (Grid, Score, Pos, PosToMove);
                }
            break;
            case 'Q' :
                if(Pos.second != 0)
                {
                   check = true;
                   PosToMove.first = Pos.first;
                   PosToMove.second = Pos.second-1;
                   Move (Grid, Score, Pos, PosToMove);
                }
            break;
        }
        ClearBuf();
        if (check) break;
        cout << "Vous ne pouvez pas déplacer un mur." << endl
             << "Vous ne pouvez pas déplacer une case hors de la grille." << endl;
    }
} //MakeAMove()

void Move (CMat & Grid, unsigned & Score, const CPosition & Pos, const CPosition & PosToMove)
{
    if((Grid[PosToMove.first][PosToMove.second] != 0) && (Grid[Pos.first][Pos.second] != 0) //On ne bouge pas un 0
    && (Grid[PosToMove.first][PosToMove.second] != 12) && (Grid[Pos.first][Pos.second] != 12))   //On ne bouge pas un mur
    {
        if (Grid[PosToMove.first][PosToMove.second] == 11)
        {
            Grid[PosToMove.first][PosToMove.second] = 0;
            DeleteAllNumber (Grid, Grid[Pos.first][Pos.second], Score);
        }
        if (Grid[Pos.first][Pos.second] == 11)
        {
            Grid[Pos.first][Pos.second] = 0;
            DeleteAllNumber (Grid, Grid[PosToMove.first][PosToMove.second], Score);
        }
    swap (Grid[PosToMove.first][PosToMove.second], Grid[Pos.first][Pos.second]);
    }
} //Move ()

bool AtLeastThreeInAColumn (const CMat & Grid, CPosition & Pos, unsigned & Howmany)
{
    for (unsigned i (0); i < Grid.size() - 2; ++i)
    {
        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            if (Grid[i][j] != 0 && Grid[i][j] != 12 && Grid[i][j] == Grid [i+1][j] && Grid[i][j] == Grid [i+2][j]) //3 affilés
            {
                Pos.first = j;
                Pos.second = i;
                Howmany = 3;
                while (i + Howmany < Grid.size() && Grid[i][j] == Grid[i + Howmany][j])
                    ++Howmany;
                return true;
            }
        }
    }
    return false;
} //AtLeastThreeInAColumn()

bool AtLeastThreeInARow  (const CMat & Grid, CPosition & Pos, unsigned & Howmany)
{
    for (unsigned i (0); i < Grid.size(); ++i)
    {
        for (unsigned j(0); j < Grid[i].size() - 2; ++j)
        {
            if (Grid[i][j] != 0 && Grid[i][j] != 12 && Grid[i][j] == Grid [i][j+1] && Grid[i][j] == Grid [i][j+2])
            {
                Pos.first = j;
                Pos.second = i;
                Howmany = 3;
                while (j + Howmany < Grid.size() && Grid[i][j] == Grid[i][j  + Howmany])
                    ++Howmany;
                return true;
            }
        }
    }
    return false;
} //AtLeastThreeInARow()

void RemovalInColumn (CMat & Grid, const CPosition & Pos, unsigned  Howmany)
{
    unsigned Cpt = 0;
    while (Cpt != Howmany)
    {

        Grid[Pos.second + Cpt][Pos.first] = 0;
        //cout << "delete de la case" << Pos.first + 1 << Pos.second + Cpt + 1 << endl;
        Cpt++;
    }
} //RemovalInColumn()

void RemovalInRow (CMat & Grid, const CPosition & Pos, unsigned  Howmany)
{
    unsigned Cpt = 0;
    while (Cpt != Howmany)
    {
        Grid[Pos.second][Pos.first + Cpt] = 0;
        //cout << "delete de la case" << Pos.first + Cpt + 1 << Pos.second + 1 << endl;
        Cpt++;
    }
} //RemovalInRow()

void FiveInColumn (CMat & Grid, const CPosition & Pos, unsigned  Howmany)
{
    unsigned Cpt = 0;
    while (Cpt != Howmany)
    {
        Grid[Pos.second][Pos.first] = 0;
        Grid[Pos.second + 1][Pos.first] = 0;
        Grid[Pos.second + 2][Pos.first] = 11;
        Grid[Pos.second + 3][Pos.first] = 0;
        Grid[Pos.second + 4][Pos.first] = 0;
        Cpt++;
    }
} //FiveInColumn()

void FiveInRow (CMat & Grid, const CPosition & Pos, unsigned  Howmany)
{
    unsigned Cpt = 0;
    while (Cpt != Howmany)
    {
        Grid[Pos.second][Pos.first] = 0;
        Grid[Pos.second][Pos.first + 1] = 0;
        Grid[Pos.second][Pos.first + 2] = 11;
        Grid[Pos.second][Pos.first + 3] = 0;
        Grid[Pos.second][Pos.first + 4] = 0;
        Cpt++;
    }
} //FiveInRow()

void DeleteAllNumber (CMat & Grid, unsigned nbtodelete, unsigned & Score)
{
    unsigned cpt;
    for (unsigned i (0); i < Grid.size(); ++i)
    {
        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            if (Grid[i][j] == nbtodelete)
            {
                Grid[i][j] = 0;
                cpt++;
            }
        }
    }
    Score += cpt*5;
} //DeleteAllNumber ()
/*
void DeleteCross (CMat & Grid, const CPosition & Pos)
{
    for(unsigned i=0; i < Grid.Size(); ++i)
    {
        if((Pos.first - 2 + i) >= 0 && (Pos.first - 2 + i) < (Grid.size()))
        {
            Grid[Pos.first-2+i][Pos.second]=0;
        }
    }
    for(unsigned i=0; i < Grid.Size(); ++i)
    {
        if((Pos.second - 2 + i) >= 0 && (Pos.second - 2 + i) < (Grid.size()))
        {
            Grid[Pos.first][Pos.second-2+i]=0;
        }
    }
    DisplayGrid (Grid);
} //DeleteCross () */

void UpdateGrid (CMat & Grid, CPosition & Pos, unsigned & Score, unsigned NbCandies)
{
    unsigned Howmany;
    do
    {
        while (AtLeastThreeInAColumn (Grid, Pos, Howmany))
        {
            cout << "Une combinaison de " << Howmany << " bonbons a ete trouve dans les colonnes en coordonnées " << Pos.first+1 << " ; " << Pos.second+1  << endl;
            Score += Howmany*5;  //50 points par case détruite

            if (Howmany == 5)
                FiveInColumn (Grid, Pos, Howmany);      //Fait spawn boule spéciale
            if (Howmany != 5)
                RemovalInColumn (Grid, Pos, Howmany);   //REMPLACE PAR DES 0

            DisplayGrid (Grid);
            sleep(1);
            DownGrid (Grid);                            //REMONTE LES 0
        }
        while (AtLeastThreeInARow  (Grid, Pos, Howmany))
        {
            cout << "Une combinaison de " << Howmany << " bonbons a ete trouve dans les lignes en coordonnées " << Pos.first+1 << " ; " << Pos.second+1  << endl;
            Score += Howmany*5; //50 points par case détruite

            if (Howmany == 5)
                FiveInRow (Grid, Pos, Howmany);         //Fait spawn boule spéciale
            if (Howmany != 5)
                RemovalInRow (Grid, Pos, Howmany);      //REMPLACE PAR DES 0

            DisplayGrid (Grid);
            sleep(1);
            DownGrid (Grid);                            //REMONTE LES 0
        }
    }  while (ReplaceEmpty (Grid, NbCandies));
}

void DisplayFile (const string & File)
{
    ifstream ifs;
    ifs.open (File);
    if (!(ifs.is_open ())) //si le fichier n'a pas pu être ouvert
    {
        if (File == "menu.txt")
        {
            cout << "Menu" << endl
                 << "1 - Jouer" << endl
                 << "2 - Options" << endl
                 << "3 - Règles" << endl
                 << "4 - Quitter" << endl;
            return;
        }
        if (File == "jouer.txt")
        {
            cout << "Menu" << endl
                 << "1 - Classique" << endl
                 << "2 - Perso" << endl
                 << "3 - Montre" << endl
                 << "4 - Retour" << endl;
            return;
        }
        if (File == "classique.txt")
        {
            cout << "Menu" << endl
                 << "1 - Facile" << endl
                 << "2 - Moyen" << endl
                 << "3 - Difficile" << endl
                 << "4 - Retour" << endl;
            return;
        }
    }
    string str;
    while (!(ifs.eof()))
    {
        getline (ifs, str);
        cout << str << endl;
    }
}// DisplayFile ()

void ClearBuf ()
{
    cin.clear ();
    cin.ignore (numeric_limits<streamsize>::max(), '\n');

}// ClearBuf ()

void RetrieveDataLevel(const string & NameLevel, vector <vector <unsigned>> & Grid, unsigned  & NbCandies, unsigned & Coup)
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
} //RetrieveDataLevel()

void LoadLevel (const string & NameLevel, CMat & Grid, unsigned & NbCandies, unsigned & Coup, unsigned & Size)
{
    ClearScreen();
    ClearBuf();
    RetrieveDataLevel(NameLevel, Grid, NbCandies, Coup);
    Size = Grid.size();
    ReplaceEmpty(Grid, NbCandies);
    ClearAssociation (Grid, NbCandies);
} //LoadLevel()

unsigned GetUnsigned (unsigned min, unsigned max)
{
    unsigned choix = 0;
    while (true)
    {
        cin >> choix;
        if (cin.fail() || choix > max || choix < min)
        {
            cout << "Valeur incorrecte ("<< min << '-' << max << ')' << endl << endl;
            ClearBuf();
            continue;
        }
        break;
    }
    return choix;
} //GetUnsigned()

CPosition GetPos(CPosition & Pos, unsigned Size)
{
    cout << "Numéro colonne (1 - " << Size << ") : ";
    Pos.second = (GetUnsigned(1,Size) - 1);
    cout << "Numéro ligne (1 - " << Size << ") : ";
    Pos.first = (GetUnsigned(1,Size) - 1);
    return Pos;
} //GetPos()

char GetDirection (char Direction)
{
    while (true)
    {
        cout << "Direction (Z,Q,S,D) : ";
        cin >> Direction;
        cout << endl;
        Direction = toupper(Direction);
        if (Direction == 'Z' || Direction == 'Q' || Direction == 'S' || Direction == 'D') break;
        ClearBuf ();
    }
    return Direction;
} //GetDirection()

void Menu (CMat & Grid, unsigned & Size, unsigned & NbCandies, unsigned & Coup)
{
    ClearScreen();
    DisplayFile  ("menu.txt");
    unsigned choix = GetUnsigned (1,5);
    switch (choix)
    {
        case 1:
            ClearScreen();
            ClearBuf();
            Jouer(Grid, Size, NbCandies, Coup);
            break;
        case 2: //A faire
            cout << "Options" << endl;
            break;
        case 3:
            ClearScreen();
            DisplayFile("regles.txt");
            char quitregles;
            cout <<"Entrez R pour retourner au menu" << endl;
            while (true)
            {
                cin>> quitregles;
                ClearBuf ();
                if (toupper(quitregles) == 'Q')
                    Menu(Grid, Size, NbCandies, Coup);
            }
            break;
        case 4:
            ClearScreen();
            AfficheScores(Key);
            char quitscores;
            cout << "Entrez R pour retourner au menu" << endl;
            while (true)
            {
                cin>> quitscores;
                ClearBuf ();
                if (toupper(quitscores) == 'Q')
                    Menu(Grid, Size, NbCandies, Coup);
            }
            break;
            break;
        case 5:
            exit(0);
            break;
    }
} //Menu ()

void Jouer (CMat & Grid, unsigned & Size, unsigned & NbCandies, unsigned & Coup)
{
    ClearScreen();
    DisplayFile  ("jouer.txt");
    unsigned choix = GetUnsigned (1,4);
    switch (choix)
    {
        case 1:
            ClearScreen();
            ClearBuf();
            Classique(Grid, Size, NbCandies, Coup);
            break;
        case 2:
            ClearScreen();
            ClearBuf();
            Perso(Grid, Size, NbCandies, Coup);
            break;
        case 3:
            ClearScreen();
            ClearBuf();
            Histoire(Grid, Size, NbCandies, Coup);
            break;
        case 4:
            ClearScreen();
            ClearBuf ();
            Menu(Grid, Size, NbCandies, Coup);
            break;
    }
}// Jouer ()

void Classique (CMat & Grid, unsigned & Size, unsigned & NbCandies, unsigned & Coup)
{
    ClearScreen();
    DisplayFile  ("classique.txt");
    unsigned choix = GetUnsigned (1,4);
    switch (choix)
    {
        case 1: //facile
            Size = 10;
            NbCandies = 5;
            Coup = 20;
            InitGrid (Grid, Size, NbCandies);
            break;
        case 2: //normal
            Size = 8;
            NbCandies = 6;
            Coup = 15;
            InitGrid (Grid, Size, NbCandies);
            break;
        case 3: //difficile
            Size = 6;
            NbCandies = 8;
            Coup = 2;
            InitGrid (Grid, Size, NbCandies);
            break;
        case 4: //retour
            Jouer(Grid, Size, NbCandies, Coup);
            break;
    }
}// Classique ()

void Perso (CMat & Grid, unsigned & Size, unsigned & NbCandies, unsigned & Coup)
{
    ClearScreen();
    DisplayFile  ("perso.txt");

    cout << "Taille de la grille (5 - 30) : ";
    Size = GetUnsigned (5,30);

    cout << "Numero de bonbon max (4 - 9) : ";
    NbCandies = GetUnsigned (4,9);

    cout << "Nombre de coup max (1 - 100) : ";
    Coup = GetUnsigned (1,100);

    InitGrid (Grid, Size, NbCandies);
} //Perso ()

void Histoire(CMat & Grid, unsigned & Size, unsigned & NbCandies, unsigned & Coup)
{
    ClearScreen();
    DisplayFile  ("histoire.txt");
    unsigned choix = GetUnsigned (1,6);

    switch (choix)
    {
        case 1:
            LoadLevel ("Level1.txt", Grid, NbCandies, Coup, Size);
            break;
        case 2:
            LoadLevel ("Level2.txt", Grid, NbCandies, Coup, Size);
            break;
        case 3:
            LoadLevel ("Leve3.txt", Grid, NbCandies, Coup, Size);
            break;
        case 4:
            LoadLevel ("Level4.txt", Grid, NbCandies, Coup, Size);
            break;
        case 5:
            LoadLevel ("Level5.txt", Grid, NbCandies, Coup, Size);
            break;
        case 6:
            ClearScreen();
            ClearBuf ();
            Jouer(Grid, Size, NbCandies, Coup);
            break;
    }
} //Histoire()

void PlayGame (CMat & Grid, CPosition Pos, unsigned & Score, unsigned & NbCandies, unsigned & Coup)
{
    for ( ; Coup != 0 ; Coup--)
    {
        ClearScreen();
        DisplayGrid (Grid);
        cout << "Il vous reste " << Coup << " coup(s) !" << endl
             << "Score actuel : " << Score << endl << endl;

        MakeAMove (Grid, Score);

        DisplayGrid (Grid);
        sleep(1);

        UpdateGrid (Grid, Pos, Score, NbCandies);
    }
    DisplayGrid (Grid);
    cout << "Partie termine !" << endl
         << "Vous avez realise un score de " << Score << " !" << endl << endl ;
}

int main()
{
    CPosition Pos;
    unsigned Score = 0;     //Score

    unsigned Size;          //Taille de la grille
    unsigned NbCandies;    //Numéro max dans la grille
    unsigned Coup;          //Nombre de coups max

    while (true)
    {
        CMat Grid;
        Menu(Grid, Size, NbCandies, Coup);

        PlayGame (Grid, Pos, Score, NbCandies, Coup);

        SaveScores(Score, Key);

        cout << "Entrez Q pour retourner au menu." << endl;
        char quit;
        while (true)
        {
            cin >> quit;
            ClearBuf ();
            if (toupper(quit) == 'Q')
               break;
        }
    }
} //main()
