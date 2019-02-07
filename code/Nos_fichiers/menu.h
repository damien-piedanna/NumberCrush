#ifndef MENU_H
#define MENU_H

#include <Nos_fichiers/jeu.h>

/*!
 * \fn void DisplayFile (const string & File)
 * \brief DisplayFile ouvre un fichier texte, si il existe, sinon creer un menu avec lequel l'utilisateur pourra interagir
 * \param File[out] fichier que la fonction ouvre
 */
void DisplayFile (const string & File);

/*!
 * \fn void Jouer (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & KNbCandies, unsigned & Coup, string & LvlScores, unsigned &ScoreToWin)
 * \brief Jouer ouvre le menu Jouer, les paramètres dépendront du mode de jeu choisi ensuite
 * \param Grid[out] la grille dans laquelle on va jouer
 * \param Size_col[out] la taille de colonne de la grille
 * \param Size_lin[out] la taille des ligne de la grille
 * \param KNbCandies[out] le nombre de chiffre différent max
 * \param Coup[out] le nombre de coup qu'aura l'utilisateur
 * \param LvlScores[out] Fichier score associé au mode de jeu
 * \param ScoreToWin[out] Le score qu'il faudra, pour reussir
 */
void Jouer (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned &ScoreToWin);

/*!
 * \fn void Classique (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & KNbCandies, unsigned & Coup, string & LvlScores, unsigned &ScoreToWin)
 * \brief Classique ouvre le menu classique dans jouer, les paramètres dépendront du mode de jeu choisi ensuite
 * \param Grid[out] la grille dans laquelle on va jouer
 * \param Size_col[out] la taille de colonne de la grille
 * \param Size_lin[out] la taille des ligne de la grille
 * \param NbCandies[out] le nombre de chiffre différent max
 * \param Coup[out] le nombre de coup qu'aura l'utilisateur
 * \param LvlScores[out] Fichier score associé au mode de jeu
 * \param ScoreToWin[out] Le score qu'il faudra, pour reussir
 */
void Classique (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned &ScoreToWin);

/*!
 * \fn void Perso(CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & KNbCandies, unsigned & Coup, string & LvlScores, unsigned &ScoreToWin)
 * \brief Perso ouvre le menu perso dans jouer, les paramètres dépendront du mode de jeu choisi ensuite
 * \param Grid[out] la grille dans laquelle on va jouer
 * \param Size_col[out] la taille de colonne de la grille
 * \param Size_lin[out] la taille des ligne de la grille
 * \param NbCandies[out] le nombre de chiffre différent max
 * \param Coup[out] le nombre de coup qu'aura l'utilisateur
 * \param LvlScores[out] Fichier score associé au mode de jeu
 * \param ScoreToWin[out] Le score qu'il faudra, pour reussir
 */
void Perso(CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned &ScoreToWin);

/*!
 * \fn void Histoire(CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned &ScoreToWin)
 * \brief Histoire ouvre le menu histoire dans jouer, les paramètres dépendront du mode de jeu choisi ensuite
 * \param Grid[out] la grille dans laquelle on va jouer
 * \param Size_col[out] la taille de colonne de la grille
 * \param Size_lin[out] la taille des ligne de la grille
 * \param NbCandies[out] le nombre de chiffre différent max
 * \param Coup[out] le nombre de coup qu'aura l'utilisateur
 * \param LvlScores[out] Fichier score associé au mode de jeu
 * \param ScoreToWin[out] Le score qu'il faudra, pour reussir
 */
void Histoire(CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned &ScoreToWin);

/*!
 * \fn vvoid Menu2 (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & KNbCandies, unsigned & Coup, string & LvlScores, unsigned &ScoreToWin)
 * \brief Menu2 ouvre le menu de départ, le paramtres changeront selon le mode de jeu choisi
 * \param Grid[out] la grille dans laquelle on va jouer
 * \param Size_col[out] la taille de colonne de la grille
 * \param Size_lin[out] la taille des ligne de la grille
 * \param NbCandies[out] le nombre de chiffre différent max
 * \param Coup[out] le nombre de coup qu'aura l'utilisateur
 * \param LvlScores[out] Fichier score associé au mode de jeu
 * \param ScoreToWin[out] Le score qu'il faudra, pour reussir
 */
void Menu2 (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned &ScoreToWin);

