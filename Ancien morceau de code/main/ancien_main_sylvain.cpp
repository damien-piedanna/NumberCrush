#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

void ClearScreen ()
{
    cout << "\033[H\033[2J";
}

void Couleur (const string & coul)
{
    cout << "\033[" << coul <<"m";
}

int rand_a_b (int a, int b) {

    return rand()%(b-a) +a;
}

namespace {


const string KReset   ("0");
const string KNoir    ("30");
const string KRouge   ("31");
const string KVert    ("32");
const string KJaune   ("33");
const string KBleu    ("34");
const string KMAgenta ("35");
const string KCyan    ("36");


typedef vector <unsigned> CVLine;
typedef vector <CVLine> CMat;
typedef pair <unsigned, unsigned> CPosition;

}

void InitGrid (CMat & Grid, unsigned Size)
{
    Grid.resize(Size);

    for (unsigned i=0 ; i < Grid.size(); ++i)
    {
        Grid[i].resize(Size);
    }


    srand(time(NULL));


    for(unsigned i=0 ; i< Size ; ++i)
    {

        for(unsigned i2=0; i2< Size ; ++i2)
        {


           Grid[i][i2] = rand_a_b(0,10);

        }
    }

}

void MakeAMove (CMat & Grid, const CPosition & Pos, char Direction)
{
    unsigned Stock;
     Stock =Grid[Pos.first][Pos.second];

    switch (Direction) {
        case 'z':


        if(Pos.first != 0)
        {

           Grid[Pos.first][Pos.second] = Grid[Pos.first-1][Pos.second];
            Grid[Pos.first-1][Pos.second] = Stock;
         }

        break;

    case 'q':
        if(Pos.second != 0)
        {

       Grid[Pos.first][Pos.second] = Grid[Pos.first][Pos.second-1];
        Grid[Pos.first][Pos.second-1] = Stock;
        }

    break;

    case 's':

        if(Pos.first != (Grid[Pos.first].size()) -1)
        {

        Grid[Pos.first][Pos.second] = Grid[Pos.first+1][Pos.second];
        Grid[Pos.first+1][Pos.second] = Stock;
        }

    break;

    case 'd':

        if(Pos.second != (Grid[Pos.first].size()) - 1)
        {

        Grid[Pos.first][Pos.second]= Grid[Pos.first][Pos.second+1];
        Grid[Pos.first][Pos.second+1] = Stock;
        }

    break;

        default:

        cout << "commande inconnue";

            break;


    }
}

void  DisplayGrid (const CMat & Grid)
{
    ClearScreen();

    for(unsigned i=0 ; i< Grid.size() ; ++i)
    {

        for(unsigned i2=0; i2< Grid[i].size() ; ++i2)
        {
            if( Grid[i][i2] <= 5)
            {
            cout << Grid[i][i2] << '|';
            }
            else
            {
            cout << ' '  << '|';
            }
        }
        cout << endl;
    }

    cout << endl;
    cout <<  "----------------------------" << endl;
}

bool AtLeastThreeInAColumn (const CMat & Grid, CPosition & Pos, unsigned & HowMany)
{
   unsigned cpt = 1;
   unsigned Start = 0;

   for(unsigned i=0 ; i < Grid[0].size() ; ++i)
   {
       for(unsigned j=0 ; j <= Grid.size() - HowMany +1 ; ++j)
       {
           if(Grid[j][i] > 5)
           {
               cpt = 1;
               continue;
           }

           if(Start == 0 && Grid[j][i] == Grid[j+1][i])
           {
               Start = 1;
               Pos.first = j;
               Pos.second = i;
           }

           if(Grid[j][i] == Grid[j+1][i])
           {
               cpt = cpt + 1;
           }
           if(Grid[j][i] != Grid[j+1][i] && cpt >= HowMany)
           {
               return true;
           }
           if (Grid[j][i] != Grid[j+1][i])
           {
               cpt = 1;
               Start = 0;
           }

           if( j == ( (Grid.size() - HowMany) +1) && cpt >= HowMany )
           {

               return true;

           }
       }
   }

    return false;
}

