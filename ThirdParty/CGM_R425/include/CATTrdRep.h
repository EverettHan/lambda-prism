/* -*-C++-*- */
#ifndef CATTrdRep_H
#define CATTrdRep_H
// COPYRIGHT DASSAULT SYSTEMES 2014

//===================================================================
//===================================================================
//
// CATTrdRep: Set of Trihedrons dedicated to mapping of exact BRep
//
//===================================================================
//===================================================================
// June 2014    Creation                         R. Rorato
//===================================================================
#include "CATErrorDef.h"
#include "CATMathematics.h"
#include "CATCGMVirtual.h"
#include "CATBoolean.h"
#include "CATTrd.h"
#include "ListPOfCATTrdRep.h"
#include "ListPOfCATTrdReport.h"
#include "CATLISTP_CATMathTransformation.h"
#include "CATListOfInt.h"
class CATTrdChk;
class CATTrdSet;
class CATTrdOptions;
class CATTrdReport;
class CATTrdRepMultiRun;
class CATPrRep;
class CATMathTransformation;
class CATMathPoint;
class CATSoftwareConfiguration;

class ExportedByCATMathematics CATTrdRep : public CATCGMVirtual
{
public:
  //------------------------------------------------------------------------------
  // Compare methods
  //------------------------------------------------------------------------------
  static HRESULT AreIsometric(CATSoftwareConfiguration &iConfig, ListPOfCATTrdRep& iReps1, ListPOfCATTrdRep& iReps2, const double iTolForAngleTest, const double iTolForSquareLengthTest,
                              const double iRequiredSimilarity, const CATTrdOptions& iOptions, CATTrdReport& ioReport);
  //------------------------------------------------------------------------------
  // Safe Cast methods
  //------------------------------------------------------------------------------
  virtual CATTrdSet* GetAsTrdSet();
  virtual CATPrRep*  GetAsPrRep();
  //------------------------------------------------------------------------------
  // Methods to be provided
  //------------------------------------------------------------------------------
  virtual CATBoolean IsIsometric(const CATMathTransformation& iTransfo, CATTrdRep& iTrdRep, 
                                 const double& iTolForAngleTest, const double& iTolForSquareLengthTest, 
                                 CATTrdChk* iChecker, const CATTrd::SimilarityType iSimilarityType, const CATBoolean iOnlyNoTranslation, 
                                 CATLISTV(CATMathTransformation)& oTransfoFromThisToiTrdRep) = 0;
  virtual CATBoolean IsEqual    (const CATMathTransformation& iTransfo, CATTrdRep& iTrdRep, 
                                 const double& iTolForAngleTest, const double& iTolForSquareLengthTest, 
                                 CATTrdRep* ithisAdjRep = NULL, CATTrdRep* iAdjRep = NULL) = 0;
  virtual double GetSize() = 0;
  virtual ListPOfCATTrd& Trd() = 0;
  virtual CATULONG32 GetTag() = 0;
  virtual void PutColor(const int iR, const int iG, const int iB);

private:
  //------------------------------------------------------------------------------
  // Internal Utilities
  //------------------------------------------------------------------------------
  static HRESULT AreIsometric(ListPOfCATTrdRep& iReps0, const double iS0, ListPOfCATTrdRep& iReps1, const double iS1, 
                              const CATTrd::SimilarityType iSimilarityType, const CATBoolean iOnlyNoTranslation, const double iTolForAngleTest, const double iTolForSquareLengthTest, 
                              const double iRequiredSimilarity, CATTrdRepMultiRun& ioMultiRun, CATTrdReport& oReport);

  static void SortSolutions(ListPOfCATTrdReport& ioReports, const double iTolForAngleTest, const double iTolForLengthTest);

  static CATBoolean Check(CATLISTV(CATMathTransformation)& iTransfo, CATLISTP(CATMathTransformation) iTransfoList[], const double iDistanceTol, const double iAngleTol, const CATTrd::SimilarityType iSimilarityType);

  static int GetPackage(const CATMathTransformation& iTransfo);
};

#endif
