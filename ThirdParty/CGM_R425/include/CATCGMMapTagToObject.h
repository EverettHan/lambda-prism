#ifndef CATCGMMapTagToObject_H
#define CATCGMMapTagToObject_H
// COPYRIGHT DASSAULT SYSTEMES  2002
/** 
 * Utilitaire Table d'association Old Tag --> New Object
 */
#include "CATCGMMapCATULONGPTR.h"

class CATCGMContainer;

class  CATCGMMapTagToObject  : public CATCGMMapCATULONGPTR
{
public:
  CATCGMMapTagToObject(CATCGMContainer *reference, unsigned int initialNumber = 0);
  virtual ~CATCGMMapTagToObject();
  CATCGMNewClassArrayDeclare;

  void AddRef();
  void Release();

protected :
  CATCGMContainer *_Container;
  int _UseCount;
};

#endif