/*!
 * \fn void RetrieveDataLevel(const string & NameLevel, vector <vector <unsigned>> & Grid, unsigned  & NbCandies, unsigned & Coup, unsigned & ScoreToWin)
 * \brief RetrieveDataLevel génère le niveau choisi à partir d'un fichier texte, les paramètres changeront selon le niveau choisi
 * \param NameLevel[out] Nom du fichier texte
 * \param Grid[out] grille dans laquelle l'on va jouer
 * \param NbCandies[out] le nombre de chiffre différent max
 * \param LvlScores[out] Fichier score associé au mode de jeu
 * \param ScoreToWin[out] Le score qu'il faudra, pour reussir
 */
void RetrieveDataLevel(const string & NameLevel, vector <vector <unsigned>> & Grid, unsigned  & NbCandies, unsigned & Coup, unsigned & ScoreToWin);

/*!
 * \fn void LoadLevel (const string & NameLevel, CMat & Grid, unsigned & NbCandies, unsigned & Coup, unsigned & Size_col, unsigned & Size_lin, unsigned & ScoreToWin)
 * \brief LoadLevel va génerer le niveau creer par RetrieveDataLevel
 * \param NameLevel[out] Nom du fichier texte
 * \param Grid[out] grille dans laquelle l'on va jouer
 * \param NbCandies[out] le nombre de chiffre différent max
 * \param Coup[out] le nombre de coup qu'aura l'utilisateur
 * \param Size_col[out] la taille de colonne de la grille
 * \param Size_lin[out] la taille des ligne de la grille
 * \param ScoreToWin[out] Le score qu'il faudra, pour reussir
 */
void LoadLevel (const string & NameLevel, CMat & Grid, unsigned & NbCandies, unsigned & Coup, unsigned & Size_col, unsigned & Size_lin, unsigned & ScoreToWin);

/*!
 * \fn void RetourMenu (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned &ScoreToWin)
 * \brief RetourMenu permet de retourner au menu principal
 * \param Grid[out] la grille dans laquelle on va jouer
 * \param Size_col[out] la taille de colonne de la grille
 * \param Size_lin[out] la taille des ligne de la grille
 * \param NbCandies[out] le nombre de chiffre différent max
 * \param Coup[out] le nombre de coup qu'aura l'utilisateur
 * \param LvlScores[out] Fichier score associé au mode de jeu
 * \param ScoreToWin[out] Le score qu'il faudra, pour reussir
 */
void RetourMenu (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned &ScoreToWin);

/*!
 * \fn void MenuScore(CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores)
 * \brief MenuScore permet de se rentrer au menu des scores pour les différents niveaux
 * \param Grid[out] la grille dans laquelle on va jouer
 * \param Size_col[out] la taille de colonne de la grille
 * \param Size_lin[out] la taille des ligne de la grille
 * \param NbCandies[out] le nombre de chiffre différent max
 * \param Coup[out] le nombre de coup qu'aura l'utilisateur
 * \param LvlScores[out] Fichier score associé au mode de jeu
 */
void MenuScore(CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores);

/*!
 * \fn void PartiePerso (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup)
 * \brief PartiePerso permet de jouer une partie personalisée
 * \param Grid[out] la grille dans laquelle on va jouer
 * \param Size_col[out] la taille de colonne de la grille
 * \param Size_lin[out] la taille des ligne de la grille
 * \param NbCandies[out] le nombre de chiffre différent max
 * \param Coup[out] le nombre de coup qu'aura l'utilisateur
 */
void PartiePerso (CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup);

/*!
 * \fn void LoadLevelCreated(CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned & ScoreToWin)
 * \brief LoadLevelCreated permet de charger un niveau precedement créer
 * \param Grid[out] la grille dans laquelle on va jouer
 * \param Size_col[out] la taille de colonne de la grille
 * \param Size_lin[out] la taille des ligne de la grille
 * \param NbCandies[out] le nombre de chiffre différent max
 * \param Coup[out] le nombre de coup qu'aura l'utilisateur
 * \param LvlScores[out] Fichier score associé au mode de jeu
 * \param ScoreToWin[out] score a depasser pour gagner
 */

void LoadLevelCreated(CMat & Grid, unsigned & Size_col, unsigned & Size_lin, unsigned & NbCandies, unsigned & Coup, string & LvlScores, unsigned & ScoreToWin);

#endif // MENU_H
