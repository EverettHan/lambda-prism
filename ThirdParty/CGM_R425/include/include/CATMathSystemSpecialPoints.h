// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathSystemSpecialPoints:
//  class used to find initialization points for surface surface intersection
//
//=============================================================================

//=============================================================================
// XScaleStatus/XScaleRules:                                                                    (NLD010616)
// 1) standard behaviour
//  - domains         must behave like power 1 of factory scale
//  - parameters      must behave like power 1 of factory scale
//  - function        must behave like power 1 of factory scale
//  - steps  computed must behave like power 1 of factory scale
//
// 2) for a system not following standard behaviour:
//  Scale behaviour may be defined by two means (from best way to worst)
//  - specify a CATMathAttrScaleOption attribute through attributes list at constructor call 
//  - use SetScaleOption()
//
//  CAUTION:
//  anyway: THIS system, when taking standard and homogeneous functions,
//  builds an internal system in which third and fourth function coordinates
//  have a different behaviour
//  see CATFunctionIntersectionSurSur::BuildSingularSystem for example,
//  in which we have
//    CATLONG32 PowerScaleF[4] =  {1,1,0,0};
//    CATLONG32 PowerScaleX[4] =  {1,1,1,1};
//  the expected new behaviour, inactive as of 010616 would be
//    CATLONG32 PowerScaleF[4] =  {1,1,1,1};
//    CATLONG32 PowerScaleX[4] =  {1,1,1,1};
//
//  CAUTION any modification of PowerScaleF should be accompanied to the study
//  of the modification of the PowerScaleF data for main calling class CATMathSystemReturningPoints
//
//  CAUTION: Class not fully migrated / certified for non standard scale option                 (NLD010616)
//     use of standard scale option very strongly recommended
//
// ATTENTION: si on change le fonctionnement en rendant le systeme homogene
// - il faut modifier le ScaleOption de tous les appelants
// - il faut etudier la derivation CATMathSystemSpecialPointsConeApex et ses appelants
//=============================================================================

//=============================================================================
// 01/06/16 NLD XScale
//              - XScaleStatus/XScaleRules pour indiquer l'etendue des degats
// 03/06/16 NLD Ajout constructeur avec configuration
//              Ajout Init()
// 10/06/16 NLD Suppression definitive du constructeur sans configuration
//=============================================================================
// 
#ifndef CATMathSystemSpecialPoints_H
#define CATMathSystemSpecialPoints_H

// ATTENTION
// - definition ici de ce #define partage, NLD010616, pour du code et une nomenclature JSX040415
// - en toute rigueur une telle modification aurait un impact XScale et donc devrait etre geree par versionning
// - le #define doit etre vu comme une facilite de prototypage/test seulement
// #define ScaleSystemSpecialPoints "ATTENTION. va conditionner des modifications dans des appelants CATFunctionIntersectionSurSur, ... NLD010616"

#include "CATMathDef.h"
#include "CATMathConstant.h"

#include "CATMathSystem.h"
#include "YN000FUN.h"

class CATMathFunctionXY;
class CATMathNxNFullMatrix;
class CATMathIntervalND;
class CATSoftwareConfiguration;

//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathSystemSpecialPoints : public CATMathSystem 
{ 
 public:

  CATMathSystemSpecialPoints  (   CATSoftwareConfiguration*  iConfig          ,
                                const CATTolerance         & iTolObject       ,
                                const CATMathFunctionXY   *  iFunctionSur1[3] ,
                                const CATMathFunctionXY   *  iFunctionSur2[3] ,
                                const CATMathAttrList     *  attributes       = NULL);


  virtual ~CATMathSystemSpecialPoints();

  //--------------------------------------------------------------------------
  // Information methods
  //--------------------------------------------------------------------------
         
  virtual CATMathClassId IsA      ()                              const;
  virtual CATBoolean     IsAKindOf(const CATMathClassId iClassId) const;
  
  /************************************************************************/
  /* Evaluators: iX is a point in R4.                                     */
  /*  . oFX = F(iX) is the image of iX by F. oFX is in R4 and is already  */
  /*    allocated.                                                        */
  /*  . oJacobianFX is the jacobian of F at iX and is a 4x4 Matrix already*/
  /*     allocated                                                        */
  /*                                                                      */
  /************************************************************************/

  virtual void Eval            (const double               *  iSX             ,
                                      double               *  oFX             );
 
  virtual void EvalJacobian    (const double               *  iX              ,
                                      CATMathNxNFullMatrix *  oJacobianFX     );

  virtual void Eval            (const double               *  iSX             ,
                                      double               *  oFX             ,
                                      CATMathNxNFullMatrix *  oJacobianFX     );

private:
          void Init            (const CATMathFunctionXY   *  iFunctionSur1[3] ,
                                const CATMathFunctionXY   *  iFunctionSur2[3] );

protected:

  const CATMathFunctionXY *_Function1[3];
  const CATMathFunctionXY *_Function2[3];

};

#endif  
