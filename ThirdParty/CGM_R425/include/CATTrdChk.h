/* -*-C++-*- */
#ifndef CATTrdChk_H
#define CATTrdChk_H
// COPYRIGHT DASSAULT SYSTEMES 2014

//===================================================================
//===================================================================
//
// CATTrdChk: Class dedicated to check a transformation  
//
//===================================================================
//===================================================================
// April 2014    Creation                         R. Rorato
//===================================================================

#include "CATCGMVirtual.h"
#include "CATBoolean.h"

class CATMathTransformation;

class CATTrdChk : public CATCGMVirtual 
{
public:

  //------------------------------------------------------------------------------
  // Check a transformation
  //------------------------------------------------------------------------------
  virtual CATBoolean Check(CATMathTransformation &iTransfo) = 0;
};

#endif
