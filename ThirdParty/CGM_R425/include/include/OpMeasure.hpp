// COPYRIGHT DASSAULT SYSTEMES 2013
#ifndef OpMeasure_HPP
#define OpMeasure_HPP
/* 
*  Ligth Interfaces Binding (For scalable and simple generic purpose)
*
*   For ZERO FootPrint (excluding live infrastructure prerequisite such as Fw System !! )
*      -> a kind of design ready for Fw SpecialAPI embedded :-)
*
*   and on demand Monitoring (some similary with V5PCSToolsPrivate )
*       but for more oriented for explicit applied domains indicators 
*       (rather than external Operating System capacity and scalability indicators) 
*/
#include "CATOpDataItf.hpp"


#define MAXNAMELENGTH 64

namespace OpMeasure
{

/** 
  * Declare a secure (before and after must be securize by catch/rethrow)
  *    explicit monitored measure (rather than an external samplings or interrruptions)
  *    to see if it is meaningfull for further analysis .
  *
  *
  * @param iDataDomain
  *       : Domain of Measure (for instance Geometric Modeling)  
 *
  * @param iName
  *       : Context of measure , Name is relative to previous DataDomain
  *
  * @param iBeforeOneShotAfter
  *    +1 : Before .
  *     0 : OneShot.
  *    -1 : After .
  *    -2 : end of process (restricted used) .
 *
  * @param iLocalStackDepth
  *       : In case of local relative Stack
  *
 */           

  extern "C" ExportedByCATOpDataItf void CATOpMeasure(const char *iDataDomain, const char *iName, int iBeforeOneShotAfter = 0, int iLocalStackDepth = -1);


/** 
  * Internal Utilities
 */           

  extern "C" ExportedByCATOpDataItf int CATOpModuleToFwTreeResp(const char *iModule, char oFw[MAXNAMELENGTH], char oTree[MAXNAMELENGTH], char oResp[MAXNAMELENGTH] );



} ;


 
#endif
