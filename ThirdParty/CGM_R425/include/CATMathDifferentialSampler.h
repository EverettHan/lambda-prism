//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2002
//=============================================================================
//
// CATMathDifferentialSampler :
//
//   Sampler for a differential system solution, 
//   designed to evaluate that solution at any value for the parameter.
//
// The order of the differential system sampled is one (as required by 
// CATMathDifferentialSystem) but its dimension is what you want.
// You can nevertheless specify that you are interrested in the 
// first coordinates only.
//
// XScaleRules:                                                                                 (NLD021213)
// (see mother class CATMathVectorialFunctionX)
//  - there is no ScaleOption (of typeCATMathAttrScaleOption) describing the vectorial function :
//    scale behaviour is imposed
//  - domains         must behave like power 1 of factory scale
//  - parameters      must behave like power 1 of factory scale
//  - points computed must behave like power 1 of factory scale
//  - steps  computed must behave like power 1 of factory scale
//=============================================================================
//
// Usage notes:
//
//
//=============================================================================
// 02/12/13 NLD Ajout XScaleRules
//              Smart indent
//=============================================================================

#ifndef CATMathDifferentialSampler_H
#define CATMathDifferentialSampler_H

#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathDiagnostic.h"
#include "CATMathStopDiagnostic.h"
#include "CATMathVectorialFunctionX.h"

#include "CATTolerance.h"

class CATMathAttrList;
class CATMathIntervalND;
class CATMathSetOfPointsND;
class CATMathDifferentialSystem;
class CATSoftwareConfiguration;

class ExportedByYN000FUN CATMathDifferentialSampler : public CATMathVectorialFunctionX
{
public :
   // ***
   // Constructor & destructor
   //
                              CATMathDifferentialSampler(const CATLONG32                    dim    ,
                                                         const CATLONG32                    dimsys ,
                                                               CATMathDifferentialSystem *  DiffSys);
         // dim is the dimension of the CATMathVectorialFunctionX you are creating
         // dimsys is the dimension of the differential system.
         // For exemple, if you handle a 2nd-order differential system, you have dimsys = dim*2,
         // then interresting coordinates are the first dim coordinates
         // (the others are derivatives).
         // You generally have : dimsys = dim * order_of_differential_system.
                              CATMathDifferentialSampler(      CATSoftwareConfiguration  *  iSoftwareConfiguration,
                                                         const CATLONG32                    dim                   ,
                                                         const CATLONG32                    dimsys                ,
                                                               CATMathDifferentialSystem *  DiffSys               ,
                                                         const CATTolerance               & iTol                  = CATGetDefaultTolerance()
                                                        );

   virtual                   ~CATMathDifferentialSampler();

   // ***
   // Solves the differential equation
   //  (computes a 1st set of points)
   // Initializes the domain of the CATMathVectorialFunctionX
           CATMathDiagnostic  Init                      (const double                    *  iStartPoint           ,
                                                         const double                       iStartParameter       ,
                                                         const double                       iMaximumParameter     ,
                                                         const CATMathIntervalND         *  iDomain               ,
                                                         const CATMathAttrList           *  iAttributes           = 0);

   // ***
   // Information Methods
   //
           CATMathStopDiagnostic GetLastStopDiagnostic  ();
      // Last StopDiagnostic obtained in evaluation or Init methods.
      // Normally OK after an Eval correctly called.
           void               CopyParameters            (      CATMathSetOfPointsND      *  oResult               );
      // Returns the set of stored parameters.

   // ***
   // Switches
   //
           void               SetStorePoints            (      CATBoolean                   store                 );
     // Indicates whether you want to store the points computed by Eval
      // to do smaller steps in the future. Default is YES.

           void               SetMaximumDensity         (      double                       iSag                  );
      // Indicates the density of initial points you want.
      // Call CopyParameters to get corresponding parameters with respect to this density.
      // If unset, all computed points will be given.

   // ***
   // Evaluation Methods
   //
   //  Computes the point on the solution for any parameter
   //  (if necessary, makes an additional step of DOPRI5, then stores the point)
   //  iX, oFX, oDFX are of dimension "dim" (cf constructor)
   virtual void               Eval                      (const double                       iX                    ,
                                                               double                    *  oFX                   ) const;
   virtual void               Eval                      (const double                       iX                    ,
                                                               double                    *  oFX                   ,
                                                               double                    *  oDFX                  ) const;
   virtual void               EvalFirstDeriv            (const double                       iX                    ,
                                                               double                    *  oDFX                  ) const; 

  // ***
   // Rem - For the 2nd derivatives, the treatment is by default
   //
// virtual void               EvalSecondDeriv           (const double  iX, double *oD2FX) const;
// virtual void               EvalDeriv                 (const double  iX, double *oDFX, double *oD2FX) const;


protected :

   // ***
   // Auxiliary Methods
   //
           void               MakeDOPRI                 (const double                       iX                    ,
                                                               CATLONG32                 *  Pind                  = 0,
                                                               int                       *  Pdiag                 = 0) const;
      // Internal evaluator : evaluates the point in dimension _DimSys.
      // The result is stored in _BPoint.

   // ***
   // Data Fields
   //
   // - The Differential System
   CATMathDifferentialSystem  * _DiffSys;

   // - Last stop diagnostic from CATMathDifferentialSystem methods
   CATMathStopDiagnostic        _LastStopDiag;

   // - Dimension of the differential system
   CATLONG32                    _DimSys;

   // - Dimension of the problem
   CATLONG32                    _Dim;

   // - Maximum density of initial points (0 to disable feature)
   double                       _Sag;

   // - Auxiliary Fields
   double                     * _BPoint; // Buffer

   // - Stored additional information
   //    Rem - CATMathVectorialFunctionX's fields already stores the values for points and derivatives.
   CATMathSetOfPointsND       * _TrFDer; // (dimsys-dim) dernieres composantes de la solution
   CATMathSetOfPointsND       * _TrSDer; // (dimsys-dim) dernieres composantes de la derivee
                                                //   (on applique F au precedent)
     // (noms choisis a cause du geodesique differentiel : derivees transformees)


private :

   CATMathDifferentialSampler * _localthis; // Selfpointer

};

#endif
