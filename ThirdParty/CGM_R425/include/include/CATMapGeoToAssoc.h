/* -*-c++-*- */
#ifndef CATMapCurveTransfo_h_
#define CATMapCurveTransfo_h_

// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMapCurveTransfo
//
// Table a accès rapide pour  lire .
// Mapping is defined by two geometric pointers + several  "attribut" pointer (Geo1,Geo2,Attr1, 
// , ... Attrn) and is not symetric - direct access is done with "hastable mechanism" on Geo1.  
//
//=============================================================================
// Usage Notes:
//=============================================================================
// Jui. 98                                                          lr
// Avr. 2002  Migration vers CATCGMHashTableWithAssoc                HCN
//=============================================================================

#include "YP00IMPL.h"

#include "CATCGMHashTableWithAssoc.h"
#include "CATCGMNewArray.h"

class CATAssociation;
class CATICGMObject;

class ExportedByYP00IMPL CATMapGeoToAssoc : public CATCGMHashTableWithAssoc
{
public:
  CATMapGeoToAssoc(int iEstimatedSize);
  ~CATMapGeoToAssoc();
  CATCGMNewClassArrayDeclare;
    
  inline int             Insert(CATICGMObject* ipCGMObject, CATAssociation* ipAssoc);
  inline CATAssociation* Locate(CATICGMObject* ipCGMObject);
  inline CATICGMObject*  GetGeo(int iPos);
  inline CATAssociation* GetAssoc(int iPos);
};

//-----------------------------------------------------------------------------
// GetItem
//-----------------------------------------------------------------------------
int CATMapGeoToAssoc::Insert(CATICGMObject* ipCGMObject, CATAssociation* ipAssoc)
{
  return (this->CATCGMHashTableWithAssoc::Insert((void*)ipCGMObject, (void*)ipAssoc));
}

//-----------------------------------------------------------------------------
// Locate
//-----------------------------------------------------------------------------
CATAssociation* CATMapGeoToAssoc::Locate(CATICGMObject* ipCGMObject)
{
  return ((CATAssociation*)this->CATCGMHashTableWithAssoc::LocateAssoc((void*)ipCGMObject));
}

//-----------------------------------------------------------------------------
// GetGeo
//-----------------------------------------------------------------------------
CATICGMObject* CATMapGeoToAssoc::GetGeo(int iPos)
{
  return ((CATICGMObject*)this->CATCGMHashTableWithAssoc::GetItem(iPos));
}

//-----------------------------------------------------------------------------
// GetAssoc
//-----------------------------------------------------------------------------
CATAssociation* CATMapGeoToAssoc::GetAssoc(int iPos)
{
  return ((CATAssociation*)this->CATCGMHashTableWithAssoc::GetAssoc(iPos));
}


#endif 
