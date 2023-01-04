/* -*-C++-*- */
#ifndef CATTrdSet_H
#define CATTrdSet_H
// COPYRIGHT DASSAULT SYSTEMES 2014

//===================================================================
//===================================================================
//
// CATTrdSet: Set of Trihedrons dedicated to mapping of exact BRep
//
//===================================================================
// NB: Canonic CATTrdSet figuring cylindrical holes own only 2 Trihedrons
//===================================================================
// April 2014    Creation                         R. Rorato
//===================================================================

#include "CATMathematics.h"
#include "CATTrdRep.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATTrd.h"

class ExportedByCATMathematics CATTrdSet : public CATTrdRep
{
public:

  //------------------------------------------------------------------------------
  // Object Management
  //------------------------------------------------------------------------------
  CATTrdSet(const unsigned char iSurfaceType);
  CATTrdSet(const CATTrdSet& iToCopy); 
  CATTrdSet(unsigned char* iStream, int& ioStreamPosition, CATTrdDic* iDic, const unsigned char iStreamLevel);
  virtual ~CATTrdSet();
  CATCGMNewClassArrayDeclare;        // Pool allocation
  CATTrdSet* GetAsTrdSet();

  //------------------------------------------------------------------------------
  // Put this into stream
  //------------------------------------------------------------------------------
  void Stream(unsigned char*& oStream, int& ioStreamPosition, const int iStreamLevel);
  int GetStreamSize(const int iStreamLevel);

  //------------------------------------------------------------------------------
  // Compare methods
  //------------------------------------------------------------------------------
  CATBoolean IsIsometric(const CATMathTransformation& iTransfo, CATTrdRep& iTrdRep, const double& iTolForAngleTest, const double& iTolForSquareLengthTest, CATTrdChk* iChecker, const CATTrd::SimilarityType iSimilarityType, const CATBoolean iOnlyWithInvariant, CATLISTV(CATMathTransformation)& oTransfoFromThisToiTrdSet);
  CATBoolean IsEqual(const CATMathTransformation& iTransfo, CATTrdRep& iTrdRep, const double& iTolForAngleTest, const double& iTolForSquareLengthTest, CATTrdRep* ithisAdjRep = NULL, CATTrdRep* iAdjRep = NULL);

  //------------------------------------------------------------------------------
  // Access to Trihedrons, Size & Center
  //------------------------------------------------------------------------------
  virtual ListPOfCATTrd& Trd();
  virtual double GetSize();
  void SetSize(const double iSize);

  //------------------------------------------------------------------------------
  // Anosotropic data
  //------------------------------------------------------------------------------
  CATTrd* GetAnisotropy();
  void InactivateAnisotropy();

  //------------------------------------------------------------------------------
  // Debug methods
  //------------------------------------------------------------------------------
  void Dump(ostream& oStream) const;
  void SetTag(const CATULONG32 iTag);
  CATULONG32 GetTag();

  //==============================================================================
  // Private section
  //==============================================================================
private:
  void ComputeAnisotropy();
  CATTrdSet& operator=(const CATTrdSet&);  
  CATBoolean IsACylindricalHole() const;
  static CATBoolean AreCylindricalHoleSimilar(ListPOfCATTrd& iTrds1, const CATMathTransformation& iTransfo, ListPOfCATTrd& iTrds2, const double& iTolForLengthTest);

  struct CATAnisotropy
  {
    CATTrd                     _Trd;        // Inertia main axis
    double                     _Coef[2];    // I & J relative moments
    CATAnisotropy(const CATMathPoint& iOrigin, const CATMathVector& iI, const CATMathVector& iJ, const CATMathVector& iK, const double iCI, const double iCJ): _Trd(iOrigin, iI, iJ, iK, CATTrd::AnisotropyVertex)
    { 
      _Coef[0] = iCI;
      _Coef[1] = iCJ; 
    }
    CATAnisotropy(const CATAnisotropy& iToCopy): _Trd(iToCopy._Trd)
    { 
      _Coef[0] = iToCopy._Coef[0];
      _Coef[1] = iToCopy._Coef[1]; 
    }
  };

  //------------------------------------------------------------------------------
  // Data
  //------------------------------------------------------------------------------
  CATULONG32     _Tag;
  double         _Size;
  unsigned char  _SurfaceType;
  CATAnisotropy* _Anisotropy;
  CATBoolean     _AnisotropyStatus; // -1: inactivated, 0: not computed yet, 1: computed
  ListPOfCATTrd  _Trds;
};

#endif
