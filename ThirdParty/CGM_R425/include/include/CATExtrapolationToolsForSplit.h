#ifndef CATExtrapolationToolsForSplit_h
#define CATExtrapolationToolsForSplit_h
//=============================================================================
// Interface Class to check whether  it is necessary to extrapolate the splitting body (_SkinBody, a shell)
// for split and DOCO so that's it's large enough to completely cut the body to split (_SolidBody) and to 
// do the extrapolation.
//
// The set methods are used to preserve behaviour for split and DOCO in January 2017 at level 
// 6192 after refactoring.
//=============================================================================
//
// 27/01/2017  G5S  Interface created.  Implementation moved to TopologicalOperators\BONEWOPE.m\src\
//                  CATExtrapolationToolsForSplitImp.cpp. 
// 02/02/2017  G5S  Make CATExtrapolationToolsForSplit into an operator with an extensible.
//                  Create function now defined in 
//                  TopologicalOperators\BONEWOPE.m\src\CATExtrapolationToolsForSplitImp.cpp.
// 07/02/2017  G5S  Use enums for extrapolation mode and limit.
// 15/02/2017  G5S  Remove two options for preserving old behaviour because it is preserved by the extrapolation
//                  limit because split supports ThruNextConnected and DOCO supports BODYBOUNDINGBOX.
// 24/02/2017  G5S  If we have a plane and we use bounding box extrapolation, create a body from the surface. In 
//                  that case, for a split operation, we might have to invert the side we select.
//=============================================================================
#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "CATTopOperator.h"
#include "CATDynExtrapolationToolsDef.h"

class ExportedByCATTopologicalObjects CATExtrapolationToolsForSplit : public CATTopOperator
{
public:
  // Default: FALSE
  // If we set this to TRUE, don't extrapolate if for any faces Face->GetInfinite() == TRUE.
  virtual void SetInitialCheckForInfiniteFaces (CATBoolean iInitialCheckForInfiniteFaces) = 0;

  // Default: TRUE
  // If TRUE, handle the error thrown when trying to get the boundary during the algorithm 
  // if the input shell is closed.  
  virtual void SetCatchClosedShellError (CATBoolean iCatchClosedShellError) = 0;
  
  // Whether we must invert the side we select for a split.  This can happen if we have a planar body with
  // infinite extrapolation and we create a new body from the surface.
  virtual CATBoolean GetMustInvertSelectionSide() = 0;

  virtual ~CATExtrapolationToolsForSplit();

protected:
  CATExtrapolationToolsForSplit(CATGeoFactory * iGeoFactory, CATTopData * iData, CATExtTopOperator* iExtensible);
};

CATExtrapolationToolsForSplit * CATCreateExtrapolationToolsForSplit(CATGeoFactory            * iFactory,
                                                                    CATTopData               * iTopData,
                                                                    CATBody                  * iSkinBody,
                                                                    CATBody                  * iSolidBody,
                                                                    CATDynExtrapolationMode    iExtrapolationMode, 
                                                                    CATDynExtrapolationLimit   iExtrapolationLimit);

#endif
