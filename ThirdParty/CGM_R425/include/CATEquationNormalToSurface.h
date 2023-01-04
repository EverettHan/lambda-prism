// 
//=============================================================================
// Usage notes:
// CATMathFunctionXY computing the normal of a surface
//
//=============================================================================
//August 2007 EYL 
//=============================================================================


#ifndef CATEquationNormalToSurface_H
#define CATEquationNormalToSurface_H

#include "CATMathFunctionXY.h"
#include "CATMathBasisFunctionXY.h"
#include "CATTolerance.h"
#include "Y30C3XGG.h"
#include "CATMathDirection.h"
#include "CATCGMNewArray.h"


class CATMathPoint;
class CATSoftwareConfiguration;
class CATMathDirection ;
class CATMathNormal;

//-----------------------------------------------------------------------------
//DG class CATEquationDistancePtSur : public CATMathFunctionXY
class  ExportedByY30C3XGG CATEquationNormalToSurface: public CATMathFunctionXY
{
// public methods
 public:
  //-----------------------------------------------------------------
  // Object management
  //-----------------------------------------------------------------
  
   CATEquationNormalToSurface(CATSoftwareConfiguration * iConfig,
     const CATMathNormal *Normal,
     CATMathDirection &RefDir);
   CATCGMNewClassArrayDeclare;      // Pool allocation

  ~CATEquationNormalToSurface();
  CATMathFunctionXY * Duplicate() const;
 
  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------

  CATMathClassId IsA() const;
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
  //CATBoolean IsOption(const CATMathOption iOption) const;
   
  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------   
  double Eval(const double & u, const double & v) const;
  
  /*CATMathDiagnostic Minimize(const CATMathInterval2D & D,
                                              CATMathSetOfPointsND & roots,
                                              const CATMathAttrList * attributes = 0) const;
*/

private:
  CATMathDirection _RefDir;
  CATSoftwareConfiguration * _Config;    
  const CATMathNormal *_Normal;

};

#endif

