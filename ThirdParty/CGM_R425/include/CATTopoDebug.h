/* -*-c++-*- */
#ifndef CATTopoDebug_H_
#define CATTopoDebug_H_
// COPYRIGHT DASSAULT SYSTEMES  2002
//============================================================================
//  Dynamic invokation of Build-In But Debug Only Software
//============================================================================
// Oct. 05 SetCoverageMode_CATCX_UPWARD(...)                             HCN
//============================================================================

#include "ExportedByCATTopologicalObjects.h"

#include <stddef.h>
#include "CATDataType.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATTopology.h"
#include "ListVOfLong.h"
#include "ListPOfCATConnectedCellsIterator.h"
#include "ListPOfListPOfCATConnectedCellsIterator.h"
#include "ListPOfCATDomain.h"
#include "CATMathInline.h"
#include "CATBoolean.h"

class CATBody;
class CATCGMOutput;
class CATGeoFactory;
class CATTopology;
class CATCXTopology;
class CATCX_CHECKUP;
class CATCXVertexIter;
class CATCXConnectedCells;

class ExportedByCATTopologicalObjects CATTopoDebug
{
public:

  INLINE static short IsAvailable();

  // keep only roots of Debug
  INLINE static CATBoolean IsTemporaryInactive();
  INLINE static CATBoolean SetTemporaryInactive(CATBoolean iInactivated);

  //---------------------------------------------------------------------------
  // Pour gestion des liens pose-Sur
  //---------------------------------------------------------------------------
  INLINE static void DumpLyingOn(CATGeoFactory   *iFactory,
                          CATCGMOutput     &ios,
                          int              &ioNumberOfCellWithLyingOn,
                          int              &ioNbCellWithGOODLyingOn,
                          int              &ioNbCellWithBADLyingOn );

  INLINE static void DumpHiddenSubdOccurences(CATTopology    *iTopology,
                                       CATCGMOutput   &ios,
                                       int            &ioNumberOfHiddenSubdOccurences);

  INLINE static void GetCellWithLyingOns(CATGeoFactory   *iFactory, CATLISTP(CATCell) & ioCells);

  //---------------------------------------------------------------------------
  // Body / CellsHighestDimension avec isLocallyManifold
  //---------------------------------------------------------------------------
  INLINE static void isLocallyManifold(
    CATBody                 * iBody,
    const CATLONG32                iCellsMaxDim,
    const CATBoolean          isHomogeneous, 
    const CATBoolean          isLocallyManifold,
    const CATLISTP(CATCell)   iFreeCell,
    const CATLISTP(CATCell)   iNonManifoldCell);

  //---------------------------------------------------------------------------
  // Controle validite des liens inverses de modelisation
  //---------------------------------------------------------------------------
  INLINE static void CheckActivation(CATCXTopology *iContext = NULL);
  INLINE static void CheckUpwardLinks(CATCXTopology *iTopo, CATCX_CHECKUP *iReport);
  INLINE static CATBoolean SetCoverageMode_CATCX_UPWARD(CATBoolean _iActive);

  //---------------------------------------------------------------------------
  // Gestion deportee du Debug CATCX_NCGM
  //---------------------------------------------------------------------------
  INLINE static void DebugVertexIter(CATCXVertexIter *iter);
  
  INLINE static void DebugIsSharingTopology(CATTopology* iFirst, CATTopology* iWith, 
    CATBoolean result,   CATLISTP(CATTopology) *ioSharingFederator);
  
  INLINE static void DebugHasInfiniteGeometry(CATBody *iBody, CATBoolean result);
  
  INLINE static void DebugFacePropagate(CATBody *iBody, 
    CATLISTP(CATFace)    *  iInitialFaces, 
    CATLISTP(CATFace)    &  result);
  
  INLINE static void DebugBodyCellNeighbours(CATBody *iBody,
    const CATLISTP(CATCell) * iCellList, 
    const CATListOfLong     * inputOrientations,    
    const short iVersionGenericNaming,
    CATLISTP(CATCell)       & result,
    CATListOfLong           & oNbOfCellsByDomain );
  
  
  INLINE static void DebugBorderedFaces(CATBody *iBody, CATCell *iCell,
                                      CATLISTP(CATCell) & oFaces,
                                      CATListOfLong     & oNbOfFacesByDomain,
                                      short iSoftwareLevel,HRESULT result) ;

