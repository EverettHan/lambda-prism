/* -*-c++-*- */
#ifndef CATLoopOrientationOperator_h
#define CATLoopOrientationOperator_h
// COPYRIGHT DASSAULT SYSTEMES  1999
//=============================================================================
//
// CATOrientationLoopFaceOperator
// 
/**
 * This operator compute the counter - clockwise orientation of a loop in his face.
 *
 * - Return CATOrientationPositive if the loop has a counter - clockwise orientation
 * and CATOrientationNegative if the loop has a clockwise orientation in the face.
 *
 * - A valid outer loop must be counter-clockwise, and a valid inner loop must be 
 * clockwise). 
 * 
 * - If the loop is not valid , use the @href CATLoop#Invert method to fix it.
 * 
 * - This operator replace the CalcArea method of CATLoop.h 
 */ 
//
//=============================================================================
// Usage Notes:
//
//=============================================================================
// Jan. 2002  Creation                                  fds
//=============================================================================

#include "CATTopDef.h"

class CATLoop;
class CATSoftwareConfiguration;


#include "ExportedByCATTopologicalObjects.h"

class ExportedByCATTopologicalObjects CATLoopOrientationOperator
{

 public :

  CATLoopOrientationOperator();

  virtual ~CATLoopOrientationOperator();

  virtual CATOrientation GetResult() = 0;

};

ExportedByCATTopologicalObjects
CATLoopOrientationOperator *  CreateLoopOrientationOperator(CATSoftwareConfiguration * iConfig, CATLoop * iLoop);

/*ExportedByCATTopologicalObjects
CATLoopOrientationOperator *  CreateLoopOrientationOperator ( CATLoop * iLoop );*/

#endif
