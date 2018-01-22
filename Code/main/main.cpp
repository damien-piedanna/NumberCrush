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
unsigned Size = 0;        //taille de la grille
unsigned KNbCandies = 0;  //numéro max dans la grille
unsigned Coup = 0;        //nombre de coups max
unsigned chlvl = 0;       //niveau

//ATTENTION !!!!!!!!
const unsigned Key(5); // Clé de chiffrement/déchiffrement par César
//AAAAAHHHH !!!!!!!!

void Couleur (const string & coul);                                                     //Permet d'afficher des couleurs sur la console
void ClearScreen ();                                                                    //Vide la console
void ClearBuf ();                                                                       //Vide le tampon de cin
void InitGrid (CMat & Grid, unsigned Size, unsigned KNbCandies);                        //Initialise la grille sans combinaison
bool ReplaceEmpty (CMat & Grid, unsigned KNbCandies);                                   //Remplace les 0 par des nombres aléatoires
void DisplayGrid (const CMat & Grid);                                                   //Affiche la grille
void DownGrid (CMat & Grid);                                                            //Fait tomber les cases quand il y a un trou en dessous d'eux
void MakeAMove (CMat & Grid, const CPosition & Pos, char Direction);                    //Permet d'effectuer un mouvement de case
bool AtLeastThreeInAColumn  (const CMat & Grid, CPosition & Pos, unsigned & Howmany);   //Permet de trouver une combinaison de Howmany en colonnes
bool AtLeastThreeInARow  (const CMat & Grid, CPosition & Pos, unsigned & Howmany);      //Permet de trouver une combinaison de Howmany en lignes
void RemovalInColumn (CMat & Grid, const CPosition & Pos, unsigned  Howmany);           //Remplace les combinaisons en colonne par des 0
void RemovalInRow (CMat & Grid, const CPosition & Pos, unsigned  Howmany);              //Remplace les combinaisons en ligne par des 0
void DeleteAllNumber(CMat & Grid, unsigned nbtodelete);                                 //Supprime tout les nbtodelete de la grille

void Menu ();      //Menu principal
void Jouer ();     //Menu pour choisir son mode de jeu
void Classique (); //Mode de jeu classique, 3 Levelx de difficultés.
void Perso();      //Mode de jeu personnalisé, le joueur peut choisir les options de la partie.
void Histoire();   //Mode histoire avec Level

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
    CPosition Posbis;
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
                    ibis--;
                }
            }
        }
    }
} //DownGrid ()