  INLINE static void DebugCellNeighbours(CATCell *iCell, CATBody *inBody, ListPOfCATCell  &oCell, HRESULT result);
  
  INLINE static void DebugSelectEdgesFromFaces(CATBody  *iBody, 
    const CATLISTP(CATFace) & iFaceList,    CATLISTP(CATCell) &result);
  
  


  INLINE static void DebugInternalVertices(CATBody *  iBody,
    const CATLISTP(CATCell) &  iFaces1,
    const CATLISTP(CATCell) &  iFaces2,
    CATLISTP(CATCell)       &  iVertices);
  
  
  INLINE static void DebugCommonEdgesBefore(CATBody *  iBody,
    const CATLISTP(CATCell) &  iFaces1, 
    const CATLISTP(CATCell) &  iFaces2);
  
  INLINE static void DebugCommonEdges(CATBody *  iBody,
    const CATLISTP(CATCell) &  iFaces1, 
    const CATLISTP(CATCell) &  iFaces2,
    CATLISTP(CATCell)         & ioResult,
    CATListOfLong             & ioListOrientation,
    CATListOfLong             & ioNbOfEdgesByDomain);

  INLINE static void DebugGroupCells(const CATLISTP(CATCell)& cellsInput, 
                                     CATBody* body,
                                     CATLISTP(CATConnectedCellsIterator) & oCellsIterator);
  
  INLINE static void DebugGroupManyCells(const CATLISTP(CATCell)& cellsInput, 
                                         CATBody* body,
                                         CATLISTP(CATConnectedCellsIterator) & oCellsIterator);
  
  INLINE static void DebugCommonCells(const CATLISTP(CATConnectedCellsIterator)& iList,
                                         CATLISTP(CATConnectedCellsIterator) &oList);
  
 INLINE static void DebugSelectBoundary(CATCXConnectedCells *iCtx, CATLISTP(CATConnectedCellsIterator) &oList);


  INLINE static void DebugCreateDomainsBefore (CATBody* iBody,const CATLISTP(CATCell)& iCells, 
                                               const CATListOfInt& iOris);

  INLINE static void DebugCreateDomains(CATBody* iBody,const CATLISTP(CATCell)& iCells, 
                                               const CATListOfInt& iOris,
                                               const CATLISTP(CATDomain) & Domains);



  //---------------------------------------------------------------------------
  // Obtention du niveau de versioning CGM lors de l'achevement de construction
  //---------------------------------------------------------------------------
  static short GetCompletedLevel(CATBody *iBody);

  //---------------------------------------------------------------------------
  // For Debug Only, obtention du contexte du dernier Body aggregeant 
  //---------------------------------------------------------------------------
  static CATBody * GetLastBodyContextForDebugOnly(CATTopology *iTopology);


protected :
  //---------------------------------------------------------------------------------
  // Pour gestion interne 
  //---------------------------------------------------------------------------------
  CATTopoDebug();
  virtual ~CATTopoDebug();

  //---------------------------------------------------------------------------
  // Pour gestion des liens pose-Sur
  //---------------------------------------------------------------------------
  virtual void _DumpLyingOn(CATGeoFactory *iFactory,
                          CATCGMOutput       &ios,
                          int                &ioNumberOfCellWithLyingOn,
                          int                &ioNbCellWithGOODLyingOn,
                          int                &ioNbCellWithBADLyingOn ) = 0; 

  virtual void _DumpHiddenSubdOccurences(CATTopology    *iTopology,
                                         CATCGMOutput   &ios,
                                         int            &ioNumberOfHiddenSubdOccurences) = 0; 

  virtual void _GetCellWithLyingOns(CATGeoFactory   *iFactory, CATLISTP(CATCell) & ioCells) = 0; 

  //---------------------------------------------------------------------------
  // Body / CellsHighestDimension avec isLocallyManifold
  //---------------------------------------------------------------------------
  virtual void _isLocallyManifold(
    CATBody                 * iBody,
    const CATLONG32                iCellsMaxDim,
    const CATBoolean          isHomogeneous, 
    const CATBoolean          isLocallyManifold,
    const CATLISTP(CATCell)   iFreeCell,
    const CATLISTP(CATCell)   iNonManifoldCell) = 0;

