#ifndef CATCGMSharpnessEvaluator_CONNECT_CHECKER_H
#define CATCGMSharpnessEvaluator_CONNECT_CHECKER_H

// COPYRIGHT DASSAULT SYSTEMES  2010
#include "GeoTopo.h"
#include "CATBoolean.h"
#include "CATMathInline.h"

class ExportedByGeoTopo CATCGMSharpnessEvaluator_CONNECT_CHECKER
{
public:
  static INLINE CATBoolean  IsForced();
  static INLINE void        ResetForced();
  static INLINE void        SetForced();

private :
 static CATBoolean _Initialised;
 static CATBoolean _Forced;
 static void       Init();
};

INLINE CATBoolean CATCGMSharpnessEvaluator_CONNECT_CHECKER::IsForced()  
{  if (! _Initialised ) Init();  return _Forced; }

INLINE void CATCGMSharpnessEvaluator_CONNECT_CHECKER::ResetForced()  
{  if (! _Initialised ) Init();   _Forced = FALSE; }
 
INLINE void CATCGMSharpnessEvaluator_CONNECT_CHECKER::SetForced()  
{  if (! _Initialised ) Init();   _Forced = TRUE; }


#endif
