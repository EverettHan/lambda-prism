// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// Class designed to handle mapping between two Curves of an EdgeCurve
// The type of Mapping is linear.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Mar. 99   Creation                                     E. Guerin
// Mar. 04 Stream/UnStreamCompact(...),
//         Stream/UnStreamCompactLossAllowed(...)                         HCN
// Jul. 09 Suppression du StreamCompact                                   VUC
//=============================================================================
#ifndef CATLinearMapX_H
#define CATLinearMapX_H


#include "CATIdentityMapX.h"

class ExportedByYP00IMPL CATLinearMapX : public CATIdentityMapX  
{
public:
   /** @nodoc */
  CATCGMNewClassArrayDeclare;
  //-------------------------------------------------------------------------
  // Constructors/Destructors
  //-------------------------------------------------------------------------
  //-------------------------------------------------------------------------
  // Creates a new CATLinearMapX with the law :
  // ParamOnRefCurve = iScale * ParamOnCurve + iShift
  //-------------------------------------------------------------------------
	CATLinearMapX(const CATCurve* iRefCurve, const CATCrvLimits & iRefLimits,
                const CATCurve* iCurve,    const CATCrvLimits & iLimits,
                const double iMaxGap,
                const double iScale,
                const double iShift);
	CATLinearMapX(const CATCurve* iRefCurve, 
                const double iRefLow, const double iRefHigh,
                const CATCurve* iCurve,    
                const double iLow, const double iHigh,
                const double iMaxGap,
                const double iScale,
                const double iShift);
  //-------------------------------------------------------------------------
  // Creates a new CATLinearMapX such as iRefParam1 is matched with iParam1
  // and iRefParam2 is matched with iParam2
  //-------------------------------------------------------------------------
	CATLinearMapX(const CATCurve* iRefCurve, const CATCrvLimits & iRefLimits,
                const CATCurve* iCurve,    const CATCrvLimits & iLimits,
                const double iMaxGap,
                const double iRefParam1,const double iParam1,
                const double iRefParam2,const double iParam2);
  //-------------------------------------------------------------------------
  // Creates a new CATLinearMapX such as the limits given for the curves
  // are matched, according to the given Orientation.
  //-------------------------------------------------------------------------
	CATLinearMapX(const CATCurve* iRefCurve, const CATCrvLimits & iRefLimits,
                const CATCurve* iCurve,    const CATCrvLimits & iLimits,
                const double iMaxGap,const short iOrientation=1);
  CATLinearMapX(const CATLinearMapX* iMapX);

  //-------------------------------------------------------------------------
  // Sets the CATLinearMapX such as iRefParam1 is matched with iParam1
  // and iRefParam2 is matched with iParam2
  //-------------------------------------------------------------------------
  virtual void Set(const double iRefParam1,const double iParam1,
                   const double iRefParam2,const double iParam2);
  //-------------------------------------------------------------------------
  // Sets the CATLinearMapX with the law :
  // ParamOnRefCurve = iScale * ParamOnCurve + iShift
  //-------------------------------------------------------------------------
  virtual void Set(const double iScale, const double iShift);

  //-------------------------------------------------------------------------
  // Gets the parameters of the CATLinearMapX
  //-------------------------------------------------------------------------
  double GetScale(const short iInvert=0)const;
  double GetShift(const short iInvert=0)const;

  virtual ~CATLinearMapX();


  //-------------------------------------------------------------------------
  // Methods of CATMapX
  //-------------------------------------------------------------------------
	virtual CATMapX* SetCurve(const CATCurve* iOldCurve, const CATCurve* iNewCurve,
                            const CATMathTransformation1D* iTransfo=0);
  virtual short GetOrientation()const;
  virtual CATMapX::Type GetType()const;

  virtual void Stream(CATCGMStream& Str);
  virtual void UnStream(CATCGMStream& Str);

  virtual CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

  virtual CATMapX* Duplicate()const;
  virtual void Invert();
  virtual void Dump(CATCGMOutput& os)const;
  virtual CATMapX* Simplify()const;
  virtual void AdjustLimits();
  virtual CATMathFunctionX* CreateFunctionX(short iRefCurveFirst=1, CATBoolean iAdjustedC2=0, const double * iDomain=0) const;

  virtual CATLONG32 Unextrapolate(const CATCrvLimits & NewLimits, double tol2, CATLONG32 Mode);

protected:
  virtual void Compose(const CATMapX* iMapX,const CATCurve* iCurve);
  virtual double GetEquivalentParamOnRefCurve(const double iParamOnCurve, short iReconvergence=1)const;
  virtual double GetEquivalentParamOnCurve(const double iParamOnRefCurve, short iReconvergence=1)const;

  virtual double GetApproximateEquivalentParamOnRefCurve(const double iParamOnCurve, const CATPositiveLength &  iApproximateResolution ) const;
  virtual double GetApproximateEquivalentParamOnCurve(const double iParamOnRefCurve, const CATPositiveLength &  iApproximateResolution ) const;

  //=============================================================
  //
  //  DATA
  //
  //=============================================================

protected :

  double _scale;
  double _shift;

  
  virtual size_t  GetStaticMemoryBytes() const;   
};

#endif
