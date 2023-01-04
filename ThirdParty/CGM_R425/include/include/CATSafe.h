#ifndef CATSafe_H
#define CATSafe_H

// COPYRIGHT DASSAULT SYSTEMES 2004

// RR: Generic definition for Safe Access to Class
// Definition Sample: CATSafe(CATMyClass);
// Usage Sample: 

// in MyClass.h
// #include CATSafe.h
// CATSafeDefine(CATMyClass);       

// in any source
// CATMyClass* MyPtr = ...;
// CATSafe(MyPtr)->MyClassAnyMethod();  // Is Safe !
// ...
// CATLISTP(CATMyClass) MyList;
// CATSafe(MyList[i])->->MyClassAnyMethod(); // Is Safe !

#include "CATTopOpIntError.h"
#include "CATMathInline.h"

#define CATSafeDefine(myClass) \
class myClass; INLINE myClass* CATSafe(myClass* iPtr) { myClass* newPtr=iPtr; if (NULL==newPtr) CATThrow(new CATTopOpIntError(TopOpIntRibbonInternalError,"TopOpIntRibbonInternalError",TopOpIntFile)); return newPtr; }

// Definitions for base classes:
CATSafeDefine(CATICGMObject);
CATSafeDefine(CATGeometry);
CATSafeDefine(CATBody);
CATSafeDefine(CATDomain);
CATSafeDefine(CATCell);
CATSafeDefine(CATVertex);
CATSafeDefine(CATEdge);
CATSafeDefine(CATFace);
//...

#endif


