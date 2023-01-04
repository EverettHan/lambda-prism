// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//   /03/00 XGN  Creation
//   /01/04 EAB  Versionning
// 09/02/22 Q48  Migration to CATGeoOperator
//=============================================================================
// Usage notes:
//  This operator is used to check the internal validity of a surface on a given SurLimits:
// 
//=============================================================================
#ifndef CATCheckSurface_H
#define CATCheckSurface_H

// Base class
#include "CATGeoOperator.h"

// ExportedBy
#include "Y30UIUTI.h"

// C++11
#include "CATGeoOpVirtual.h"

// Maths
#include "CATMathDef.h"

// Geometric Objects
#include "CATSurLimits.h"

// GeometricOperators
#include "CATCreateCheckSurface.h"

class CATGeoFactory;
class CATSurface;
class CATError;
class CATCGMOutput;
class CATSoftwareConfiguration;

class ExportedByY30UIUTI CATCheckSurface : public CATGeoOperator
{
public:
   //-----------------------------------------------------------------------
   //- Object management
   //-----------------------------------------------------------------------

   CATCheckSurface(CATGeoFactory            * iFactory,
                   CATSoftwareConfiguration * iConfig,
		             CATSurface               * iSurface);

   virtual ~CATCheckSurface();

   //-----------------------------------------------------------------------
   //- Settings methods
   //-----------------------------------------------------------------------

   void SetLimits(const CATSurLimits & iLimits);

   //-----------------------------------------------------------------------
   //- Get methods
   //-----------------------------------------------------------------------

   // Array of errors pointers is returned (0 is no error found)
   // This array must be deleted by the caller.
   CATError ** GetCheckResult(CATLONG32 & oNbErrors);

   //-----------------------------------------------------------------------
   //- Running the operator
   //-----------------------------------------------------------------------


   int Run();

   //-----------------------------------------------------------------------
   //- For internal use only : Write in the console the detected errors when
   //  encountered during the Run()
   //-----------------------------------------------------------------------
   void SetConsoleOutput();
   void SetOutput(CATCGMOutput & os);

   //-----------------------------------------------------------------------
   // Perform more check. Warning : this mode is expensive
   //-----------------------------------------------------------------------
   void SetAdvancedMode();

protected:
   void Initialize();
   void RunAdvanced();

   CATSurLimits _Limits;
   CATSurface * _Surface;

   CATLONG32 _SurfaceKO; // counter of number of errors

   // - Internal data 
   CATBoolean _CGMOutput;
   CATCGMOutput *_os;

   // - Advanced mode
   CATBoolean _AdvancedMode;

   CATSoftwareConfiguration * _Config;
};

#endif
