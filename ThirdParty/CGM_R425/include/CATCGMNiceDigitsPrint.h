#ifndef CATCGMNiceDigitsPrint_h
#define CATCGMNiceDigitsPrint_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//==========================================================================

#include "CATDataType.h"
#include <iostream.h>
#include <iomanip.h>
#include <stdio.h>
#include "CATMathematics.h"

void ExportedByCATMathematics CATCGMNiceDigitsPrint(CATULONG64 value,  ostream &outputText, short ForcePrintOn15characters = 1 );
void ExportedByCATMathematics CATCGMNiceBytesPrint(CATULONG64 nbytes,  ostream &logstat );
void ExportedByCATMathematics CATCGMNiceTimesPrint(CATULONG64 valueMs,  ostream &outputText );
ExportedByCATMathematics char *  CATCGMNiceDigitsPrintStatic(CATULONG64 value,  short ForcePrintOn15characters = 1,  short index = 1);

#endif

