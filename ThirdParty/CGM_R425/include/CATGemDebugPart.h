/* -*-c++-*- */
#ifndef CATGemDebugPart_H_
#define CATGemDebugPart_H_
// COPYRIGHT DASSAULT SYSTEMES  2002
//=============================================================================
//  Dynamic invokation of Build-In But Debug Only Software
//=============================================================================
// Nov. 03 GetMechanicalPartSolid(...)                                    HCN
//=============================================================================
#include "ExportedByGeometricObjects.h"
#include <stddef.h>
#include "CATErrorDef.h"
#include "CATBaseUnknown.h" 
#include "CATGemDebugShow.h" 
#include "CATBoolean.h" 
#include "CATGemDebugPartUpdate.h"
#include "CATMathStreamVersionDef.h" 
#include "CATGeometryType.h" 
#include "CATDataType.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATMathInline.h"
#include "CATCGMItfName.h"
 
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif


class CATUnicodeString;
class CATDocument;
class CATBody;
class CATLISTP(CATDocument);
class CATLISTP(CATBody);

class CATCldPolygon;
class CATSubdivMesh;
class CATCldBody;
class CATGeoFactory;

class CATDlgMultiList;
class CATDlgEditor;
class CATICGMObject;
class DataSiteReport;
class CATOmbLifeCycleRootsBag;



class ExportedByGeometricObjects CATGemDebugPart
{
public:

  INLINE static short IsAvailable();
  

  //---------------------------------------------------------------------------
  // Dump
  //---------------------------------------------------------------------------
  INLINE static void Dump(CATGemDebugShow iShow, CATDocument * iDoc, 
                          CATDlgMultiList *iPanel,  ostream &outputText,
                          CATDlgEditor *iEditor, CATCGMStreamVersion* ipStreamVersion = NULL);
    
  //---------------------------------------------------------------------------------
  // Force + Update + SingleUpdate
  //---------------------------------------------------------------------------------
  INLINE static HRESULT Update(CATDocument  * iDoc,  ostream &outputText, CATGemDebugPartUpdate iFlags = 0);


  //---------------------------------------------------------------------------------
  // Force + FeatureUpdate + Save
  //---------------------------------------------------------------------------------
  INLINE static HRESULT FeatureUpdateSave(CATDocument  * iDoc,  ostream &outputText, CATGemDebugPartUpdate iFlags = 0);

  //=================================================================
  //  ForceGeoFactoryLoad
  //=================================================================
  static HRESULT ForceGeoFactoryLoad(CATDocument * iDoc, CATGeoFactory* &ioFactory);

  //=================================================================
  //  PrepareLightDesignMode
  //=================================================================
  INLINE static HRESULT PrepareLightDesignMode(CATDocument * iDoc);

  //=================================================================
  //  DicoFeature
  //=================================================================
  INLINE static CATCGMItfNames * DicoFeature(CATDocument     * iDoc,
                                                      CATGemDebugShow    iShow,
                                                      CATGeoFactory   * &ioFactory,
                                                      short           * pMaxInitialSpecConfiglevel = NULL);


  //---------------------------------------------------------------------------------
  // Pour Enumeration des documents CATPart avec Containers Feature et CATGeoFactory
  //---------------------------------------------------------------------------------
  INLINE static HRESULT GetCATParts( CATLISTP(CATDocument) & ioParts );

  //---------------------------------------------------------------------------------
  // Creation d'un Document CATPart a partir d'une liste de Body
  //---------------------------------------------------------------------------------
  INLINE static HRESULT CreateNewPart(CATLISTP(CATBody)& iDatums, CATDocument * & iNewDoc);

  //---------------------------------------------------------------------------------
  // Creation d'un Document CATPart a partir d'un Polygon
  //---------------------------------------------------------------------------------
  INLINE static HRESULT CreateNewPart(CATCldPolygon * Polygon, CATDocument * & iNewDoc);

  //---------------------------------------------------------------------------------
  // Creation d'un Document CATPart a partir d'un Polygon
  //---------------------------------------------------------------------------------
  INLINE static HRESULT CreateNewPart(CATSubdivMesh * SS, CATDocument * & iNewDoc);

  //---------------------------------------------------------------------------------
  // Dans un document CATPart, "featurisation" en terme de DATUM
  //---------------------------------------------------------------------------------
  INLINE static HRESULT MakeAsDatum(CATLISTP(CATBody)& iDatums);

  //---------------------------------------------------------------------------
  // FeatureName
  //---------------------------------------------------------------------------
  static CATBoolean FeatureName(CATICGMObject * iObject, CATUnicodeString & iString );

  //---------------------------------------------------------------------------
  // GetMechanicalPartSolid : recuperation du resulting body
  //---------------------------------------------------------------------------
  INLINE static HRESULT GetMechanicalPartSolid(CATDocument* ipDoc, CATBody*& iopBody, CATUnicodeString& ioFeatureName);

