#ifndef CATTopHiddenSeamCellManager_H
#define	CATTopHiddenSeamCellManager_H
// COPYRIGHT DASSAULT SYSTEMES  2009
//===========================================================================  
//  Class  CATTopHiddenSeamCellManager  
//---------------------------------------------------------------------------  
//
//  Class to propagate Hidden Seam Cells after the execution of a topological operator.
//
//  If a cell is considered as a Hidden Seam Cell, then an attribute 
//  is created on this cell. The attribute represents a paire of incident
//  cells, in the context of the body.  
//  If the input body has hidden seam cells hence the CATTopHiddenSeamCellManager
//  has to propagate these information in the output body.
//  This is done through the Cell Tracker which rely on TYopological Journal of 
//  the Operator
//  
//===========================================================================   
#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "CATListOfCATCells.h"
#include "CATMathInline.h"
#include "ListPOfCATBody.h"
#include "ListVOfLong.h"
#include "CATErrorDefs.h"
#include "CATBody.h"
#include "CATCGMJournal.h"
#include "CATListOfCATCGMJournals.h"
#include "CATCollec.h"
#include "CATTopCGMAttributeLabel.h"
#include "CATTopCGMAttributeManager.h"


class CATTopCGMAttributeManager;
class CATTopData;
class CATEdgeCurve;
class CATCurve;
class CATCell;
class CATDomain;
class CATTopOperator;
class CATCGMCellTrackerImp;
class CATCGMOutput;
class CATCGMJournal;
class CATCGMJournalList;
class CATCGMJournalItem;
class CATSoftwareConfiguration;
class CATCellHashTable;
class CATCGMHashTableWithAssoc;
class CATLISTP(CATCurve);
class CATLISTP(CATCGMJournal);
class CATTopCellWithCGMAttribute;
class CATLISTP(CATTopCellWithCGMAttribute);
class CATTopHashTableOfCellWithCGMAttributesState;


/** @nodoc @nocgmitf */
/**
* Class to analyze and propagate Hiden Seam attribute from input bodies to output bodies through CGM Journals.
* Class to propagate CGM Attributes after the execution of a topological operator.
*
* A CATTopHiddenSeamCellManager allow propagation of CGM Attributes from input bodies 
* to output bodies.
*
* If an origin cell own a Hidden Seam Attribute, then under given conditions 
* (driven by Kind and specificity of the Hidden Seam Attribute)
* the target cell will own a Hidden Seam Attribute.

* The Cell Tracker which relies on CGM Journal of the Operator, is used 
* to match pertinent output cells with input cells.
* 
*<ul>
* <li>A CATTopHiddenSeamCellManager object is created with the <tt>CreateCATTopHiddenSeamCellManager</tt> 
* global function. It must be directly deleted with the <tt>delete</tt> operator. It is not streamable. 
* <li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method.
*</ul>
*/

/** @nodoc @nocgmitf */
class ExportedByCATTopologicalObjects CATTopHiddenSeamCellManager
{
public:
   
	/** @nodoc @nocgmitf */
   /** 
   * Method to create a CATTopHiddenSeamCellManager without the context of a CATTopOperator
   *
   * <br><b>Role</b>: Method to create a CATTopHiddenSeamCellManager without the context of a CATTopOperator
   *
	* @param piSoftConfig 
	* a pointer to a SoftwareConfigucration
	*
	* @param iListOfInputBody 
	* list of input bodies from where resulte bodies have been built.
	*
	* @param iListOfOutputBody
	* list of output bodies that have been built rom input bodies.
	*
	* @param piListOfCGMJournal 
	* list of CGM Journals that describe how output bodies have been built from input bodies.
	*
	*/
   //static CATTopHiddenSeamCellManager *CreateCATTopHiddenSeamCellManager(CATSoftwareConfiguration *piSC, ListPOfCATBody& iListOfInputBody, ListPOfCATBody& iListOfOutputBody, CATLISTP(CATCGMJournal)& iListOfCGMJournal);

