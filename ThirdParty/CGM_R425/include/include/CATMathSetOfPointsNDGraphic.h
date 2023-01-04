// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathSetOfPointsNDGraphic
// Set of points in dimension N>=1 used as an Algorithm Checker
//
//=============================================================================

#ifndef CATMATHSETOFPOINTSNDGRAPHIC_H
#define CATMATHSETOFPOINTSNDGRAPHIC_H

#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathDefGraphic.h"
#include "CATMathSetOfPointsND.h"

class ExportedByYN000FUN CATMathSetOfPointsNDGraphic :
      public CATMathSetOfPointsND
{
 public:
  //---------------------------------------------------------------------------
  // Object Management: all other methods are inherited
  //---------------------------------------------------------------------------

  CATMathSetOfPointsNDGraphic ( const CATLONG32 iN, const CATLONG32 iNumberOfPoint )
  : CATMathSetOfPointsND ( iN, iNumberOfPoint ) {}

  CATMathSetOfPointsNDGraphic ( const CATMathSetOfPointsND & iCopy )
  : CATMathSetOfPointsND ( iCopy ) {}

  //---------------------------------------------------------------------------
  // Analysis methods
  // WARNING: don't mix AlgoChecker and PixelChecker under the same identifier
  //---------------------------------------------------------------------------

  // Graphic debug: independant display of 2D functions with automatic viewing
  // iMode              :  display modes, may be combined by '|'
  //                       CAT_POLYLINE, CAT_POLYMARKER, CAT_POLYVECTOR 
  //                       CAT_SYMMETRIC    origin centered
  //                       CAT_PROPORTIONAL || CAT_SEMI_LOG
  //                       CAT_NONE         no display
  //                       CAT_AUTO         no interactive
  //                       CAT_KEEP         no chart file destroy
  //                       CAT_PAPER        white backcolor
  // IsLast             :  CAT_IS_LAST || CAT_IS_NOT_LAST
  //                       identifying the last chart
  // Appli              :  identifier on 4 characters max for a charts set
  // iZoom              :  global zoom ratio
  // iExtent            :  extended window ratio (doesn't affect the drawing)
  // iFirst and iSecond :  1st and 2nd components (X and Y axes)

  void AlgoChecker ( const CATLONG32 iMode  = CAT_POLYLINE | CAT_PROPORTIONAL |
                                         CAT_KEEP,
                     const CATLONG32 IsLast = CAT_IS_LAST,
                     const char *Appli = "MyCv",
                     const double iZoom = 1., const double iExtent = 1.,
                     const CATLONG32 iFirst = 0,   const CATLONG32 iSecond = 1 );

  // Pixel array independant display with automatic viewing
  // Hint: a 1st call with 2 pixels at opposite corners of the bounding box
  // Different calls to this method with the same identifier must define
  // disjoined areas, when their mode implies CAT_PIXEL_ARRAY
  // When CAT_PIXEL_ARRAY is not specified, isolated pixels are displayed
  //
  // iColors            :  colors coded in 0x00BBGGRR mode
  //                       ( red + 256 * green + 256 * 256 * blue )
  //                       numbered like the points
  // iMode              :  display modes, may be combined by '|'
  //                       CAT_PIXEL_ARRAY  pixel array
  //                       CAT_SYMMETRIC    origin centered
  //                       CAT_NONE         no display
  //                       CAT_AUTO         no interactive
  // IsLast             :  CAT_IS_LAST || CAT_IS_NOT_LAST
  //                       identifying the last pixel subset
  // Appli              :  identifier on 4 characters max for a pixel set
  // iZoom              :  global zoom ratio
  // iExtent            :  extended window ratio (doesn't affect the drawing)
  // iFirst and iSecond :  1st and 2nd components (X and Y axes)

  void PixelChecker ( CATMathSetOfLongs & iColors,
                      const CATLONG32 iMode  = CAT_POLYMARKER,
                      const CATLONG32 IsLast = CAT_IS_LAST,
                      const char *Appli = "Pixy",
                      const double iZoom = 1., const double iExtent = 1.,
                      const CATLONG32 iFirst = 0,   const CATLONG32 iSecond = 1 );

 private:
  // common launch utility for AlgoChecker and PixelChecker

  void Launcher ( CATMathSetOfLongs * ipColors,
                  const CATLONG32 iMode,   const CATLONG32 IsLast,
                  const char *Appli,
                  const double iZoom, const double iExtent,
                  const CATLONG32 iFirst,  const CATLONG32 iSecond );
};
#endif