  ///---------------------------------------------------------------------
  ///  Marque la vivicite de toutes les edges ou vertices de tous les bodies
  ///  d'une factory.
  ///  Utilise pour evaluer la taille de ces donnees de vivicite
  ///
  /// WARNING : CE SERVICE NE PEUT ETRE APPELE QU'A UN MOMENT OU TOUTE
  ///           LA TOPOLOGIE DU CONTAINER EST MODIFIABLE !
  ///---------------------------------------------------------------------  
 INLINE  static int SetAllSharpness( CATGeoFactory*    iFactory,
                              CATGeometricType  iEdgeOrVertex, // CATEdgeType ou CATVertexType ou CATGeometryType pour les deux
                              CATULONG32 &    oNbSharpnessDataStored);

  ///---------------------------------------------------------------------
  ///  ShowType ...
  ///---------------------------------------------------------------------  
  static const char *ShowType(const short itp);


protected :
  //---------------------------------------------------------------------------------
  // Pour gestion interne 
  //---------------------------------------------------------------------------------
  CATGemDebugPart();
  virtual ~CATGemDebugPart();

  //---------------------------------------------------------------------------
  // Dump
  //---------------------------------------------------------------------------
  virtual void _Dump(CATGemDebugShow iShow, CATDocument * iDoc, 
                     CATDlgMultiList *iPanel, ostream &outputText,
                     CATDlgEditor *iEditor, CATCGMStreamVersion* ipStreamVersion) = 0;

  //---------------------------------------------------------------------------------
  // Force + Update
  //---------------------------------------------------------------------------------
  virtual HRESULT _Update(CATDocument * iDoc,  ostream &outputText, CATGemDebugPartUpdate iFlags) = 0;

  //---------------------------------------------------------------------------------
  // Force + FeatureUpdate + Save
  //---------------------------------------------------------------------------------
  virtual HRESULT _FeatureUpdateSave(CATDocument * iDoc,  ostream &outputText, CATGemDebugPartUpdate iFlags) = 0;

  //=================================================================
  //  PrepareLightDesignMode
  //=================================================================
  virtual HRESULT _PrepareLightDesignMode(CATDocument * iDoc) = 0;

  //=================================================================
  //  DicoFeature
  //=================================================================
  virtual CATCGMItfNames * _DicoFeature(CATDocument        * iDoc,
                                                 CATGemDebugShow      iShow, 
                                                 CATGeoFactory     * &ioFactory,
                                                 short             *  pMaxInitialSpecConfiglevel = NULL) = 0;

  //---------------------------------------------------------------------------------
  // Pour Enumeration des documents CATPart avec Containers Feature et CATGeoFactory
  //---------------------------------------------------------------------------------
  virtual HRESULT _GetCATParts(CATLISTP(CATDocument) & ioParts) = 0;

  //---------------------------------------------------------------------------------
  // Creation d'un Document CATPart a partir d'une liste de Body
  //---------------------------------------------------------------------------------
  virtual HRESULT _CreateNewPart(CATLISTP(CATBody)& iDatums, CATDocument * & iNewDoc) = 0;

  //---------------------------------------------------------------------------------
  // Creation d'un Document CATPart a partir d'une liste de Body
  //---------------------------------------------------------------------------------
  virtual HRESULT _CreateNewPart(CATCldPolygon * Polygon, CATDocument * & iNewDoc) = 0;

  virtual HRESULT _CreateNewPart(CATSubdivMesh * SS, CATDocument * & iNewDoc) = 0;

  //---------------------------------------------------------------------------------
  // Dans un document CATPart, "featurisation" en terme de DATUM
  //---------------------------------------------------------------------------------
  virtual HRESULT _MakeAsDatum(CATLISTP(CATBody)& iDatums) = 0;
 
  //---------------------------------------------------------------------------
  // GetMechanicalPartSolid : recuperation du resulting body
  //---------------------------------------------------------------------------
  virtual HRESULT _GetMechanicalPartSolid(CATDocument* ipDoc, CATBody*& iopBody, CATUnicodeString& ioFeatureName) = 0;
 

  virtual int _SetAllSharpness( CATGeoFactory*    iFactory,
    CATGeometricType  iEdgeOrVertex, // CATEdgeType ou CATVertexType ou CATGeometryType pour les deux
    CATULONG32 &    oNbSharpnessDataStored)= 0 ;

  //---------------------------------------------------------------------------
  // Acces a l'init
  //---------------------------------------------------------------------------
  static CATGemDebugPart *GetDebugOnly();
  static CATGemDebugPart *_Debug;
  static short            _Once;
};  

//-----------------------------------------------------------
// IsAvailable
//-----------------------------------------------------------
INLINE short CATGemDebugPart::IsAvailable()
{
  return ( (_Once || GetDebugOnly()) && _Debug ) ? 1 : 0;
}

