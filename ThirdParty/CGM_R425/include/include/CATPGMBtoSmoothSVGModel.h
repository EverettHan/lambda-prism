#ifndef CATPGMBtoSmoothSVGModel_h_
#define CATPGMBtoSmoothSVGModel_h_

// COPYRIGHT DASSAULT SYSTEMES 2015

#include "CATGMOperatorsInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATCollec.h"

class CATBody;
class CATSoftwareConfiguration;
class CATMathSetOfPointsND;
class CATMathVector; 
class CATBody;
class CATGeoFactory;
class CATMathPoint;
class CATLISTP(CATBody);

/**
 * Class defining a geometric operator that convert a set of Controles points (representing a C0, C1 or C2 curves ) to create a Bezier, B-spline C2 result.
 * <br>The CATPGMBtoSmoothSVGModel operator follows the global frame of the geometric operators: 
 *<ul>
 * <li>A CATPGMBtoSmoothSVGModel operator is created with the <tt>CATBtoCreateSmoothSVGModel</tt> global method 
 * and must be directly <tt>delete</tt>d with the usual C++ delete operator after use.
 * It is is not streamable. 
 *<li>Options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>In both cases, the result is accessed with the <tt>Getxxx</tt> methods. 
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATPGMBtoSmoothSVGModel: public CATCGMVirtual
{
public :
  /**
   * Constructor
   */
  CATPGMBtoSmoothSVGModel();

  /**
   * Destructor
   */
  virtual ~CATPGMBtoSmoothSVGModel (); 

  /**
  * Runs <tt>this</tt> operator .
  */ 
  virtual int Run () = 0; 
  
  // 1 Mode Exact
  // 2 Mode C2 (Nurbs Catia )
  // 3 Mode Simplify 
  virtual void setModeConversion(const int iMode=2) = 0 ;

  /**
  * Defines the degree of the resulting curve.
  * @param iDegree
  * The degree value for each curve (iDegree >= (iOrder-1)).
  */
  virtual void SetDegree (const int iDegree=5) = 0;  
	
	/**
	* Defines the maximum number of arcs of the created curve ( Use In Simplfy Mode : not yet implemented ).
	* @param iMaxNumberOfArcs
	* The maximum number of arcs of each created curve 
	* @param iInternalContinuity
	* The Internal continuity of each created curve, iInternalContinuity = 2, 3, 4.
	*/
	virtual void SetMaxNumberOfArcs (int iMaxNumberOfArcs = 64) = 0;
   
  /**
  * Defines the Tolerance of the result ( Use In Simplfy Mode : not yet implemented) . 
  * @param iTol3d
	* The maximum distance between the input points and the SetOfCurves. 
  */
  virtual void SetTolerance (const double iTol3d  = 0.1 ) = 0; 

  // ===========================================================================================
  //
  // ***************************** Les Fonctions Get ***************************** 
  //
  // ===========================================================================================
  /**
	* Returns the SetOfCurves Result.  
  * List Of body result according to G1 discontinuities detected 
  */
  virtual void GetResult (CATLISTP(CATBody) &oBodiesResult) = 0 ;  
};

/**
* Creates the operator that smoothes a set of Controles points to create a Set of Body.
* @param iFactory
* The pointer to the factory of the geometry.
* @param iOrder
* The ??? = 4 .
* @param iNbOfPoints
* The number of Controles points (multiple of iOrder).
* @param iTabOfCtrlPoints
* The pointer to the set of Controles points (Its dimension=3).
* @return
* The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
*/
ExportedByCATGMOperatorsInterfaces CATPGMBtoSmoothSVGModel *CATPGMBtoCreateSmoothSVGModel(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration * iConfig,
  int iOrder,
  int iNbOfPoints,
  CATMathPoint *iTabOfCtrlPoints);

#endif /* CATPGMBtoSmoothSVGModel_h_ */
