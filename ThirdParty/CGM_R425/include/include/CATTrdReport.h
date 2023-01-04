/* -*-C++-*- */
#ifndef CATTrdReport_H
#define CATTrdReport_H
// COPYRIGHT DASSAULT SYSTEMES 2014

//===================================================================
//===================================================================
//
// CATTrdReport: information of Trd mapping
//
//===================================================================
//===================================================================
// Oct 2014    Creation                         R. Rorato
//===================================================================
#include "CATMathematics.h"
#include "CATBoolean.h"
#include "ListPOfCATTrdRep.h"
#include "ListPOfCATTrdReport.h"
#include "CATListOfInt.h"
#include "CATListOfULONG32.h"
#include "CATCGMVirtual.h"
#include "CATMathTransformation.h"
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATCGMProgressBar;

class ExportedByCATMathematics CATTrdReport : public CATCGMVirtual
{
public:
  //------------------------------------------------------------------------------
  CATTrdReport();
  void GetMatchedFacesCount(int& oMatchedFacesCount1, int& oFacesCount1, int& oMatchedFacesCount2, int& oFacesCount2); // Only fully mapped reps
  void GetMatchedFacesCount(int &oFullyMappedCount1, int &oFullyMappedCount2, int &oPartiallyMappedCount1, int &oPartiallyMappedCount2, int &oNotMapped1, int &oNotMapped2) const;
  CATBoolean IsFullyIsometric();
  double GetSimilarity(); // oMatchedFacesCount / max (oFacesCount1, oFacesCount2)
  void GetTransformation(CATMathTransformation& oTransfoFrom1To2);
  void GetAlternatives(ListPOfCATTrdReport& oAlternatives); // Caller becomes oAlternatives owner
  virtual ~CATTrdReport();

  HRESULT GetFullyMappedRep(ListPOfCATTrdRep &oMappedRep1, ListPOfCATTrdRep &oMappedRep2);
  HRESULT GetPartiallyMappedRep(ListPOfCATTrdRep &oMappedRep1, ListPOfCATTrdRep &oMappedRep2);
  HRESULT GetNotMappedRep(ListPOfCATTrdRep &oNotMappedRep1, ListPOfCATTrdRep &oNotMappedRep2);

  //------------------------------------------------------------------------------
  // CGM private. Do not use
  //------------------------------------------------------------------------------
  void Set(const CATMathTransformation& iTransfo, const double iSimilarity, ListPOfCATTrdRep& iRep1, ListPOfCATTrdRep& iRep2, CATListOfInt& iRepMap1, CATListOfInt& iRepMap2);
  void GetUnMatchedReps(ListPOfCATTrdRep oReps[2]);
  static int Compare2Values(CATTrdReport* iReport1, CATTrdReport* iReport2);
  virtual CATTrdReport* Clone() const;
  void Append(CATTrdReport*& ioAlternative); // this becomes ioAlternative owner
  static void GetMappedIndexes(ListPOfCATTrdReport& iReports, const int iRepIndex0, CATListOfInt& oMappedIndexes); // Only fully mapped reps
  virtual HRESULT MatchAdjacentReps(CATSoftwareConfiguration &iConfig, const double iTolForAngleTest, const double iTolForSquareLengthTest);
  virtual void CreateSimilarBodies(CATSoftwareConfiguration* iConfig, CATGeoFactory* iFactory);
  virtual void SetProgress(const double iValue, const double iTotalValue);
  void SetProgressBar(CATCGMProgressBar* iProgressBar);
  CATCGMProgressBar* GetProgressBar() const;
  void Dump(ostream* iStream=0L) const;
  void SetRepTag(); // For CGMReplay result mapping check
  CATTrdReport(const unsigned char* iUCharArray, int& ioPosition);
  void Stream(unsigned char*& oUCharArray, int& oLength) const; // oUCharArray to be deleted afterward
  void Write(unsigned char* oUCharArray, int& ioPosition) const;
  static int Compare(CATTrdReport& iReport1, CATTrdReport& iReport2, const double iDistanceTol, const double iAngleTol, ostream* iStream = NULL);
  CATTrdReport(const CATTrdReport& iToCopy); 
  CATTrdReport& operator=(const CATTrdReport&);

protected:
  const ListPOfCATTrdRep& GetRep(const int iIndex) const; // iIndex = 0 or 1
  const CATListOfInt& GetRepMap(const int iIndex) const; // iIndex = 0 or 1
  HRESULT SetMatching(const int iIndex0, const int iIndex1, const CATBoolean iFullMatching);

private:
  // FullyMapped1 and FullyMapped2 are synchronized by index
  // PartiallyMapped1 and PartiallyMapped2 are synchronized by index
  HRESULT GetMappedRep(ListPOfCATTrdRep &oFullyMapped1, ListPOfCATTrdRep &oFullyMapped2,
                       ListPOfCATTrdRep &oPartiallyMapped1, ListPOfCATTrdRep &oPartiallyMapped2,
                       ListPOfCATTrdRep &oNotMapped1, ListPOfCATTrdRep &oNotMapped2);

  //------------------------------------------------------------------------------
  int GetStreamLength() const;
  void GetDeviation(double& oDeviation, double& oSize);
  //------------------------------------------------------------------------------
  // Output
  //------------------------------------------------------------------------------
  ListPOfCATTrdRep      _Rep[2];
  CATListOfInt          _RepMap[2]; // 0: not mapped, >0 fully mapped, <0 Localy mapped
  CATListOfULONG32      _RepTag[2]; // Only used for CGMReplay output mapping
  CATMathTransformation _Transfo;
  double                _Similarity;
  ListPOfCATTrdReport   _Alternatives;
  CATCGMProgressBar*    _ProgressBar;
  //------------------------------------------------------------------------------
};

#endif
