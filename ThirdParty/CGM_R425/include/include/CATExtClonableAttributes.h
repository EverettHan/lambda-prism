#ifndef CATExtClonableAttributes_h_
#define CATExtClonableAttributes_h_
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//
//  INTERDICTION D'INCLURE DANS HEADER CAA
//  HEADER IMPLEMENTATION : PERMETTRE EVOLUTION VUE IMPLEMENTATIVE
//
//=============================================================================
#include "CATExtGeoOperator.h"
#include "CATCloneManager.h"
#include "CATICGMObject.h"
#include "YP00IMPL.h"

class CATICGMObject;
class CATCGMAttribute;
#include "CATListOfCATCGMAttribute.h"
#include "CATMathInline.h"


class ExportedByYP00IMPL CATExtClonableAttributes 
{
public :
  CATExtClonableAttributes(CATICGMObject* iOrigin, CATICGMObject* iDestination,
                           CATLISTP(CATCGMAttribute) & ioAttributesList);

  ~CATExtClonableAttributes();

  INLINE CATICGMObject               *GetOrigin() const;
  INLINE CATICGMObject               *GetDestination() const;
  INLINE CATLISTP(CATCGMAttribute)   *GetAttributesList() const;

  CATCGMNewClassArrayDeclare;

protected :
  CATICGMObject*              _Origin;
  CATICGMObject*              _Destination;
  CATLISTP(CATCGMAttribute) _AttributesList;
};


INLINE CATICGMObject               *CATExtClonableAttributes::GetOrigin() const 
{ return _Origin;}

INLINE CATICGMObject               *CATExtClonableAttributes::GetDestination() const
{ return _Destination;}

INLINE CATLISTP(CATCGMAttribute)   *CATExtClonableAttributes::GetAttributesList() const
{ return (CATLISTP(CATCGMAttribute)   *)&_AttributesList;}

// BreakPoint de gestion des integrations
extern "C" ExportedByYP00IMPL void  catcgmreportodo();   
extern "C" ExportedByYP00IMPL void  catcgmreportdone();   


#endif
