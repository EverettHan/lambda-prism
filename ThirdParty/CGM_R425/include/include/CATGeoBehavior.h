/* -*-c++-*- */
#ifndef CATGeoBehavior_H
#define CATGeoBehavior_H
//============================================================================
//  Specifing Behavior from Geometric Modeler
//============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2002
//---------------------------------------------------
#include "ExportedByGeometricObjects.h"
#include "CATCGMNewArray.h"
#include "CATBoolean.h"
#include "CATMathInline.h"

class CATError;

//------------------------------------------------------------
// Liste des Comportements possibles
//------------------------------------------------------------
struct CATGeoBehaviorStatus
{
  unsigned int	ThrowOnError      :  1;
  unsigned int	PanelOnError      :  1;
  unsigned int	LogOnError        :  1;
  unsigned int	ExitOnError       :  1;
  unsigned int	CleanOnError      :  1;

  unsigned int	RFU               : 25;

  unsigned int	WithCheckUp       :  1;
  unsigned int	LogDiskBytes      :  1;
};

//------------------------------------------------------------
// Objet de definition du comportement 
//------------------------------------------------------------
class ExportedByGeometricObjects CATGeoBehavior
{
public :
  
  CATGeoBehavior();
  ~CATGeoBehavior();
  CATCGMNewClassArrayDeclare;  
  
  void Manage(CATError *iError);
  
  INLINE CATBoolean Cleaning() const;

  void Add(const CATGeoBehavior &iBehavior);
  void Remove(const CATGeoBehavior &iBehavior);

  CATGeoBehaviorStatus _ToDo;
};

//------------------------------------------------------------
// inlining ...
//------------------------------------------------------------
INLINE CATBoolean CATGeoBehavior::Cleaning() const
{
  return _ToDo.CleanOnError ? TRUE : FALSE;
}


#endif
