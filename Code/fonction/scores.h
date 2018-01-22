#ifndef MAIN_COPY_H
#define MAIN_COPY_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

ifstream ifs;
ofstream ofs;

typedef vector <string> CVString;

void RetrieveData(CVString & VString);

void WriteData(CVString & VString);

unsigned GetScore (CVString & VScores,const unsigned & Ligne);

string GetName(CVString & VScores, const unsigned & Ligne);

void DescendreLignes(CVString & VScores,const unsigned & Ligne);

void AjustementLignes(CVString & VScores);

void ModifScores (CVString & VScores,const unsigned & Score,const string & Name);

void ChiffreCesar(string & Ligne,const unsigned Key);

void DeChiffreCesar(string & Ligne,const unsigned Key);

void MScores(string & Name, unsigned & Score);

#endif // MAIN_COPY_H
