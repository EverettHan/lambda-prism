#ifndef __CATTopSewSkin_h__
#define __CATTopSewSkin_h__

// COPYRIGHT DASSAULT SYSTEMES  2003

/**
 * @level Protected
 * @usage U1
 */

#include "ExportedByCATTopologicalObjects.h"
#include "CATCreateSewSkin.h"
#include "CATTopOperator.h"

#include "ListPOfCATEdge.h"
#include "CATListOfDouble.h"

#include "CATListOfCATCells.h"

#include "CATIAV5Level.h"
#include "CATIACGMLevel.h"

class CATCell;
class CATEdge;

/**
 * Interface representing the operator to sew a skin onto a body (solid or skin).
 * Sewing is a boolean operation combining a surface with a body. 
 * This capability adds or removes material by modifying the input body.
 * You can sew all types of surfaces onto bodies as long as there is no gap greater 
 * than the tolerance (default value 0.1) between the
 * bording edges of the surface to be sewn and the initial body. 
 * Either the borders of the surface must lay on
 * the body (gaps <= tolerance), or the surface must fully cross the body.
 * To use this operator:
 *<ul>
 * <li>Create it with the <tt>CATCreateSewSkin</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
 * <li>Run it
 * <li>Get the resulting GetResult method. If you do not want 
 * to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the 
 * geometric factory, after the operator deletion.
 *<li>delete it after use  with the usual C++ <tt>delete</tt> operator.
 *</ul> 
 */

class ExportedByCATTopologicalObjects CATTopSewSkin: public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopSewSkin);
   protected:

   /**
   * @nodoc
   * Constructor - not to be used.
   */
      CATTopSewSkin(CATGeoFactory * iFactory, CATTopData * iTopData);      


   /**
   * @nodoc
   * Constructor - not to be used.
   */
      CATTopSewSkin(CATGeoFactory * iFactory, CATTopData * iTopData, CATExtTopOperator * iExtensible); 


   public:
      /**
      * @nodoc
      * Destructor.
      */
      virtual ~CATTopSewSkin();
     /**
      * @nodoc
      */
      virtual CATBoolean GetCheckJournal()                   const  = 0;
      /**
      * @return
      * The selection side. 
      */
      virtual CATBoolean GetSelectionSide()                  const  = 0;

      /**
      * Checks whether a sewing operation onto a skin (skin/skin operation)
      * results in a closed skin.
      * @return
      * TRUE if the result is a closed shell, otherwise returns FALSE. 
      * Always returns TRUE when applied to a solid/skin operation. 
      */
      virtual CATBoolean ResultIsClosed()                           = 0; 
      /**
      * Retrieves the gaps between the bording edges of the skin to be
      * sewn and the input body.
      * @param ioEdges
      * The list of edges.
      * @param ioGaps
      * The associated list of gaps. 
      */                                        
      virtual void       GetEdgesAndGaps(CATLISTP(CATEdge)& ioEdges, CATListOfDouble& ioGaps) = 0 ;
      /**
      * @nodoc
      * Not to be used.
      */   
      virtual void       SetCheckJournal(CATBoolean iCheckMode)         = 0;
      /**
      * To be used to indicate the side where the material is to be added or kept.
      * Note that if the side is not properly specified, the sewing operation
      * onto a solid may produce an exception. 
      */
      virtual void       SetSelectionSide(CATBoolean iSameSkinSide)     = 0;
      /**
      * To be used to specify whether the simplification mode is to be applied.
      * Using this option (TRUE), if in the resulting solid there are connected
      * faces defined on the same geometric support (faces separated by smooth edges), 
      * these faces will be merged into one single face
      */
      virtual void       SetSimplificationMode(CATBoolean iSimplifMode) = 0;

      /**
      * To be used only when sewing a skin on a skin.
      * If set to FALSE, enable to follow the boundary of the skin to sew through the report.
      */
      virtual void       LogDeletionOnImmersedEdges(CATBoolean iLogDeletion = FALSE) = 0;
	  

      /**
      * To be used to set a tolerance for the Sewing.
	    * @param iTolerance
      * The input tolerance.
      */	  
	  virtual void       SetTolerance(double iTolerance) = 0;
	  
	    /**
      * To be used to map a free edge of the skin onto a cell of the body (edge or face),
	    * to avoid unnecessary calculations.
	    * @param iMappedFreeEdge
      * The free edge of the skin body that is mapped.
	    * @param iTargetCell
	    * The cell of the trimming body on which the edge is mapped. It can be a edge or a face.
      */	  
	  virtual void       SetEdgeMapping(CATEdge * iMappedFreeEdge, CATCell * iTargetCell) = 0;
	  
#ifdef CATIACGMV5R22
    /**
      * To be used to specify the operator if it is called in CATIA LiveShape Environment,
	    * to deal with the simlpification of LiveGroups.
	    * @param iLiveMode
      * The mode to specify
      */	  
    virtual void SetLiveMode(CATBoolean iLiveMode) = 0;
#endif

      /**
      * Runs the operator.
      */
      virtual int  Run() = 0;
      /**
      * @nodoc @nocgmitf
      */
      virtual void Dump(ostream & iOutStream) const = 0;
      /**
      * Returns the body resulting from the sewing operation.
      * @param ioJournal
      * The topological journal.
      * @return
      * The resulting body. 
      */
      virtual CATBody * GetResult(CATCGMJournalList * ioJournal) = 0;
};

#endif
