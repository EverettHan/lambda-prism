#ifndef CATIPGMDynMassProperties2D_h_
#define CATIPGMDynMassProperties2D_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATMathDef.h"
#include "CATCollec.h"

class CATFace;
class CATMathPoint;
class CATTopData;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynMassProperties2D;

class ExportedByCATGMOperatorsInterfaces CATIPGMDynMassProperties2D: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDynMassProperties2D();

  virtual CATPositiveLength GetArea() = 0;

  virtual void GetCenterOfGravity(CATMathPoint &oResult) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDynMassProperties2D(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynMassProperties2D *CATPGMDynCreateMassProperties2D(const CATFace *);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynMassProperties2D *CATPGMDynCreateMassProperties2D(const CATLISTP(CATFace) &);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynMassProperties2D *CATPGMDynCreateMassProperties2D(
  CATTopData *iTopData,
  const CATLISTP(CATFace) &iFaces);

#endif /* CATIPGMDynMassProperties2D_h_ */