	/** @nodoc @nocgmitf */
	/**
	* Method to create a CATTopHiddenSeamCellManager with the context of a CATTopOperator
	*
	* <br><b>Role</b>: Method to create a CATTopHiddenSeamCellManager with the context of a CATTopOperator
	*
	* @param iHiddenSeamCriterion 
	* Criterion taking into account in decision of assign a Hidden Seam attribute to candidate cells
	*
	*/
   //static CATTopHiddenSeamCellManager *CreateCATTopHiddenSeamCellManager(CATTopOperator *piTopOperator)//CATTopHiddenSeamCriterion iHiddenSeamCriterion=CATTopHiddenSeamCriterion_GeometricSupport);

	/** @nodoc @nocgmitf */
   /** 
   * Dtor  
   */
   ~CATTopHiddenSeamCellManager();	

	/** @nodoc @nocgmitf */
	/**
	* 
	*
	* @param iDimCell
	*.
	*
	* @param iListOfIDAttr
	* 
	* @return
	*
	*/
	static CATBoolean PropagateCGMAttribute(CATTopCGMAttributePropagateOption& iAttributePropagateOption, CATCell *piDestCell, CATBody *piOutputBody, CATCellHashTable *piHashTableOfCellsOfOutputBody, 
                                          CATLISTP(CATTopCellWithCGMAttribute) &iListOfCellWithCGMAttributes, CATTopHashTableOfCellWithCGMAttributesState *pioHashTab_OutputFacesWithCGMAttributesState, 
                                          CATTopHashTableOfCellWithCGMAttributesState *pioHashTab_OutputEdgesWithCGMAttributesState,
														CATTopHashTableOfCellWithCGMAttributesState *pioHashTab_OutputVerticesWithCGMAttributesState);

	/** @nodoc @nocgmitf */
	/**
	* Dump CGM Attributes of all input and output bodies
	*
	* @param ios 
	* the stream through where information are dumped.
	*
	* @param piCell
	* the Cell on which CGM attribute carried by
	* will be dumped
	*
	* @param piBody
	* the Body to which the Cell belongs
	*
	*/
	static void Dump(CATCGMOutput& os, CATCell *piCell, CATBody *piBody = NULL);

   /** @nodoc @nocgmitf */
	/**
   * Retrieve all paires of incident cells that are stored by the Hidden Seam attribute owned by <tt>iHiddenCell</tt>
   * 
   * <br><b>Role</b>: Retrieve all paires of incident cells that are stored by the Hidden Seam attribute owned by 
	* <tt>iHiddenCell</tt>. if {(IncidCell_1,IncidCell_2)k}k are theoretically the set of paires of Incid Cells
	* The method get back all first Incident Cells (IncidCell_1)k in the list oListIncidCell1 and all(IncidCell_2)k
   * in the list oListIncidCell2
	*
	* @param piHiddenCell
	* the cell that will be analyzed
	*
	* @param oListIncidCell1
	* Output list that will contain Incident cells 
	*
	* @param oListIncidCell2
	* Output list that will contain Incident cells 
	*
   */
   static void GetIncidCellsOfHiddenSeamCell(CATCell* piHiddenCell,CATLISTP(CATCell) &oListIncidCell1,CATLISTP(CATCell) &oListIncidCell2);

	/** @nodoc @nocgmitf */
	/** 
   * Internal Use : Check if a given Cell has a Hidden Seam attribute in the context of the hash table of cells 
	* of a body
	*
   * <br><b>Role</b>: Check if a given Cell has a Hidden Seam attribute in the context of the hash table of cells 
	* of a body
	*
	* @param piCellHashTabOfBody
	*	the Hash Table of Cells of a body
	*
	* @param piHiddenCell
	*	the under scope cell
	*
	* @return
	* <dl>
	* <dt><tt>TRUE</tt>     <dd>if the Cell has a Hidden Seam attribute in the given contexte
	* <dt><tt>FALSE</tt>    <dd>otherwise
	* </dl>
	*
   */
   static CATBoolean IsHiddenSeamCell(CATCell* piCell, CATCellHashTable *piCellHashTabOfBody);

