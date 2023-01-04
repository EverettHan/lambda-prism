#ifndef CATIPGMBodyDatumiser_h_
#define CATIPGMBodyDatumiser_h_

// COPYRIGHT DASSAULT SYSTEMES 2006
#include "CATIACGMLevel.h"

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"
#ifdef CATIACGMR216CAA
#include "CATBodyDatumiserCheckStatus.h"
#endif

class CATCGMJournalList;
class CATLISTP_CATCGMGeometryOfFatAble_;
class CATMathTransformation;
class CATCGMHashTable;
class CATLISTP(CATCGMGeometryOfFatAble);

/**
 * @level Protected
 * @usage U1
 */

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMBodyDatumiser;
/**
 * Class which defines an operator to copy bodies from one container
 * to another or within the same container. <br>
 * This operator provides you with a way to remove the useless geometries
 * from the topology definition. When copying a body, the usefull geometry is context dependent.
 * Depending on whether a vertex is used as the corner of a solid or is used as an isolated point,
 * the geometry required by its definition is not the same. Copying vertices belonging to a solid or volume
 * to isolated vertices can lead to undesirable model size if the useless underlying geometries are not
 * cleaned during the duplication process. Useless geometries resulting from a duplication process
 * are called "fat geometries". It is recommended to get rid of them by using the appropriate options
 * of CATIPGMBodyDatumiser.<br>
 * The CATIPGMBodyDatumiser simplifies the following topologies:
 * <ol>
 * <li>Vertices defined as VertexInVolume. The underlying geomtry must be a MacroPoint with a single
 * Cartesian point.
 * <li>The support of vertices or edges which have been created by a "laydown" operation and are no longer required
 * in the definition of copied objects (the surfaces are cleaned).
 * <li>The edges which are only used in a wire body (underlying CATEdgeCurve/CATPCurve are simplified and 
 * replaced with CATEdgeCurve/CATCurve(3D curve).
 * </ol>
 */
class ExportedByCATGMModelInterfaces CATIPGMBodyDatumiser: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMBodyDatumiser();

  /**
	* @nodoc
	* Requires the creation of a topological journal. If not called, GetDatumResult does not
	* return any journal.
	*/
  virtual void AskDedicatedJournalList() = 0;
 
    /**
	* @nodoc
	* Retrieves the copied body created by the operator as well as the operation journal.
	* @param ioDatumBody
	* The copied body. If no simplification has been performed, the copied body is the same as
	* the input body.
	* @param iNumBody
	* The number of bodies to be copied. 
	* <ul>
	* <li>1 for a single body treatment
	* <li>the number of bodies to be treated for a multi-body treatment.
	* <pre>
	* int  nbBody = iInputBodies.Size(); 
	* CATListOfInt  ComputedSimplified;
	* CATLISTP(CATBody)  iOutputBodies;
	* for  (  int  numBody=1;  numBody<=nbBody;    numBody++  )  
    *    {  
    *        CATBody  *iBody  =  iInputBodies[numBody]; 
    *        CATBody  *oBody  =  NULL;                 
    *        CATCGMJournalList  *journal  =  NULL;            
	*		 short computedSimplified  =  bodyDatumiser->GetDatumResult(&oBody, numBody, &journal);  
    *        ComputedSimplified.Append(computedSimplified);  
    *        iOutputBodies.Append(oBody);  
	*		...
	*	 }
    * </pre>
	* </ul>
	* @param ioJournal
	* The topological journal.
	* @param ioOutputMapping
	* The list of output objects associated with the list of input objects specified in <tt>CATPGMCreateBodyDatumiser</tt>
	* (optional argument). The topological journal is a restricted way to retrieve the relationship between the input and output
	* bodies. However it does not allow you to establish the correspondence between internal cells or geometry
	* as they are not reported in the journal.
	* @return 
	* A simplification indicator:
	* <ul>
	* <li>0: no simplification (ioDatumBody is equivalent to the input body)
	* <li>1: ioDatumBody is a new body.
	* </ul>
	*/
  virtual short GetDatumResult(
    CATBody **ioDatumBody = NULL,
    const int iNumBody = 1,
    CATCGMJournalList **ioJournal = NULL,
    CATLISTP(CATICGMObject) *ioOutputMapping = NULL) = 0;

    /**
	* @nodoc
	* INTERNAL USE.<br>
	* Returns the number of "fat geometries".
	* "Fat geometries" are geometries which are not required for the definition of the topology. <br>
	* Example: a vertex representing the corner of a cube is defined with three underlying POECs. All this geometry
	* is "fat" if the vertex is to be copied independently of the cube context (a vertex can be defined
	* by a single cartesian point). If you need to copy such input vertices from a solid, it is better to remove
	* the useless geometry and simplify the definition of these vertices. This is sometimes a good way to minimize the
	* model size.
	* @return
	* The number of copied objects (vertices, edges...) which are initially too "fat".
	*/
  virtual CATLONG32 GetNumberOfFatGeometry() = 0;
   
   /**
	* @nodoc
	* INTERNAL USE.<br>
	* Returns the list of "fat geometries".
	* "Fat geometries" are geometries which are not required for the definition of the topology. <br>
	* Example: a vertex representing the corner of a cube is defined with three underlying POECs. All this geometry
	* is "fat" if the vertex is to be copied independently of the cube context (a vertex can be defined
	* by a single cartesian point). If you need to copy such input vertices from a solid, it is better to remove
	* the useless geometry and simplify the definition of these vertices. This can be a way to minimize the
	* model size.<br>
	* The returned list contains the copied objects of the initial "fat" objects. These objects are "light"
	* objects but their origin is "fat".
	* @param ioppGeomsNotFatStatusButFatSymptoms
	* Internal use.
	* @return 
	* The list of copied objects which have a "fat" origin. The CATCell can be retrieved by using the
	* <tt>CATCGMGeometryOfFatAble::GetCell</tt> method.
	*/
  virtual CATLONG32 GetNbInputBodies() = 0;

  virtual const CATLISTP(CATCGMGeometryOfFatAble) *GetFatGeometries(
    CATLISTP(CATCGMGeometryOfFatAble) **ioppGeomsNotFatStatusButFatSymptoms = NULL) = 0;

  /**
	* @nodoc
	* INTERNAL USE.<br>
    * Specifies the duplication of the body with a transformation. Provides
	* you with the same capability as CATTransfoManager. If the specified transformation
	* is the Identity matrix, the capability is equivalent to CATCloneManager.
	* <pre>
	* CATMathTransformation Identity;
    * CATMathTransformation Translation(CATMathVector(100,200,300));
    * ...
	* CATIPGMBodyDatumiser * BodyDatumiser = CATPGMCreateBodyDatumiser( NewFactory , InputBody[i] , *TopData );
    * BodyDatumiser->SetFullDuplicate(&Translation);
    * </pre>
	* @param iTransfo
	* The CATMathTransformation to be performed through the duplication process.
	*/
  virtual void SetFullDuplicate(const CATMathTransformation *iTransfo) = 0;

   /**
	* @nodoc
	* INTERNAL USE.
	*/
  virtual void SetLyingOnAsUseful() = 0;

