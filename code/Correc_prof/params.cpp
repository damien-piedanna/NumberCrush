#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Correc_prof/params.h"
#include "game.h"

using namespace std;


void InitParams (CMyParam & Param)
{
    //Move Keys
    Param.MapParamChar["KeyUp"]   = 'z';
    Param.MapParamChar["KeyDown"] = 's';
    Param.MapParamChar["KeyLeft"] = 'q';
    Param.MapParamChar["KeyRight"] = 'd';


    //Size of grid -- suppose to be squared
    Param.MapParamUnsigned["GridSize"] = 10;

    //Display Colors
    Param.MapParamString["LineColor"] = KColor.find("KRed")->second ;
    Param.MapParamString["RowColor"] = KColor.find("KGreen")->second ;
    Param.MapParamString["IndexColor"] = KColor.find("KBlue")->second ;
    Param.MapParamString["MyColor"] = KColor.find("KBack")->second ;
}

void LoadParams (CMyParam & Param)
{
    ifstream ifs ("../M1103-ProjetNumberCrush/Nos_fichiers/config.yaml");
    if (!ifs.is_open())
    {
        cerr << "pas le bon fichier de configuration";
        exit (2);
    }
    string Key;
    while (ifs >> Key)
    {
        char tmp;
        ifs >> tmp;
        if (find (KAuthorizedKey.VParamChar.begin(), KAuthorizedKey.VParamChar.end(), Key) != KAuthorizedKey.VParamChar.end())
            ifs >> Param.MapParamChar[Key];
        else if (find (KAuthorizedKey.VParamUnsigned.begin(), KAuthorizedKey.VParamUnsigned.end(), Key) != KAuthorizedKey.VParamUnsigned.end())
            ifs >> Param.MapParamUnsigned[Key];
        else if (find (KAuthorizedKey.VParamString.begin(), KAuthorizedKey.VParamString.end(), Key) != KAuthorizedKey.VParamString.end())
        {
            string Val;
            ifs >> Val;
            Param.MapParamString[Key] = KColor.find(Val)->second;
        }
    }
}
