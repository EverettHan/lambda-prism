#ifndef CATCGMGeometryOfFatAble_H
#define CATCGMGeometryOfFatAble_H
//---------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2002
//---------------------------------------------------
//=============================================================================
// Nov. 02  Parametre ioUselessGeometries pour IsFat(...)                 HCN
// Jul. 03  _pNewStartPOEC, _pNewEndPOEC, GetNewPOECs(...)
//          Parametre iGeomTargetType pour IsFat(...)                     HCN
// Aug. 03  Parametre _EdgeCrvSimplRevOris, _POECWeakTopoLinkCountMismatch
//          _OldStarPOECWeakTopoLinkCount, _OldEndPOECWeakTopoLinkCount,
//          Copy Constructor pour CATCGMGeometryOfFatAble                 HCN
// Oct. 03  _AllSupports                                                  HCN
// Oct. 03  OverrideFatStatusReason                                       HCN
// Nov. 03  Parametre CATBoolean iFatEdgeRequired pour IsFat(...)
//          ReasonCurveOKInOtherEdge                                      HCN
// Dec. 03  ReasonEdgeCrvNotSimplifiable, ReasonCanonicCurves             HCN
// 2009 : For more precise analysis of targetted optimisation             TCX
//             Poec/Pos detection is delayed if their support are still usefull
//               (from strong link of Edge/Face defined in the context) 
//             even if no explicit topological usage [ Cell(Edge,) or Subd(LyingOn)) ]
//=============================================================================
#include "ExportedByGeometricObjects.h"
#include "CATCGMNewArray.h"
#include "CATListOfCATGeometries.h"
#include "CATGeometryType.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATMathInline.h"
#include "CATGeometry.h"

class CATCell;
class CATGeometry;
class CATCGMOutput;
class CATICGMObject;
class CATCGMGeometryOfFatAble;
class CATPointOnEdgeCurve;
class CATCGMOutput;
class CATCGMHashTable;
class CATSoftwareConfiguration;
 
//---------------------------------------------------
// Pour la geometrie cliente de Curve/Surface
//---------------------------------------------------
class  ExportedByGeometricObjects CATCGMGeometryOfAnyone
{
public:
  virtual ~CATCGMGeometryOfAnyone();
  CATCGMNewClassArrayDeclare;  
  CATCGMGeometryOfAnyone(CATICGMObject *Obj);


  CATICGMObject *const _Obj;


  CATCGMGeometryOfAnyone * const _PrevHashTable;
  CATCGMGeometryOfAnyone * const _NextHashTable;
 

  virtual void  Dump( CATCGMOutput& os );
  
  short                    isForCell() const;
  virtual CATCGMGeometryOfFatAble *FatAble()   const;

protected :

  // Coverage (explicit mkodt-impact) of found optimisable data structure
  short  FatBreak(short isFat);

private :
    CATCGMGeometryOfAnyone(const CATCGMGeometryOfAnyone&);
    CATCGMGeometryOfAnyone& operator=(const CATCGMGeometryOfAnyone&);
};



//---------------------------------------------------
// Pour la geometrie cliente de Curve/Surface
//---------------------------------------------------
class  ExportedByGeometricObjects CATCGMGeometryOfFatAble : public CATCGMGeometryOfAnyone
{
public:


  enum OverrideFatStatusReason { ReasonNone                   = 0x00000000,
                                 ReasonYetIsFat               = 0x00000001,
                                 ReasonLyingOnLink            = 0x00000002,
                                 ReasonEdgeInWire             = 0x00000004,
                                 ReasonCurveOKInOtherEdge     = 0x00000008,
                                 ReasonEdgeCrvNotSimplifiable = 0x00000010,
                                 ReasonCanonicCurves          = 0x00000020};

  CATCGMGeometryOfFatAble(CATCell *iCell, CATGeometry *iContainerOfSupport, short geometryOrientation );
  CATCGMGeometryOfFatAble(const CATCGMGeometryOfFatAble& FatAbleToCopy);
  virtual ~CATCGMGeometryOfFatAble();
  CATCGMNewClassArrayDeclare;  

  virtual void  Dump( CATCGMOutput& os );
  virtual CATCGMGeometryOfFatAble *FatAble()   const;

  //----------------------------------------------------------------------
  // Pour la phase d'analyse initiale de deduction des geometries utiles
  //----------------------------------------------------------------------
  CATLISTP(CATGeometry) _AllSupports; // renseigne apres l'appel a ::IsFat(...)

  CATLISTP(CATGeometry) _UsefullSupports;

