#ifndef	CATICGMObjectHashTable_h
#define	CATICGMObjectHashTable_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

class CATICGMObject ;
#include  "YP0LOGRP.h"
/** 
* @nodoc
* @deprecated V5R14
*/
class ExportedByYP0LOGRP  CATICGMObjectHashTable
{
public:
  /**
   * @nodoc
   * @deprecated V5R14
   */
  virtual CATICGMObject*  KeyInterfaceLocate   (int iTag) const = 0;

  /**
   * @deprecated V5R14
   */
  CATICGMObjectHashTable() {};

  /**
   * @nodoc
   * @deprecated V5R14
   */
  CATICGMObjectHashTable(const CATICGMObjectHashTable & iTableToCopy)  {};
  virtual ~CATICGMObjectHashTable() {};
};
#endif
