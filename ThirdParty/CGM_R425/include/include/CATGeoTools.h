/* -*-C++-*- */
#ifndef CATGeoTools_H
#define CATGeoTools_H

// COPYRIGHT DASSAULT SYSTEMES 1998

//-----------------------------------------------------------------------------
//
// CATGeoTools
// -----------
//  Geometrical Basic Services 
//  do not instanciate this class
//
// Class for several utility services useful for performance improvement : 
//
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 16/09/09 FDS Creation
//-----------------------------------------------------------------------------

// ExportedBy
#include "Y30UIUTI.h"

// Data types
#include "CATBoolean.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATPointOnEdgeCurve;
class CATCurve;
class CATSurface;
class CATSurLimits;
class CATCrvParam;
class CATSurParam;

class ExportedByY30UIUTI CATGeoTools
{
public:

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Utilities about Confusions
  // - It can be too costly in terms of performances to create an operator, to run it and to get the result.
  // - In this case , the treatment can be replaced by  a single static service which can be either called by the run operation or
  // by a static service which is available in "CATGeoTools" class.
  // - A typical example is the point - point confusion operator which has a very efficient elimination criterion when 2 points are not confused.
  // - This operator had a very high cost just for creation and run infrastructure ( with CGMReplay test .... )
  // because it was called intensively by the other geometrical operators.
  // - By replacing it by a "CATGeoTools" service  , we had a very important performance improvment when updating canonical part
  // ( several % of total cost ).
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //----------------------------------------------------------------------------------------------------------
  // Static optimized Run for "ConfusionPtOnCrvPtOnCrv" ( avoid operator creation for simple operation )
  //----------------------------------------------------------------------------------------------------------
  static CATBoolean CATGetConfusion(      CATGeoFactory             * iFactory,
                                          CATSoftwareConfiguration  * iConfig,
                                    const CATPointOnEdgeCurve       * iPECrv1,
                                    const CATPointOnEdgeCurve       * iPECrv2,
                                    const CATCurve                  * iCrv,
                                    const double                      iTol);


  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Static optimized Run for "ConfusionPtOnCrvPtOnCrv" ( avoid operator creation for simple operation )
  // Note : "iControlParam" was added for compatibility because some check where done only in "CATCreateConfusion" and not in constructur when called directly
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  static CATBoolean CATGetConfusion(      CATGeoFactory            * iFactory,
                                          CATSoftwareConfiguration * iConfig,
                                    const CATCrvParam              & iParam1,
                                    const CATCrvParam              & iParam2,
                                    const CATCurve                 * iCrv,
                                    const double                     iTol,
                                    const int                        iControlParam = 1);

  //----------------------------------------------------------------------------------------------------------
  // Satic optimized Run for "ConfusionPtOnSurPtOnSur" ( avoid operator creation for simple operation )
  //----------------------------------------------------------------------------------------------------------
  static CATBoolean CATGetConfusion(      CATGeoFactory            * iFactory,
                                          CATSoftwareConfiguration * iConfig,
                                    const CATSurParam              & iParam1,
                                    const CATSurParam              & iParam2,
                                    const CATSurface               * iSurface,
                                    const double                     iTol);


  //----------------------------------------------------------------------------------------------------------
  // Satic optimized TryLinearConfusion for "ConfusionCrvCrv" ( avoid operator creation for simple operation )
  //----------------------------------------------------------------------------------------------------------
  
  static CATBoolean TryLinearConfusion(      CATGeoFactory * iFactory,
                                       const CATCurve      * crv1,
                                       const CATCurve      * crv2,
                                       const CATCrvParam   & Start1,
                                       const CATCrvParam   & End1,
                                       const CATCrvParam   & Start2,
                                       const CATCrvParam   & End2,
                                       const double          iTol,
                                       const short           CGMLevel);

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Utilities about Surfaces and Curves
  // Methods which adjust the scales for the mathematical solvers by taking into account the dimensions defining surfaces or curves (size, distance from the origin, ...).
  // If one of these characteristics has a precision around 1e6, the computation loses 6 orders of precision.
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Compute Scale : compute a scale to update numerical errors in solvers
  static double ComputeNumericalErrorScale(CATSoftwareConfiguration * iConfig, const CATSurface * iSurface, const CATSurLimits & iSurLim);

  static double ComputeNumericalErrorScale(CATSoftwareConfiguration * iConfig, const CATCurve * iCurve, const double w0, const double w1);

  // Detects curves with complex shapes, like helices.
  //Operators  like CATIntersectionCrvSurCx2 & CATConfusionCrvCrvCx2 take extra care with such curves.
  static CATBoolean IsComplexCurve(const CATCurve * iCurve);



  private:
  CATGeoTools();
  CATGeoTools(const CATGeoTools &);//Necessary to prevent unwanted automatic creation by compiler
  void operator = (const CATGeoTools &);

};


#endif
