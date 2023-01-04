#ifndef CATIPGMTopConcatenateSurOperator_h_
#define CATIPGMTopConcatenateSurOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATIsoParameter.h"
#include "CATMathConstant.h"

class CATBody;
class CATCell;
class CATFace;
class CATGeometry;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopConcatenateSurOperator;

/**
* Performs the concatenation of two juxtaposed surfaces.<br>
* ( a advanced version of the operator allows the concatenation of several list
* of juxtaposed surfaces ).
* Note: the concatenation operation is limited by strong geometrical constraints.<br>
* The concatenation operates on a single body which is itself made up of 
* a single shell.
* This shell contains only two faces linked by a common edge 
* (in interactive mode, faces can be joined by the Join operator, as developer
* you must use the CATIPGMHybAssemble operator).
* Each face is lying on a CATNurbsSurface 
* and is limited by the four limit-isoparametrics of the surface.
* 
* The result is one body containing a mono-face shell limited 
* by the limit-isoparametrics of the concatenated surfaces.
* <br>
* The concatenation is such that the common direction is homogeneized :
*     <ul>
*     <li> degree is the max degree,
*     <li>the number of knots of the result is equal or less than 
*     the sum of the numbers knots.
*     </ul>
* The user can specify a maximum deformation. If he does not specify it
* or give a negative value, the concatenation will be done with the minimum
* deviation.
*
* A new implemetation has been provided to concatenate not only two faces , but to concatenate several list of faces
* Each list of faces will then be transformed into one face.
* 
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopConcatenateSurOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopConcatenateSurOperator();

  /**
    * @nodoc
	* Specifies the admissible tolerance. 
	* if this tolerance is negative, we will force the concatenation
  * thanks to the threshold value . 
  * It will be the default value, thus enabling us to concatenate automatically
  * with the smallest deviation. 
	*/
  virtual void SetDeformationTolerance(double iTolerance) = 0;

  /**
    * @nodoc
	* Deprecated.
	*/
  virtual CATLONG32 SetTolerance(double iTolerance) = 0;

  /**
    * @nodoc
	* Checks the input data.
	* Return values:
	*     0 - the input data meet the specified concatenation criteria
    *     1 - the body is not mono-domain.
    *     2 - the domain is not a shell.
    *     3 - the shell is not made of up of two faces
    *     4 - one face does not lie on a Nurbs surface.
    *     5 - both faces are lying on the same surface.
    *     6 - one face is not limited by the four limit-isoparametrics of its surface.
    *     7 - both faces are not corectly linked by a common edge.
    * Note : this method is meaningless in case of advanced operator.
	*/
  virtual CATLONG32 Check() = 0;

  /**
    * @nodoc
	* To be called before the Run() method. Otherwise it is automatically started
	* by the Run() method.
	* Returns 0 if the computation has successed, a non null value otherwise.
  *     1 - unspecified error.
  *     2 - surfaces must be mergeable at their common coins.
	* Allows you to know the minimum value required to perform the concatenation.
	* If the specified tolerance is smaller that this value, the Run() method fails.
	* This value is the sum of the C0 concatenation parametric deviation
  * and of the C2 deformation.
	*/
  virtual CATLONG32 ComputeThresholdValue(double &oThreshold) = 0;

  /**
    * @nodoc
	* Allows you to access the maximum deformation resulting from the concatenation.
	* This deformation is the sum of the C0 parametric deviation concatenation 
  * and of the C2 deformation.
	*/
  virtual void GetDeformation(double &oDeformation) = 0;

  /**
    * @nodoc
	* Allows you to access the C0 parametric deviation that is necessarily 
  * to perform the C0 concatenation, before optimising the C0 surface up to C2.
  * This value is the first term of the threshold value.
  * the second one is the deformation to make it C2.
	*/
  virtual void GetParametricC0Deviation(double &parametricC0Deviation) = 0;

  /** 
  * @nodoc
  * In case of incomplete surface grid , define a preference for sub grid definition
  * ( to be used with advanced operator only )
  */
  virtual void SetPreference(
    CATFace *iReferenceFace,
    CATIsoParameter iIsoParameter) = 0;

  /** 
  * @nodoc
  * to prevent us from any shape optimisation
  */
  virtual void MakeNoShapeOptimization() = 0;

  /** 
  * @nodoc
  * to specify the expected continuity order ( 0 , 1 , 2 )
  * 1 is the default value for advanced operator
  * 2 is the default value for the standard operator
  */
  virtual void SetObjectiveContinuity(CATLONG32 iObjectiveContinuity) = 0;

  /** 
  * @nodoc
  * 0 for C 
  * 1 for G (default value)
  * ( to be use with advanced operator only )
  */
  virtual void SetKindOfContinuity(CATLONG32 iKindOfContinuity = 1) = 0;

  /** 
  * @nodoc
  * Set the max admissible angle ( in radian ) for face concatentation
  * Default value is 0.008726 redian ( = 0.5 degree )
  * ( to be use with advanced operator only )
  */
  virtual void SetMaxAngle(const CATAngle &iMaxAngle) = 0;

  /** 
  * @nodoc
  * Get the angle ( in radian ) for face concatentation
  * ( to be use with advanced operator only )
  */
  virtual void GetAngle(CATAngle &oAngle) = 0;

  /** 
  * @nodoc
  * Level of concatenation
  * = 0 : standard level
  * = 1 : enable to concatenate even in case of topological sharing of surface
  */
  virtual void SetConcatenationLevel(const int iConcatenationLevel) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopConcatenateSurOperator(); // -> delete can't be called
};

/**
* Creates a topological SurToNurbsSur operator :
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iShellBody
* The Shell which contains the faces iFaceCell1 and iFaceCell2.
* @param iFaceCell1
* The first face to concatenate.
* @param iFaceCell2
* The second face to concatenate.
* @return [out, IUnknown#Release]
* A pointer to the created operator. To be released with the <tt>Release</tt> method.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopConcatenateSurOperator *CATPGMCreateTopConcatenateSurOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iShellBody,
  CATCell *iFaceCell1,
  CATCell *iFaceCell2);

/**
* Creates a advanced topological SurToNurbsSur operator.
* This operator allows to concatenate several list of juxtaposed surfaces.
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iBodyToConcatenate
* The Body which contains all the faces lists to concatenate
* @param iNbFacesListToConcatenate
* The number of faces lists to concatenate ( size of array "iFacesListToConcatenate" ).
* @param iFacesListToConcatenate
* The array of faces lists to concatenate.
* @return [out, IUnknown#Release]
* A pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopConcatenateSurOperator *CATPGMCreateTopConcatenateSurOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBodyToConcatenate,
  const int iNbFacesListToConcatenate,
  CATLISTP(CATFace) *iFacesListToConcatenate);

#endif /* CATIPGMTopConcatenateSurOperator_h_ */
