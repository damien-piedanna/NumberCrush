#ifndef USERACTIONS_H
#define USERACTIONS_H

#include <Nos_fichiers/jeu.h>



/*!
 * \fn unsigned GetUnsigned (unsigned min, unsigned max)
 * \brief GetUnsigned permet de demander à l'utilisateur un entier naturel entre min et max
 * \param min[in] l'entier naturel definissant la borne min
 * \param max[in] l'entier naturel definissant la borne max
 * \return un entier naturel compris entre min et max
 */
unsigned GetUnsigned (unsigned min, unsigned max);                                      //Recupération d'un unsigned

/*!
 * \fn CPosition GetPos (CPosition & Pos, unsigned & Size_col, unsigned & Size_lin)
 * \brief GetPos permet de demander à l'utilisateur de rentrer une position dans la grille
 * \param Pos[out] la position que l'on av recuperer
 * \param Size_col[in] la taille de colonne de la grille à ne pas depasser
 * \param Size_lin[in] la taille de la ligne de la grille à ne pas dépasser
 * \return une position dans la grille
 */
CPosition GetPos (CPosition & Pos, unsigned & Size_col, unsigned & Size_lin);           //Récupération positions


/*!
 * \fn char GetDirection (char Direction)
 * \brief GetDirection affiche un choix de direction et permet de demander à l'utilisateur de rentrer une direction pour effectuer un mouvement
 * \param Direction[out] la direction entrée par l'utilisateur
 * \return une direction pour effectuer un mouvement
 */
char GetDirection (char Direction);                                            //Récupération direction

#endif // USERACTIONS_H
