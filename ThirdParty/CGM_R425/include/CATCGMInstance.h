/* -*-C++-*- */

#ifndef CATCGMInstance_H
#define CATCGMInstance_H

// COPYRIGHT DASSAULT SYSTEMES 2006

//===================================================================
//===================================================================
//
// CATCGMInstance
//
// generic class for Collaborative Variational Modelling (CVM) log
//
//===================================================================


//===================================================================
// Usage notes:
//
//===================================================================

//===================================================================
// Dec. 2006    Creation                         Alex State
//===================================================================

#include "YP0LOGRP.h"
#include "CATBoolean.h"
#include "CATMathTransformation.h"
#include "CATCGMNewArray.h"
#include "CATCGMUnknown.h"

class ExportedByYP0LOGRP CATCGMInstance : public CATCGMUnknown
{
  //------------------------------------------------------------------------------
  // Pool allocation
  //------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;
  //------------------------------------------------------------------------------
  // Create a Instance
  //------------------------------------------------------------------------------
  public:
  static CATCGMInstance *Create(CATMathTransformation &iTransformation);

  //------------------------------------------------------------------------------
  // Constructor
  //------------------------------------------------------------------------------
  protected:
  CATCGMInstance();

  //------------------------------------------------------------------------------
  // Destructor
  //------------------------------------------------------------------------------
  protected:
  virtual ~CATCGMInstance();
  
  private:
  HRESULT SetTransformation (CATMathTransformation &iTransformation);
  
  public:
  HRESULT GetTransformation (CATMathTransformation &iTransformation);

  //------------------------------------------------------------------------------
  // Necessary to prevent unwanted automatic creation by compiler
  //------------------------------------------------------------------------------
  private:
  CATCGMInstance(const CATCGMInstance &);
  void operator = (const CATCGMInstance &);

  //------------------------------------------------------------------------------
  // Data
  //------------------------------------------------------------------------------
  private:
  CATMathTransformation  _Transfo;
  CATBoolean             _IsEmpty;
  
};
#endif
