#ifndef CREATOR_H
#define CREATOR_H

#include <string>
#include <vector>

using namespace std;

/*!
 * \fn void DisplayGridCreator(unsigned & Compteur, vector <string> & StockDeVar, unsigned & GridSize)
 * \brief DisplayGridCreator permet d'afficher la grille que l'utilisateur est en train de creer
 * \param Compteur[in] permet de connaitre le numéro de la ligne que l'on cree
 * \param StockDeVar[out] vecteur dans le lequel on stock les UserImput necessaire à la creation d'un niveau
 * \param GridSize[out] taille de la grille creee par l'utilisateur
 */

void DisplayGridCreator(unsigned & Compteur, vector <string> & StockDeVar, unsigned & GridSize);


/*!
 * \fn bool TestValeurDansString(string & Str, unsigned & GridSize)
 * \brief TestValeurDansString verifie que la chaine Str contient bien uniquement des 0 et des 1 et qu'elle fait la bonne taille
 * \param Str[in] chaine de caractere a verifier
 * \param GridSize[in] taille de la grille creee par l'utilisateur
 * \return vrai si la chaine de caractere si Str contient uniquement des 0 et des 1 et quelle fais la meme taille que GridSize
 */
bool TestValeurDansString(string & Str, unsigned & GridSize);

/*!
 * \fn string UserImputNomLevel()
 * \brief UserImputNomLevel Demande à l'utilisateur de rentrer le nom de son niveau
 * \return le nom du niveau rentree par l'utilisateur
 */

string UserImputNomLevel();


/*!
 * \fn unsigned UserImputTailleGrille()
 * \brief UserImputTailleGrille Demande à l'utilisateur de rentrer la taille de son niveau
 * \return la taille de la grille rentree par l'utilisateur
 */
unsigned UserImputTailleGrille();

/*!
 * \fn unsigned UserImputScoreToWin()
 * \brief UserImputScoreToWin Demande à l'utilisateur de rentrer le score a atteindre pour gagner
 * \return Le score pour gagner rentre par l'utilisateur
 */
unsigned UserImputScoreToWin();

/*!
 * \fn unsigned UserImputNbCandies()
 * \brief UserImputNbCandies Demande à l'utilisateur de rentrer le nombre de bonbon different de son niveau
 * \return le nombre de bonbon different rentre par l'utilisateur
 */
unsigned UserImputNbCandies();

/*!
 * \fn unsigned UserImputCoups()
 * \brief UserImputCoups Demande à l'utilisateur de rentrer le nombre de coup de son niveau
 * \return le nombre de coup rentre par l'utilisateur
 */
unsigned UserImputCoups();


/*!
 * \fn vector <string> UserImputNiveau(vector <string> & StockDeVar, unsigned & GridSize)
 * \brief UserImputNiveau demande à l'utilisateur de creer son niveau en entrant des 0 et des 1
 * \param StockDeVar[out] vecteur dans le lequel on stock les UserImput necessaire à la creation d'un niveau
 * \param GridSize[out] taille de la grille creee par l'utilisateur
 * \return StockDeVar qui contient toute les informations pour creer le niveau
 */
vector <string> UserImputNiveau(vector <string> & StockDeVar, unsigned & GridSize);

/*!
 * \fn void LevelCreator()
 * \brief LevelCreator Permet de creer son propre niveau
 */
void LevelCreator();

#endif // CREATOR_H
