#ifndef CATIPGMTopToolsDuplicateDomains_h_
#define CATIPGMTopToolsDuplicateDomains_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATIPGMTopToolsDuplicateDomains;
class CATTopology;
class CATLISTP(CATDomain);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopToolsDuplicateDomains;

//--------------------------------------------------------------------------------------------------
// L'outil topologique proprement dit
//--------------------------------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATIPGMTopToolsDuplicateDomains: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopToolsDuplicateDomains();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopToolsDuplicateDomains(); // -> delete can't be called
};

//--------------------------------------------------------------------------------------------------
// Constructeur de l'outil topologique
//--------------------------------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopToolsDuplicateDomains *CATPGMCreateTopToolsDuplicateDomains(
  CATBody *inputBody,
  short iContainedCellsDimension,
  short iContainingCellDimension,
  CATLISTP(CATDomain) &iCreatedDomains,
  const CATTopData &iTopData,
  CATTopology *iBodyOrCell = NULL,
  const CATBoolean iWithInvert = TRUE);

#endif /* CATIPGMTopToolsDuplicateDomains_h_ */
