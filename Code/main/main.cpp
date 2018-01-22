#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <limits>
#include <scores.h>

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
void InitGrid (CMat & Grid, unsigned Size, unsigned KNbCandies);                        //Initialise la grille sans combinaison

void DisplayGrid (const CMat & Grid);                                                   //Affiche la grille
void MakeAMove (CMat & Grid, unsigned & Score);                                         //Donne la possibilité au joueur de faire un move
void Move (CMat & Grid, unsigned & Score, const CPosition & Pos, const CPosition & PosToMove);                          //

bool AtLeastThreeInAColumn  (const CMat & Grid, CPosition & Pos, unsigned & Howmany);   //Permet de trouver une combinaison de Howmany en colonnes
bool AtLeastThreeInARow  (const CMat & Grid, CPosition & Pos, unsigned & Howmany);      //Permet de trouver une combinaison de Howmany en lignes
void RemovalInColumn (CMat & Grid, const CPosition & Pos, unsigned  Howmany);           //Remplace les combinaisons en colonne par des 0
void RemovalInRow (CMat & Grid, const CPosition & Pos, unsigned  Howmany);              //Remplace les combinaisons en ligne par des 0
void DeleteAllNumber(CMat & Grid, unsigned nbtodelete, unsigned & Score);               //Supprime tout les nbtodelete de la grille
void UpdateGrid (CMat & Grid, CPosition & Pos, unsigned & Score, unsigned KNbCandies);  //Mets à jour la grille en cherchant les combinaisons, remontant les 0 et replacer des cases

bool ReplaceEmpty (CMat & Grid, unsigned KNbCandies);                                   //Remplace les 0 par des nombres aléatoires
void DownGrid (CMat & Grid);                                                            //Fait tomber les cases quand il y a un trou en dessous d'eux

unsigned GetUnsigned (unsigned min, unsigned max);                                      //Recupération d'un unsigned
CPosition GetPos (CPosition & Pos, unsigned Size);
char GetDirection (char Direction);
void Menu (CMat & Grid, unsigned & Size, unsigned & KNbCandies, unsigned & Coup);       //Menu principal
void Jouer (CMat & Grid, unsigned & Size, unsigned & KNbCandies, unsigned & Coup);      //Menu pour choisir son mode de jeu
void Classique (CMat & Grid, unsigned & Size, unsigned & KNbCandies, unsigned & Coup);  //Mode de jeu classique, 3 Levelx de difficultés.
void Perso( CMat & Grid, unsigned & Size, unsigned & KNbCandies, unsigned & Coup);      //Mode de jeu personnalisé, le joueur peut choisir les options de la partie.
void Histoire( CMat & Grid, unsigned & Size, unsigned & KNbCandies, unsigned & Coup);   //Mode histoire avec Level

void Couleur (const string & coul)
{
    cout << "\033[7;" << coul <<"m";
} // Couleur()

void ClearScreen ()
{
    cout << "\033[H\033[2J";
} // ClearScreen ()

void InitGrid (CMat & Grid, unsigned Size, unsigned KNbCandies)
{
    Grid.resize (Size, vector <unsigned> (Size));
    srand(time(NULL));
    for (unsigned i (0); i < Grid.size(); ++i)
    {
        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            Grid [i][j] = rand()%KNbCandies+1;
        }
    }
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
    } while (ReplaceEmpty(Grid, KNbCandies));
} // InitGrid ()

