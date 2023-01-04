/* -*-c++-*- */
#ifndef CATGMLiveShapeManifoldInfra_h
#define CATGMLiveShapeManifoldInfra_h
// COPYRIGHT DASSAULT SYSTEMES  2008
//
// Fichier temporaire pour la migration ManifoldInfra = 2
//
// Resp: LAP

#include "CATGMModelInterfaces.h" 

ExportedByCATGMModelInterfaces int GetGMCellManifoldPattern();

ExportedByCATGMModelInterfaces int GetGMCellManifoldOffset();

ExportedByCATGMModelInterfaces int GetGMCellManifoldGroupJournal();

/**
 *	GetAllDimensionConstraint values :
 *			=> 0 : Volume (face, edge, vertex)
 *			=> 1 : Volume + Skin only (face, edge, vertex)
 *			=> 2 : Volume + Skin + Wire line only (edge line + vertex between 2 lines or extremity ) + alone Point
 *			=> 3 : Volume + Skin + Wire + alone Point
 * 
 *	By default, GetAllDimensionConstraint = 1.
 */
ExportedByCATGMModelInterfaces int GetAllDimensionConstraint();       // Only used by NaturalShape.                     Resp : LAP

ExportedByCATGMModelInterfaces int GetRemoveUserConstraintSpec();     // Only used by NaturalShape.                     Resp : LAP

ExportedByCATGMModelInterfaces int GetGMManifoldInfra();              // Only used by CAT3DXVM.tst.                     Resp : LAP

ExportedByCATGMModelInterfaces int GetCDMSessionInfra();              // Only used by NaturalShape

ExportedByCATGMModelInterfaces int GetLiveDuplicateWithPaste();       // Only used by CDMModel

ExportedByCATGMModelInterfaces int GetUseDeclarativeAgentCreator();   // Only used by CATAdvancedBRepToDRepOperator

ExportedByCATGMModelInterfaces int GetImprovedMappingCMGroups();

ExportedByCATGMModelInterfaces int GetSplitterEnhancementForCarton(); // Only for Carton lateral faces.                Resp : VB7

ExportedByCATGMModelInterfaces int GetLiveShapeDisableDrawClosure();  // Only used by NaturalShape

ExportedByCATGMModelInterfaces int GetChangeIndustryStatus();         // Only used by NaturalShape+CGM                 Resp : QF2/LAP

ExportedByCATGMModelInterfaces int GetEmbeddedSkinStatus();           // Only used by NaturalShape+CGM                 Resp : LAP

ExportedByCATGMModelInterfaces int GetGMDeclarativeManifoldButton();  // Only used by NaturalShape+CGM                 Resp : VB7

ExportedByCATGMModelInterfaces int GetSplitterRemoveSPDSHM();         // Only used by SPD+SHM+CGM                      Resp : VB7

ExportedByCATGMModelInterfaces int GetAdvancedStampLevel();           // Only used by NaturalShape+CDM+CGM             Resp : VB7/LAP

ExportedByCATGMModelInterfaces int GetCLSDRepDraft();                 // Only used by NaturalShape+CGM                 Resp : QF2/LAP

ExportedByCATGMModelInterfaces int GetSPDConvergenceCMCreation();     // Only used by SPD+SHM+CGM                      Resp : VB7

ExportedByCATGMModelInterfaces int GetNTS();                          // Only used for proto NTS                       Resp : LAP

ExportedByCATGMModelInterfaces int GetCLSAllUserSelection();          // Only used for Debug in NS                     Resp : QF2/LAP

ExportedByCATGMModelInterfaces int GetCstOnDRepCharactElement();      // Only used for POC Project - constraint on DRep     : QF2/LAP

ExportedByCATGMModelInterfaces int GetAutoPartitioningCmd();          // Only used by SIMULIA                          Resp : VB7

ExportedByCATGMModelInterfaces int GetExtrudeDraftNewSpec();          // Only used by NS + CGM                         Resp : QF2

ExportedByCATGMModelInterfaces int GetNSMoveEdgeOnSupport();          // Only used by NS, CGM, CDS                     Resp : QF2


#endif

