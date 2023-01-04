
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// Class designed to handle mapping between two Curves 
// The Mapping is realised using a projection Points on each Curve..
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Jan. 00 Creation                                                  R. HAMZA
// Aug. 11 Added the function GetType() (for comparing geometries).       R1Y
// Oct. 13 Cleaning of "memorySize" Methods                               JSX
//         It is not necessary to define them in that class.
//         should be deployed on the classes tree
// Jun. 17 Clean header
//         Add SimpleNewton, OldSimpleNewton methods                      F1Z
//=============================================================================
//-----------------------------------------------------------------------------
#ifndef CATProjectCrvSurMapX_H
#define CATProjectCrvSurMapX_H

// Advanced Mathematics
#include "CATMathFunctionX.h"

// Geometric Objects
#include "CATSetOfPointsMapX.h"
#include "CATCrvParam.h"
#include "YP00IMPL.h"

class CATCurve;
class CATSoftwareConfiguration;
class CATTolerance;

// ================================================================================= //
//                               CATProjectCrvSurMapX                                //
// ================================================================================= //
class ExportedByYP00IMPL CATProjectCrvSurMapX : public CATSetOfPointsMapX
{
public:
   /** @nodoc */
   CATCGMNewClassArrayDeclare;

   //-------------------------------------------------------------------------
   // Object management
   //-------------------------------------------------------------------------
   CATProjectCrvSurMapX (const CATCurve                 * iCurveToProject        ,
                         const CATCrvLimits             & iLimitsToProject       ,
                         const CATCurve                 * iCurveProjected        ,
                         const CATCrvLimits             & iLimitsProjected       ,
                         const double                     iMaxGap                ,
                         const CATLONG32                  iNbPoints        = 0   ,
                         const double                   * iParamsToProject = 0   ,
                         const double                   * iParamsProjected = 0   ,
                         const short                      iDuplicate       = 1   ,
                               CATSoftwareConfiguration * iConfig          = NULL);

   CATProjectCrvSurMapX(const CATCurve                  * iCurveToProject        ,
                        const double                      iRefLow                ,
                        const double                      iRefHigh               ,
                        const CATCurve                  * iCurveProjected        ,
                        const double                      iLow                   ,
                        const double                      iHigh                  ,
                        const double                      iMaxGap                ,
                        const CATLONG32                   iNbPoints        = 0   ,
                        const double                    * iParamsToProject = 0   ,
                        const double                    * iParamsProjected = 0   ,
                        const short                       iDuplicate       = 1   ,
                              CATSoftwareConfiguration  * iConfig          = NULL);

   CATProjectCrvSurMapX(const CATProjectCrvSurMapX      * iMapX                  );

   ~CATProjectCrvSurMapX();

   virtual CATMapX* Duplicate()const;

   //-------------------------------------------------------------------------
   // Set (interface)
   //-------------------------------------------------------------------------
   void SetConfig(CATSoftwareConfiguration * iConfig );

   //-------------------------------------------------------------------------
   // Get (interface)
   //-------------------------------------------------------------------------
   virtual CATMapX::Type GetType()const;

   //-------------------------------------------------------------------------
   // Methods
   //-------------------------------------------------------------------------
   virtual void Dump(CATCGMOutput& os)const;

protected:
   //-----------------------------------------------------------------------------
   // CATMapX methods (Reconverge depend de la fonctionnelle de projection PT/CRV)
   //-----------------------------------------------------------------------------
   void       Reconverge (const CATCurve          * iCurveToProject             ,
                          const double              iPointToProject             ,
                          const CATCurve          * iCurveProjected             ,
                                double            & oPointProjected             ,
                          const double              iLowProjected               ,
                          const double              iHighProjected              ,
                          const CATPositiveLength   iApproximateResolution = 0.0) const;

   CATBoolean BestReconverge (const CATCurve      * iCurveToProject             ,
                              const double          iPointToProject             ,
                              const CATCurve      * iCurveProjected             ,
                                    double        & oPointProjected             ,
                              const double          iLowProjected               ,
                              const double          iHighProjected              ) const;

   // INTERNAL ONLY
   virtual size_t  GetDynamicMemoryBytes() const;
   virtual size_t  GetStaticMemoryBytes () const;

private:
   //-----------------------------------------------------------------------------
   // Methods (private)
   //-----------------------------------------------------------------------------
   CATBoolean OldSimpleNewton          (const CATCurve         * iCurveToProject             ,
                                        const double             iPointToProject             ,
                                        const CATCurve         * iCurveProjected             ,
                                        const double             iLowProjected               ,
                                        const double             iHighProjected              ,
                                              double           & oPointProjected             ,
                                              CATBoolean       & oSolutionFound              ,
                                              CATBoolean       & oStrongerConvergenceNeeded  ) const;

   CATBoolean SimpleNewton             (const CATCurve         * iCurveToProject             ,
                                        const double             iPointToProject             ,
                                        const CATCurve         * iCurveProjected             ,
                                        const double             iLowProjected               ,
                                        const double             iHighProjected              ,
                                              double           & oPointProjected             ,
                                              CATBoolean       & oSolutionFound              ,
                                              CATBoolean       & oStrongerConvergenceNeeded  ) const;

   CATBoolean ReconvergeWithSolveNewton(const CATCurve         * iCurveToProject             ,
                                        const double             iPointToProject             ,
                                        const CATCurve         * iCurveProjected             ,
                                              double           & oPointProjected             ,
                                        const double             iLowProjected               ,
                                        const double             iHighProjected              ,
                                        const CATPositiveLength  iApproximateResolution = 0.0) const;

   //-------------------------------------------------------------------------
   // Attributs (private)
   //-------------------------------------------------------------------------
   CATSoftwareConfiguration * _Config;
};


// ================================================================================= //
//                                  ProjectFunction                                  //
// ================================================================================= //
// Derivative of Projection Function
class ProjectFunction : public CATMathFunctionX
{
public:
   //-------------------------------------------------------------------------
   // Object management
   //-------------------------------------------------------------------------
   ProjectFunction(const CATCurve   * iiCurveToProject,
                   const CATCurve   * iiCurveProjected,
                         CATBoolean   iiDirectReport  );

   CATMathFunctionX * Duplicate() const ;

   //-------------------------------------------------------------------------
   // Meta
   //-------------------------------------------------------------------------
   CATMathClassId IsA() const;

   //-------------------------------------------------------------------------
   // Set (interface)
   //-------------------------------------------------------------------------
   void SetTarget(double w);

   //-------------------------------------------------------------------------
   // Methods
   //-------------------------------------------------------------------------
   double Eval(const double & iT) const;

public:
   //-------------------------------------------------------------------------
   // Attributs (public)
   //-------------------------------------------------------------------------
   const CATCurve    * _CurveToProject ;
   const CATCurve    * _CurveProjected ;

         double        _Target         ;
         CATBoolean    _DirectReport   ;

         CATCrvParam   _W0ToProject    ;
         CATCrvParam   _W0Projected    ;
         CATCrvParam * _pW0ToProject   ;
         CATCrvParam * _pW0Projected   ;
};

#endif
