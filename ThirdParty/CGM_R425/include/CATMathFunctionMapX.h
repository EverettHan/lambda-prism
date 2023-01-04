// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// Class designed to handle mapping between two Curves of an EdgeCurve
// The Mapping is defined with two CATMathFunctionMapX.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Mar. 99   Creation                                     E. Guerin
//=============================================================================
#ifndef CATMathFunctionMapX_H
#define CATMathFunctionMapX_H


#include "CATIdentityMapX.h"

class CATMathFunctionX;
class CATMathFunctionXY;

class ExportedByYP00IMPL CATMathFunctionMapX : public CATIdentityMapX  
{
public:
   /** @nodoc */
  CATCGMNewClassArrayDeclare;
  //-------------------------------------------------------------------------
  // Constructors/Destructors
  //-------------------------------------------------------------------------
  //-------------------------------------------------------------------------
  // Creation of a CATMathFunctionMapX :
  //  - iFunction    : paramOnCurve------>paramOnRefCurve
  //  - iRefFunction : paramOnRefCurve--->paramOnCurve
  // The limits of definition of the Functions must also be supplied.
  // If iDuplic==1, the Functions are DeepDuplicated()
  // If iDuplic==0, they are not, but they will still be destroyed when
  // the CATMathFunctionMapX is released.
  //-------------------------------------------------------------------------
  CATMathFunctionMapX(const CATCurve* iRefCurve, const CATCrvLimits & iRefLimits,
                      const CATCurve* iCurve,    const CATCrvLimits & iLimits,
                      const double iMaxGap,
                      const CATMathFunctionX* iRefFuction,
                      const double iRefLow,const double iRefHigh,
                      const CATMathFunctionX* iFunction,
                      const double iLow,const double iHigh,
                      const short iDuplic=0);
  CATMathFunctionMapX(const CATCurve* iRefCurve,
                      const double iRefCurveLow, const double iRefCurveHigh,
                      const CATCurve* iCurve,
                      const double iCurveLow, const double iCurveHigh,
                      const double iMaxGap,
                      const CATMathFunctionX* iRefFuction,
                      const double iRefLow,const double iRefHigh,
                      const CATMathFunctionX* iFunction,
                      const double iLow,const double iHigh,
                      const short iDuplic=0);
  CATMathFunctionMapX(const CATMathFunctionMapX* iMapX);
	virtual ~CATMathFunctionMapX();

  //-------------------------------------------------------------------------
  // Gets the function which parameters are taken on iCurve. The caller
  // must not delete the returned function.
  //-------------------------------------------------------------------------
  const CATMathFunctionX* GetFunction(const CATCurve* iCurve)const;

  //-------------------------------------------------------------------------
  // CATMapX methods
  //-------------------------------------------------------------------------
  virtual short GetOrientation()const;
  virtual CATMapX::Type GetType()const;

  virtual void Stream(CATCGMStream& Str);
  virtual void UnStream(CATCGMStream& Str);
  virtual CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

  virtual CATMapX* Duplicate()const;
  virtual void Invert();
  virtual CATMapX* SetCurve(const CATCurve * iOldCurve, const CATCurve * iNewCurve,
                            const CATMathTransformation1D* iTransfo);
  virtual void GetMappingLimits(const CATCurve*  iCurve,
                                double &         oLow,
                                double &         oHigh)const;

  virtual CATMapX* Simplify()const;
  virtual void AdjustLimits();
  virtual void Dump(CATCGMOutput & os)const;
  virtual CATMathFunctionX* CreateFunctionX(short iRefCurveFirst=1, CATBoolean iAdjustedC2=0, const double * iDomain=0)const;

  virtual CATLONG32 Unextrapolate(const CATCrvLimits & NewLimits, double tol2, CATLONG32 Mode = 0);

protected:
  virtual void Compose(const CATMapX* iMapX,const CATCurve* iCurve);
  virtual double GetEquivalentParamOnRefCurve(const double iParamOnCurve, short iReconvergence)const;
  virtual double GetEquivalentParamOnCurve(const double iParamOnRefCurve, short iReconvergence)const;

  virtual double GetApproximateEquivalentParamOnRefCurve(const double iParamOnCurve, const CATPositiveLength &  iApproximateResolution ) const;
  virtual double GetApproximateEquivalentParamOnCurve(const double iParamOnRefCurve, const CATPositiveLength &  iApproximateResolution ) const;



  //=============================================
  //
  // DATA 
  // 
  //=============================================

protected:

  CATMathFunctionX* _RefFunction;  // RefCurve ---> Curve
  double            _RefLow,_RefHigh;
  CATMathFunctionX* _Function;     // Curve    ---> RefCurve
  double            _Low,_High;

  // INTERNAL ONLY 
  virtual size_t  GetDynamicMemoryBytes() const;   
  virtual size_t  GetStaticMemoryBytes() const;   
};

#endif
