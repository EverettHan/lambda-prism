//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : JJ3
//
// DESCRIPTION  : Class used to get righ cell on CDM constraints from CATCDMBaseServices.
//                CDMBaseInterfaces\ProtectedInterfaces\CATGMConstraint.h
//                CDMModel/CDMCGMBridge.m/src/CATGMConstraint.cpp
//
//=============================================================================
// 30/08/10  JJ3  Creation
//=============================================================================

#ifndef CATTransientCellTracker_H
#define CATTransientCellTracker_H

#include "CATCGMVirtual.h"
#include "PersistentCell.h"
#include "CATListOfCATCells.h"
#include "IUnknown.h" // For HRESULT
#include "CATSysErrorDef.h"
#include "CATPersistentCellInfra.h"
#include "ListPOfCATPersistentBodies.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "ListPOfCATCellManifold.h"
#include "CATListOfInt.h"
#include "CATSoftwareConfiguration.h"

class CATGMConstraint;
class CATCellManifold;
class CATListPtrCATCellManifold;
class CATCellManifoldGroup;


// @nocgmitf (this class doesn't need a CATIPGM interface)
class ExportedByPersistentCell CATTransientCellTracker : public CATCGMVirtual
{
public:
	
	// Constructor
  CATTransientCellTracker(CATPersistentCellInfra            & iPersistentInfra,
                          const ListPOfCATPersistentBodies  & iInputPersistentBodiesList,
                          const ListPOfCATPersistentBodies  & iCurrentPersistentBodiesList,
                          CATSoftwareConfiguration          * iConfig);

  CATBody * GetCurrentBody(const CATBody * iInputBody);

  void SetUnmodifiedBodies(ListPOfCATBody & iUnmodifiedBodyList);
	
  // Destructor
	virtual ~CATTransientCellTracker();

  // Translate Cell list
  HRESULT GetTranslatedCellList(const CATLISTP(CATCell)  & iInputCellList,
                                const CATBody           *  iInputBody,
                                CATLISTP(CATCell)        & oCurrentCellList,
                                CATBody                 *& oCurrentBody);

  HRESULT GetTranslatedCellList(const CATLISTP(CATCell)  & iInputCellList,
                                const CATBody           *  iInputBody,
                                CATLISTP(CATCell)        & oCurrentCellList,
                                CATListOfInt             & oOrientationCurrentCellvsInputCellList,  // 0 : not computed, 1: same orientation, -1: inverted orientation , 2: Error
                                CATBody                 *& oCurrentBody);


  HRESULT GetTranslatedCellManifold(const CATLISTP(CATCell)  & iInputCellList,
                                    const CATBody           *  iInputBody,
                                    CATCellManifold         *& oCurrentCellManifold,
                                    CATBody                 *& oCurrentBody);

  // Translate CellManifold list
  HRESULT GetTranslatedCellManifoldList(ListPOfCATCellManifold   & iInputCellManifoldList,
                                        const CATBody           *  iInputBody,
                                        ListPOfCATCellManifold   & oCurrentCellManifoldList,
                                        CATBody                 *& oCurrentBody);

  
  // Translate Group list
  HRESULT GetTranslatedCellManifoldList(ListPOfCATCellManifoldGroup  & iGroups,
                                        const CATBody               *  iInputBody,
                                        ListPOfCATCellManifold       & oCurrentCellManifoldList,
                                        CATBody                     *& oCurrentBody);


  HRESULT GetTranslatedCellList(ListPOfCATCellManifoldGroup  & iGroups,
                                const CATBody               *  iInputBody,
                                CATLISTP(CATCell)            & oCurrentCellList,
                                CATBody                     *& oCurrentBody);


  // Translate Group 
  HRESULT GetTranslatedCellList(CATCellManifoldGroup    *  iGroup,
                                const CATBody           *  iInputBody,
                                CATLISTP(CATCell)        & oCurrentCellList,
                                CATBody                 *& oCurrentBody);

  HRESULT GetTranslatedCellManifoldList(CATCellManifoldGroup    *  iGroup,
                                        const CATBody           *  iInputBody,
                                        ListPOfCATCellManifold   & oCurrentCellManifoldList,
                                        CATBody                 *& oCurrentBody);


  // Translate cell support from constraint
  HRESULT GetCellManifoldsSupport(CATGMConstraint           * iGMConstraint,
                                  int                         iNumber,
                                  CATLISTP(CATCellManifold) & oCurrentCellManifoldsList,
                                  CATLISTP(CATBody)         & oCurrentBodiesList);

  HRESULT GetCellManifoldsSupport(CATGMConstraint  * iGMConstraint,
                                  int                iNumber,
                                  CATCellManifold *& oCurrentCellManifolds,
                                  CATBody         *& oCurrentBodies);


  
  void Stream(CATGeoFactory *iFactory, CATCGMStream & ioStream);
  static CATTransientCellTracker * UnStream(CATGeoFactory *iFactory, CATSoftwareConfiguration * iConfig, CATCGMStream & ioStream);
  
  // Ajoute a ioBodiesList les bodies utilises par le TransientCellTracker.
  // Est appele par l'operateur qui utilise le TransientCellTracker pour Streamer les bodies necessaires.
  void GetBodies(CATLISTP(CATBody)  & ioBodiesList);


private:

  HRESULT GetTranslatedCellList(const CATLISTP(CATCell)  & iInputCellList,
                                const CATBody           *  iInputBody,
                                CATLISTP(CATCell)        & oCurrentCellList,
                                CATListOfInt            *  opOrientationCurrentCellvsInputCellList,  // 0 : not computed, 1: same orientation, -1: inverted orientation , 2: Error
                                CATBody                 *& oCurrentBody);

  void AppendEdgeOrientation(CATCell  * ipInputEdge,
    const CATLISTP(CATCell)  &  iImageEdgeList,
    CATBody           * ipInputBody,
    CATListOfInt      & oOrientationCurrentCellvsInputCellList);

  int ComputeStableEdgeOrientation(CATEdge  * ipEdge,
                                   CATFace  * ipFace,
                                   CATBody  * ipBody);


  CATBody * GetCurrentBody(const CATBody * iInputBody, CATPersistentBody *& ioCurrentPersistentBody);

  void GetCurrentBodies(CATLISTP(CATBody)  & ioBodiesList) const;



  CATPersistentCellInfra       * _PersistentInfra;
  ListPOfCATPersistentBodies     _InputPersistentBodiesList;
  ListPOfCATPersistentBodies     _CurrentPersistentBodiesList;
  ListPOfCATBody               * _UnmodifiedBodyList;

  CATSoftwareConfiguration     * _Config;

  CATBoolean    _CGMReplayMode;

};

// Create
ExportedByPersistentCell CATTransientCellTracker *CATCreateTransientCellTracker(CATPersistentCellInfra            & iPersistentInfra,
                                                                                const ListPOfCATPersistentBodies  & iInputPersistentBodiesList,
                                                                                const ListPOfCATPersistentBodies  & iCurrentPersistentBodiesList,
                                                                                CATSoftwareConfiguration          * iConfig);

#endif
