#ifndef CATlsoOrientationUtil_H
#define CATlsoOrientationUtil_H

// ++++ Includes ++++
#include "PersistentCell.h"
#include "CATFace.h"
#include "CATBody.h"
#include "CATMathVector.h"
#include "CATTopDefine.h"

class CATSurParam;
class CATSurface;
class CATPersistentFace;
class CATPersistentBody;
class CATlsoPersistentContext;
class CATMathVector;

//=============================================================================
// CATlsoOrientationUtil
// 
// responsable: LAP
// 
// Classe utilitaire pour l'object Body. Elle ne contient que des methodes
// pour facilité les problemes d'orientation.
//=============================================================================

class ExportedByPersistentCell CATlsoOrientationUtil
{
public:
   static CATMathVector ComputeNormalVsShell(CATFace      & iFace, 
                                             CATBody      & iBody,
                                             CATSurParam  * iParam=NULL);

  static CATOrientation ComputeOrientationFaceVsShell(CATFace & iFace,
                                                      CATBody & iBody);

  static CATOrientation ComputeOrientationSurfaceVsShell(CATFace & iFace,
                                                         CATBody & iBody);

  static CATOrientation ComputeOrientationSurfaceVsShell(CATPersistentFace       * iPersistentFace,
                                                         CATPersistentBody       * iPersistentBody,
                                                         CATlsoPersistentContext & iContext);

  static CATSurface * GetSurfaceFromPersistentFace(CATPersistentFace       * iPersistentFace,
                                                   CATPersistentBody       * iPersistentBody,
                                                   CATlsoPersistentContext & iContext);

  
};

#endif /* CATlsoOrientationUtil_H */
