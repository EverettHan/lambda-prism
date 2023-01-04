// COPYRIGHT DASSAULT SYSTEMES  <1996>
//=============================================================================
//
// CATSubdPerf.h:
//
//=============================================================================
// Usage Notes:
//
// systeme de services et macro permettant de faire des mesures CPU 
// facilement debrayables
//
//=============================================================================
// Mar. 97   Creation                                             Yves RIBIERE
//=============================================================================
//
#ifndef CATSubdPerf_H
#define CATSubdPerf_H

// La ligne suivante active les macros de mesure CPU, sa mise en commentaire
// supprime ces mesures (apres un re-build...)
#define CATSubdPerfOn

// Macros de mesure CPU
#ifdef CATSubdPerfOn

// Mesures unitaires
//===================
// Debut de mesure
#define CATSubdPerfBegin(text)    CATSubdPerfoMeasureStart(text)
// Fin de la derniere mesure lancee, sortie des temps
#define CATSubdPerfEnd            CATSubdPerfoMeasureStop()

// Mesures cumulees
//===================
// Initialisation d'une mesure cumulee referencee par text
#define CATSubdPerfCumulInit(id, text)      CATSubdPerfoCumulMeasureInit(id, text)
// Debut d'une mesure cumulee referencee par id
#define CATSubdPerfCumulBegin(id)           CATSubdPerfoCumulMeasureStart(id)
// Fin d'une mesure cumulee referencee par id, cumul mis a jour
#define CATSubdPerfCumulEnd(id)             CATSubdPerfoCumulMeasureStop(id)
// Fin definitive d'une mesure cumulee referencee par id, sortie des temps
#define CATSubdPerfCumulFinish(ident, id)          CATSubdPerfoCumulMeasureFinish(ident, id)

#else

// Mesures unitaires
#define CATSubdPerfBegin(text)
#define CATSubdPerfEnd
// Mesures cumulees
#define CATSubdPerfCumulInit(id, text)
#define CATSubdPerfCumulBegin(id)
#define CATSubdPerfCumulEnd(id)
#define CATSubdPerfCumulFinish(ident, id)

#endif

//DG
#include "BOOLEAN.h"

// Services de mesures CPU unitaires
ExportedByBOOLEAN void CATSubdPerfoMeasureStart(const char *);
ExportedByBOOLEAN void CATSubdPerfoMeasureStop(void);
// Services de mesures CPU cumulees
ExportedByBOOLEAN void CATSubdPerfoCumulMeasureInit(int, const char *);
ExportedByBOOLEAN void CATSubdPerfoCumulMeasureStart(int);
ExportedByBOOLEAN void CATSubdPerfoCumulMeasureStop(int);
ExportedByBOOLEAN void CATSubdPerfoCumulMeasureFinish(int, int);

#endif // CATSubdPerf_H
