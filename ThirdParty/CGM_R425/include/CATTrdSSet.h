/* -*-C++-*- */
#ifndef CATTrdSSet_H
#define CATTrdSSet_H
// COPYRIGHT DASSAULT SYSTEMES 2014

//===================================================================
//===================================================================
//
// CATTrdSSet: Set of Set of Trihedrons dedicated to mapping of exact BRep
//
//===================================================================
//===================================================================
// April 2014    Creation                         R. Rorato
//===================================================================

#include "CATMathematics.h"
#include "CATTrd.h"
#include "CATTrdOptions.h"
#include "CATCGMVirtual.h"
#include "CATCGMNewArray.h"
#include "CATSysErrorDef.h"
#include "ListPOfCATTrdSet.h"
#include <iosfwd.h>

class CATMathTransformation;
class CATTrdOptions;
class CATTrdReport;
class CATTrdDic;
class CATSoftwareConfiguration;

class ExportedByCATMathematics CATTrdSSet : public CATCGMVirtual
{
public:

  //------------------------------------------------------------------------------
  // Object Management
  //------------------------------------------------------------------------------
  CATTrdSSet(unsigned char*& ioStream, const CATBoolean iDeleteStream = TRUE); //  if iDeleteStream then ioStream is deleted and ioStream is set to null
  CATTrdSSet(char* ioStream); // deprecated
  CATTrdSSet(const double iScale, const ListPOfCATTrdSet& iTrdSets, CATTrdDic*& ioDic);
  virtual ~CATTrdSSet();
  CATCGMNewClassArrayDeclare;        // Pool allocation

  //------------------------------------------------------------------------------
  // Put this into stream
  //------------------------------------------------------------------------------
  HRESULT Stream(unsigned char*& oStream, int& oStreamLength, const int iCompressionLevel=0);  // 0<=iCompressionLevel<=9
  HRESULT Stream(char*& oStream, int& oStreamLength, const int iCompressionLevel=0);  // deprecated

  //------------------------------------------------------------------------------
  // Compare methods
  //------------------------------------------------------------------------------
  HRESULT IsSimilar(CATSoftwareConfiguration &iConfig, CATTrdSSet& iTrdSSet, const double iRequiredSimilarity, const CATTrdOptions& iOptions, CATTrdReport& oReport);
  
  // Deprecated
  HRESULT IsSimilar(CATTrdSSet& iTrdSSet, const double iRequiredSimilarity, CATTrdReport& oReport);
  HRESULT IsSimilar(CATTrdSSet& iTrdSSet, const double iRequiredSimilarity, const CATTrdOptions& iOptions, CATTrdReport& oReport);

  //------------------------------------------------------------------------------
  // Debug methods
  //------------------------------------------------------------------------------
  void Dump(ostream* oStream) const;

  //==============================================================================
  // Private section
  //==============================================================================
private:
  CATTrdSSet(const CATTrdSSet& iToCopy); 
  CATTrdSSet& operator=(const CATTrdSSet&);  

  //------------------------------------------------------------------------------
  // Data
  //------------------------------------------------------------------------------
private:
  ListPOfCATTrdSet _TrdSets;
  double           _Scale;
  CATTrdDic*       _Dic;
};

#endif
