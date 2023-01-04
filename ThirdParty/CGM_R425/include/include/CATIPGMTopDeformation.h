#ifndef CATIPGMTopDeformation_h_
#define CATIPGMTopDeformation_h_

// COPYRIGHT DASSAULT SYSTEMES 2008

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATFDFGeoApplyType.h"
#include "ListPOfCATBody.h"

class CATApproxStrategy;
class CATBody;
class CATCGMJournalList;
class CATEdge;
class CATGeoFactory;
class CATSpaceDeformationMapDefine;
class CATSpaceDeformationTopoMap;
class CATLISTP(CATEdge);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopDeformation;

/**
 * Class defining the operator that deforms a body according to a given
 * map.
 * <br>The map is the way to define the deformation and is created
 * by running an operator such as @href CATBumpDefine .
 * The CATIPGMTopDeformation operator follows the global frame of the topological operators 
 * and satisfies the smart mechanism: 
 * the input body is not modified. A new resulting body is created, 
 * possibly sharing data with the input body.
 *<ul>
 * <li>A CATIPGMTopDeformation operator is created with the <tt>CATPGMCreateTopDeformation</tt> global method:
 * It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
 *<li>Options can be precised, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopDeformation: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopDeformation();

  /** 
	* Choose a specific algorithm of aproximation.
	*
	* @param iType [in]
	*   The kind of approximation choosen.
	*
	*/
  virtual void SetGeometricalApply(const CATFDFGeoApplyType iType) = 0;

  /**
	 * Sets options on the approximation process.
	 * Optional method.
	 */
  virtual void SetApproxStrategy(CATApproxStrategy *approxStrategy) = 0;

   /** 
	 *  @nodoc
	 *  en etat de proto . A utiliser  uniquement  en interne 
     */
  virtual int SetSubBodiesToMove(CATBody * iBodyToMove, const CATBoolean isFixed=FALSE) =0;

  /**
   * Defines whether the resulting body must be freeze or not.
   * @param iFreezeMode
   * The freeze mode.
   */
  virtual void SetFreezeMode(CATBodyFreezeMode iFreezeMode) = 0;

  /** 
	* Allow to turn off the ProgressBar Management
	* <br><b>Role</b>: By default this operator manage the current progress Bar 
	*<li> this can lead to conflicts with other management of the progress Bar.
	*<li> this methode is a way to solve the conflict.
	*
	* @param iProgBarIsAuthorized [in]
	*   TRUE : The ProgressBar management is turn ON.
	*   FALSE: The ProgressBar management is turn OFF.
	*/
  virtual void SetProgressBarAuthorized(CATBoolean iProgBarIsAuthorized) = 0;

  /**
  * 
  * <br><b>Role</b>: Define if a warning must be generated if some gap upper than resolution are created inside edges .
  * by default, no warning are generated.
  *
  */
  virtual void SetWarningForNewGap() = 0;

  /**
   * Retrieves the G0 continuity diagnosis for a given edge.
   * The edges have to belong to one of the deformed faces.
   * @param iE
   * The pointer to the edge to test.
   * @param ioG0Error
   * The value of the maximum G0 deviation along the edge.
   * @return
   * -1 if the edge has not been impacted by the deformation
   */
  virtual int G0MaxError(
    CATEdge *iE,
    double &ioG0Error,
    const CATBoolean isAfterDeformation = TRUE) const = 0;

  /**
   * Retrieves the G1 continuity diagnosis for a given edge.
   * The edges have to belong to one of the deformed faces.
   * @param iE
   * The pointer to the edge to test.
   * @param ioG0Error
   * The value of the maximum G0 deviation along the edge.
   * @return
   * -1 if the edge has not been impacted by the deformation
   */
  virtual int G1MaxError(
    CATEdge *iE,
    double &ioG1Error,
    const CATBoolean isAfterDeformation = TRUE) const = 0;

  /**
 * This method can be called  after the deformation
 * It returns the list of the edges with remaining G0 
 * continuity default relativly to the tolerance.
 * @param ioListOfEdges
 * The list of the pointers to the Edges that have been oppened by the operator.
 * @return
**/
  virtual int GetOpenEdges(CATLISTP(CATEdge) &ioListOfEdges) = 0;

  /**
 * This method after deformation
 * It returns the list of the "G1-edges" with remaining G1 
 * continuity default relativly to the tolerance.
 * The "G1-edges" are the wiche are G1 before the deformation and must 
 * keep this continuity relatively to the MapDefine.
 * @param ioListOfEdges
 * The list of the pointers to the Edges that have not been corrected.
 * @return
**/
  virtual int GetSharpEdges(CATLISTP(CATEdge) &ioListOfEdges) = 0;

/** 
  * @nodoc
  * en etat de proto.  A utiliser uniquement  en interne 
  */
  virtual CATLISTP(CATBody) GetNotKeptRigidZones(
    CATCGMJournalList *ioReport = NULL) = 0;

/** 
  * @nodoc
  * en etat de proto.  A utiliser uniquement  en interne 
  */
  virtual CATLISTP(CATBody) GetRigidZonesWithSmoothCommonEdges(
    CATCGMJournalList *ioReport = NULL) = 0;


  /** 
  * @nodoc
  * en etat de proto.  A  utiliser uniquement  pour les tests  
  */
   virtual void *  GetImplForTests()=0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopDeformation(); // -> delete can't be called
};

/**
 * Creates the operator that deforms a body according to a given map.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iTopData
 * The pointer to the data defining the configuration.
 * @param iMapDefine
 * The pointer to the map definition to apply.
 * @param iBodyToBeDeformed
 * The pointer to the body to deform. As the operator follows the smart mechnanism, 
 * this input body is not modified. A new one is created, et can be retrieved with 
 * the <tt>GetResult</tt> method.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopDeformation *CATPGMCreateTopDeformation(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATSpaceDeformationMapDefine *iMapDefine,
  CATBody *iBodyToBeDeformed);


/**
 * Creates the operator that deforms a body according to a given map.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iTopData
 * The pointer to the data defining the configuration.
 * @param iMapDefine
 * The pointer to the map definition to apply.
 * @param iBodyToBeDeformed
 * The pointer to the body to deform. As the operator follows the smart mechnanism, 
 * this input body is not modified. A new one is created, et can be retrieved with 
 * the <tt>GetResult</tt> method.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopDeformation *CATPGMCreateTopDeformation(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATSpaceDeformationTopoMap*     iMap,
  CATBody *iBodyToBeDeformed);


#endif /* CATIPGMTopDeformation_h_ */
