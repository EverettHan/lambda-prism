#ifndef CATConnectSurfaceToolData_h
#define CATConnectSurfaceToolData_h

// COPYRIGHT DASSAULT SYSTEMES 2002
// =====================================================
// CATConnectSurfaceToolData:
// Interface class used to retrieve the creation data of
// a connect surface
// =====================================================
// June 2002  S.Dauby Creation                           
// 2012/01/10 XMH     Add HoldCurve Fillet type
// =====================================================


#include "YP00IMPL.h"                    
#include "CATCGMVirtual.h"

class CATCurve;
class CATLaw;

class ExportedByYP00IMPL CATConnectSurfaceToolData : public CATCGMVirtual
{
public:
  CATConnectSurfaceToolData();
  virtual ~CATConnectSurfaceToolData();

  enum ToolType {
    VariableFillet, 
    ConstantFillet, 
    TriTangentFillet, 
    BiTangentCircleFillet, 
    SweepCircle, 
    HoldCurveCircleFillet,
    VariableFilletG1,
    ConstantChordalFillet,
    VariableChordalFillet,
    HoldCurveFillet
  };

  virtual double GetRadius() const =0;
  virtual CATCurve * GetSpine() const =0;
  virtual CATLaw * GetRadiusLaw() const =0;
  virtual CATLaw * GetMappingLaw() const =0;
  virtual CATCurve * GetCircleSpine() const =0;
  virtual double GetChord() const =0;
  virtual CATLaw * GetChordLaw() const =0;
  virtual ToolType GetToolType() const =0;
  virtual size_t GetStaticMemoryBytes() const;   
};

#endif
