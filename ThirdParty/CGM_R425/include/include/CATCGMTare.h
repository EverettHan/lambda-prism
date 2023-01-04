/* -*-c++-*- */
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//-----------------------------------------------------------------------------
// Usage :Simulate rough overweigth disk size for PCS criteria
// November 2009 : TCX
//=============================================================================
#ifndef CATCGMTare_H
#define CATCGMTare_H
#include "CATCGMStreamAttribute.h"                                 
#include "CATDataType.h"


class ExportedByYP0LOGRP CATCGMTare : public CATCGMStreamAttribute
{
public :
  // Definition of the attribute (constructor, destructor, stream etc...)
  CATCGMTare();
  ~CATCGMTare();

  CATCGMNewClassArrayDeclare;

  CATCGMDeclareAttribute (CATCGMTare,CATCGMStreamAttribute);

  virtual void Stream   (CATCGMStream&) const;
  virtual void UnStream (CATCGMStream&);
 
private :
  CATCGMTare(const CATCGMTare&);
  CATCGMTare& operator = (const CATCGMTare&);

  CATLONG32       _MemoryLength;
  unsigned char * _MemoryTare;
};

#endif
