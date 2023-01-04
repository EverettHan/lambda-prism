#ifndef CATTopDomainTracker_H
#define	CATTopDomainTracker_H

//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2013
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
//	Class			:		CATTopDomainTracker
//	Creation		:		24/05/2013
//
//
//	Synopsis	:	Header class of CATTopDomainTracker.
//					
//	
//
//
//	Authors		:  KY1
//-----------------------------------------------------------------------------
#include "CATErrorDef.h"
#include "CATTopJournalOfDomainTypeDef.h"
#include "CATCGMNewArray.h"
#include "CATListOfShort.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATDomain.h"
#include "CATBoolean.h"
#include "CATListOfCATGeometries.h"


class CATDomain;
class CATBody;
//class CATLISP(CATBody); 
class CATCGMJournalList;
class CATCGMHashTable;
class CATCGMHashTableWithAssoc;

/** @nodoc @nocgmitf */
/**
* 
* 
*
* 
*/

class   CATTopDomainTracker
{
public:

   CATCGMNewClassArrayDeclare;

   /** @nodoc @nocgmitf */
   /**
   * creation method
   * @param iListOfCells 
   *   Cells List to transpose in a CATTopDomainTracker
   */
   static CATTopDomainTracker *CreateCATTopDomainTracker(CATCGMJournalList *piCGMJournalList,CATLISTP(CATBody) &iListOfInputBody, CATBody* piOuputBody);

   /** @nodoc @nocgmitf */
   /**
   * destructor
   */
   virtual ~CATTopDomainTracker();

   /** @nodoc @nocgmitf */
   /**
   * Set List of input domains 
   * @param iListOfInputDomains
   *  the under scope list
   */
   void SetInputDomains(CATLISTP(CATDomain) &iListOfInputDomains);

   /** @nodoc @nocgmitf */
   /**
   * Set List of output domains 
   * @param iListOfOutputDomains
   *  the under scope list
   */
   void SetOutputDomains(CATLISTP(CATDomain) &iListOfOutputDomains);

   /** @nodoc @nocgmitf */
   /**
   * Get the image of the given domain in the target body
   * @param piInputDomain
   *  the query domain (the input domain)
   *
   * @param ioListOfImageDomain
   *  the List of domains resulted from the input domain image type the Domain 
   *
   * @param ioListOfTypeOfConstruction
   *  List of Type of construction for each image domain found (modified, created, deleted)
   *
   * @param ioListOfNonDeletedCells
   *	List Of input Cells that have non deleted, not used in Creation or Modification
   *
   * @return
   *   <dl>
   *	 <dt><tt>S_OK</tt>		<dd>if Computation is succedded
   *	 <dt><tt>E_FAIL</tt>    <dd>otherwise
   *	 </dl>
   *   
   */
   HRESULT GetImage(CATDomain *piInputDomain,CATLISTP(CATDomain) &ioListOfImageDomain, CATListOfShort &ioListOfTypeOfConstruction, CATLISTP(CATCell) &ioListOfNonDeletedCells);

   /** @nodoc @nocgmitf */
   /**
   * Get the image of the given domain in the target body
   * @param piOutputDomain
   *  the query domain (the output domain)
   * @param ioListOfSourceDomain 
   *  the List of domains resulted from the input domain image type the Domain 
   * @param  ioTypeOfConstruction
   *  Type of construction of the given output domain from the computed input domains (modified, created, deleted) 
   *
   * @return
   *   <dl>
   *	 <dt><tt>S_OK</tt>		<dd>if Computation is succedded
   *	 <dt><tt>E_FAIL</tt>    <dd>otherwise
   *	 </dl>
   * 
   */
   HRESULT GetSource(CATDomain *piOutputDomain,CATLISTP(CATDomain) &ioListOfSourceDomain,short &ioTypeOfConstruction);

   /* We already know that the piCell belong to the Domain */
   static CATBoolean IsUpperCellOfDomain(CATCell *piCell,CATDomain *piDomain);

   /* Remove from the Input List Removed Geometries,, non Cells */
   static void CleanListOfGeometry(CATLISTP(CATGeometry) &iDirtyListOfGeometry,CATLISTP(CATGeometry) &ioCleanListOfGeometry);
private: 

   /**
   * default ctor
   */
   CATTopDomainTracker ();

   /**
   * copy ctor
   * @param iTopDomainTracker
   *   iTopDomainTracker to copy
   */
   CATTopDomainTracker (const CATTopDomainTracker& iTopDomainTracker);

   /**
   * operator =
   * @param iTopDomainTracker
   *   iTopDomainTracker to copy
   */

   CATTopDomainTracker& operator = (const CATTopDomainTracker& iTopDomainTracker);

   /**
   * param ctor
   * * @param piCGMJournalList
   *   the Journal of Cell
   *   @param iListOfInputBody
   *   the list of input bodies
   *   @param iListOfOuputBody
   *   the list of output bodies
   */
   CATTopDomainTracker (CATCGMJournalList *piCGMJournalList,CATLISTP(CATBody) &iListOfInputBody, CATBody* piOutputBody);


   /******* Internal services *******/

   CATCGMHashTableWithAssoc *GetHashTabInputDomainExpectedReportingCells(CATDomain *piInputDomain);

   /* */
   CATBoolean IsDomainWithModifiedCells(CATDomain *pOutputDomain);

   /* restricted to lumps*/
   CATBoolean IsImageDomainFromOnlyOneDomain(CATDomain *pOutputDomain, CATDomain *pInputDomain, CATCGMHashTableWithAssoc *piHashTabOfInputCellsOfDomainWithOrientation/*, CATLISTP(CATCell)& iListOfOutputCellAlreadyChecked*/);

   /* We already know that the piCell belong to the Domain */
   //CATBoolean IsUpperCellOfDomain(CATCell *piCell,CATDomain *piDomain);

   /* */
   short IsVolumicContext();
   /* */
   void InitWorkingData();


   //DATA

   CATCGMJournalList*						_piCGMJournalList;
   CATLISTP(CATBody)							_iListOfInputBodies;
   CATBody          *						_piOutputBody;

   CATLISTP(CATDomain)                 _ListOfInputDomains;
   CATLISTP(CATDomain)                 _ListOfOutputDomains;

   CATLISTP(CATCell)							_ListOfModifiedCell;

   CATCGMHashTable*							_HashTabOutputCreation;
   CATCGMHashTable*							_HashTabOutputModification;
   CATCGMHashTable*							_HashTabOutputSubdivision;
   CATCGMHashTable*							_HashTabOutputAbsorption;
   CATCGMHashTable*							_HashTabOutputDeletion;
   CATCGMHashTable*							_HashTabOutputKeep;

   CATCGMHashTableWithAssoc  *         _pHashTabOfInputDomainsWithExpectedReportingCells;
   CATCGMHashTable           *         _pHashTabOfAllExpectedReportingInputCells;

   CATBoolean _InitWorkingDataDone;
   short _IsVolumicContext;
};



#endif 
