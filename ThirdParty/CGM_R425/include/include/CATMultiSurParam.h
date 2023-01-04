#ifndef CATMultiSurParam_H
#define CATMultiSurParam_H

//=============================================================================
// CATMultiSurParam:
//   Geometric Object devoted to the position on a CATMultiSurface. This class
//   is a simple overlay of a CATSurParam Object and its main methods.
//
//=============================================================================
// LJL2   Sep. 19 : Creation (basic constructors, getting and setting methods)
//=============================================================================

// Basic Types
#include "CATDataType.h"

// Geometric Objects
class CATSurface;
class CATMultiSurface;
#include "CATSurParam.h"
#include "YP00IMPL.h"

// Mathematics
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathDirection.h"

//=============================================================================

class ExportedByYP00IMPL CATMultiSurParam
{

public:

    // ------------------------------------------------------------------------
    // Constructors
    // ------------------------------------------------------------------------

    CATMultiSurParam();

    CATMultiSurParam(double                  iParamU,
                     double                  iParamV,
                     const CATMultiSurface * iReferenceMultiSurface);

    CATMultiSurParam(const CATMultiSurParam & iMultiSurParamToCopy);

    // ------------------------------------------------------------------------
    // Destructor
    // ------------------------------------------------------------------------

    ~CATMultiSurParam();

    // ------------------------------------------------------------------------
    // Setting Methods
    // ------------------------------------------------------------------------

    void SetMultiSurParam(const CATMultiSurParam & iMultiSurParam);

    void SetParam(double iParamU,
                  double iParamV);

    void SetParam(      CATLONG32     iIndexU,
                        CATLONG32     iIndexV,
                  const CATSurParam & iLocalParam);

	void SetReference(const CATMultiSurface * iReferenceMultiSurface);

    // ------------------------------------------------------------------------
    // Getting Methods
    // ------------------------------------------------------------------------

    void GetParam(double & oParamU,
                  double & oParamV) const;

	void GetParam(double    & oSurParamU,
		          double    & oSurParamV,
		          CATLONG32 & oIndexU,
		          CATLONG32 & oIndexV) const;

    void GetParam(      CATLONG32   & oIndexU,
                        CATLONG32   & oIndexV,
                        CATSurParam & oLocalParam) const;

    void GetIndex(CATLONG32 & oIndexU,
                  CATLONG32 & oIndexV) const;

    const CATMultiSurface * GetReference() const;

private:

    // ------------------------------------------------------------------------
    // Internal Methods
    // ------------------------------------------------------------------------

    double GetSurParamU() const;

    double GetSurParamV() const;

    CATSurface * GetSurface() const;

    // ------------------------------------------------------------------------
    // Internal Datas
    // ------------------------------------------------------------------------

          CATSurParam       _UV;
          CATLONG32         _IndexU;
          CATLONG32         _IndexV;
    const CATMultiSurface * _MultiSurface;
};

//=============================================================================

#endif
