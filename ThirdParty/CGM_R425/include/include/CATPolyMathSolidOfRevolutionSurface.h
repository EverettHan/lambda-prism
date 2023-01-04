// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathSolidOfRevolutionSurface.h
// Header definition of CATPolyMathSolidOfRevolutionSurface
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// nov 2009  xcz
//===================================================================

#ifndef CATPolyMathSolidOfRevolutionSurface_H
#define CATPolyMathSolidOfRevolutionSurface_H

#include "CATPolyMathQuadSurface.h"
#include "CATPolyMathSurface.h"
#include "CATErrorDef.h"

#include "CATMathPoint.h"
#include "CATMathBox2D.h"
#include "CATMathVector.h"
#include "CATMathLine.h"
#include "CATPolyMathCurve.h"




//       Points/Normals       
//       --------------       
//
//           P1/N1     Side 4     P4/N4    
//             __v_______________             
//          u /                 /
//           /                 /
//          /                 /
//  Side 1 /                 / Side 3
//        /                 /  
//       /                 /   
//      /                 /    
//     /_________________/     
//  P2/N2               P3/N3 
//         Side 2      
//

/**
 * Describe your class here.
 */
class ExportedByPolyMathSurfaces CATPolyMathSolidOfRevolutionSurface : public CATPolyMathQuadSurface
{

public:

  CATPolyMathSolidOfRevolutionSurface (CATMathLine &iRevolAxis,CATPolyMathCurve *iProfileCurve,double iSweepAngle);
  virtual ~CATPolyMathSolidOfRevolutionSurface ();

private:
  //SPECIFIC
  CATMathLine _RevolAxis;
  CATPolyMathCurve *_ProfileCurve;
  double _SweepAngle;


public:
  //INHERITED
  CATPolyMathQuadSurface * Clone () const;  
  Type GetType () const;
  const CATPolyMathSolidOfRevolutionSurface* CastAsSolidOfRevolution()const;
  CATPolyMathSolidOfRevolutionSurface* CastAsSolidOfRevolution();

  void GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const;

  void GetNormal (const unsigned int vertex, CATMathVector& oNormal) const;

  void Evaluate (const double u, const double v, CATMathPoint& oPoint) const;
  void Evaluate (const double u, const double v, CATMathVector& oNormal) const ;

  void Evaluate (const double u, const double v, CATMathPoint& oPoint,
                         CATMathVector& oNormal) const;

  void EvaluatePartialDerivatives (const double u, const double v, 
                                           double odPdu[], double odPdv[]) const;

  void EvaluateAlongSide (const int iSide, const double t, 
                                  CATMathPoint& oPoint) const;

  void EvaluateAlongSide (const int iSide, const double t, 
                                  CATMathPoint& oPoint, CATMathVector& oNormal) const;

  void EvaluateDerivativeAlongSide (const int iSide, const double t, 
                                            double odPdt[]) const;
  
  void GetMaxSecondDerivatives(double& oMaxSecondDerivativeAlongU,double& oMaxSecondDerivativeAlongV)const;
  void GetSecondDerivatives(const double u, const double v, double oDuu[],double oDvv[],double oDuv[])const;

  HRESULT Accept (CATPolyMathSurfaceConstVisitor &iV) const ;
  HRESULT Accept (CATPolyMathSurfaceVisitor &iV) ;

  //SPECIFIC (TODO: INHERITED)
  HRESULT EvaluateGridLimits(double iSag,double &oUmin,double &oUmax,double &oVmin,double &oVmax,int &oNbPtsU,int &oNbPtsV,double &oStepU ,double &oStepV);

};



#endif
