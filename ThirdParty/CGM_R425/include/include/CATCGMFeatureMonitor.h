#ifndef CATCGMFeatureMonitor_h
#define CATCGMFeatureMonitor_h
#include "ExportedByGeometricObjects.h"
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2002
//   Coverage, See CATCGAMeasure superseding this old deprecated debug
//=============================================================================

#include <stdlib.h>
#include <stddef.h>
#include "CATDataType.h"
#include "ExportedByGeometricObjects.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATGemDebugPartUpdate.h"
#include "CATCGMFactoryTransaction.h"
#include "CATCGMVirtual.h"
#include "CATMathInline.h"

class CATISpecObject;
class CATBrpGraph;
class CATReportAppliElt;
class CATIMfProcReport;

class CATDocument;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATICGMUnknown;
class CATICGMObject;
class CATCGMItfName;


//--------------------------------------------------------------------
// Gestion de transaction d'Update
//-------------------------------------------------------------------- 
class ExportedByGeometricObjects CATCGMFeatureMonitor : public CATCGMVirtual
{
public:
 
  static void  CATCGAMeasureFlush(CATDocument *iDoc);
 
protected:
  CATCGMFeatureMonitor();
  virtual ~CATCGMFeatureMonitor();

  virtual void  _CATCGAMeasureFlush(CATDocument *iDoc)  = 0;
 
};

 
#define  CATCGMFeatureMonitor_DEBUG_CreateProcReport(iFeature,iGraph) 
#define  CATCGMFeatureMonitor_DEBUG_StoreProcReport(iFeature,iReportFeature,iMainResult) 
#define  CATCGMFeatureMonitor_DEBUG_DeleteProcReport() 
#define  CATCGMFeatureMonitorBegin(iLevel,iFeature,iOldGeometry)  
#define  CATCGMFeatureMonitorEnd(iLevel,iFeature,iNewGeometry)  


#endif
