#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Nos_fichiers/scores.h"
#include "Nos_fichiers/menu.h"
#include "Nos_fichiers/gridmanage.h"
#include "Nos_fichiers/consolemanagement.h"
#include "Nos_fichiers/move.h"
#include "Correc_prof/gridmanagement.h"


#ifdef __linux__
bool IsOnLinuxJeu = true;
#elif __APPLE__
bool IsOnLinuxJeu = false;
#endif





void PlayGame (CMat & Grid, CPosition Pos, unsigned & Score, unsigned & NbCandies, unsigned & Coup, unsigned & ScoreToWin)
{
        cout << Coup;
        for ( ; Coup != 0 ; Coup--)
        {
            ClearScreen();
            DisplayGrid2 (Grid);
            cout << "Il vous reste " << Coup << " coup(s) !" << endl;
            if (ScoreToWin == 0)
                cout  << "Score actuel : " << Score << endl << endl;
            if (ScoreToWin != 0)
                cout << "Score actuel : " << Score << " / " << ScoreToWin << endl << endl;

            MakeAMove2 (Grid, Score);

            DisplayGrid2 (Grid);
            Pause (0.5);

            UpdateGrid (Grid, Pos, Score, NbCandies);
        }
        DisplayGrid2 (Grid);
        cout << "Partie termine !" << endl;
        if (ScoreToWin == 0)
            cout << "Vous avez realise un score de " << Score << " !" << endl << endl;
        else if (Score < ScoreToWin)
            cout << "Perdu !"
                 << "Vous avez realise un score de " << Score << " / " << ScoreToWin << endl << endl;
        else
            cout << "Gagné !"
                 << "Vous avez realise un score de " << Score << " / " << ScoreToWin << endl << endl;
} // PlayGame()

int jeu()
{
    CPosition Pos;
    unsigned Score = 0;      //Score
    unsigned ScoreToWin(0);  //Score pour gagner
    unsigned Size_col;       //Taille de la grille
    unsigned Size_lin;       //Taille de la grille
    unsigned NbCandies;      //Numéro max dans la grille
    unsigned Coup;           //Nombre de coups max
    string LvlScores;        // Quel fichier de scores on load

    if(IsOnLinuxJeu)
    {
        try
        {
            system("amixer -D pulse sset Master unmute");
            system("amixer sset Master 60%");
        }
        catch (...)
        {
            string tmp;
            cout << "Veuillez augmenter le volume des hauts-parleurs, puis appuyez sur Entrée :" << endl;
            cin >> tmp;
        }
    }

    while (true)
    {
        Score=0;
        CMat Grid;
        Menu2(Grid, Size_col, Size_lin, NbCandies, Coup, LvlScores, ScoreToWin);

        PlayGame (Grid, Pos, Score, NbCandies, Coup, ScoreToWin);

        SaveScores(Score, Key, LvlScores);

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
    return 0;
} // jeu()
