#ifndef TopoDebugTools_h
#define TopoDebugTools_h
//******************************************************************************************************
// TopoDebugTools
//-----------------------------------------------------------------------------------------------------
// 2011 WEEK 42      Creation                                                       LD2
// 2017 WEEK 32      Modification                                                   U29
//******************************************************************************************************
#include "CATUnicodeString.h"
#include "ExportedByCATTopologicalObjects.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATCGMEventType.h"
#include "CATMathInline.h"
#include "CATCGMPointerPList.h"

class CATICGMObject;
class CATListPtrCATICGMObject;
class CATCGMStream;
class CATCurve;
class CATCrvLimits;
class CATGeoFactory;
class CATCGMJournalList;
class CATCGMOutput;
class CATCGMJournal;
class CATBody;
class CATTopology;
class CATTopOperator;
class CATBodiesMapping;
class CATCGMHashTableWithAssoc;
class CATBaseUnknown;
class CATListPtrCATTopology;
class CATCGMObject;
class CATCell;
class HashTableAssocList;
class CATAdaptiveHashTable;
class CATListValCATUnicodeString;

class ExportedByCATTopologicalObjects TopoDebugTools
{
public:
  //----------------------------------------------------------------------------
  // Tools for dump.
  //----------------------------------------------------------------------------

  /** @nodoc @nocgmitf */
  static const char * SafeIsA(CATICGMObject * iObject);

  /** @nodoc @nocgmitf */
  static const char * SafeIsA(CATCGMObject * iObject);

  /** @nodoc @nocgmitf */
  static CATULONG32 SafeGetPersistentTag(CATICGMObject * iObject);

  /** @nodoc @nocgmitf */
  static CATULONG32 SafeGetPersistentTag(CATCGMObject * iObject);

  //----------------------------------------------------------------------------
  // SaveObjToNCGM: utilities to save one or more CATICGMObject to a NCGM file.
  //----------------------------------------------------------------------------

  /** @nodoc @nocgmitf */
  static HRESULT SaveObjToNCGM(CATListPtrCATICGMObject & iObjects, const char * iCompleteName);

  /** @nodoc @nocgmitf */
  static HRESULT SaveObjToNCGM(CATListPtrCATICGMObject & iObjects, CATUnicodeString iCompleteNameString);

  /** @nodoc @nocgmitf */
  static HRESULT SaveObjToNCGM(CATICGMObject * iObject, CATUnicodeString iCompleteNameString);

  /** @nodoc @nocgmitf */
  static HRESULT SaveObjToNCGM(CATICGMObject * iObject, const char * iCompleteName);

  //----------------------------------------------------------------------------
  // Stream utilities
  //----------------------------------------------------------------------------

  /** @nodoc @nocgmitf */
  static void WriteCurvesToStream(CATCGMStream  & Str,
                                  int             iNbCurves,
                                  CATCurve     ** iCurves,
                                  CATCrvLimits  * iLimits,
                                  short         * iOrientations);

  /** @nodoc @nocgmitf */
  static void ReadCurvesFromStream(CATCGMStream  & Str,
                                   CATGeoFactory  * iFactory,
                                   CATLONG32      & iNbCurves,
                                   CATCurve     **& iCurves,
                                   CATCrvLimits  *& iLimits,
                                   short         *& iOrientations);

  /** @nodoc @nocgmitf */
  static CATBody * ReadBody(CATCGMStream & Str);

  /** @nodoc @nocgmitf */
  static void AddJournalContentsAsInputObjects(CATTopOperator & ioOperator,
                                               CATCGMJournalList & iJournal);


  //----------------------------------------------------------------------------
  // Dump utilities
  //----------------------------------------------------------------------------

  static void DumpCell_TypeAndTag(CATCell* ipCell,
                                  CATCGMOutput & os);

  static void DumpCell_TypeAndTag(CATCell * ipCell,
                                  CATUnicodeString& ioString);

