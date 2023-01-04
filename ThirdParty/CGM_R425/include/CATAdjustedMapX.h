// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// Base class designed to handle mapping between parametrization of
// two Curves of an EdgeCurve
// For this class, only one curve and its limits on the EdgeCurve are stored
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Jan. 00   Creation                                     R.HAMZA
// 05/06/08 NLD Ajout ForceMaxGap()
// 09/08/11 R1Y Removed the type enum (which is also in CATMapX.h), and added
//              access functions for comparing geometries.
//=============================================================================
#ifndef CATAdjustedMapX_H
#define CATAdjustedMapX_H

#include "YP00IMPL.h"                    
#include "CATMapX.h"
#include "CATBoolean.h"

class CATCrvParam;

//-----------------------------------------------------------------------------
//
class ExportedByYP00IMPL CATAdjustedMapX : public CATMapX 
{
public:
   /** @nodoc */
  CATCGMNewClassArrayDeclare;

  //-------------------------------------------------------------------------
  // Constructors
  //-------------------------------------------------------------------------
	CATAdjustedMapX(CATMapX * iMapX, 
									const CATCrvParam & iStartRef, const CATCrvParam & iEndRef,
									const CATCrvParam & iStartCrv, const CATCrvParam & iEndCrv) ;
	CATAdjustedMapX(CATMapX * iMapX, 
		              const CATCrvParam & iStartCrvMap, const CATCrvParam & iEndCrvMap,
									const CATCrvParam & iStartRef, const CATCrvParam & iEndRef,
									const CATCrvParam & iStartCrv, const CATCrvParam & iEndCrv) ;
    
  //-------------------------------------------------------------------------
  // virtual Destructor
  //-------------------------------------------------------------------------
  virtual ~CATAdjustedMapX();
  
   
    //-------------------------------------------------------------------------
  // Creates CATMathFunctionX* which transforms a parameter expressed on
  // one curve to the parameter expressed on the other.
  // * If iRefCurveFist==1 (default), the function maps from RefCurve to Curve.
  // Otherwise, the function maps from Curve to RefCurve
	// * If iAdjustedC2=1, the returned function is adjusted to have a one-to-one mapping
	// and returns a C2 function.
  // The returned function must be deleted by the caller.
  //-------------------------------------------------------------------------
  virtual CATMathFunctionX* CreateFunctionX(short iRefCurveFirst=1, CATBoolean iAdjustedC2=0, const double * iDomain=0)const;

	//-------------------------------------------------------------------------
  // Gets the relative orientation between the two curves
  //-------------------------------------------------------------------------
  virtual short GetOrientation()const;

  //-------------------------------------------------------------------------
  // Retrieves the MaxGap.
  //-------------------------------------------------------------------------
	virtual double GetMaxGap()const;
  //-------------------------------------------------------------------------
  // Force max gap value
  //-------------------------------------------------------------------------
   virtual void ForceMaxGap(double iMaxGap);
  
  //-------------------------------------------------------------------------
  // Gets the type of mapping
  //-------------------------------------------------------------------------
  virtual short IsATypeOf(CATMapX::Type iType)const;
  virtual CATMapX::Type GetType()const;
  virtual CATBoolean IsAdjustedMapXType() const;

  //-------------------------------------------------------------------------
  // Returns the the mapped oEquivalentParam of a iCurrentParam expressed on iCurrentCurve.
  ///     GetEquivalentParam / GetApproximateEquivalentParam 
  //-------------------------------------------------------------------------

  virtual void GetEquivalentParam(const CATCurve *    iCurrentCurve, 
                                  const CATCrvParam & iCurrentParam,
                                  CATCrvParam &       oEquivalentParam,
                                  short               iReconvergence=1)const;

  virtual void GetApproximateEquivalentParam(const CATCurve          *  iCurrentCurve, 
                                             const CATCrvParam       &  iCurrentParam,
                                             const CATPositiveLength &  iApproximateResolution,
                                             CATCrvParam             &  oEquivalentParam ) const;




  //-------------------------------------------------------------------------
  // Gets a pointer toward each Curve of the mapping
  //-------------------------------------------------------------------------
  const CATCurve* GetRefCurve()const;
  virtual const CATCurve* GetCurve()const;
  virtual const CATCurve* OtherCurve(const CATCurve* iCurve)const;
	//-------------------------------------------------------------------------
  // Returns a new MapX, composition of this MapX and iMapX.
  // The new RefCurve is the curve of THIS MapX which is not in iMapX.
  // The new Curve is the curve of iMapX which is not in THIS.
  // THIS and iMapX can be destroyed afterwards, if necessary.
  //-------------------------------------------------------------------------
  virtual CATMapX* CreateComposition(const CATMapX* iMapX)const;

  //-------------------------------------------------------------------------
  // Says wether or not iCurve is in the Mapping.
  // Returned value is 1 if iCurve is the RefCurve.
  // Returned value is 2 if iCurve is the Curve.
  //-------------------------------------------------------------------------
  virtual short IsContaining(const CATCurve* iCurve)const;

  //-------------------------------------------------------------------------
  // Access functions.
  //-------------------------------------------------------------------------
  double GetRefMappingStart() const;
  double GetRefMappingEnd() const;
  double GetCrvMappingStart() const;
  double GetCrvMappingEnd() const;
  double GetRefStart() const;
  double GetRefEnd() const;
  double GetCrvStart() const;
  double GetCrvEnd() const;

  protected:

  virtual double GetEquivalentDouble(const CATCurve* iCurrentCurve,  const double    iCurrentParam,
                                     short           iReconvergence=1)const;

  virtual double GetApproximateEquivalentDouble(const CATCurve* iCurrentCurve, const double    iCurrentParam,
                                              const CATPositiveLength &  iApproximateResolution ) const;

  // Fills _DegenerateDiags
  virtual void UpdateDegenerateDiags();

  virtual size_t  GetDynamicMemoryBytes() const;
  virtual size_t  GetStaticMemoryBytes() const;
  //-------------------------------------------------------------------------
  // Data
  //-------------------------------------------------------------------------
  protected:

     CATMapX * _MapX ;
     double  _RefMappingStart, _RefMappingEnd; // mapping limits
     double  _CrvMappingStart, _CrvMappingEnd; 
     double  _RefStart, _RefEnd, _CrvStart, _CrvEnd; // curve limits

     // _DegenerateDiags conventions:
     //    i = 0: RefCurve
     //    i = 1: Curve
     //
     // _DegenerateDiags[2*i]   = 1 if mapping limits are degenerated, 0 otherwise
     // _DegenerateDiags[2*i+1] = 1 if curve limits are degenerated, 0 otherwise
     int _DegenerateDiags[4];


};

#endif
