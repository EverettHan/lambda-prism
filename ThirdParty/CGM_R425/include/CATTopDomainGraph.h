#ifndef CATTopDomainGraph_H
#define	CATTopDomainGraph_H

//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2013
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
//	Class			:		CATTopDomainGraph
//	Creation		:		24/05/2013
//
//
//	Synopsis	:	Header class of CATTopDomainGraph.
//					
//	
//
//
//	Authors		:  KY1
//-----------------------------------------------------------------------------

//#include "CATCollec.h" 
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATBody.h"
#include "CATCGMOutput.h"
#include "CATDomain.h"
#include "ListPOfCATDomain.h"




class CATTopDomainNode;
class CATTopHashTableOfDomainNode;
class CATBody;
class CATCGMJournalList;
//class CATLISTP(CATBody);
class CATTopDomainTracker;
class CATCGMHashTableWithAssoc;
class CATCGMHashTable;

/** @nodoc @nocgmitf */
/**
* Class that build a journal of domains from a journal of cells, input bodies
* and the result body.
* Retrieve the result with GetJournal() service.
* the the life cycle of the returned journal is under the responsability 
* of the caller
*  
*/

class   CATTopDomainGraph
{
public:

  CATCGMNewClassArrayDeclare;

  /** @nodoc @nocgmitf */
  /**
  * creation method
  * @param iListOfInputBodies 
  *    List of Input Bodies 
  * @param piOutputBody 
  *    the output body obtained from the givent input bodies
  * @param piCGMJournalList 
  *    the journal of cells that describe how cells of the result body 
  *    were built from cells of the input bodies
  *
  * @return
  *    the Graph of Domain
  *    
  */
  static CATTopDomainGraph *CreateCATTopDomainGraph(CATLISTP(CATBody) &iListOfInputBodies,CATBody *piOutputBody, CATCGMJournalList *piCGMJournalList);

  /** @nodoc @nocgmitf */
  /**
  * destructor
  */
  virtual ~CATTopDomainGraph();

  /** @nodoc @nocgmitf */
  /**
  * Run conputation of the Journal of Domains ...
  *
  * @return
  *   <dl>
  *	 <dt><tt>S_OK</tt>		<dd>if Computation is succedded
  *	 <dt><tt>E_FAIL</tt>    <dd>otherwise
  *	 </dl>
  *
  */
  HRESULT 						Run();

  /** @nodoc @nocgmitf */
  /**
  * Get the the journal of Domain 
  * @return
  *   the Journal Of Domain
  */
  CATCGMJournalList*		GetJournal();

private:

  /** @nodoc @nocgmitf */
  /**
  * Get the DomainNode corresponding to the query domain
  * @param piDomain
  *  the query domain
  * @return
  *  return the DomainNode in the graph hat corresponds to the query domain, 
  *  NULL if doesn't exist in the graph  
  *    
  */
  CATTopDomainNode*				GetDomainNode(CATDomain *piDomain);

  /** @nodoc @nocgmitf */
  /**
  * Fill the Journal Of Domains from thre Built Graph Of DomainNode
  *
  * @return
  *   <dl>
  *	 <dt><tt>S_OK</tt>		<dd>if Computation is succedded
  *	 <dt><tt>E_FAIL</tt>    <dd>otherwise
  *	 </dl>
  *    
  */
  HRESULT	  						FillJournalFromGraph();

  /** @nodoc @nocgmitf */
  /**
  * Post Process Algorithm Step : Process DomainNode with Inknown Status 
  * (case happen generally when journal information is not sufficient to deduce the Node Status)
  *
  * @return
  *   <dl>
  *	 <dt><tt>S_OK</tt>		<dd>if Post Processing is succedded
  *	 <dt><tt>E_FAIL</tt>    <dd>otherwise
  *	 </dl>
  *    
  */
  HRESULT							PostProcessTrickyNodeDomain();

  /** @nodoc @nocgmitf */
  /**
  * Init Graph Of Domains from given inputs
  *
  * @return
  *   <dl>
  *	 <dt><tt>S_OK</tt>		<dd>if Computation is succedded
  *	 <dt><tt>E_FAIL</tt>    <dd>otherwise
  *	 </dl>
  *    
  */
  HRESULT				  			InitGraphOfDomain();

  /** @nodoc @nocgmitf */
  /**
  * Build Graph Of Domains 
  *
  * @return
  *   <dl>
  *	 <dt><tt>S_OK</tt>		<dd>if Computation is succedded
  *	 <dt><tt>E_FAIL</tt>    <dd>otherwise
  *	 </dl>
  *
  */
  HRESULT				  			BuildGraphOfDomain();

  /** @nodoc @nocgmitf */
  /**
  * Dump Graph nodes
  * @param ioCGMStr
  *   iTopDomainGraph to copy
  */
  void Dump(CATCGMOutput& ioCGMStr);

