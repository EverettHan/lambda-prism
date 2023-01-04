// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATEquationDistancePtSur :
// Function of two variables representing the square of the distance from a point
// to a surface (in 3d).
// 
//=============================================================================
// Usage notes:
//
//=============================================================================
// Jul.  97     Creation                                               J. Peter
//    06 04 EAB Versionning Interne
// 02 12 05 NLD Ajout de _LastGridEvalResults, _LastGridEvalOption,
//              _LastGridEvalNbX, _LastGridEvalNbY,
//              _LastGridEvalMinX, _LastGridEvalMaxX,
//              _LastGridEvalMinY, _LastGridEvalMaxY
//              pour optimisation si rappel sur la meme grille
// 30/01/09 NLD Interface R20 (CATSoftwareConfiguration)
//              pour Minimize()
//              Puis suppression de la methode qui ne faisait qu'une indirection
//              sur la methode standard
//   /04/22 smt1 Deplacement de GeometricOperators vers AdvancedMathematics
//              pour utilisation dans GeometricObjects
// 18/01/22 NLD Mise au propre, detabulation
//              Deflaggage
//=============================================================================

#ifndef CATEquationDistancePtSur_H
#define CATEquationDistancePtSur_H

#include "CATMathFunctionXY.h"

class CATMathPoint;
class CATSoftwareConfiguration;

//-----------------------------------------------------------------------------
//DG class CATEquationDistancePtSur : public CATMathFunctionXY
#include "YN000FUN.h"
#include "CATMathBasisFunctionXY.h"
#include "CATTolerance.h"


// ExportedByY30A3HGG removed -- wxh 03 Dec 2010
class ExportedByYN000FUN CATEquationDistancePtSur : public CATMathBasisFunctionXY
{
   // public methods
public:
   //-----------------------------------------------------------------
   // Object management
   //-----------------------------------------------------------------

                      CATEquationDistancePtSur(const CATEquationDistancePtSur & iF);
                      CATEquationDistancePtSur(      CATSoftwareConfiguration * iConfig    ,
                                               const CATMathPoint             & iPt        ,
                                               const CATMathFunctionXY        * iFX        ,
                                               const CATMathFunctionXY        * iFY        ,
                                               const CATMathFunctionXY        * iFZ        ,
                                               const CATTolerance             & iTolObject = CATGetDefaultTolerance());
                      ~CATEquationDistancePtSur();

   CATMathFunctionXY * Duplicate() const;
   void                SetPoint(const CATMathPoint &);

   //-----------------------------------------------------------------
   // Information methods
   //-----------------------------------------------------------------

   CATMathClassId      IsA      ()                              const;
   CATBoolean          IsAKindOf(const CATMathClassId iClassId) const;
   CATBoolean          IsOption (const CATMathOption  iOption)  const;

   //-----------------------------------------------------------------
   // Evaluators on doubles
   //-----------------------------------------------------------------   
   double Eval             (const double & u, const double & v) const;
   double EvalFirstDerivX  (const double & u, const double & v) const;
   double EvalFirstDerivY  (const double & u, const double & v) const;
   double EvalSecondDerivX2(const double & u, const double & v) const;
   double EvalSecondDerivXY(const double & u, const double & v) const;
   double EvalSecondDerivY2(const double & u, const double & v) const;

   void   Eval             (const double   u, const double   v,
                            const CATMathOption iOption,
                                  double * f, 
                                  double * dfx  = 0, double * dfy  = 0,
                                  double * dfxx = 0, double * dfxy = 0, double * dfyy = 0) const;

   void   Eval             (const CATMathIntervalND & iDomain ,
                            const CATLONG32         * NbPoints,
                            const CATMathOption       iOptions,
                                  double * f,
                                  double * fx  = 0, double * fy  = 0,
                                  double * fx2 = 0, double * fxy = 0, double *fy2 = 0) const;

   //-----------------------------------------------------------------
   // Evaluators on intervals
   //-----------------------------------------------------------------
   CATMathInterval Eval(const CATMathInterval & Du,
                        const CATMathInterval & Dv,
                        const CATTolerance    & iTolObject = CATGetDefaultTolerance()) const;

   CATMathInterval EvalFirstDerivX  (const CATMathInterval & x, const CATMathInterval & y) const;
   CATMathInterval EvalFirstDerivY  (const CATMathInterval & x, const CATMathInterval & y) const;
   CATMathInterval EvalSecondDerivX2(const CATMathInterval & x, const CATMathInterval & y) const;
   CATMathInterval EvalSecondDerivXY(const CATMathInterval & x, const CATMathInterval & y) const;
   CATMathInterval EvalSecondDerivY2(const CATMathInterval & x, const CATMathInterval & y) const;

   /* NLD300109
   CATMathDiagnostic Minimize(const CATMathInterval2D & D,
                                    CATMathSetOfPointsND & roots,
                              const CATMathAttrList * attributes
                              #ifdef CATMathFunctionXYR20Interface
                                   ,CATSoftwareConfiguration* iConfig=NULL
                              #endif

                             ) const;
   */

private:
         double                     _x;
         double                     _y;
         double                     _z;
   const CATMathFunctionXY        * _FX;
   const CATMathFunctionXY        * _FY;
   const CATMathFunctionXY        * _FZ;
         CATSoftwareConfiguration * _Config;
   // Donnees d'optimisation NLD021205
         double                   * _LastGridEvalResults ;
         CATMathOption              _LastGridEvalOption ;
         CATLONG32                  _LastGridEvalNbX    ;
         CATLONG32                  _LastGridEvalNbY    ;
         double                     _LastGridEvalMinX   ;
         double                     _LastGridEvalMaxX   ;
         double                     _LastGridEvalMinY   ;
         double                     _LastGridEvalMaxY   ;
 //const CATTolerance             & _TolObject;

};

#endif
