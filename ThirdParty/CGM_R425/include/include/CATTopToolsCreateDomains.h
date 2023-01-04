#ifndef CATTopToolsCreateDomains_H
#define CATTopToolsCreateDomains_H

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATListOfCATCells.h"
#include "CATListOfInt.h"
#include "ListPOfCATDomain.h"

class CATBody;
class CATDomain;
class CATTopToolsCreateDomains;
class CATTopData;


// ===============================================================================
//  I. Proper NEW Constructor [OFFICAL]
// ===============================================================================
/**
* Creates a CATTopToolsCreateDomains operator. 
* [Compliant with Polyhedral Modeler]
*  -> The created body will  be Polyhedral if the input cells are polyhedral, 
*     exact/continuous (cgm modeler) otherwise.
* @param ipFactory
*   The input CGM Container.
* @param iTopData
*   A pointer to the topological data (versioning)
* @param iCellList
*   The list of cells to be used to created new domains.
* @param iOrientationList
*   The list of cell orientations. It is not recommended to specify orientations unless you
*   can guarantee that the resulting topology is consistent. The operator computes the right
*   orientations and if the computed orientations conflict with the input ones, an exception is raised.

* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATTopologicalObjects CATTopToolsCreateDomains * CATCreateNewTopCreateDomains(CATGeoFactory             * ipFactory,
                                                                                        const CATTopData          & iTopData,
                                                                                        const CATLISTP(CATCell)   & iCellList, 
                                                                                        const CATListOfInt        & iOrientationList);


/**
*  II. 
* ---------------------------------------------------------------------------------
*  - NEW -
*
* EASY CALL to CATCreateNewTopCreateDomains.
* Generic Run - Compliant polyhedral modeler.
* Under Try-Catch : Create, run, and get result from operator, then delete it. 
* All in one single line. 
* ---------------------------------------------------------------------------------
*/
ExportedByCATTopologicalObjects CATBody * CallTopToolsCreateDomains(CATGeoFactory             * ipFactory, 
                                                                    CATSoftwareConfiguration  * iConfig, 
                                                                    const CATLISTP(CATCell)   & iCellList, 
                                                                    const CATListOfInt        & iOrientationList,                                                                    
                                                                    CATBoolean                  iAuthorizeAnyOrientation=FALSE,
                                                                    CATLISTP(CATDomain)       * oCreatedDomains = NULL);


/**
* Class defining an operator to create one or more domains from a list of cells. 
* This operator manages the cell connexity. From a set of cells which are not necessarily connected, the 
* operator gathers connected cells into domains. The result is a new body which is not frozen.
* No journal is created by the operator.
*/

class ExportedByCATTopologicalObjects CATTopToolsCreateDomains : public CATTopOperator
{
  
  CATCGMVirtualDeclareClass(CATTopToolsCreateDomains);
public:

  // No Doc to avoid question about PCS tuning on intermediaite Bodies
  virtual void CATCXForceActivate() = 0; // If Body is mandatory ready with inverse links
  virtual void CATCXForceInactivate() = 0; // If Body has needs for inverse links

  // To Force Enhanced management of TopToolsCreateDomains
  virtual void MakeClosedShellAsIsolatedLump() = 0;


  //
  // -- NEW -- [Polyhedreal modeler Compliant]
  // 
  // Can only be used only with the CATCreateNewTopCreateDomains(CATGeoFactory *,const CATTopData & , const CATLISTP(CATCell) &, const CATListOfInt &);
  // return E_FAIL otherwise. 
  //
  // Option to call before Run(), allowing the caller to give a list of inconsistent orientations in the Create, 
  // without any error during the computation.
  // This option is compliant with any case of input list of orientations, empty or not.
  // If not empty, the input list of orientations will be considered as a preference, and not any more as a strict specification.
  //
  //
  virtual HRESULT AuthorizeAnyOrientation(CATBoolean iVal=TRUE) = 0;

 /** 
  * Retrieve the creates domains if the run has returned 0.
  * @param oCreatedDomains
  *   The created domains
  * @return 
  *   return code E_FAIL if called before run or run is KO.
  *   S_OK otherwise.
  */
  virtual HRESULT GetCreatedDomains(ListPOfCATDomain & oCreatedDomains) const = 0;


