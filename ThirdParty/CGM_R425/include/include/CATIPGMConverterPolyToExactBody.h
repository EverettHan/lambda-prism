#ifndef CATIPGMConverterPolyToExactBody_h_
#define CATIPGMConverterPolyToExactBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2016

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMPolyTopOperator.h"
#include "CATCGMJournal.h"

class CATBody;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMConverterPolyToExactBody;

class ExportedByCATGMOperatorsInterfaces CATIPGMConverterPolyToExactBody: public CATIPGMPolyTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMConverterPolyToExactBody();

  //=============================================================================
  // Optional Settings
  //=============================================================================
  /** 
  * @nodoc 
  * Sets the type of journal items 
  * (CATCGMJournal::Creation or CATCGMJournal::Modification)
  * default is Creation
	*/
  virtual void SetJournalType(CATCGMJournal::Type iJournalType) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMConverterPolyToExactBody(); // -> delete can't be called
};

/**
 * Creates a CATIPGMConverterPolyToExactBody operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iBody
 * The pointer to the polyhedral body to convert
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMConverterPolyToExactBody *CATPGMCreateConverterPolyToExactBody(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody);

#endif /* CATIPGMConverterPolyToExactBody_h_ */