  static void PrintCallStackToCgmOutput(CATCGMOutput & iCgmOutput);


  //----------------------------------------------------------------------------
  // String utilities
  //----------------------------------------------------------------------------

  /** @nodoc @nocgmitf */
  template <class NUMTYPE>
  static CATUnicodeString String(NUMTYPE iNum)
  {
    CATUnicodeString Result;
    Result.BuildFromNum(iNum);
    return Result;
  }

  /** @nodoc @nocgmitf */
  static CATUnicodeString ConvertToStringNCharacters(int iNumber, int N);

  /** @nodoc @nocgmitf */
  static void SplitString(
    const CATUnicodeString & iToRead,
    const char iSeparator,
    CATListValCATUnicodeString & oSubStrings);

  /** @nodoc @nocgmitf */
  static CATUnicodeString MergeStrings(
    CATListValCATUnicodeString & iStrings,
    const char iSeparator);

  /** @nodoc @nocgmitf */
  static CATUnicodeString StringGetNextField(const CATUnicodeString & iToRead,
                                             int & ioIndex,
                                             const char iSeparator);

  /** @nodoc @nocgmitf */
  static CATBoolean StringContainsField(const CATUnicodeString & iToTest,
                                        const char * iField,
                                        CATUnicodeString * oReminder = NULL,
                                        const char iSeparator = ',');

  //----------------------------------------------------------------------------
  // System utilities
  //----------------------------------------------------------------------------

  /** @nodoc @nocgmitf
  * Reads an environment flag and converts the string to an integer.
  * Returns 0 if the environment flag is not set.
  * Differently from CATMathDebug::integerGetEnv, it works also when CATDevelopmentStage is not set.
  * WARNING: this could be expensive in CPU time. We advise to store the result of the call to avoid calling it again.
  */
  static int IntegerGetEnv(const char * iFlag);

  //----------------------------------------------------------------------------
  // Dynamic tool
  //----------------------------------------------------------------------------

  class ExportedByCATTopologicalObjects DynTool
  {
  public:
    static INLINE DynTool * Get()
    {
      static DynTool * _Singleton = DynTool::GetInstance();
      return _Singleton;
    }
    virtual void Send(const CATUnicodeString & iMessage, CATCGMPointerPList * iArguments = NULL, CATUnicodeString * oAnswer = NULL, CATCGMPointerPList * oResults = NULL) = 0;
    virtual void SetParameterValue(const CATUnicodeString & iParameterKey, const CATUnicodeString iParameterValue) = 0;
    virtual CATUnicodeString GetParameterValue(const CATUnicodeString & iParameterKey) = 0;
    virtual CATBoolean CheckParameterValue(const CATUnicodeString & iParameterKey, const CATUnicodeString & iTestedValue) = 0;
  protected:
    DynTool() {}
    virtual ~DynTool() {}
  private:
    static DynTool * GetInstance();
  };

  //----------------------------------------------------------------------------
  // Journal utilities
  //----------------------------------------------------------------------------

  /** @nodoc @nocgmitf */
  static void DumpInJREFStyle(CATCGMJournal * iJournal,
                              CATCGMOutput & ioOutput);

  /** @nodoc @nocgmitf */
  static void DuplicateTassAndDumpJournal(CATCGMJournalList * iJournal,
                                          CATCGMOutput & ioOutput);

  /** @nodoc @nocgmitf */
  static void DuplicateTassAndDumpJournal_jref(CATCGMJournalList * iJournal,
                                               CATCGMOutput & ioOutput);

  /** @nodoc @nocgmitf */
  static CATCGMJournalList * UnStreamJournal(CATCGMStream  & Str,
                                             CATGeoFactory * iFactory);

  /** @nodoc @nocgmitf */
  static void StreamJournal(CATCGMStream  & Str,
                            CATCGMJournalList * iJournal,
                            CATGeoFactory * iFactory);

