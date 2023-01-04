/* -*-c++-*- */

/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */
#ifndef CATGeoClnCheckParameter_H
#define CATGeoClnCheckParameter_H

//=============================================================================
// DESCRIPTION : used by CGMCleaner rules, in methods
//               CATCX_CHECKUP::CGMCleanerCheck(...) and
//               CATCX_CHECKUP::CGMCleanerSpecificCheck(...)
//=============================================================================
// Oct. 03  Creation                                                      HCN
// Avr. 04  La struct devient une classe                                  FDN
//=============================================================================

#include "ExportedByGeometricObjects.h"

#include "CATGeoClnIDs.h"

#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"
class CATLISTP(CATICGMUnknown);

//-----------------------------------------------------------------------------
// CATGeoClnCheckParameter and CATLISTP(CATGeoClnCheckParameter)
//-----------------------------------------------------------------------------
class ExportedByGeometricObjects CATGeoClnCheckParameter
{
public :
  CATGeoClnCheckParameter();

  CATGeoClnIDs::RuleID _pRuleID;  // The CATGeoClnIDs::RuleID of the target check rule
  size_t               _DataSize; // Must be initialised to the size of the data pointed by _pData
  void*                _pData;    // Pointer to the data you want to send to you check rule
  int                  _Severity; // Input User defined severity - optional (default=-1)
  int                  _Return;   // Output Return code - optional (default = OK = 0)
  CATLISTP(CATICGMUnknown) * _ListObjects; // Output : list of the KO objects, filled only if defined by user
};

#include "CATCGMLISTPP_Declare.h"

CATCGMLISTPP_DECLARE(CATGeoClnCheckParameter);

#endif
