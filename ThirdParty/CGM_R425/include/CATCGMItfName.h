#ifndef CATCGMItfName_H
#define CATCGMItfName_H
//---------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2002
//---------------------------------------------------
#include "CATMathematics.h"
#include "CATCGMNewArray.h"
#include "CATUnicodeString.h" 
#include "CATDataType.h"
#include "CATCGMHashTable.h"
#include "IUnknown.h"
#include "CATCGAMeasureGMData.h"


class CATechSetOfChar;

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

typedef unsigned int CATCGMItfNameFLAGS;

#define CATCGMItfNameFLAGS_Feature                    0x0001
#define CATCGMItfNameFLAGS_WithoutCarriageReturn      0x0002
#define CATCGMItfNameFLAGS_WithLevel                  0x0004
#define CATCGMItfNameFLAGS_WithCommaHeader            0x0008

#define CATCGMItfNameFLAGS_WithoutFeatureScopeStatus  0x0010
#define CATCGMItfNameFLAGS_WithGeometricalWorkflow    0x0020
#define CATCGMItfNameFLAGS_TypeCollector              0x0040

typedef struct _CATCGMItfIdentifier
{
  CATULONG32    _Tag;
  CATULONG32    _IdNumber;
  CATBoolean    _HasBeenLoaded;

  CATUnicodeString  _ObjectName;

  _CATCGMItfIdentifier()  : _Tag(0), _IdNumber(0), _HasBeenLoaded(FALSE) 
  {}

} CATCGMItfIdentifier;


class CATICGMObject;


class  ExportedByCATMathematics CATCGMItfName
{
public:
  CATCGMItfName( CATCGMItfIdentifier & iGMObject, const char *Name );
  ~CATCGMItfName();

  CATCGMNewClassArrayDeclare;  
  
  void SetTransient( IUnknown * iTransient );
  void SetObject( CATCGMItfIdentifier & iGMObject );

         void DumpSetOfChar(CATechSetOfChar &ioDump,  CATCGMItfNameFLAGS iFlags, int numDashBoard );

         void Dump(ostream &ioDump,          CATCGMItfNameFLAGS iFlags);
  static void DumpBetween(ostream &ioDump,   CATCGMItfNameFLAGS iFlags, short i_0Hea_1Name );

  CATUnicodeString   _Type;

  CATUnicodeString   _ObjectName;
  CATULONG32         _Tag;
  CATULONG32         _IdNumber;

  CATUnicodeString       _Name;
  
  CATUnicodeString   _ExtractName;
  CATUnicodeString   _ExtractType;


  IUnknown       * const _Transient;
  CATULONG32             _Diezele;
  CATULONGPTR            _ContainerIdSession;

  CATULONG32        _ParentDiezele;
  CATULONG32        _BrpEle;

  CATULONG32        _WorkingTag;


  struct CGMFlags
  {
    short          CfgLevel;
    short          ResultLevel;

    unsigned int  ScopeWithoutFeature        :  1;
    unsigned int  FeatureNotAggregated       :  1;
    unsigned int  FeatureNotToDate           :  1;
    unsigned int  ScopeNotActive             :  1;
    unsigned int	datum                      :  1;
    unsigned int	rolled                     :  1;
    unsigned int  FeatureAnalysedAsBestSoFar :  1;
    unsigned int  FromScopeAnalysis          :  1;

    unsigned int	noNeedToSave               :  1;
    unsigned int	smart                      :  1;
    unsigned int	unsmart                    :  1;
    unsigned int	GMHasBeenLoaded            :  1;
    unsigned int	isValid                    :  4;

    unsigned int  IsTyped                    :  1;
    unsigned int  RFU                        : 13;
  }
  Flags;

  // Working Results (by Class)
  CATULONG32    _NbUpdated;
  CATULONG32    _NbIsUpToDate;

  CATULONG32    _NumberOfWorkingResult;

  void AddCumulatedDimOfWorkingResult(CATLONG32  Dim);

  CATLONG32     _CumulatedDimOfWorkingResult;


  CATCGAMeasureGMData   _GMData;


private :


         CATULONG32    _History;
  static CATULONG32    _HistoryCounter;

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGMItfName(const CATCGMItfName &iCopy);
  CATCGMItfName& operator=(const CATCGMItfName &iCopy);

};

extern "C" { typedef void CATCGMItfNameAutoFilling(CATCGMItfName * ioItfName); }  
class CATISpecObject_var;
extern "C" { typedef CATBoolean CATCGMItfNameAutoFillingFeature(CATISpecObject_var & feat, CATCGMItfName * & oItfName); }  
extern "C" { typedef void CATCGMItfNameExtract(const int iBeforeOneShotAfter); }  
extern "C" { typedef void CATCGAMeasurePlayBacking(const int iStartOrEnd); }  

//---------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2002
//---------------------------------------------------
typedef struct _CATCGMItfInputData
{
  CATULONG32          _IdNumber;
  CATUnicodeString    _InputData;
} 
CATCGMItfInputData;   

class   ExportedByCATMathematics  CATCGMItfNames  : protected  CATCGMHashTable
{
public: 
  virtual ~CATCGMItfNames();

  CATCGMNewClassArrayDeclare;  

  int             Insert(CATCGMItfName* ipCGMObject);
  CATCGMItfName*  Locate(CATCGMItfName* ipCGMObject) const;

  int             Remove(CATCGMItfName* ipCGMObject);
  CATCGMItfName*  Next(int& ioNumBucket, int& ioPos) const;

  int             Size() const;
  CATCGMItfName*  Get(int iPos) const;

  CATCGMItfInputData _Origin;

protected:
 
  CATCGMItfNames( const CATCGMItfInputData & iOrigin, PFHASHKEYFUNCTION ipHashKeyFunction , PFCOMPAREFUNCTION	ipCompareFunction, int iEstimatedSize = 0);

private :


         CATULONG32    _History;
  static CATULONG32    _HistoryCounter;

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGMItfNames(const CATCGMItfNames &iCopy);
  CATCGMItfNames& operator=(const CATCGMItfNames &iCopy);

};


/**
*  Dictionnary of CATCGMItfNameByTag ... ByTag.
*/

class   ExportedByCATMathematics  CATCGMItfNameByTag  : public  CATCGMItfNames
{
public:
   CATCGMItfNameByTag(const CATCGMItfInputData & iOrigin, int iEstimatedSize = 0);
  ~CATCGMItfNameByTag();

  CATCGMNewClassArrayDeclare;
};



/**
*  Dictionnary of CATCGMItfNameByDiezele ... ByDiezele.
*/

class   ExportedByCATMathematics  CATCGMItfNameByDiezele  : public  CATCGMItfNames
{
public:
   CATCGMItfNameByDiezele(const CATCGMItfInputData & iOrigin, int iEstimatedSize = 0);
  ~CATCGMItfNameByDiezele();

  CATCGMNewClassArrayDeclare;
};


/**
*  Dictionnary of CATCGMItfNameByType ...  .
*/

class   ExportedByCATMathematics  CATCGMItfNameByType  : public  CATCGMItfNames
{
public:
   CATCGMItfNameByType(const CATCGMItfInputData & iOrigin, int iEstimatedSize = 0);
  ~CATCGMItfNameByType();

  CATCGMNewClassArrayDeclare;
};

#endif
