//======================================================================================//
// COPYRIGHT Dassault Systemes 2015/05/25
//======================================================================================//
//               CATCivilHorizCurveData                                                 //
//======================================================================================//
// Historic:
// 25/05/15 F1Z : Creation for Pt-Dir input case
// 14/12/15 F1Z : Implementation Line-Circle input case.
// 02/02/16 F1Z : Implementation Point-Point-Vector input case.
// 09/12/16 F1Z : Implementation End information case.
// 12/04/19 F4E : Implement Circle-Circle input case.
// 18/07/19 F4E : change private method signature
// 09/08/19 F4E : Add public Run() in CATCivilHorizCurveData class, 
//                and derived in daughter class when needed (if internal data to compute from inputs)
// 22/11/19 F4E : Add new private attribute for internal computations
// 13/12/19 F4E : New Circle-Circle case: for a clothoide with constrained Length (thus second circle position is not constrained)
//                * Add new CATCivilHorizCurveDataCircleCircleFixedLength derived from CATCivilHorizCurveDataCircleCircle
// 17/04/20 F4E : Migration to new class name for generic civil archi
// 05/06/20 F4E : Add attribute for CATCivilHorizComputeParam + Indent
// 08/06/20 F4E : Add Circle-Circle for foxed length method from CATClothoideFunctions and generalize it to spirals
// 11/08/20 Q48 : Small file tidy (const / C++ key-words) etc
// 16/10/20 Q48 : Migrate CheckParamValue to namespace CATCivilCurveDef
// 27/10/20 Q48 : Change signature ComputeFromRDR for cubic-parabola
// 03/11/20 Q48 : Add MaxDomain to separate curve domain (l) from curve length (L)
// 17/12/20 Q48 : Get data methods for validation of CivilCurveEvaluator
// 09/02/21 Q48 : Add CGMReplay stream/unstream/dump
// 11/03/21 Q48 : Split ComputeFromRDR for different transition tpyes
// 13/04/21 Q48 : IR-832058: compute civil curve from any 2 of the 5 parameters
// 13/04/21 Q48 : Unify some solvers (behind Q48_NEW_SOLVERS_DR)
// 12/05/21 Q48 : Tidy and debug for circle-circle
// 27/05/21 Q48 : Migration to GetTransformation (needed for CSC)
// 27/05/21 Q48 : New methods for CSC for sinusoidal / cosinusoidal
// 07/06/21 Q48 : Make Run protected to prevent reset of civil curve parameters
// 16/06/21 Q48 : Changes for CircleCircleFixedLength (re-factor to allow new transition types)
// 25/06/21 Q48 : Handle CircleCircle (including FixedLength) in small -> big circle cases
// 21/07/21 Q48 : Minor changes for CirleCircle
// 10/09/21 Q48 : Add compare methods for CGMReplay validation (migration from global Compare)
// 22/09/21 Q48 : Add init data from CDS for CircleCircle
// 05/10/21 Q48 : Split into new interface and implementation classes (in PrivateInterfaces)
//                   - now in this file is only CATCivilHorizCurveData (for CDS)
// 23/12/21 Q48 : Add copy constructor
//=====================================================================================//

#ifndef CATCivilHorizCurveData_H
#define CATCivilHorizCurveData_H

// Base class
#include "CATCivilCurveDataImp.h"

// ExportedBy
#include "GeoAdvCurves.h"

// C++11
#include "CATGeoOpVirtual.h"

// System
#include "CATBoolean.h"

// Mathematics
#include "CATMathConstant.h"
#include "CATMathDirection2D.h"
#include "CATMathTransformation2D.h"

// Advanced Mathemtics
#include "CATMathIdentifierMacros.h"

// GMModelInterfaces
#include "CATCivilCurveDef.h"

// GeometricOperators
#include "CATCivilCurveDefProtected.h"
//#include "CATCivilHorizParam.h"

class CATSoftwareConfiguration;
class CATTolerance;
class CATCGMOutput;
class CATCGMStream;
class CATGeoODTScaleManager;
class CATGeoFactory;
class CATSurface;
class CATPLine;
class CATPCircle;
class CATMathPoint2D;
class CATCivilHorizParam;

class CATCivilCurveEvaluator;
class CATCivilCurveComputeParam;
class CATCivilHorizComputeParam;
class CATCivilSolver;

// Validation
#include "CATUnicodeString.h"

// Debug
#include "CATGeoOpDebugDeclare.h"
class CATGeoOpDebugOutput;

// Temp
#include "CATCivilCurveArchiTEMP.h"

class ExportedByGeoAdvCurves CATCivilHorizCurveData : public CATCivilCurveDataImp
{
protected:

  CATCivilHorizCurveData(      CATSoftwareConfiguration * iConfig,
                         const CATTolerance             & iTol);

  CATCivilHorizCurveData(const CATCivilHorizCurveData & iToCopy);

public:

   virtual ~CATCivilHorizCurveData();

   DECLARE_SIMPLE_IDENTIFIER();

   // --------------------------------------------------------------------------
   // Get methods
   // --------------------------------------------------------------------------
   
   virtual HRESULT GetParams(double * oA2            = NULL,
                             double * oFinalL        = NULL,
                             double * oFinalRadius   = NULL,
                             double * oFinalAngle    = NULL,
                             double * oFinalShifting = NULL) const = 0;

   // --------------------------------------------------------------------------
   // CGM replay
   // --------------------------------------------------------------------------

protected:

  virtual void Dump(CATCGMOutput &  os) const CATGEOOverride;
};
#endif // CATCivilHorizCurveData_H