//---------------------------------------------------------------------------
// Dump
//---------------------------------------------------------------------------
INLINE void CATGemDebugPart::Dump(CATGemDebugShow iShow, CATDocument * iDoc,
                                  CATDlgMultiList *iPanel, ostream &outputText,
                                  CATDlgEditor *iEditor, CATCGMStreamVersion* ipStreamVersion)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_Dump(iShow,iDoc,iPanel,outputText,iEditor,ipStreamVersion);
}

//------------------------------------------------------------------------------------------------------------------------------------
//  Force + Update 
//------------------------------------------------------------------------------------------------------------------------------------
INLINE HRESULT CATGemDebugPart::Update(CATDocument * iDoc,  ostream &outputText, CATGemDebugPartUpdate iFlags)
{
  if ( (_Once || GetDebugOnly()) && _Debug )
    return  _Debug->_Update(iDoc,outputText,iFlags);
  return E_FAIL;
}

//------------------------------------------------------------------------------------------------------------------------------------
//  Force + Update 
//------------------------------------------------------------------------------------------------------------------------------------
INLINE HRESULT CATGemDebugPart::FeatureUpdateSave(CATDocument * iDoc,  ostream &outputText, CATGemDebugPartUpdate iFlags)
{
  if ( (_Once || GetDebugOnly()) && _Debug )
    return  _Debug->_FeatureUpdateSave(iDoc,outputText,iFlags);
  return E_FAIL;
}


//---------------------------------------------------------------------------------
// PrepareLightDesignMode
//---------------------------------------------------------------------------------
INLINE HRESULT CATGemDebugPart::PrepareLightDesignMode(CATDocument * iDoc)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) 
    return _Debug->_PrepareLightDesignMode(iDoc);
  return E_FAIL;
}


//---------------------------------------------------------------------------------
// ForceGeoFactoryLoad
//---------------------------------------------------------------------------------
INLINE CATCGMItfNames * CATGemDebugPart::DicoFeature(CATDocument     *   iDoc,
                                                              CATGemDebugShow     iShow,
                                                              CATGeoFactory   * & ioFactory,
                                                              short           *   pMaxInitialSpecConfiglevel)
{
  ioFactory = NULL;
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_DicoFeature(iDoc,iShow,ioFactory,pMaxInitialSpecConfiglevel);
  return NULL;
}



//---------------------------------------------------------------------------------
// Pour Enumeration des documents CATPart avec Containers Feature et CATGeoFactory
//---------------------------------------------------------------------------------
INLINE HRESULT CATGemDebugPart::GetCATParts(CATLISTP(CATDocument) & ioParts)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_GetCATParts(ioParts);
  return E_FAIL;
}

//---------------------------------------------------------------------------------
// Creation d'un Document CATPart a partir d'une liste de Body
//---------------------------------------------------------------------------------
INLINE HRESULT CATGemDebugPart::CreateNewPart(CATLISTP(CATBody)& iDatums, CATDocument * & iNewDoc)
{
  iNewDoc = NULL;
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_CreateNewPart(iDatums,iNewDoc);
  return E_FAIL;
}

//---------------------------------------------------------------------------------
// Creation d'un Document CATPart a partir d'une liste de Body
//---------------------------------------------------------------------------------
INLINE HRESULT CATGemDebugPart::CreateNewPart(CATCldPolygon * Polygon, CATDocument * & iNewDoc)
{
  iNewDoc = NULL;
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_CreateNewPart(Polygon,iNewDoc);
  return E_FAIL;
}

INLINE HRESULT CATGemDebugPart::CreateNewPart(CATSubdivMesh * SS, CATDocument * & iNewDoc)
{
  iNewDoc = NULL;
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_CreateNewPart(SS,iNewDoc);
  return E_FAIL;
}

//---------------------------------------------------------------------------------
// Dans un document CATPart, "featurisation" en terme de DATUM
//---------------------------------------------------------------------------------
INLINE HRESULT CATGemDebugPart::MakeAsDatum(CATLISTP(CATBody)& iDatums)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_MakeAsDatum(iDatums);
  return E_FAIL;
}
   
 
//---------------------------------------------------------------------------
// GetMechanicalPartSolid : recuperation du resulting body
//---------------------------------------------------------------------------
INLINE HRESULT CATGemDebugPart::GetMechanicalPartSolid(CATDocument* ipDoc, CATBody*& iopBody, CATUnicodeString& ioFeatureName)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_GetMechanicalPartSolid(ipDoc, iopBody, ioFeatureName);
  return E_FAIL;
}
 
//---------------------------------------------------------------------------------
// 3DXML
//---------------------------------------------------------------------------------
INLINE int CATGemDebugPart::SetAllSharpness( CATGeoFactory*    iFactory,
                              CATGeometricType  iEdgeOrVertex,  
                              CATULONG32 &    oNbSharpnessDataStored)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_SetAllSharpness(iFactory,iEdgeOrVertex,oNbSharpnessDataStored);
  return 0;
}   
 

#endif
