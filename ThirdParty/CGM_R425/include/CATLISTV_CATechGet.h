
/**
 * @level Protected
 * @usage U1
 */

/* -*-c++-*- */
#ifndef CATLISTV_CATechGet_H_
#define CATLISTV_CATechGet_H_

// COPYRIGHT DASSAULT SYSTEMES 1999
/**
 * @collection CATLISTV(CATechGet_var)
 * Collection class for specobjects.
 * Only the following methods of handler collection classes are available:
 * @fullReview LPU FOC 14/12/01
 * <ul>
 * <li><tt>Append</tt></li>
 * <li><tt>AppendList</tt</li>
 * <li><tt>InsertAt</tt</li>
 * <li><tt>Locate</tt</li>
 * <li><tt>eqOP</tt</li>
 * <li><tt>neOP</tt</li>
 * <li><tt>RemoveValue</tt</li>
 * <li><tt>RemovePosition</tt</li>
 * <li><tt>RemoveAll</tt</li>
 * <li><tt>RemoveDuplicatesCount</tt</li>
 * <li><tt>ReSize</tt</li>
 * <li><tt>QuickSort</tt</li>
 * </ul> 
 * Refer to the articles dealing with collections in the encyclopedia.
 */

#include "ExportedByCATTechTools.h"

#include "CATechGet.h"
class CATechGet_var;
 
#include "CATLISTHand_Clean.h"

#define  CATLISTHand_Append
#define  CATLISTHand_AppendList
#define  CATLISTHand_InsertAt
#define  CATLISTHand_Locate
#define  CATLISTHand_eqOP
#define  CATLISTHand_neOP
#define  CATLISTHand_RemoveValue
#define  CATLISTHand_RemovePosition
#define  CATLISTHand_RemoveAll
#define  CATLISTHand_RemoveDuplicatesCount
#define  CATLISTHand_ReSize
#define  CATLISTHand_QuickSort

#include "CATLISTHand_Declare.h"

#undef	CATCOLLEC_ExportedBy
#define	CATCOLLEC_ExportedBy	ExportedByCATTechTools

CATLISTHand_DECLARE( CATechGet_var )
 
#endif
