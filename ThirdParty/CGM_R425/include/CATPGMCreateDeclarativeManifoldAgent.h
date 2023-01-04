#ifndef CATPGMCreateDeclarativeManifoldAgent_h_
#define CATPGMCreateDeclarativeManifoldAgent_h_

// COPYRIGHT DASSAULT SYSTEMES 2008

#include "CATGMModelInterfaces.h"
#include "CATCollec.h"

class CATBody;
class CATDeclarativeManifoldAgent;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATIPGMChamferTool;
class CATIPGMTrimByThick;
class CATLISTP(CATCellManifold);
class CATLISTP(CATCell);
class CATRecognizerContext;
class CATLISTP(CATFace);

/**
 * Creates a Fillet Recognizer Agent.
 */
ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateFilletRecognizer();

ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateFilletAdvancedRecognizer();

ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateFilletAdvancedRecognizer(double iMaxRadius);

// IZE wk. 27 2010 Fillet recognition taking tolerances into account
ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateFilletAdvancedRecognizer(
  CATRecognizerContext &iRecognizerContext);

/**
 * Creates a Canonic Recognizer Agent.
 */
ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateCanonicRecognizer();

ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateCanonicAdvancedRecognizer();

/**
 * Creates a Subdivision Recognizer Agent.
 */
ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateSubdivisionRecognizer();

/**
* Create Chamfer Creator Agent
*/
ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateChamferManifoldCreator(
  CATIPGMChamferTool *iTool);

/**
* Create Chamfer Recognizer Agent
*/
ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateDrivenChamferRecognizer(
  CATIPGMChamferTool *iTool,
  CATLISTP(CATFace)& iRefSupportFaces,
  CATLISTP(CATFace)& iOtherSupportFaces,
  CATLISTP(CATCell)& iCandidateChamferCells);

/**
* Create Chamfer Recognizer Agent
*/
ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateChamferRecognizer();

/**
* Create Chamfer Recognizer Agent
*/
ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateChamferAdvancedRecognizer();

// IZE wk. 51 2014 Chamfer recognition taking tolerances into account
ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateChamferAdvancedRecognizer(
  CATRecognizerContext &iRecognizerContext);

/**
* Create Button Recognizer Agent
*/
ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateButtonManifoldGlobalRecognizer();

/**
* ST5 Wk18-2012: Create Extrusion Recognizer Agent --> Create Pad/Pocket Recognizer Agent
*/
// IZE remark : ExtrusionManifoldCreator shouldn't be exposed
ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateExtrusionManifoldCreatorBase();

ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreatePadPocketManifoldCreator();

// IZE, Create the missing extrusion features
ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateHoleManifoldCreator();

ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateSlotManifoldCreator();

ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateNotchManifoldCreator();

/**
 * Creates a Draft Recognizer Agent.
 */
ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateDraftRecognizer();

ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateDraftAdvancedRecognizer();

ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateDraftAdvancedRecognizer(
  CATRecognizerContext &iRecognizerContext);


/**
 * Creates a Logo Recognizer Agent.
 */
ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateLogoRecognizer();

/**
* VB7 W10 2018
* Create AdvancedStamp Recognizer Agent
*/
ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateDRepAdvancedStampLocalRecognition();

ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateDRepAdvancedStampGlobalRecognition();

ExportedByCATGMModelInterfaces CATDeclarativeManifoldAgent *CATPGMCreateDRepAdvancedStampCreator();

#endif /* CATPGMCreateDeclarativeManifoldAgent_h_ */
