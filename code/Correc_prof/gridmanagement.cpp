#include <iostream>
#include <iomanip>
#include "gridmanagement.h"

#include "Correc_prof/type.h" //nos types
#include "Correc_prof/params.h" //nos parametres

using namespace std;



void ClearScreen()
{
    cout << "\033[H\033[2J";
}// ClearScreen ()

void Color (const string & Col)
{
    cout << "\033[" << Col.c_str () <<"m";
} // Color ()

void DisplayGridWithLineAndColumnNumbersAndColor (const CMat & Mat, const CMyParam & Param)
{

    ClearScreen ();
    cout << string (4, ' ');
    for (unsigned i (0); i < Mat.size (); ++i)
    {
        Color (Param.MapParamString.find("IndexColor")->second);

        cout << setw (2) << i;

        Color (Param.MapParamString.find("RowColor")->second);
        cout<< setw (2) << '|';
    }
    cout << endl;
    string Rule (4*Mat.size () + 1, '=');
    Rule = string (3, ' ') + Rule;


    Color (Param.MapParamString.find("LineColor")->second);
    cout << Rule << endl;
    unsigned LineNumber (0);
    for (const CVLine & Aline : Mat)
    {

        Color (Param.MapParamString.find("IndexColor")->second);

        cout << setw (2) << LineNumber++;
        Color (Param.MapParamString.find("RowColor")->second);

        cout << "||";
        for (auto Cel : Aline)
        {

            Color (Param.MapParamString.find("MyColor")->second);
            cout << setw (2);
            if (KImpossible == Cel)
                cout << ' ';
            else
                cout << Cel;
            Color (Param.MapParamString.find("RowColor")->second);

            cout<< setw (2) << '|';
        }
        Color (Param.MapParamString.find("LineColor")->second);

        cout << endl << Rule << endl;
    }
    Color (KColor.find("KReset")->second);

} // DisplayWithLineAndColumnNumbersAndColor ()

void DisplayGridWithLineAndColumnNumbers (const CMat & Mat)
{
    ClearScreen ();
    cout << string (4, ' ');
    for (unsigned i (0); i < Mat.size (); ++i)
        cout << setw (2) << i << setw (2) << '|';
    cout << endl;
    string Rule (4*Mat.size () + 1, '=');
    Rule = string (3, ' ') + Rule;
    cout << Rule << endl;
    unsigned LineNumber (0);
    for (const CVLine & Aline : Mat)
    {
        cout << setw (2) << LineNumber++ << '|';
        cout << '|';
        for (auto Cel : Aline)
            cout << setw (2) << Cel << setw (2) << '|';
        cout << endl << Rule << endl;
    }
} // DisplayWithLineAndColumnNumbers ()

void DisplayGrid (const CMat & Mat, const CMyParam & Param, bool ShowLineNumber /*= true*/, bool ShowColor /*= true*/)
{
    ClearScreen ();
    if (ShowLineNumber)
    {
        if (ShowColor)
            DisplayGridWithLineAndColumnNumbersAndColor (Mat, Param);
        else
            DisplayGridWithLineAndColumnNumbers (Mat);
        return;
    }

    string Rule (4*Mat.size () + 1, '=');
    cout << Rule << endl;
    for (const CVLine & Aline : Mat)
    {
        cout << '|';
        for (auto Cel : Aline)
            cout << setw (2) << Cel << setw (2) << '|';
        cout << endl << Rule << endl;
    }
}// DisplayGrid ()

void InitGrid (CMat & Grid, unsigned Size)
{
    Grid.resize (Size);
    for (auto & Line : Grid)
    {
        Line.resize (Size);
        for (auto & Cel : Line)
            Cel = Rand () +1;
     }
} // InitMat ()