	/** @nodoc @nocgmitf */
	/** 
	* Internal Use : Check if a given Cell has a Hidden Seam attribute in the context of the hash table of cells 
	* of a body
	*
	* <br><b>Role</b>: Check if a given Cell has a Hidden Seam attribute in the context of the hash table of cells 
	* of a body
	*
	* @param piCellHashTabOfBody
	*	the Hash Table of Cells of a body
	*
	* @param piHiddenCell
	*	the under scope cell
	*
	* @return
	* <dl>
	* <dt><tt>TRUE</tt>     <dd>if the Cell has a Hidden Seam attribute in the given contexte
	* <dt><tt>FALSE</tt>    <dd>otherwise
	* </dl>
	*
	*/
	static void IsHiddenSeamCell(CATCell* piCell, CATCellHashTable *piCellHashTabOfBody,CATCGMAttribute *&pioCGMAttribute);


	/** @nodoc @nocgmitf */
	/** 
	* Internal Use : Check if a given Cell has a Hidden Seam attribute in the context of the hash table of cells 
	* of a body
	*
	* <br><b>Role</b>: Check if a given Cell has a Hidden Seam attribute in the context of the hash table of cells 
	* of a body
	*
	* @param piHiddenCell
	*	the under scope cell
	*
	* @return
	* <dl>
	* <dt><tt>TRUE</tt>     <dd>if the Cell has a Hidden Seam attribute in the given contexte
	* <dt><tt>FALSE</tt>    <dd>otherwise
	* </dl>
	*
	*/
	static void IsHiddenSeamCell(CATCell* piCell, CATCGMAttribute *&pioCGMAttribute);


	/** @nodoc @nocgmitf */
	/** 
	* Internal Use : Check if a given Cell has a Hidden Seam attribute in the context of the hash table of cells 
	* of a body
	*
   * <br><b>Role</b>: Check if a given Cell has a Hidden Seam attribute in the context of the hash table of cells 
	* of a body
	*
	* @param piCellHashTabOfBody
	*	the Hash Table of Cells of a body
	*
	* @param piHiddenCell
	*	the under scope cell
	*
	* @return
	* <dl>
	* <dt><tt>TRUE</tt>     <dd>if the Cell has a Hidden Seam attribute in the given contexte
	* <dt><tt>FALSE</tt>    <dd>otherwise
	* </dl>
	*
   */
	static CATBoolean IsTrackingOverAllInputBodies();

	/** @nodoc @nocgmitf */
	/** 
	* Internal Use : 
	*
	* <br><b>Role</b>: 
	*
	* @param piCell
	*	the under scope cell
	*
	* @return
	* <dl>
	* <dt><tt>TRUE</tt>     <dd>
	* <dt><tt>FALSE</tt>    <dd>otherwise
	* </dl>
	*
	*/
   static CATBoolean IsCellAdmissibleToCarryCGMAttribute(CATCell *piCell,CATBody *piBody);
	
	/** @nodoc @nocgmitf */
	/**
	* 
	* 
	* 
	* 
	* <br><b>Role</b>: 
	*
	* @param piCell
	*
	* @param iListOfManagedKindAttributeForCell
	*
	*/
	static CATBoolean CheckIfHiddenSeamSearchRequiredForBoderedCells(CATCell *piSourceCell,CATCell *piOutputCell,CATListOfInt &iListOfManagedKindAttributeForSourceCell,CATListOfInt &iListOfManagedKindAttributeForOutputCell,short &ioDeepDim);

