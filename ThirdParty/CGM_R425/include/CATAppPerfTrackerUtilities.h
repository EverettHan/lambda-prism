/* -*-C++-*- */

#ifndef CATAppPerfTracker_H
#define CATAppPerfTracker_H
/*  
=============================================================================

RESPONSABLE  : V Bouvier

DESCRIPTION  : Utilities of CATAppPerfTracker
               
=============================================================================
*/

#include "CATPersistentCell.h"

class CATIPGMTopOperator;
class CATPersistentExtTopOperator;

class ExportedByPersistentCell CATAppPerfTrackerUtilities
{
public:
  //@nocgmitf
  static void StartTopOperator(CATTopOperator * iOpe);
  //@nocgmitf
  static void EndTopOperator  (HRESULT iOpeResult);
  //@nocgmitf
  static void StartPersistentOperator(CATPersistentExtTopOperator * iOpe);
  //@nocgmitf
  static void EndPersistentOperator  (CATBoolean              iOpeResult);
  //@nocgmitf
  static void StartPersistentOperatorConstr(CATPersistentExtTopOperator * iOpe);
  //@nocgmitf
  static void EndPersistentOperatorDestr  (CATBoolean              iOpeResult);
  //@nocgmitf
  static void EndPersistentOperator  (int                     iRval);
  //@nocgmitf
  static void StartAgent(CATDeclarativeManifoldAgent * iAgent);
  //@nocgmitf
  static void EndAgent  (HRESULT iAgentResult);
  //@nocgmitf
  static void ForceNeutralLevel();
};

#endif
