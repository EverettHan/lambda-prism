#ifndef CATCellManifoldGroupNavigator_H
#define CATCellManifoldGroupNavigator_H

#include "CATGMModelInterfaces.h"
#include "CATManifoldNavigator.h"
#include "ListPOfCATCell.h"
#include "CATErrorDef.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATIAV5Level.h"
#include "ListPOfCATCellManifold.h"

class CATCellManifoldGroup;
class CATCellManifoldExtrusionNavigatorInterface;
class CATCellManifoldHoleNavigatorInterface;
class CATCellManifoldSlotNavigatorInterface;
class CATCellManifoldNotchNavigatorInterface;
class CATCellManifoldPadPocketNavigatorInterface;
class CATCellManifoldPatternNavigator;
class CATCellManifoldOffsetNavigator;
class CATCellManifoldPatternNavigatorInterface;
class CATCellManifoldSHMNavigator;
class CATCellManifoldCutoutNavigatorInterface;
class CATCellManifoldCutoutNavigator;
class CATCellManifoldLogoNavigatorInterface;
class CATCellManifoldLogoNavigator;
class CATCellManifoldCRTNavigator;
class CATCellManifoldCRTWallNavigator;
class CATCellManifoldCRTBendNavigator;
class CATCellManifoldCRTGlueNavigator;
class CATCGMOutput;
class CATCellManifoldGroupCarrier;
class CATCGMJournalList;
class CATLiveBody;
class CATCellManifoldOffsetNavigatorInterface;
class CATTopData;
class CATCellManifoldCRTCurvedBendNavigator;
class CATAdvancedStampNavigator;
class CATCellManifoldVolatileDraftGroupNavigator;
class CATCellManifoldThinWallDraftGroupNavigator;
class CATCellManifoldPairingGroupNavigator;
class CATCellManifoldWallNavigatorInterface;
class CATCellManifoldWallNavigator;
class CATCellManifoldBendNavigatorInterface;
class CATCellManifoldBendNavigator;

class ExportedByCATGMModelInterfaces CATCellManifoldGroupNavigator : public CATManifoldNavigator
{
public:

  // Constructor
  CATCellManifoldGroupNavigator();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Destructor
  virtual ~CATCellManifoldGroupNavigator();

  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const;

  virtual HRESULT GetCells(ListPOfCATCell& oCells) const;

  virtual CATCellManifoldGroup * BelongsToGroup(CATCellManifold *ipCellManifold) const;

  //return TRUE if iCells cover all the group. Could be overloaded (as in Pattern)
  virtual CATBoolean IsFullyCoveredByCells(const ListPOfCATCellManifold &iCellManifolds);

  // return TRUE if the group is modifiable with operator CATManifoldEditor. FALSE is the default value
  virtual CATBoolean IsEditable() const;

  // Pattern Offset
  virtual CATCellManifoldPatternNavigator *            GetAsPatternNavigator();
  virtual CATCellManifoldOffsetNavigator *             GetAsOffsetNavigator();
  virtual CATCellManifoldPatternNavigatorInterface *   GetAsPatternNavigatorInterface();
  virtual CATCellManifoldOffsetNavigatorInterface  *   GetAsOffsetNavigatorInterface(); 

  // Extrusion Hole Slot Notch Pocket Logo Cutout
  virtual CATCellManifoldExtrusionNavigatorInterface * GetAsExtrusionNavigatorInterface(); 
  virtual CATCellManifoldHoleNavigatorInterface *      GetAsHoleNavigatorInterface();
  virtual CATCellManifoldSlotNavigatorInterface *      GetAsSlotNavigatorInterface();
  virtual CATCellManifoldNotchNavigatorInterface *     GetAsNotchNavigatorInterface();
  virtual CATCellManifoldPadPocketNavigatorInterface*  GetAsPadPocketNavigatorInterface();
  virtual CATCellManifoldLogoNavigatorInterface *      GetAsLogoNavigatorInterface(); 
  virtual CATCellManifoldLogoNavigator   *             GetAsLogoNavigator();
  virtual CATCellManifoldCutoutNavigatorInterface *    GetAsCutoutNavigatorInterface();
  virtual CATCellManifoldCutoutNavigator *             GetAsCutoutNavigator();

  // Wall Bend
  virtual CATCellManifoldWallNavigatorInterface *      GetAsWallNavigatorInterface();
  virtual CATCellManifoldWallNavigator *               GetAsWallNavigator();
  virtual CATCellManifoldBendNavigatorInterface *      GetAsBendNavigatorInterface();
  virtual CATCellManifoldBendNavigator *               GetAsBendNavigator();

  // SHM and CRT
  virtual CATCellManifoldSHMNavigator *                GetAsSHMNavigator();
  virtual CATCellManifoldCRTNavigator *                GetAsCRTNavigator();
  virtual CATCellManifoldCRTWallNavigator *            GetAsCRTWallNavigator();
  virtual CATCellManifoldCRTBendNavigator *            GetAsCRTBendNavigator();
  virtual CATCellManifoldCRTGlueNavigator *            GetAsCRTGlueNavigator();
  virtual CATCellManifoldCRTCurvedBendNavigator *      GetAsCRTCurvedBendNavigator();

  // AdvancedStamp
  virtual CATAdvancedStampNavigator *                  GetAsAdvancedStampNavigator();

  // Draft grouping
  virtual CATCellManifoldVolatileDraftGroupNavigator * GetAsVolatileDraftGroupNavigator();
  virtual CATCellManifoldThinWallDraftGroupNavigator * GetAsThinWallDraftGroupNavigator();

  // Pairing
  virtual CATCellManifoldPairingGroupNavigator *       GetAsPairingGroupNavigator();

  virtual void Dump(CATCGMOutput& Output);

protected:

  void SetTopData(const CATTopData & iTopData);

private:
  virtual CATCellManifoldGroupNavigator* GetAsGroupNavigator();

protected:
  CATTopData * _TopData;

};


#endif