 /**
  * Retrieve the final computed orientation if the run has returned 0.
  * @param oComputedOrientations
  *   The orientation list.
  * @param ioOriHaveBeenChanged [optional]
  *   A pointer on the boolean value.
  *   *ioOriHaveBeenChanged = TRUE, if the returned orienations are different from input iOrientationList.
  *   *ioOriHaveBeenChanged = FALSE, if no orientations has been changed from input.
  * @return 
  *   return code E_FAIL if called before run or run is KO.
  *   S_OK otherwise.
  */
  virtual HRESULT GetComputedOrientations(CATListOfInt & oComputedOrientations, CATBoolean * ioOriHaveBeenChanged = NULL) const = 0;



protected:


  CATTopToolsCreateDomains(CATGeoFactory *,  const CATTopData &iData);
  CATTopToolsCreateDomains(CATGeoFactory *,  CATCGMJournalList*); // To Remove !

private :
  // copy constructeur et affectation (lancent une exception), ne pas les appeler
  CATTopToolsCreateDomains(const CATTopToolsCreateDomains & iOrig);
  CATTopToolsCreateDomains & operator= (const CATTopToolsCreateDomains & iOrig);

};





// ===============================================================================
//  Constructor 1 - OLD : Please Use CATCreateNewTopCreateDomains instead
// 
// This constructor triggers and old algorithm that 
// do not behave as a proper CATTopOperator... 
//
// ===============================================================================
/**
* Creates a CATTopToolsCreateDomains operator. 
* @param iBodyFactory
* The input body.
* @param iCells
* The list of cells to be used to created new domains.
* @param iOrientations
* The list of cell orientations. It is not recommended to specify orientations unless you
* can guarantee that the resulting topology is consistent. The operator computes the right
* orientations and if the computed orientations conflict with the input ones, an exception is raised.
* @param oCreatedDomains
* The created domains.
* @param iTopData
* A pointer to the topological data.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATTopologicalObjects CATTopToolsCreateDomains *CATCreateTopCreateDomains(CATBody                   * iBodyFactory, 
                                                                                    const CATLISTP(CATCell)   & iCells, 
                                                                                    const CATListOfInt        & iOrientations,
                                                                                    CATLISTP(CATDomain)       & oCreatedDomains,
                                                                                    const CATTopData          & iTopData );



// =====================================================================================
//   ####      DO NOT USE - INTERNAL ONLY   ####
// =====================================================================================

/**
* ---------------------------------------------------------
* @DEPRECATED R424-CXR32
* ---------------------------------------------------------
* Creates a CATTopToolsCreateDomains operator. 
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
#ifdef _WINDOWS_SOURCE
__declspec(deprecated("is deprecated [R424/R2022x] - Use the right CATCreateNewTopCreateDomains instead."))
#endif
ExportedByCATTopologicalObjects CATTopToolsCreateDomains *CATCreateTopCreateDomainsDEDICATED
(
 CATBody                   *iBodyFactory, 
 const CATLISTP(CATCell)   &iCells, 
 const CATListOfInt        &iOrientations,
 CATLISTP(CATDomain)       &iCreatedDomains,
 const CATTopData          &iTopData,
 CATBoolean                 iAddDomain = TRUE,
 CATCell                   *iMasterCell = NULL
);

/**
* ---------------------------------------------------------
* @DEPRECATED R424-CXR32
* ---------------------------------------------------------
* Creates a CATTopToolsCreateDomains operator. 
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
#ifdef _WINDOWS_SOURCE
__declspec(deprecated("is deprecated [R424/R2022x] - Use the right CATCreateNewTopCreateDomains instead."))
#endif
ExportedByCATTopologicalObjects CATTopToolsCreateDomains *  CATCreateTopCreateDomains(CATBody                   *iBodyFactory, 
                                                                                       const CATLISTP(CATCell)   &iCells, 
                                                                                       const CATListOfInt        &iOrientations,
                                                                                       CATLISTP(CATDomain)       &iCreatedDomains,
                                                                                       CATBoolean                 iAddDomain  = TRUE,
                                                                                       CATCell                   *iMasterCell = NULL,
                                                                                       CATSoftwareConfiguration  *iSoftwareVersion = NULL,
                                                                                       CATBoolean                 iAvoidFirstVersion = FALSE
);

#endif

