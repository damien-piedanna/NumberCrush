#ifndef PARAMS2_H
#define PARAMS2_H
#include <string>
#include "Nos_fichiers/consolemanagement.h"


/*!
 * \enum MoveUp
 * \brief MoveUp associe un caractère au mouvement haut
 */
const char MoveUp='Z';


/*!
 * \enum MoveDown
 * \brief MoveDown associe un caractère au mouvement bas
 */
const char MoveDown='S';

/*!
 * \enum MoveLeft
 * \brief MoveLeft associe un caractère au mouvement gauche
 */
const char MoveLeft='Q';

/*!
 * \enum MoveRight
 * \brief MoveRight associe un caractère au mouvement droit
 */
const char MoveRight='D';


/*!
 * \fn void DisplayCouleur(const int & Chiffre)
 * \brief DisplayCouleur permet d'afficher en fond une couleur
 * \param Chiffre[in] affiche la couleur correspondant à l'entier
 */
void DisplayCouleur(const int & Chiffre);

#endif // PARAMS2_H
