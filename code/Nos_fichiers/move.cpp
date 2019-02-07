#include "Nos_fichiers/move.h"
#include "Nos_fichiers/consolemanagement.h"
#include "Nos_fichiers/useractions.h"


void ClearAssociation (CMat & Grid, unsigned NbCandies)
{
    CPosition Pos;
    unsigned Howmany;
    bool init = true;
    do
    {
        while (AtLeastThreeInAColumn2 (Grid, Pos, Howmany, init))
        {
            RemovalInColumn2 (Grid, Pos, Howmany);
        }
        while (AtLeastThreeInARow2  (Grid, Pos, Howmany, init))
        {
            RemovalInRow2 (Grid, Pos, Howmany);
        }
    } while (ReplaceEmpty(Grid, NbCandies, init));
} // ClearAssociation()

bool ReplaceEmpty (CMat & Grid, unsigned NbCandies, bool init)
{
    srand(time(NULL));
    bool check = false;
    for (float i (Grid.size() - 1); i != -1; --i)
    {
        for (float j(Grid[i].size() - 1); j != -1; --j)
        {
            if (Grid [i][j] == 0)
            {
                Grid [i][j] = rand()%NbCandies+1;
                //cout << "remplacement de la case" << i+1 << j+1 << endl;
                check = true;
            }
        }
        if (check & !init)
        {
            Pause (0.2);
            DisplayGrid2(Grid);
        }
    }
    return check;
} // ReplaceEmpty()

void DisplayGrid2 (const CMat & Grid)
{
    ClearScreen ();
    Couleur(CReset);
    unsigned line = 1;
    unsigned columns = 1;
    cout << "  ";
    while (columns <= Grid[0].size())
    {
        cout << columns;
        if (columns <= 9)
            cout << ' ';
        ++columns;
    }
    columns=1;
    cout << endl;
    for (unsigned i (0); i < Grid.size(); ++i)
    {
        Couleur(CReset);
        cout << line;
        if (line <= 9)
            cout << ' ';

        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            DisplayCouleur(Grid[i][j]);
            if (Grid [i][j] == 0) //cases vides
            {
                Couleur(CReset);
                cout << "  ";
            }
            if (Grid [i][j] == 11) //boules spéciales
            {
                Couleur(CReset);
                cout << "()";
            }
            if (Grid [i][j] == 12) //Mur
            {
                DisplayCouleur(12);
                cout << "  ";
            }
            if (Grid [i][j] <= 9 && Grid [i][j] != 0)
                cout << Grid [i][j] << ' ';
        }
        Couleur(CReset);
        if (line <= 9)
            cout << ' ';
        cout << line;
         ++line;
        cout << endl;

    }
    Couleur(CReset);
    cout << "  ";
    while (columns <= Grid[0].size())
    {
        cout << columns;
        if (columns <= 9)
            cout << ' ';
        ++columns;
    }
    cout << endl << endl;
} // DisplayGrid()

void DownGrid (CMat & Grid)
{
    for (unsigned i(0); i < Grid.size(); ++i)
    {
        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            unsigned cpt = 0;
            if (Grid [i][j] == 0)
            {
                while (i-cpt-1 < Grid.size())
                {
                    swap (Grid[i-cpt-1][j], Grid[i-cpt][j]);
                    //cout << "echange de la case" << j+1 << i-cpt << " avec " << j+1 << i-cpt+1 << endl;
                    cpt++;
                }
            }
        }
    }
} // DownGrid()

void MakeAMove2 (CMat & Grid, unsigned & Score)
{
    bool check = false;
    CPosition Pos;
    CPosition PosToMove;
    char Direction;
    unsigned Size_col = Grid[0].size();
    unsigned Size_lin = Grid.size();
    while (true)
    {
        Pos = GetPos (Pos, Size_col, Size_lin); //Récupération position
        cout << endl;
        Direction = GetDirection (Direction); //Récupération direction
        switch (Direction)
        {
            case MoveUp :
                if(Pos.first != 0)
                {
                   check = true;
                   PosToMove.first = Pos.first-1;
                   PosToMove.second = Pos.second;
                   Move (Grid, Score, Pos, PosToMove);
                }
            break;
            case MoveDown :
                if(Pos.first != Grid.size()-1)
                {
                   check = true;
                   PosToMove.first = Pos.first+1;
                   PosToMove.second = Pos.second;
                   Move (Grid, Score, Pos, PosToMove);
                }

            break;
            case MoveRight :
                if(Pos.second != Grid[0].size()-1)
                {
                   check = true;
                   PosToMove.first = Pos.first;
                   PosToMove.second = Pos.second+1;
                   Move (Grid, Score, Pos, PosToMove);
                }
            break;
            case MoveLeft :
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
        ClearScreen();
        DisplayGrid2(Grid);
        cout << "Vous ne pouvez pas déplacer un mur." << endl
             << "Vous ne pouvez pas déplacer une case hors de la grille." << endl << endl;
    }
} // MakeAMove2()

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
} // Move()

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
} // DeleteAllNumber()

void UpdateGrid (CMat & Grid, CPosition & Pos, unsigned & Score, unsigned NbCandies)
{
    unsigned Howmany;
    bool init = false;
    do
    {
        while (AtLeastThreeInAColumn2 (Grid, Pos, Howmany, init))
        {
            cout << "Une combinaison de " << Howmany << " bonbons a ete trouve dans les colonnes en coordonnées " << Pos.first+1 << " ; " << Pos.second+1  << endl;
            Score += Howmany*5;  //5 points par case détruite

            if (Howmany == 5)
                FiveInColumn (Grid, Pos, Howmany);      //Fait spawn boule spéciale
            if (Howmany != 5)
                RemovalInColumn2 (Grid, Pos, Howmany);   //REMPLACE PAR DES 0

            DisplayGrid2 (Grid);
            Pause (0.3);
            DownGrid (Grid);
            Pause (0.3);
            DisplayGrid2 (Grid);
        }
        while (AtLeastThreeInARow2  (Grid, Pos, Howmany, init))
        {
            cout << "Une combinaison de " << Howmany << " bonbons a ete trouve dans les lignes en coordonnées " << Pos.first+1 << " ; " << Pos.second+1  << endl;
            Score += Howmany*5; //5 points par case détruite

            if (Howmany == 5)
                FiveInRow (Grid, Pos, Howmany);      //Fait spawn boule spéciale
            if (Howmany != 5)
                RemovalInRow2 (Grid, Pos, Howmany);  //Remplace par des 0

            DisplayGrid2 (Grid);
            Pause (0.3);
            DownGrid (Grid);
            Pause (0.3);
            DisplayGrid2 (Grid);
        }
    }  while (ReplaceEmpty (Grid, NbCandies, init));
} // UpdateGrid()
