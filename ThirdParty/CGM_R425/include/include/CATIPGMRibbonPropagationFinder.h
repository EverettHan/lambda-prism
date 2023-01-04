#ifndef CATIPGMRibbonPropagationFinder_h_
#define CATIPGMRibbonPropagationFinder_h_

// COPYRIGHT DASSAULT SYSTEMES 2021

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATBody.h"
#include "ListPOfCATFace.h"

class CATGeoFactory;
class CATIPGMRibbonPropagationFinder;
class CATRibbonPropagationFinderImpl;
class CATSoftwareConfiguration;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMRibbonPropagationFinder;

class ExportedByCATGMOperatorsInterfaces CATIPGMRibbonPropagationFinder: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMRibbonPropagationFinder();

  /**
  * Set selected faces from which the propagation should be started
  */
  virtual void SetSelectionFaces(CATLISTP(CATFace) &iSelectionFaces) = 0;

  /**
  * Returns S_OK if the corresponding porpagation faces were found
  * oPropagationFaces: list of faces found by propagation for selected faces
  */
  virtual HRESULT GetListOfPropagationFaces(CATLISTP(CATFace) &oPropagationFaces) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMRibbonPropagationFinder(); // -> delete can't be called
};

//----------------------------------------------------------------------------
// Public section
//----------------------------------------------------------------------------
/** 
* Creates a CATIPGMRibbonPropagationFinder operator.
* @param iFactory
* Factory in which objects may be created.
* @param iConfig
* CATSoftwareConfiguration to manage upward compatibility of changes in the implementation.
* @param iBody
* Body to be analyzed. 
* @return [out, delete]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMRibbonPropagationFinder *CATPGMCreateRibbonPropagationFinder(
  CATGeoFactory &iFactory,
  CATSoftwareConfiguration &iConfig,
  CATBody &iBody);

#endif /* CATIPGMRibbonPropagationFinder_h_ */
