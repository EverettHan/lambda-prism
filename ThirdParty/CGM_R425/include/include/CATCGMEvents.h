/* -*-c++-*- */
#ifndef CATCGMEvents_H
#define CATCGMEvents_H
// COPYRIGHT DASSAULT SYSTEMES  2002
//=============================================================================
//  Managing nested Debug Software outside commercial Product
//=============================================================================
// Jui  02   Portage 64 bits                                              HCN
// Mar. 04   Changement de la signature de StreamSizeObject               MNA
// Jul. 04   Argument CATCGMStream* pour
//           CATCGMEventImplicitFactoryLife::Un/Streaming(...)            HCN
//=============================================================================
#include "ExportedByGeometricObjects.h"
#include "CATCGMNewArray.h"
#include "CATCGMEventType.h"
#include "CATGeometryType.h"
#include "CATBoolean.h"
#include "CATListOfCATCGMEvents.h"
#include "CATCGMVirtual.h"
#include "CATMathInline.h"

#include <stddef.h>

class CATICGMUnknown;
class CATICGMObject;
class CATICGMSession;
class CATGeoFactory;
class CATCGMObject;
class CATBody;
class CATTopData;
class CATCrvLimits;
class CATSurLimits;
class CATCurve;
class CATSurface;
class CATTopology;
class CATCGMStream;
class CATExtCGMEventPublisher;
class CATCGMAttributeDef;

//---------------------------------------------------------------------------------
// Classe de Base de tous les evenements de Debug
//---------------------------------------------------------------------------------
class ExportedByGeometricObjects CATCGMEvents : public CATCGMVirtual
{
public:

  /** GetEventType */
  INLINE CATCGMEventType GetEventType() const;
  
  /** GetPublisher */
  INLINE CATICGMUnknown  *GetPublisher() const;
  
  
  /** InternalUse */
  static CATBoolean CheckType(const CATCGMEventType itp);
    
  /** InternalUse */
  void Clear();

  /** Be Carefull */
  virtual ~CATCGMEvents();

protected :
  CATCGMEvents(CATCGMEventType iType, CATICGMUnknown *iObj);
  
  static void GetSubcribers(CATICGMUnknown *publisher, const CATCGMEventType itp, CATLISTP(CATCGMEvents) & ioSubcribers);

private :
  CATICGMUnknown  *  _Obj;
  CATExtCGMEventPublisher * _Publisher;
  CATCGMEventType    _Type;
};



//========================= 
//   RemoveComponent
//========================= 
class ExportedByGeometricObjects CATCGMEventRemoveComponent : public CATCGMEvents
{
public:
  CATCGMEventRemoveComponent(CATICGMUnknown *iContainer, CATGeometricType iFilter); 

  //---------------------------------------------------------------------------------
  // Subscriber USE : get information about RemoveComponent
  //---------------------------------------------------------------------------------
  virtual void ComponentLife(CATICGMUnknown *iComponent) = 0;

  //---------------------------------------------------------------------------------
  // Publisher USE : easy integration
  //---------------------------------------------------------------------------------
  static  void ComponentLife(CATICGMUnknown *iContainer, CATICGMUnknown*iComponent);

protected :
  CATGeometricType    _Filter;
};



//========================= 
//   Explicit
//========================= 
class ExportedByGeometricObjects CATCGMEventExplicitChange : public CATCGMEvents
{
public:
  CATCGMEventExplicitChange(CATGeoFactory *iFactory); 

  //---------------------------------------------------------------------------------
  // Subscriber USE : get information about ExplicitChange
  //---------------------------------------------------------------------------------
  virtual void ExplicitChange(CATICGMUnknown *iComponent) = 0;

  //---------------------------------------------------------------------------------
  // Publisher USE : easy integration
  //---------------------------------------------------------------------------------
  static  void ExplicitChange(CATICGMUnknown *iContainer, CATICGMUnknown*iComponent);
};



//========================= 
// Very Old Management
//========================= 
class ExportedByGeometricObjects CATCGMEventCallback : public CATCGMEvents
{
public:
  CATCGMEventCallback(CATGeoFactory *iFactory); 

