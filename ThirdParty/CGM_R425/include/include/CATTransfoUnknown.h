/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATTransfoUnknown: Mother class of CATTransformationReplace,
//                    CATTransfoDuplicate and CATTransfoInNewFactory
// 
//=============================================================================
// Usage notes:
//
// 
// 
//
//=============================================================================
// Abstract Class     : Yes
// Inline Functions   : No
//=============================================================================
// Oct. 97 Creation                                               ILY (I. Levy)
// Apr. 04 _CheckInvariance et SetCheckInvariance(...) pour RI 444339     HCN
//=============================================================================
#ifndef CATTRANSFOUNKNOWN_H
#define CATTRANSFOUNKNOWN_H

//Windows compatibility
#include "YP00IMPL.h"

#include "CATTransfoManager.h"
class CATMapGeoToAssoc;

class CATGeometry;
class CATSurface;
class CATCurve;
class CATTransfoManager;
class CATMathTransformation2D;
class CATMathTransformation1D;

//-----------------------------------------------------------------------------
class ExportedByYP00IMPL CATTransfoUnknown
{
public:
  enum CATScanMode {Duplicate, FullDuplicate, Replace};
  //---------------------------------------------------------------------------
  //- Constructor
  //---------------------------------------------------------------------------
  CATTransfoUnknown(CATTransfoManager* iTransfoManager    ,
		    CATLONG32               iTransfoManagerType);

  //---------------------------------------------------------------------------
  //- Destructor
  //---------------------------------------------------------------------------
  virtual ~CATTransfoUnknown();

  //---------------------------------------------------------------------------
  //- Run: finds the objects that need to be duplicated
  //-      and calculate the transformed objects if necessary
  //--------------------------------------------------------------------------
  virtual void Run(CATMapGeoToAssoc* iAssocList, CATLONG32 iNoFindLinks = 0 ) = 0 ;

  //---------------------------------------------------------------------------
  //- Compute: returns the transformed support (general case)
  //---------------------------------------------------------------------------
  virtual void Compute(CATGeometry      *  iIn,
		       CATMapGeoToAssoc *  iAssocList,
		       CATGeometry      * &oOut) = 0 ;

  //---------------------------------------------------------------------------
  //- ComputeUV: returns the transformed support and
  //- the transformation of a 2 dimension support (Surface)
  //---------------------------------------------------------------------------
  virtual void ComputeUV(CATSurface              *  iIn,
			 CATMapGeoToAssoc        *  iAssocList,
			 CATSurface              * &oOut,
			 CATMathTransformation2D * &oTransfo2D) = 0 ;

  //---------------------------------------------------------------------------
  //- ComputeW: returns the transformed support and
  //- the transformation of a 1 dimension support (Curve)
  //---------------------------------------------------------------------------
  virtual void ComputeW(CATCurve                *  iIn,
			CATMapGeoToAssoc        *  iAssocList,
			CATCurve                * &oOut,
			CATMathTransformation1D * &oTransfo1D) = 0 ;

  //---------------------------------------------------------------------------
  //- IsInvariant: returns 1 if an object is invariant (general case)
  //---------------------------------------------------------------------------
  virtual CATLONG32 IsInvariant(CATGeometry      * iIn,
                           CATMapGeoToAssoc * iAssocList);

  //---------------------------------------------------------------------------
  //- IsInvariantW: returns 1 if a 1D object is invariant else returns 0
  //---------------------------------------------------------------------------
  virtual CATLONG32 IsInvariantW(CATCurve                * iIn,
			    CATMapGeoToAssoc        *  iAssocList,
                            CATMathTransformation1D * oTransfo1D = NULL);

  //---------------------------------------------------------------------------
  //- IsInvariantUV: returns 1 if a 2D object is invariant else returns 0
  //---------------------------------------------------------------------------
  virtual CATLONG32 IsInvariantUV(CATSurface              * iIn,
			     CATMapGeoToAssoc        * iAssocList,
                             CATMathTransformation2D * oTransfo2D = NULL);

  //---------------------------------------------------------------------------
  //- IsModified: returns 1 if an object is modified
  //---------------------------------------------------------------------------
  CATLONG32 IsModified(CATGeometry *            iIn     ,
                  CATMapGeoToAssoc*        iAssocList);

  //---------------------------------------------------------------------------
  //- SetCheckInvariance
  //---------------------------------------------------------------------------
  void SetCheckInvariance(CATBoolean iMode);

  virtual void ObjectAdded(CATICGMObject * iIn);

protected:
  CATTransfoManager* _TransfoManager;
  CATLONG32               _FactoryIsExplicit;
  int                _CheckBoxStop; //In order to enable several runs
  CATLONG32               _Type;
  CATMapGeoToAssoc * _ListOfSurLimits;
  CATBoolean         _CheckInvariance;
  
  //---------------------------------------------------------------------------
  //- FindLinks: finds the links of the object and adds attributes 
  //- to these links if they are not specified In Entry
  //  if Mode==Replace, also detects whether objects need to be replaced
  //---------------------------------------------------------------------------
  virtual void FindLinks(CATGeometry      * iIn,
                         CATMapGeoToAssoc * iAssocList,
                         CATScanMode        iMode = Duplicate);

  //---------------------------------------------------------------------------
  //- CheckInvarianceOfLinks: if all the links of the object
  //- are invariant, return (1), else return (0)
  //---------------------------------------------------------------------------
  virtual CATLONG32 CheckInvarianceOfLinks(CATGeometry      * iIn,
                                      CATMapGeoToAssoc * iAssocList);

  //---------------------------------------------------------------------------
  //- AnalysisOfLinks: Analysis of Links with SharedStatus != 0
  //---------------------------------------------------------------------------
  virtual void AnalysisOfLinks(CATGeometry      * iIn,
                               CATMapGeoToAssoc * iAssocList,
                               CATScanMode        iMode = Duplicate);

  //---------------------------------------------------------------------------
  //- DecreaseCountOfLinks: apply Decrease CurrentCount of each link (recursive)
  //---------------------------------------------------------------------------
  void DecreaseCountOfLinks(CATGeometry      * iIn,
			    CATMapGeoToAssoc * iAssocList);

  //---------------------------------------------------------------------------
  //- Check that T(_BoxUV) in contained in the MaxLimits of Out
  //---------------------------------------------------------------------------
  void CheckBox(CATGeometry      * iIn,
		CATGeometry      * iOut,
		CATMapGeoToAssoc * iAssocList);
  
  //---------------------------------------------------------------------------
  //- IsTopology: returns 1 if In is a topological object
  //---------------------------------------------------------------------------
  CATLONG32 IsTopology(CATGeometry * iIn);

  //---------------------------------------------------------------------------
  //- IsClosed: returns 1 if In is a closed
  //---------------------------------------------------------------------------
  CATLONG32 IsClosed(CATCurve * iIn);

};
#endif
