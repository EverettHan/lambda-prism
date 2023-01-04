#ifndef CATIPGMLiveShapeManifoldTrackerOpe_h_
#define CATIPGMLiveShapeManifoldTrackerOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2014

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"
#include "CATListOfULONG32.h"

class CATGMLiveShapeManifoldTrackerImpl;
class CATSoftwareConfiguration;
class CATLISTP(CATManifold);
class CATLISTP(CATBody);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMLiveShapeManifoldTrackerOpe;

/**
* This class is used to select faces with.<br>
**/
class ExportedByCATGMOperatorsInterfaces CATIPGMLiveShapeManifoldTrackerOpe: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMLiveShapeManifoldTrackerOpe();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMLiveShapeManifoldTrackerOpe(); // -> delete can't be called
};

//==============================================================================
// Data
//==============================================================================
//==============================================================================
// CATGMLiveShapeManifoldTracker - 1
//==============================================================================
/**
* static methode to get the Journal of CATManifold<br>
**/
ExportedByCATGMOperatorsInterfaces HRESULT CATPGMLiveShapeManifoldTracker(
  const CATLISTP(CATBody) &iPreviousBodyList,
  const CATLISTP(CATBody) &iCurrentBodyList,
  const CATCGMJournalList &iCMJournal,
  const CATLISTP(CATManifold) &iPreviousManifoldList,
  CATSoftwareConfiguration &iConfig,
  CATCGMJournalList &oManifoldJournal);

//==============================================================================
// CATGMLiveShapeManifoldTracker - 2
//==============================================================================
/**
* static methode to get the Journal of CATManifold<br>
**/
ExportedByCATGMOperatorsInterfaces HRESULT CATPGMLiveShapeManifoldTracker(
  const CATLISTP(CATBody) &iPreviousBodyList,
  const CATLISTP(CATBody) &iCurrentBodyList,
  const CATCGMJournalList &iCMJournal,
  const CATListOfULONG32  &iGeometryTypeList,
  CATSoftwareConfiguration &iConfig,
  CATCGMJournalList &oManifoldJournal);

#endif /* CATIPGMLiveShapeManifoldTrackerOpe_h_ */