  /** @nodoc @nocgmitf */
  static CATBoolean SimpleJournalMapping(CATBodiesMapping & iBodiesMappingAlreadyRun,
                                         CATBody & iResultBody,
                                         CATBody & iReferenceBody,
                                         CATCGMJournalList & iResultJournal,
                                         CATCGMJournalList & iReferenceJournal);

  /** @nodoc @nocgmitf */
  static CATBoolean SimpleJournalMapping(CATCGMHashTableWithAssoc & iMappingTable,
                                         CATCGMJournalList & iResultJournal,
                                         CATCGMJournalList & iReferenceJournal);

  //----------------------------------------------------------------------------
  // Statistics tools
  //----------------------------------------------------------------------------

  /** @nodoc @nocgmitf */
  static int ComputeNumberOfCellsInCommon(CATTopology * iTopology1, CATTopology * iTopology2);

  /** @nodoc @nocgmitf */
  static int ComputeNumberOfCellsInCommon(CATTopology * iTopology1, CATListPtrCATTopology & iTopologies2);

  /** @nodoc @nocgmitf
  * U29@100717
  * Moved from CATCGMSplitShellByWires
  * iValue must range from 0.0 to 1.0
  **/
  static void GradualPutColor(CATICGMObject * iObject, double iValue);

  /** @nodoc @nocgmitf
  * Removes all Deletion and Keep items from the journal.
  * (the journal is tassed)
  */
  static void RemoveDeleteAndKeepItems(CATCGMJournalList & ioJournal);

  static int CountVerticesWithUselessPoints(
    CATTopology * iTopology,
    CATCGMEventType iSpecificContext,
    CATAdaptiveHashTable * iVerticesToIgnore = NULL,
    HashTableAssocList * oVertexToUselessPoecs = NULL,
    CATCGMOutput * oDump = NULL);

  static void UnlinkUselessPointsOfVertices(
    CATTopology * iTopology,
    CATCGMEventType iSpecificContext);


private:
  static CATBoolean StringContainsPrefix(CATUnicodeString & iToTest,
                                         CATUnicodeString & iPrefix,
                                         CATUnicodeString * oReminder);
};

/** @nodoc @nocgmitf */
#define MacroDump(CATICGMOBJECT) TopoDebugTools::SafeIsA(CATICGMOBJECT) << " " << TopoDebugTools::SafeGetPersistentTag(CATICGMOBJECT)

/** @nodoc @nocgmitf */
#define ObjectDumperDeclare(ObjectDumper, ObjectType)                                                       \
struct ObjectDumper                                                                                         \
{                                                                                                           \
  ObjectDumper(ObjectType * ipObject);                                                                      \
  ~ObjectDumper();                                                                                          \
  ObjectType * _pObject;                                                                                    \
};                                                                                                          \
CATCGMOutput & operator<< (CATCGMOutput & iCGMOutput, const ObjectDumper & iDumper);

/** @nodoc @nocgmitf */
#define ObjectDumperDefine(ObjectDumper, ObjectType, DumpFunction)                                          \
ObjectDumper::ObjectDumper(ObjectType * ipObject) : _pObject(ipObject) {}                                   \
ObjectDumper::~ObjectDumper() {_pObject = NULL;}                                                            \
CATCGMOutput & operator<< (CATCGMOutput & CGMOutput, const ObjectDumper & iDumper)                          \
{                                                                                                           \
  ObjectType * ObjectInstance = iDumper._pObject;                                                           \
  if (ObjectInstance)                                                                                       \
  {                                                                                                         \
    DumpFunction(CGMOutput, *ObjectInstance);                                                               \
  }                                                                                                         \
  return CGMOutput;                                                                                         \
}

/** @nodoc @nocgmitf */
#define ObjectDumperDeclareAndDefine(ObjectDumper, ObjectType, DumpFunction)                                \
ObjectDumperDeclare(ObjectDumper, ObjectType);                                                              \
ObjectDumperDefine(ObjectDumper, ObjectType, DumpFunction);

#endif

