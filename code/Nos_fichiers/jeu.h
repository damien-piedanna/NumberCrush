#ifndef JEU_H
#define JEU_H

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include "Nos_fichiers/scores.h"



/*!
 * \struct CVLine
 * \brief CVLine un vector d'entier naturel
 */
typedef vector <unsigned> CVLine; // un type représentant une ligne de la grille

/*!
 * \struct CVLMat
 * \brief CMat un vecteur de CVLine, donc un vecteur de vecteur d'entier naturel
 */
typedef vector <CVLine> CMat; // un type représentant la grille

/*!
 * \struct CPosition
 * \brief CPosition creer une pair d'entier naturel permettant de definir une position dans une grille
 */
typedef pair <unsigned, unsigned> CPosition; // une position dans la girlle

/*!
 * \enum CReset
 * \brief CReset permet de reinitialiser les couleurs
 */
const string CReset   ("0");

/*!
 * \enum Key
 * \brief Key defini le clef de chiffrement pour le tableau de score
 */
const unsigned Key(5); // Clé de chiffrement/déchiffrement par César

/*!
 * \fn void PlayGame (CMat & Grid, CPosition Pos, unsigned & Score, unsigned & NbCandies, unsigned & Coup, unsigned &ScoreToWin)
 * \brief PlayGame lance la "partie" tant que le joueur dispose de coup pour jouer
 * \param Grid[out] la grill dans laquel l'utilisateur joue
 * \param Pos[out] les positions dans une grille
 * \param Score[out] le score du joueur
 * \param NbCandies[out] le nombre de chiffre différent max
 * \param Coup[out] le nombre de coup que le joueur aura
 * \param ScoreToWin[out] le score que le joueur devra faire pour reussir une partie, si le type de partie le demande
 */
void PlayGame (CMat & Grid, CPosition Pos, unsigned & Score, unsigned & NbCandies, unsigned & Coup, unsigned &ScoreToWin);  //Lance la partie jusqu'à qu'il n'y ai plus de coups

/*!
 * \fn int jeu()
 * \brief jeu lance le code, c'est un peu le main
 * \return vrai tout le temps
 */
int jeu();

#endif // JEU_H
