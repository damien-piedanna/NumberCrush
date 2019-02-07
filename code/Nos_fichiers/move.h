#ifndef MOVE_H
#define MOVE_H
#include "jeu.h"
#include "Correc_prof/gridmanagement.h"
#include "gridmanage.h"
#include "consolemanagement.h"
#include <unistd.h>
#include "Nos_fichiers/params2.h"


/*!
 * \fn void ClearAssociation (CMat & Grid, unsigned NbCandies)
 * \brief ClearAssociation permet de bien detecter quand il y a une combinaison en ligne et en colonne en même temps
 * \param Grid[in,out] grille dans laquelle est l'utilisateur
 * \param NbCandies[in] le nombre de chiffre différent max
 */
void ClearAssociation (CMat & Grid, unsigned NbCandies);

/*!
 * \fn bool ReplaceEmpty (CMat & Grid, unsigned NbCandies, bool init)
 * \brief ReplaceEmpty permet de remplacer les cases vides après suppression
 * \param Grid[in,out] grille dans laquelle l'utilisateur joue
 * \param NbCandies[in] le nombre de chiffre différent max
 * \param init[out] sert a savoir si la grille doit se rafraichir ou non
 * \return savoir si on a remplacer des chiffres ou non
 */
bool ReplaceEmpty (CMat & Grid, unsigned NbCandies, bool init);

/*!
 * \fn void DisplayGrid2 (const CMat & Grid)
 * \brief DisplayGrid2 permet d'afficher la grille actuelle
 * \param Grid[in] grille dans laquelle l'utilisateur joue ou va jouer
 */
void DisplayGrid2 (const CMat & Grid);

/*!
 * \fn void DownGrid (CMat & Grid)
 * \brief DownGrid permet de faire "tomber" les chiffres lorsque d'autres sont supprimés en dessous
 * \param Grid[in,out] grille dans laquelle est l'utilisateur
 */
void DownGrid (CMat & Grid);

/*!
 * \fn void MakeAMove2 (CMat & Grid, unsigned & Score)
 * \brief MakeAMove2 demande à l'utilisateur de bouger une case de la grille
 * \param Grid[in] grille dans laquelle l'utilisateur joue
 * \param Score[out] score du joueur
 */
void MakeAMove2 (CMat & Grid, unsigned & Score);

/*!
 * \fn void Move (CMat & Grid, unsigned & Score, const CPosition & Pos, const CPosition & PosToMove)
 * \brief Move effectue un mouvement dans une grille, altérant le score du joueur
 * \param Grid[in,out] grille dans laquelle l'utilisateur joue
 * \param Score[out] score du joueur
 * \param Pos[in] Case que le joueur veut deplacer
 * \param PosToMove[in] case vers laquelle le joueur veut deplacer
 */
void Move (CMat & Grid, unsigned & Score, const CPosition & Pos, const CPosition & PosToMove);

/*!
 * \fn void DeleteAllNumber (CMat & Grid, unsigned nbtodelete, unsigned & Score)
 * \brief DeleteAllNumber efface les chiffres lors de l'utilisation du bonus (bombe), update le score du joueur
 * \param Grid[in,out] grille dans laquelle l'utilisateur joue
 * \param nbtodelete[in] nombre a effacer partout
 * \param Score[out] score du joueur
 */
void DeleteAllNumber (CMat & Grid, unsigned nbtodelete, unsigned & Score);

/*!
 * \fn void UpdateGrid (CMat & Grid, CPosition & Pos, unsigned & Score, unsigned NbCandies)
 * \brief UpdateGrid met a jour la grille en fonction des coups du joueur
 * \param Grid[in,out] grille dans laquelle l'utilisateur joue
 * \param Pos[out] la position de la premiere occurence du chiffre faisant une combinaison
 * \param Score[out] score du joueur
 * \param NbCandies[in] le nombre de chiffre différent max
 */
void UpdateGrid (CMat & Grid, CPosition & Pos, unsigned & Score, unsigned NbCandies);

#endif // MOVE_H
