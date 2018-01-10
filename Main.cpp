#include <iostream>
#include <vector>

using namespace std;

typedef vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMat; // un type représentant la grille
typedef pair <unsigned, unsigned> CPosition; // une position dans la girlle

/* AFFICHAGE */
const string CReset   ("0");
const string CNoir    ("30");
const string CRouge   ("31");
const string CVert    ("32");
const string CJaune   ("33");
const string CBleu    ("34");
const string CMAgenta ("35");
const string CCyan    ("36");

const string FNoir    ("40");
const string FRouge   ("41");
const string FVert    ("42");
const string FJaune   ("43");
const string FBleu    ("44");
const string FMAgenta ("45");
const string FCyan    ("46");

void MakeAMove (CMat & Grid, const CPosition & Pos, char Direction);

void Couleur (const string & coul)
{
    cout << "\033[7;" << coul <<"m";
}

void ClearScreen ()
{
    cout << "\033[H\033[2J";
}
/* AFFICHAGE */

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
}

void  DisplayGrid (const CMat & Grid)
{
    ClearScreen ();
    Couleur(CReset);
    for (unsigned i (0); i < Grid.size(); ++i)
    {
        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            Couleur (to_string(Grid [i][j] + 29));
            if (Grid [i][j] == 0)
                Couleur(CReset);
            cout << Grid [i][j] << ' ';
        }
        cout << endl;
    }
    Couleur(CReset);
}

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
}

void MakeAMove (CMat & Grid, const CPosition & Pos, char Direction)
{
    bool check = false;
    while (!check)
    {
        switch (Direction)
        {
            case 'z' :
                swap (Grid[Pos.first-1][Pos.second], Grid[Pos.first][Pos.second]);
                DisplayGrid (Grid);
                check = true;
            break;
            case 's' :
                swap (Grid[Pos.first+1][Pos.second], Grid[Pos.first][Pos.second]);
                DisplayGrid (Grid);
                check = true;
            break;
            case 'd' :
                swap (Grid[Pos.first][Pos.second+1], Grid[Pos.first][Pos.second]);
                DisplayGrid (Grid);
                check = true;
            break;
            case 'q' :
                swap (Grid[Pos.first][Pos.second-1], Grid[Pos.first][Pos.second]);
                DisplayGrid (Grid);
                check = true;
            break;
            default:
                cout << "Choix incorect, z=haut / q=gauche / s=bas / d=droite" << endl;
                cin >> Direction;
        }
    }
}

bool AtLeastThreeInAColumn (const CMat & Grid, CPosition & Pos, unsigned & Howmany)
{
    for (unsigned i (0); i < Grid.size(); ++i)
    {
        for (unsigned j(0); j < Grid[i].size() - 2; ++j)
        {
            if (Grid[i][j] == Grid [i+1][j] && Grid[i][j] == Grid [i+2][j]) //3 affilés
            {
                if (Grid[i][j] == 0) break;
                Pos.first = j + 1;
                Pos.second = i + 1;
                Howmany = 3;
                while (Grid[i][j] == Grid[i + Howmany][j])
                    Howmany++;
                return true;
            }
        }
    }
    return false;
}

bool AtLeastThreeInARow  (const CMat & Grid, CPosition & Pos, unsigned & Howmany)
{
    for (unsigned i (0); i < Grid.size(); ++i)
    {
        for (unsigned j(0); j < Grid[i].size() - 2; ++j)
        {
            if (Grid[i][j] == Grid [i][j+1] && Grid[i][j] == Grid [i][j+2])
            {
                if (Grid[i][j] == 0) break;
                Pos.first = j + 1;
                Pos.second = i + 1;
                Howmany = 3;
                while (Grid[i][j] == Grid[i][j + Howmany])
                    ++Howmany;
                return true;
            }
        }
    }
    return false;
}

void RemovalInColumn (CMat & Grid, const CPosition & Pos, unsigned  Howmany)
{
    unsigned Cpt = 0;
    while (Howmany != 0)
    {
        Howmany--;
        Grid[Pos.second + Cpt - 1][Pos.first - 1] = 0;
        Cpt++;
    }
    DownGrid (Grid);
    DisplayGrid (Grid);
}

void RemovalInRow (CMat & Grid, const CPosition & Pos, unsigned  Howmany)
{
    unsigned Cpt = 0;
    while (Howmany != 0)
    {
        Howmany--;
        Grid[Pos.second - 1][Pos.first - 1 + Cpt] = 0;
        Cpt++;
    }
    DownGrid (Grid);
    DisplayGrid (Grid);
}

int main()
{
    //INITIALISATION
    CMat Grid;
    unsigned Size;
    char Direction;
    unsigned KNbCandies = 6;
    unsigned x;
    unsigned y;
    CPosition Pos;
    unsigned Coup;

    cout << "Bienvenue sur NumberCrush !" << endl;

    char choix = '0';
    while (choix != '1' && choix != '2')
    {
        cout << "Voulez vous configurer la partie ?" << endl << endl
             << "1- OUI" << endl
             << "2- NON" << endl;
        cin >> choix;
    }
    switch (choix)
    {
        case '1':
            cout << "Taille de la grille ?" << endl;
            cin >> Size;
            cout << "Nombre de coup max ?" << endl;
            cin >> Coup;
            break;
        case '2':
            Size = 8;
            Coup = 10;
            break;
    }
    //INITIALISATION
    InitGrid (Grid, Size, KNbCandies);
    DisplayGrid (Grid);
    while (Coup != 0)
    {
        while (true)
        {
            cout << "Saisir X entre 1 et " << Size << endl;
            cin >> x;
            if (x < Size) break;
        }
        while (true)
        {
            cout << "Saisir Y entre 1 et " << Size << endl;
            cin >> y;
            if (y < Size) break;
        }

        Pos.first = y-1;
        Pos.second = x-1;
        cout << "direction ?  z=haut / q=gauche / s=bas / d=droite" << endl;
        cin >> Direction;
        Direction = tolower(Direction);


        MakeAMove (Grid, Pos, Direction);
        unsigned Howmany;
        while (AtLeastThreeInARow  (Grid, Pos, Howmany))
        {
            cout << "Une combinaison de " << Howmany << " bonbons a ete trouve dans les lignes en coordonnées " << Pos.first << " ; " << Pos.second  << endl;
            RemovalInRow (Grid, Pos, Howmany);
        }
        while (AtLeastThreeInAColumn  (Grid, Pos, Howmany))
        {
            cout << "Une combinaison de " << Howmany << " bonbons a ete trouve dans les colonnes en coordonnées " << Pos.first << " ; " << Pos.second  << endl;
            RemovalInColumn (Grid, Pos, Howmany);
        }
        --Coup;
    }

    return 0;
}
