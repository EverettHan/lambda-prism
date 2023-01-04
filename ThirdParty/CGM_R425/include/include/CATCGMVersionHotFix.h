/* -*-C++-*-*/
#ifndef CATCGMVersionHotFix_H
#define CATCGMVersionHotFix_H
// COPYRIGHT DASSAULT SYSTEMES 2006
//----------------------------------------------------------------------------------------------
// Methode permettant de verifier qu'on  est sur un level HotFix donne
//----------------------------------------------------------------------------------------------
#include "ExportedByCATMathStream.h"
#include "CATBoolean.h"

class CATSoftwareConfiguration;

extern ExportedByCATMathStream CATBoolean TorresHFR16SP4(CATSoftwareConfiguration * iConfig);
extern ExportedByCATMathStream CATBoolean AIRBUS_HFR16SP4(CATSoftwareConfiguration * iConfig);
extern ExportedByCATMathStream CATBoolean AIRBUS_HFR16SP9(CATSoftwareConfiguration * iConfig);
extern ExportedByCATMathStream CATBoolean BOEING_HFR19SP5(CATSoftwareConfiguration * iConfig);

#endif

