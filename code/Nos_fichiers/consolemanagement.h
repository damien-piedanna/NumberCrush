#ifndef CONSOLEMANAGEMENT_H
#define CONSOLEMANAGEMENT_H

#include <Nos_fichiers/jeu.h>

/*!
 * \fn void Couleur (const string & coul)
 * \brief Couleur permet d'afficher des couleurs sur la console
 * \param coul[in] couleur a afficher
 */

void Couleur (const string & coul); //Permet d'afficher des couleurs sur la console

/*!
 * \fn void ClearBuf ()
 * \brief ClearBuf vide le tampon de cin
 */
void ClearBuf ();                   //Vide le tampon de cin

/*!
 * \fn void Pause (float secondes)
 * \brief Pause permet de mettre une pause d'affichage
 * \param secondes temps de la pause (en sec)
 */
void Pause (float secondes);        //Permet de faire une pause (en sec)

#endif // CONSOLEMANAGEMENT_H
