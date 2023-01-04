#ifndef CATTopImprintCellManager_H
#define CATTopImprintCellManager_H
// COPYRIGHT DASSAULT SYSTEMES  2009
//===========================================================================  
//  Class  CATTopImprintCellManager  
//---------------------------------------------------------------------------  
//
//  Class to propagate Imprint Attributesafter the execution of a topological operator.
//
//  If a target cell is considered as an Imprint Cell, then the attribute 
//  of the source that has been linked with the target cell is set on this latter. 
//  If the input body has Imprint cells hence the CATTopImprintCellManager
//  has to propagate these information in the output body.
//  This is done through the Cell Tracker which rely on Topological Journal of 
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
class CATTopCGMAttributePropagateOption;


/** @nodoc @nocgmitf */
/**
* Class to analyze and propagate Imprint attribute from input bodies to output bodies through CGM Journals.
* Class to propagate Imprint Attributes after the execution of a topological operator.
*
* A CATTopImprintCellManager allow propagation of Imprint Attributes from input bodies 
* to output bodies.
*
* If an origin cell own an Imrint Attribute, then under given conditions 
* (driven by Kind and specificity of the Imprint Attribute)
* the target cell will share the Imprint Attribute.

* The Cell Tracker which relies on CGM Journal of the Operator, is used 
* to match pertinent output cells with input cells.
* 
*<ul>
* <li>A CATTopImprintCellManager object is created with the <tt>CreateCATTopIlmprintCellManager</tt> 
* global function. It must be directly deleted with the <tt>delete</tt> operator. It is not streamable. 
* <li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method.
*</ul>
*/

/** @nodoc @nocgmitf */
class ExportedByCATTopologicalObjects CATTopImprintCellManager
{
public:
   
	/** @nodoc @nocgmitf */
   /** 
   * Method to create a CATTopImprintCellManager without the context of a CATTopOperator
   *
   * <br><b>Role</b>: Method to create a CATTopImprintCellManager without the context of a CATTopOperator
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
   //static CATTopImprintCellManager *CreateCATTopImprintCellManager(CATSoftwareConfiguration *piSC, ListPOfCATBody& iListOfInputBody, ListPOfCATBody& iListOfOutputBody, CATLISTP(CATCGMJournal)& iListOfCGMJournal);

	/** @nodoc @nocgmitf */
	/**
	* Method to create a CATTopImprintCellManager with the context of a CATTopOperator
	*
	* <br><b>Role</b>: Method to create a CATTopImprintCellManager with the context of a CATTopOperator
	*
	*/
   //static CATTopImprintCellManager *CreateCATTopImprintCellManager(CATTopOperator *piTopOperator);

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
   static CATBoolean IsImprintCell(CATCell* piCell);

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
   static void IsImprintCell(CATCell* piCell,CATCGMAttribute *&pioCGMAttribute);

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
   static CATBoolean IsCellAdmissibleToCarryCGMAttribute(CATCell *piCell,CATBody *piBody, CATBoolean iAllowNewImprintForFaces);

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
	static CATBoolean CheckIfImprintCellSearchRequiredForBoderedCells(CATCell *piSourceCell,CATCell *piOutputCell,CATListOfInt &iListOfManagedKindAttributeForSourceCell,
                                                                     CATListOfInt &iListOfManagedKindAttributeForOutputCell,CATBoolean iCheckImprintOnVertex,short &ioDeepDim);

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
	static void GetIncidCells(CATCell *piCell, CATBody *piBody, CATLISTP(CATCell) &ioListOfIncidCells);

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
	static CATBoolean PropagateCGMAttribute(CATTopCGMAttributePropagateOption& iAttributePropagateOption, CATCell *piDestCell, CATBody *piOutputBody, 
                                          CATCellHashTable *piHashTableOfCellsOfOutputBody, CATLISTP(CATTopCellWithCGMAttribute) &iListOfCellWithCGMAttributes,
														CATTopHashTableOfCellWithCGMAttributesState *pioHashTab_OutputFacesWithCGMAttributesState, 
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

protected:

	/** @nodoc @nocgmitf */
	/** 
   * Internal Use : Get the Imprint attribute of a given Cell if it exists
	*
   * <br><b>Role</b>: Get the Imprint attribute of a given Cell if it exists
	* of a body
	*
	* @param piCellHashTabOfBody
	*	the Hash Table of Cells of a body
	*
	* @param piCell
	*	the under scope cell
	*
	* @return
	*  A pointer to the Imprint Attribute if it exists
   */
   //static CATCGMImprintAttribute *GetImprintAttribute(CATCell* piCell);
		
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
	*/
   //CATTopImprintCellManager(CATSoftwareConfiguration *piSC, ListPOfCATBody& iListOfInputBody, ListPOfCATBody& iListOfOutputBody, CATLISTP(CATCGMJournal)& iListOfCGMJournal);

	/** @nodoc @nocgmitf */
	/**
	* Parameters Ctor
	*
	* <br><b>Role</b>: Constructor with the context of a CATTopOperator
	*
	* @param piTopOperator 
	* a pointer to the Top Operator that already was run
	*
	*/
   //CATTopImprintCellManager(CATTopOperator *piTopOperator);

	/** @nodoc @nocgmitf */
	/**
   * Forbidden Copy Ctor
   *
   * <br><b>Role</b>: Copy Ctor
   *
   */
   CATTopImprintCellManager(const CATTopImprintCellManager &iCopy);

	/** @nodoc @nocgmitf */
   /**
   * Forbidden Equal Operator
   *
   * <br><b>Role</b>: Equal Operator
   *
   */
   CATTopImprintCellManager& operator = (const CATTopImprintCellManager &iCopy);

	/** @nodoc @nocgmitf */
	/** 
	* Dtor  
	*/
	virtual ~CATTopImprintCellManager();
};





#endif
