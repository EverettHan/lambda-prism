#ifndef CATIPGMTopUntrimOperator_h_
#define CATIPGMTopUntrimOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2016

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATExtTopOperator;
class CATGeoFactory;
class CATString;
class CATTopData;
class CATTopUntrimContextForFastRun;
class CATTopUntrimOperatorExt;
class CATListPtrCATCell;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopUntrimOperator;

/**
* Class defining an operator to untrim a surface or a curve.
*
* Create it using <tt>CATPGMCreateTopUntrimOperator</tt> function (see comments of that function on how to use it).
* Execute it by calling <tt>Run</tt> method, and get the result via <tt>GetResult</tt>.
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopUntrimOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopUntrimOperator();

  /**
  * @nodoc
  * Return the fastrun context if it exists, otherwise create it.
  * @return [out, CATBaseUnknown#Release]
  */
  virtual CATTopUntrimContextForFastRun *GetOrCreateTopUntrimContextForFastRun() = 0;

  /**
  * @nodoc
  * Return the fastrun context if it exists.
  * @return [out, CATBaseUnknown#Release]
  */
  virtual CATTopUntrimContextForFastRun *GetNoCreateTopUntrimContextForFastRun() = 0;

  /**
  * @nodoc
  * To be called after Run.
  * If the operation is impossible, returns a value different from 0.
  *
  * If the input body contains cells which are not all on the same support, returns 1, and <tt>GetResult</tt> will return NULL.
  */
  virtual CATLONG32 GetErrorCode() = 0;

  /**
  * @nodoc
  * To be called after Run.
  * If the input surface is twisted, returns TRUE.
  * In this case the call to <tt>GetResult</tt> will return a body built
  * using the 2D bounding box of the input face(s).
  */
  virtual CATBoolean GetIsTwisted() = 0;

  /**
  * @nodoc
  * To be called before Run.
  * Desextrapolation before the untrim
  */
  virtual void SetDesextrapolation(CATBoolean iDesextrapolation, CATBoolean iUseOriginalLimits) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopUntrimOperator(); // -> delete can't be called
};

/**
* @nodoc
* Creates an untrim operator.
*
* @param iFactory
*   The geometrical factory.
* @param iConfig
*   The software configuration.
* @param iBodyToBeUntrimmed
*   The input body. It must be a 2D or 1D body, whose cells are all on the same support.
* @param iListOfCells
*   In the case of a 2D body only, to perform a partial untrim.
*   If the list is specified, for each edge of the list we test if it is able to cut in 2 the result of global untrim.
*   If it is true for all edges of the list, then we build the result face using the non-selected edges + the extra parts associated to each selected edge.
* @param iJournal
*   The topological journal, that will be filled by the operator.
*   Example of the final journal in the case of a 2D body:
*     [] -Creation -> [F_755] Info=1
*     [] -Creation -> [E_759] Info=2
*     [] -Creation -> [E_765] Info=3
*     [] -Creation -> [E_771] Info=4
*     [] -Creation -> [E_777] Info=5
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopUntrimOperator *CATPGMCreateTopUntrimOperator(
  CATGeoFactory &iFactory,
  CATSoftwareConfiguration &iConfig,
  CATBody *iBodyToBeUntrimmed,
  CATListPtrCATCell *iListOfCells,
  CATCGMJournalList *iJournal);

#endif /* CATIPGMTopUntrimOperator_h_ */
