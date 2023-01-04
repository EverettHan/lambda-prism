//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : ZFC / LAP
//
// DESCRIPTION  : Class used to store general run options for Live Shape
//                Operators
//
//=============================================================================
// 28/01/09  ZFC  Creation
//=============================================================================

#ifndef CATGMLiveShapeRunOptions_H
#define CATGMLiveShapeRunOptions_H

#include "CATGMOperatorsInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATBoolean.h"

class ExportedByCATGMOperatorsInterfaces CATGMLiveShapeRunOptions : public CATCGMVirtual
{
public:
  /**
   * Constructor
   */
  CATGMLiveShapeRunOptions();

  /**
   * Destructor
   */
  virtual ~CATGMLiveShapeRunOptions();

  // ----------------------------
  // Set Methode for Application
  // ----------------------------
  // INTERRUPT WITH BEST RESULT
  // --------------------------
  // Call this methode with the interrupt methode SetParentProgressBar
  // For validation (last run), set iBestResultMode to false.
  // Default value : this mode is desactivate.
  // Warning : When the BestResult is return with the mode OnlyMovingFaces,
  // the returned journal do not contain the deletion order for performance reasons.
  // So in this case and in this case only, the journal is not valid.
  virtual void SetBestResultMode(CATBoolean iBestResultMode) = 0;

  // VALIDATION WITH BEST TIME COMSUMING
  // -----------------------------------
  // Call this methode only for validation.
  // Default value : this mode is desactivate.
  virtual void SetSameInputAsPreviousRun(CATBoolean iSameInputAsPreviousRun) = 0;

  // IMPLICITE TANGENCY FOR VARIATIONAL SOLVER
  // ------------------------------------------
  // Default behavior : KeepImplicitTangency is false.
  virtual void SetKeepImplicitTangency(CATBoolean iKeepImplicitTangency) = 0;

};

ExportedByCATGMOperatorsInterfaces CATGMLiveShapeRunOptions* CATCreateGMLiveShapeDefaultRunOptions();
ExportedByCATGMOperatorsInterfaces CATGMLiveShapeRunOptions* CATCreateGMLiveShapeRunOptionsForDeformPreview();

#endif /* CATPGMLiveShapeRunOptionsImpl_h_ */
