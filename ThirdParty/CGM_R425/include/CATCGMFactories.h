/* -*-c++-*- */
#ifndef CATCGMFactories_H
#define CATCGMFactories_H
#include "ExportedByCATCGMFusion.h"
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// CATCGMFactories Integration Atelier de Debug du departement CGM
//=============================================================================
// Sept. 2000    Creation                                     TCX
//=============================================================================
#include "CATEventSubscriber.h"
#include "CATCGMNewArray.h"
#include "CATNotification.h"
#include "CATBoolean.h"
#include "CATCGMFactoriesNotif.h"

class CATCGMContainer;
class CATCGMObject;
class CATCGMFactoryLife;

class  ExportedByCATCGMFusion CATCGMFactories : public CATEventSubscriber
{
public:
  
  CATDeclareClass;
  CATCGMNewClassArrayDeclare;

  // EXTERNE : Declaration/Suppression d'un abonnement
  static CATCGMFactories *AddRefFromSubscriber(CATEventSubscriber *iSubscribe, CATSubscriberMethod  iMethodToCall);
  static CATCGMFactories *ReleaseFromSubscriber(CATEventSubscriber *iSubscribe);

  // INTERNE : Uniquement pour tester rapidement l'existence d'un abonnement en cours
  static CATBoolean _MustPublish;

  // INTERNE : Creation/Suppression de CATGeoFactory
  static void Create(CATCGMContainer *implicit); 
  static void Delete(CATCGMContainer *implicit);
  static void Refresh(CATCGMContainer *implicit); // Perfo

  // INTERNE : Creation/Suppression de CATGeometry
  static void Add(CATCGMContainer *implicit,    CATCGMObject    *geometry); 
  static void Remove(CATCGMContainer *implicit, CATCGMObject    *geometry);

  // INTERNE : CATIGenericNamed : Linked/Unlinked
  static void Linked(CATCGMContainer *implicit,   CATCGMObject    *geometry);
  static void Unlinked(CATCGMContainer *implicit, CATCGMObject    *geometry);

private:

  static CATCGMFactories *_CATGem;

  CATCGMFactories();
  virtual ~CATCGMFactories();
};


#endif
