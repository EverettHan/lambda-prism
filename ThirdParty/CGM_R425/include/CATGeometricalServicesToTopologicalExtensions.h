/* -*-c++-*- */
/**
* @COPYRIGHT DASSAULT SYSTEMES 2009
*/
#ifndef CATGeometricalServicesToTopologicalExtensions_H 
#define CATGeometricalServicesToTopologicalExtensions_H 
//=============================================================================
// DESCRIPTION : CATGeometricalServicesToTopologicalExtensions
//=============================================================================
// October. 09 Extension topologique for CloneManager 
//=============================================================================
#include "YP0LOGRP.h"
#include "CATBoolean.h"
#include "CATCX_MEMORY.h"
#include "CATCGMStreamVersion.h"
#include "CATErrorDef.h"
#include "CATCGMJournal.h"

class CATExtCloneManager;
class CATExtClonableManager;
class CATExtCGMReplay;
class CATCXduplicateManager;
class CATICGMObject;
class CATMathStream;
class CATCGMJournalList;  
class CATLISTP(CATExtClonableAttributes);

/**
*  Class for GeometricalServices To TopologicalExtensions
*/
class ExportedByYP0LOGRP CATGeometricalServicesToTopologicalExtensions
{
public :
 

  /**
  * GetServices .
  */
  static CATGeometricalServicesToTopologicalExtensions*  GetServices();
  
  /**
  * Destructor .
  */
  virtual ~CATGeometricalServicesToTopologicalExtensions();

 
  /**
  * Asynchroneous ReportClonableAttributes.
  */
  virtual void ReportClonableAttributes(CATExtCloneManager * iCloneManager) = 0 ;

  /**
  * Asynchroneous ReportClonableAttributes.
  */
  virtual void ReportClonableAttributes(CATCXduplicateManager * iDuplicateManager) = 0 ;

  /**
  * Debug HasReportedClonableAttributes.
  */
  virtual CATBoolean HasReportedClonableAttributes(CATICGMObject *iClonableAttributes) = 0 ;

#ifdef CATIACGMR421CAA
  /**
  * WriteImprintReport.
  */
  virtual void WriteImprintReport(CATLISTP(CATExtClonableAttributes) *piClonableAttributes, CATCGMJournalList *&ioJournal, CATCGMJournal::Type iType , CATBoolean iAddInfo) = 0;
#endif
  /**
  * Debug Relimitation Impact Replay .
  *    Des operateurs recoivent en Input des adresses de journaux invalides
  *    qui ne sont detectees que sur ces operations 
  */
   static CATBoolean CATCGMReplayWithJournaling();
 
protected  :

  //------------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------------
  CATGeometricalServicesToTopologicalExtensions();

  static CATGeometricalServicesToTopologicalExtensions* _Result;

private :

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATGeometricalServicesToTopologicalExtensions(const CATGeometricalServicesToTopologicalExtensions &iCopy);
  CATGeometricalServicesToTopologicalExtensions& operator=(const CATGeometricalServicesToTopologicalExtensions &iCopy);
 
};


 
/**
* @nodoc
*/
extern "C" { typedef CATGeometricalServicesToTopologicalExtensions* CATGeometricalServicesToTopologicalExtensions_Creator(); }  

#endif