  //---------------------------------------------------------------------------
  // Controle validite des liens inverses de modelisation
  //---------------------------------------------------------------------------
  virtual void _CheckActivation(CATCXTopology *iContext) = 0;
  virtual void _CheckUpwardLinks(CATCXTopology *iTopo, CATCX_CHECKUP *iReport) = 0;
  virtual CATBoolean _SetCoverageMode_CATCX_UPWARD(CATBoolean _iActive) = 0;

  //---------------------------------------------------------------------------
  // Gestion deportee du Debug CATCX_NCGM
  //---------------------------------------------------------------------------
  virtual void _DebugVertexIter(CATCXVertexIter *iter) = 0;

  virtual void _DebugIsSharingTopology(CATTopology* iFirst, CATTopology* iWith, 
                                            CATBoolean result,   CATLISTP(CATTopology) *ioSharingFederator) = 0;

  virtual void _DebugHasInfiniteGeometry(CATBody *iBody, CATBoolean result) = 0;

  virtual void _DebugFacePropagate(CATBody *iBody, 
     CATLISTP(CATFace)    *  iInitialFaces, 
     CATLISTP(CATFace)    &  result) = 0;

  virtual void _DebugBodyCellNeighbours(CATBody *iBody,
    const CATLISTP(CATCell) * iCellList, 
    const CATListOfLong     * inputOrientations,  
    const short iVersionGenericNaming,    
    CATLISTP(CATCell)       & result,
    CATListOfLong           & oNbOfCellsByDomain ) = 0;
    

 virtual void _DebugBorderedFaces(CATBody *iBody, CATCell *iCell,
                                      CATLISTP(CATCell) & oFaces,
                                      CATListOfLong     & oNbOfFacesByDomain,
                                      short iSoftwareLevel,HRESULT result) = 0;

  virtual void _DebugCellNeighbours(CATCell *iCell, CATBody *inBody, ListPOfCATCell  &oCell, HRESULT result)= 0;
  
  virtual void _DebugSelectEdgesFromFaces(CATBody  *iBody, 
    const CATLISTP(CATFace) & iFaceList,    CATLISTP(CATCell) &result)= 0;


  virtual void _DebugInternalVertices(CATBody *  iBody,
    const CATLISTP(CATCell) &  iFaces1,
    const CATLISTP(CATCell) &  iFaces2,
    CATLISTP(CATCell)       &  iVertices)= 0;
  
  
  virtual void _DebugCommonEdgesBefore(CATBody *  iBody,
    const CATLISTP(CATCell) &  iFaces1, 
    const CATLISTP(CATCell) &  iFaces2)= 0;
  
  virtual void _DebugCommonEdges(CATBody *  iBody,
    const CATLISTP(CATCell) &  iFaces1, 
    const CATLISTP(CATCell) &  iFaces2,
    CATLISTP(CATCell)         & ioResult,
    CATListOfLong             & ioListOrientation,
    CATListOfLong             & ioNbOfEdgesByDomain)= 0;

  virtual void _DebugGroupCells(const CATLISTP(CATCell)& cellsInput, 
                                     CATBody* body,
                                     CATLISTP(CATConnectedCellsIterator) & oCellsIterator)= 0;
  
  virtual void _DebugGroupManyCells(const CATLISTP(CATCell)& cellsInput, 
                                         CATBody* body,
                                         CATLISTP(CATConnectedCellsIterator) & oCellsIterator)= 0;
  
  virtual void _DebugCommonCells(const CATLISTP(CATConnectedCellsIterator)& iList,
                                         CATLISTP(CATConnectedCellsIterator) &oList)= 0;
  
 virtual void _DebugSelectBoundary(CATCXConnectedCells *iCtx, CATLISTP(CATConnectedCellsIterator) &oList)= 0;


  virtual void _DebugCreateDomainsBefore (CATBody* iBody,const CATLISTP(CATCell)& iCells, 
                                               const CATListOfInt& iOris)= 0;

  virtual void _DebugCreateDomains(CATBody* iBody,const CATLISTP(CATCell)& iCells, 
                                               const CATListOfInt& iOris,
                                               const CATLISTP(CATDomain) & Domains)= 0;


  //---------------------------------------------------------------------------
  // Acces a l'init
  //---------------------------------------------------------------------------
  static CATTopoDebug *GetDebugOnly();
  static CATTopoDebug *_Debug;
  static short         _Once;

  static CATBoolean   _TemporaryInactivated; // keep only roots 

};

