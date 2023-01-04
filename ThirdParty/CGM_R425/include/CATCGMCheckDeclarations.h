
#ifndef CATCGMCheckDeclarations_H
#define CATCGMCheckDeclarations_H

/**
 * @COPYRIGHT DASSAULT SYSTEMES 2004
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2004
// DESCRIPTION : Declarations and Constants for CGM check rules.
//
// May2004	  Creation                                                      AJM
// 18/01/08 NLD XScale. CGM_CHECK_TOLERANCE_NUMERICAL_RELATIVE remplace CGM_CHECK_TOLERANCE_NUMERICAL
// 14/11/12 NLD XScale. CGM_CHECK_TOLERANCE_LENGTHTEST remplace CGM_CHECK_TOLERANCE_NUMERICAL_RELATIVE desormais devoyee
//=============================================================================


// #define CGM_CHECK_ACTIVATE_TRACES

#ifdef CGM_CHECK_ACTIVATE_TRACES
  #include <iostream.h>
#endif

//=============================================================================

// Env var for enabling debug dump for AJM
#define CGM_DEBUG_AJM                 "CGM_DEBUG_AJM"

// Env var for enabling Impure check (for 'Failed' Checks)
#define CGM_CHECK_IMPURE_RESULT       "CGM_CHECK_IMPURE_RESULT"

// Env var for enabling Impure check (for 'Caught' Throws)
#define CGM_CHECK_IMPURE_THROW        "CGM_CHECK_IMPURE_THROW"

//=============================================================================

// Env vars for ICG_1 check: number of samples 
#define CGM_CHECK_ICG_NB_SAMPLES          (15)
#define CGM_CHECK_ICG_NB_SAMPLES_MAX      (CGM_CHECK_ICG_NB_SAMPLES - 1)

// Env vars for INF_1 check: number of samples 
#define CGM_CHECK_INF_NB_SAMPLES          (9)
#define CGM_CHECK_INF_NB_SAMPLES_MAX      (CGM_CHECK_INF_NB_SAMPLES - 1)

// Env vars for ULO_1 check: to bypass line's check
#define CGM_CHECK_ULO_BYPASS_LINES        "CGM_CHECK_ULO_BYPASS_LINES"

// Env vars for PPO_1 check: to check the support
#define CGM_CHECK_PPO_CHECK_SUPPORT       "CGM_CHECK_PPO_CHECK_SUPPORT"

//=============================================================================

// Tolerances for CGM check rules
//                                              l'ancienne tolerance CGM_CHECK_TOLERANCE_NUMERICAL renommee CGM_CHECK_TOLERANCE_NUMERICAL_RELATIVE
//                                              pour enfoncer le clou et pervertie par operations d'Octobre 2012 est desormais
//                                              nommee CGM_CHECK_TOLERANCE_LENGTHTEST pour un respect minimum des nomenclatures de l'esprit
//                                              et de la maintenabilite du code.                                                         NLD141112
#define CGM_CHECK_TOLERANCE_LENGTHTEST          GetToleranceObject().LargeEpsgForLengthTest()
//#define CGM_CHECK_TOLERANCE_NUMERICAL_RELATIVE  GetToleranceObject().LargeEpsgForLengthTest() // *** NE PLUS UTILISER. RESTE TRANSITOIREMENT 141112 POUR LIMITATION IMPORTS SI CONFLITS DE LIVRAISON ****
//#define CGM_CHECK_TOLERANCE_NUMERICAL_NOTTOUSE  (CATSqrtEpsg)
// Env var for altering the numerical tolerance value
#define CGM_CHECK_ENV_TOLERANCE_NUMERICAL       "CGM_CHECK_ENV_TOLERANCE_NUMERICAL"
// Env var for altering the geometrical tolerance value
#define CGM_CHECK_ENV_TOLERANCE_GEOMETRICAL     "CGM_CHECK_ENV_TOLERANCE_GEOMETRICAL"

//=============================================================================


#endif // CATCGMCheckDeclarations_H

