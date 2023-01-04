#ifndef	CATTopHashTableOfDomainNode_H
#define	CATTopHashTableOfDomainNode_H
// COPYRIGHT DASSAULT SYSTEMES  2013

//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2013
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
//	Class			:		CATTopHashTableOfDomainNode
//	Creation		:		24/05/2013
//
//
//	Synopsis	:	Header class of CATTopHashTableOfDomainNode. 
//             
//	
//
//
//	Authors		:  KY1
//-----------------------------------------------------------------------------

#include "CATCGMNewArray.h"
#include "CATCGMHashTable.h"


class CATTopDomainNode;


/** @nodoc @nocgmitf */
/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* Do not use the @href CATTopHashTableOfDomainNode constructor to
* do such and such but instead...
*
* @example
*  // example is optional
*  pObject = new CATTopHashTableOfDomainNode;
*  pObject->SetXXX(...);
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/

class   CATTopHashTableOfDomainNode : public CATCGMHashTable
{
public :
	CATCGMNewClassArrayDeclare;

   /** @nodoc @nocgmitf */
	CATTopHashTableOfDomainNode(int iEstimatedSize = 0);  
   /** @nodoc @nocgmitf */
	virtual ~CATTopHashTableOfDomainNode();
	/** @nodoc @nocgmitf */
	int                 Insert(CATTopDomainNode* piTopDomainNode);
   /** @nodoc @nocgmitf */
	CATTopDomainNode*   Locate(CATTopDomainNode* piTopDomainNode) const;
   /** @nodoc @nocgmitf */
	int                 Remove(CATTopDomainNode* piTopDomainNode);
};


#endif