//-----------------------------------------------------------
// IsAvailable
//-----------------------------------------------------------
INLINE short CATTopoDebug::IsAvailable()
{
  return ( (_Once || GetDebugOnly()) && _Debug ) ? 1 : 0;
}



// keep only roots of Debug
INLINE CATBoolean CATTopoDebug::IsTemporaryInactive() 
{ return _TemporaryInactivated; }

INLINE CATBoolean CATTopoDebug::SetTemporaryInactive(CATBoolean iInactivated) 
{ _TemporaryInactivated = iInactivated; return _TemporaryInactivated; }


//---------------------------------------------------------------------------
// Body / CellsHighestDimension avec isLocallyManifold
//---------------------------------------------------------------------------
INLINE void  CATTopoDebug::isLocallyManifold(
    CATBody                 * iBody,
    const CATLONG32                iCellsMaxDim,
    const CATBoolean          isHomogeneous, 
    const CATBoolean          isLocallyManifold,
    const CATLISTP(CATCell)   iFreeCell,
    const CATLISTP(CATCell)   iNonManifoldCell)
{
  if ( (_Once || GetDebugOnly()) && _Debug )
    _Debug->_isLocallyManifold(iBody,iCellsMaxDim,isHomogeneous,isLocallyManifold,iFreeCell,iNonManifoldCell);
}


//---------------------------------------------------------------------------
// Pour gestion des liens pose-Sur
//---------------------------------------------------------------------------
INLINE void  CATTopoDebug::DumpLyingOn(CATGeoFactory      *iFactory, CATCGMOutput       &ios,
                                     int                &ioNumberOfCellWithLyingOn,
                                     int                &ioNbCellWithGOODLyingOn,
                                     int                &ioNbCellWithBADLyingOn )
{
  if ( (_Once || GetDebugOnly()) && _Debug )
    _Debug->_DumpLyingOn(iFactory,ios,ioNumberOfCellWithLyingOn,ioNbCellWithGOODLyingOn,ioNbCellWithBADLyingOn);
}

//---------------------------------------------------------------------------
// Pour gestion des liens pose-Sur
//---------------------------------------------------------------------------
INLINE void  CATTopoDebug::DumpHiddenSubdOccurences(CATTopology    *iTopology, CATCGMOutput &ios,
                                                    int            &ioNumberOfHiddenSubdOccurences) 
{
  if ( (_Once || GetDebugOnly()) && _Debug )
    _Debug->_DumpHiddenSubdOccurences(iTopology,ios,ioNumberOfHiddenSubdOccurences);
}

//---------------------------------------------------------------------------
// Pour gestion des liens pose-Sur
//---------------------------------------------------------------------------
INLINE void CATTopoDebug::GetCellWithLyingOns(CATGeoFactory   *iFactory, CATLISTP(CATCell) & ioCells)
{
  if ( (_Once || GetDebugOnly()) && _Debug )
    _Debug->_GetCellWithLyingOns(iFactory,ioCells);
}

//---------------------------------------------------------------------------
// Controle validite des liens inverses de modelisation
//---------------------------------------------------------------------------
INLINE void  CATTopoDebug::CheckActivation(CATCXTopology *iContext) 
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_CheckActivation(iContext);
}


//---------------------------------------------------------------------------
// Controle validite des liens inverses de modelisation
//---------------------------------------------------------------------------
INLINE void  CATTopoDebug::CheckUpwardLinks(CATCXTopology *iTopo, CATCX_CHECKUP *iReport)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_CheckUpwardLinks(iTopo,iReport);
}


//---------------------------------------------------------------------------
// Controle validite des liens inverses de modelisation
//---------------------------------------------------------------------------
INLINE CATBoolean CATTopoDebug::SetCoverageMode_CATCX_UPWARD(CATBoolean _iActive)
{
  if ( (_Once || GetDebugOnly()) && _Debug )
    return _Debug->_SetCoverageMode_CATCX_UPWARD(_iActive);
  else
    return FALSE;
}

//---------------------------------------------------------------------------
// DebugVertexIter
//---------------------------------------------------------------------------
INLINE void  CATTopoDebug::DebugVertexIter(CATCXVertexIter *iter)
{
  if ( (_Once || GetDebugOnly()) && _Debug && ! _TemporaryInactivated ) _Debug->_DebugVertexIter(iter);
}

