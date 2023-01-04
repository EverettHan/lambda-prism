/* -*-C++-*- */
#ifndef CATTrdOptions_H
#define CATTrdOptions_H
// COPYRIGHT DASSAULT SYSTEMES 2014

//===================================================================
//===================================================================
//
// CATTrdOptions: options for Trd mapping
//
//===================================================================
//===================================================================
// Jan 2054    Creation                         R. Rorato
//===================================================================
#include "CATMathematics.h"
#include "CATBoolean.h"
#include "CATCGMVirtual.h"

class CATTrdOptions;

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;// to suppress
#endif

extern ExportedByCATMathematics const CATTrdOptions CATTrdOptionsDefault;
extern ExportedByCATMathematics const CATTrdOptions CATTrdOptionsOnlyIdentity;
extern ExportedByCATMathematics const CATTrdOptions CATTrdOptionsOnlyTranslation;
extern ExportedByCATMathematics const CATTrdOptions CATTrdOptionsOnlyIsometry;
extern ExportedByCATMathematics const CATTrdOptions CATTrdOptionsOnlyPositiveSimilarity;
extern ExportedByCATMathematics const CATTrdOptions CATTrdOptionsOnlyNegativeSimilarity;
extern ExportedByCATMathematics const CATTrdOptions CATTrdOptionsOnlyPositiveIsometry;
extern ExportedByCATMathematics const CATTrdOptions CATTrdOptionsOnlyNegativeIsometry;
extern ExportedByCATMathematics const CATTrdOptions CATTrdOptionsOnlyMirror;

class ExportedByCATMathematics CATTrdOptions : public CATCGMVirtual
{
public:
  //------------------------------------------------------------------------------
  CATTrdOptions(); // Default options
  CATTrdOptions(const CATBoolean iOnlyIsometry, const CATBoolean iOnlyPositiveSimilarity, const CATBoolean iOnlyNegativeSimilarity, const CATBoolean iBestSimilarity, const CATBoolean iFullGeometryCheck, const CATBoolean iPartialSearch, const CATBoolean iOnlyWithInvariant, const CATBoolean iOnlyTranslation, const CATBoolean iTolerantMode);
  virtual ~CATTrdOptions();

  //------------------------------------------------------------------------------
  // Options. Better use predefined CATTrdOptions, see below.
  //------------------------------------------------------------------------------
  void SetBestSimilarity(const CATBoolean iBestSimilariry = TRUE);
  CATBoolean GetBestSimilarity() const;
  void SetOnlyIsometry(const CATBoolean iOnlyIsometry = TRUE);
  CATBoolean GetOnlyIsometry() const;
  void SetOnlyTranslation(const CATBoolean iOnlyTranslation = TRUE);
  CATBoolean GetOnlyTranslation() const;
  void SetOnlyPositiveSimilarity(const CATBoolean iOnlyPositiveSimilarity = TRUE);
  CATBoolean GetOnlyPositiveSimilarity() const;
  void SetOnlyNegativeSimilarity(const CATBoolean iOnlyNegativeSimilarity = TRUE);
  CATBoolean GetOnlyNegativeSimilarity() const;
  //void SetOnlyWithInvariant(const CATBoolean iOnlyWithInvariant); // Not fully supported yet
  CATBoolean GetOnlyWithInvariant() const ;
  void SetFullGeometryCheck(const CATBoolean iFullGeometryCheck = TRUE);
  CATBoolean GetFullGeometryCheck() const;
  void SetPartialSearch(const CATBoolean iPartialSearch = TRUE);
  CATBoolean GetPartialSearch() const;
  void SetTolerantMode(const CATBoolean iTolerantMode = TRUE);
  CATBoolean GetTolerantMode() const;
 
  //------------------------------------------------------------------------------
  // Debug
  //------------------------------------------------------------------------------
  void Dump(ostream* iStream=0L) const;

  //------------------------------------------------------------------------------
  // Do not use
  //------------------------------------------------------------------------------
  CATTrdOptions(const unsigned char* iUCharArray, int& ioPosition, const CATBoolean iOldFormat = FALSE);
  void Stream(unsigned char*& oUCharArray, int& oLength, const CATBoolean iOldFormat = FALSE) const;

protected:
  //------------------------------------------------------------------------------
  // Private
  //------------------------------------------------------------------------------
private:
  CATBoolean _OnlyIsometry;                   // Default: FALSE
  CATBoolean _OnlyTranslation;                // Default: FALSE
  CATBoolean _OnlyPositiveSimilarity;         // Default: FALSE
  CATBoolean _OnlyNegativeSimilarity;         // Default: FALSE
  CATBoolean _OnlyWithInvariant;              // Default: FALSE
  CATBoolean _BestSimilarity;                 // Default: TRUE
  CATBoolean _FullGeometryCheck;              // Default: TRUE
  CATBoolean _PartialSearch;                  // Default: FALSE
  CATBoolean _TolerantMode;                   // Default: FALSE
  //------------------------------------------------------------------------------
};
#endif
