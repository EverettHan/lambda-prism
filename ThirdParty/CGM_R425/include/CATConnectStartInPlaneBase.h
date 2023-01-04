//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2016
//==========================================================================
//
// 
//
//========================================================================== 
// June 2016                                                   SMT1
//========================================================================== 


#ifndef CATConnectStartInPlaneBase_H
#define CATConnectStartInPlaneBase_H

#include "Connect.h"
#include "CATGeoOperator.h"

class CATConnectTool;

class ExportedByConnect CATConnectStartInPlaneBase : public CATGeoOperator
{    
protected:

  CATConnectStartInPlaneBase(CATGeoFactory * iFactory);

public:
  ~CATConnectStartInPlaneBase();

  /**
  * GetDiagnostic : returns 1 if a solution has been found, 0 otherwise.
  */

  virtual CATLONG32 GetDiagnostic() = 0;

  // Following get methods must be call if GetDiagnostic returns 1

  /**
  *  GetCurve
  *  Returns the 3D solution curve: a line (chamfer) or a circle (fillet).
  *  Caller must manage deletion.
  */
  virtual CATCurve * GetCurve() = 0;

  /**
  *  GetCurveCenter
  *  Returns the 3D center of solution curve (eg. the center of the circle).
  *  The method returns 1 if this center exists, 0 otherwise (case of a line or infinite radius circle).
  */
  virtual int GetCurveCenter(CATMathPoint & oCurveCenter);

  /**
  *  GetFixedPoint
  *  Returns the input 3D fixed point and the maximum distance from 3D solution points on supports.
  */
  virtual void GetFixedPoint(CATMathPoint & oFixedPoint, double & oMaxDist);

  /**
  *  GetPlane
  *  Returns the math plane solution centered on bitangent circle center,
  *  with axis U = FirstTrace ( = Trace1 - CircleCenter), and axis V orthognal.
  *  Caller must manage deletion.
  */
  virtual CATMathPlane * GetMathPlane();

  /**
  *  GetPoints
  *  Returns the 3D points / UV-points solution.
  */
  virtual CATBoolean GetPoints(CATMathPoint & oPtSupp1, CATMathPoint & oPtSupp2);
  virtual CATBoolean GetPoints(CATSurParam  & oPtSupp1, CATSurParam  & oPtSupp2);

  virtual CATBoolean GetPoints(CATMathPoint & oPtSupp1, CATMathPoint & oPtSupp2, CATMathPoint & oPtSupp3);
  virtual CATBoolean GetPoints(CATSurParam  & oPtSupp1, CATSurParam  & oPtSupp2, CATSurParam  & oPtSupp3);

  virtual CATBoolean GetPoints(CATMathPoint &ioPointOnEdge,
    CATMathPoint &ioPointOnSupport11,
    CATMathPoint &ioPointOnSupport2,
    CATMathPoint &ioCenterPoint,
    double &oMaxDistFromEdge); 

  virtual CATBoolean GetPoints(CATSurParam &oPointOnSupport1, CATSurface *& oSupport1,
    CATSurParam &oPointOnSupport2, CATSurface *& oSupport2);

  virtual const CATConnectTool *GetTool() = 0;

  /**
  *  GetRadius
  *  Returns the radius solution (usefull for variable fillet).
  */
  virtual double GetRadius() = 0;

  virtual void SetLimits(CATSurLimits * iLimitsOnSupport1, CATSurLimits * iLimitsOnSupport2);
};
#endif
