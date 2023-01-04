/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */

//=============================================================================
//
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "FEG_1", "FEG_2" Fat Edges
//
// Aug. 03	Creation                                                      HCN
// Nov. 03  Methode definie par CATCGMCLEANER_RULE_CREATE_XXX             HCN
//=============================================================================

#ifndef CATGeoClnFatEdge_h
#define CATGeoClnFatEdge_h

#include "CATGeoClnBodyDatumiser.h"

//*********************************************************************************
// On ne peut pas utiliser les macros definies dans CATGeoClean.h car on
// veut heriter de CATGeoClnBodyDatumiser
//*********************************************************************************

CATCGMCLEANER_RULE_CREATE_DECLARE( CATGeoClnFatEdge, ExportedByCATCGMGeoClnTopo )

class ExportedByCATCGMGeoClnTopo CATGeoClnFatEdge : public CATGeoClnBodyDatumiser
{
public :
  CATGeoClnFatEdge(CATSoftwareConfiguration* ipConfig,
                   CATICGMUnknown*           ipICGMFederator,
                   CATCGMRuleDef*            ipCGMRuleDef,
                   CATBoolean                iVerbose);
  
  ~CATGeoClnFatEdge();

  CATCGMNewClassArrayDeclare;
  
  static CATGeoCln* CreateRule(CATSoftwareConfiguration* ipConfig,
                               CATICGMUnknown*           ipICGMFederator,
                               CATCGMRuleDef*            ipCGMRuleDef,
                               CATBoolean                iVerbose);
  
  virtual void SetBodyDatumiserTargetType(CATBodyDatumiser* ipBodyDatumiser);
};


#endif

