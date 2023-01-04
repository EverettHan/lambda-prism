#ifndef ListPOfListPOfCATConnectedCellsIterator_h
#define ListPOfListPOfCATConnectedCellsIterator_h

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "ListPOfCATConnectedCellsIterator.h"
//
// clean previous functions requests
#include "CATLISTPP_Clean.h"
//
/** 
 * @collection CATLISTP(ListPOfCATConnectedCellsIterator)
 * Collection class for pointers to iterators on the connected cells.
 * Only the following methods of pointer collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li> 
 * <li><tt>Size</tt></li>
 * <li><tt>ReSize</tt></li> 
 * <li><tt>AppendList</tt></li>
 * <li><tt>InsertAt</tt></li> 
 * <li><tt>Locate</tt></li> 
 * <li><tt>RemovePosition</tt></li> 
 * <li><tt>RemoveAll</tt></li> 
 * </ul>
 * Refer to the articles dealing with collections in the encyclopedia. 
*/
#define CATLISTPP_Append
#define CATLISTPP_Size
#define CATLISTPP_ReSize
#define	CATLISTPP_AppendList
#define	CATLISTPP_InsertAt
#define	CATLISTPP_Locate
#define	CATLISTPP_RemovePosition
#define	CATLISTPP_RemoveAll
//
// generate interface of collection class
//
// get macros
#include "CATLISTPP_Declare.h"
//
// generate interface of collection class
// (functions declarations)
#include "CATGMModelInterfaces.h"
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces
CATLISTPP_DECLARE_TS(ListPOfCATConnectedCellsIterator, 10)
typedef CATLISTP(ListPOfCATConnectedCellsIterator) ListPOfListPOfCATConnectedCellsIterator;

#endif