	/** @nodoc @nocgmitf */
	/** 
   * Internal Use : Check if a given Cell has a Hidden Seam attribute
	* of a body
	*
   * <br><b>Role</b>: Check if a given Cell has a Hidden Seam attribute
	* of a body
	*
	* @param piHiddenCell
	*	the under scope cell
	*
	* @return
	* <dl>
	* <dt><tt>TRUE</tt>     <dd>if the Cell has a Hidden Seam attribute in the given contexte
	* <dt><tt>FALSE</tt>    <dd>otherwise
	* </dl>
	*
   */
   static CATBoolean IsHiddenSeamCell(CATCell* piHiddenCell);

protected:

	/** @nodoc @nocgmitf */
	/**
	* Specific Init and Tuning of CGMAttributeManger oriented type attribute
	* 
	* <br><b>Role</b>: Specific Init and Tuning of CGMAttributeManger oriented type attribute
	* 
	*/
	//void SpecificInit();

   
	/** @nodoc @nocgmitf */
	/** 
   * Internal Use : Process Candidate Edges that have only one incident face capitalized 
   *
   * <br><b>Role</b>: 
   *
   * @param piOutputBody
	*
	* @param piHashTableOfEdges
	*
	* @param piHashTableOfOutputBody
	*
	* @param pioHashTableOfVertices
	*
	* @param pioHashTableOfVertices
	*
	*
   */
   //void ProcessEdgesWithOneIncidFace(CATBody *piOutputBody,CATCellHashTable *piHashTableOfEdges,CATCellHashTable *piHashTableOfOutputBody,
	//											 CATCellHashTable *pioHashTableOfVertices,CATCellHashTable *pioHashTableOfVertices);

	/** @nodoc @nocgmitf */
   /** 
   * Internal Use : from a list of cells, construct connex group of cells with respect to crriteria of same support   
   *                and if not to criteria of smooth
   * <br><b>Role</b>: from a list of cells, construct connex group of cells with respect to crriteria of same support   
   *                and if not to criteria of smooth
   *
   * @param iListOfCells
	*		List of Cells to group
	*
	* @param oListOfGroupedCells
	*     List of groups of cells 
	*
	* @param oListOfIndex
	*     List of longs that designate sizes of groups
	*		
	* @param iWithSharpnessCheck
	*	If Activated, this option allow to check and modulate the groupment process if the cell <tt>piCell</tt>
	*  is internal or border and use the sharpness information for goupment purpose if the cell is border. 
	*
	* @param piTopData
	*	a TopData
	*
	* @param piCell
	*	the under scope cell : the cell where all cells of <tt>iListOfCells</tt> are incidents
	*
   */
   static void GroupCellsBySupports(ListPOfCATCell iListOfCells,ListPOfCATCell& oListOfGroupedCells,CATListOfLong& oListOfIndex, 
												CATBoolean iWithSharpnessCheck=FALSE,CATTopData* piTopData=NULL,CATCell *piCell=NULL);
	
	/** @nodoc @nocgmitf */
	/** 
   * Internal Use : from a list of cells, construct connex group of cells with respect to the sharpness criteria
	*
   * <br><b>Role</b>: from a list of cells, construct connex group of cells with respect to the sharpness criteria
	*
	* @param piTopData
	*	a TopData
	*
		* @param piCell
	*	the under scope cell : the cell where all cells of <tt>iListOfCells</tt> are incidents
	*
   * @param iListOfCells
	*		List of Cells to group
	*
	* @param oListOfGroupedCells
	*     List of groups of cells 
	*
	* @param oListOfIndex
	*     List of longs that designate sizes of groups
	*
   */
   static void GroupCellsBySharpness(CATTopData* piTopData,CATCell *piCell,ListPOfCATCell iListOfCells,
												 ListPOfCATCell& oListOfGroupedCells,CATListOfLong& oListOfIndex);
	

