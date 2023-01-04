// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : ZUT
//
// DESCRIPTION  : CATThinWallDraftSideManifoldAttribute
//
//=============================================================================
// Creation ZUT March 2020
//=============================================================================

#ifndef CATThinWallDraftSideManifoldAttribute_H
#define CATThinWallDraftSideManifoldAttribute_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATVolatileDraftGroupManifoldAttribute.h"
#include "CATDataType.h"
#include "CATTopDefine.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfListPOfCATEdge.h"
#include "CATMathInline.h"

class CATBody;
class CATCell;
class CATMathDirection;
class CATDraftManifold;
class CATGeoFactory;

class ExportedByPersistentCell CATThinWallDraftSideManifoldAttribute : public CATVolatileDraftGroupManifoldAttribute
{
public:
  CATCGMDeclareAttribute (CATThinWallDraftSideManifoldAttribute, CATVolatileDraftGroupManifoldAttribute);

  CATCGMNewClassArrayDeclare; // Pool allocation

  CATThinWallDraftSideManifoldAttribute();
  CATThinWallDraftSideManifoldAttribute( const CATLISTP(CATCellManifold) & iListOfDraftCMs, const CATLISTP(CATCellManifold) & iListOfLateralCMs );
  virtual ~CATThinWallDraftSideManifoldAttribute();

  // Cast
  virtual CATThinWallDraftSideManifoldAttribute * GetAsThinWallDraftSideManifoldAttribute();

  // ThinWallDraftSide specific method
  short HasCommonPullingDir( CATMathDirection * oPullingDir = NULL ) const;
  short HasCommonDraftAngle( CATAngle * oDraftAngle = NULL ) const;
  void GetListOfDraftCMs( CATLISTP(CATCellManifold) & oListOfDraftCMs ) const;
  void GetListOfLateralCMs( CATLISTP(CATCellManifold) & oListOfLateralCMs ) const;

  HRESULT ComputeListsOfDraftLateralConnections( CATBody & iBody, CATLISTP(ListPOfCATEdge) & oListsOfDraftLateralConnections ) const;

  // CellManifoldGroup generic methods
  virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory * iFactory) const;
  virtual CATBoolean AreSpecificDatasImagesEqualToParents(CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier)const;
  virtual CATBoolean HaveSameType(CATManifoldAttribute & iOtherManifoldAttribute)const;

  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);

  virtual void Dump(CATCGMOutput & oStr) const;
  virtual void GetColor(int & oRed, int & oGreen, int & oBlue) const;

  // Helper methods
  static void CompareDraftData( CATGeoFactory    & iFactory,
                                CATDraftManifold & iDraftDM,
                                CATDraftManifold & iOtherDraftDM,
                                short            * oHasSameDraftAngle = NULL,
                                CATAngle         * oDraftAngle        = NULL,
                                short            * oHasSamePullingDir = NULL,
                                CATMathDirection * oPullingDir        = NULL );

protected:

  CATGeoFactory * GetFactory() const;

  virtual void Write(CATCGMStream & ioStream) const;
  virtual void Read(CATCGMStream & ioStream);

  virtual CATManifoldAttribute * CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) & iListOfParentGroups, 
                                                      const CATCellManifoldGroup           & iImageCellManifoldGroup, 
                                                            CATCellManifoldsManager        & iCellManifoldsManager) const;

  // ATTRIBUTE DATA
  short                       _TWDSStreamVersion; // Version du stream
  CATLISTP(CATCellManifold)   _ListOfDraftCMs;
  CATLISTP(CATCellManifold)   _ListOfLateralCMs;
};

INLINE void CATThinWallDraftSideManifoldAttribute::GetListOfDraftCMs( CATLISTP(CATCellManifold) & oListOfDraftCMs ) const {
  oListOfDraftCMs = _ListOfDraftCMs; }

INLINE void CATThinWallDraftSideManifoldAttribute::GetListOfLateralCMs( CATLISTP(CATCellManifold) & oListOfLateralCMs ) const {
  oListOfLateralCMs = _ListOfLateralCMs; }

#endif /* CATThinWallDraftSideManifoldAttribute_H */
