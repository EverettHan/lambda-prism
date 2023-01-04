#ifndef CATIPGMExtrapolTool_h_
#define CATIPGMExtrapolTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATIPGMDistanceTool;
class CATGeoFactory;
class CATLaw;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMExtrapolTool;

//
//--------------------------------------------------------------------------
//
/**
 * Class defining the extrapol computation.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMExtrapolTool: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMExtrapolTool();

  /** @nodoc */
  virtual CATBody *ComputeExtrapolation(
    CATBody *Wire,
    CATCGMJournalList *JournalOfReturn,
    CATLONG32 iForceCode = 0) = 0;

  /**
     * Retrieves the skin body on which the extrapolation is computed.
     * @param oSupport
     * The pointer to the skin body. 
     */
  virtual void GetSupport(CATBody *&oSupport) = 0;

  /**
   * @return [out, IUnknown#Release]
   */
  virtual CATIPGMExtrapolTool *Duplicate() = 0;

  virtual void SetSupport(CATBody *oSupport) = 0;

  /* inactive implementation */
  virtual int Run() = 0;

  virtual CATBody *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMExtrapolTool(); // -> delete can't be called
};

#endif /* CATIPGMExtrapolTool_h_ */
