//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//==============================================================================================================
// CATPolyError : Main class handling errors in polyhedral modeler
//                to be derived for dedicated use 

//                An "error" object is basically a stack of error messages that is 
//                mapped onto the call stack of the error, each message being associated
//                with additional information such as the file name and line of the method involved,
//                a severity code (0 to 2), hresult, and an error number
//==============================================================================================================
// Creation : CHU  july 2003
//==============================================================================================================

#ifndef CATPolyError_H
#define CATPolyError_H

#include "PolyhedralUtilities.h"     // ExportedBy definition
#include "CATDataType.h"
#include "CATErrorDef.h"   // HRESULT definition

#define ErrCatch(err,comm,fil,linenum) CATPolyError::Filter( err , S_OK , -1, 0, comm , fil , linenum)
#define ERRDUMP(obj) CATPolyDumpablePendingForExtensiveDump(obj)
#define CGMOUT CATPolyError::DumpInCgmout
#define CGMERR CATPolyError::DumpInCgmerr

class CATPolyDumpable;
class CATPolyDumpablePendingForExtensiveDump;
class CATPolyPendingForDump;
class CATCGMOutput;

class ExportedByPolyhedralUtilities CATPolyError
{

public :

  static CATPolyError _PolyAllocationError;

  enum DumpDirective { DumpInCgmout, DumpInCgmerr };

  // Life cycle
  CATPolyError(HRESULT ihr = E_FAIL,
               int iSeverity = 2,
               int iErrorNumber = 0,
               char * iComment = 0,
               char * iFileName = 0, int iLineNumber = 0,
               int iDumpToCgmout = 0);

  virtual ~CATPolyError();

  // HRESULT and severity management (default implementation yields hresult and max severity contained in data)
  // Severity scale:  0=warning, 1=processing error, 2=fatal error (e.g. alloc. error)
  virtual HRESULT GetHRESULT() const; 
  virtual int GetSeverity() const; 

  // Delete the error (the pointer ioError becomes null in output) and raise a HRESULT
  static HRESULT FlushAndConvertToHRESULT(CATPolyError *& ioError);

  // Default implementation of GetMessage() gives the highest message stacked, same for GetErrorNumber
  // char * returned by GetMessage() must not be deleted (owned by error)
  virtual const char * GetMessage() const;
  virtual int GetErrorNumber() const;

  // Flush() dumps the error onto the given CATCGMOutput if any, and then deletes the error
  // (the pointer ioError becomes null in output)
  static void Flush(CATPolyError *& ioError, CATCGMOutput * iStream);

  // Filter() flushes the error (onto cgmout, see above) if its severity (taking iNewSeverity into account) is
  // inferior or equal to iMaxSeverityForFlushingError. Otherwise (higher severity) the error is
  // fed with the new data (or created if ioError was null in input), and returned in output
  // If severity, comment and file name are all equal to default, then ioError is just returned 
  // untouched in output, without any information added (then it should not be null in input)
  // Use macro define ErrCatch for compacity (does not allow re-assigning severity or hresult)
  static CATPolyError * Filter(CATPolyError *& ioError,
                               HRESULT iLocalHR = S_OK,
                               int iNewSeverity = -1,
                               int iNewErrorNumber = 0,
                               char * iNewComment = 0,
                               char * iFileName = 0, int iLineNumber = 0,
                               int iMaxSeverityForFlushingError = 0,
                               int iDumpToCgmout = 0);

  // Add information to last created sub-error, using a dedicated dump method
  friend ExportedByPolyhedralUtilities CATPolyError & operator << ( CATPolyError& e, const char * iText);
  friend ExportedByPolyhedralUtilities CATPolyError & operator << ( CATPolyError& e, const int iValue);
// #ifndef PLATEFORME_DS64
//   friend ExportedByPolyhedralUtilities CATPolyError & operator << ( CATPolyError& e, const CATLONG32 iValue);
// #endif
  friend ExportedByPolyhedralUtilities CATPolyError & operator << ( CATPolyError& e, const float iValue);
  friend ExportedByPolyhedralUtilities CATPolyError & operator << ( CATPolyError& e, const double iValue);

