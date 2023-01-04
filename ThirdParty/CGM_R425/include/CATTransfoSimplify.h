/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATTransfoSimplify: Transformation in Simplify mode (no factory change)
// 
//=============================================================================
// Usage notes:
//
// 
// 
//
//=============================================================================
// Abstract Class     : No
// Inline Functions   : No
//=============================================================================
// Sept. 98   Creation                                 ILY (I. Levy)
//=============================================================================
#ifndef CATTRANSFOSIMPLIFY_H
#define CATTRANSFOSIMPLIFY_H

//Windows compatibility
#include "YP00IMPL.h"

//Inheritance library
#include "CATTransfoUnknown.h"

class CATGeometry;
class CATSurface;
class CATCurve;
class CATTransfoManager;
class CATMathTransformation2D;
class CATMathTransformation1D;

//-----------------------------------------------------------------------------
class ExportedByYP00IMPL CATTransfoSimplify: public CATTransfoUnknown
{
public:
  //---------------------------------------------------------------------------
  //- Constructor
  //---------------------------------------------------------------------------
  CATTransfoSimplify(CATTransfoManager* iTransfoManager    ,
		     CATLONG32               iTransfoManagerType);
  
  //---------------------------------------------------------------------------
  //- Destructor
  //---------------------------------------------------------------------------
  virtual ~CATTransfoSimplify();
  
  //---------------------------------------------------------------------------
  //- Run: finds the objects that need to be duplicated
  //-      and calculate the transformed objects if necessary
  //--------------------------------------------------------------------------
  virtual void Run( CATMapGeoToAssoc * iAssociationList, CATLONG32 iNoFindLinks = 0);
  
  //---------------------------------------------------------------------------
  //- Compute: returns the transformed support (general case)
  //---------------------------------------------------------------------------
  virtual void Compute(CATGeometry*  iIn     ,
               CATMapGeoToAssoc*     iAssocList,
               CATGeometry* &oOut    );
  
  //---------------------------------------------------------------------------
  //- ComputeUV: returns the transformed support and
  //- the transformation of a 2 dimension support (Surface)
  //---------------------------------------------------------------------------
  virtual void ComputeUV(CATSurface*               iIn       ,
                 CATMapGeoToAssoc*     iAssocList ,
                 CATSurface*              &oOut      ,
                 CATMathTransformation2D* &oTransfo2D);
  
  //---------------------------------------------------------------------------
  //- ComputeW: returns the transformed support and
  //- the transformation of a 1 dimension support (Curve)
  //---------------------------------------------------------------------------
  virtual void ComputeW(CATCurve*                 iIn       ,
                CATMapGeoToAssoc*     iAssocList ,
                CATCurve*                &oOut      ,
                CATMathTransformation1D* &oTransfo1D);

  //---------------------------------------------------------------------------
  //- IsInvariant: returns 1 if an object is invariant (general case)
  //---------------------------------------------------------------------------
  virtual CATLONG32 IsInvariant ( CATAssociation * iAssoc );

  //---------------------------------------------------------------------------
  //- IsInvariantW: returns 1 if a 1D object is invariant else returns 0
  //---------------------------------------------------------------------------
  virtual CATLONG32 IsInvariantW(CATCurve                * iIn              ,
		    CATMapGeoToAssoc*     iAssocList      ,
		    CATMathTransformation1D * oTransfo1D = NULL);

  //---------------------------------------------------------------------------
  //- IsInvariantUV: returns 1 if a 2D object is invariant else returns 0
  //---------------------------------------------------------------------------
  virtual CATLONG32 IsInvariantUV(CATSurface              * iIn              ,
		     CATMapGeoToAssoc*     iAssocList        ,
		     CATMathTransformation2D * oTransfo2D = NULL);

protected:  
  //---------------------------------------------------------------------------
  //- FindLinks: finds the links of the object and adds attributes 
  //- to these links if they are not specified In Entry
  //---------------------------------------------------------------------------
  virtual void FindLinks(CATGeometry* iIn              ,
                 CATMapGeoToAssoc*     iAssocList     ,
                 CATScanMode  iMode = Duplicate);
    
  //---------------------------------------------------------------------------
  //- CheckInvarianceOfLinks: if all the links of the object
  //- are invariant, return (1), else return (0)
  //---------------------------------------------------------------------------
  virtual CATLONG32 CheckInvarianceOfLinks ( CATGeometry      * iIn        ,
                                     CATAssociation   * iAssoc     ,
                                     CATMapGeoToAssoc * iAssocList );

  //---------------------------------------------------------------------------
  //- AnalysisOfLinks: Analysis of Links with SharedStatus != 0
  //---------------------------------------------------------------------------
  virtual void AnalysisOfLinks ( const int          iIndice           ,
                         CATGeometry      * iIn               ,
                         CATMapGeoToAssoc *     iAssocList    ,
                         CATScanMode        iMode = Duplicate );

};
#endif
