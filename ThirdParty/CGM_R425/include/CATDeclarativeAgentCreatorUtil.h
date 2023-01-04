//===============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014
//===============================================================================================================
//
// CATDeclarativeAgentCreatorUtil :
// Class containing static methods which generate Declarative Agents according to the given Application.
// It should be used by ManifoldCreator, BRepToDRep operator or CATAdvancedDeclarativeAgentCreator [Declarative].
// The Declarative recognition Agents have to be created by CATDeclarativeAgentCreatorUtil only.
// 
// Declarative Agents that can be created :
// --------------------------------------
// - Fillet  Recog
// - Canonic Recog
// - Chamfer Recog
// - Hole    Recog

//===============================================================================================================
// Aug. 06 Creation                                                                         Q. FREGER
//===============================================================================================================


#ifndef CATDeclarativeAgentCreatorUtil_H
#define CATDeclarativeAgentCreatorUtil_H


#include "PersistentCell.h"
#include "ListPOfCATDeclarativeManifoldAgent.h"
#include "CATDeclarativeApplication.h"
#include "CATDeclarativeOriginModeler.h"
#include "CATListOfInt.h"
#include "IUnknown.h" // For HRESULT

class CATSoftwareConfiguration;
class CATDeclarativeContext;
class CATDRepBehavior;

// @nocgmitf
class ExportedByPersistentCell CATDeclarativeAgentCreatorUtil
{

public :

  // Create Declarative Agents according to CATDeclarativeApplication.
  // Carefull, ioGeneratedAgents is not emptied. Generated Agents will be added to the list. 

  // Signature 1
  static HRESULT GenerateAgents(CATSoftwareConfiguration  * iConfig,
                                CATDeclarativeContext     * iContext,
                                CATDeclarativeApplication   iAppli, 
                                CATDeclarativeOriginModeler iModeler, 
                                ListPOfCATDeclarativeManifoldAgent & ioGeneratedAgents);

  // Signature 2
  static HRESULT GenerateAgents(CATSoftwareConfiguration  * iConfig,
                                CATDRepBehavior           * iDRepBehavior,
                                ListPOfCATDeclarativeManifoldAgent & ioGeneratedAgents);



  // ---------------------------------
  // ## Debug ##
  // ---------------------------------
  // For developpement interface only - Dedicated to CATGMLiveBRepToDRepPanel.h
  // First signature. Can be changed
  static HRESULT GenerateAgentRecognitionType(CATDeclarativeApplication iAppli, CATListOfInt &oIDAgentGenerated /*enum FeatureRecognitionType*/);  // see CATGMLiveBRepToDRepPanel.h (CAT3DTopo.tst)
 
private : 

  static HRESULT GenerateBaseAgents(CATSoftwareConfiguration  * iConfig, 
                                    const CATDeclarativeApplication iAppli, 
                                    ListPOfCATDeclarativeManifoldAgent *ioGeneratedAgents=NULL, 
                                    CATListOfInt *oIDAgentGenerated=NULL);


};





#endif 

