#ifndef CATIPGMExtrapolParallelTool_h_
#define CATIPGMExtrapolParallelTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMVirtual.h"
#include "CATDataType.h"

class CATBody;
class CATCGMJournalList;
class CATIPGMDistanceTool;
class CATGeoFactory;
class CATLaw;
class CATICGMDistanceTool;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMExtrapolParallelTool;

//
//--------------------------------------------------------------------------
//
/**
 * Class defining the parallel computation.
 * <br>This class must be created with the @href CATPGMCreateExtrapolParallelTool
 * global function and is used by the @href CATIPGMTopParallel operator
 * to define its parameters.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMExtrapolParallelTool: public CATIPGMVirtual
{
public:
  /**
   * Constructor
   */
  CATIPGMExtrapolParallelTool();

  /** @nodoc */
  virtual int ComputeExtrapolationPar(
    CATBody *Wire[2],
    CATLaw **MapLaw1,
    CATLaw **MapLaw2,
    CATBody *Parallel[2],
    CATBody *Extrap[2],
    CATCGMJournalList *Report,
    CATLONG32 WT[2]) = 0;

  /** @nodoc */
  virtual int ComputeInMatter(
    CATBody *Wire,
    CATLaw **MapLaw1,
    CATBody *PointToLocate,
    double &Radius,
    double &MinDist) = 0;

  /**
     * Retrieves the type of computation.
     * @param oDistTool [out, IUnknown#Release]
     * The pointer to the definition of the computation type. 
     */
  virtual void GetDistanceTool(CATICGMDistanceTool *&oDistTool) = 0;

  /**
     * Retrieves the factory that creates the resulting body.
     * @param oFactory
     * The pointer to the factory that creates the resulting body. 
     */
  virtual void GetFactory(CATGeoFactory *&oFactory) = 0;

  /**
     * Retrieves the skin body on which the parallel is computed.
     * @param oSupport
     * The pointer to the skin body. 
     */
  virtual void GetSupport(CATBody *&oSupport) = 0;

  /**
     * Retrieves the topological data associated with <tt>this</tt> tool.
     * @param oData
     * The pointer to the topological data.
     */
  virtual void GetData(CATTopData *&oData) = 0;

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

  /** @nodoc */
  virtual void SetReport(CATCGMJournalList *iJournal) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMExtrapolParallelTool(); // -> delete can't be called
};

/**
 * Creates a parallel computation definition.
 * @param iGeoFactory
 * The pointer to the geometry factory that creates the resulting body.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iDist
 * The type of computation (parallel, geodesic).
 * @param iSkinBody
 * The pointer to the skin body on which the parallel is computed.
 * @param iRelimitType
 * The type of relimitation.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>1</tt></dt><dd>Straight relimitation
 * <dt><tt>0</tt></dt><dd>Round relimitation
 * </dl>
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMExtrapolParallelTool *CATPGMCreateExtrapolParallelTool(
  CATGeoFactory *iGeoFactory,
  CATTopData *iData,
  CATICGMDistanceTool *iDist,
  CATBody *iSkinBody,
  int iRelimitType = 1);

#endif /* CATIPGMExtrapolParallelTool_h_ */
