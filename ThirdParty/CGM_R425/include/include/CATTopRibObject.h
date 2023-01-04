/* -*-C++-*- */

#ifndef CATTopRibObject_H
#define CATTopRibObject_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//------------------------------------------------------------------------------
//
// CATTopRibObject
// Base class for all Rib objects
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// March 2000    Creation                         R. Rorato
//------------------------------------------------------------------------------

#include "PersistentCell.h"
#include "CATCGMVirtual.h"
#include "CATBoolean.h"
#include "CATTopOperator.h"
#include "CATListOfCATGeometries.h"
#include "ListPOfCATTopRibObject.h"
//#define CATTopRibObjectInterruptPerfo
#ifdef CATTopRibObjectInterruptPerfo
#include "CATTime.h"
#include "CATLib.h"
#endif

class CATExtTopOperator;
class CATCGMOutput;
class CATError;
class CATCGMDiagnosis;

class CATBody;
class CATShell;
class CATDomain;
class CATGeometry;
class CATFace;
class CATEdge;
class CATVertex;
class CATLoop;
class CATWire;
class CATPoint;
class CATMacroPoint;
class CATPointOnSurface;
class CATPointOnEdgeCurve;
class CATPointOnCurve;
class CATCurve;
class CATPCurve;
class CATPLine;
class CATEdgeCurve;
class CATSurface;
class CATFilletSurface;
class CATLaw;
class CATICGMTopOperator;
class CATLiveBody;
class CATCGMProgressBar;

#include "CATSafe.h"
CATSafeDefine(CATTopRibObject);

class ExportedByPersistentCell CATTopRibObject : public CATCGMVirtual
{

  CATCGMVirtualDeclareClass(CATTopRibObject);

public:
//===========================================================================================================

  //------------------------------------------------------------------------------
  // Constructor
  //------------------------------------------------------------------------------
  CATTopRibObject();
  CATTopRibObject(const CATTopRibObject & iObjectToCopy);
  CATTopRibObject& operator=(const CATTopRibObject &iObjectToCopy);

  //------------------------------------------------------------------------------
  // Destructor
  //------------------------------------------------------------------------------
  virtual ~CATTopRibObject();

  //------------------------------------------------------------------------------
  // Access to Tag
  //------------------------------------------------------------------------------
  CATULONG32 GetTag() const;

  //------------------------------------------------------------------------------
  // Dump internal data
  //------------------------------------------------------------------------------
  virtual void Dump(CATCGMOutput& ioOS);

  //------------------------------------------------------------------------------
  // Display 
  //------------------------------------------------------------------------------
  virtual void Display(const int iR=7, const int iG=7, const int iB=7, 
                       CATLISTP(CATGeometry) * iCreatedObject=NULL);

  //------------------------------------------------------------------------------
  // Check internal validity of this object
  //------------------------------------------------------------------------------
  virtual void Check();

  void CheckKO(const char* iMessage, const CATBoolean iSevere=TRUE); // To be called whenever Check detects error

  //------------------------------------------------------------------------------
  // Garbage Collector
  //------------------------------------------------------------------------------
  void LinkForDelete(CATTopRibObject* iObjectToDelete);

  //------------------------------------------------------------------------------
  // Common utilities
  //------------------------------------------------------------------------------
  static void ThrowInternalError();
  static int GetTraceOption(int DebugLevel=0); // 0: inactive  >0: active
  static int GetCheckOption(); // 0: inactive  >0: active

  //------------------------------------------------------------------------------
  // Flush all errors except a few specific error types that are kept
  // returns TRUE if Flush succeeded (call from within CATCatch block), then iError is set to NULL
  //------------------------------------------------------------------------------
  static CATBoolean FilteredFlush(CATError* &ioError);


  void SetMasterOperator(CATExtTopOperator*         iMasterOperator = NULL);
  void SetMasterOperator(CATTopOperator*            iMasterOperator = NULL);
  void SetMasterOperator(CATICGMTopOperator*        iIMasterOperator = NULL);
  void SetMasterOperator(CATTopRibObject* iObjectWithMasterOperator = NULL);

  CATCGMProgressBar* GetProgressBar() const;

  CATBoolean CheckIfAlive ();