//---------------------------------------------------------------------------
// DebugIsSharingTopology
//---------------------------------------------------------------------------
INLINE void  CATTopoDebug::DebugIsSharingTopology(CATTopology* iFirst, CATTopology* iWith, 
                                            CATBoolean result,   CATLISTP(CATTopology) *ioSharingFederator)
{
  if ( (_Once || GetDebugOnly()) && _Debug && ! _TemporaryInactivated ) _Debug->_DebugIsSharingTopology(iFirst,iWith,result,ioSharingFederator);
}

//---------------------------------------------------------------------------
// DebugHasInfiniteGeometry
//---------------------------------------------------------------------------
INLINE void  CATTopoDebug::DebugHasInfiniteGeometry(CATBody *iBody, CATBoolean result)
{
  if ( (_Once || GetDebugOnly()) && _Debug && ! _TemporaryInactivated) _Debug->_DebugHasInfiniteGeometry(iBody,result);
}

//---------------------------------------------------------------------------
// DebugFacePropagate
//---------------------------------------------------------------------------
INLINE void  CATTopoDebug::DebugFacePropagate(CATBody *iBody, 
     CATLISTP(CATFace)    *  iInitialFaces, CATLISTP(CATFace)    &  result)
{
  if ( (_Once || GetDebugOnly()) && _Debug && ! _TemporaryInactivated) _Debug->_DebugFacePropagate(iBody,iInitialFaces,result);
}

//---------------------------------------------------------------------------
// DebugFacePropagate
//---------------------------------------------------------------------------
INLINE void  CATTopoDebug::DebugBodyCellNeighbours(CATBody *iBody,
    const CATLISTP(CATCell) * iCellList, 
    const CATListOfLong     * inputOrientations,    
    const short iVersionGenericNaming,
    CATLISTP(CATCell)       & result,
    CATListOfLong           & oNbOfCellsByDomain )
{
  if ( (_Once || GetDebugOnly()) && _Debug && ! _TemporaryInactivated)
    _Debug->_DebugBodyCellNeighbours(iBody,iCellList,inputOrientations,iVersionGenericNaming,result,oNbOfCellsByDomain);
}

//---------------------------------------------------------------------------
// DebugFacePropagate
//---------------------------------------------------------------------------
INLINE void  CATTopoDebug::DebugBorderedFaces(CATBody *iBody, CATCell *iCell,
                                      CATLISTP(CATCell) & oFaces,
                                      CATListOfLong     & oNbOfFacesByDomain,
                                      short iSoftwareLevel,HRESULT result)
{
  if ( (_Once || GetDebugOnly()) && _Debug && ! _TemporaryInactivated )
    _Debug->_DebugBorderedFaces(iBody,iCell,oFaces,oNbOfFacesByDomain,iSoftwareLevel,result);
}

//---------------------------------------------------------------------------
// DebugCellNeighbours
//---------------------------------------------------------------------------
INLINE void  CATTopoDebug::DebugCellNeighbours(CATCell *iCell, CATBody *inBody, ListPOfCATCell  &oCell, HRESULT result)
{
  if ( (_Once || GetDebugOnly()) && _Debug  && ! _TemporaryInactivated ) _Debug->_DebugCellNeighbours(iCell,inBody,oCell,result);
}

//---------------------------------------------------------------------------
// DebugSelectEdgesFromFaces
//---------------------------------------------------------------------------
INLINE void  CATTopoDebug::DebugSelectEdgesFromFaces(CATBody  *iBody, 
                                                     const CATLISTP(CATFace) & iFaceList,    CATLISTP(CATCell) &result)
{
  if ( (_Once || GetDebugOnly()) && _Debug  && ! _TemporaryInactivated) _Debug->_DebugSelectEdgesFromFaces(iBody,iFaceList,result);
}

//---------------------------------------------------------------------------
// DebugInternalVertices
//---------------------------------------------------------------------------
INLINE void CATTopoDebug::DebugInternalVertices(CATBody *  iBody,
                                                       const CATLISTP(CATCell) &  iFaces1,
                                                       const CATLISTP(CATCell) &  iFaces2,
                                                       CATLISTP(CATCell)       &  iVertices)
{
  if ( (_Once || GetDebugOnly()) && _Debug  && ! _TemporaryInactivated) _Debug->_DebugInternalVertices(iBody,iFaces1,iFaces2,iVertices);
}

