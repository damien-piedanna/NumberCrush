#include "params2.h"

using namespace std;

void DisplayCouleur(const int & Chiffre)
{
    switch (Chiffre)
    {
        case 1 :
            Couleur("30"); // Chiffre 1 en Noir
        break;
        case 2 :
            Couleur("31"); // Chiffre 2 en Rouge
        break;
        case 3 :
            Couleur("32"); // Chiffre 3 en Vert
        break;
        case 4 :
            Couleur("33"); // Chiffre 4 en Jaune
        break;
        case 5 :
            Couleur("34"); // Chiffre 5 en Bleu
        break;
        case 6 :
            Couleur("35"); // Chiffre 6 en Magenta
        break;
        case 7 :
            Couleur("36"); // Chiffre 7 en Cyan
        break;
        case 8 :
            Couleur("37"); // Chiffre 8 en Gris
        break;
        case 12 :
            Couleur("37"); // Mur Gris
        break;
    }

} // DisplayCouleur()