  //---------------------------------------------------------------------------
  // Apres analyse de la modelisation
  // Determination du status optimal du support geometrique
  //     rc = 0 aucune simplification envisageable
  //     bit 1  : simplification de la geometry support
  //     bit 2  : simplification par passage au clonemanager (PoseSur)
  //---------------------------------------------------------------------------
  short IsLocallyFat(CATSoftwareConfiguration * iConfig,
                     CATCGMHashTable      * iUseFullSupport,
                     CATGeometry**          ioSimplifiedContainer,
                     CATGeometricType       iGeomTargetType,
                     CATLISTP(CATGeometry)* ioUselessGeometries,
                     CATBoolean             iFatEdgeRequired);

  //------------------------------------------------------
  // Pour la gestion des cellules
  //------------------------------------------------------
  CATCell              *GetCell() const;
  INLINE short          GetGeometryOrientation() const;
  INLINE void           GetNewPOECs(CATPointOnEdgeCurve** ioppNewStartPOEC, CATPointOnEdgeCurve** ioppNewEndPOEC) const;
  CATGeometry  *const   _OriginalContainer;  
  
  //--------------------------------------------------------------------------------------
  // Pour forcer une declaratoion de Simplication
  //  gestion des liens pose-sur que l'on devrait pas trouver sur de la Topologie DATUM
  //--------------------------------------------------------------------------------------
  INLINE short ContainsNonDatumModelisation() const;
  INLINE void  SetContainsNonDatumModelisation() ;

  //------------------------------------------------------
  // Pour gestion des exceptions
  //------------------------------------------------------
  // Passer CATCGMGeometryOfFatAble::ReasonNone) met _OverrideFatStatusReasons a 0
  void AddOverrideFatStatusReason(CATCGMGeometryOfFatAble::OverrideFatStatusReason iReason);

  CATCGMGeometryOfFatAble::OverrideFatStatusReason GetOverrideFatStatusReason();

  void DumpOverrideFatStatusReason(CATCGMOutput& iOutput);
  INLINE void  SetSimplifiedContainer(CATGeometry  * iSimplifiedContainer) ;
 
  // For Fat EdgeCurves simplification
  CATBoolean  _EdgeCrvSimplRevOris;
  CATULONG32  _OldStarPOECWeakTopoLinkCount;
  CATULONG32  _OldEndPOECWeakTopoLinkCount;
  CATBoolean  _POECWeakTopoLinkCountMismatch;
  
protected:

  //--------------------------------------------------------------------
  // Donnees membres de la classe
  //-------------------------------------------------------------------- 
  struct CATCGMStatus
  {
    unsigned char analyseFat            :1; 
    unsigned char FatGeometrySupport    :1; 
    unsigned char computedSimplified    :1; 
      signed char geometryOrientation   :4; 
    unsigned char containsNonDatumData  :1; 
  } _Status;

  CATGeometry            * _SimplifiedContainer;

  // For Fat EdgeCurves simplification
  CATPointOnEdgeCurve    * _pNewStartPOEC;
  CATPointOnEdgeCurve    * _pNewEndPOEC;

  CATCGMGeometryOfFatAble::OverrideFatStatusReason _OverrideFatStatusReasons;


private :
    CATCGMGeometryOfFatAble& operator=(const CATCGMGeometryOfFatAble&);

};


INLINE short CATCGMGeometryOfFatAble::GetGeometryOrientation() const
{
  return (short ) _Status.geometryOrientation;
}

INLINE void CATCGMGeometryOfFatAble::GetNewPOECs(CATPointOnEdgeCurve** ioppNewStartPOEC, CATPointOnEdgeCurve** ioppNewEndPOEC) const
{
  if (ioppNewStartPOEC)
    *ioppNewStartPOEC = _pNewStartPOEC;

  if (ioppNewEndPOEC)
    *ioppNewEndPOEC = _pNewEndPOEC;
}

INLINE short CATCGMGeometryOfFatAble::ContainsNonDatumModelisation() const
{
  return (short ) _Status.containsNonDatumData;
}

INLINE void CATCGMGeometryOfFatAble::SetContainsNonDatumModelisation() 
{
  _Status.containsNonDatumData = 1;
}

INLINE void  CATCGMGeometryOfFatAble::SetSimplifiedContainer(CATGeometry  * iSimplifiedContainer)  
{
  if (  _OriginalContainer == iSimplifiedContainer ) return;
  // if ( _OriginalContainer ) _OriginalContainer->Release();
  *((CATGeometry **)&_OriginalContainer) = iSimplifiedContainer;
  // if ( _OriginalContainer ) _OriginalContainer->AddRef();
}


#endif
