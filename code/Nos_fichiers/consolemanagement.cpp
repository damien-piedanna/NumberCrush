#include "Nos_fichiers/jeu.h"
#include <limits>
#include <unistd.h>

void Couleur (const string & coul)
{
    cout << "\033[7;" << coul <<"m";
} // Couleur()

void ClearBuf ()
{
    cin.clear ();
    cin.ignore (numeric_limits<streamsize>::max(), '\n');

} // ClearBuf()

void Pause (float secondes)
{
    usleep(secondes*1e6);
} // Pause()
