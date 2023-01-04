/* -*-C++-*- */

#ifndef CATWeekVersioning_H
#define CATWeekVersioning_H
/*  
=============================================================================

RESPONSABLE  : L Marini

DESCRIPTION  : Temporary versioning tools class
                 - It's usefull to find which code break an ODT.
                              
=============================================================================
*/

/* 
-------------------------------------
Sample of code
-------------------------------------

#include "CATWeekVersioning.h" // For temporary versioning

if (GetWeekVersioning("LAP",22,"NoDatum")) // Code to be cleaned W24

if (GetWeekVersioning("LAP",25,"Project",FALSE)) // FALSE = Desactivated code

-------------------------------------
To find the code that break an ODT
-------------------------------------

1. weekvers ODTName   All will be be done automatically

or

1. set CATWeekVersioning_Check=1
2. qodt -el ODTName
3. weekvers ODTName
or
weekvers address_file.output
4. Test the desactivation of the last variables.

-------------------------------------
To desactivate a versioned code
-------------------------------------

set CATWeekVersioning_Check=1
set CATWeekVersioning_LAP_W22_NoDatum=0

-------------------------------------
To desactivate all versioned code from one week
-------------------------------------

set CATWeekVersioning_Check=1
set CATWeekVersioning_Week=22

-------------------------------------
To activate your desactivated code
-------------------------------------

set CATWeekVersioning_Check=1
set CATWeekVersioning_LAP_W25_Project=1

*/



// --------------------------------------------------------
/* Exemple of code:

#include "CATWeekVersioning.h"  // For temporary versioning

// For temporary versioning
// -------------------------
CATBoolean noDatumActivated  = GetWeekVersioning("LAP",22,"NoDatum");          


// For temporary versioning
//  To activate the code
//  set CATWeekVersioning_Check=1
//  set CATWeekVersioning_LAP_W22_Project1 = 1
// -------------------------------------------
CATBoolean project1Activated = GetWeekVersioning("LAP",22,"Project1",FALSE);

*/
// --------------------------------------------------------

#ifndef NULL
#define NULL 0
#endif

#include "CATMathematics.h"
#include "CATSysBoolean.h"


//-----------------------------------------------------------------------------
// GetWeekVersioning
//
//  The week number of activation is very important.
//  When an ODT is KO, check only the from the week.
//  When you have to clean the code from your temporary versioning, find in files : Versioning("LAP",
//
//-----------------------------------------------------------------------------
ExportedByCATMathematics CATBoolean GetWeekVersioning(const char * iTrigram,
                                                      int          iWeekOfActivation,
                                                      const char * iProjectName=NULL,
                                                      CATBoolean   iActivated=TRUE);

#endif
