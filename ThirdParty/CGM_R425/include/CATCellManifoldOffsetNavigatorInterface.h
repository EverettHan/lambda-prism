#ifndef CATCellManifoldOffsetNavigatorInterface_H
#define CATCellManifoldOffsetNavigatorInterface_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldGroupNavigator.h"
#include "ListPOfCATCellManifold.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATCollec.h"
#include "ListPOfCATFace.h"
#include "CATDeclarativeManifold.h"
#include "CATEdge.h"
#include "CATListOfShort.h"

class CATCell;
class CATOffsetLateralFacesManifoldAttribute;

class ExportedByCATGMModelInterfaces CATCellManifoldOffsetNavigatorInterface : public CATCellManifoldGroupNavigator
{
public:

  // Constructor
  CATCellManifoldOffsetNavigatorInterface(); 

  // Destructor
  virtual ~CATCellManifoldOffsetNavigatorInterface();

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATCellManifoldOffsetNavigatorInterface * GetAsOffsetNavigatorInterface();

  
  //-------------------------------------------------
  //    Methodes globales
  //-------------------------------------------------

  virtual HRESULT    GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const=0;
  // @nocgmitf
  virtual CATBoolean BelongsToOffsetGroup(CATCellManifold * iCM, short &oSkinNumber)=0;
  // @nocgmitf
  virtual CATBoolean BelongsToOffsetGroup(CATCell * iCell, short &oSkinNumber)=0;
  // @nocgmitf
  virtual double     GetOffsetValue(short iSkinNumber)=0; // we presume that each son of a skin has the same offsetValue - To Delete VB7
  // @nocgmitf
  virtual CATBoolean IsNullOffset(short iSkinNumber)=0; // we presume that each son of a skin has the same offsetValue - To Delete VB7
  // @nocgmitf
  virtual int        GetOverloadOffsetValues(short iSkinNumber, CATLISTP(CATCellManifoldGroup) &oOverloadCMGroupRef)=0;
  // @nocgmitf
  virtual CATBoolean HasUpdateGlobalThicknessInputs(short iSkinNumber, CATLISTP(CATFace) &oThickInputFaces, double &oThicknessValue)=0; // global value only - do not use when local value are overloaded
  // @nocgmitf
  virtual double     GetOffsetValue(short iSkinNumber, CATCellManifold * iCM)=0;
  // @nocgmitf
  virtual double     GetThicknessValue(short iFirstSkinNumber, short iSecondSkinNumber)=0;
  // @nocgmitf
  // For NaturalShape - assume that there is only two skins
  virtual double     GetThicknessValue(CATCellManifold * iCM)=0;
  //For OffsetReplicator - uses in hyperNavigator
  // @nocgmitf
  virtual void       GetThicknessValueImage(CATFace * iFace, double iThicknessValue, short iSkinNumber, double & oThicknessValue)=0;
  // input : fillet DeclarativeManifold and its radius, target Skin
  // output : radius of image of input DeclarativeManifold on target Skin
  // @nocgmitf
  virtual double     GetFilletParameterImage(double iFilletRadius, CATDeclarativeManifold * iDM, short iTargetSkin)=0;
  // input : edge where Fillet will be created and its radius, target Skin
  // output : radius after an offset on target Skin
  // @nocgmitf
  virtual double     GetFilletParameterImage(double iFilletRadius, CATEdge * iEdge, short iTargetSkin)=0;

  // @nocgmitf
  virtual void GetAllSkins(ListPOfCATCellManifoldGroup& oInstanceGroups, CATListOfShort & oSkinNumbers)=0;
  // @nocgmitf
  virtual int  GetSkinNumber(CATCellManifoldGroup * iGroup) const=0;

  // @nocgmitf
  virtual void GetSkinGroup(int iSkin, CATCellManifoldGroup *& oOffsetGroup)=0;

  // @nocgmitf
  virtual void GetAllCellManifolds( CATLISTP(CATCellManifold) &oCellManifolds)=0;
  // @nocgmitf
  virtual void GetSkinCellManifolds(int iSkinNumber, CATLISTP(CATCellManifold) &oSkinCellManifolds)=0;
  // @nocgmitf
  virtual void GetSkinCells(int iSkinNumber, CATLISTP(CATCell) &oSkinCells)=0;

  // @nocgmitf
  virtual void GetLateralFacesCellManifolds(CATLISTP(CATCellManifold) &oLateralCellManifolds)=0;

  // @nocgmitf <-------------- USED BY KUB/PKC
  virtual void GetReferenceCellManifolds(CATLISTP(CATCellManifold) & oReferenceCellManifolds)=0;
  // @nocgmitf
  virtual void GetReferenceCellManifold(CATCellManifold* &iSkinCellManifold, ListPOfCATCellManifold &oRefCellManifold)=0;
  // @nocgmitf 
  virtual void GetReferenceCellManifoldImages(CATCellManifold *        iReferenceCellManifold, 
                                      short                    iSkinNumber, 
                                      ListPOfCATCellManifold & oReferenceCellManifoldImages)=0;
  // @nocgmitf <-------------- USED BY KUB/PKC
  virtual void GetReferenceCellManifoldImages(CATCellManifold *        iReferenceCellManifold, 
                                      short                    iSkinNumber, 
                                      ListPOfCATCellManifold & oReferenceCellManifoldImages,
                                      double                 & oOffsetValue)=0;
  // @nocgmitf
  virtual void GetSkinCellManifoldImages(CATCellManifold *        iCellManifold,
                                 short                    iSkinNumber, 
                                 ListPOfCATCellManifold & oCellManifoldImages)=0;

  // @nocgmitf
  virtual void GetSkinCellManifoldImages(CATCellManifold *        iCellManifold,
                                 short                    iSkinNumber, 
                                 ListPOfCATCellManifold & oCellManifoldImages,
                                 double                 & oThicknessValue)=0;

  void Dump(CATCGMOutput& Output);

private:

};


#endif
