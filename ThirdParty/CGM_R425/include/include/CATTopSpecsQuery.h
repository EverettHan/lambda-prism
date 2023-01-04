/* -*-c++-*- */
#ifndef CATTopSpecsQuery_H_
#define CATTopSpecsQuery_H_
// COPYRIGHT DASSAULT SYSTEMES  2002
//============================================================================
//  Dynamic invokation of Build-In But Debug Only Software
//============================================================================
#include <stddef.h>
#include "ExportedByGeometricObjects.h"
#include "CATErrorDef.h"
#include "CATListOfCATICGMObjects.h"
#include "CATBoolean.h"

class CATDocument;
class CATIContainer;
class CATGeoFactory;

class ExportedByGeometricObjects CATTopSpecsQuery
{
public:
  inline static short IsAvailable();
  
  //---------------------------------------------------------------------------
  // IsPartResultContainer
  //     Verification de la nature d'un Container
  //     pour tester s'il s'agit bien d'un container Result geometrique de CATPart
  //-----------------------------------------------------------------------------------
  inline static CATDocument * IsPartResultContainer(CATIContainer *iContainer);

  //---------------------------------------------------------------------------
  //  ForceGeoFactoryLoad
  //     Suite au chargement partiel du contenu d'une CATPart (CGR dans contexte CATProduct)
  //     Permettre de Forcer la chargement du Container Result geometrique
  //---------------------------------------------------------------------------
  inline static HRESULT ForceGeoFactoryLoad(CATDocument * iDoc, CATGeoFactory* &ioFactory);
  

  //-------------------------------------------------------------------------------------
  //  GetCurrentVisuContainer
  //     Synchronisation CATPart -> NCGM des attributs graphiques  Show et Couleurs
  //     On obtient en prime les objets participant au dernier etat de construction 
  //------------------------------------------------------------------------------------
  inline static HRESULT GetCurrentVisuContainer(CATGeoFactory* iFactory, CATLISTP(CATICGMObject) & ioVisuPart);

  
  //---------------------------------------------------------------------------
  // MakeSureBRepIsLoaded
  //     Suite aux divers chargements partiels (et perte de coherence)
  //     Permettre de verifier le container BRep (indispensable Write de Container Result geometrique)
  //---------------------------------------------------------------------------
  inline static HRESULT MakeSureBRepIsLoaded(CATDocument *iDoc);

  
  //---------------------------------------------------------------------------
  // PartialLoadIsNeeded
  //     Pour Light Brep Mode, Determination du mode de chargement Full / Dual
  //---------------------------------------------------------------------------
  inline static HRESULT PartialLoadIsNeeded(CATIContainer *iContainer, CATBoolean & ioResult);
  
  //---------------------------------------------------------------------------
  // DualLoadingJustOccured
  //     Synchronisation GenericNaming apres chargement du Dual
  //---------------------------------------------------------------------------
  inline static HRESULT DualLoadingJustOccured(CATIContainer *iContainer);
  
  //---------------------------------------------------------------------------
  // FullLoadingJustOccured
  //     Synchronisation GenericNaming apres chargement du chargement complet
  //---------------------------------------------------------------------------
  inline static HRESULT FullLoadingJustOccured(CATIContainer *iContainer);
  
    //---------------------------------------------------------------------------
  // GetInitURL
  //     Suite aux diverses nommage generique d embedded geometrique
  //---------------------------------------------------------------------------
  inline static HRESULT GetInitURL(CATDocument *iDoc, CATUnicodeString & oInitURL);
 
  //---------------------------------------------------------------------------
  // For ODT Only ...  DefineLoadingMode
  //---------------------------------------------------------------------------
  enum PartLoadingMode
  {
      Visu, // For CATProduct
      Edit, // For CATPart
      BRep  // New ...
  };
  
  inline static void DefineLoadingMode(CATTopSpecsQuery::PartLoadingMode iLoadingMode = CATTopSpecsQuery::Edit);
  
  

protected :
  //---------------------------------------------------------------------------------
  // Pour gestion interne 
  //---------------------------------------------------------------------------------
  CATTopSpecsQuery();
  virtual ~CATTopSpecsQuery();

  //---------------------------------------------------------------------------
  // IsPartResultContainer
  //---------------------------------------------------------------------------
  virtual CATDocument * _IsPartResultContainer(CATIContainer *iContainer) = 0;

  //---------------------------------------------------------------------------
  // MakeSureBRepIsLoaded
  //---------------------------------------------------------------------------
  virtual HRESULT _MakeSureBRepIsLoaded(CATDocument *iDoc) = 0;

  //---------------------------------------------------------------------------------
  // Pour implementation ForceGeoFactoryLoad
  //---------------------------------------------------------------------------------
  virtual HRESULT _ForceGeoFactoryLoad(CATDocument * iDoc, CATGeoFactory* &ioFactory) = 0;

  //---------------------------------------------------------------------------
  //  GetCurrentVisuContainer
  //---------------------------------------------------------------------------
  virtual HRESULT _GetCurrentVisuContainer(CATGeoFactory* iFactory, CATLISTP(CATICGMObject) & ioVisuPart) = 0;


  //---------------------------------------------------------------------------
  // PartialLoadIsNeeded
  //     Pour Light Brep Mode, Determination du mode de chargement Full / Dual
  //---------------------------------------------------------------------------
  virtual HRESULT _PartialLoadIsNeeded(CATIContainer *iContainer, CATBoolean & ioResult) = 0;

