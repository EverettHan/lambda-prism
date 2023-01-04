#ifndef CATFilletPerfos_h
#define CATFilletPerfos_h

#include "Connect.h"
/*
#define CWM_PERFOS

#include "CATListOfCATSurfaces.h"

class ExportedByConnect CATFilletPerfos
{
public:
  CATFilletPerfos();
  ~CATFilletPerfos();

  void CleanData();

  void DumpForMultiRibbon();
  void DumpForInit();
  void DumpForRelimitation();
  void DumpForNuplet();
  void DumpForRibs();

  void DumpForConnect();
  void DumpForConnectPiece();

  void DumpForUnTwist();

public:
  int _NumberOfMultiRibbonFilletsRun;
  int _NumberOfMultiRibbonFilletsRunTwice;

  int _NumberOfConnectSurSur;
  int _NumberOfConnectWithSameCoupleOfSurfaces;
  CATLISTP(CATSurface) _ConnectSurfaces[2];

  int _NumberOfConnectPieceSurSur;
  int _NumberOfConstantFilletPieceSurSur;
  int _NumberOfConstantFilletSurfaces;
  int _NumberOfConstantFilletTwistDetections;
  
  int _NumberOfConstantFilletPieceWithSameCoupleOfSurfaces;
  CATLISTP(CATSurface) _ConstantFilletPieceSurfaces[2];

  int _NumberOfFilletEdgeInits;
  int _NumberOfFilletEdgeAdjacentInits;
  int _NumberOfFilletEdgeAdjacentInitsOnMaxLimits;
  int _NumberOfFilletEdgeNonAdjacentInits;
  int _NumberOfFilletEdgeNonAdjacentInitsOnMaxLimits;

  int _NumberOfFilletFaceFaceInits;
  int _NumberOfFilletFaceFaceInitsOnMaxLimits;

  int _NumberOfRlmRibbonsRun;
  int _NumberOfRewinds;

  int _NumberOfNupletsToExport;
  int _NumberOfCreatedBlendNuplets;

  int _NumberOfRibs;
  int _NumberOfRibInits;
  int _NumberOfRibbonFaces;
  int _NumberOfBlendTopOp;

  int _NumberOfEdgeRibbons;
  int _NumberOfSmallEdgeRibbons;

  int _NumberOfCheckFilletSkinValidity;
  int _NumberOfOldCheckShellValidity;
  int _NumberOfUnTwistByFill;
};

ExportedByConnect CATFilletPerfos & FilletPerfos();  
*/ 

ExportedByConnect int GetMultiProcEnv();  

//#define SOU_FILLET_MULTIPROC_TRACES_4
//#define SOU_FILLET_PERFOS
//#define SOU_FILLET_MULTIPROC_NCGM_TRACES_4
//#define SOU_FILLET_MULTIPROC_TRACES_1 

#endif

