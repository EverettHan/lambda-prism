#ifndef CATIPGMFilletRibbonAroundRibFinder_h_
#define CATIPGMFilletRibbonAroundRibFinder_h_

// COPYRIGHT DASSAULT SYSTEMES 2021

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATBody.h"
#include "ListPOfCATFace.h"


class CATIPGMFilletRibbonAroundRibFinder;
class CATFilletRibbonAroundRibFinderImpl;
class CATGeoFactory;
class CATSoftwareConfiguration;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFilletRibbonAroundRibFinder;

class ExportedByCATGMOperatorsInterfaces CATIPGMFilletRibbonAroundRibFinder: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMFilletRibbonAroundRibFinder();

  /**
  * Set selected faces from which the propagation should be started
  */
  //void SetSelectionFaces(CATLISTP(CATFace) iSelectionFaces);
  /**
   * Returns S_OK if the corresponding faces were found
   * oTriTangentFaces: list of TriTangent faces found in given body
   */
  virtual HRESULT GetListOfTriTangentFaces(CATLISTP(CATFace) &oTriTangentFaces) = 0;

  /**
  * Returns S_OK if the corresponding faces were found
  * oBiTangentFaces: list of BiTangent faces found in given body
  */
  virtual HRESULT GetListOfBiTangentFaces(CATLISTP(CATFace) &oBiTangentFaces) = 0;

  /**
  * Returns S_OK if the corresponding direction was found for given face
  * oDirectionOfFace: direction of rolling ball for given fillet face 
  */
  virtual HRESULT GetDirectionOfFilletFace(CATFace* iFace, CATMathVector& oDirectionOfFace) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFilletRibbonAroundRibFinder(); // -> delete can't be called
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
ExportedByCATGMOperatorsInterfaces CATIPGMFilletRibbonAroundRibFinder *CATPGMCreateFilletRibbonAroundRibFinder(
  CATGeoFactory &iFactory,
  CATSoftwareConfiguration &iConfig,
  CATBody &iBody);

#endif /* CATIPGMFilletRibbonAroundRibFinder_h_ */