  static void ResetMaxTag(int iOperatorLevel = 1);
  static int       _MinOperatorLevelForReset;
  static void ResetMinOperatorLevelForReset();

  static CATBody             *ConvertToBody            (CATGeometry *iGeometry); // safe
  static CATDomain           *ConvertToDomain          (CATGeometry *iGeometry); // safe
  static CATShell            *ConvertToShell           (CATGeometry *iGeometry); // safe
  static CATFace             *ConvertToFace            (CATGeometry *iGeometry); // safe
  static CATEdge             *ConvertToEdge            (CATGeometry *iGeometry); // safe
  static CATVertex           *ConvertToVertex          (CATGeometry *iGeometry); // safe
  static CATLoop             *ConvertToLoop            (CATGeometry *iGeometry); // safe
  static CATWire             *ConvertToWire            (CATGeometry *iGeometry); // safe
  static CATCell             *ConvertToCell            (CATGeometry *iGeometry); // safe
  static CATPoint            *ConvertToPoint           (CATGeometry *iGeometry); // safe
  static CATMacroPoint       *ConvertToMacroPoint      (CATGeometry *iGeometry); // safe
  static CATPointOnSurface   *ConvertToPointOnSurface  (CATGeometry *iGeometry); // safe
  static CATPointOnEdgeCurve *ConvertToPointOnEdgeCurve(CATGeometry *iGeometry); // safe
  static CATPointOnCurve     *ConvertToPointOnCurve    (CATGeometry *iGeometry); // safe
  static CATCurve            *ConvertToCurve           (CATGeometry *iGeometry); // safe
  static CATEdgeCurve        *ConvertToEdgeCurve       (CATGeometry *iGeometry); // safe
  static CATPCurve           *ConvertToPCurve          (CATGeometry *iGeometry); // safe
  static CATPLine            *ConvertToPLine           (CATGeometry *iGeometry); // safe
  static CATSurface          *ConvertToSurface         (CATGeometry *iGeometry); // safe
  static CATFilletSurface    *ConvertToFilletSurface   (CATGeometry *iGeometry); // safe
  static CATGeometry         *ConvertToGeometry        (CATGeometry *iGeometry); // safe
  static CATLaw              *ConvertToLaw             (CATICGMObject *iObject); // safe

  // DRepLifeCycle
  virtual CATLiveBody * GetLiveBodyCGM(CATBody * iCreationBody);
  
protected:
//===========================================================================================================

  //------------------------------------------------------------------------------
  // Warning management & Interrupt
  // ex: if ( Warning_On == GetWarningMode() )   // Warning_Off Warning_Advanced
  //------------------------------------------------------------------------------
  CATCGMWarning GetWarningMode() const;
  void AppendWarning(CATCGMDiagnosis* iWarning);
  virtual void ThrowIfInterrupted(const int iProgressValue=0, const int iProgressRange=0);
  CATCGMInterruptFunction GetInterruptFunction() const;

  //------------------------------------------------------------------------------
  // Errors
  //------------------------------------------------------------------------------
  virtual void              NotifyProblem();
  virtual void              RIBThrow_InvInput();
  virtual void              RIBThrow_BadTopo();

  void GetInputObjectsForJournal(CATBoolean              & oSucceeded,
                                 CATLISTP(CATICGMObject) & oObjects,
                                 CATTopCheckJournalType    iCopy_Or_Not   = CATTopCheckCopy,
                                 CATGeometricType          iTypeOfObjects = CATBodyType     ) ;

private:
//===========================================================================================================

  //------------------------------------------------------------------------------
  // Data
  //------------------------------------------------------------------------------    
  CATULONG32              _Tag ;

  int                     _IsAlive;
  CATTopOperator*         _MasterOperator;
  CATICGMTopOperator*     _IMasterOperator;
  
  CATTopRibObject*        _GCMaster;
  ListPOfCATTopRibObject* _GCSlaves;

  static CATULONG32       _MaxTag ;
  static CATULONG32       _TraceOption ;
  static CATULONG32       _CheckOption ;

  int                     _NbPb;


#ifdef CATTopRibObjectInterruptPerfo
  static CATULONG32  _InterruptionTime;
  static CATTimerId  _InterruptionTimerId;
#endif

};
#endif
