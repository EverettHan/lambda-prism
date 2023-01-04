#ifndef CATTopOriShellVsVolume_H
#define CATTopOriShellVsVolume_H
//=============================================================================
// Function to calculate the orientation of a closed shell
// in view of volume creation (si l'orientation est negative, il faut inverser
// les faces par rapport au shell avant de creer le volume)
//-----------------------------------------------------------------------------
// Juin/June 2009   Creation                                  LD2
//=============================================================================
#include "ExportedByCATTopologicalObjects.h"
#include "CATTopDefine.h"

class CATGeoFactory;
class CATShell;
class CATSoftwareConfiguration;

ExportedByCATTopologicalObjects CATOrientation CATTopOriShellVsVolume(CATGeoFactory* iFactory,
                                                                      CATShell * iShell,
                                                                      CATSoftwareConfiguration * iConfig);

#endif
