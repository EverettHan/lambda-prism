#ifndef CATIPGMLiveRunnerOperator_h_
#define CATIPGMLiveRunnerOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

#include "CATGMModelInterfaces.h"
#include "CATIPGMVirtual.h"
#include "CATGMLiveShapeInterruptLevel.h"
#include "CATIACGMLevel.h"
#include "CATBoolean.h"
#ifdef CATIAR213
#include "CATSysBoolean.h"
#endif
#include "IUnknown.h" // For HRESULT
#include "CATCollec.h"

class CATLISTP(CATCell);
class CATCDMBaseServices;
class CATPGMDRepBehavior;
class CATMathTransformation;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMLiveRunnerOperator;

/**
 * Class for operator runner.
   */

#ifndef CAT_GENERATE_TIE

class ExportedByCATGMModelInterfaces CATIPGMLiveRunnerOperator: public CATIPGMVirtual
{
public:
  /**  
   * Constructor
   */
  CATIPGMLiveRunnerOperator();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMLiveRunnerOperator(); // -> delete can't be called

public:

#else

class ExportedByCATGMModelInterfaces CATIPGMLiveRunnerOperator: public IUnknown
{
public:

#endif

  virtual CATGMLiveShapeInterruptLevel GetInterruptLevel() = 0;

  virtual void SetCDMBaseServices(CATCDMBaseServices *iCDMBaseServices) = 0;

  virtual void SetDRepBehavior(CATPGMDRepBehavior *iDRepBehavior) = 0;

  virtual void SetPreviewMode(const CATBoolean &iPreview=TRUE) = 0;

  virtual HRESULT AppendTransfo(const CATLISTP(CATCell) &iCellsList, const CATMathTransformation &iMathTransfo) = 0;

  /**
   * @nodoc
   * Returns the meta class associated with the interface.<br>
   * Note that it's handled by the implementation in order not to expose more internal data.
   */
  virtual const CATCGMItfMetaClass &GetItfMetaClass() const = 0;

protected:
  /**
   * @nodoc
   * Returns the internal data.
   */
  virtual CATCGMItfInternalData &GetInternalData() = 0;
};

#endif /* CATIPGMLiveRunnerOperator_h_ */