#ifdef CATIACGMR216CAA
  /**
  * @nodoc
  * INTERNAL USE.<br>
  * Try to Estimate if the import may be successfull just before computing the run process
  *  CATBodyDatumiserCheckStatus_Undefined     : only for initialization;
  *  CATBodyDatumiserCheckStatus_CheckError    : obvious
  *  CATBodyDatumiserCheckStatus_EmptyResult   : no expected solution
  *  CATBodyDatumiserCheckStatus_MayBeClipped  : obvious    
  *  CATBodyDatumiserCheckStatus_FullResult    : no clipping will be done after effective import 
  *  CATBodyDatumiserCheckStatus_NoCheck       : no check done (input scale and output scale are equal ) 
  */
  virtual CATBodyDatumiserCheckStatus EstimateImportCapability() = 0;

#endif
  //=======================================================================================
  // volatile usage on local Optimisation analysis with scope context
  //  for delayed optimisation , more precise analysis of targetted optimisation  
  //             Poec/Pos detection is delayed if their support are still usefull
  //               (from strong link of Edge/Face defined in the context) 
  //             even if no explicit topological usage [ Cell(Edge,) or Subd(LyingOn)) ]
  //=======================================================================================
  virtual CATCGMHashTable *GetUseFullSupport() const = 0;

  /**
	* @nodoc
	* Specifies the duplication of a given type of objects.
	* <pre>
	* CATIPGMBodyDatumiser  *  pBodyDatumiser  =  CATPGMCreateBodyDatumiser(piNewGeomFactory, bodytobecopied,  *topdata )
	* pFactoryDatumiser->SetTargetGeometricType(CATEdgeType); 
	* </pre>
	* @param iTargetType
	* The type of object to be copied.
	*/
  virtual void SetTargetGeometricType(CATGeometricType iTargetType) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMBodyDatumiser(); // -> delete can't be called
};

/**
  * @nodoc
  * Creates an operator to copy a single body within a given container or to copy a single body from 
  * one container to another container.
  * @param iFactory
  * The pointer to the initial factory.
  * @param iInputBody
  * The body to be copied.
  * @param iTopData
  * The pointer to the data defining the software configuration and the journal. 
  * @param iInputMapping
  * The list of object for which a mapping is required.
  * @return [out, IUnknown#Release]
  * The CATIPGMBodyDatumiser operator.
 */
ExportedByCATGMModelInterfaces CATIPGMBodyDatumiser *CATPGMCreateBodyDatumiser(
  CATGeoFactory *iFactory,
  CATBody *iInputBody,
  const CATTopData &iTopData,
  const CATLISTP(CATICGMObject) *iInputMapping = NULL);

/**
  * @nodoc
  * Creates an operator to copy a list of bodies within a given container or to copy a list of bodies from 
  * one container to another container.
  * @param iFactory
  * The pointer to the initial factory.
  * @param iInputBodies
  * The list of bodies to be copied.
  * @param iTopData
  * The pointer to the data defining the software configuration and the journal. 
  * @param iInputMapping
  * The list of object for which a mapping is required.
  * @return [out, IUnknown#Release]
  * The CATIPGMBodyDatumiser operator.
 */
ExportedByCATGMModelInterfaces CATIPGMBodyDatumiser *CATPGMCreateBodyDatumiser(
  CATGeoFactory *iFactory,
  const CATLISTP(CATBody) &iInputBodies,
  const CATTopData &iTopData,
  const CATLISTP(CATICGMObject) *iInputMapping = NULL);

/**
  * @nodoc
  * INTERNAL USE (dedicated to factory cleaner).
  * Creates an operator to copy a list of bodies within a given container or to copy a list of bodies from 
  * one container to another container.
  * @param iFactory
  * The pointer to the initial factory.
  * @param iTopData
  * The pointer to the data defining the software configuration and the journal. 
  * @return [out, IUnknown#Release]
  * The CATIPGMBodyDatumiser operator.
 */
ExportedByCATGMModelInterfaces CATIPGMBodyDatumiser *CATPGMCreateFactoryDatumiser(
  CATGeoFactory *iFactory,
  const CATTopData &iTopData);

#endif /* CATIPGMBodyDatumiser_h_ */
