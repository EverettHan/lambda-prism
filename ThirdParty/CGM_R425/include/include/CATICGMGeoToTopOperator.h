#ifndef CATICGMGeoToTopOperator_h_
#define CATICGMGeoToTopOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
* @CAA2Level L1
* @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATCGMJournalInfo;
class CATCGMJournalList;
class CATDomain;
class CATGeoFactory;
class CATGeometry;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMGeoToTopOperator;

/**
* Base abstract class of the operators that create topology from geometry.
*/
class ExportedByCATGMOperatorsInterfaces CATICGMGeoToTopOperator: public CATICGMTopOperator
{
public:
	/**
	* Constructor
	*/
	CATICGMGeoToTopOperator();

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
	virtual ~CATICGMGeoToTopOperator(); // -> delete can't be called
};

#endif /* CATICGMGeoToTopOperator_h_ */
