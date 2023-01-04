/* -*-C++-*- */

#ifndef CATlsoBodyTrackerDebug_H
#define CATlsoBodyTrackerDebug_H

// @nocgmitf (this class doesn't need a CATIPGM interface)


/*  
=============================================================================

RESPONSABLE  : LAP

DESCRIPTION  : A utility class to help for track the bodies still in the factory after the destruction of operator.
               The constructor list the bodies in session.
               The destructor list the bodies created after constructor.

Debug is piloted by environment variables :
  set CATlsoBodyTracker=1 : Activate the trace.

CREATION     : 16 January 2017 by LAP

=============================================================================
*/

// ++++ Includes ++++
#include "PersistentCell.h"
#include "CATCGMVirtual.h"
#include "CATBoolean.h"
#include "ListPOfCATBody.h"

class CATGeoFactory;
class CATPersistentExtTopOperator;

// @nocgmitf (this class doesn't need a CATIPGM interface)
class ExportedByPersistentCell CATlsoBodyTrackerDebug : public CATCGMVirtual
{

public:

  //---------------------------------------------------------------------------
  // CONSTRUCTOR(S) / DESTRUCTORS
  //---------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;

  CATlsoBodyTrackerDebug(CATPersistentExtTopOperator * iPersistentExtTopOperator);
  ~CATlsoBodyTrackerDebug();




  //---------------------------------------------------------------------------
  // METHODS for activation
  //---------------------------------------------------------------------------
  static CATBoolean GetActivateTrace();
  static void       SetActivateTrace(CATBoolean iActivateTrace);
  
private:

  void CreatePreviousBodyList();  // Call in constructor
  void CreateNewBodyList();       // Call in destructor
  void CreateBodyInFactoryList(ListPOfCATBody & oBodyList);
  void DumpList(ListPOfCATBody & iBodyList, const char * iPrefixName);
  void DumpTitle(const char * iPrefixName);
 
  //---------------------------------------------------------------------------
  // MEMBER DATA
  //---------------------------------------------------------------------------
  ListPOfCATBody                _PreviousBodyList;
  CATGeoFactory               * _ImplicitFactory;
  CATPersistentExtTopOperator * _PersistentExtTopOperator;
};

#endif /* CATlsoBodyTrackerDebug_H */
