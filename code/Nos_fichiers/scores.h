#ifndef SCORES_H
#define SCORES_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

/*!
 * \namespace std
 */
using namespace std;

/*!
 * \struct CVString
 * \brief CVString creer un vecteur de string
 */
typedef vector <string> CVString;

/*!
 * \fn void RetrieveData(CVString & VString, const string & FichierSource)
 * \brief RetrieveData remplit VString par le contenu du fichier source
 * \param VString[in,out] VString que l'on remplit
 * \param FichierSource[in] Fichier source que l'on copit
 */
void RetrieveData(CVString & VString, const string & FichierSource);

/*!
 * \fn void WriteData(CVString & VString, const string & FichierDest)
 * \brief WriteData remplit FicSource par le contenue de VString
 * \param VString[in] String contenant ce que l'on veut recuperer
 * \param FichierDest[in,out] Fichier que l'on remplit
 */
void WriteData(CVString & VString, const string & FichierDest);

/*!
 * \fn unsigned GetScore (CVString & VScores,const unsigned & Ligne)
 * \brief GetScore recupère le score d'un joueur
 * \param VScores[in] vecteur contenant des scores
 * \param Ligne[in] ligne du score à recuperer
 * \return le score du joueur
 */
unsigned GetScore (CVString & VScores,const unsigned & Ligne);

/*!
 * \fn string GetName(CVString & VScores, const unsigned & Ligne)
 * \brief GetName recupère le nom de celui qui a fait le score
 * \param VScores[in] vecteur contenant les scores
 * \param Ligne[in] ligne du scoreur
 * \return le nom du scoreur
 */
string GetName(CVString & VScores, const unsigned & Ligne);

/*!
 * \fn void DescendreLignes(CVString & VScores,const unsigned & Ligne)
 * \brief DescendreLignes permet de classer les scors lors de l'ajout d'un nouveau
 * \param VScores[in,out] vecteur contenant les scores
 * \param Ligne[in] ligne à partir de laqulle on classe
 */
void DescendreLignes(CVString & VScores,const unsigned & Ligne);

/*!
 * \fn void AjustementLignes(CVString & VScores)
 * \brief AjustementLignes ajuste le classement avec le score
 * \param VScores[in,out] vecteur contenant les scores
 */
void AjustementLignes(CVString & VScores);

/*!
 * \fn void ModifScores (CVString & VScores,const unsigned & Score,const string & Name)
 * \brief ModifScores modifie le vecteur contenant les scores
 * \param VScores[in,out] vecteur contenant les scores
 * \param Score[in] score obtenu pas un joueur
 * \param Name[in] nom du scoreur
 */
void ModifScores (CVString & VScores,const unsigned & Score,const string & Name);


/*!
 * \fn void ChiffreCesar(string & Ligne,const unsigned Key)
 * \brief ChiffreCesar chiffre les scores pour eviter les modification
 * \param Ligne[in,out] ligne a chiffrer
 * \param Key[in] clef de chiffrement
 */
void ChiffreCesar(string & Ligne,const unsigned Key);

/*!
 * \fn void DeChiffreCesar(string & Ligne,const unsigned Key)
 * \brief  DeChiffreCesar dechiffre les scores
 * \param Ligne[in,out] ligne a dechiffrer
 * \param Key[in] clef de chiffrement
 */
void DeChiffreCesar(string & Ligne,const unsigned Key);

/*!
 * \fn void DisplayFile2 (const string & File)
 * \brief DisplayFile2 permet d'afficher un fichier
 * \param File[in] fichier a afficher
 */
void DisplayFile2 (const string & File);

/*!
 * \fn void AfficheScores(const unsigned Key, string & File)
 * \brief AfficheScores affiche les scores depuis un fichier
 * \param Key[in] clef de chiffrement
 * \param File[in] fichier des scores
 */
void AfficheScores(const unsigned Key, string & File);

/*!
 * \fn void MScores(string & Name, unsigned & Score, const unsigned Key)
 * \brief MScores ajoute un score meilleur au fichier score
 * \param Name[in] nom du scoreur
 * \param Score[in] score du joueur
 * \param Key[in] clef de chiffrement
 */
void MScores(string & Name, unsigned & Score, const unsigned Key);

/*!
 * \fn string GetStringName(const unsigned & MaxSize)
 * \brief GetStringName enregistre le nom du joueur
 * \param MaxSize[in] taille maximum du nom
 * \return nom du scoreur
 */
string GetStringName(const unsigned & MaxSize);

/*!
 * \fn void SaveScores(unsigned & Score, const unsigned & Key, string & File)
 * \brief SaveScores demande au joueur d'enregistrer son nom
 * \param Score[in] score du joueur
 * \param Key[in] clef de chiffrement
 * \param File[in,out] fichier où on veut enregistrer
 */
void SaveScores(unsigned & Score, const unsigned & Key, string & File);

#endif // SCORES_H