  //---------------------------------------------------------------------------
  // DualLoadingJustOccured
  //     Synchronisation GenericNaming apres chargement du Dual
  //---------------------------------------------------------------------------
  virtual HRESULT _DualLoadingJustOccured(CATIContainer *iContainer) = 0;

  //---------------------------------------------------------------------------
  // FullLoadingJustOccured
  //     Synchronisation GenericNaming apres chargement du Dual
  //---------------------------------------------------------------------------
  virtual HRESULT _FullLoadingJustOccured(CATIContainer *iContainer) = 0;

  //---------------------------------------------------------------------------
  // DefineLoadingMode
  //---------------------------------------------------------------------------
  virtual void _DefineLoadingMode(CATTopSpecsQuery::PartLoadingMode iLoadingMode ) = 0;


  //---------------------------------------------------------------------------
  // _GetInitURL
  //---------------------------------------------------------------------------
  virtual HRESULT _GetInitURL(CATDocument *iDoc, CATUnicodeString & oInitURL) = 0;


  //---------------------------------------------------------------------------
  // Acces a l'init
  //---------------------------------------------------------------------------
  static CATTopSpecsQuery *GetBridgeOnce();
  static CATTopSpecsQuery *_Bridge;
  static short             _Once;
};  

//-----------------------------------------------------------
// IsAvailable
//-----------------------------------------------------------
inline short CATTopSpecsQuery::IsAvailable()
{
  return ( (_Once || GetBridgeOnce()) && _Bridge ) ? 1 : 0;
}

//---------------------------------------------------------------------------
// IsPartResultContainer
//---------------------------------------------------------------------------
inline CATDocument * CATTopSpecsQuery::IsPartResultContainer(CATIContainer *iContainer)
{
  if ( (_Once || GetBridgeOnce()) && _Bridge ) return _Bridge->_IsPartResultContainer(iContainer);
  return NULL;
}

//---------------------------------------------------------------------------
// MakeSureBRepIsLoaded
//---------------------------------------------------------------------------
inline HRESULT CATTopSpecsQuery::MakeSureBRepIsLoaded(CATDocument *iDoc)
{
  if ( (_Once || GetBridgeOnce()) && _Bridge ) return _Bridge->_MakeSureBRepIsLoaded(iDoc);
  return E_FAIL;
}

//---------------------------------------------------------------------------
// MakeSureBRepIsLoaded
//---------------------------------------------------------------------------
inline HRESULT CATTopSpecsQuery::ForceGeoFactoryLoad(CATDocument * iDoc, CATGeoFactory* &ioFactory)
{
  ioFactory = NULL;
  if ( (_Once || GetBridgeOnce()) && _Bridge ) return _Bridge->_ForceGeoFactoryLoad(iDoc,ioFactory);
  return E_FAIL;
}

//---------------------------------------------------------------------------
//  GetCurrentVisuContainer
//---------------------------------------------------------------------------
inline HRESULT CATTopSpecsQuery::GetCurrentVisuContainer(CATGeoFactory* iFactory, CATLISTP(CATICGMObject) & ioVisuPart) 
{
  if ( (_Once || GetBridgeOnce()) && _Bridge ) return _Bridge->_GetCurrentVisuContainer(iFactory,ioVisuPart);
  return E_FAIL;
}

//---------------------------------------------------------------------------
// PartialLoadIsNeeded
//     Pour Light Brep Mode, Determination du mode de chargement Full / Dual
//---------------------------------------------------------------------------
inline HRESULT  CATTopSpecsQuery::PartialLoadIsNeeded(CATIContainer *iContainer, CATBoolean & ioResult)
{
  if ( (_Once || GetBridgeOnce()) && _Bridge ) return _Bridge->_PartialLoadIsNeeded(iContainer,ioResult);
  return E_FAIL;
}

//---------------------------------------------------------------------------
// DualLoadingJustOccured
//     Synchronisation GenericNaming apres chargement du Dual
//---------------------------------------------------------------------------
inline HRESULT  CATTopSpecsQuery::DualLoadingJustOccured(CATIContainer *iContainer)
{
  if ( (_Once || GetBridgeOnce()) && _Bridge ) return _Bridge->_DualLoadingJustOccured(iContainer);
  return E_FAIL;
}


//---------------------------------------------------------------------------
// FullLoadingJustOccured
//     Synchronisation GenericNaming apres chargement du Dual
//---------------------------------------------------------------------------
inline HRESULT  CATTopSpecsQuery::FullLoadingJustOccured(CATIContainer *iContainer)
{
  if ( (_Once || GetBridgeOnce()) && _Bridge ) return _Bridge->_FullLoadingJustOccured(iContainer);
  return E_FAIL;
}
 


//---------------------------------------------------------------------------
// DefineLoadingMode
//---------------------------------------------------------------------------
inline void  CATTopSpecsQuery::DefineLoadingMode(CATTopSpecsQuery::PartLoadingMode iLoadingMode)
{
  if ( (_Once || GetBridgeOnce()) && _Bridge ) _Bridge->_DefineLoadingMode(iLoadingMode);
}


//---------------------------------------------------------------------------
// _GetInitURL
//---------------------------------------------------------------------------
inline HRESULT  CATTopSpecsQuery::GetInitURL(CATDocument *iDoc, CATUnicodeString & oInitURL)
{
  if ( (_Once || GetBridgeOnce()) && _Bridge ) return _Bridge->_GetInitURL(iDoc,oInitURL);
  return E_FAIL;
}
 
#endif
