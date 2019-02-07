#ifndef GRIDMANAGEMENT_H
#define GRIDMANAGEMENT_H

#include <string>

#include "Correc_prof/type.h" //nos types
#include "Correc_prof/nsutil.h"

void ClearScreen ();

void Color (const std::string & Col);

void DisplayGridWithLineAndColumnNumbersAndColor (const CMat & Mat, const CMyParam & Params);

void DisplayGridWithLineAndColumnNumbers (const CMat & Mat);

void DisplayGrid (const CMat & Mat, const CMyParam & Params, bool ShowLineNumber = true, bool ShowColor = true);



void InitGrid (CMat & Grid, unsigned Size);

#endif // GRIDMANAGEMENT_H
