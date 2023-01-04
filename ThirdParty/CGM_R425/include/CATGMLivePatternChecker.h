#ifndef CATGMLivePatternChecker_H
#define CATGMLivePatternChecker_H

//-------------------------------------------------------------------------------------------------------
// CATGMLivePatternChecker
//-------------------------------------------------------------------------------------------------------
// Check the DRep Pattern rules.
// JJ3 : 19-03-2012 : Creation
//-------------------------------------------------------------------------------------------------------
// Check si le Pattern suit bien les regles de construction.
  // Regle 0           : Verification de la coherence du model.
  // Regle 1           : Pas de Pattern qui n'a qu'une seule instance.
  // Regle 2 (bridage) : Pas de Pattern en collision au last run.
  // Regle 3 (bridage) : Domain Rules
  // 3-0 : No surfacic pattern.
  // 3-1 : No multi domain pattern.
  //  -> R2013x : in volumic case we allow multi-domaine pattern. It is still forbidden for the surfacic case. 
  // Regle 4           : Differents cas de specialisation
  // 4-0                           : Pas de specialisation en position
  // 4-1                           : Pas d'ajout de detail => Pas de creation de face interne a une instance. 
  // 4-2 (pour operateur non live) : Pas de modification de la geometrie d'une instance => Comparaison des geometreies avant/apres grace au journal.
  // 4-3 (pour operateur non live) : Pas de deletion d'un detail autrement que par collision avec le context environnant => ?? on ne peux pas distinguer => par defaut on refuse.
  // Regle 5          : L'unitary transformation 
  // 5-0                 : L'unitary transformation doit etre une Translation ou une Rotation.
  // 5-1                 : Si rotation : l'angle ne doit pas etre superieur a 2Pi/3.
  // Regle 6          : La reference doit etre connexe.
  // Rule 7           : Fillets must have the same convexity in all instances.
  // Rule 8           : Circular pattern should not go beyond 360 degrees
  // Rule 9           : pattern reference has same matter orientation than instances.
  // Rule 10          : all instances should be protrusion or depression - VB7 - July 2014 //Not activated W14 2016
  // Rule 11          : pattern halo has to be in its instance boundingBox


#include "PersistentCell.h"
#include "CATCGMDiagnosis.h"
//#include "CATCellManifoldGroup.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATListPOfCATCGMDiagnoses.h"

class CATLiveBody;
class CATCellManifoldPatternNavigator;
class CATGMLiveShapeExtVectorialOperator;
class CATSoftwareConfiguration;
class CATPersistentCellInfra;
class CATCellManifoldGroup;
class CATPersistentCell;
class CATExtTopOperator;
class CATCGMJournalList;

class ExportedByPersistentCell CATGMLivePatternChecker
{
public:

  
  //-------------------------------------------------------------------------------------------------------
  // Constructor / Destructor
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;      // Pool allocation
  CATGMLivePatternChecker(CATLiveBody * iLiveBody, CATSoftwareConfiguration * iConfig=NULL);
  ~CATGMLivePatternChecker();

  //-------------------------------------------------------------------------------------------------------
  // Set
  //-------------------------------------------------------------------------------------------------------
  void SetIsLastRun(CATBoolean iIsLastRun = FALSE);
  void SetIsCalledByLiveOperator(CATBoolean iIsCalledByLiveOperator = FALSE);
  void SetWarningReport(CATPersistentCellInfra * iInfra, CATExtTopOperator * iOp);
  void SetNoThrow(CATBoolean iNoThrow=TRUE);

  //-------------------------------------------------------------------------------------------------------
  // Run
  //-------------------------------------------------------------------------------------------------------
  int Run();

  //-------------------------------------------------------------------------------------------------------
  // Get
  //-------------------------------------------------------------------------------------------------------
private : 
  CATLISTP(CATCGMDiagnosis) GetWarningList();

private : 

  void Init();
  int CheckPattern(CATCellManifoldPatternNavigator * ipPatternNavigator);  
  void AddPatternToDelete(CATCellManifoldGroup * iPatternToDelete);
  void ClearWarningList();
  void CreateWarningOrError(int iErrorNumber, const char * iMsgId, CATCellManifoldPatternNavigator * iPatternNavigator, int & oErrorNumber);
  CATBoolean R124Level();

  // Deprecated 
  void AddWarning(CATCGMDiagnosis * iWarning, CATBoolean iLocationIsSet = FALSE, CATCellManifoldPatternNavigator * ipPatternNavigator = NULL);

  HRESULT RunDeletePatternGroup(CATBody * ioInputBody, CATCellManifoldGroup * iGroupToDelete, CATCGMJournalList * oJournal);

  CATBoolean IsLastRun();
  CATBoolean IsCalledByLiveOperator();

  int CheckRule_1(CATCellManifoldPatternNavigator * ipPatternNavigator);
  int CheckRule_2(CATCellManifoldPatternNavigator * ipPatternNavigator);
  int CheckRule_3(CATCellManifoldPatternNavigator * ipPatternNavigator);
  int CheckRule_4(CATCellManifoldPatternNavigator * ipPatternNavigator);
  int CheckRule_5(CATCellManifoldPatternNavigator * ipPatternNavigator);
  int CheckRule_6(CATCellManifoldPatternNavigator * ipPatternNavigator);
  int CheckRule_7(CATCellManifoldPatternNavigator * ipPatternNavigator);
  int CheckRule_8(CATCellManifoldPatternNavigator * ipPatternNavigator);
  int CheckRule_9(CATCellManifoldPatternNavigator * ipPatternNavigator);
  int CheckRule_10(CATCellManifoldPatternNavigator * ipPatternNavigator);
  int CheckRule_11(CATCellManifoldPatternNavigator * ipPatternNavigator);

  CATLiveBody          * _LiveBody;
  CATBoolean             _IsLastRun;
  CATBoolean             _IsCalledByLiveOperator;
  CATBoolean             _NoThrow;

  CATLISTP(CATCGMDiagnosis) _WarningList;
  CATLISTP(CATCellManifoldGroup) _PatternToDeleteList;
  CATPersistentCellInfra * _PCInfra;
  CATExtTopOperator * _Op;
  CATSoftwareConfiguration * _Config;

};

#endif

