#ifndef CATHomotopyDef_H
#define CATHomotopyDef_H

// COPYRIGHT DASSAULT SYSTEMES 1999
#include "CATDataType.h"

typedef CATLONG32 CATHomotopyDiag;
#define CATHomotopyOK                  0
#define CATHomotopyStop                1
#define CATHomotopySpecifiedLimits     2
#define CATHomotopySeamLimits          4
#define CATHomotopyDetectsPathToPole   8
#define CATHomotopyDegenerateSystem    16
#define CATHomotopyDetectsPathFromPole 32


typedef CATLONG32 CATSideToExtrapolate;
#define CATNoSide   0
#define CATSideUMin 1
#define CATSideUMax 2
#define CATSideVMin 4
#define CATSideVMax 8
#define CATSideWMin 16 
#define CATSideWMax 32

typedef CATLONG32 CATSideToOffset;
#define CATSideLeftToOffset      1
#define CATSideRightToOffset     2
#define CATNoSideToOffset        0

// Attention ! Egal a CATTopSharpAngle defini dans CATTopDef.h
#define CATHomotopySharpAngle 0.0087266463


#endif
