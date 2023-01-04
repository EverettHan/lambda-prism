//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2016
//=============================================================================
//
// CATPSDirectVersioning:
//    Header file for the CATPSDirectVersioning class
//
//=============================================================================
//
//=============================================================================
// 19/10/16 R1Y Creation
// 13/07/17 Q48 Move to GeometricOperators and re-write as base class
//                --> available for XGM and IntersectionMultiSurface
// 26/09/18 Q48 Re-write to use arrays (automatic reset of class data in replays)
//=============================================================================

#ifndef CATPSDirectVersioning_H
#define CATPSDirectVersioning_H

#include "CATCGMVirtual.h"

#include "CATMathInline.h"

#include "CATBoolean.h"
#include "CATDataType.h"  // for CATLONG32
#include "CATUnicodeString.h"

#include "CATGeoOpDebug.h"

//=============================================================================
// Q48 11/03/19: Use C++11 array initialiser syntax to remove static arrays
//=============================================================================

// - the aim is to remove static const arrays from the versioning
//   classes because these arrays are initialized during the load
//   of the dll (==> unnecessary work and in fact triggered some
//   crashes during unrelated multi-threading ODTs - see IR-668550)
// 
// - the new way to initialize the arrays relies on some "new" C++
//   standard which may not be supported on all platforms

#include "CATGeoOpCpp11.h"

// If we cannot use C++11, we must use the static arrays to handle the list
// of versioning flags

#ifndef GEO_CPP11
#define Q48_StaticArraysForVersioning
#endif
//=============================================================================

//=============================================================================
// 04/03/19 Q48: backup #define in case of build errors (force the old usage of
//               static arrays. To be removed after a few weeks of testing
//=============================================================================
//#define Q48_StaticArraysForVersioning
//=============================================================================

// Usage Notes
// ===========

// Adding a New XGM Versioning Variable
// ------------------------------------
// 1. Create a new entry in the "Versioning Variables" section of the XGM / MSINT files
// 2. Each entry consists of the name of the versioning variable, the activation week, and optionally a comment
// 3. There must be a back-slash character ("\") at the end of all lines except the last
// 4. In the source code, XGM versioning can be accessed using the IsXGMFlagActive macro
//      if (IsXGMFlagActive(NewVersioningVariable))
//      {
//        // New code.
//      }
//      else
//      {
//        // Previous code.
//      }
// 5. Add a new activation week to the ACTIVATION_WEEKS list

// Adding a New Activation Week
// ----------------------------
// 1. If the current activation week is not present in the "Activation Weeks" section, create a new entry immediately before the last line ("CREATE_WEEK(WeekEnd)")

// Setting the Current Activation Week on the Command Line
// -------------------------------------------------------
// 1. The current activation week can be set on the command line using the environment variable "XGM_CurrentWeek" (for example, "set XGM_CurrentWeek=Year2016_Week43")
// 2. If the current activation week is set to "NotActivated" then all of the versioning variables become inactive
// 3. As integer comparisons are performed, the activation weeks must begin at zero, and must be in ascending order; therefore, an enum is created for these values

// Activating or Deactivating a Versioning Variable on the Command Line
// --------------------------------------------------------------------
// 1. To activate a versioning variable:
//    a. Obtain the name of the variable (i.e., the first data item for the variable in the section entitled "Versioning Variables" below)
//    b. On the command line, enter (for setting the first variable in the list), for example:
//           set XGM_IR371977_Convergence=1
//    c. Any non-zero integer can be used instead of the "1" in the example.
//    d. Note the additional prefix "XGM_" or "MSINT_"
// 2. To deactivate a versioning variable:
//    a. Obtain the name of the variable (i.e., the first data item for the variable in the section entitled "Versioning Variables" below).
//    b. On the command line, enter (for setting the first variable in the list), for example:
//           set XGM_IR371977_Convergence_OFF=1
//    c. Any non-zero integer can be used instead of the "1" in the example
//    d. Note the additional characters in "XGM_" (or "MSINT") and "_OFF"
// 3. Additional variables can be activated and deactivated in a similar manner
// 4. If a variable is both activated and deactivated on the command line, a warning is issued, and the variable is taken to be inactive

//=============================================================================

// Macros for creating information for the activation weeks
#define PSDIRECT_CREATE_WEEK_BEGIN(Name, Value) Name = Value
#define PSDIRECT_CREATE_WEEK(Name) Name

// Macro for creating data for the versioning variables
#define PSDIRECT_CREATE_FLAG_DATA(Name, Week) Name

//=============================================================================

// ----------------------------------------------------------------------------

// class for storing data in a versioning flag
class PSDirect_FlagData
{
public:
  // Enumeration for the current state of a versioning flag
  enum PSDirect_FlagState
  {
    Uninitialised = 0,
    Active,
    Inactive
  };

  // Constructor
  INLINE PSDirect_FlagData(const char      * const iName,
                           const CATLONG32         iWeek);

  // Destructor
  INLINE ~PSDirect_FlagData();

  GEOPDEBUG_CMD(CATUnicodeString Debug_StringFromState(const PSDirect_FlagState & iState) const);
  GEOPDEBUG_CMD(CATUnicodeString Debug_StringFromState() const);

private:
  // Member data
  const   CATUnicodeString   _Name;   // the name of the flag (which is used to set the value on the command line)
  const   CATLONG32          _Week;   // the activation week for the flag (which is used as an index for the enumeration for the activation weeks)
  mutable PSDirect_FlagState _State;  // the state for the flag ("mutable", so it can be modified in GetFlagState)

  friend class CATPSDirectVersioning; // to allow the state to be modified in GetFlagState
};

// Constructor
INLINE PSDirect_FlagData::PSDirect_FlagData(const char      * const iName,
                                            const CATLONG32         iWeek) :
_Name(iName), _Week(iWeek), _State(Uninitialised)
{}

// Destructor
INLINE PSDirect_FlagData::~PSDirect_FlagData()
{}

//=============================================================================

// Class for XGM versioning
class ExportedByY3DYNOPE CATPSDirectVersioning : public CATCGMVirtual
{
public:

  // Function to determine whether a versioning variable is active
  CATBoolean IsFlagActive(const int iFlagIndex) const;

protected:

  // Protected Member Functions
  // ------------------------

  CATPSDirectVersioning(const CATUnicodeString  & iPrefix,
                        const PSDirect_FlagData * ipFlags,
                        const int                 iNumFlags);

  virtual ~CATPSDirectVersioning();

  // Initialise the versioning object
  // --------------------------------

  void Reset() const;

  virtual void ForceCurrentWeek(const int iNewWeek) const = 0;

  // Update the current activation week if it has been set on the command line
  virtual void UpdateCurrentWeek() const = 0;
  
  // Access to the activation week strings
  virtual const CATUnicodeString & GetActivationWeekName(const int) const = 0;

  // Implementation
  void DoUpdateCurrentWeek(const int iWeekEnd) const;
  void DoForceCurrentWeek(const int iNewWeek) const;

  CATBoolean DoCheckRollBack(const CATUnicodeString & iPrefix) const;

  // Determine whether a versioning variable is active or inactive, and store this state
  CATBoolean GetFlagState(const PSDirect_FlagData & ioFlagData) const;

  // Protected Member Data
  // ---------------------

  const   CATUnicodeString _PrefixStr;
  mutable int              _CurrentWeek; // make this private ?? (add protected get / set)

  // Private Member Data
  // -------------------

  const PSDirect_FlagData* _pFlags;
  const int                _nFlags;

protected:
  static const int _NotActivated = 0; // start value of the enum (common to all derived classes)
};
//=============================================================================
#endif
