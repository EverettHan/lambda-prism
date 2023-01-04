/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2002
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "FVX_1" Fat Vertices
//
// Aug. 02	Creation sous le nom CATGeoClnFatVertex, DAT_1           HCN
// Oct. 02  Changement de nom : "FVX_1" Fat Vertices
//          a la place de "DAT_1" Body Datumization                  HCN
// Oct. 02  Changement de nom en CATGeoClnFatVextex
//          Possibilite de checker/cleaner un body                   HCN 
// Oct. 02  CheckOrCleanCGMEntity(...)                               HCN
// Jan. 03  friend class CATGeoClnFatGeometries                      HCN
// Aug. 03  Derivation de CATGeoClnBodyDatumiser                     HCN
// Nov. 03  Methode definie par CATCGMCLEANER_RULE_CREATE_XXX        HCN
//=============================================================================

#ifndef CATGeoClnFatVertex_h
#define CATGeoClnFatVertex_h

#include "CATGeoClnBodyDatumiser.h"

//*********************************************************************************
// On ne peut pas utiliser les macros definies dans CATGeoClean.h car on
// veut heriter de CATGeoClnBodyDatumiser
//*********************************************************************************

CATCGMCLEANER_RULE_CREATE_DECLARE( CATGeoClnFatVertex, ExportedByCATCGMGeoClnTopo )

class ExportedByCATCGMGeoClnTopo CATGeoClnFatVertex : public CATGeoClnBodyDatumiser
{
public :
  CATGeoClnFatVertex(CATSoftwareConfiguration* ipConfig,
                     CATICGMUnknown*           ipICGMFederator,
                     CATCGMRuleDef*            ipCGMRuleDef,
                     CATBoolean                iVerbose);
  
  ~CATGeoClnFatVertex();

  CATCGMNewClassArrayDeclare;
  
  static CATGeoCln* CreateRule(CATSoftwareConfiguration* ipConfig,
                               CATICGMUnknown*           ipICGMFederator,
                               CATCGMRuleDef*            ipCGMRuleDef,
                               CATBoolean                iVerbose);
  
  virtual void SetBodyDatumiserTargetType(CATBodyDatumiser* ipBodyDatumiser);
};

#endif
