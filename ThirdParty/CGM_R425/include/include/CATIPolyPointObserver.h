//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// Listen for point modification events.
//
//=============================================================================
// 2007-04-04   BPG     * New.
//=============================================================================
#ifndef CATIPolyPointObserver_H
#define CATIPolyPointObserver_H

#include "PolyhedralModel.h"
#include "CATPolyRefCounted.h"
#include "CATErrorDef.h"

class CATIPolyPoint;
class CATMathPoint;


/**
* Observer class for CATIPolyPoint.
*/
class ExportedByPolyhedralModel CATIPolyPointObserver : public CATPolyRefCounted
{

public:

  virtual ~CATIPolyPointObserver () {}

public:

  virtual HRESULT ReactToSetPosition (const CATIPolyPoint &p, const CATMathPoint &P);

};

#endif // !CATIPolyPointObserver_H
