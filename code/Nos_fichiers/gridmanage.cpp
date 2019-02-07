#include "Nos_fichiers/jeu.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Nos_fichiers/move.h"

#ifdef __linux__
bool IsOnLinux = true;
#elif __APPLE__
bool IsOnLinux = false;
#endif

void InitGrid2 (CMat & Grid, unsigned Size_col, unsigned Size_lin, unsigned NbCandies)
{
    Grid.resize (Size_col, vector <unsigned> (Size_lin));
    srand(time(NULL));
    for (unsigned i (0); i < Grid.size(); ++i)
    {
        for (unsigned j(0); j < Grid[i].size(); ++j)
        {
            Grid [i][j] = rand()%NbCandies+1;
        }
    }
    ClearAssociation (Grid, NbCandies);
} // InitGrid()

bool AtLeastThreeInAColumn2 (const CMat & Grid, CPosition & Pos, unsigned & Howmany, bool init)
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
                if(IsOnLinux && Howmany>=4 && !init)
                    system("aplay ../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/sons/sweet.wav");
                return true;
            }
        }
    }
    return false;
} // AtLeastThreeInAColumn2()

bool AtLeastThreeInARow2  (const CMat & Grid, CPosition & Pos, unsigned & Howmany, bool init)
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
                if(IsOnLinux && Howmany>=4 && !init)
                    system("aplay ../G4_Legrand_Piedanna_Prat_Robbe_Trouin/Nos_fichiers/sons/sweet.wav");
                return true;
            }
        }
    }
    return false;
} // AtLeastThreeInARow2()

void RemovalInColumn2 (CMat & Grid, const CPosition & Pos, unsigned  Howmany)
{
    unsigned Cpt = 0;
    while (Cpt != Howmany)
    {

        Grid[Pos.second + Cpt][Pos.first] = 0;
        //cout << "delete de la case" << Pos.first + 1 << Pos.second + Cpt + 1 << endl;
        Cpt++;
    }
} // RemovalInColumn()

void RemovalInRow2 (CMat & Grid, const CPosition & Pos, unsigned  Howmany)
{
    unsigned Cpt = 0;
    while (Cpt != Howmany)
    {
        Grid[Pos.second][Pos.first + Cpt] = 0;
        //cout << "delete de la case" << Pos.first + Cpt + 1 << Pos.second + 1 << endl;
        Cpt++;
    }
} // RemovalInRow()

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
} // FiveInColumn()

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
} // FiveInRow()
