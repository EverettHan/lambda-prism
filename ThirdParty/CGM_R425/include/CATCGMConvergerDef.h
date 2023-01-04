#ifndef CATCGMConvergerDef_H
#define CATCGMConvergerDef_H

// COPYRIGHT DASSAULT SYSTEMES 2022
 
  enum CATCVG_ApplicationName
  {    
    CATCVG_APPLI_CGM                = 1,
    CATCVG_APPLI_Machining,
    CATCVG_APPLI_PartDesign,
    CATCVG_APPLI_SheetMetal
  };

  enum CATCVG_CreationType
  {
    CATCVG_CREATE_Undef             = 0,
    CATCVG_CREATE_ExtrPrim          = 1,
    CATCVG_CREATE_ExtrReco,
    CATCVG_CREATE_LiveBody,
    CATCVG_CREATE_BRepDRep
  };

  enum CATCVG_FeatureType
  {
    CATCVG_FEAT_BTD_Hole            = 1, // BTD = BRepToDRep
    CATCVG_FEAT_BTD_Slot,
    CATCVG_FEAT_BTD_PPoc,
    CATCVG_FEAT_BTD_Notc,
    CATCVG_FEAT_BTD_TapH,
    CATCVG_FEAT_BTD_TapP,
    CATCVG_FEAT_BTD_LocP
  };

  enum CATCVG_PrimShapeType
  {
    CATCVG_SHAPE_ExtrOnly           = 1,
    CATCVG_SHAPE_WithDeco,
    CATCVG_SHAPE_WithSupp
  };



#endif
// Ne rien ecrire sous cette ligne
//==============================================================================
