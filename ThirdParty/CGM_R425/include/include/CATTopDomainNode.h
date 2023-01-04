#ifndef CATTopDomainNode_H
#define	CATTopDomainNode_H

//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2013
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
//	Class			:		CATTopDomainNode
//	Creation		:		24/05/2013
//
//
//	Synopsis	:	Header class of CATTopDomainNode.
//					
//	
//
//
//	Authors		:  KY1
//-----------------------------------------------------------------------------


class CATBody;
class CATCGMJournalList;
class CATTopDomainTracker;

#include "CATCGMNewArray.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "ListPOfCATTopDomainNode.h"
#include "CATTopJournalOfDomainTypeDef.h"
#include "CATDomain.h"
#include "CATCGMOutput.h"


class CATCGMHashTable;

/** @nodoc @nocgmitf */
/**
* Class to manage a node domain in the context of a graph node "CATTopDomainGraph" 
* Class used to construct nodes of the the graph of domains
* Graph of domains is used to deduce the Journal of Domains
* 
* 
*
* 
*/

class   CATTopDomainNode
{
public:

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	/**
	* creation method
	* @param iListOfCells 
	*   Cells List to transpose in a CATTopDomainNode
	*/
	static CATTopDomainNode *CreateCATTopDomainNode(CATDomain *piDomain,CATTopDomainNodeOriginKind iDomainFromWhere);

	/** @nodoc @nocgmitf */
	/**
	* destructor
	*/
	virtual ~CATTopDomainNode();

	/** @nodoc @nocgmitf */
	/**
	* Get the Domain refrenced by the CATTopDomainNode
	* @return
	*   type the Domain 
	*/
	INLINE  CATDomain *								GetDomain();
		
	/** @nodoc @nocgmitf */
	/**
	* Get the type of the Domain : Lump, Shell, Wire, ...
	* @return
	*   type of Construction of the Domain 
	*/
	INLINE  int 										GetTypeOfDomain();

	/** @nodoc @nocgmitf */
	/**
	* Get to which kind of body, the domain belongs : input, output or both, ...
	* @return
	*   to which kind of body the domain belongs
	*/
	INLINE  CATTopDomainNodeOriginKind						GetOriginKindOfDomainNode();
	
	/** @nodoc @nocgmitf */
	/**
	* Get the type of Construction of the Domain : Has been created, modified or deleted
	* @return
	*   type of Construction of the Domain 
	*/
	INLINE CATTopDomainTypeOfConstruction		GetTypeOfConstruction();

	/** @nodoc @nocgmitf */
	/**
	* Set how the domain has been built : creation, deletion, modification
	* 
	* @param iTypeOfConstruction
	*    Type of construction
	*/
	INLINE void											SetTypeOfConstruction(CATTopDomainTypeOfConstruction iTypeOfConstruction);

	/** @nodoc @nocgmitf */
	/**
	* Get the the flag status	
	* @return
	*   flag status
	*/
	INLINE CATBoolean									GetFlagStatus();

	/** @nodoc @nocgmitf */
	/**
	* Set the flag status
	* 
	* @param iFlagStatus
	*    value of flag status
	*/
	INLINE void											SetFlagStatus(CATBoolean iFlagstatus);

	/** @nodoc @nocgmitf */
	/**
	* Get list of ascendant domains
	* @return
	*    list of ascendant domains
	*/
	INLINE ListPOfCATTopDomainNode&	  	      GetListOfAscendantDomain();

	/** @nodoc @nocgmitf */
	/**
	* Get list of descendant domains
	* @return
	*    list of descendant domains
	*/
	INLINE ListPOfCATTopDomainNode&	  			GetListOfDescendantDomain();
	
	/** @nodoc @nocgmitf */
	/**
	* Compute descendant(s) of the domain int the result body given as input argument.
	* Could be Null.
	* 
	* @param
	*   piCGMJournalList CGM Journal of Cells that back tack input cells in the Result body
	*   given as second argument
	*
	* @param
	*   piOutputBody Result body in which the ascendant domain is retrieved
	*   
	* @return
	*   <dl>
	*	 <dt><tt>S_OK</tt>		<dd>if Computation is succedded
	*	 <dt><tt>E_FAIL</tt>    <dd>otherwise
	*	 </dl>
	*/
	//HRESULT												ComputeDescendantsDomains(CATTopDomainTracker*	_pTopDomainTracker);

	/** @nodoc @nocgmitf */
	/**
	* Add ascendant DomainNode to this 
	* 
	* @param
	*   piTopDomainNode the ascendant DomainNode
	*/
	void													AddAscendant(CATTopDomainNode *piTopDomainNode);
	
	/** @nodoc @nocgmitf */
	/**
	* Add descendant DomainNode to this 
	* 
	* @param
	*   piTopDomainNode the descendant DomainNode
	*/
	void													AddDescendant(CATTopDomainNode *piTopDomainNode);
  
  /**
	* Test if the Domain has create a Domain
	*/
  CATBoolean	                  IsCreatedADomain();

  /**
	* Test if the Domain as modifies into one or several domains 
	*/
	CATBoolean										IsModifiedInto();
  

  /**
	* Set the input domain to be deleted
	* 
  * @param iOption
  *   Tune the Flag to dedicated flag TRUE or FALSE
	*/
  void                          ToDelete(CATBoolean iOption);

  /**
	* Is the domain has to be deleted
	*/
  CATBoolean                    HasToBeDeleted();

