// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : DBS
//
// DESCRIPTION  : 
//
//=============================================================================
// Creation ZUS June 2013
//=============================================================================

#ifndef CATWallAnalyzer_h
#define CATWallAnalyzer_h


#include "CATGMModelInterfaces.h"

#include "CATBoolean.h"
#include "IUnknown.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATCell.h"
#include "CATListOfDouble.h"
#include "CATTopDefine.h"
#include "CATSurParam.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATFace;
class CATBody;
class CATMathPoint;
class CATMathVector;



//----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATWallAnalyzer
{
public:

  /**
   * Constructor
   */
  CATWallAnalyzer();

  /**
   * Destructor
   */
  virtual ~CATWallAnalyzer();

  //--------------------------------------------------------------------------------------------
  // Option
  //--------------------------------------------------------------------------------------------

  /**
  *  Set outgoing direction discard. To use in cases where we might be firing a ray outside the 
  *  input body.
  *  @param iValue
  *     Default value : FALSE
  */

  virtual void SetOutgoingDirectionDiscard(CATBoolean iValue) = 0;


  //--------------------------------------------------------------------------------------------
  // Methods
  //--------------------------------------------------------------------------------------------

  /**
  *  Compute distance and intersection point with a ray (start point, direction vector) to the body.
  *  @param ipInputBody
  *     input body.
  *  @param iStartPoint
  *     input start point of the ray.
  *  @param iDirection
  *     input direction vector of the ray.
  *  @param oDistance
  *     output distance from start point to intersected point.
  *  @param oIntersectedPoint
  *     output intersected point.
  *  @param oIntersectedFace
  *     output intersected face of the input body.
  * @return
  *     HRESULT
  * Legal values : 
  *     - E_FAIL : if KO.
  *     - S_FALSE : if operation failed.
  *     - S_OK : if operation succeeded.
  */

  virtual HRESULT ComputeDistance(CATBody        *  ipInputBody, 
                                  CATMathPoint   *  iStartPoint,
                                  CATMathVector  *  iDirection,
                                  double         &  oDistance,
                                  CATMathPoint   &  oIntersectedPoint,
                                  CATFace       *&  oIntersectedFace) = 0;

  /**
  *  Compute distance and intersection point with a ray (start point, direction vector) to the body.
  *  @param ipInputBody
  *     input body.
  *  @param iStartPoint
  *     input start point of the ray.
  *  @param iDirection
  *     input direction vector of the ray.
  *  @param iMaxThickness
  *     input maximum thickness to discard distance > maximum thickness.
  *  @param oDistance
  *     output distance from start point to intersected point.
  *  @param oIntersectedPoint
  *     output intersected point.
  *  @param oIntersectedFace
  *     output intersected face of the input body.
  *  @param oMinPointSurParam
  *     output param of intersected point (inner or full location).
  *  @param oLocation
  *     output location (CATLocationInner/CATLocationFull/CATLocationOuter).
  *  @param iFaceToStartSearch
  *     input face to start search.
  *  @param iModeLight
  *     input mode to stop at the first intersection finded (inner or full).
  * @return
  *     HRESULT
  * Legal values :
  *     - E_FAIL : if KO.
  *     - S_FALSE : if operation failed.
  *     - S_OK : if operation succeeded.
  */

  virtual HRESULT ComputeDistance(CATBody        *  ipInputBody,
                                  CATMathPoint   *  iStartPoint,
                                  CATMathVector  *  iDirection,
                                  double            iMaxThickness,
                                  double         &  oDistance,
                                  CATMathPoint   &  oIntersectedPoint,
                                  CATFace       *&  oIntersectedFace,
                                  CATSurParam    & oMinPointSurParam,
                                  CATLocation    & oLocation,
                                  CATFace        * iFaceToStartSearch = NULL,
                                  CATBoolean       iModeLight = FALSE) = 0;


  /**
  * @nodoc
  */

  virtual HRESULT ComputeDistance(CATBody        * ipInputBody, 
                                  ListPOfCATFace & iListOfFaces, 
                                  double           iMaxThickness,
                                  double         & oMinDist, 
                                  double         & oMaxDist, 
                                  double         & oAverageDist) = 0;
  /**
  * @nodoc
  */

  /*virtual HRESULT ComputeDistanceAndOppositeFaces(CATBody        * ipInputBody, 
                                                  ListPOfCATFace & iListOfFaces, 
                                                  double           iMaxThickness,
                                                  double         & oMinDist, 
                                                  double         & oMaxDist, 
                                                  double         & oAverageDist,   
                                                  ListPOfCATFace & oListOfOppositeFaces) = 0;*/
  /**
  * @nodoc
  */

  virtual HRESULT ComputeDistanceAndOppositeFaces(CATBody        * ipInputBody, 
                                                  CATFace        * ipFace, 
                                                  double           iMaxThickness,
                                                  double         & oMinDist, 
                                                  double         & oMaxDist, 
                                                  double         & oAverageDist,   
                                                  ListPOfCATFace & oListOfOppositeFaces) = 0;
  /**
  * @nodoc
  */

  virtual HRESULT ComputeDistanceAndOppositeFaces(CATBody              * ipInputBody, 
                                                  const ListPOfCATCell & iListOfInputBodyFaces,
                                                  CATFace              * ipFace, 
                                                  double                 iMaxThickness,
                                                  CATListOfDouble      & oListMinDist, 
                                                  CATListOfDouble      & oListMaxDist, 
                                                  CATListOfDouble      & oListAverageDist,   
                                                  ListPOfCATFace       & oListOfOppositeFaces) = 0;

  

};

/** 
* Constructor [CATWallAnalyzer] 
* @return [out, delete]
*/

ExportedByCATGMModelInterfaces 
  CATWallAnalyzer * CATCreateWallAnalyzer(CATGeoFactory            * iFactory,
                                          CATSoftwareConfiguration * ipConfig);

/**
* Constructor [CATWallAnalyzer]
* @return [out, delete]
*/

ExportedByCATGMModelInterfaces
  CATWallAnalyzer * CATCreateWallAnalyzer(CATGeoFactory            * iFactory,
                                        CATSoftwareConfiguration * ipConfig,
                                        CATBody                  * iBody);


#endif /* CATWallAnalyzer_h */