bool ReplaceEmpty (CMat & Grid, unsigned KNbCandies)
{
    srand(time(NULL));
    bool check = false;
    for (unsigned i (0); i < Grid.size(); ++i)
    {
        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            if (Grid [i][j] == 0)
            {
                Grid [i][j] = rand()%KNbCandies+1;
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
                   PosToMove.first = Pos.first+1;
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
                while (i + Howmany < Grid.size() && Grid[i][j] == Grid[i][j  + Howmany])
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
    Score += cpt*50;
} //DeleteAllNumber ()

/*void DeleteCross (CMat & Grid, const CPosition & Pos)
{
    for(unsigned i=0; i < 5; ++i)
    {
        if((Pos.first - 2 + i) >= 0 && (Pos.first - 2 + i) < (Grid.size()))
        {
            Grid[Pos.first-2+i][Pos.second]=0;
        }
    }
    for(unsigned i=0; i < 5; ++i)
    {
        if((Pos.second - 2 + i) >= 0 && (Pos.second - 2 + i) < (Grid.size()))
        {
            Grid[Pos.first][Pos.second-2+i]=0;
        }
    }
    DisplayGrid (Grid);
} //DeleteCross () */

void UpdateGrid (CMat & Grid, CPosition & Pos, unsigned & Score, unsigned KNbCandies)
{
    unsigned Howmany;
    do
    {
        while (AtLeastThreeInAColumn (Grid, Pos, Howmany))
        {
            cout << "Une combinaison de " << Howmany << " bonbons a ete trouve dans les colonnes en coordonnées " << Pos.first+1 << " ; " << Pos.second+1  << endl;
            Score += Howmany*50;  //50 points par case détruite

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
            Score += Howmany*50; //50 points par case détruite

            if (Howmany == 5)
                FiveInRow (Grid, Pos, Howmany);         //Fait spawn boule spéciale
            if (Howmany != 5)
                RemovalInRow (Grid, Pos, Howmany);      //REMPLACE PAR DES 0

            DisplayGrid (Grid);
            sleep(1);
            DownGrid (Grid);                            //REMONTE LES 0
        }
    }  while (ReplaceEmpty (Grid, KNbCandies));
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

void Level1(CMat & Grid, unsigned & KNbCandies)
{
    KNbCandies = 7;
    InitGrid(Grid, 10, KNbCandies);
    for(unsigned i=0; i<5 ;++i)
    {
        Grid[i][0]=12;
        Grid[i][Grid.size()-1]=12;
    }
    for(unsigned i=0; i<5 ;++i)
    {
        for(unsigned j=0 ; j<=i ; ++j)
        {
            Grid[5+i][j]=12;
        }
    }
    for(unsigned i=0; i<5 ;++i)
    {
        for(unsigned j=0 ; j<=i ; ++j)
        {
            Grid[5+i][(Grid.size()-1)-j]=12;
        }
    }
} //Level1()

void Level2(CMat & Grid, unsigned & KNbCandies)
{
    KNbCandies = 7;
    InitGrid(Grid, 10, KNbCandies);

    for(unsigned i=0; i <= 5; ++i)
    {
        for(unsigned j = i; j <= Grid.size()-1-i; ++j)
        {
            Grid[Grid.size()-1-i][j] = 12;
        }
    }
    for(unsigned i=0; i < 3; ++i)
    {
        Grid[2+i][4] = 12;
         Grid[2+i][5] = 12;
    }
} //Level2()

void Level3(CMat & Grid, unsigned & KNbCandies)
{
    KNbCandies = 7;
    InitGrid(Grid, 15, KNbCandies);

    for(unsigned i =0; i < 12; ++i)
    {
        Grid[Grid.size()-1-i][11] = 12;
        Grid[Grid.size()-1-i][7] = 12;
        Grid[Grid.size()-1-i][3] = 12;
    }
} //Level3()

void Level4(CMat & Grid, unsigned & KNbCandies)
{
    KNbCandies = 7;
    InitGrid(Grid, 20, KNbCandies);

    for(unsigned i=0; i < 3 ; ++i)
    {
        for(unsigned j=i ; j < 5-i ; ++j)
        {
            Grid[Grid.size()-1-i][j]=12;
            Grid[Grid.size()-1-i][5+j]=12;
            Grid[Grid.size()-1-i][10+j]=12;
            Grid[Grid.size()-1-i][15+j]=12;

        }
    }
} //Level4()

void Level5(CMat & Grid, unsigned & KNbCandies)
{
    KNbCandies = 7;
    InitGrid(Grid, 20, KNbCandies);

    for(unsigned i=0; i < 3 ; ++i)
    {
        for(unsigned j=i ; j < 5-i ; ++j)
        {
            Grid[Grid.size()-1-i][j]=12;


            Grid[Grid.size()-1-i][15+j]=12;

        }
    }
    for(unsigned i=0; i < 15 ; ++i )
    {
       Grid[Grid.size()-1-i][5]=12;
       Grid[Grid.size()-1-i][14]=12;
    }
} //Level5()

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
}

CPosition GetPos(CPosition & Pos, unsigned Size)
{
    cout << "Numéro colonne (1 - " << Size << ") : ";
    Pos.second = (GetUnsigned(1,Size) - 1);
    cout << "Numéro ligne (1 - " << Size << ") : ";
    Pos.first = (GetUnsigned(1,Size) - 1);
    return Pos;
}

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
}

void Menu (CMat & Grid, unsigned & Size, unsigned & KNbCandies, unsigned & Coup)
{
    ClearScreen();
    DisplayFile  ("menu.txt");
    unsigned choix = GetUnsigned (1,5);
    switch (choix)
    {
        case 1:
            ClearScreen();
            ClearBuf();
            Jouer(Grid, Size, KNbCandies, Coup);
            break;
        case 2: //A faire
            cout << "Options" << endl;
            break;
        case 3:
            ClearScreen();
            DisplayFile("regles.txt");
            char quit;

            cout <<"Entrez Q pour quitter" << endl;
            while (true)
            {
                cin>> quit;
                ClearBuf ();
                if (quit == 'Q' || quit == 'q')
                    Menu(Grid, Size, KNbCandies, Coup);
            }
            break;
        case 4:
            ClearScreen();
            AfficheScores(Key);
            break;
        case 5:
            exit(0);
            break;
    }
} //Menu ()

void Jouer (CMat & Grid, unsigned & Size, unsigned & KNbCandies, unsigned & Coup)
{
    ClearScreen();
    DisplayFile  ("jouer.txt");
    unsigned choix = GetUnsigned (1,4);
    switch (choix)
    {
        case 1:
            ClearScreen();
            ClearBuf();
            Classique(Grid, Size, KNbCandies, Coup);
            break;
        case 2:
            ClearScreen();
            ClearBuf();
            Perso(Grid, Size, KNbCandies, Coup);
            break;
        case 3:
            ClearScreen();
            ClearBuf();
            Histoire(Grid, Size, KNbCandies, Coup);
            break;
        case 4:
            ClearScreen();
            ClearBuf ();
            Menu(Grid, Size, KNbCandies, Coup);
            break;
    }
}// Jouer ()

void Classique (CMat & Grid, unsigned & Size, unsigned & KNbCandies, unsigned & Coup)
{
    ClearScreen();
    DisplayFile  ("classique.txt");
    unsigned choix = GetUnsigned (1,4);
    switch (choix)
    {
        case 1: //facile
            Size = 10;
            KNbCandies = 5;
            Coup = 20;
            InitGrid (Grid, Size, KNbCandies);
            break;
        case 2: //normal
            Size = 8;
            KNbCandies = 6;
            Coup = 15;
            InitGrid (Grid, Size, KNbCandies);
            break;
        case 3: //difficile
            Size = 6;
            KNbCandies = 8;
            Coup = 2;
            InitGrid (Grid, Size, KNbCandies);
            break;
        case 4: //retour
            Jouer(Grid, Size, KNbCandies, Coup);
            break;
    }
}// Classique ()

void Perso (CMat & Grid, unsigned & Size, unsigned & KNbCandies, unsigned & Coup)
{
    ClearScreen();
    DisplayFile  ("perso.txt");

    cout << "Taille de la grille (5 - 30) : ";
    Size = GetUnsigned (5,30);

    cout << "Numero de bonbon max (4 - 9) : ";
    KNbCandies = GetUnsigned (4,9);

    cout << "Nombre de coup max (1 - 100) : ";
    Coup = GetUnsigned (1,100);

    InitGrid (Grid, Size, KNbCandies);
} //Perso ()

void Histoire(CMat & Grid, unsigned & Size, unsigned & KNbCandies, unsigned & Coup)
{
    ClearScreen();
    DisplayFile  ("histoire.txt");
    unsigned choix = GetUnsigned (1,6);

    switch (choix)
    {
        case 1:
            ClearScreen();
            ClearBuf();
            Level1(Grid, KNbCandies);
            break;

        case 2:
            ClearScreen();
            ClearBuf();
            Level2(Grid, KNbCandies);
            break;

        case 3:
            ClearScreen();
            ClearBuf();
            Level3(Grid, KNbCandies);
            break;

        case 4:
            ClearScreen();
            ClearBuf ();
            Level4(Grid, KNbCandies);
            break;

        case 5:
            ClearScreen();
            ClearBuf();
            Level5(Grid, KNbCandies);
            break;
        case 6:
            ClearScreen();
            ClearBuf ();
            Jouer(Grid, Size, KNbCandies, Coup);
            break;
    }
} //Histoire()

int main()
{
    CPosition Pos;
    unsigned Score = 0;     //Score

    unsigned Size;          //Taille de la grille
    unsigned KNbCandies;    //Numéro max dans la grille
    unsigned Coup;          //Nombre de coups max

    while (true)
    {
        CMat Grid;
        Menu(Grid, Size, KNbCandies, Coup);
        for ( ; Coup != 0 ; Coup--)
        {
            ClearScreen();
            DisplayGrid (Grid);
            cout << "Il vous reste " << Coup << " coup(s) !" << endl
                 << "Score actuel : " << Score << endl << endl;

            MakeAMove (Grid, Score);

            DisplayGrid (Grid);
            sleep(1);

            UpdateGrid (Grid, Pos, Score, KNbCandies);
        }
        DisplayGrid (Grid);
        cout << "Partie termine !" << endl
             << "Vous avez realise un score de " << Score << " !" << endl << endl ;

        //NICO IL FAUDRAIT METTRE ÇA DANS UNE FONCTION STP
        /*
        cout << "Pour sauvegarder votre score, entrez votre nom : " << endl;
        string Name;
        cin >> Name;
        bool NoAccent = true;
        while(Name.size()>11)
        {
            cout << "Votre nom est trop long (11 caractères maximum) !" << endl;
            cout << "Pour sauvegarder votre score, entrez votre nom : " << endl;
            cin >> Name;
            for(unsigned i(0); i < Name.size() ; ++i)
            {
                if(!isalpha(Name[i]))
                    NoAccent = false;
            }
            while(!NoAccent)
            {
                NoAccent=true;
                for(unsigned i(0); i < Name.size() ; ++i)
                {
                    if(!isalpha(Name[i]))
                        NoAccent = false;
                }
                if(!NoAccent)
                {
                    cout << "Votre nom comporte des accents ou des chiffres !" << endl;
                    cout << "Pour sauvegarder votre score, entrez votre nom : " << endl;
                    cin >> Name;
                }
            }
        }

        MScores(Name,Score, Key);
        */

        cout <<"Entrez Q pour retourner au menu." << endl;
        while (true)
        {
            char quit='h';
            cin >> quit;
            if (quit == 'Q' || quit == 'q')
            {
                ClearScreen();
                ClearBuf();
                break;
            }
        }
    }
} //main()
