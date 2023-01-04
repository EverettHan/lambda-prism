// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// Class designed to handle mapping between parametrization of two Curves of
// an EdgeCurve.
// The mapping is ParamOnRefCurve=ParamOnCurve
// and the limits of the EdgeCurve on each curve are different.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Mar. 99   Creation                                     E. Guerin
// Mar. 04 Stream/UnStreamCompact(...),
//         Stream/UnStreamCompactLossAllowed(...)                         HCN
// Jun. 04 GetStreamSortingKey(...),
//         HasCommonStreamData(...),
//         CopyCommonStreamData(...)                                      HCN
// Jul. 09 Suppression du StreamCompact                                   VUC
// Aug. 11 Added the functions GetCurveLow() and GetCurveHigh() (for
//         comparing geometries).                                         R1Y
//=============================================================================
#ifndef CATIdentityMapX_H
#define CATIdentityMapX_H

#include "YP00IMPL.h"                    
#include "CATTrivialMapX.h"

//-----------------------------------------------------------------------------
//
class ExportedByYP00IMPL CATIdentityMapX : public CATTrivialMapX
{
public:
   /** @nodoc */
  CATCGMNewClassArrayDeclare;

  //-------------------------------------------------------------------------
  // Constructors
  //-------------------------------------------------------------------------
  CATIdentityMapX(const CATCurve* iRefCurve,const CATCrvLimits & iRefLimits,
                  const CATCurve* iCurve,   const CATCrvLimits & iLimits,
                  const double iMaxGap);
  CATIdentityMapX(const CATCurve* iRefCurve,
                  const double iRefLow, const double iRefHigh,
                  const CATCurve* iCurve,
                  const double iLow, const double iHigh,
                  const double iMaxGap);
  CATIdentityMapX(const CATIdentityMapX* iMapX);

  //-------------------------------------------------------------------------
  // virtual Destructor
  //-------------------------------------------------------------------------
  virtual ~CATIdentityMapX();
  
  //-------------------------------------------------------------------------
  // CATMapX methods
  //-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
  // Creates CATMathFunctionX* which transforms a parameter expressed on
  // one curve to the parameter expressed on the other.
  // * If iRefCurveFirst==1 (default), the function maps from RefCurve to Curve.
  // Otherwise, the function maps from Curve to RefCurve
	// * If iAdjustedC2=1, the returned function is adjusted to have a one-to-one mapping
	// and returns a C2 function.
  // The returned function must be deleted by the caller.
	// *iDomain contains the limits from RefCurve and Curve if iRefCurvefirst=1
	// on the contrary if iRefCurvefirst =!1
  //-------------------------------------------------------------------------
  virtual CATMathFunctionX* CreateFunctionX(short iRefCurveFirst=1, CATBoolean iAdjustedC2=0, const double * iDomain=0)const;

  virtual void SetLimits(const CATCurve* iCurve,
                         const CATCrvLimits &  iLimits);
  virtual void GetLimits(const CATCurve* iCurve,
                         CATCrvLimits &  oLimits)const;
  virtual void GetLimits(const CATCurve* iCurve,
                         CATCrvParam &   oLow,
                         CATCrvParam &   oHigh)const;
  virtual CATMapX::Type GetType()const;

  virtual void Stream( CATCGMStream& Str ) ;
  virtual void UnStream( CATCGMStream& Str ) ;

  virtual int  GetStreamSortingKey(CATCGMStream& Str);
  virtual int  HasCommonStreamData(const CATMapX* ipMapXToCompare, CATCGMStream& Str);
  virtual void CopyCommonStreamData(const CATMapX* ipMapXToCompare, int iSimilarityLevel, CATCGMStream& Str);

  virtual CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

  virtual CATMapX* SetCurve(const CATCurve* iOldCurve, const CATCurve* iNewCurve,
                            const CATMathTransformation1D* iTransfo=0);
  virtual double ComputeMaxGap();
  virtual void Invert();
  virtual CATMapX* Duplicate()const;
  virtual CATMapX* Simplify()const;
  virtual void Dump(CATCGMOutput& os)const;
  virtual void AdjustLimits();

  double GetCurveLow() const;
  double GetCurveHigh() const;

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


  virtual CATLONG32 Unextrapolate(const CATCrvLimits & NewLimits, double tol2, CATLONG32 Mode);
  
  //-------------------------------------------------------------------------
  // Protected methods.
  //-------------------------------------------------------------------------
protected:
  
  virtual void Compose(const CATMapX* iMapX,const CATCurve* iCurve);

  virtual double GetEquivalentDouble(const CATCurve* iCurrentCurve, const double    iCurrentParam,
                                     short           iReconvergence=1)const;

  virtual double GetApproximateEquivalentDouble(const CATCurve* iCurrentCurve, const double    iCurrentParam,
                                              const CATPositiveLength &  iApproximateResolution ) const;


  virtual double GetEquivalentParamOnRefCurve(const double iParamOnCurve,    short iReconvergence=1)const;
  virtual double GetEquivalentParamOnCurve(const double iParamOnRefCurve,    short iReconvergence=1)const;

  virtual double GetApproximateEquivalentParamOnRefCurve(const double iParamOnCurve, const CATPositiveLength &  iApproximateResolution ) const;
  virtual double GetApproximateEquivalentParamOnCurve(const double iParamOnRefCurve, const CATPositiveLength &  iApproximateResolution ) const;

  //-------------------------------------------------------------------------
  // Data
  //-------------------------------------------------------------------------
  double              _CurveLow,_CurveHigh;
  
  virtual size_t  GetStaticMemoryBytes() const;   
};

#endif