//---------------------------------------------------------------------------
// DebugCommonEdgesBefore
//---------------------------------------------------------------------------
INLINE void CATTopoDebug::DebugCommonEdgesBefore(CATBody *  iBody,
                                                        const CATLISTP(CATCell) &  iFaces1, 
                                                        const CATLISTP(CATCell) &  iFaces2)
{
  if ( (_Once || GetDebugOnly()) && _Debug  && ! _TemporaryInactivated) _Debug->_DebugCommonEdgesBefore(iBody,iFaces1,iFaces2);
}

//---------------------------------------------------------------------------
// DebugCommonEdges
//---------------------------------------------------------------------------
INLINE void CATTopoDebug::DebugCommonEdges(CATBody *  iBody,
                                                  const CATLISTP(CATCell) &  iFaces1, 
                                                  const CATLISTP(CATCell) &  iFaces2,
                                                  CATLISTP(CATCell)         & ioResult,
                                                  CATListOfLong             & ioListOrientation,
                                                  CATListOfLong             & ioNbOfEdgesByDomain)
{
  if ( (_Once || GetDebugOnly()) && _Debug && ! _TemporaryInactivated ) _Debug->_DebugCommonEdges(iBody,iFaces1,iFaces2,ioResult,ioListOrientation,ioNbOfEdgesByDomain);
}

//---------------------------------------------------------------------------
// DebugGroupCells
//---------------------------------------------------------------------------
INLINE void CATTopoDebug::DebugGroupCells(const CATLISTP(CATCell)& cellsInput, 
                                                 CATBody* body,
                                                 CATLISTP(CATConnectedCellsIterator) & oCellsIterator)
{
  if ( (_Once || GetDebugOnly()) && _Debug  && ! _TemporaryInactivated) _Debug->_DebugGroupCells(cellsInput,body,oCellsIterator);
}

//---------------------------------------------------------------------------
// DebugGroupManyCells
//---------------------------------------------------------------------------
INLINE void CATTopoDebug::DebugGroupManyCells(const CATLISTP(CATCell)& cellsInput, 
                                                     CATBody* body,
                                                     CATLISTP(CATConnectedCellsIterator) & oCellsIterator)
{
  if ( (_Once || GetDebugOnly()) && _Debug  && ! _TemporaryInactivated) _Debug->_DebugGroupManyCells(cellsInput,body,oCellsIterator);
}

//---------------------------------------------------------------------------
// DebugCommonCells
//---------------------------------------------------------------------------
INLINE void CATTopoDebug::DebugCommonCells(const CATLISTP(CATConnectedCellsIterator)& iList,
                                                  CATLISTP(CATConnectedCellsIterator) &oList)
{
  if ( (_Once || GetDebugOnly()) && _Debug  && ! _TemporaryInactivated) _Debug->_DebugCommonCells(iList,oList);
}

//---------------------------------------------------------------------------
// DebugSelectBoundary
//---------------------------------------------------------------------------
INLINE void CATTopoDebug::DebugSelectBoundary(CATCXConnectedCells *iCtx, CATLISTP(CATConnectedCellsIterator) &oList)
{
  if ( (_Once || GetDebugOnly()) && _Debug && ! _TemporaryInactivated ) _Debug->_DebugSelectBoundary(iCtx,oList);
}

//---------------------------------------------------------------------------
// DebugCreateDomainsBefore
//---------------------------------------------------------------------------
INLINE void CATTopoDebug::DebugCreateDomainsBefore (CATBody* iBody,const CATLISTP(CATCell)& iCells, 
                                                           const CATListOfInt& iOris)
{
  if ( (_Once || GetDebugOnly()) && _Debug  && ! _TemporaryInactivated) _Debug->_DebugCreateDomainsBefore(iBody,iCells,iOris);
}

//---------------------------------------------------------------------------
// DebugCreateDomains
//---------------------------------------------------------------------------
INLINE void CATTopoDebug::DebugCreateDomains(CATBody* iBody,const CATLISTP(CATCell)& iCells, 
                                             const CATListOfInt& iOris,
                                             const CATLISTP(CATDomain) & Domains)
{
  if ( (_Once || GetDebugOnly()) && _Debug  && ! _TemporaryInactivated) _Debug->_DebugCreateDomains(iBody,iCells,iOris,Domains);
}

#endif
