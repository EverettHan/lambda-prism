#ifndef CATPositionPtVolOperator_h
#define CATPositionPtVolOperator_h

// COPYRIGHT DASSAULT SYSTEMES  2005
/**
 * @level Protected
 * @usage U1
 */ 

#include "CATTopDef.h"
#include "CATMathBox.h"
#include "CATMathPoint.h"
#include "CATTopOperator.h"
#include "CATIACGMLevel.h"
class CATGeoFactory;
class CATVolume;
class CATFace;
class CATTopData;

#include "ExportedByCATTopologicalObjects.h"
/**
 * Class defining the operator that tests the position of a 3D point 
 * with respect to a volume.
 * The CATPositionPtVolOperator operator is created with the 
 * <tt>CATCreatePositionPtVolOperator</tt> global function.
 * It must be directly deleted with the usual C++ <tt>delete</tt> 
 * operator after use. It is not streamable. 
 *<li>It must be executed by the <tt>Run</tt> method. 
 *<li>The result ot the test is accessed with the <tt>GetLocationResult</tt> method.
 *</ul>
 */ 

class ExportedByCATTopologicalObjects CATPositionPtVolOperator: public CATTopOperator
{

  CATCGMVirtualDeclareClass(CATPositionPtVolOperator);
 public :
  /** @nodoc */
  /*  USE THE CATCreatePositionPtVolOperator global function instead */
  CATPositionPtVolOperator(CATGeoFactory * iFactory, CATTopData * iTopData);
  /** @nodoc */
  CATPositionPtVolOperator(CATGeoFactory * iFactory);
  /** @nodoc */
  virtual ~CATPositionPtVolOperator();

#ifdef CATIACGMR424CAA 
  /** @nodoc   */
  virtual void SetPoint(CATMathPoint & PointToPosition) = 0;
#endif

 /**
   * Runs <tt>this</tt> operator.
  */
  virtual int         Run() = 0;
  
  /**
   * Returns the 3D point location.
   * <br>To be called after the <tt>Run</tt> method.
   * @return
   * <dl>
   * <dt><tt>CATLocationInner</tt><dd> if the point is inside the volume
   * <dt><tt>CATLocationOuter</tt><dd> if the point is out of the volume
   * <dt><tt>CATLocationFull</tt><dd> if the point is on the boundary of
   * the volume.
   * </dl>
   */ 
  virtual CATLocation GetLocationResult() = 0;
};
  /** @nodoc */
ExportedByCATTopologicalObjects
CATPositionPtVolOperator*  CATCreatePositionPtVolOperator(CATGeoFactory * iFactory, 
                                                          CATMathPoint  & iPoint, 
                                                          CATVolume     * iVolume);
  /** @nodoc */
ExportedByCATTopologicalObjects
CATPositionPtVolOperator*  CATCreatePositionPtVolOperator( CATGeoFactory * iFactory, 
                                                           CATMathPoint  & iPoint, 
                                                           CATFace      ** iFacesArray, 
                                                           CATLONG32       nbFacesInArray, 
                                                           CATSide       * iSidesArray = NULL);
/**
 * Creates an operator to test the position of a point with regards to a volume.
 * @param iFactory
 * The factory of the geometry. 
 * @param iTopData
 * The pointer to the CATTopData.
 * @param iPoint
 * The point to be tested.
 * @param iVolume
 * The pointer to the volume.
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
 */
ExportedByCATTopologicalObjects
CATPositionPtVolOperator*  CATCreatePositionPtVolOperator(CATGeoFactory * iFactory, 
                                                          CATTopData    * iTopData,
                                                          CATMathPoint  & iPoint, 
                                                          CATVolume     * iVolume);
 /** @nodoc */
ExportedByCATTopologicalObjects
CATPositionPtVolOperator*  CATCreatePositionPtVolOperator( CATGeoFactory * iFactory, 
                                                           CATTopData    * iTopData,
                                                           CATMathPoint  & iPoint, 
                                                           CATFace      ** iFacesArray, 
                                                           CATLONG32       nbFacesInArray, 
                                                           CATSide       * iSidesArray = NULL);
#endif
