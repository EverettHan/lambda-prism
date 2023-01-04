#ifndef CATMakePoint_H
#define CATMakePoint_H
//--------------------------------------------------------------------------------------------------------
// Customized performance tool adapter.
//    incorporating of course  System CATMakeStartPoint && CATMakeStopPoint   
//        but adding some additional generic features of component modeler such as Geometrical Domain 
//        intermediate logging ,  used for a more popular approach of Performance  
//    for elementary results without advanced specialized cookbooks.    
//--------------------------------------------------------------------------------------------------------
#include "CATDataType.h"
#include "CATUnicodeString.h"
#include "CATPerformanceToolAdapter.h"

#include "CATCGAreport_Measures.h"

#include "CATMathInline.h"
#include "CATMathematics.h"
#include "CATCGAreport_PCS.h"
#include "CATCGATimer.h"
#include "CATListPV.h"
 
 
class CATCGAPoorMeasure ;
class CATCGMemoryPOOL;
class CATCGMExitProcess;
class CATTime;
class CATMfMechanicalFeature;
class CATCGAMeasure;
class CATExtCGMReplay;
class CATCGATimer;
class CATechSetup;
class CATGMayday;
class CATMathODTCGM;
class CATCGMemoryPOOL_Session;
 

#if ! defined ( ForwardExportedByCATMathStream )
#ifdef _STATIC_SOURCE
#define	ForwardExportedByCATMathStream
#elif defined(__CATMathStream)
#define ForwardExportedByCATMathStream DSYExport
#else
#define ForwardExportedByCATMathStream DSYImport
#endif
#include "DSYExport.h"
#endif

class CATSoftwareConfiguration;
ForwardExportedByCATMathStream  short GetCGMLevel(CATSoftwareConfiguration* iConfig, const char* iModifId);


/**
 * CATMakePoint , reviewing a legacy of performance check points which should not be so widespread 
 *  For instance, according to best practices and mkCheckSource ,  
 *        CATMakeStartPoint && CATMakeStopPoint is forbidden inside GM Core Modeling
 *  On the other side, the global relimitation impact of PCS criteria
*       should be easier and more accessible than the actual numerous personnal cookbooks.
 */
class  ExportedByCATMathematics CATMakePoint
{ 
public:

 //  Legacy  (199.. equivalent of  CATMakeStartPoint && CATMakeStopPoint  _
 static void GetPrimayKEY(char uuidChar[CATMakePointMAXPrimayKEY], CATTime & oStartTime );  
 static void GetComputerAndMain(CATUnicodeString & oComputer, CATUnicodeString & oEXE );

  //  Legacy  (199.. equivalent of  CATMakeStartPoint && CATMakeStopPoint  _
 static HRESULT Start(void* Object, const char* ObjectName,  CATMonitoredObjectType CurrentType = BasicType ) ;
 static HRESULT Stop(void* Object,  const char* ObjectName,  CATMonitoredObjectType CurrentType = BasicType ) ;
   
private:
  
  static const CATBoolean  _IsForbidden;
  static  CATBoolean       _FullForceUpgradeAuthorised;

  friend class CATCGAPoorMeasure ;
  friend class CATCGMemoryPOOL;
  friend class CATCGMemoryPOOL_Session;
  friend class CATCGMExitProcess;
  friend class CATMfMechanicalFeature;
  friend class CATCGAMeasure;
  friend class CATExtCGMReplay;

  // AuthorisedQueryPerformance
  friend class CATCGATimer;
  friend class CATGMayday;
  friend class CATechSetup;
  friend class CATMathODTCGM;

  friend ForwardExportedByCATMathStream  short GetCGMLevel(CATSoftwareConfiguration* iConfig, const char* iModifId);

};
 
 

#endif
