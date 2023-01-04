#ifndef CATIPGMExtrapolParallelTool2_h_
#define CATIPGMExtrapolParallelTool2_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMExtrapolParallelTool.h"

class CATBody;
class CATCGMJournalList;
class CATIPGMDistanceTool;
class CATGeoFactory;
class CATLaw;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMExtrapolParallelTool2;

//
//--------------------------------------------------------------------------
//
/**
 * Class defining the parallel computation.
 * <br>This class must be created with the @href CATPGMCreateExtrapolParallelTool 
 * global function and is used by the @href CATIPGMTopParallel operator 
 * to define its parameters.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMExtrapolParallelTool2: public CATIPGMExtrapolParallelTool
{
public:
  /**
   * Constructor
   */
  CATIPGMExtrapolParallelTool2();

  /** @nodoc */
  virtual int ComputeExtrapolationPar(
    CATBody * Wire[2],
    CATLaw **MapLaw1,
    CATLaw **MapLaw2,
    CATBody * Parallel[2],
    CATBody * Extrap[2],
    CATCGMJournalList *Report,
    CATLONG32 WT[2]) = 0;

  /**
     * Returns the relimitation type.
     * @return
     * The type of relimitation.
     * <br><b>Legal values</b>:
     * <dl><dt><tt>1</tt></dt><dd>Straight relimitation
     * <dt><tt>1</tt></dt><dd>Round relimitation
     * </dl>
     */
  virtual int GetExtrapInfo() = 0;

  virtual CATLONG32 GetConnexionInfo() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMExtrapolParallelTool2(); // -> delete can't be called
};

#endif /* CATIPGMExtrapolParallelTool2_h_ */
