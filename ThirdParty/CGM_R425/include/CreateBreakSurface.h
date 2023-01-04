// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CreateBreakSurface :
// Declaration of global functions used to create and destroy
// an instance of the Break Surface operator
//
//=============================================================================
// Usage notes:
//  Attention :
//    Cet operateur de break par PCurve  tient compte des limites de la PCurve:
//    Si les MaxLimits sont differentes des Limits , alors ce sont les  
//    Limits qui sont prises en compte  
//    Concernant la surface : 
//    Si la surface est extrapolee et que ses MaxLimits sont differentes 
//    de ses Limits ce sont les Max qui sont prises en compte .
//    Pour ne prendre en compte que la partie initiale de la surface ,
//    Il faut refaire un Set des Limits .
//
//=============================================================================
// July. 97  Creation                          GDR
// Feb.  98  Modification (with a KnotRank)    NDN
//=============================================================================
#ifndef CreateBreakSurface_H 
#define CreateBreakSurface_H 
//
#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"
#include "CATIsoParameter.h"
#include "CATListOfCATPCurves.h"
//
class CATGeoFactory;
class CATPCurve;
class CATPointOnSurface;
class CATBreakSurface;
class CATNurbsSurface;
class CATSoftwareConfiguration;

ExportedByCATGMOperatorsInterfaces
CATBreakSurface * CATCreateBreakSurface(CATGeoFactory  *iFactory, CATSoftwareConfiguration * iSoftwareConfiguration,
                                        CATPCurve *iCurve,
                                        CATSkillValue iMode = BASIC);

ExportedByCATGMOperatorsInterfaces
CATBreakSurface * CATCreateBreakSurface(CATGeoFactory  *iFactory, CATSoftwareConfiguration * iSoftwareConfiguration, 
                                        CATPointOnSurface *iPtBreak,
                                        CATSkillValue iMode = BASIC);
ExportedByCATGMOperatorsInterfaces
CATBreakSurface * CATCreateBreakSurface(CATGeoFactory  *iFactory, CATSoftwareConfiguration * iSoftwareConfiguration,
                                        CATLISTP(CATPCurve ) &iListe,
                                        CATSkillValue iMode = BASIC);

ExportedByCATGMOperatorsInterfaces
CATBreakSurface * CreateBreakSurface(CATGeoFactory  *iFactory,
                                     CATPCurve *iCurve,
                                     CATSkillValue iMode = BASIC);

ExportedByCATGMOperatorsInterfaces
CATBreakSurface * CreateBreakSurface(CATGeoFactory  *iFactory,
                                     CATPointOnSurface *iPtBreak,
                                     CATSkillValue iMode = BASIC);

ExportedByCATGMOperatorsInterfaces
CATBreakSurface * CreateBreakSurface(CATGeoFactory  *iFactory,
                                     CATLISTP(CATPCurve ) &iListe,
                                     CATSkillValue iMode = BASIC);
//
ExportedByCATGMOperatorsInterfaces
void Remove( CATBreakSurface *&ioBreakSurface );

#endif