  enum  Notification { Created, Modified, Deleted, GraphicModified };

  //---------------------------------------------------------------------------------
  // Subscriber USE : get information about ExplicitChange
  //---------------------------------------------------------------------------------
  virtual void Callback(CATICGMUnknown* Object, CATCGMEventCallback::Notification iNotif) = 0;

  //---------------------------------------------------------------------------------
  // Publisher USE : easy integration
  //---------------------------------------------------------------------------------
  static  void Callback(CATICGMUnknown *iContainer, CATICGMUnknown* Object, CATCGMEventCallback::Notification iNotif);
};




//========================= 
//  Extrapolation
//========================= 
class ExportedByGeometricObjects CATCGMEventExtrapolation : public CATCGMEvents
{
public:
  CATCGMEventExtrapolation(CATGeoFactory *iFactory); 

  //---------------------------------------------------------------------------------
  // Subscriber USE : get information about Extrapolation
  //---------------------------------------------------------------------------------
  virtual void Extrapolation(CATCurve   *iCurve,   const CATCrvLimits & iBefore, const CATCrvLimits & iAfter) = 0;
  virtual void Extrapolation(CATSurface *iSurface, const CATSurLimits & iBefore, const CATSurLimits & iAfter) = 0;

  //---------------------------------------------------------------------------------
  // Publisher USE : easy integration
  //---------------------------------------------------------------------------------
  static  void Extrapolation(CATICGMUnknown *iContainer, CATCurve   *iCurve, 
                             const CATCrvLimits & iBefore, const CATCrvLimits & iAfter);

  static  void Extrapolation(CATICGMUnknown *iContainer, CATSurface *iSurface, 
                             const CATSurLimits & iBefore, const CATSurLimits & iAfter);

};



//========================= 
//    StreamSizeObject
//========================= 
class ExportedByGeometricObjects CATCGMEventStreamSizeObject : public CATCGMEvents
{
public:
  CATCGMEventStreamSizeObject(CATGeoFactory *iFactory); 
  
  //---------------------------------------------------------------------------------
  // Subscriber USE : get information about streaming information
  //---------------------------------------------------------------------------------
  virtual void StreamSize(short itp,   CATCGMObject *impl, size_t streamSize, short iAddTransversMod=0) = 0;
  virtual void UnStreamSize(short itp, CATCGMObject *impl, size_t streamSize) = 0;
  
  virtual void StreamAttributeSize(short itp,   CATCGMAttributeDef *  iDefinition, size_t iCoreSize, size_t iAppliSize, short iAddTransversMod=0) = 0;
  virtual void UnStreamAttributeSize(short itp, CATCGMAttributeDef *  iDefinition, size_t iCoreSize, size_t iAppliSize) = 0;

  //---------------------------------------------------------------------------------
  // Publisher USE : easy integration
  //---------------------------------------------------------------------------------
  static void StreamSize(CATICGMUnknown *publisher, short itp, CATCGMObject *impl, size_t streamSize, short iAddTransversMod=0);
  static void UnStreamSize(CATICGMUnknown *publisher, short itp, CATCGMObject *impl, size_t streamSize);
 
  static void StreamAttributeSize(CATICGMUnknown *publisher, short itp,   CATCGMAttributeDef *  iDefinition, size_t iCoreSize, size_t iAppliSize, short iAddTransversMod=0)  ;
  static void UnStreamAttributeSize(CATICGMUnknown *publisher, short itp, CATCGMAttributeDef *  iDefinition, size_t iCoreSize, size_t iAppliSize) ;


};


//========================= 
//    TopologyCompletion
//========================= 
class ExportedByGeometricObjects CATCGMEventTopologyCompletion : public CATCGMEvents
{
public:
  CATCGMEventTopologyCompletion(CATGeoFactory *iFactory, CATGeometricType iFilter); 

  //---------------------------------------------------------------------------------
  // Subscriber USE : get information about Body completion
  //---------------------------------------------------------------------------------
  virtual void TopologyCompletion(CATTopology *iTopology, const CATTopData  * iData) = 0;

