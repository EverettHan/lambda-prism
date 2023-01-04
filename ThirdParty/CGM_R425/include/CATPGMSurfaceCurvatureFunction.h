#ifndef CATPGMSurfaceCurvatureFunction_h_
#define CATPGMSurfaceCurvatureFunction_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATMathBasisFunctionXY.h"
#include "CATTolerance.h"

typedef enum
{
  GaussianCurvature,
  MeanCurvature,
  MaxPrincipalCurvature,
  MinPrincipalCurvature    
} CATCurvatureType;

//-----------------------------------------------------------------------------
//DG
//class CATPGMSurfaceCurvatureFunction : public CATMathBasisFunctionXY
class ExportedByCATGMModelInterfaces CATPGMSurfaceCurvatureFunction: public CATMathBasisFunctionXY
{
public:
  /**
   * Constructor
   */
  CATPGMSurfaceCurvatureFunction(const CATTolerance & iTolObject, CATLONG32 p1, CATLONG32 p2);

  /**
   * Destructor
   */
  virtual ~CATPGMSurfaceCurvatureFunction();

  virtual CATMathFunctionXY *Duplicate() const = 0;

  virtual void SetType(const CATCurvatureType NewType) = 0;

  virtual CATCurvatureType GetType() = 0;

  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
  virtual CATMathClassId IsA() const = 0;

  virtual CATBoolean IsAKindOf(const CATMathClassId iClassId) const = 0;

  virtual CATBoolean IsOption(const CATMathOption iOption) const = 0;

  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------
  virtual double Eval(const double &u, const double &v) const = 0;

};

//DG
// CATMathFunctionXY * CreateSurfaceCurvatureFunction(const CATMathFunctionXY * iFX,
ExportedByCATGMModelInterfaces CATMathFunctionXY *CATPGMCreateSurfaceCurvatureFunction(
  const CATMathFunctionXY *iFX,
  const CATMathFunctionXY *iFY,
  const CATMathFunctionXY *iFZ,
  const CATTolerance &iTolObject = CATGetDefaultTolerance(),
  const CATCurvatureType itype = GaussianCurvature);

#endif /* CATPGMSurfaceCurvatureFunction_h_ */
