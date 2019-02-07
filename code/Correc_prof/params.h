#ifndef PARAMS_H
#define PARAMS_H

#include "Correc_prof/type.h"

const unsigned KNbCandies  = 4;
const unsigned KMaxTimes   = 20;
const unsigned KImpossible = KNbCandies + 2;


void InitParams (CMyParam & Param);

void LoadParams (CMyParam & Param);
#endif // PARAMS_H
