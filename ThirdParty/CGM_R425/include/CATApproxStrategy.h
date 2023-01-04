#ifndef CATApproxStrategy_H
#define CATApproxStrategy_H
//=========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//=========================================================================
// CATApproxStategy
/**
* @level Protected
* @usage U3
*/ 


#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"


//=======================================================================
// Class Definition 
//=======================================================================
/**
* Class represent a strategy for powerdef approximation.
* <br><b>Role</b>: A useful class to define some elements in the Approximation Stategy.
* @example
* <br> CATTopDeformation * DeformationOpe = xxx;
* <br> //.....
* <br> pObject = CATCreateApproxStrategy(8, 64, FALSE, FALSE);
* <br> DeformationOpe->SetApproxStrategy(pObject);
* <br> //....
* <br> DeformationOpe->Run();
* <br> //....
* <br> delete DeformationOpe;
* <br> DeformationOpe = NULL;
* <br> delete pObject;
* <br> pObject = NULL;
*
* @see @href CATTopDeformation
*
* <p> In some define operator, an advice strategy is sugested see @href  CATVectorFieldDefine#GetAdviceStrategy
*/
class ExportedByCATGMOperatorsInterfaces CATApproxStrategy
{
  public :

	virtual ~CATApproxStrategy();




	/** 
	* Internal Tolerances management.
	*
	* <br><b>Role</b>: Define the objectives accuracies.
	*
	* @param oTolG0 [out]
	*   The internal G0 accuracy. (the accuracy o the boundaries can not be modified)
	* @param oTolG1 [out]
	*   The internal G1 accuracy.
	* @param oTolG2 [out]
	*   The internal G2 accuracy.
	*
	*/
	virtual void Tolerances(double & oTolG0, double & oTolG1, double & oTolG2) const=0;

/*
 
*/
	/** 
	* Keep or not Keep the initial parametrization.
	* <br><b>Role</b>: Say if the paramtetrization have to be keen unchanged
	*
	* @return
	*   TRUE : The output paramtetrization must be the input one.
	* <br>  FALSE : The output is free,
	*
	*/
	virtual CATBoolean KeepParametrization() const =0;


/** 
  * Keep or not Keep the initial geometry degree.
	* <br><b>Role</b>: Say if we have to Keep the same degree than initial geometry.
	*
	*
	* @return
	*   TRUE : The result must keep the same degree than the input (if possible)
	* <br>  FALSE : The result's degree is free.
	*/
	virtual CATBoolean KeepDegree() const=0;


	/** 
	 * Keep or not Keep the initial geometry segmentation.
	* <br><b>Role</b>: Get if we have to keep the same segmentation
	*
	* @return
	*   TRUE : The result must keep the same segmentation than the input (if possible)
	* <br>  FALSE : The result's segmentation is free.
	*/
	virtual CATBoolean KeepSegmentation()const =0;

/*
	Get if it is better to increase degree than increase the segmentation
*/
	virtual CATBoolean IncreaseDegreeBeforeSegmentation()const =0;


  /** 
  * Get the max degree wich can be used in approximation.
  *
  * <br><b>Role</b>: Define the maximum degree than can be used in approximation.
	* <p> <b>Limiataion</b>: if the inial geometry have an upper degree, this methode have 
	*  no effect on the asociated output geometry.
	*
  * @return
  *   The maximum degree.
  */
  virtual CATLONG32 GetMaxDegree() const = 0;


	/** 
  * Get the max segmentation wich can be used in approximation.
  *
  * <br><b>Role</b>: Define the maximum segmentation than can be used in approximation.
	* <p> <b>Limiataion</b>: 
	* <li> If the inial geometry have more segmentation , this methode have 
	*       no effect on the asociated output geometry.
	* <li> If the inial geometry is only C1 , the max segmentation value is another one (see #GetMaxSegmentation_C1).
	*
  * @return
  *   The maximum number of span.
  */
  virtual CATLONG32 GetMaxSegmentation() const = 0;


  /** 
  * Get the max segmentation for C1 cases.
  *
  * <br><b>Role</b>: Get the max segmentation wich can be used in approximation
	*  in the specific case where the initial geometry is only C1
	*  default is 2 time the max segmentation (see #GetMaxSegmentation )
  *
  * @return
  *   The maximum number of span.
  *
  */
  virtual CATLONG32 GetMaxSegmentation_C1() const = 0;

/*
	Get the max segmentation wich can be used in approximation
	in the case where the initial surface is only C1
*/
//  virtual int SetMaxSegmentation_C1(const int iMaxSegmentation_C1) = 0;
};

/** 
* Create a strategy objet.
*
* <br><b>Role</b>: Allow to define some parameter for the approximation.
*
* @param iMaxDegree [in]
*   The maximum degree authorised in the approximation.
* @param iMaxNumberOfSpan [in]
*   The maximum number of span authorised in the approximation.
* @param iKeepDegree [in]
*   if it is true, the output geometry must have the seme degree than the input one.
* @param iKeepSegmentation [in]
*   if it is true, the output geometry must have the seme segmentation than the input one.
* @param iTolG0 [in]
*   Internal G0 tolerance fr the approximation.
* @param iTolG1 [in]
*   Internal G1 tolerance fr the approximation. (Not implemented)
* @param iTolG2 [in]
*   Internal G2 tolerance fr the approximation. (Not implemented)
* @param iKeepParametrization [in]
*   If it is true, the output geometry must have the seme parametrization than the input one.
* @param iIncreaseDegreeBefSeg [in]
*   If it is true, the algorith must try to increase the degree before the segmentation. (Not implemented)
*
* @return
*   Explain return values
*
*/
ExportedByCATGMOperatorsInterfaces CATApproxStrategy * CATCreateApproxStrategy(
																					const CATLONG32 iMaxDegree,
																					const CATLONG32 iMaxNumberOfSpan,
																					const CATBoolean iKeepDegree,
																					const CATBoolean iKeepSegmentation,
																					const double iTolG0 = 0.1,
																					const double iTolG1 = 1.,
																					const double iTolG2 = 1.,
																					const CATBoolean iKeepParametrization = 1,
																					const CATBoolean iIncreaseDegreeBefSeg = 0); 
#endif


