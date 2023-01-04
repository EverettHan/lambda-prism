// COPYRIGHT DASSAULT SYSTEMES 2012
//===============================================================================================================
//
// CATDeclarativeApplication :
// Name of the application for a live recognition.
// The application defines a list of recognizer agent, like filletRecognizer, chamferRecognizer, canonicRecognizer.
//
//===============================================================================================================
// July 09 Creation                                                                         L. Marini
//===============================================================================================================

#ifndef CATDeclarativeApplication_H
#define CATDeclarativeApplication_H 

enum CATDeclarativeApplication {
  CATDeclarativeApplication_NotDefined = -1, // Only CGM Use
  CATDeclarativeApplication_CATIALiveShape = 0,
  CATDeclarativeApplication_CATIABendPartDesign,
  CATDeclarativeApplication_CATIALiveBuildings,
  CATDeclarativeApplication_CATIADirectEdit,
  CATDeclarativeApplication_SolidWorksDirectEdit,
  CATDeclarativeApplication_CGMComponentDirectEdit, // same as CGMComponent, just a different name
  CATDeclarativeApplication_CGMComponent = CATDeclarativeApplication_CGMComponentDirectEdit, // same as CGMComponentDirectEdit, just a different name
  CATDeclarativeApplication_CATIADefeaturing,
  CATDeclarativeApplication_CDMInfra,
  CATDeclarativeApplication_SolidWorksImport,
  CATDeclarativeApplication_CATIACartonDesign,
  CATDeclarativeApplication_Exalead3DSearch,
  CATDeclarativeApplication_CGMInternalUse,
  CATDeclarativeApplication_UserDefinedMachiningFeature,
  CATDeclarativeApplication_CATIAMeanDimension, // Y2019 LAP : For this application the moves could be less than the resolution.
  CATDeclarativeApplication_SIMULIAMeshing,
  CATDeclarativeApplication_DesignForManufacturing, // DFM
  CATDeclarativeApplication_DieFaceDesign // Fillet radius reduction
};


#endif