void MakeAMove (CMat & Grid)
{
    bool check = false;
    CPosition Pos;
    unsigned x;
    unsigned y;
    unsigned Size;
    char Direction;
    Size = Grid.size();
    while (true)
    {
        //recup coordonnées
        while (true)
        {
            cout << "Numéro colonne (1 - " << Size << ") : ";
            cin >> x;
            if (x <= Size && x != 0) break;
            ClearBuf ();
        }
        ClearBuf ();
        while (true)
        {
            cout << "Numéro ligne (1 - " << Size << ") : ";
            cin >> y;
            if (y <= Size && y != 0) break;
            ClearBuf ();
        }
        cout << endl;
        ClearBuf ();
        Pos.first = y-1;
        Pos.second = x-1;
        //recup direction
        while (true)
        {
            cout << "Direction (Z,Q,S,D) : ";
            cin >> Direction;
            cout << endl;
            Direction = toupper(Direction);
            if (Direction == 'Z' || Direction == 'Q' || Direction == 'S' || Direction == 'D') break;
            ClearBuf ();
        }
        switch (Direction)
        {
            case 'Z' : if((Pos.first != 0) && //Sortie de grille
                         (Grid[Pos.first-1][Pos.second] != 0) && (Grid[Pos.first][Pos.second] != 0) //On ne bouge pas un 0
                      && (Grid[Pos.first-1][Pos.second] != 12) && (Grid[Pos.first][Pos.second] != 12))   //On ne bouge pas un mur
                {
                    check = true;

                    //Boules spéciales 11
                    if (Grid[Pos.first-1][Pos.second] == 11)
                    {
                        Grid[Pos.first-1][Pos.second] = 0;
                        DeleteAllNumber (Grid, Grid[Pos.first][Pos.second]);
                    }
                    if (Grid[Pos.first][Pos.second] == 11)
                    {
                        Grid[Pos.first][Pos.second] = 0;
                        DeleteAllNumber (Grid, Grid[Pos.first-1][Pos.second]);
                    }

                    swap (Grid[Pos.first-1][Pos.second], Grid[Pos.first][Pos.second]);
                }
            break;
            case 'S' : if((Pos.first != Grid.size()-1) && //Sortie de grille
                          (Grid[Pos.first+1][Pos.second] != 0) && (Grid[Pos.first][Pos.second] != 0) //On ne bouge pas un 0
                       && (Grid[Pos.first+1][Pos.second] != 12) && (Grid[Pos.first][Pos.second] != 12))  //On ne bouge pas un mur
                {
                    check = true;

                    if (Grid[Pos.first+1][Pos.second] == 11)
                    {
                        Grid[Pos.first+1][Pos.second] = 0;
                        DeleteAllNumber (Grid, Grid[Pos.first][Pos.second]);
                    }
                    if (Grid[Pos.first][Pos.second] == 11)
                    {
                        Grid[Pos.first][Pos.second] = 0;
                        DeleteAllNumber (Grid, Grid[Pos.first+1][Pos.second]);
                    }

                    swap (Grid[Pos.first+1][Pos.second], Grid[Pos.first][Pos.second]);
                }
            break;
            case 'D' : if((Pos.second != Grid.size()-1) && //Sortie de grille
                          (Grid[Pos.first][Pos.second+1] != 0) && (Grid[Pos.first][Pos.second] != 0) //On ne bouge pas un 0
                       && (Grid[Pos.first][Pos.second+1] != 12) && (Grid[Pos.first][Pos.second] != 12))   //On ne bouge pas un mur
                {
                    check = true;

                    if (Grid[Pos.first][Pos.second+1] == 11)
                    {
                        Grid[Pos.first][Pos.second+1] = 0;
                        DeleteAllNumber (Grid, Grid[Pos.first][Pos.second]);
                    }
                    if (Grid[Pos.first][Pos.second] == 11)
                    {
                        Grid[Pos.first][Pos.second] = 0;
                        DeleteAllNumber (Grid, Grid[Pos.first][Pos.second+1]);
                    }

                    swap (Grid[Pos.first][Pos.second+1], Grid[Pos.first][Pos.second]);
                }
            break;
            case 'Q' : if(Pos.second != 0 && //Sortie de grille
                          (Grid[Pos.first][Pos.second-1] != 0) && (Grid[Pos.first][Pos.second] != 0) //On ne bouge pas un 0
                       && (Grid[Pos.first][Pos.second-1] != 12) && (Grid[Pos.first][Pos.second] != 12))   //On ne bouge pas un mur
                {
                    check = true;

                    if (Grid[Pos.first][Pos.second-1] == 11)
                    {
                        Grid[Pos.first][Pos.second-1] = 0;
                        DeleteAllNumber (Grid, Grid[Pos.first][Pos.second]);
                    }
                    if (Grid[Pos.first][Pos.second] == 11)
                    {
                        Grid[Pos.first][Pos.second] = 0;
                        DeleteAllNumber (Grid, Grid[Pos.first][Pos.second-1]);
                    }

                    swap (Grid[Pos.first][Pos.second-1], Grid[Pos.first][Pos.second]);
                }
            break;
        }
        ClearBuf();
        if (check) break;
        cout << "Vous ne pouvez pas déplacer un mur." << endl
             << "Vous ne pouvez pas déplacer une case hors de la grille." << endl;
    }
} //MakeAMove()

