
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2010
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
//	Class		   :		CATCXHashTableOfExplicitReport
//	Creation	   :		11/22/2013
//
//
//	Synopsis	:	Header class of CATCXHashTableOfExplicitReport. It allows handle of a collection of CATCXReport
//	
//
//
//	Authors		:  AAD + KY1 +TCX
//-----------------------------------------------------------------------------
//18/08/2010 Class creation
//-----------------------------------------------------------------------------

#ifndef CATCXHashTableOfExplicitReport_H
#define	CATCXHashTableOfExplicitReport_H

#include "CATCGMHashTable.h"


class CATExplicitReport;

/**
* @nodoc
*/
/**
* Class representing a Hast Table of CATExplicitReport Objects.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* Do not use the @href CATCGMUnsmartList constructor to
* do such and such but instead...
*
* @example
*  // example is optional
*  pHT_ExplicitReport = new CATCXHashTableOfExplicitReport(33);
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/

class CATCXHashTableOfExplicitReport : public CATCGMHashTable
{
public :
   CATCXHashTableOfExplicitReport(int iEstimatedSize = 0);  
   ~CATCXHashTableOfExplicitReport();
   CATCGMNewClassArrayDeclare;

   int                  Insert(CATExplicitReport* piExplicitReport);
   CATExplicitReport*   Locate(CATExplicitReport* piExplicitReport) const;
   int                  Remove(CATExplicitReport* piExplicitReport);
};

#endif

