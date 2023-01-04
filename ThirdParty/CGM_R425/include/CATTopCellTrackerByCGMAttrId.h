#ifndef  CATTopCellTrackerByCGMAttrId_H
#define	CATTopCellTrackerByCGMAttrId_H

// COPYRIGHT DASSAULT SYSTEMES  2009
//===========================================================================  
//  Class  CATTopCellTrackerByCGMAttrId  
//---------------------------------------------------------------------------  
//
//  A CATTopCellTrackerByCGMAttrId allows, for a given CGM Attribute, to test if a given Output Cell 
//  has at least as descendent, an input cell with a CGM Attribute of a required type
//
//  
//===========================================================================   
#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "CATListOfCATCells.h"
#include "CATMathInline.h"
#include "ListPOfCATBody.h"
#include "CATBody.h"
#include "CATCGMJournal.h"
#include "CATListOfCATCGMJournals.h"
#include "CATCollec.h"
#include "CATTopImprintAttributeServices.h"
#include "CATCGMAttrId.h"



class CATCGMCellTrackerImp;
class CATCGMJournal;
class CATCGMJournalList;
class CATSoftwareConfiguration;


/**
*  A CATTopCellTrackerByCGMAttrId allows, for a given CGM Attribute, to test if a given Output Cell 
*  has at least as descendent, an input cell with a CGM Attribute of a required type
*
*/
/** @nodoc @nocgmitf */
class ExportedByCATTopologicalObjects CATTopCellTrackerByCGMAttrId
{
public:

   /** @nodoc @nocgmitf */
   /** 
   * Method to create a CATTopCellTrackerByCGMAttrId without the context of a CATTopOperator
   *
   * <br><b>Role</b>: Method to create a CATTopCellTrackerByCGMAttrId without the context of a CATTopOperator
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
   * @param piCGMAttrId 
   * the Id of CGM Attribute
   *	
   */
   static CATTopCellTrackerByCGMAttrId *CreateCATTopCellTrackerByCGMAttrId(CATSoftwareConfiguration *piSC, ListPOfCATBody& iListOfInputBody, ListPOfCATBody& iListOfOutputBody, CATLISTP(CATCGMJournal)& iListOfCGMJournal, 
                                                                       CATCGMAttrId *piCGMAttrId);

   /** @nodoc @nocgmitf */
   /** 
   * Dtor  
   */
   virtual ~CATTopCellTrackerByCGMAttrId();

   /** @nodoc @nocgmitf */
   /**
   * Set the Id of CGM Attribute to be tracked
   * 
   * * <br><b>Role</b>: Set the Id of CGM Attribute to be tracked
   *
   * @param piCGMAttrId 
   * the Id of CGM Attribute
   *
   */
   INLINE void SetCGMAttrId(CATCGMAttrId *piCGMAttrId);

   /** @nodoc @nocgmitf */
   /**
   * Test whether a Cell has a descendant with the specified CGM Attr Id
   * (the type of the attribute was specified in the constructor)
   * @return
   * <dl>
   * <dt><tt>TRUE</tt>     <dd>if there is at least one descendant cell with the requested CGM Attr Id
   * <dt><tt>FALSE</tt>    <dd>if no there is descendant cell with the requested CGM Attr Id
   * </dl>
   */
   CATBoolean IsCellDescendantFromCellWithCGMAttrId(CATCell *piCell);

   /** @nodoc @nocgmitf */
   /** 
   * Split a set of output cells, that given as input argument, into two disjoint sets
   * A set of cells that have as descendants at least one cell 
   * with the requested CGM Attr Id and a second set of cells that have no 
   * descendant cell with the requested CGM Attr Id
   *
   * <br><b>Role</b>: Split a set of output cells, that given as input argument, into two disjoint sets
   * A set of cells that have as descendants at least one cell 
   * with the requested CGM Attr Id and a second set of cells that have no 
   * descendant cell with the requested CGM Attr Id
   *
   * @param piHashTabOfQueryCells 
   * the set of output cells that have to be tested.
   *
   * @param pioHashTabCellsWithDescendantCellsCGMAttrId 
   * the set of cells, each cell has at least one descendant with the requested CGM Attribut Type.
   *
   * @param pioHashTabCellsWithoutDescendantCellsCGMAttrId
   * the set of cells, each cell has no descendant with the requested CGM Attribut Type.
   *
   */
   void RetrieveCellsDescendantFromCellWithCGMAttrId(CATCellHashTable *piHashTabOfQueryCells,CATCellHashTable *pioHashTabCellsWithDescendantCellsCGMAttrId,CATCellHashTable *pioHashTabCellsWithoutDescendantCellsCGMAttrId);
   
private:   

   /** @nodoc @nocgmitf */
   /** 
   * Method to create a CATTopCellTrackerByCGMAttrId without the context of a CATTopOperator
   *
   * <br><b>Role</b>: Method to create a CATTopCellTrackerByCGMAttrId without the context of a CATTopOperator
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
   * @param piCGMAttrId
   * Id of CGM Attribute to be used.
   *
   */
   CATTopCellTrackerByCGMAttrId(CATSoftwareConfiguration *piSC, ListPOfCATBody& iListOfInputBody, ListPOfCATBody& iListOfOutputBody, CATLISTP(CATCGMJournal)& iListOfCGMJournal, CATCGMAttrId *piCGMAttrId);

   /** @nodoc @nocgmitf */
   /**
   * forbidden Default Ctor
   *
   * <br><b>Role</b>: Default ctor.
   *
   */
   CATTopCellTrackerByCGMAttrId();


   /** @nodoc @nocgmitf */
   /**
   * forbidden Copy Ctor
   *
   * <br><b>Role</b>: Copy ctor.
   *
   */
   CATTopCellTrackerByCGMAttrId(const CATTopCellTrackerByCGMAttrId &iCopy);

   /** @nodoc @nocgmitf */
   /**
   * forbidden Equal Operator
   *
   * <br><b>Role</b>: Equal Operator
   *
   */
   CATTopCellTrackerByCGMAttrId& operator = (const CATTopCellTrackerByCGMAttrId &iCopy);


   /*************************** Data ***************************/
   //
   ListPOfCATBody				      _ListOfInputBody;
   CATLISTP(CATBody)  	  			_ListOfOutputBody;
   CATLISTP(CATCGMJournal)       _ListOfCGMJournal;
   CATSoftwareConfiguration		*_SC;
   CATCGMAttrId                  *_pUAID_CGMAttribute;
   //
   CATCGMCellTrackerImp				*_pCellTracker;
};


//================================================================================================================================================================================================
//
//
//================================================================================================================================================================================================
INLINE void CATTopCellTrackerByCGMAttrId::SetCGMAttrId(CATCGMAttrId *piCGMAttrId)
{
   _pUAID_CGMAttribute = piCGMAttrId;
}

#endif



