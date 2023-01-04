#ifndef CATUnofficialAndNonOptimized_h
#define CATUnofficialAndNonOptimized_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1999
/**
  * @level Private
  * @usage U1
  *    
  *   2013.Week 18   ->   01.04.2013 
  *      for enhance advanced expert internal dedicated cookbooks with safe pcs noise reduction on commercial software  
  *      Enhancing some DEBUG unexpected  (and useless) on end-user interactive commercial package but visibile by  PCS indicators 
  *
  *  As some internal advanced but intermediate debug and support technics
  *     may have some  significant and visible influence on commercial end-user performance
  *     (commercial package or integrated applicative solutions)
  *
  * Under conditions that those debug symbols are visible 
  *    for instance inside external third party PCS measures such as http://pcs/coverage.php
  *    Those internal proprieraty cookbooks unexpected inside commercial or PCS conditions
  *    may be restrained to elementary debug purpose
  *
  * Those technics required at least one of the following explicit environnement variables
  *    either classical general purpose          CATDevelopmentStage=TRUE       () 
  *    either dedicated and customized variable  CATUnofficialAndNonOptimized   (to reduce without noise on those particular technics)
  *      
 */
 
#include "CATCGMKernel.h"
#include "CATBoolean.h"
 

extern  ExportedByCATCGMKernel CATBoolean CATUnofficialAndNonOptimized;
 
#endif
