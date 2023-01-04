#ifndef CATSpaceDeformationSplitTool_H
#define CATSpaceDeformationSplitTool_H

// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CATDataType.h"
#include "CATGMOperatorsInterfaces.h"

#include "ListPOfCATCell.h"
#include "CATListOfCATICGMObjects.h"
#include "CATCGMStreamVersion.h"
#include "CATMathStream.h"
#include "CATBoolean.h"

class CATBody;
class CATGeoFactory;
class CATMathDirection;
class CATTopData;

//#define NewSplitMemory
/**
 * Class defining the topological definition of the map of a topological deformation.
 * <br>CATSpaceDeformationSplitTool retrieves the cells to be impacted by the deformntion.
 */
class ExportedByCATGMOperatorsInterfaces CATSpaceDeformationSplitTool
{
  public:



/**
 * Defines the cutting option.
 * @param iWithCutting
 * The cutting option.
 * <br><b>Legal values</b>: <tt>TRUE</tt> to allow the split of the input body to keep
 * good quality surfaces, <tt>FALSE</tt> otherwise.
 */
	virtual void SetCuttingMode(const CATBoolean iWithCutting) = 0;

/**
 * Defines the body to deform.
 * @param  iBodyToDeform
 * The pointer to the body to deform
 */
	virtual void SetBody(CATBody* iBodyToDeform) = 0;

/**
 * Defines the configuration.
 * @param iTopData
 * The pointer to the data defining the configuration.
 * @param iReport
 * The pointer to the journal.
 */
	virtual void SetTopData(CATTopData*  iTopData) = 0;

/**
 * Runs the computation of the impact.
 */
	virtual CATLONG32 Run() = 0;

/**
 * Returns the resulting body.
 * @return
 * The pointer to the created body, result of the operation.
 * or the Initial body if nothing is done.
 */
  virtual CATBody* GetResult() = 0;

/**
 * Returns the resulting body.
 * @return
 * A Boolean if true the result correspond with the input body, 
 * else the method Run() must be called before the method GetResult()
 */
	virtual CATBoolean GetIsDone() const = 0;

/**
 * Returns if the split tool accept WireFrame or not.
 * @return
 * A Boolean if true this splittool can be used with a wire
 */
	virtual CATBoolean GetWireFrameAccepted() const = 0;

  /** 
  * Get the Number of cluster.
  *
  * <br><b>Role</b>: In cases where multi maps are needed the impacted cells are in different cluster,
  * in order to know wich map must be used
  *
  *
  * @return
  *   The number of clusters defined in this area.
  *
  */
  virtual int GetClusterNumber() const = 0;

/**
 * Retrieves the list of the cells impacted by the deformation.
 * @param impactedCells
 * The list of pointers to the impacted cells.
 * @param iNumCluster
 * The cluster numero of impactedCells.
 */
	virtual void GetTheBodyPartToDeform(CATLISTP(CATCell)*& ioImpactedCells, const int iNumCluster = 1) const = 0;

/**
 * Retrieves the list of cells divide.
 * @param ioBreakingCells
 * The list of pointers to the cells where the body can be ripped.
 */
  virtual void GetBreakingCells(CATLISTP(CATCell)*& ioBreakingCells) const = 0;

  virtual void GetPrerequisiteObjects( CATLISTP(CATICGMObject)& olObjects)const = 0;

 ///**
 //* Get the cutting option.
 //* @return  The cutting option.
 //* <br><b>Legal values</b>: <tt>TRUE</tt> to allow the split of the input body to keep
 //* good quality surfaces, <tt>FALSE</tt> otherwise.
 //*/

	//virtual CATBoolean GetCuttingMode() const = 0;

  virtual CATBoolean CuttingIsNecessary() const = 0;

  /**
	*
	* <br><b>Tells if the object supports Stream or not</b>: 
	* @return
	* <br><b>Legal values</b>: <tt>TRUE</tt> if stream is implemented,
	* <tt>FALSE</tt> otherwise.
	* 
	*/
	virtual CATBoolean IsStreamable(const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible )const =0;

	
	virtual void Stream( CATMathStream& ioWriteStream )const  = 0;


  /**
   * Increments the reference count of the instance.
   */
   virtual void AddRef()=0;

  /**
   * Decrements the reference count of the instance.  When the counter reaches 0, the instance is deleted.
   */
   virtual void Release()=0;

  protected :
    	virtual ~CATSpaceDeformationSplitTool();

};

ExportedByCATGMOperatorsInterfaces CATSpaceDeformationSplitTool * CATCreateSpaceDeformationSplitTool(CATGeoFactory*    iFactory,
                                                                   CATTopData *iTopData );                   

#endif
