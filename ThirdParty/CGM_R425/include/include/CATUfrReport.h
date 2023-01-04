// COPYRIGHT DASSAULT SYSTEMES 2017, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : RR 
// Result description of BodyAnalyzer::SearchFeatures
//
//=============================================================================
// Creation RR feb 2017
//=============================================================================
#ifndef CATUfrReport_H
#define CATUfrReport_H

#include "ListPOfListPOfCATDeclarativeManifold.h"
#include "ListPOfListPOfListPOfCATDeclarativeManifold.h"
#include "CATGMOperatorsInterfaces.h"
#include "ListPOfCATCell.h"
#include "CATCGMVirtual.h"
#include "CATCGMNewArray.h"
#include "CATBoolean.h"

class CATMathStream;
class CATGeoFactory;

class ExportedByCATGMOperatorsInterfaces CATUfrReport : public CATCGMVirtual
{
public:

  // Constructor
  CATUfrReport();
  CATCGMNewClassArrayDeclare;        // Pool allocation

  CATUfrReport(const CATUfrReport& iToCopy); 

  // Destructor
  virtual ~CATUfrReport();

  // Number of features
  int GetFeatureCount() const;

  // Number of instances of a Feature (iFeatureIndex>0)
  int GetInstanceCount(const int iFeatureIndex) const;

  // List of Cells of an instance of a feature (iInstanceIndex>0: instances, iInstanceIndex=0: feature)
  void GetRep(const int iFeatureIndex, const int iInstanceIndex, ListPOfCATCell& oCells) const;

  // List of DeclarativeManifold of an instance of a feature (iInstanceIndex>0: instances, iInstanceIndex=0: feature)
  ListPOfCATDeclarativeManifold GetRep(const int iFeatureIndex, const int iInstanceIndex) const;
  void GetRep(const int iFeatureIndex, const int iInstanceIndex, ListPOfCATDeclarativeManifold& oDMs) const;

  // List of DeclarativeManifold of an instance of a feature grouped to map the declarative manifolds of the pattern
  // if oMappedDMs is set, the mapped DMs in the pattern are also returned
  // !!! the elements of oDMGroups must be CLEANED by the USER !!!
  void GetRep(const int iFeatureIndex, const int iInstanceIndex, ListPOfListPOfCATDeclarativeManifold& oDMGroups, ListPOfCATDeclarativeManifold* oMappedDMs = NULL) const;

  // Dump
  void Dump(CATCGMOutput& ioOS) const;

  // ----------------------------------------------------------------------------
  // CGM Private section
  // ----------------------------------------------------------------------------
  void SetPatternRep(const int iFeatureIndex, const ListPOfCATDeclarativeManifold& iRep);
  
  // Append a List of DeclarativeManifold to an instance of a feature 
  // iMappedRep is the list associating for each DM of iRep a DM of the pattern
  void AppendRep(const int iFeatureIndex, const int iInstanceIndex, const ListPOfCATDeclarativeManifold& iRep, const ListPOfCATDeclarativeManifold& iMappedRep);

  // Reset this
  void Reset(const int iSize);

  // Stream/UnStream
  void Stream(CATMathStream& ioStr) const;
  CATUfrReport(CATMathStream& iStr, CATGeoFactory& iFactory);

  // Compare
  static int Compare(const CATUfrReport& iReport1, const CATUfrReport& iReport2, CATCGMOutput* os = NULL);
  static CATBoolean HaveSameElements(ListPOfCATDeclarativeManifold *iDMs1, ListPOfCATDeclarativeManifold *iDMs2);

  // ----------------------------------------------------------------------------
  // Private section
  // ----------------------------------------------------------------------------
private:
  int _Size; // Number of Features (Size of _Map)
  ListPOfListPOfListPOfCATDeclarativeManifold* _Map;  // _Map[i-1][j]: i Feature, j instance of feature i, returns a ListPOfListPOfCATDeclarativeManifold*
};

#endif
