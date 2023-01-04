#ifndef CATIPGMClosedFilletRibbonFinder_h_
#define CATIPGMClosedFilletRibbonFinder_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATBody.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "CATDeclarativeContext.h"
#include "CATDeclarativeApplication.h"
#include "CATLISTV_CATMathPoint.h"
#include "ListPOfCATVertex.h"

class CATIPGMClosedFilletRibbonFinder;
class CATClosedFilletRibbonFinderImpl;
class CATGeoFactory;
class CATSoftwareConfiguration;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMClosedFilletRibbonFinder;

class ExportedByCATGMOperatorsInterfaces CATIPGMClosedFilletRibbonFinder: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMClosedFilletRibbonFinder();

  /**
  * Set DeclarativeApplication
  */
  virtual void SetDeclarativeApplication(CATDeclarativeApplication iDeclarativeApplication) = 0;

  /**
  * Set industry for DeclarativeContext
  * if not specified, industry is selected using DRepIndustryAssistant (running time nearly x2)
  */
  virtual void SetDeclarativeContextIndustry(CATDeclarativeContextIndustry iIndustry) = 0;
  
  
  /**
  * Activate the extremity points calculation
  */
  virtual void ActivateExtremitiesCalculation(CATBoolean iExtrem) = 0;
  
  
  /**
  * Activate the curvature change finder
  */
  virtual void ActivateCurvatureChange(CATBoolean iCurvat) = 0;


  /**
  * Returns the number of closed fillet ribbons detected
  */
  virtual int GetNumberOfClosedFilletRibbons() = 0;

  /**
  * Returns S_OK if the corresponding closed ribbon was found
  * <br> iRibbon : Index (from 1 to NumberOfClosedFilletRibbons) of the closed fillet ribbon to retrieve
  * <br> oClosedRibbonFaces : Faces of the closed fillet ribbon to retrieve
  */
  virtual HRESULT GetClosedFilletRibbonFaces(int iRibbon, ListPOfCATFace &oClosedRibbonFaces) = 0;

  /**
  * Returns the number of external fillets crossed by a closed ribbon
  * <br> iRibbon : Index (from 1 to NumberOfClosedFilletRibbons) of the closed fillet ribbon
  */
  virtual int GetNumberOfCrossedFillets(int iRibbon) = 0;

  /**
  * Returns S_OK if the corresponding closed ribbon and crossed fillet was found
  * <br> iRibbon : Index (from 1 to NumberOfClosedFilletRibbons) of the closed fillet ribbon
  * <br> iCrossedFillet : Index (from 1 to NumberOfCrossedFillets(iRibbon)) of the crossed fillet
  * <br> oCrossedFilletContactEdges : Contact edges between the closed ribbon and the crossed fillet
  */
  virtual HRESULT GetCrossedFilletContactEdges(int iRibbon, int iCrossedFillet, ListPOfCATEdge &oCrossedFilletContactEdges) = 0;


  //Added for extremity points
  /**
  * Returns the number of extremity points
  * <br> iRibbon : Index (from 1 to NumberOfClosedFilletRibbons) of the closed fillet ribbon
  */
  virtual int GetNumberOfExtremityPoints(int iRibbon) = 0;

  /**
 * Returns S_OK if the corresponding closed ribbon and extremity points were found
 * <br> iRibbon : Index (from 1 to NumberOfClosedFilletRibbons) of the closed fillet ribbon
 * <br> oExtremityPoints : list of extremity points
 */
  virtual HRESULT GetExtremityPoints(int iRibbon, CATListValCATMathPoint& oExtremityPoints) = 0;

  //Added for curvature vertices
  /**
  * Returns the number of extremity points
  * <br> iRibbon : Index (from 1 to NumberOfClosedFilletRibbons) of the closed fillet ribbon
  */
  virtual int GetNumberOfCurvatureVertices(int iRibbon) = 0;

  /**
 * Returns S_OK if the corresponding closed ribbon and curvature vertices were found
 * <br> iRibbon : Index (from 1 to NumberOfClosedFilletRibbons) of the closed fillet ribbon
 * <br> oCurvatureVertices : list of curvature vertices
 */
  virtual HRESULT GetCurvatureVertices(int iRibbon, ListPOfCATVertex& oCurvatureVertices) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMClosedFilletRibbonFinder(); // -> delete can't be called
};

//----------------------------------------------------------------------------
// Public section
//----------------------------------------------------------------------------
/** 
* Creates a CATIPGMClosedFilletRibbonFinder operator.
* @param iFactory
* Factory in which objects may be created.
* @param iConfig
* CATSoftwareConfiguration to manage upward compatibility of changes in the implementation.
* @param iBody
* Body to be analyzed. 
* @return [out, delete]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMClosedFilletRibbonFinder *CATPGMCreateClosedFilletRibbonFinder(
  CATGeoFactory &iFactory,
  CATSoftwareConfiguration &iConfig,
  CATBody &iBody);

#endif /* CATIPGMClosedFilletRibbonFinder_h_ */
