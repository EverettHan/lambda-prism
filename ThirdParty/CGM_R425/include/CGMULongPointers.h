/* -*-c++-*- */
#ifndef CGMULongPointers_H
#define CGMULongPointers_H
// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
// Table d'assocation CATULONGPTR -> CATULONGPTR
// implementee par une table de hachage classique
//=============================================================================
// Mar. 02   Creation  TCX
//=============================================================================
#include "CATMathematics.h"
#include "CATCGMNewArray.h"
#include "CATDataType.h"

class CGMULongPointers
{
public:
  inline  CGMULongPointers(CATULONGPTR iOld, CATULONGPTR iNew) : _Old(iOld), _New(iNew) {}
  inline ~CGMULongPointers() { _Old=0; _New=0; }
  CATCGMNewClassArrayDeclare;

  CATULONGPTR    _Old;
  CATULONGPTR    _New;
};

#include "CATHTAB_Clean.h"
#define CATHTAB_Insert
#define CATHTAB_Locate
#define CATHTAB_Next
#define CATHTAB_KeyLocate
#define	CATHTAB_NextPosition
#define CATHTAB_Remove
#define CATHTAB_RemoveAll

#include "CATHTAB_Declare.h"
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATMathematics
CATHTAB_DECLARE( CGMULongPointers )

ExportedByCATMathematics unsigned int HashKeyCGMULongPointers(CGMULongPointers* inew);
ExportedByCATMathematics int          CompareCGMULongPointers(CGMULongPointers* i1, CGMULongPointers *i2);                                    

#endif
