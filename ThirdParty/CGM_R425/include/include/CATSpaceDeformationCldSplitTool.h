#ifndef CATSpaceDeformationCldSplitTool_H
#define CATSpaceDeformationCldSplitTool_H

// COPYRIGHT DASSAULT SYSTEMES 2007

#include "CATBoolean.h"
#include "CATListOfInt.h"
#include "CATListOfCATCldCells.h"
#include "CATIAV5Level.h"

class CATCldBody;
class CATCldCell;
class CATIPolySurface;
class CATSoftwareConfiguration;


#if defined CATIAV5R20 || defined CATIAR208
#define SPLITMigration_CLD_TO_PolyMeshAPI
#endif
//#define  SPLITMigration_CLD_TO_PolyMeshAPI


/**
 * Class defining the cloud definition of the map deformation.
 * This class is used by the @href CATTopSimulation class.
 * It answers to the question : What is morphed ? What is freezed ?
 * <br>
 * Warning : There is not implementation of this class at the Topological Level
 * </ul>
 */

class  CATSpaceDeformationCldSplitTool
{      
  public:

    virtual ~CATSpaceDeformationCldSplitTool(){};

#ifdef  SPLITMigration_CLD_TO_PolyMeshAPI

  /**
 * Defines the PolySurface to deform.
 * @param  iSurfaceToDeform
 * The pointer to the cloud body to deform
 */
    virtual void SetPolySurface(CATIPolySurface* iSurfaceToDeform) {};// A REmplacer par= 0;
 /**
 * @deprecated
 * // A VIRER
 */
    virtual void SetCldBody(CATCldBody* iBodyToDeform) {}; // A Virer


#else
/**
 * Defines the cldbody to deform.
 * @param  iBodyToDeform
 * The pointer to the cloud body to deform
 */
	virtual void SetCldBody(CATCldBody* iBodyToDeform) = 0;
#endif

/**
 * Defines the configuration.
 * @param iConfig
 * The pointer to the data defining the configuration.
 */
	virtual void SetSoftwareConfiguration(CATSoftwareConfiguration* iConfig) = 0;

/**
 * Runs the computation of the impact.
 */
	virtual int Run() = 0;

#ifdef  SPLITMigration_CLD_TO_PolyMeshAPI

  /** 
  * Get the splitted Surface
  *
  * @return
  *   return the splitted Surface
  *
  */
  virtual CATIPolySurface* GetSplitedSurface() const {return 0;} // A Remplacer par = 0;


 /**
 * @deprecated
 */
  virtual CATCldBody* GetResult() const {return 0;} // A VIRER

#else
  /**
 * Returns the resulting body.
 * @return
 * The pointer to the created body, result of the operation.
 * or the Initial body if nothing is done.
 */
  virtual CATCldBody* GetResult() const = 0;

#endif



/**
 * Returns if the deformation is done.
 * @return
 * A Boolean if true the result correspond with the input body, 
 * else the method Run() must be called before the method GetResult()
 */
	virtual CATBoolean GetIsDone() const = 0;


#ifdef  SPLITMigration_CLD_TO_PolyMeshAPI
   /** 
	* @nodoc
	* @deprecated
	*/
  virtual void GetTheBodyPartToDeform(CATLISTP(CATCldCell)& oImpactedCells) const {}; // A VIRER


	/** 
	* @nodoc
	* @deprecated
	*/
  virtual int GetTheCldPartToDeform(CATCldCell* iCldCell, CATListOfInt& ioImpactedVerticiesIndexes) const {return 0;} // A VIRER


#else

  /** 
	* @nodoc
	* @deprecated
	*/
	virtual void GetTheBodyPartToDeform(CATLISTP(CATCldCell)& oImpactedCells) const = 0;


	/** 
	* @nodoc
	* @deprecated
	*/
	virtual int GetTheCldPartToDeform(CATCldCell* iCldCell, CATListOfInt& ioImpactedVerticiesIndexes) const = 0;

#endif


  /** 
	* Retrieves the list of verticies impacted by the deformation.
	*
	* <br><b>Role</b>: Define the verticies to deform.
	* @param oImpactedVerticiesIndexes [inout]
	*   The list of indexes of the impacted verticies.
	* @return
	*   0 : All is OK
  *   >0 : an error has occured.
	*
	*/
	virtual int GetTheCldPartToDeform(CATListOfInt& oImpactedVerticiesIndexes) const = 0;

};
#endif


