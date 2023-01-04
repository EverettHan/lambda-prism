#ifndef CATGMLiveOffsetChecker_H
#define CATGMLiveOffsetChecker_H

//-------------------------------------------------------------------------------------------------------
// CATGMLiveOffsetChecker
//-------------------------------------------------------------------------------------------------------
// Check the DRep Offset rules.
// VB7 : 16-10-2013 : Creation
//-------------------------------------------------------------------------------------------------------

#include "PersistentCell.h"
#include "CATCGMDiagnosis.h"
// #include "CATCellManifoldGroup.h"
#include "ListPOfCATCellManifoldGroup.h"

class CATLiveBody;
class CATCellManifoldOffsetNavigator;
class CATGMLiveShapeExtVectorialOperator;
class CATPersistentCellInfra;
class CATCellManifoldGroup;
class CATPersistentCell;

class ExportedByPersistentCell CATGMLiveOffsetChecker
{
public:

  
  //-------------------------------------------------------------------------------------------------------
  // Constructor / Destructor
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;      // Pool allocation
  CATGMLiveOffsetChecker(CATLiveBody * iLiveBody, CATPersistentCellInfra * iPersistentCellInfra);
  ~CATGMLiveOffsetChecker();

  //-------------------------------------------------------------------------------------------------------
  // Set
  //-------------------------------------------------------------------------------------------------------
  void SetIsLastRun(CATBoolean iIsLastRun = FALSE);
  void SetIsCalledByLiveOperator(CATBoolean iIsCalledByLiveOperator = FALSE);

  //-------------------------------------------------------------------------------------------------------
  // Run
  //-------------------------------------------------------------------------------------------------------
  int Run();

  //-------------------------------------------------------------------------------------------------------
  // Get
  //-------------------------------------------------------------------------------------------------------
private : 


private : 

  void Init();
  int CheckOffset(CATCellManifoldOffsetNavigator * ipOffsetNavigator);
  void AddOffsetToDelete(CATCellManifoldGroup * iOffsetToDelete);
  CATBoolean IsLastRun();
  CATBoolean IsCalledByLiveOperator();
  //Regle 1           : Pas d'Offset qui n'a qu'une seule instance.
  int CheckRule_1(CATCellManifoldOffsetNavigator * ipOffsetNavigator);
  //Regle 2           : Deux instances ne peuvent avoir la même valeur d'offset
  int CheckRule_2(CATCellManifoldOffsetNavigator * ipOffsetNavigator);
  //Regle 3           : Limitation 2015x - G2/Chordal/Variable Fillet are forbidden
  int CheckRule_3(CATCellManifoldOffsetNavigator * ipOffsetNavigator);
  CATLiveBody          * _LiveBody;
  CATBoolean             _IsLastRun;
  CATBoolean             _IsCalledByLiveOperator;

  CATPersistentCellInfra * _PersistentCellInfra;
  CATLISTP(CATCellManifoldGroup) _OffsetToDeleteList;

};

#endif

