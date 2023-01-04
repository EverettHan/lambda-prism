/*-*-C++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// Internal Functions of the Interpolation Operator for Curves and PCurves.
//
//==========================================================================
//
// Usage notes:
//==========================================================================
// Sept. 97 DHN Creation                                            Davidoff
// Mars. 98 NDN Lifting + Surfacic functions
// Apri. 99 NDN Interpolation with tangents
// Janv. 10 JSX Archi
//              Suppression de la methode InterpolWithTangents
//              Elle n'est pas utilisée et n'a rien a faire dans le FW GeometricObjects
//              Déplacement dans FreeForm de la méthode ControlledInterpolWithTangents
//              Elle est specifique au loft, la redescendre dans GeoOperator si necessaire 
// 20/05/14 NLD Detabulation
//              Smart indent
// 10/06/14 NLD XScale: argument iTolObject a HermitInterpolation()
//========================================================================== 

#ifndef CATFrFUtiPolynomialBasis_H
#define CATFrFUtiPolynomialBasis_H

#include "CATTolerance.h"

class CATMathSetOfPointsNDTwoTangents;
class CATMathSetOfPointsND;
class CATKnotVector;

#include "YP00IMPL.h"

#define CATFrFUtiPolynomialBasis_ARCHIJSX_InterpolWithTangentsNotUsed                   "Activation JSX 2010"
#define CATFrFUtiPolynomialBasis_ARCHIJSX_ControlledInterpolWithTangentsOwnedByFrF      "Activation JSX 2010"

///////////////////////////////////////////////////////////////////////////////
//                          CAS COURBE                                       //
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
//  Hermit Interpolation function -> Creates or modifies a NurbsCurve
//  iDimension =2 for posed geometry and 3 for free geometry.
//-----------------------------------------------------------------------------
ExportedByYP00IMPL
            CATMathPoint        * GetHermitInterpolationResult    (const double                          *  iPoints            ,
                                                                   const double                          *  iTangents          ,
                                                                   const CATLONG32                        & iNbOfPoints        ,
                                                                   const CATKnotVector                   *  iKnotVector        ,
                                                                   const CATLONG32                        & iDimension         );

//-----------------------------------------------------------------------------
// Fonction Globale permettant de calculer les points de controle d'une courbe
// Nubs dont on connait le vecteur nodal et son expression polynomial arc par arc.
// OB 2/00  : ShiftType =0 :no shift 
//            ShiftType=1 : Shift of half arc parameter length on *PolCoef ( compliant with GetShiftedxx of CATKnotVector) 
//-----------------------------------------------------------------------------
ExportedByYP00IMPL
            CATMathPoint        * FromPolynomialBasisToNurbsBasis (const CATKnotVector                   *  iKnotVector        ,
                                                                   const CATLONG32                        & iDimension         ,
                                                                   const double                          *  PolCoef            ,
                                                                   const CATLONG32                        & iShiftType         = 0);

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
ExportedByYP00IMPL
            void                  GetHermitCoefficients           (const double                          *  iPoints            ,
                                                                   const double                          *  iTangents          ,
                                                                   const CATLONG32                        & iNbOfPoints        ,
                                                                   const CATKnotVector                   *  iKnotVector        ,
                                                                   const CATLONG32                        & iDimension         ,
                                                                         double                          *  oPolynomCoef       );

//-----------------------------------------------------------------------------
//  Set new points and/or new first derivatives to interpolate 
//-----------------------------------------------------------------------------
// N.B quelques explications très postérieures, NLD081119
//     - on travaille en dimension 2 ou 3, selon iDimension
//     - cependant les coordonnées qui nous interessent, X, Y et éventuellement Z
//       ne sont pas forcement aux indices 0, 1 (et 2) dans iPoints
//       mais aux indices nvar0, nvar1, nvar2 (indices commençant en 0)
ExportedByYP00IMPL
            CATKnotVector       * HermitInterpolation             (const CATMathSetOfPointsND            *  iPoints            ,
                                                                   const CATLONG32                        & iDimension         ,
                                                                   const CATLONG32                        & nvar0              ,
                                                                   const CATLONG32                        & nvar1              ,
                                                                   const CATLONG32                        & nvar2              ,
                                                                         double                          *  ioPoints           ,
                                                                         double                          *  ioTangents         ,
                                                                         CATLONG32                        & iNbOfPoints        ,
                                                                         CATKnotVector                   *  iImposedKnotVector = NULL,
                                                                   const CATTolerance                     & iTolObject         = CATGetDefaultTolerance()
                                                                  );

//-----------------------------------------------------------------------------
// Fonction Globale permettant de construire un KnotsVector a partir de donnees
// elementaires (degre,etc) et de l'expression polynomiale arc par arc.
// Cette fonction detecte la continuite inter-arc (jusqu'a C2) des polynomes,
// dans le choix des multiplicites nodales. Le vecteur nodal doit pointer sur NULL.
//-----------------------------------------------------------------------------
ExportedByYP00IMPL
            CATKnotVector       * ComputeKnotVector               (const CATLONG32                        & Degree             ,
                                                                   const CATLONG32                        & NbArcs             ,
                                                                   const double                          *  Knots              ,
                                                                   const double                          *  PolCoef            ,
                                                                   const CATTolerance                     & iTolObject         = CATGetDefaultTolerance()
                                                                  );

#ifndef CATFrFUtiPolynomialBasis_ARCHIJSX_InterpolWithTangentsNotUsed
//-----------------------------------------------------------------------------
//Interpolation permettant de fixer de maniere exacte les tangentes dans l'interpolation.
//Cette methode supporte egalement, la non imposition en une extremite de la tangente.
//Comme le CATMathSetOfPointsNDTwoTangents a necessairement des tangentes, il faut renseigner
//ImposeStart et ImposeEnd. Par defaut, ils valent 1 et donc les tangentes sont imposees.
//L'interolation multiformes ne marche qu'en dimension 3, cad que la dimension du
//CATMathSetOfPointsNDTwoTangents doit etre un multiple de 3. Dans ce cas, les points
//controles en sortie sont correctement formates en vue de la creation d'une MultiForm de degre 3.
//-----------------------------------------------------------------------------
ExportedByYP00IMPL
            CATMathPoint        * InterpolWithTangents            (      CATMathSetOfPointsNDTwoTangents *  Points              ,
                                                                   const CATKnotVector                   *  KV                  ,
                                                                         CATLONG32                          ImposeStart         = 1,
                                                                         CATLONG32                          ImposeEnd           = 1
                                                                  );

#endif

#ifndef CATFrFUtiPolynomialBasis_ARCHIJSX_ControlledInterpolWithTangentsOwnedByFrF
//-----------------------------------------------------------------------------
// Interpolation permettant de fixer de maniere exacte les tangentes dans l'interpolation.
// Cette methode supporte egalement, la non imposition en une extremite de la tangente.
// Comme le CATMathSetOfPointsNDTwoTangents a necessairement des tangentes, il faut renseigner
// ImposeStart et ImposeEnd. Par defaut, ils valent 1 et donc les tangentes sont imposees.
// L'interolation multiformes ne marche qu'en dimension 3, cad que la dimension du
// CATMathSetOfPointsNDTwoTangents doit etre un multiple de 3. Dans ce cas, les points
// controles en sortie sont correctement formates en vue de la creation d'une MultiForm.
// SPECIAL FONCTION DELTA ( evolution de Fonction difference )
// LA specificite de cette methode est de privilegier les stabilites de la fonction.
// si deux valeurs a interpoler consecutives sont egales, alors la fonction est constante entre les deux.
//-----------------------------------------------------------------------------
ExportedByYP00IMPL
            CATMathPoint        * ControlledInterpolWithTangents  (      CATMathSetOfPointsNDTwoTangents *  Points              ,
                                                                   const CATKnotVector                   *  KV                  ,
                                                                         CATLONG32                          ImposeStart         = 1,
                                                                         CATLONG32                          ImposeEnd           = 1,
                                                                         CATLONG32                          CGMLevel            = 0,
                                                                   const CATTolerance                     & iTolObject          = CATGetDefaultTolerance()
                                                                  );

#endif
///////////////////////////////////////////////////////////////////////////////
//                          CAS SURFACIQUE                                   //
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// Fonction Globale permettant de calculer les points de controle d'une surface
// Nubs dont on connait les vecteurs nodaux et son expression polynomial carreaux
// par carreaux.
// OB 2/00  : ShiftType =0 :no shift 
//            ShiftType=1 : Shift of half arc parameter length on *PolCoef ( compliant with GetShiftedxx of CATKnotVector)
//-----------------------------------------------------------------------------
ExportedByYP00IMPL
            CATMathPoint        * FromPolynomialBasisToNurbsBasis (const CATKnotVector                   *  iKnotVectorU         ,
                                                                   const CATKnotVector                   *  iKnotVectorV         ,
                                                                   const double                          *  PolCoef              ,
                                                                   const CATLONG32                          iShiftTypeU          = 0,
                                                                   const CATLONG32                          iShiftTypeV          = 0);

//-----------------------------------------------------------------------------
// Fonction Globale permettant de construire deux KnotsVectors a partir de donnees
// elementaires (degre,etc) et de l'expression polynomiale carreau par carreau
// Cette fonction detecte la continuite (jusqu'a C2) inter-carreaux des polynomes,
// dans le choix des multiplicites nodales. Les vecteurs nodaux doivent pointer sur NULL.
// SENS U
//-----------------------------------------------------------------------------
ExportedByYP00IMPL
            CATKnotVector       * ComputeKnotVectorU              (const CATLONG32                        & DegreeU              ,
                                                                   const CATLONG32                        & DegreeV              ,
                                                                   const CATLONG32                        & NbArcsU              ,
                                                                   const CATLONG32                        & NbArcsV              ,
                                                                   const double                          *  KnotsU               ,
                                                                   const double                          *  PolCoef              ,
                                                                   const CATTolerance                     & iTolObject           = CATGetDefaultTolerance()
                                                                  );

//-----------------------------------------------------------------------------
// Fonction Globale permettant de construire deux KnotsVectors a partir de donnees
// elementaires (degre,etc) et de l'expression polynomiale carreau par carreau
// Cette fonction detecte la continuite (jusqu'a C2) inter-carreaux des polynomes,
// dans le choix des multiplicites nodales. Les vecteurs nodaux doivent pointer sur NULL.
// SENS V
//-----------------------------------------------------------------------------
ExportedByYP00IMPL
            CATKnotVector       * ComputeKnotVectorV              (const CATLONG32                        & DegreeU              ,
                                                                   const CATLONG32                        & DegreeV              ,
                                                                   const CATLONG32                        & NbArcsU              ,
                                                                   const CATLONG32                        & NbArcsV              ,
                                                                   const double                          *  KnotsV               ,
                                                                   const double                          *  PolCoef              ,
                                                                   const CATTolerance                     & iTolObject           = CATGetDefaultTolerance()
                                                                  );

#endif
