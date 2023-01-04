#ifndef CATCGAreport_PCS_H
#define CATCGAreport_PCS_H
//------------------------------------------------------------------------------
// Outils de Validation massive a partir d'une reutilisation de Persistence
//   Progressivite dans les traitements sur une multitude de fichiers 
//   Ouverts pour des operations specialisees
//------------------------------------------------------------------------------
#include "CATCGAreport_Measures.h"

#include "CATMathematics.h"
#include "CATCGMNewArray.h"
#include "CATDataType.h"
#include "CATMathInline.h"
#include "CATCGATimer.h"
#include "CATCGAMeasureContext.h"


class CATCGMItfName;

#define CATMakePointMAXPrimayKEY 72

/**
 * CATCGAreport_PCS  (Cf CATechTimer)
 */
class ExportedByCATMathematics CATCGAreport_PCS
{ 
public:

  CATCGMNewClassArrayDeclare;  

  INLINE CATCGAreport_PCS(const CATCGAMeasureContext &iCopy)  
    : _NbMeasures(0), _Context(iCopy)
  {}

  INLINE CATCGAreport_PCS(const char * iOperation, const char * iOperationDomain , CATCGMItfName    *  iWorkingFeature)  
    : _NbMeasures(0), _Context(iOperation,iOperationDomain,iWorkingFeature)
  {} 

  INLINE CATCGAreport_PCS() 
    : _NbMeasures(0)
  {} 

  /**
  * Reset 
  */
  void  Reset();

  /**
  * AddMeasure 
  */
  void  AddMeasure(CATCGATimer & iMeasure, const CATULONG64 iDiskBytes );

  /**
  * AddMeasure 
  */
  void  AddMeasure(CATCGAreport_Measures & iMeasure );

  /**
  * GetRSD  (return number of measures)
  */
  int  GetRSD(double & oCpu, double  & oElapsed, double & oWorkingSetDelta, CATULONG64 & oTicks, CATULONG64 & oDiskBytes,
              double oRSD[report_PCS_NbMeasures] );


  /**
  * Sum 
  */
  void  Sum(const CATCGAreport_PCS & iReport );
 
  // Number of measures
  int                    _NbMeasures;
  //  
  CATCGAMeasureContext   _Context;

  // Average
  CATCGAreport_Measures _Average;
 
  // RSD
  CATCGAreport_Measures _SquareSum;

  // Min
  CATCGAreport_Measures _Min;

  // Max
  CATCGAreport_Measures _Max;


 
private :

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGAreport_PCS(const CATCGAreport_PCS &iCopy);
  CATCGAreport_PCS& operator=(const CATCGAreport_PCS &iCopy);
};
 
 
 
#endif
