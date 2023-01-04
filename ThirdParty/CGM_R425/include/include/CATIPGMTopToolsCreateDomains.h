#ifndef CATIPGMTopToolsCreateDomains_h_
#define CATIPGMTopToolsCreateDomains_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"

class CATBody;
class CATDomain;
class CATIPGMTopToolsCreateDomains;
class CATCell;
class CATLISTP(CATDomain);
class CATLISTP(CATCell);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopToolsCreateDomains;

/**
* Class defining an operator to create one or more domains from a list of cells. 
* This operator manages the cell connexity. From a set of cells which are not necessarily connected, the 
* operator gathers connected cells into domains. The result is a new body which is not frozen.
* No journal is created by the operator.
*/
class ExportedByCATGMModelInterfaces CATIPGMTopToolsCreateDomains: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopToolsCreateDomains();

  // No Doc to avoid question about PCS tuning on intermediaite Bodies
  virtual void CATCXForceActivate() = 0;

  virtual void CATCXForceInactivate() = 0;

  // To Force Enhanced management of TopToolsCreateDomains
  virtual void MakeClosedShellAsIsolatedLump() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopToolsCreateDomains(); // -> delete can't be called
};

//--------------------------------------------------------------------------------------------------
// Constructeur OFFICIEL DE l'outil topologique
//--------------------------------------------------------------------------------------------------
/**
* Creates a CATIPGMTopToolsCreateDomains operator. 
* @param iBodyFactory
* The input body.
* @param iCells
* The list of cells to be used to created new domains.
* @param iOrientations
* The list of cell orientations. It is not recommended to specify orientations unless you
* can guarantee that the resulting topology is consistent. The operator computes the right
* orientations and if the computed orientations conflict with the input ones, an exception is raised.
* @param iCreatedDomains
* The created domains.
* @param iTopData
* A pointer to the topological data.
 * @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATIPGMTopToolsCreateDomains *CATPGMCreateTopCreateDomains(
  CATBody *iBodyFactory,
  const CATLISTP(CATCell) &iCells,
  const CATListOfInt &iOrientations,
  CATLISTP(CATDomain) &iCreatedDomains,
  const CATTopData &iTopData);

















//--------------------------------------------------------------------------------------------------
// Constructeurs ADVANCED DEDICATED TO CGM Specific purpose ...
//--------------------------------------------------------------------------------------------------
/**

* ---------------------------------------------------------
* @DEPRECATED R424-CXR32
* ---------------------------------------------------------

* Creates a CATIPGMTopToolsCreateDomains operator. 
* Internal use only.
* @param iBodyFactory
* The input body.
* @param iCells
* The list of cells to be used to created new domains.
* @param iOrientations
* The list of cell orientations. It is not recommended to specify orientations unless you
* can guarantee that the resulting topology is consistent. The operator computes the right
* orientations and if the computed orientations conflict with the input ones, an exception is raised.
* @param iCreatedDomains
* The created domains.
* @param iTopData
* A pointer to the topological data.
* @param iAddDomain
* Internal use.
* @param iMasterCell
* Internal use.
 * @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
// [[deprecated("CATIPGMTopToolsCreateDomains is deprecated [R424/R2022x] - Use the right CATCreate instead.")]]
#ifdef _WINDOWS_SOURCE
__declspec(deprecated("is deprecated [R424/R2022x] - Use the right CATCreate instead."))
#endif
ExportedByCATGMModelInterfaces CATIPGMTopToolsCreateDomains *CATPGMCreateTopCreateDomainsDEDICATED(
  CATBody *iBodyFactory,
  const CATLISTP(CATCell) &iCells,
  const CATListOfInt &iOrientations,
  CATLISTP(CATDomain) &iCreatedDomains,
  const CATTopData &iTopData,
  CATBoolean iAddDomain = TRUE,
  CATCell *iMasterCell = NULL);

//--------------------------------------------------------------------------------------------------
// Constructeurs Intermediaire  : amener a disparaitre
//--------------------------------------------------------------------------------------------------
/**

* ---------------------------------------------------------
* @DEPRECATED R424-CXR32
* ---------------------------------------------------------

* Creates a CATIPGMTopToolsCreateDomains operator. 
* Internal use only.
* @param iBodyFactory
* The input body.
* @param iCells
* The list of cells to be used to created new domains.
* @param iOrientations
* The list of cell orientations. It is not recommended to specify orientations unless you
* can guarantee that the resulting topology is consistent. The operator computes the right
* orientations and if the computed orientations conflict with the input ones, an exception is raised.
* @param iCreatedDomains
* The created domains.
* @param iAddDomain
* Internal use.
* @param iMasterCell
* Internal use.
* @param iSoftwareVersion
* A pointer to the software configuration.
* @param iAvoidFirstVersion
* Internal use.
 * @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATIPGMTopToolsCreateDomains *CATPGMCreateTopCreateDomains(
  CATBody *iBodyFactory,
  const CATLISTP(CATCell) &iCells,
  const CATListOfInt &iOrientations,
  CATLISTP(CATDomain) &iCreatedDomains,
  CATBoolean iAddDomain = TRUE,
  CATCell *iMasterCell = NULL,
  CATSoftwareConfiguration *iSoftwareVersion = NULL,
  CATBoolean iAvoidFirstVersion = FALSE);

#endif /* CATIPGMTopToolsCreateDomains_h_ */
