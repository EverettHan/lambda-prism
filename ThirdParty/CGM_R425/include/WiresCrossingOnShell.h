#ifndef WiresCrossingOnShell_h
#define WiresCrossingOnShell_h

//************************************************************************************************************
// Function WiresCrossingOnShell
//-----------------------------------------------------------------------------------------------------------
// This function returns TRUE if iWireBody1 and iWireBody2 are crossing.
// Conditions for the algorithm to work properly:
//  - iShellBody must contain 1 (and only 1) shell
//  - iWireBody1 must contain 1 (and only 1) wire
//  - iWireBody2 must contain 1 (and only 1) wire
//  - The 2 wires must be lying on the shell
//  - Input wires shouldn't represent dead-ends on the shell
//-----------------------------------------------------------------------------------------------------------
// 2012 WEEK 21     Creation                                                                        LD2
// 2012 WEEK 23     Change parameters iWire1Edges and iWire2Edges to from ListPOfCATCell to         G5S
//                  ListPOfCATEdge.
//************************************************************************************************************

#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "ListPOfCATTopology.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATEdge.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATBody;

/** @nodoc @nocgmitf */
ExportedByCATTopologicalObjects CATBoolean WiresCrossingOnShell(CATGeoFactory * iFactory,
                                                                CATSoftwareConfiguration * iConfig,
                                                                CATBody * iShellBody,
                                                                CATBody * iWireBody1,
                                                                CATBody * iWireBody2);

/** @nodoc @nocgmitf */
ExportedByCATTopologicalObjects CATBoolean WiresCrossingOnShell(CATGeoFactory * iFactory,
                                                                CATSoftwareConfiguration * iConfig,
                                                                ListPOfCATTopology & iShellFaces,
                                                                ListPOfCATTopology & iWire1Edges,
                                                                ListPOfCATTopology & iWire2Edges);

/** @nodoc @nocgmitf */
ExportedByCATTopologicalObjects CATBoolean WiresCrossingOnShell(CATGeoFactory * iFactory,
                                                                CATSoftwareConfiguration * iConfig,
                                                                ListPOfCATCell & iShellFaces,
                                                                ListPOfCATEdge & iWire1Edges,
                                                                ListPOfCATEdge & iWire2Edges);

#endif
