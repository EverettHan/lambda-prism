// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================
#ifndef XXXAreaPhoenix_H
#define XXXPhoenix_H

/* To use this, operator class should have defined macros. E.g. for CATPolyBodyArea
  #define XXX CATPolyBodyArea
  #define XXXObserver CATPolyBodyAreaObserver
  #define XXXName "CATPolyBodyArea"
*/

#include "CATBoolean.h"

class XXX;
class XXXObserver;
class CATechExt;


void InitializePhoenixCaptureObserver (XXX& iOperator, CATechExt *& iExtension);

void FinalizePhoenixCaptureObserver (XXX& iOperator, CATechExt *& iExtension);


#endif
