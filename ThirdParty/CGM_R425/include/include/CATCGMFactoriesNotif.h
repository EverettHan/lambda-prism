/* -*-c++-*- */
#ifndef CATCGMFactoriesNotif_H
#define CATCGMFactoriesNotif_H
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// CATCGMFactoriesNotif Integration Atelier de Debug du departement CGM
//=============================================================================
// Sept. 2000    Creation                                     TCX
//=============================================================================
#include "CATEventSubscriber.h"
#include "CATCGMNewArray.h"
#include "CATNotification.h"
#include "CATBoolean.h"
#include "ExportedByCATCGMFusion.h"

class CATCGMContainer;
class CATCGMObject;
class CATCGMFactoryLife;
 

class ExportedByCATCGMFusion CATCGMFactoriesNotif : public CATNotification
{
public:
  CATDeclareClass;
  CATCGMNewClassArrayDeclare;
  CATCGMFactoriesNotif(CATCGMContainer *cont, CATCGMObject *geo);
  virtual ~CATCGMFactoriesNotif();

  // --------------------------------------------------------------------------
  //  Identification de l'evenement en cours
  //     Create   : Creation d'une CATGeoFactory V5 (Identification Container inplicite)
  //     Delete   : Close d'une CATGeoFactory V5 (Identification Container inplicite)
  //     Add      : Ajout d'un element dans le Container (juste apres insertion)
  //     Remove   : Suppression d'un element du Container (juste avant dechainage)
  // ----------------------------------------------------------------------------------
  enum Event { Unknown = 0, Create = +1,  Add = +2, Linked = +3, Unlinked = -3, Remove = -2, Delete = -1, Refresh=10 };

  Event            _event;
  CATCGMContainer *_implicit;
  CATCGMObject    *_geometry;
};

#endif
