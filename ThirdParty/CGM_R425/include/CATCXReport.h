/* -*-c++-*- */
#ifndef CATCXReport_h
#define CATCXReport_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2000
//-----------------------------------------------------------------------------
#include "CATCX_CHECKUP.h"
#include "CATUnicodeString.h"
#include "CATCGMCheck.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"
#include "ExportedByCATCGMFusion.h"

#define CATCXReportMaxWitness   250
#define CATCXReportMaxEntier    100
//IR-756725 Max size increase 5000 -> 15000
#define CATCXReportMaxUnicode   15000   

class CATCXReport;
class CATCGMObject;
class CATCXReport;

ExportedByCATCGMFusion int SortCATCXReport(CATCXReport *left, CATCXReport *right);
ExportedByCATCGMFusion int TrivialIndexSortCATCXReport(CATCXReport *left, CATCXReport *right);

class ExportedByCATCGMFusion CATCXReport 
{
public:
  CATCGMNewClassArrayDeclare;

  static void BuildIndex(CATCGMObject *topo, const char rule[], const char *offense, char ioName[48], size_t *pioLength = NULL);

  char                        _MsgName[48];
  size_t                      _LgrMsgName;
  int                         _NbCgmObject;
  CATCGMObject*               _CgmObject[CATCXReportMaxWitness+1];    
  int                         _NbEntiers;    
  int                         _Entiers[CATCXReportMaxEntier];
  int                         _NbUnicodes;    
  CATUnicodeString           *_ArrayUnicodes;
  CATCX_CHECKUP::KindOfEvent  _KindOf;
  short                       _isPotDeVin;    
  short                       _isDirectError;    
  short                       _isFromError;
  short                       _isCleaner;
  CATCGMCheck::Category       _Categorie;
  CATBoolean                  _forCompleted;
  void        *               _invalidPointer;
  
  //-------------------------------------------------------------
  // creation of an Event (respect or offense) 
  //-------------------------------------------------------------
  CATCXReport(CATCGMCheck::Category Kategory, CATCGMObject *topo, const char rule[],
    const CATCX_CHECKUP::KindOfEvent what=CATCX_CHECKUP::respect,
    const char *offense=NULL,
    const int nbWitness=0, CATCGMObject*const *witnesses=NULL,
    const int nbint=0, const int *tabint=NULL,
    const int nbother=0, CATUnicodeString *const others=NULL,
    const short potDeVin=0, const short cleaner=0,
    CATBoolean ForCompleted = FALSE);
  
  //-------------------------------------------------------------
  // creation of an Event (external Error) 
  //-------------------------------------------------------------
  CATCXReport(CATCGMObject *topo, CATCGMObject *geo, CATError* err,
    CATCGMCheck::Category Kategory, CATBoolean ForCompleted = FALSE);
    
  //-------------------------------------------------
  // Destructeur
  //-------------------------------------------------
  ~CATCXReport();

  //-------------------------------------------------------------
  // generation of a message adequate to the EVENT
  //-------------------------------------------------------------
   void BuildMessage(const int withHeader, CATUnicodeString &iomsg);
  
  //-------------------------------------------------------------
  // Give all information needed
  //-------------------------------------------------------------
  void BuildMessage(int & nb, CATCGMObject* * &objects, 
    CATCX_CHECKUP::KindOfEvent &nature, const int withHeader, CATUnicodeString &iomsg);

  //-------------------------------------------------------------
  // Query on an event, to ask if concerned 
  //-------------------------------------------------------------
  int IsConcernedBy(CATCGMObject *const concerned);
  //-------------------------------------------------------------
  // Query on main Object
  //-------------------------------------------------------------
  CATCGMObject *GetMainObject( CATCX_CHECKUP::KindOfEvent &nature);
private :
   //For internal use :
   //Constraint the number of relevant objects to Dump according 
   // to the nature of the offense
   int HowManyObjectToDump();
};

#endif
