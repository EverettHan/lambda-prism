/* -*-c++-*- */

/**
 * @COPYRIGHT DASSAULT SYSTEMES 2005
 */

#ifndef CATCGMSortableAttribute_H_
#define CATCGMSortableAttribute_H_

//=============================================================================
// CATCGMSortableAttribute
//=============================================================================
// Jan. 10	Creation                                                      VUC
//=============================================================================
#include "ExportedByCATCGMFusion.h"

class CATCGMStreamAttribute;

/**
 *  Class used for sorting attributes, because they don't have any sortable attributes
 */
class ExportedByCATCGMFusion CATCGMSortableAttribute 
{
 public:

     /**
  * Constructs CATCGMSortableAttribute for stream operation (read and write acces are allowed).
  */
  CATCGMSortableAttribute(CATCGMStreamAttribute* iStreamAttributeToSort);

  virtual ~CATCGMSortableAttribute();

  void SetBuffer();

  void GetBuffer(char*& obuffer,int& olength);
  CATCGMStreamAttribute* GetAttribute();

  int Compare(CATCGMSortableAttribute* AttributeToCompare);

  CATCGMStreamAttribute* _Attribute;

  //buffer which will define the sort
  char *_buffer;
  int _length;

};

#endif

