/* -*-c++-*- */
#ifndef CATGeoTemporary_h
#define CATGeoTemporary_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2001  
//-----------------------------------------------------------------------------
// class CATGeoTemporary
// 
// 
//-----------------------------------------------------------------------------
// Usage Notes:
//
//
//-----------------------------------------------------------------------------
// Mar. 01 Transfert GeometryVisualization -> GeometricObjects           TCX
// Dec. 01 Modification interface pour :                                 HCN
//               - iOriginalFeature passe en CATBaseUnknown
//                 Le feature est passe actuellement mais non exploite.
//                 Il pourra l'etre ulterieurement. Pour cela il doit
//                 repondre a CATIOrientation et sa gestion de duree
//                 de vie doit etre correcte...
//               - Set/GetIntValue, Set/GetMathPoint
// Juin 02 Passage sur nouvelle delegation                               HCN
//-----------------------------------------------------------------------------
#include "CATGeometricObjects.h" 
#include "CATBaseUnknown.h"
#include "CATCGMNewArray.h"
#include "CATBoolean.h"
#include "CATListOfCATGeoTemporary.h"
#include "CATMathInline.h"
#include "CATDataType.h"
 
#define IS_GEOTEMPORARYCONTAINER(Container_var) Container_var->GetImpl()->IsAKindOf("CGMV5Container")

class CATMathTransformation;
class CATTransfoManager;
class CATGeometry;
class CATSoftwareConfiguration;
class CATMathPoint;

class ExportedByCATGeometricObjects CATGeoTemporary : public CATBaseUnknown
{
  CATDeclareClass ;
  
public:
  
  static HRESULT Create ( CATSoftwareConfiguration*     iConfig,
                          CATBaseUnknown*               iOriginalFeature,
                          CATGeometry*                  iOriginalGeom,
                          const CATMathTransformation&  iTransfo, 
                          CATGeoTemporary*&             ioResult,
                          CATBoolean                    iForCoverage = FALSE);
  
  //---------------------------------------------------------------------------
  // Pour une vraie gestion de Factory Temporaire
  //---------------------------------------------------------------------------  
  static void        RemoveAllUnusedGeoTemporary();

  virtual CATBoolean CanBeRemoved() = 0;

  virtual ~CATGeoTemporary();
  
  virtual HRESULT SetIntValue(int iValue) = 0;
  virtual HRESULT GetIntValue(int& ioValue) = 0;

  // csr le passage par copie en raison impact build Unix CATIAShapeAccess/Mechanical...
  virtual HRESULT SetMathPoint(const CATMathPoint & iMathPoint) = 0;

  virtual HRESULT GetMathPoint(CATMathPoint& ioMathPoint) = 0;
  
  virtual HRESULT GetGeom(CATGeometry*& ioGeom) = 0;
  
  virtual HRESULT GetMathTransfo(CATMathTransformation &ioTransfo) = 0;

// Pour debug
  /** @nodoc */
  CATULONG64 GetTemporaryTag();

  /** @nodoc */
  virtual void ActivateTrace() = 0;

  /** @nodoc */
  virtual void DesactivateTrace() = 0;
  
  /** @nodoc */
  CATCGMNewClassArrayDeclare;

  /** @nodoc */
  INLINE CATULONG64 GetTempoTag()
  {
    return _TempoTag;
  }


  static CATBoolean  NEW_TEMPORARYGEO();


protected :
  
  CATGeoTemporary();
  
  virtual void ClearCGM(const CATBoolean iForceRelease = FALSE) = 0;

  virtual ULONG GetImpl_mcRef() = 0;
  virtual ULONG GetImplGeom_mcRef() = 0;

  //---------------------------------------------------------------------------
  // Pseudo gestion tag
  //---------------------------------------------------------------------------
  static CATULONG64 _TempoTagCounter;
  CATULONG64        _TempoTag;

  //---------------------------------------------------------------------------
  // Gestion des objets encore vivants
  //---------------------------------------------------------------------------
  CATGeoTemporary        *_PrevTemporary;
  CATGeoTemporary        *_NextTemporary;
  static CATGeoTemporary *_ChainTemporary;

  //---------------------------------------------------------------------------
  // Trigger pour les traces de debug de DisplayChainTemporaryList
  //---------------------------------------------------------------------------
  static CATBoolean _TracesOn;

  //---------------------------------------------------------------------------
  // IR-734994 : pour gestion de la destruction de la Factory Temporaire
  //---------------------------------------------------------------------------
  //static CATBoolean _GarbageCollector;

  // Pour nouvelle delegation
  static int _New_Delegation_System;

private :
  static CATGeoTemporary *_NextInDeletionTemporary;
  static void _RemoveAllUnusedGeoTemporary();
  static void _RemoveUnusedGeoTemporary(CATGeoTemporary * iToRemove);
  void Insert();
  void Remove();

};

#endif