bool AtLeastThreeInAColumn (const CMat & Grid, CPosition & Pos, unsigned & Howmany)
{
    for (unsigned i (0); i < Grid.size() - 2; ++i)
    {
        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            if (Grid[i][j] != 12 && Grid[i][j] == Grid [i+1][j] && Grid[i][j] == Grid [i+2][j]) //3 affilés
            {
                if (Grid[i][j] == 0) break;
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
            if (Grid[i][j] !=+ 12 && Grid[i][j] == Grid [i][j+1] && Grid[i][j] == Grid [i][j+2])
            {
                if (Grid[i][j] == 0) break;
                Pos.first = j;
                Pos.second = i;
                Howmany = 3;
                while (Grid[i][j] == Grid[i][j + Howmany])
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
        Cpt++;
    }
} //RemovalInColumn()

void RemovalInRow (CMat & Grid, const CPosition & Pos, unsigned  Howmany)
{
    unsigned Cpt = 0;
    while (Cpt != Howmany)
    {
        Grid[Pos.second][Pos.first + Cpt] = 0;
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

void DeleteAllNumber (CMat & Grid, unsigned nbtodelete)
{
    for (unsigned i (0); i < Grid.size(); ++i)
    {
        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            if (Grid[i][j] == nbtodelete)
            {
                Grid[i][j] = 0;
            }
        }
    }
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

void ClearBuf ()    //clear the buffer
{
    cin.clear ();
    cin.ignore (numeric_limits<streamsize>::max(), '\n');

}// ClearBuf ()

void Level1(CMat & Grid)
{
    InitGrid(Grid, 10, 5);
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
}

void Level2(CMat & Grid)
{
    InitGrid(Grid, 10, 5);

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
}

void Level3(CMat & Grid)
{
    InitGrid(Grid, 15, 5);

    for(unsigned i =0; i < 12; ++i)
    {
        Grid[Grid.size()-1-i][11] = 12;
        Grid[Grid.size()-1-i][7] = 12;
        Grid[Grid.size()-1-i][3] = 12;
    }
}

void Level4(CMat & Grid)
{
    InitGrid(Grid, 20, 5);

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
}

void Level5(CMat & Grid)
{
    InitGrid(Grid, 20, 5);

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
}

void Menu ()
{
    ClearScreen();
    DisplayFile  ("menu.txt");
    bool check = true;
    unsigned choix = 0;
    while (true)
    {
        cin >> choix;
        if (cin.fail() || choix > 5 || choix < 1)
        {
            cout << "Valeur incorrecte 1-2-3-4-5" << endl << endl;
            ClearBuf();
            continue;
        }
        switch (choix)
        {
        case 1:
            ClearScreen();
            ClearBuf();
            Jouer();
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
                    Menu();
            }
            break;
        case 4:
            ClearScreen();
            AfficheScores(Key);
            break;
        case 5:
            exit(0);
            break;
        default:
            check = false;
            cout << "Valeur incorrecte 1-2-3-4-5" << endl << endl;
            ClearBuf ();
            break;
        }
        if (check) break;
    }
} //Menu ()

void Jouer ()
{
    ClearScreen();
    DisplayFile  ("jouer.txt");
    bool check = true;
    unsigned choix = 0;
    while (true)
    {
        cin >> choix;
        if (cin.fail() || choix > 4 || choix < 1)
        {
            cout << "Valeur incorrecte 1-2-3-4" << endl << endl;
            ClearBuf();
            continue;
        }
        switch (choix)
        {
            case 1: {
                ClearScreen();
                ClearBuf();
                Classique();
                break;
                }
            case 2: {
                ClearScreen();
                ClearBuf();
                Perso();
                break;
                }
            case 3: {
                ClearScreen();
                ClearBuf();
                Histoire();
                break;
                }
            case 4: {
                ClearScreen();
                ClearBuf ();
                Menu();
                break;
                }
        }
        if (check) break;
    }
}// Jouer ()

void Classique ()
{
    ClearScreen();
    DisplayFile  ("classique.txt");
    bool check = true;
    unsigned choix = 0;
    while (true)
    {
        cin >> choix;
        if (cin.fail() || choix > 4 || choix < 1)
        {
            cout << "Valeur incorrecte 1-2-3-4" << endl << endl;
            ClearBuf();
            continue;
        }
        switch (choix)
        {
            case 1: { //facile
                Size = 10;
                KNbCandies = 5;
                Coup = 20;
                break;
                }
            case 2: { //normal
                Size = 8;
                KNbCandies = 6;
                Coup = 15;
                break;
                }
            case 3: { //difficile
                Size = 6;
                KNbCandies = 8;
                Coup = 10;
                break;
                }
            case 4: {//retour
                Jouer();
                break;
                }
        }
        if (check) break;
    }
}// Classique ()

void Perso ()
{
    ClearScreen();
    DisplayFile  ("perso.txt");
    while (true)
    {
        cout << "Taille de la grille (5 - 30) : ";
        cin >> Size;
        if (Size <= 30 && Size >= 5) break;
        ClearBuf ();
    }
    ClearBuf ();
    while (true)
    {
        cout << "Numero de bonbon max (4 - 9) : ";
        cin >> KNbCandies;
        if (KNbCandies <= 9 && KNbCandies >= 4) break;
        ClearBuf ();
    }
    ClearBuf ();
    while (true)
    {
        cout << "Nombre de coup max (1 - 100) : ";
        cin >> Coup;
        if (Coup <= 100 && Coup != 0) break;
        ClearBuf ();
    }
    ClearBuf ();
} //Perso ()

void Histoire()
{
    ClearScreen();
    DisplayFile  ("histoire.txt");
    bool check = true;
    unsigned choix = 0;

    while (true)
        {
            cin >> choix;
            if (cin.fail() || choix > 6 || choix < 1)
            {
                cout << "Valeur incorrecte 1-2-3-4-5-6" << endl << endl;
                ClearBuf();
                continue;
            }
            switch (choix)
            {
                case 1:
                    ClearScreen();
                    ClearBuf();
                    chlvl = 1;
                    break;

                case 2:
                    ClearScreen();
                    ClearBuf();
                    chlvl = 2;
                    break;

                case 3:
                    ClearScreen();
                    ClearBuf();
                    chlvl = 3;
                    break;

                case 4:
                    ClearScreen();
                    ClearBuf ();
                    chlvl = 4;
                    break;

                case 5:
                    ClearScreen();
                    ClearBuf();
                    chlvl = 5;
                    break;
                case 6:
                    Jouer();
                    break;
            }
            if (check) break;
        }
} //Histoire()

int main()
{
    CMat Grid;
    CPosition Pos;
    unsigned Howmany;
    unsigned Score = 0;
    while (true)
    {
        Menu();
        if (chlvl == 0)
            InitGrid (Grid, Size, KNbCandies); //Initialisation de la grille avec paramètres choisis
        else
        {
            switch (chlvl)
            {
            case 1:
                Coup = 10;
                Level1(Grid);
                break;
            case 2:
                Coup = 10;
                Level2(Grid);
                break;
            case 3:
                Coup = 10;
                Level3(Grid);
                break;
            case 4:
                Coup = 10;
                Level4(Grid);
                break;
            case 5:
                Coup = 10;
                Level5(Grid);
                break;
            }
        }
        while (Coup != 0)
        {
            ClearScreen();
            DisplayGrid (Grid);
            cout << "Il vous reste " << Coup << " coup(s) !" << endl
                 << "Score actuel : " << Score << endl << endl;
            MakeAMove (Grid);
            DisplayGrid (Grid);
            sleep(1);
            do
            {
                while (AtLeastThreeInAColumn (Grid, Pos, Howmany))
                {
                    cout << "Une combinaison de " << Howmany << " bonbons a ete trouve dans les colonnes en coordonnées " << Pos.first << " ; " << Pos.second  << endl;
                    if (Howmany == 5)
                        FiveInColumn (Grid, Pos, Howmany);
                    if (Howmany != 5)
                        RemovalInColumn (Grid, Pos, Howmany);   //REMPLACE PAR DES 0
                    DisplayGrid (Grid);                         //AFFICHE
                    sleep(1);
                    DownGrid (Grid);                            //REMONTE LES 0
                    Score += 10;
                }
                while (AtLeastThreeInARow  (Grid, Pos, Howmany))
                {
                    cout << "Une combinaison de " << Howmany << " bonbons a ete trouve dans les lignes en coordonnées " << Pos.first << " ; " << Pos.second  << endl;
                    if (Howmany == 5)
                        FiveInRow  (Grid, Pos, Howmany);
                    if (Howmany != 5)
                        RemovalInRow (Grid, Pos, Howmany);   //REMPLACE PAR DES 0
                    DisplayGrid (Grid);                     //AFFICHE
                    sleep(1);
                    DownGrid (Grid);                        //REMONTE LES 0
                    Score += 10;
                }
            }  while (ReplaceEmpty (Grid, KNbCandies));

            --Coup;
        }
        cout << "Partie termine !" << endl
             << "Vous avez realise un score de " << Score << " !" << endl << endl ;
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

        cout <<"Entrez Q pour retourner au menu." << endl;
        while (true)
        {
            char quit='h';
            cin >> quit;
            if (quit == 'Q' || quit == 'q')
            {
                Score = 0;
                ClearScreen();
                ClearBuf();
                break;
            }
        }
    }
} //main()
