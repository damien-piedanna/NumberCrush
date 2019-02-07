#include "useractions.h"
#include "consolemanagement.h"
#include "params2.h"

using namespace std;

unsigned GetUnsigned (unsigned min, unsigned max)
{
    unsigned choix = 0;
    while (true)
    {
        cin >> choix;
        if (cin.fail() || choix > max || choix < min)
        {
            cout << "Valeur incorrecte ("<< min << '-' << max << ')' << endl << endl;
            ClearBuf();
            continue;
        }
        break;
    }
    return choix;
} // GetUnsigned()

CPosition GetPos(CPosition & Pos, unsigned & Size_col, unsigned & Size_lin)
{
    cout << "Numéro colonne (1 - " << Size_col << ") : ";
    Pos.second = (GetUnsigned(1,Size_col) - 1);
    cout << "Numéro ligne (1 - " << Size_lin << ") : ";
    Pos.first = (GetUnsigned(1,Size_lin) - 1);
    return Pos;
} // GetPos()

char GetDirection (char Direction)
{
    while (true)
    {
        cout << "Direction (Haut : "<<MoveUp<<", Gauche : "<<MoveLeft<<", Bas : "<<MoveDown<<", Droite : "<<MoveRight<<") ? ";
        cin >> Direction;
        cout << endl;
        Direction = toupper(Direction);
        if (Direction == MoveUp || Direction == MoveLeft || Direction == MoveDown || Direction == MoveRight) break;
        ClearBuf ();
    }
    return Direction;
} // GetDirection()