bool AtLeastThreeInARow (const CMat & Grid, CPosition & Pos, unsigned & HowMany)
{
    unsigned cpt = 1;
    unsigned Start = 0;

    for(unsigned j=0 ; j < Grid.size() ; ++j)
    {
        for(unsigned i=0 ; i <= Grid[0].size() - HowMany +1 ; ++i)
        {
            if(Grid[j][i] > 5)
            {
                cpt = 1;
                continue;
            }

            if(Start == 0 && Grid[j][i] == Grid[j][i+1])
            {
                Start = 1;
                Pos.first = j;
                Pos.second = i;
            }

            if(Grid[j][i] == Grid[j][i+1])
            {
                cpt = cpt + 1;

            }
            if(Grid[j][i] != Grid[j][i+1] && cpt >= HowMany)
            {

                return true;
            }
            if (Grid[j][i] != Grid[j][i+1])
            {
                cpt = 1;
                Start = 0;
            }

            if( i == ( (Grid[0].size() - HowMany) +1) && cpt >= HowMany )
            {

                return true;
            }
        }
    }

     return false;
}

void RemovalInColumn (CMat & Grid, const CPosition & Pos, unsigned  HowMany)
{
    unsigned a;
    a = Grid[Pos.first][Pos.second];

    unsigned i = Pos.first;

    while(i != Grid.size() && Grid[i][Pos.second] == a)
    {
        Grid[i][Pos.second] = 99;

        ++i;
    }
}


void RemovalInRow (CMat & Grid, const CPosition & Pos, unsigned  HowMany)
{
    unsigned a;
    a = Grid[Pos.first][Pos.second];

    unsigned i = Pos.second;

    while(i != Grid[0].size() && Grid[Pos.first][i] == a)
    {
        Grid[Pos.first][i] = 99;

        ++i;
    }
}

int main()
{
    CMat Grid;
    InitGrid(Grid,5);
    DisplayGrid(Grid);

    while(true)
    {
        unsigned HowMany = 3;
        unsigned PosFirst;
        unsigned PosSecond;
        char Commande;
        CPosition Pos;


        if(AtLeastThreeInAColumn(Grid, Pos,HowMany))
        {

            RemovalInColumn (Grid, Pos, HowMany);
            DisplayGrid(Grid);
        }


        if(AtLeastThreeInARow(Grid, Pos,HowMany))
        {

            RemovalInRow(Grid, Pos, HowMany);
            DisplayGrid(Grid);
        }


        do {
            for(;;)
            {
                cout << "Inserer coordonnÃ©e 1" << endl;
                cin >> PosFirst;

                if (cin) break;

                if(cin.fail())
                {
                    cout << "echec de lecture" << endl;
                    cin.clear();
                    string Buf;
                    getline(cin, Buf);
                }
            }
            if(PosFirst <= 4) break;
            cout << "Taper un chiffre entre 0 et 4" << endl;
        }while(true);

        do{
            for(;;)
            {
                cout << "Inserer coordonnÃ©e 2" << endl;
                cin >> PosSecond;
                if (cin) break;
                if(cin.fail())
                {
                    cout << "echec de lecture" << endl;
                    cin.clear();
                    string Buf;
                    getline(cin, Buf);
                }
            }
            if(PosFirst <= 4) break;
            cout << "Taper un chiffre entre 0 et 4" << endl;
        }while(true);

        while(true)
        {
        cout << "Taper une commande" << endl;
        cin >> Commande;
        Commande=tolower(Commande);
        if(Commande == 'z' || Commande == 'q' || Commande == 's' || Commande == 'd') break;
        cout << "Commande invalide (z,q,s,d)" << endl;
        }


        Pos.first = PosFirst;
        Pos.second = PosSecond;

         MakeAMove (Grid, Pos, Commande);
         DisplayGrid(Grid);


    }

    return 0;
}
