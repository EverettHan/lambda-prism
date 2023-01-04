/*-*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1997
//==========================================================================
//
// CATFrFNurbsBiparCheck :
//
// This class is done to check if a bipar is degenerated, closed
//  and it is out of CATIA space.
//==========================================================================
#ifndef CATFrFNurbsBiparCheck_H
#define CATFrFNurbsBiparCheck_H

#include "YP00IMPL.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"

class CATMathPoint;
class CATMathNurbsBipar;

//-----------------------------------------------------------------------------
class ExportedByYP00IMPL CATFrFNurbsBiparCheck : public CATCGMVirtual
{
  public :

    //
    CATFrFNurbsBiparCheck(CATMathNurbsBipar* bipar);

    //
    virtual  ~CATFrFNurbsBiparCheck();

    void      ActivateGlobalLengthCheck(double toleranceLength);

    void      ActivateFiniteDataCheckMode(double iInfiniteValue);

    // 0 if the element is not too short,
    // 1 if it is too small in u,
    // 2 if it is too small in v,
    // 3 if it is too small in both directions.
    CATLONG32 GetGlobalLengthDiagnostic();

    // To get the closure diagnostic, the global length check has to be done.
    // Method that supply some additional information when the element
    // is not degenerated
    // -2 if the computation has not been done.
    // -1 the element is too short, the closure diagnostic has no sense.
    // 0 if the element is not closed in that direction
    // 1 if the element is closed in that direction
    void      GetClosureDiagnostic(CATLONG32& isClosedU, CATLONG32& isClosedV);

    // 0 if no control points is out of space [-infiniteValue, + infiniteValue]^3
    // 1 otherwise
    CATLONG32 GetFiniteDataDiagnostic();
    CATLONG32 Run();

  private :

    CATLONG32 BipareHasConfusedBoundariesInU(CATMathPoint* CPs, CATLONG32 nbCPsU, CATLONG32 nbCPsV, CATLONG32& diag);
    CATLONG32 BipareHasConfusedBoundariesInV(CATMathPoint* CPs, CATLONG32 nbCPsU, CATLONG32 nbCPsV, CATLONG32& diag);

    CATLONG32 BipareIsClosedButNotDegeneratedInU(CATMathPoint* CPs, CATLONG32 nbCPsU, CATLONG32 nbCPsV, CATLONG32& isClosedAndNotDegeneretedInU);
    CATLONG32 BipareIsClosedButNotDegeneratedInV(CATMathPoint* CPs, CATLONG32 nbCPsU, CATLONG32 nbCPsV, CATLONG32& isClosedAndNotDegeneretedInV);

    CATLONG32 CheckGlobalLength(CATLONG32& diagnostic);

    CATLONG32 CheckControlPointsCoordinates(CATLONG32& controlPointsOutOfSpace);

    CATMathNurbsBipar* _bipar;

    CATLONG32          _globalLengthCheckMode;
    CATLONG32          _globalLengthDiagnotic;
    double             _toleranceLength;

    CATLONG32          _hasConfusedExtremitiesInU;
    CATLONG32          _hasConfusedExtremitiesInV;

    CATLONG32          _isClosedAndNotDegeneratedInU;
    CATLONG32          _isClosedAndNotDegeneratedInV;

    CATLONG32          _finiteDataCheckMode;
    double             _infiniteValue;
    CATLONG32          _controlPointsOutOfSpace;

    CATLONG32          _isClosedU;
    CATLONG32          _isClosedV;
};
#endif











