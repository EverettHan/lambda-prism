#ifndef CATMathStopDiagnostic_H 
#define CATMathStopDiagnostic_H 


// COPYRIGHT DASSAULT SYSTEMES 1999
#include "CATDataType.h"

typedef  CATLONG32 CATMathStopDiagnostic;

#define   CATMathNoStop                        0
#define   CATMathStopByDomain                  1
#define   CATMathStopByStartingPoint           2
#define   CATMathStopInsideDomain              4
#define   CATMathStopByUserConstraint          8
#define   CATMathStopByEndPoints              16
#define   CATMathStopBySingularPoint          32
#define   CATMathStopByMaximumParam           64
#define   CATMathStopOnFirstPoint            128
#define   CATMathStopByStartingPointOnDomain 256
#define   CATMathStopByMaxDomain             512
#define   CATMathTooMuchPoints              1024

#endif