  /** @nodoc @nocgmitf */
  /**
  * Gives the highest cells of a given domain 
  * @param piDomain
  *   Domain under Scope
  * @param pioHashTabOfDomainCells
  *   Hash Table that contains cells of the requested Domain
  */
  HRESULT GetCellsOfDomain(CATDomain *piDomain, CATCGMHashTable *& pioHashTabOfDomainCells);

  /** @nodoc @nocgmitf */
  /**
  * Stores a Domain Node tht need t be post processed
  *
  * @param piTopDomainNode
  *   The Domain Node under Scope
  * @param piDomain
  *   The Domain under Scope
  * @param iInOrOutputDomain
  *   precisece tif the Domain under scope is an input Domain or an outpur domain 
  */
  HRESULT AddTrickyDomainNode(CATTopDomainNode *piTopDomainNode, CATDomain *piDomain, CATBoolean iInOrOutputDomain);

  /** @nodoc @nocgmitf */
  /**
  * Test whether a given cell belongs to an input body
  *
  * @param pioCell
  *   The Cell under Scope
  */
  CATBoolean IsCellBelongToInputBody(CATCell *pioCell);

  /** @nodoc @nocgmitf */
  /**
  * Check whether exists a cell belongs to the Domain, given as input argument,
  * has been modified into 
  * @param piDomain
  *   The Domain under Scope
  */
  CATBoolean IsThereCellModified(CATDomain *piDomain);

  /* To enhance : review archi of classes to factorize better the code */
  CATBoolean IsCellModified(CATCell *piCell);

  /** @nodoc @nocgmitf */
  /**
  * Add in a given Journal a Modifcation, Subdivision or Absorption Item
  *
  * @param piCGMJournal
  *   The Journal under scope
  *
  * @param ioListFrom
  *   The List of Input Geometry (Domains)
  *
  * @param ioListInto
  *   The List of Output Geometry (Domains)
  */
  HRESULT ReportModificationOrder(CATCGMJournalList *& piCGMJournal, CATLISTP(CATGeometry) &ioListFrom, CATLISTP(CATGeometry) &ioListInto); 

  
  /** @nodoc @nocgmitf */
  /**
  * Add in a deletions item of Input Domains in the JOfDom : INTERNAL USE 
  */
  void AddDeletionItems();

    /** @nodoc @nocgmitf */
  /**
  * Add in a creations item of Output Domains in the JOfDom : INTERNAL USE 
  */
  void AddCreationItems();

  /** @nodoc @nocgmitf */
  /**
  * default ctor
  */
  CATTopDomainGraph();

  /** @nodoc @nocgmitf */
  /**
  * copy ctor
  * @param iTopDomainGraph
  *   iTopDomainGraph to copy
  */
  CATTopDomainGraph (const CATTopDomainGraph& iTopDomainGraph);

  /** @nodoc @nocgmitf */
  /**
  * operator =
  * @param iTopDomainGraph
  *   iTopDomainGraph to copy
  */
  CATTopDomainGraph& operator = (const CATTopDomainGraph& iTopDomainGraph);

  /** @nodoc @nocgmitf */
  /**
  * param ctor
  * @param iListOfInputBodies 
  *    List of Input Bodies 
  * @param piOutputBody 
  *    the output body obtained from the givent input bodies
  * @param piCGMJournalList 
  *    the journal of cells that describe how cells of the result body 
  *    were built from cells of the input bodies
  */
  CATTopDomainGraph(CATLISTP(CATBody) &iListOfInputBodies,CATBody *piOutputBody, CATCGMJournalList *piCGMJournalList);

  /** @nodoc @nocgmitf */
  //DATA

  CATBody*									_piOutputBody;
  CATLISTP(CATBody)						_iListOfInputBodies;
  CATCGMJournalList*					_piCGMJournalList;

  CATTopHashTableOfDomainNode*		_pGraphOfDomainNode;
  CATCGMHashTable*					_pTmpHashTableOfTrickyDomainNode;
  CATBoolean								_IsJournalGetted;
  CATBoolean							_IsCGMJournalOfCellsEmpty;

  CATCGMJournalList*					_poJournalOfDomains;

  CATTopDomainTracker*				   _pTopDomainTracker;

  //CATLISTP(CATDomain) _ListOfTrickyOutputDomain;
  CATCGMHashTableWithAssoc *		_pHashTableOfDomainWithItCells;
  CATCGMHashTable *					_pHashTableOfTrickyInputDomain;
  CATCGMHashTable *					_pHashTableOfTrickyOutputDomain;

  CATLISTP(CATDomain) _ListOfInputDomain;
  CATLISTP(CATDomain) _ListOfOutputDomain;
  CATBoolean _IsInputAndOutputBodiesWithIdenticalDomains;
  CATBoolean _NoDomainsInInputBodies;
  CATBoolean _NoDomainsInOutputBody;
};


#endif 
