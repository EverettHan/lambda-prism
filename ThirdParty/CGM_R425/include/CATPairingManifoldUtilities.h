// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : ZUT
//
// DESCRIPTION  : CATPairingManifoldUtilities
//
//=============================================================================
// Creation ZUT February 2021
//=============================================================================

#ifndef CATPairingManifoldUtilities_H
#define CATPairingManifoldUtilities_H

#include "PersistentCell.h"

class CATCellManifoldGroup;
class CATLiveBody;
class CATCellManifold;
class CATFace;
class CATPairingManifoldAttribute;

class ExportedByPersistentCell CATPairingManifoldUtilities
{
public:

  static CATCellManifoldGroup * GetPairingManifoldGroup( CATLiveBody * iLiveBody, CATCellManifold * iCM );

  static CATCellManifoldGroup * GetPairingManifoldGroup( CATLiveBody * iLiveBody, CATFace * iFace );

  static CATPairingManifoldAttribute * GetPairingManifoldAttribute( CATCellManifoldGroup * iPairingGroup );
};

#endif /* CATPairingManifoldUtilities_H */
