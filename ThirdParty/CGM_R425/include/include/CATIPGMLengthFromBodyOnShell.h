#ifndef CATIPGMLengthFromBodyOnShell_h_
#define CATIPGMLengthFromBodyOnShell_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATMathDef.h"
#include "CATSkillValue.h"

class CATBody;
class CATEdge;
class CATGeoFactory;
class CATShell;
class CATSurface;
class CATVertex;
class CATMathPoint;
class CATMathVector;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMLengthFromBodyOnShell;

class ExportedByCATGMModelInterfaces CATIPGMLengthFromBodyOnShell: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMLengthFromBodyOnShell();

  // If Run() was already used, all previous results will be lost
  virtual int Run() = 0;

  virtual CATLONG32 GetProjIni(CATMathPoint &PointIni) = 0;

  virtual CATLONG32 GetCoords(CATMathVector &vect, CATPositiveLength &Lgth) = 0;

  virtual CATBody *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMLengthFromBodyOnShell(); // -> delete can't be called
};

//
// creates the operator
//
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMLengthFromBodyOnShell *CATPGMCreateLengthFromBodyOnShell(
  CATGeoFactory *iFactory,
  CATBody *VertexIni,
  CATBody *VertexTarget,
  CATBody *SupportShell,
  CATSkillValue modev = BASIC);

#endif /* CATIPGMLengthFromBodyOnShell_h_ */