   /** @nodoc @nocgmitf */
	/** 
   * Internal Use : Retrieve the other incident cell of that form a pair of incidet cells
	*                stored in the Hidden Seam Attribute of a given cell in a context 
	*                of a body represented by the hash table of its cells 
	*
   * <br><b>Role</b>: Retrieve the other incident cell of that form a pair of incidet cells
	*                  stored in the Hidden Seam Attribute of a given cell in a context 
	*                  of a body represented by the hash table of its cells 
	*
	* @param piHashTabOfOutputBody
	*	the hash table of cells of the context body
	*
	* @param piHiddenCell
	*	the under scope cell
	*
	* @param piHashTabOfOutputBody
	*	the hash tablle of cells of the context body
	*
	* @param piIncidCell1
	*	the given Incident Cell
	*
	* @param poIncidCell2
	*	the looked for Incident Cell
	*

	* @return
	* <dl>
	* <dt><tt>TRUE</tt>     <dd>if the Cell has a Hidden Seam attribute in the given contexte
	* <dt><tt>FALSE</tt>    <dd>otherwise
	* </dl>
	*
   */
   //static void SearchTheOtherIncidCellsOfAHiddenCell(CATCellHashTable *piHashTabOfOutputBody,CATCell *piHiddenCell,CATCell *piIncidCell1,CATCell *& poIncidCell2);


	/** @nodoc @nocgmitf */
	/** 
   * Internal Use : Test if piCell is a border or an internal cell in the context of its incident cell 
	* piIncidCell1 and piIncidCell2. The incident cells rely on the same support. The purpose is find out 
	* if the cell has 2 PCurves (2 Poec) or 1 PCurve (1 Poec)
   * If it's the firstSituation (2) than the cell is a bordered cell otherwise (1) it's an internal cell
	*
   * <br><b>Role</b>: Test if piCell is a border or an internal cell in the context of its incident cell 
	* piIncidCell1 and piIncidCell2. The incident cells rely on the same support. The purpose is find out 
	* if the cell has 2 PCurves (2 Poec) or 1 PCurve (1 Poec)
   * If it's the firstSituation (2) than the cell is a bordered cell otherwise (1) it's an internal cell
	*
	* @param piCell
	*	the under scope cell
	*
	* @param piHashTabOfOutputBody
	*	the hash tablle of cells of the context body
	*
	* @param piIncidCell1
	*	the given Incident Cell
	*
	* @param piIncidCell2
	*	the looked for Incident Cell
	*
	* @return
	* <dl>
	* <dt><tt>TRUE</tt>     <dd>if the Cell Border
	* <dt><tt>FALSE</tt>    <dd>otherwise
	* </dl>
	*
   */
   static CATBoolean IsCellBorder(CATCell *piCell, CATCell *piIncidCell1, CATCell *piIncidCell2);

   /** @nodoc @nocgmitf */
	/** 
   * Internal Use : Test if the cell piCell is sharp or smooth in the context of it's incident cells 
	* piIncidCell1 and piIncidCell2
	*
   * <br><b>Role</b>: Test if the cell piCell is sharp or smooth in the context of it's incident cells 
	* piIncidCell1 and piIncidCell2
	*
	* @param piCell
	*	the under scope cell
	*
	* @param piHashTabOfOutputBody
	*	the hash tablle of cells of the context body
	*
	* @param piIncidCell1
	*	the given Incident Cell
	*
	* @param piIncidCell2
	*	the looked for Incident Cell
	*
	* @param piTopData
	*	a TopData
	*
	* @return
	* <dl>
	* <dt><tt>TRUE</tt>     <dd>if the Cell is Sharp
	* <dt><tt>FALSE</tt>    <dd>otherwise
	* </dl>
	*
   */
   static CATBoolean IsCellSharp(CATCell *piCell, CATCell *piIncidCell1, CATCell *piIncidCell2, CATTopData *piTopData);

