#ifndef CATCellManifoldGroupLayerCatalog_h
#define CATCellManifoldGroupLayerCatalog_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATIACGMLevel.h"
#include "CATCGMNewArray.h"
#include "CATBoolean.h"

class CATCellManifoldLogoLayer;
class CATCellManifoldWallAndBendLayer;
class CATCellManifoldExtrusionLayer;
class CATCellManifoldRigidBlockLayer;
class CATCellManifoldPatternLayer;
class CATCellManifoldOffsetLayer;
class CATCellManifoldContextualGroupLayer;
class CATCellManifoldGroupLayer;
class CATDRepGroupThreadLayer;
class CATCellManifoldAdvancedStampLayer;
class CATCellManifoldVolatileDraftGroupLayer;
class CATCellManifoldPairingGroupLayer;
class CATCGMStream;
//#ifdef CATIAR212
// class CATSHMLiveCellManifoldLayer;
//#endif

#include "CATGMModelInterfaces.h"
#include "ListPOfCATCellManifoldGroupLayer.h"
class ExportedByCATGMModelInterfaces CATCellManifoldGroupLayerCatalog
{
public:
  CATCellManifoldGroupLayerCatalog(); 
  virtual ~CATCellManifoldGroupLayerCatalog();
  static void Clean();

  static CATCellManifoldLogoLayer               * GetCellManifoldLogoLayer();
  static CATCellManifoldWallAndBendLayer        * GetCellManifoldWallAndBendLayer();
  static CATCellManifoldExtrusionLayer          * GetCellManifoldExtrusionLayer();
  static CATCellManifoldRigidBlockLayer         * GetCellManifoldRigidBlockLayer();
  static CATCellManifoldPatternLayer            * GetCellManifoldPatternLayer();
  static CATCellManifoldOffsetLayer             * GetCellManifoldOffsetLayer();
  static CATCellManifoldContextualGroupLayer    * GetCellManifoldContextualGroupLayer();
  static CATDRepGroupThreadLayer                * GetDRepGroupThreadLayer();
  static CATCellManifoldAdvancedStampLayer      * GetCellManifoldAdvancedStampLayer();
  static CATCellManifoldVolatileDraftGroupLayer * GetCellManifoldVolatileDraftGroupLayer();
  static CATCellManifoldPairingGroupLayer       * GetCellManifoldPairingGroupLayer();

  static int GetNumberOfLayer();
  static CATCellManifoldGroupLayer* GetLayer(int iLayerIndex);
  static CATBoolean LayerBelongsToCatalog(CATCellManifoldGroupLayer* iLayer,int &oLayerIndex);

  //Stream util
  static void StreamLayerList(const ListPOfCATCellManifoldGroupLayer & iLayerList, CATCGMStream& ioStr);
  static void UnstreamLayerList(ListPOfCATCellManifoldGroupLayer & oLayerList, CATCGMStream& ioStr);

protected:
  CATCellManifoldLogoLayer               * GetCellManifoldLogoLayerProtected();
  CATCellManifoldWallAndBendLayer        * GetCellManifoldWallAndBendLayerProtected();
  CATCellManifoldExtrusionLayer          * GetCellManifoldExtrusionLayerProtected();
  CATCellManifoldRigidBlockLayer         * GetCellManifoldRigidBlockLayerProtected();
  CATCellManifoldPatternLayer            * GetCellManifoldPatternLayerProtected();
  CATCellManifoldOffsetLayer             * GetCellManifoldOffsetLayerProtected();
  CATCellManifoldContextualGroupLayer    * GetCellManifoldContextualGroupLayerProtected();  
  CATDRepGroupThreadLayer                * GetDRepGroupThreadLayerProtected();
  CATCellManifoldAdvancedStampLayer      * GetCellManifoldAdvancedStampLayerProtected();
  CATCellManifoldVolatileDraftGroupLayer * GetCellManifoldVolatileDraftGroupLayerProtected();
  CATCellManifoldPairingGroupLayer       * GetCellManifoldPairingGroupLayerProtected();

  void CleanProtected();

private:
  CATCellManifoldLogoLayer                 * _Logo; 
  CATCellManifoldWallAndBendLayer          * _WallAndBend;
  CATCellManifoldExtrusionLayer            * _Extrusion; 
  CATCellManifoldRigidBlockLayer           * _RigidBlock;
  CATCellManifoldPatternLayer              * _Pattern;
  CATCellManifoldOffsetLayer               * _Offset;
  CATCellManifoldContextualGroupLayer      * _ContextualGroup;
  CATDRepGroupThreadLayer                  * _DRepGroupLayer;
  CATCellManifoldAdvancedStampLayer        * _AdvancedStampLayer;
  CATCellManifoldVolatileDraftGroupLayer   * _VolatileDraftGroupLayer;
  CATCellManifoldPairingGroupLayer         * _PairingGroupLayer;
};
#endif
