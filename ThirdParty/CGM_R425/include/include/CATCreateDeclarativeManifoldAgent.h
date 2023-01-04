#ifndef CATCreateDeclarativeManifoldAgent_H
#define CATCreateDeclarativeManifoldAgent_H

#include "PersistentCell.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATCell.h"
#include "CATBoolean.h"

class CATDeclarativeManifoldAgent;
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATBody;
class CATChamferTool;
class CATIPGMChamferTool;
class CATIPGMTrimByThick;
class CATRecognizerContext;

/**
 * Creates a Fillet Recognizer Agent.
 */
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateFilletRecognizer();

ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateFilletAdvancedRecognizer();
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateFilletAdvancedRecognizer(double iMaxRadius);
// IZE wk. 27 2010 Fillet recognition taking tolerances into account
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateFilletAdvancedRecognizer(CATRecognizerContext &iRecognizerContext);

/**
 * Creates a Canonic Recognizer Agent.
 */
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateCanonicRecognizer();

ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateCanonicAdvancedRecognizer();

/**
 * Creates a Subdivision Recognizer Agent.
 */
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateSubdivisionRecognizer();

/**
* Create Chamfer Creator Agent
*/
ExportedByPersistentCell CATDeclarativeManifoldAgent* CATCreateChamferManifoldCreator(CATIPGMChamferTool *iTool);

/**
* Create Chamfer Recognizer Agent
*/ 
ExportedByPersistentCell CATDeclarativeManifoldAgent* CATCreateDrivenChamferRecognizer(const CATChamferTool *iTool
                                                                                     , CATLISTP(CATFace)& iRefSupportFaces
                                                                                     , CATLISTP(CATFace)& iOtherSupportFaces
                                                                                     , CATLISTP(CATCell)& iCandidateChamferCells);

/** @nocgmitf */
ExportedByPersistentCell CATDeclarativeManifoldAgent* CATCreateDrivenChamferRecognizer(CATIPGMChamferTool *iTool
                                                                                     , CATLISTP(CATFace)& iRefSupportFaces
                                                                                     , CATLISTP(CATFace)& iOtherSupportFaces
                                                                                     , CATLISTP(CATCell)& iCandidateChamferCells);
/**
* Create Chamfer Recognizer Agent
*/ 
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateChamferRecognizer();

/**
* Create Chamfer Recognizer Agent
*/ 
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateChamferAdvancedRecognizer();
// IZE wk. 51 2014 Chamfer recognition taking tolerances into account
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateChamferAdvancedRecognizer(CATRecognizerContext &iRecognizerContext);

/**
* Create Button Recognizer Agent
*/ 
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateButtonManifoldGlobalRecognizer();

/**
* ST5 Wk18-2012: Create Extrusion Recognizer Agent --> Create Pad/Pocket Recognizer Agent
*/ 
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateExtrusionManifoldCreatorBase(); //Temporary
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreatePadPocketManifoldCreator();
// IZE, Create the missing extrusion features
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateHoleManifoldCreator();
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateSlotManifoldCreator();
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateNotchManifoldCreator();

/**
 * Creates a Draft Recognizer Agent.
 */
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateDraftRecognizer();
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateDraftAdvancedRecognizer();
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateDraftAdvancedRecognizer(CATRecognizerContext &iRecognizerContext);

/**
 * Creates a Logo Recognizer Agent.
 */
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateLogoRecognizer();

/**
* VB7 W10 2018
* Create AdvancedStamp Recognizer Agent
*/ 
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateDRepAdvancedStampLocalRecognition();
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateDRepAdvancedStampGlobalRecognition();
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateDRepAdvancedStampCreator();

/**
* QF2 W15 2019
*/ 
ExportedByPersistentCell CATDeclarativeManifoldAgent *CATCreateDRepNameCarrierAgent(CATBoolean iRematch=FALSE);


#endif
