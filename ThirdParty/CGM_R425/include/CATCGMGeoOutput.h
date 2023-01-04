#ifndef CATCGMGeoOutput_h_
#define CATCGMGeoOutput_h_

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "ExportedByCATCGMGeoMath.h"
#include "CATCGMOutput.h"

class CATCrvParam;
class CATCrvLimits;
class CATSurParam;
class CATSurLimits;


ExportedByCATCGMGeoMath CATCGMOutput & operator << ( CATCGMOutput& , const  CATCrvParam& );
ExportedByCATCGMGeoMath CATCGMOutput & operator << ( CATCGMOutput& , const  CATCrvLimits& );
ExportedByCATCGMGeoMath CATCGMOutput & operator << ( CATCGMOutput& , const  CATSurParam& );
ExportedByCATCGMGeoMath CATCGMOutput & operator << ( CATCGMOutput& , const  CATSurLimits& );


#endif