	/** @nodoc @nocgmitf */
	/** 
   * Internal Use : Extract all Curves of the Merged Curve piEdgeCurve
	* (Recursive method)
	*
   * <br><b>Role</b> : Extract all Curves of the Merged Curve piEdgeCurve
	*
	* @param piEdgeCurve
	*	the under scope EdgeCurve
	*
	* @param oListOfCATCurve
	*	List of all Curves owned by the given EdgeCurve
	*
	*/
   static void GetAllCurvesFromEdgeCurve(CATEdgeCurve *piEdgeCurve,CATLISTP(CATCurve)& oListOfCATCurve);

private:

	/** @nodoc @nocgmitf */
   /** 
   * Parameters Ctor
   *
   * <br><b>Role</b>: Constructor without the context of a CATTopOperator
   *
	* @param piSoftConfig 
	* a pointer to a SoftwareConfigucration
	*
	* @param iListOfInputBody 
	* list of input bodies from where resulte bodies have been built.
	*
	* @param iListOfOutputBody
	* list of output bodies that have been built rom input bodies.
	*
	* @param piListOfCGMJournal 
	* list of CGM Journals that describe how output bodies have been built from input bodies.
	*
	* @param iHiddenSeamCriterion 
	* Criterion taking into account in decision of assign a Hidden Seam attribute to candidate cells
	*
	*/
   //CATTopHiddenSeamCellManager(CATSoftwareConfiguration *piSC, ListPOfCATBody& iListOfInputBody, 
	//									 ListPOfCATBody& iListOfOutputBody, CATLISTP(CATCGMJournal)& iListOfCGMJournal, 
	//									 CATTopHiddenSeamCriterion iHiddenSeamCriterion=CATTopHiddenSeamCriterion_GeometricSupport);

	/** @nodoc @nocgmitf */
	/**
	* Parameters Ctor
	*
	* <br><b>Role</b>: Constructor with the context of a CATTopOperator
	*
	* @param piTopOperator 
	* the Top Operator
	*
	*/
   //CATTopHiddenSeamCellManager(CATTopOperator *piTopOperator, 
	//									 CATTopHiddenSeamCriterion iHiddenSeamCriterion=CATTopHiddenSeamCriterion_GeometricSupport);

	/** @nodoc @nocgmitf */
	/**
   * Forbidden Copy Ctor
   *
   * <br><b>Role</b>: Copy Ctor
   *
   */
   CATTopHiddenSeamCellManager(const CATTopHiddenSeamCellManager &iCopy);

	/** @nodoc @nocgmitf */
   /**
   * Forbidden Equal Operator
   *
   * <br><b>Role</b>: Equal Operator
   *
   */
   CATTopHiddenSeamCellManager& operator = (const CATTopHiddenSeamCellManager &iCopy);

	//////  Data //////
	
	//Options
   //CATTopHiddenSeamCriterion     _HiddenSeamCriterion;							// By default, the criterion is CATCGMGeometricSupport   
   //CATBoolean                    _IsGlobSharpSupportSameGeoCriterion;		// Si le critère same support n'est pas suffisant alors on introduit le critère glob sharp
   //CATBoolean                    _CheckIfCellIsSmartInOutputBody;
};



//INLINE void CATTopHiddenSeamCellManager::SetGlobSharpSupportSameGeoCriterion(CATBoolean iGlobSharpSupportSameGeoCriterion)
//{
//   _IsGlobSharpSupportSameGeoCriterion = iGlobSharpSupportSameGeoCriterion;
//}


//INLINE void CATTopHiddenSeamCellManager::SetCheckIfCellIsSmartInOutputBody(CATBody *iBody, CATBoolean iCheckIfCellIsSmartInOutputBody)
//{
//   if (iBody) 
//   {
//      _CheckIfCellIsSmartInOutputBody = iCheckIfCellIsSmartInOutputBody;
//   }
//}


#endif
