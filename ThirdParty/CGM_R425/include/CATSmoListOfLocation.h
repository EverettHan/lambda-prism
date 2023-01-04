//====================================================================
// Copyright Dassault Systemes Provence 2007, all rights reserved 
//====================================================================
//
// CATSmoListOfLocation.h
//
//====================================================================
//
// Usage notes:
//
//====================================================================
// August,     2007 : RNO : Creation CATSmoListOfLocation.h
//====================================================================
#ifndef CATSmoListOfLocation_h
#define CATSmoListOfLocation_h

#include "CATSmoOperators.h"

#include "CATLISTV_Clean.h"

#include "CATSmoEvalLocation.h"

/**
 * @nodoc 
 */
inline int operator == (const CATSmoEvalLocation &Location1, const CATSmoEvalLocation &Location2)
{
  return( Location1._SobFace==Location2._SobFace &&
          Location1._Level==Location2._Level &&
          Location1._u==Location2._u &&
          Location1._v==Location2._v &&
          Location1._Daughter==Location2._Daughter);
          
}
/**
 * @nodoc 
 */
inline int operator != (const CATSmoEvalLocation &Location1, const CATSmoEvalLocation &Location2)
{
	  return( Location1._SobFace!=Location2._SobFace ||
          Location1._Level!=Location2._Level ||
          Location1._u!=Location2._u ||
          Location1._v!=Location2._v ||
          Location1._Daughter!=Location2._Daughter);
}
#define  CATLISTV_Append
#define	CATLISTV_InsertAt
#define	CATLISTV_RemovePosition
//#include "CATLISTV_AllFunct.h"

#include "CATLISTV_Declare.h"


#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATSmoOperators

CATLISTV_DECLARE (CATSmoEvalLocation)
#endif
