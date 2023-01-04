#ifndef CATIPGMGeoToTopOperator_h_
#define CATIPGMGeoToTopOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCGMJournal.h"

class CATBody;
class CATCGMJournalInfo;
class CATCGMJournalList;
class CATDomain;
class CATGeoFactory;
class CATGeometry;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMGeoToTopOperator;

/**
* Base abstract class of the operators that create topology from geometry.
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMGeoToTopOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMGeoToTopOperator();

  /** 
		* Defines the tolerance for assembling the geometry.
		* <br>Very sensitive point. The default value is the factory resolution, 
		* and it is strongly recommended to keep it.
		* @param iTol
	  * The tolerance for assembling the geometry.
		*/
  virtual void SetTolerance(double iTol) = 0;

  /**
	 * Returns the tolerance for assembling the geometry.
	 * @return
	 * The tolerance.
	 */
  virtual double GetTolerance() const = 0;

  /** @nodoc
	 * To decide if non-cell elements can appear as parents in journal items.
	 */
  virtual void SetUseGeometriesInJournalItems(int iUseGeometriesInJournalItems) = 0;

  /** @nodoc */
  virtual void Report(
    CATCGMJournal::Type iType,
    const CATGeometry *iBeforeObjects,
    const CATGeometry *iAfterObjects,
    CATCGMJournalInfo *iOptionalInfo = NULL) = 0;

  /**
	 * Returns the pointer to the topological journal associated with <tt>this</tt> operator.
	 * @return
	 * The pointer to the journal. Remember that you give the journal at the operator creation, 
	 * if you want to have a report. So you have to manage the journal cycle life.
	 */
  virtual CATCGMJournalList *GetReport() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMGeoToTopOperator(); // -> delete can't be called
};

#endif /* CATIPGMGeoToTopOperator_h_ */
