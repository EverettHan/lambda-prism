//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
//
// CATOffsetOperator :
//   Class for creating offsets of surfaces.
//
//=============================================================================
// Usage notes:
//
//
//=============================================================================


#ifndef CATOffsetOperator_H
#define CATOffsetOperator_H 

#include "Y30C3XGG.h"

#include "CATGeoOperator.h"
#include "CATSurLimits.h"

#include "CATString.h"
#include "CATGeoOpTimer.h"

class CATSurface;
class CATGeoFactory;
class CATSoftwareConfiguration;



class ExportedByY30C3XGG CATOffsetOperator : public CATGeoOperator
{

  CATCGMVirtualDeclareClass(CATOffsetOperator);
  public :

  //-----------------------------------------------------------------------
  //- Object Management
  //-----------------------------------------------------------------------

/**
 * Use the global function CATCreateOffsetOperator (described below) instead.
 */
  CATOffsetOperator (CATGeoFactory* iFactory);


/**
 * Use the global function Remove (described below) instead.
 */
  virtual ~CATOffsetOperator ();
    

  //-----------------------------------------------------------------------
  //- Settings
  //-----------------------------------------------------------------------

/**
 * Enables or disables the possibility of cutting the result surface.
 * Default is OFF.
 * If ON, you must specify the rules for cutting with SetApproxMode (described below).
 * You can also specify limits for cutting. If the result consists of several surfaces,
 * the only surfaces returned by the operator will be those that intersect this zone.
 */
  virtual void SetCuttingMode (CATLONG32 iEnable = 1, CATSurLimits * iCuttingZone = NULL) = 0;

/**
 * Activates the approximation mode.
 * If CuttingMode is ON, the operator will cut the result whenever a discontinuity is encountered.
 * If CuttingMode is OFF, the result will be given as a single nurbs only if this is possible.
 * (Otherwise, a CATProcOffsetSurface will be constructed).
 *    iContinuityLevelForCutting = the minimum continuity level (above this level, the result will be cut
 *         if you have enabled this possibility).
 *    iContinuityLevelForPatches = the continuity level required for the result surface(s).
 * Default behaviour is no approx (Except for some particular cases).
 */
  virtual void SetApproxMode (double iMaxDeviation,
                              CATLONG32 iContinuityLevelForCutting, CATLONG32 iContinuityLevelForPatches = -1) = 0;


  //-----------------------------------------------------------------------
  //- Run the algorithm
  //-----------------------------------------------------------------------

/**
 * Run the operator and creates the result in the factory.
 * Defined in mother class.
 */
  // virtual int Run();


  //-----------------------------------------------------------------------
  //- Get result after run
  //-----------------------------------------------------------------------

/**
 * Provides a diagnosis.
 * -1 - No run done.
 *  0 - An unexpected error has occured.
 *  1 - Success : the result could have been created in the required mode.
 *  2 - Success, but a proc offset has been created because the approximation failed.
 */
  virtual CATLONG32 GetDiagnostic () = 0;

/**
 * Provides the number of result(s), and the arrays of cutting parameters.
 * These arrays will be deleted by the destructor.
 * GetNumberOfResult is equal to the product (NbBreakU + 1) * (NbBreakV + 1).
 */
  virtual CATLONG32 GetNumberOfResult () = 0;
  virtual void GetNumberOfCuts (CATLONG32 & oNbBreakU, CATLONG32 & oNbBreakV) = 0;
  virtual void GetCuttingParams (double *& ParamsU, double *& ParamsV) = 0;

/**
 * In the case where there is only one, provides the result surface.
 * A CATOffsetSurface will be given, linking the input surface.
 */
  virtual void GetResult (CATSurface *& oSurface) = 0;

/**
 * In the case where there is only one, provides the result surface.
 * A geometric representation will be given (no link with the basic input surface).
 */
  virtual void GetResultRep (CATSurface *& oSurface) = 0;

/**
 * In all cases, provides a bidimensional array of pointers on the result surfaces.
 * The given surfaces are of kind CATOffsetSurface, linking the (same) input surface.
 * The array will be deleted by the destructor.
 */
  virtual void GetResults (CATSurface ***& oTab) = 0;

/**
 * In all cases, provides a bidimensional array of pointers on the result surfaces.
 * The given surfaces are only geometric representations, and are not linked to the
 * input surface.
 * The array will be deleted by the destructor.
 */
  virtual void GetResultReps (CATSurface ***& oTab) = 0;

};




/**
 * Creates an instance of a CATOffsetOperator.
 *  iRequiredMaxLimits = the max limits imposed on the offset result surface.
 *    They must be contained inside the max limits of the input surface.
 *    The actual max limits of the result will CONTAIN these ones.
 *    Default is max limits of input.
 */
ExportedByY30C3XGG CATOffsetOperator * CATCreateOffsetOperator (CATGeoFactory                * iFactory,
                                                                CATSoftwareConfiguration     * iConfig,
                                                                CATSurface                   * iSurfaceToOffset,
                                                                const double                   iOffsetValue,
                                                                CATSurLimits                 * iRequiredMaxLimits = 0);

/**
 * Removes an instance of a CATOffsetOperator created by CATCreateOffsetOperator.
 * The caller must set the pointer to NULL after the call.
 */
ExportedByY30C3XGG void Remove (CATOffsetOperator * OffsetOper);

#endif
