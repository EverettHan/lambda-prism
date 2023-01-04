#ifndef CATTopCGMAttributeManager_H
#define	CATTopCGMAttributeManager_H
// COPYRIGHT DASSAULT SYSTEMES  2009
//===========================================================================  
//  Class  CATTopCGMAttributeManager  
//---------------------------------------------------------------------------  
//
//  Base Class who offers services related to propagation of  CGM Attributes 
//  after the execution of a topological operator.
//
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



class CATSoftwareConfiguration;
class CATCGMCellTracker;
class CATTopImprintCellManager;
class CATTopHiddenSeamCellManager;
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
* A CATTopCGMAttributeManager allow propagation of Imprint Attributes from input bodies 
* to output bodies.
*
* If an origin cell own an Imrint Attribute, then under given conditions 
* (driven by Kind and specificity of the Imprint Attribute)
* the target cell will share the Imprint Attribute.

* The Cell Tracker which relies on CGM Journal of the Operator, is used 
* to match pertinent output cells with input cells.
* 
*<ul>
* <li>A CATTopCGMAttributeManager object is created with the <tt>CreateCATTopIlmprintCellManager</tt> 
* global function. It must be directly deleted with the <tt>delete</tt> operator. It is not streamable. 
* <li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method.
*</ul>
*/

/** @nodoc @nocgmitf */
class ExportedByCATTopologicalObjects CATTopCGMAttributeManager
{
public:
   
	/** @nodoc @nocgmitf */
   /** 
   * Method to create a CATTopCGMAttributeManager without the context of a CATTopOperator
   *
   * <br><b>Role</b>: Method to create a CATTopCGMAttributeManager without the context of a CATTopOperator
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
   //static CATTopCGMAttributeManager *CreateCATTopCGMAttributeManager(CATSoftwareConfiguration *piSC, ListPOfCATBody& iListOfInputBody, ListPOfCATBody& iListOfOutputBody, CATLISTP(CATCGMJournal)& iListOfCGMJournal);

	/** @nodoc @nocgmitf */
	/**
	* Method to create a CATTopCGMAttributeManager with the context of a CATTopOperator
	*
	* <br><b>Role</b>: Method to create a CATTopCGMAttributeManager with the context of a CATTopOperator
	*
	*/
   //static CATTopCGMAttributeManager *CreateCATTopCGMAttributeManager(CATTopOperator *piTopOperator);

	/** @nodoc @nocgmitf */
   /** 
   * Dtor  
   */
   ~CATTopCGMAttributeManager();

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
	static CATBoolean IsCellAdmissibleToCarryCGMAttribute(CATCell *piCell,CATBody *piBody,CATTopCGMAttributeLabel &iKindOfManagedAttributes,CATBoolean iAllowNewImprintForFaces);
	
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
	static CATCGMAttribute *IsCGMAttribute(CATCell *piCell,CATTopCGMAttributeLabel &iAttributeLabel,CATCellHashTable *piCellHashTabOfBody = NULL);

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
	static CATBoolean IsTrackingOverAllInputBodies(CATTopCGMAttributeLabel &iAttributeLabel);

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
	static CATBoolean IsTrackingOverAllSrcCells(CATTopCGMAttributeLabel &iAttributeLabel);

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
                                          CATLISTP(CATTopCellWithCGMAttribute) &iListOfCellWithCGMAttributes, CATTopCGMAttributeLabel& iCGMAttributeToPropagate,
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
	static void Dump(CATCGMOutput& os, CATListOfInt &iListOfCGMAttributes,CATCell *piCell, CATBody *piBody = NULL);


//protected:

	/** @nodoc @nocgmitf */
	/**
	* Specific Init and Tuning of CGMAttributeManager oriented type attribute
	* 
	* <br><b>Role</b>: Specific Init and Tuning of CGMAttributeManger oriented type attribute
	* 
	*/
	//void SpecificInit();

	/** @nodoc @nocgmitf */   
	/**
	*
	*/
	static void SetCellTracker(CATCGMCellTracker *piCellTracker);

	/** @nodoc @nocgmitf */   
	/**
	*
	*/
	static void SetTopOperator(CATTopOperator *piTopOperator);

	/** @nodoc @nocgmitf */   
	/**
	*
	*/
	static void SetSoftwareConfiguration(CATSoftwareConfiguration *piSoftConfig);

	 
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
		
//protected:

	// Static Methods

	


	// Static Data
	
	static CATSoftwareConfiguration		*_pSoftConfig;
	static CATCGMCellTracker				*_pCellTracker;
	static CATTopOperator					*_pTopOperator;
	static ListPOfCATBody				   _ListOfInputBody;
	static CATLISTP(CATBody)  	  			_ListOfOutputBody;
	static CATLISTP(CATCGMJournal)      _ListOfCGMJournal;
	static CATLISTP(CATBody)            _ListOfAllBodies;
   static CATListOfInt                 _ListOfDimOfAllBodies;

	static CATBoolean _MustHSAttributeOnEachInputBody;
	static CATBoolean _InitSpecific;

//private :	
	/** @nodoc @nocgmitf */
	/**
	* Forbidden Copy Ctor
	*
	* <br><b>Role</b>: Default Ctor
	*
	*/
	CATTopCGMAttributeManager();

	/** @nodoc @nocgmitf */
	/**
   * Forbidden Copy Ctor
   *
   * <br><b>Role</b>: Copy Ctor
   *
   */
   CATTopCGMAttributeManager(const CATTopCGMAttributeManager &iCopy);

	/** @nodoc @nocgmitf */
   /**
   * Forbidden Equal Operator
   *
   * <br><b>Role</b>: Equal Operator
   *
   */
   CATTopCGMAttributeManager& operator = (const CATTopCGMAttributeManager &iCopy);	
};


//================================================================================================================================================================================================
//
//
//================================================================================================================================================================================================
class CATTopCGMAttributePropagateOption
{   
   public :
      CATTopCGMAttributePropagateOption():_PropagateFromImprintedVtxToEdge(FALSE) {};
      void SetPropagateFromImprintedVtxToEdge(CATBoolean iOption) {_PropagateFromImprintedVtxToEdge=iOption;};
      CATBoolean GetPropagateFromImprintedVtxToEdge() {return _PropagateFromImprintedVtxToEdge;};
private:
      CATBoolean _PropagateFromImprintedVtxToEdge;
};



#endif
