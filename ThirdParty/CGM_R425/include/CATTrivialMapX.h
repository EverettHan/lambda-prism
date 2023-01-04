// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// Class designed to handle mapping between parametrization of two Curves of
// an EdgeCurve.
// The mapping is ParamOnRefCurve=ParamOnCurve
// and the limits of the EdgeCurve on each curve are the same.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Mar. 99   Creation                                     E. Guerin
// Mar. 04 Stream/UnStreamCompact(...),
//         Stream/UnStreamCompactLossAllowed(...)                         HCN
// May. 04 GetStreamSortingKey(...),
//         HasCommonStreamData(...),
//         CopyCommonStreamData(...)                                      HCN
// 05/06/08 NLD Ajout ForceMaxGap()
// Jul. 09 Suppression du StreamCompact                                   VUC
// Aug. 11 Added the functions GetRefCurveLow() and GetRefCurveHigh()
//         (for comparing geometries).                                    R1Y
//=============================================================================
#ifndef CATTrivialMapX_H
#define CATTrivialMapX_H

#include "CATMapX.h"

//-----------------------------------------------------------------------------
//
class ExportedByYP00IMPL CATTrivialMapX : public CATMapX
{
public:
   /** @nodoc */
  CATCGMNewClassArrayDeclare;

  //-------------------------------------------------------------------------
  // Constructors
  //-------------------------------------------------------------------------
  CATTrivialMapX(const CATCurve* iRefCurve, const CATCrvLimits& iRefLimits,
                 const CATCurve* iCurve,
                 const double    iMaxGap);
  CATTrivialMapX(const CATCurve* iRefCurve, 
                 const double iRefLow, const double iRefHigh,
                 const CATCurve* iCurve,
                 const double    iMaxGap);
  CATTrivialMapX(const CATTrivialMapX* iMapX);

  //-------------------------------------------------------------------------
  // virtual Destructor
  //-------------------------------------------------------------------------
  virtual ~CATTrivialMapX();
  
  //-------------------------------------------------------------------------
  // CATMapX methods
  //-------------------------------------------------------------------------
  virtual void SetLimits(const CATCurve* iCurve,
                         const CATCrvLimits &  iLimits);
  virtual void GetLimits(const CATCurve* iCurve,
                         CATCrvLimits &  oLimits)const;
  virtual void GetLimits(const CATCurve* iCurve,
                         CATCrvParam &   oLow,
                         CATCrvParam &   oHigh)const;
  virtual double GetMaxGap()const;
  virtual void ForceMaxGap(double iMaxGap);
  virtual double ComputeMaxGap();

  virtual CATMapX::Type GetType()const;
  virtual void Stream( CATCGMStream& Str ) ;
  virtual void UnStream( CATCGMStream& Str ) ;

  virtual int  GetStreamSortingKey(CATCGMStream& Str);
  virtual int  HasCommonStreamData(const CATMapX* ipMapXToCompare, CATCGMStream& Str);
  virtual void CopyCommonStreamData(const CATMapX* ipMapXToCompare, int iSimilarityLevel, CATCGMStream& Str);

  virtual CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

  double GetRefCurveLow()  const;
  double GetRefCurveHigh() const;

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


  virtual const CATCurve* GetCurve()const;
  virtual CATMapX* SetCurve(const CATCurve* iOldCurve, const CATCurve* iNewCurve,
                            const CATMathTransformation1D* iTransfo=0);
  virtual void SetCurves(const CATCurve* iRefCurve,const CATCurve* iCurve);
  virtual void Invert();
  virtual CATMapX* Duplicate()const;
  virtual CATMapX* Clone(CATCloneManager& iCloneManager)const;  
  virtual short IsContaining(const CATCurve* iCurve)const;
  virtual void Dump(CATCGMOutput& os)const;

  virtual CATLONG32 Unextrapolate(const CATCrvLimits & NewLimits, double tol2, CATLONG32 Mode);

  //-------------------------------------------------------------------------
  // Protected methods.
  //-------------------------------------------------------------------------
protected:

  virtual void Compose(const CATMapX* iMapX, const CATCurve* iCurve);

  virtual double GetEquivalentDouble(const CATCurve* iCurrentCurve,
                                     const double    iCurrentParam,
                                     short           iReconvergence=1)const;

  virtual double GetApproximateEquivalentDouble(const CATCurve* iCurrentCurve, const double    iCurrentParam,
                                              const CATPositiveLength &  iApproximateResolution ) const;


	virtual void UpdateLimits();
  //-------------------------------------------------------------------------
  // Data
  //-------------------------------------------------------------------------
  const CATCurve*     _Curve;
  double              _MaxGap;
  double              _RefCurveLow,_RefCurveHigh;

  // INTERNAL ONLY
  virtual size_t  GetDynamicMemoryBytes() const;   
  virtual size_t  GetStaticMemoryBytes() const;   
};

#endif
