// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : ZUT
//
// DESCRIPTION  : CATThinWallDraftGroupManifoldAttribute
//
//=============================================================================
// Creation ZUT March 2020
//=============================================================================

#ifndef CATThinWallDraftGroupManifoldAttribute_H
#define CATThinWallDraftGroupManifoldAttribute_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATVolatileDraftGroupManifoldAttribute.h"
#include "CATDataType.h"
#include "ListPOfCATFace.h"
#include "CATMathPlane.h"
#include "CATXBoolean.h"
#include "CATMathInline.h"

class CATCell;

class ExportedByPersistentCell CATThinWallDraftGroupManifoldAttribute : public CATVolatileDraftGroupManifoldAttribute
{
public:
  CATCGMDeclareAttribute (CATThinWallDraftGroupManifoldAttribute, CATVolatileDraftGroupManifoldAttribute);

  CATCGMNewClassArrayDeclare; // Pool allocation

  CATThinWallDraftGroupManifoldAttribute();
  CATThinWallDraftGroupManifoldAttribute( const CATMathPlane & iMirrorPlane );
  virtual ~CATThinWallDraftGroupManifoldAttribute();

  // Cast
  virtual CATThinWallDraftGroupManifoldAttribute * GetAsThinWallDraftGroupManifoldAttribute();

  // ThinWallDraftGroup specific methods
  short HasMirrorPlane( CATMathPlane * oMirrorPlane = NULL) const;

  void SetNeutralSurfaceBody( CATBody * iNeutralSurfaceBody ); // Cache data
  CATBody* GetNeutralSurfaceBody() const; // Cache data. Handle with care, body may not exist anymore

  // CellManifoldGroup generic methods
  virtual CATCellManifoldGroupNavigator * CreateGroupNavigator(CATLiveBody * iLiveBody, const CATTopData & iTopData, CATCellManifoldGroup * iGroup) const;

  virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory * iFactory) const;
  virtual CATBoolean AreSpecificDatasImagesEqualToParents(CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier)const;
  virtual CATBoolean HaveSameType(CATManifoldAttribute & iOtherManifoldAttribute)const;

  virtual void ComputeSpecificTreatment(const CATLISTP(CATCellManifoldGroup)  & iParentGroups,
                                              CATLISTP(CATCellManifoldGroup)  & ioImageSonList,
                                              CATCellManifoldGroupCarrier    *  iCellManifoldGroupCarrier) const;

  virtual void OrganizeSonImageByGroup(CATLISTP(CATCellManifoldGroup)         & iCellManifoldGroupsToCarry,
                                       CATLISTP(CATCellManifoldGroup)         & iParentSonsImages,
                                       CATCellManifoldGroupCarrier           *  iCellManifoldGroupCarrier,
                                       CATLISTP(ListPOfCATCellManifoldGroup)  & oSortedSonsImages);

  virtual void OrganizeImageByGroup(CATLISTP(CATCellManifoldGroup)    & iCellManifoldGroupsToCarry,
                                    CATLISTP(CATCellManifold)         & iLeavesImages,
                                    CATListOfShort                   *  iLeavesImagesType,
                                    CATCellManifoldGroupCarrier      *  iCellManifoldGroupCarrier,
                                    CATCellManifoldGroupLayer        *  iGroupLayer,
                                    CATLISTP(ListPOfCATCellManifold)  & oSortedLeavesImages,
                                    CATLISTP(CATListOfShort)          & oSortedLeavesImagesType);

  virtual HRESULT ManageContextImages(CATLISTP(CATCellManifoldGroup)    iCellManifoldGroupsToCarry,
                                      CATCellManifoldGroupCarrier    *  iCellManifoldGroupCarrier,
                                      CATLISTP(CATCellManifold)       & oParentContextsImages,
                                      CATListOfShort                  & oParentContextsImagesType,
                                      CATXBooleanTrue                 & oContextsImagesWithType,
                                      CATXBooleanTrue                 & oImagesAreEqualToParents);

  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);

  virtual void Dump(CATCGMOutput & oStr) const;
  virtual void GetColor(int & oRed, int & oGreen, int & oBlue) const;

protected:

  virtual void Write(CATCGMStream & ioStream) const;
  virtual void Read(CATCGMStream & ioStream);

  virtual CATManifoldAttribute * CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) & iListOfParentGroups, 
                                                      const CATCellManifoldGroup           & iImageCellManifoldGroup, 
                                                            CATCellManifoldsManager        & iCellManifoldsManager) const;

  short          _TWDGStreamVersion; // Version du stream

  short          _HasMirrorPlane;
  CATMathPlane   _MirrorPlane;

  // Cache data (not streamed)
  CATBody      * _NeutralSurface;
};

INLINE short CATThinWallDraftGroupManifoldAttribute::HasMirrorPlane( CATMathPlane * oMirrorPlane ) const {
  if ( oMirrorPlane ) 
    *oMirrorPlane = ( _HasMirrorPlane ) ? ( _MirrorPlane ) : ( CATMathPlane() );
  return _HasMirrorPlane; }

INLINE void CATThinWallDraftGroupManifoldAttribute::SetNeutralSurfaceBody( CATBody * iNeutralSurfaceBody ) {
  _NeutralSurface = iNeutralSurfaceBody; }

INLINE CATBody* CATThinWallDraftGroupManifoldAttribute::GetNeutralSurfaceBody() const {
  return _NeutralSurface; }

#endif /* CATThinWallDraftGroupManifoldAttribute_H */
