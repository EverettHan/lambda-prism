#ifndef CATCubicMultiSurfaceIntersectionCurve_H
#define CATCubicMultiSurfaceIntersectionCurve_H

// COPYRIGHT DASSAULT SYSTEMES  2000

#include "Y30C3XGG.h"
#include "CATGeoOperator.h"
#include "CATLISTP_CATMathPoint.h"

class CATMultiSurface;
class CATMathPoint;
class CATEdgeCurve;
class CATMathFunctionX;

/**
* @nodoc
* Classe permettant l'intersection de deux reseaux de surfaces.
*
*
*/
class ExportedByY30C3XGG CATCubicMultiSurfaceIntersectionCurve : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATCubicMultiSurfaceIntersectionCurve);
public:
/**
* @nodoc
*     MultiSurfaces  :  Liste des surfaces. Les surfaces sont supposees rangees dans la liste de maniere a
*                       former une matrice NU * NV. Deux paves contigus de la matrice sont supposes continus
*                       G0 (au sens du modeleur emetteur), les limites courantes de chaque surface correspondnt a la
*                       partie utile (a revoir).
*
*/
  
  CATCubicMultiSurfaceIntersectionCurve(CATGeoFactory * iFactory);
  
  /**
  * @nodoc
  * Destructor.
  */
  virtual ~CATCubicMultiSurfaceIntersectionCurve();
  
  /**
  * @nodoc
  * Set the list of init/exit 3D points that defines limitations of the intersection  
  */
  virtual void SetStartingPoints(CATLISTP(CATMathPoint)* iPointList)=0;
  
   /**
  * @nodoc
  * Set the list of CrvParam that defines the intersection  
  */
  virtual void SetParamOnCurve(CATListOfDouble & iCrvList)=0;
  
  /**
  * @nodoc
  * Creates the  solution equation of <tt>this</tt> CATInterpolationMultiSurface operator.
  */
  virtual void GetResults(CATMathFunctionX*& oX, CATMathFunctionX*& oY,CATMathFunctionX*& oZ)=0;
  /**
  * @nodoc
  * Creates the  solution curves of <tt>this</tt> CATInterpolationMultiSurface operator.
  */
  virtual void GetCurvesResults( CATLISTP(CATCurve) &ListOfCurves)=0;

};

/**
* @nodoc
* Create MultiSurface Interpole Operator
*/
ExportedByY30C3XGG
CATCubicMultiSurfaceIntersectionCurve * CATCreateCubicMultiSurfaceIntersectionCurve(CATGeoFactory *iWhere,
                                                                                    CATSoftwareConfiguration *iConfig,
                                                                                    CATMultiSurface *iSurface1,
                                                                                    CATMultiSurface *iSurface2);


#endif