  /**
  * Set the input domain as he creates a domain
  * 
  * @param iOption
  *   Tune the Flag to dedicated flag TRUE or FALSE
  */
  void                        SetCreatedADomain(CATBoolean iOption);

  /**
  * Set the input domain as he modifies a domain
  * 
  * @param iOption
  *   Tune the Flag to dedicated flag TRUE or FALSE
  */
  void                        SetModifiedIntoDomain(CATBoolean iOption);
  

  
	/**
	* Set the list of the Cells belonging to an input Domain that Haven't been deleted or Not lead to creatioon or modifcation event
	* 
	* @param
	*   ioListOfNonDeletedCells the list to set
	*/
	void													SetListOfNonDeletedCells(CATLISTP(CATCell) &ioListOfNonDeletedCells);

	/**
	* Get the Cells belonging to an input Domain that Haven't been deleted or Not lead to creation or modifcation event
	* 
	* @param
	*   pioHashTabOfNonDeletedCells the collection of requested cells 
	*/
	void													GetNonDeletedCells(CATCGMHashTable *& pioHashTabOfNonDeletedCells);

	/** @nodoc @nocgmitf */
	/**
	* Test the equality between two CATTopDomainNode
	*	  @param
	*    iTopDomainNode CATTopDomainNode to compare with this
	* @return
	*	  <dl>
	*	  <dt><tt>0</tt>		<dd>if the sets contains the same cells
	*	  <dt><tt>1</tt>        <dd>if the sets are not equal
	*	  </dl>
	*/
	int													IsEqual(CATTopDomainNode *piTopDomainNode);

	/** @nodoc @nocgmitf */
	/**
	* Computes the HashKey of the CATTopDomainNode
	* @return
	*    a hash key of this
	*/
	CATULONG32											HashKey();

	/** @nodoc @nocgmitf */
	/** LifeCycle protection  */
	INLINE unsigned short							AddRef();

	/** @nodoc @nocgmitf */
	INLINE unsigned short							Release();

   /** @nodoc @nocgmitf */
   void Dump(CATCGMOutput& ioCGMStr, int depth = 1);

private: 

	/**
	* default ctor
	*/
	CATTopDomainNode ();

	/**
	* copy ctor
	* @param iTopDomainNode
	*   iTopDomainNode to copy
	*/
	CATTopDomainNode (const CATTopDomainNode& iTopDomainNode);

	/**
	* operator =
	* @param iTopDomainNode
	*   iTopDomainNode to to copy
	*/

	CATTopDomainNode& operator = (const CATTopDomainNode& iTopDomainNode);

	/**
	* param ctor
	* * @param iListOfCells 
	*   Cells List to transpose in a CATTopDomainNode
	*/
	CATTopDomainNode (CATDomain *piDomain,CATTopDomainNodeOriginKind iDomainFromWhere);

    //----
	//DATA
	//----
	CATDomain*									      _piDomain;
	ListPOfCATTopDomainNode						_oListOfAscendantDomains;
	ListPOfCATTopDomainNode						_oListOfDescendantDomains;

	CATTopDomainNodeOriginKind				_iDomainFromWhere;
	CATTopDomainTypeOfConstruction		_oTypeOfConstruction;
	CATBoolean									      _FlagStatus; 
  CATBoolean                        _HasToBeDeleted;

  CATBoolean                        _IsCreatedADomain;     //Est ce que le domain a permis de crée un autre domaine
  CATBoolean                        _IsModifiedIntoDomain;  //Est ce que le domain a permis de modifier un autre domaine

	CATLISTP(CATCell)							    _ListOfNonDeletedCells;

	/** LifeCycle */
	unsigned int								      _Counter;

};


INLINE  unsigned short CATTopDomainNode::AddRef()
{ 
	return ++_Counter; 
}

INLINE  unsigned short CATTopDomainNode::Release()
{ 
	unsigned short rc = --_Counter; 
	if ( 0 == rc ) delete this; 
	return rc; 
}


INLINE  CATDomain *CATTopDomainNode::GetDomain()
{
	return _piDomain;
}

INLINE int		CATTopDomainNode::GetTypeOfDomain()
{
	if (!_piDomain) return -1;
	if (_piDomain->IsATypeOf(CATLumpType))
	{
		return CATLumpType;
	}
	else if (_piDomain->IsATypeOf(CATShellType))
	{
		return CATShellType;
	}
	else if (_piDomain->IsATypeOf(CATWireType))
	{
		return CATWireType;
	}
	else
	{
		return -1;
	}
}

INLINE CATBoolean	CATTopDomainNode::GetFlagStatus()
{
	return _FlagStatus;
}

INLINE void CATTopDomainNode::SetFlagStatus(CATBoolean iFlagStatus)
{
	_FlagStatus = iFlagStatus;
}

INLINE  CATTopDomainNodeOriginKind	CATTopDomainNode::GetOriginKindOfDomainNode()
{
	return _iDomainFromWhere;
}
INLINE CATTopDomainTypeOfConstruction		CATTopDomainNode::GetTypeOfConstruction()
{
	return _oTypeOfConstruction;
}

INLINE void		CATTopDomainNode::SetTypeOfConstruction(CATTopDomainTypeOfConstruction iTypeOfConstruction)
{
	_oTypeOfConstruction = iTypeOfConstruction;
}

INLINE ListPOfCATTopDomainNode&		CATTopDomainNode::GetListOfAscendantDomain()
{
	return _oListOfAscendantDomains;
}

INLINE ListPOfCATTopDomainNode&		CATTopDomainNode::GetListOfDescendantDomain()
{
	return _oListOfDescendantDomains;
}


#endif 