  friend ExportedByPolyhedralUtilities CATPolyError & operator << ( CATPolyError& e, const CATPolyDumpable * iElt);
  friend ExportedByPolyhedralUtilities CATPolyError & operator << ( CATPolyError& e, const CATPolyDumpablePendingForExtensiveDump & iElt);
  friend ExportedByPolyhedralUtilities CATPolyError & operator << ( CATPolyError& e, const CATPolyPendingForDump & iElt);

  friend ExportedByPolyhedralUtilities CATPolyError & operator << ( CATPolyError& e, const DumpDirective & iDirective);

  // Dump utility
  friend void DumpFileIntoError(CATPolyError& e, char * iDummyFilePath);

  // Initialize _AllocFailed (called once for static object dedicated to alloc. problems)
  inline void SetAllocFailed(int iAllocFailed);

  // Dump
  virtual HRESULT Dump( CATCGMOutput & s) const;
  friend ExportedByPolyhedralUtilities CATCGMOutput & operator << ( CATCGMOutput& s, const CATPolyError & iObj);

protected:

  struct SubError {
    HRESULT _hr;       // ignored if =S_OK or if _Sev=-1 (then next -deeper- sub-error is watched)
    int     _Sev;      // -1,0,1 or 2 (-1=cf deeper sub-error, 0=warning, 1=error, 2=fatal)
    int     _ErrNum;   // any number (e.g. give valuable information for debug)
    char *  _Comment;  // may also be ommitted (deeper sub-error comment still relevant)
    char  * _FileName; // may be ommitted
    int     _Line;     // relevant if not zero, may be ommitted

    SubError();
    ~SubError();
    void Dump(CATCGMOutput & s);
    SubError & operator= (const SubError& iRight);
  };

  // Append a sub error into the list
  void AppendSubError(int iSeverity, int iErrorNumber, char * iComment,
    char * iFileName, int iLineNumber, HRESULT iLocalHR);

  // Data

  HRESULT _FinalHR;  // should be the highest (as opposed to deepest) hresult not null with severity>=0 in stack
  int     _MaxSev;   // should be the max severity of stacked sub-errors

  int     _AllocFailed; // if =1, all other data are to be ignored

  SubError * _ErrStack; // [0] = highest,... [_ErrStackSize] = deepest (method in which the error was raised)
  int        _ErrStackSize;
  int        _ErrStackMaxSize;
};

inline void CATPolyError::SetAllocFailed(int iAllocFailed) {
  _AllocFailed = iAllocFailed; }

// Following classes are designed to be used as right-values of operator <<
// with a CATPolyError object as left value, in order to add a formatted dump
// to the last sub-error.

// A constructor of these classes is invoked between two <<, this invokation is
// generally compacted by using a macro (see #define in top of this file),
// A temporary object will then be generated by the compiler, and operator<<
// being called with this object as rvalue, will invoke a specific overload
// (see list of friend methods in CATPolyError) that will, in its turn, invoke
// a formatted dump method
class CATPolyDumpablePendingForExtensiveDump {
public:
  CATPolyDumpablePendingForExtensiveDump(CATPolyDumpable * iObj);
  CATPolyDumpable * _Obj;
};

// The most generic implementation of the mechanism mentioned above is done by the
// following class where the formatted dump method itself is a pointer to a function
// that will be initialized in each sub-class (whose definitions follow). All dump
// functions take a CATCGMOutput, and not a char* (as required by comments in sub-errors),
// then we will use a temporary file and create a CATCGMOutput plugged onto this file,
// and put the result of the dump in this temporary file at first, then create an
// "ifstream" to collect all lines written in the file and append these lines as char*
// to the last sub-error (this is done in the .cpp, see the implementation of operator<<
// for CATPolyPendingForDump right value)
class CATPolyPendingForDump {
public:
  CATPolyPendingForDump(void * iData, void (*iDumpMethod)(CATCGMOutput&,void *));
  void * _DataToDump;
  void (*_DumpMethod)(CATCGMOutput & s, void * iData);
};

#endif
