//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2020
//=============================================================================
//
// CATForeignDebugSurfaceFunc & CATForeignDebugSurfaceData
// 
// Debug classes to create ad hoc surfaces directly from an explicit implementation of the coordinate function.
// NOT TO BE USED IN RELEASE!!!!!
// As an extra level of protection these surfaces can only be created from the CATPlayGroundTest class in GeometricOperators.tst
// Once created, the surfaces can be streamed and used in CGMReplays as usual
//
// To create a new surface addtional cases can be added to  CATForeignDebugSurfaceFunc::Eval & EvalFirstDeriv
// The CATForeignDebugSurfaceData constructor takes 3 CATLONG32 which pick the desired case from these Evals
// The domain is an array of 4 doubles {Umin, Vmin, UMax, VMax}
//=============================================================================
// Usage notes:
//
//=============================================================================
// History:
// 
//    May  2020  SMT1  Creation
//
//=============================================================================


#include "CATForeignSurfaceData.h"
#include "CATMathFunctionXY.h"

class ExportedByYP00IMPL CATForeignDebugSurfaceFunc : public CATMathFunctionXY
{
public:
    CATForeignDebugSurfaceFunc(CATLONG32 iCase);

    ~CATForeignDebugSurfaceFunc();

    CATMathClassId IsA() const;

    void  Stream(CATCGMStream & iStr) const;
    void  UnStream(CATCGMStream & iStr);

    virtual CATMathFunctionXY* Duplicate() const;

    CATBoolean IsOption (const CATMathOption iOption) const;

    virtual double  Eval             (const double                   & iX         ,
                                      const double                   & iY         ) const;
                                     
    virtual double  EvalFirstDerivX  (const double                   & iX         ,
                                      const double                   & iY         ) const;
                                     
    virtual double  EvalFirstDerivY  (const double                   & iX         ,
                                      const double                   & iY         ) const;

private:
    CATLONG32 _Case;
};


class ExportedByYP00IMPL CATForeignDebugSurfaceData : public CATForeignSurfaceData
{
  friend class CATPlaygroundTest;

  CATCGMDeclareAttribute (CATForeignDebugSurfaceData,CATForeignSurfaceData);
protected:
  CATForeignDebugSurfaceData();
  CATForeignDebugSurfaceData(CATLONG32 iEquationCase[3],double * iDomain);
public:
  ~CATForeignDebugSurfaceData();

  virtual void SetLimits(const CATSurLimits & iNewLimits); 
	
  virtual void GetLimits(CATSurLimits & ioLimits) const;

  virtual void GetMaxLimits(CATSurLimits & ioLimits) const;

  virtual CATBoolean Extrapolate(const CATMathVector2D & iRequiredParamExtension,
      CATMathVector2D * ioActualExtension = NULL  );

  virtual void GetInternalMaxLimits(const CATLONG32 iPatchU, const CATLONG32 iPatchV, CATSurLimits & ioLimits) const;

  virtual void CreateLocalEquation(const CATLONG32 iPatchU, const CATLONG32 iPatchV,
			                       const CATMathFunctionXY * & oFx,
			                       const CATMathFunctionXY * & oFy,
			                       const CATMathFunctionXY * & oFz); 
 
  
  // Mandatory methods for CATForeignGeometryData
  CATForeignGeometryData* Clone(CATCloneManager & iCloning) const;
  void Move3D(CATTransfoManager & iTransfo) {};

      // Mandatory methods for CATCGMAttribute
  void  Stream(CATCGMStream & iStr) const;
  void  UnStream(CATCGMStream & iStr);
  CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

  virtual const CATKnotVector * GetKnotVectorU() const {return NULL;}

  virtual const CATKnotVector * GetKnotVectorV() const {return NULL;}
  
   CATBoolean IsConfused(const CATMathTransformation   & iTransfo,
			                  const CATSurface         * iTSurface,
                              CATMathTransformation2D * oTransfo2D = NULL) const {return FALSE;}
  CATBoolean IsPeriodicU() const {return FALSE;}
  CATBoolean IsPeriodicV() const {return FALSE;}

private:

    CATForeignDebugSurfaceFunc** _Equation;
    double * _Domain;
    double * _MaxDomain;
    CATLONG32 _StreamVersion;
};