  //---------------------------------------------------------------------------------
  // Publisher USE : easy integration
  //---------------------------------------------------------------------------------
  static  void TopologyCompletion(CATICGMUnknown *publisher, CATTopology *iTopology, const CATTopData  * iData);

protected :
  CATGeometricType    _Filter;
};


//========================= 
//   GraphicModification
//========================= 
class ExportedByGeometricObjects CATCGMEventGraphicModification : public CATCGMEvents
{
public:
  CATCGMEventGraphicModification(CATGeoFactory *iFactory); 

  enum  GraphicModif { ShowNoShow, Color };

  //---------------------------------------------------------------------------------
  // Subscriber USE : get information about GraphicModification
  //---------------------------------------------------------------------------------
  virtual void GraphicModification(CATICGMUnknown *itf, const GraphicModif afterEvent) = 0;

  //---------------------------------------------------------------------------------
  // Publisher USE : easy integration
  //---------------------------------------------------------------------------------
  static  void GraphicModification(CATICGMUnknown *publisher, CATICGMUnknown*itf, const GraphicModif afterEvent);
};


//========================= 
//  ImplicitFactoryLife 
//========================= 
class ExportedByGeometricObjects CATCGMEventImplicitFactoryLife : public CATCGMEvents
{
public:
  CATCGMEventImplicitFactoryLife(CATICGMSession *iSession); 

  //---------------------------------------------------------------------------------
  // Subscriber USE : get information about ImplicitFactoryLife
  //---------------------------------------------------------------------------------
  //
  virtual void Creating(CATGeoFactory *iFactory) = 0;

  // Icontext   -1 : before RemoveAll,    +1 : after closing
  virtual void Closing(CATGeoFactory *iFactory, short iContext) = 0;

  // Icontext   -1 : before UnStreaming,    +1 : before Freezing
  virtual void UnStreaming(CATGeoFactory *iFactory, CATCGMStream* ipStr, short iContext) = 0;

  // Icontext   -1 : before Streaming,    +1 : after Streaming
  virtual void Streaming(CATGeoFactory *iFactory, CATCGMStream* ipStr, short iContext) = 0;

  //---------------------------------------------------------------------------------
  // Publisher USE : easy integration
  //---------------------------------------------------------------------------------
  static void Creating(CATICGMUnknown *publisher,   CATGeoFactory *iFactory);
  static void Closing(CATICGMUnknown *publisher,    CATGeoFactory *iFactory, short iContext);
  static void UnStreaming(CATICGMUnknown *publisher,CATGeoFactory *iFactory, CATCGMStream* ipStr, short iContext);
  static void Streaming(CATICGMUnknown *publisher,  CATGeoFactory *iFactory, CATCGMStream* ipStr, short iContext);
};


//========================= 
//   GenericNamed 
//========================= 
class ExportedByGeometricObjects CATCGMEventGenericNamed : public CATCGMEvents
{
public:
  CATCGMEventGenericNamed(CATGeoFactory *iFactory); 

  enum EvtGenericNamed { linked = +1, unlinked = 0, deleted = -1, datum = +2 , 
                         noNeedToSave = +3,  Smart = +4 ,  unSmart = +5 };

  //---------------------------------------------------------------------------------
  // Subscriber USE : get information about GenericNamed
  //---------------------------------------------------------------------------------
  // Icontext   -1:delete,    0:unlinked   +1:linked   2:datum
  virtual void Event(CATICGMUnknown *iObject, const CATCGMEventGenericNamed::EvtGenericNamed iContext) = 0;

  //---------------------------------------------------------------------------------
  // Publisher USE : easy integration
  //---------------------------------------------------------------------------------
  static void Event(CATICGMUnknown *publisher, CATICGMUnknown *iObject, const CATCGMEventGenericNamed::EvtGenericNamed iContext);
};



//----------------
// INLINE ...
//----------------

INLINE CATCGMEventType CATCGMEvents::GetEventType() const
{
  return _Type;
}

INLINE CATICGMUnknown  *CATCGMEvents::GetPublisher() const
{
  return _Obj;
}



#endif
