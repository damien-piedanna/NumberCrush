#ifndef GRIDMANAGE_H
#define GRIDMANAGE_H
#include "Nos_fichiers/jeu.h"

/*!
 * \fn void InitGrid2 (CMat & Grid, unsigned Size_col, unsigned Size_lin, unsigned NbCandies)
 * \brief InitGrid2 permet d'initialiser la grille
 * \param Grid[in,out] la grille à initialiser
 * \param Size_col[in] le nombre de colone voulu pour la grille
 * \param Size_lin[in] le nombre de ligne voulu pour la grille
 * \param NbCandies[in] la valeur du plus grand nombre voulu dans la grille
 */
void InitGrid2 (CMat & Grid, unsigned Size_col, unsigned Size_lin, unsigned NbCandies);                                     //Initialise la grille sans combinaison

/*!
 * \brief AtLeastThreeInAColumn2 permet de detecter si il y a au moin 3fois le même chiffre d'affilé dans une même colonne
 * \fn bool AtLeastThreeInAColumn2  (const CMat & Grid, CPosition & Pos, unsigned & Howmany, bool init)
 * \param Grid[in] la grille dans laquelle on effectue le test
 * \param Pos[out] la position de la premiere occurence du chiffre faisant une combinaison
 * \param Howmany[out] le nombre de chiffre d'affilé
 * \param init[in] savoir si on est en initialisation de la grille ou jeu
 * \return Un booleen nous disant si on a detecter 3chiffre ou plus d'affilé ou non
 */

bool AtLeastThreeInAColumn2  (const CMat & Grid, CPosition & Pos, unsigned & Howmany, bool init);    //Permet de trouver une combinaison de Howmany en colonnes

/*!
 * \brief AtLeastThreeInARow2 permet de detecter si il y a au moin 3fois le même chiffre d'affilé dans une même ligne
 * \fn bool AtLeastThreeInARow2  (const CMat & Grid, CPosition & Pos, unsigned & Howmany, bool init)
 * \param Grid[in] la grille dans laquelle on effectue le test
 * \param Pos[out] la position de la premiere occurence du chiffre faisant une combinaison
 * \param Howmany[out] le nombre de chiffre d'affilé
 * \param init[in] savoir si on est en initialisation de la grille ou jeu
 * \return Un booleen nous disant si on a detecter 3chiffre ou plus d'affilé ou non
 */
bool AtLeastThreeInARow2  (const CMat & Grid, CPosition & Pos, unsigned & Howmany, bool init);       //Permet de trouver une combinaison de Howmany en lignes

/*!
 * \brief RemovalInColumn2 permet de supprimer les chiffres detectés par AtLeastThreeInAColumn2
 * \fn void RemovalInColumn2 (CMat & Grid, const CPosition & Pos, unsigned  Howmany)
 * \param Grid[in,out] la grille dans laquelle on effectue la suppression
 * \param Pos[in] la position de la premiere occurence du chiffre faisant une combinaison
 * \param Howmany[in] le nombre de chiffre a supprimer
 */
void RemovalInColumn2 (CMat & Grid, const CPosition & Pos, unsigned  Howmany);                      //Remplace les combinaisons en colonne par des 0

/*!
 * \brief RemovalInRow2 permet de supprimer les chiffres detectés par AtLeastThreeInARow2
 * \fn void RemovalInRow2 (CMat & Grid, const CPosition & Pos, unsigned  Howmany)
 * \param Grid[in,out] la grille dans laquelle on effectue la suppression
 * \param Pos[in] la position de la premiere occurence du chiffre faisant une combinaison
 * \param Howmany[in] le nombre de chiffre a supprimer
 */
void RemovalInRow2 (CMat & Grid, const CPosition & Pos, unsigned  Howmany);                         //Remplace les combinaisons en ligne par des 0

/*!
 * \brief FiveInColumn permet de faire apparait un bonus quand il y a 5chiffres d'affilé en ligne
 * \fn void FiveInColumn (CMat & Grid, const CPosition & Pos, unsigned  Howmany)
 * \param Grid[in] la grille dans laquelle on joue
 * \param Pos[in] la position de la premiere occurence du chiffre faisant une combinaison
 * \param Howmany le nombre de chiffre d'affilé (ici ce sera toujours 5)
 */
void FiveInColumn (CMat & Grid, const CPosition & Pos, unsigned  Howmany);

/*!
 * \brief FiveInColumn permet de faire apparait un bonus quand il y a 5chiffres d'affilé en colonne
 * \fn void FiveInColumn (CMat & Grid, const CPosition & Pos, unsigned  Howmany)
 * \param Grid[in] la grille dans laquelle on joue
 * \param Pos[in] la position de la premiere occurence du chiffre faisant une combinaison
 * \param Howmany le nombre de chiffre d'affilé (ici ce sera toujours 5)
 */
void FiveInRow (CMat & Grid, const CPosition & Pos, unsigned  Howmany);


#endif // GRIDMANAGE_H
