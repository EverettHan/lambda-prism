// COPYRIGHT DASSAULT SYSTEMES  2012
//=============================================================================
//
// CATMathSystemSpecialPointsConeApex:
//   This class is used to find the surface-surface intersection 
//   in the singular case of a cone apex
//
//   Implements the equations (F is the cone, G is the other surface):
//      (F-G).Fv       = 0
//      (F-G)._Axis    = 0
//      (Fv).(Gr ^ Gs) = 0
//  
//=============================================================================
// 22/10/12 Q48 Creation
// 07/06/16 NLD New constructor with software configuration
// 10/06/16 NLD Suppression definitive du constructeur sans configuration
//              Smart indent
// 01/07/16 NLD Changement de notations:
//              - iEquationIndex  remplace iEquationNumber
//              - iVariableIndex  remplace iVariableNumber
//              - iVariableIndex1 remplace iVariableNumber1
//              - iVariableIndex2 remplace iVariableNumber2
//=============================================================================


#ifndef CATMathSystemSpecialPointsConeApex_H
#define CATMathSystemSpecialPointsConeApex_H

// Base class
#include "CATMathSystemSpecialPoints.h"

// Basic types
#include "CATDataType.h"
#include "CATBoolean.h"

// Mathematics
#include "CATMathDef.h"
#include "CATMathConstant.h"

class CATMathFunctionXY;
class CATTolerance;
class CATMathAttrList;
class CATMathNxNFullMatrix;
class CATMathIntervalND;

//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathSystemSpecialPointsConeApex : public CATMathSystemSpecialPoints 
{ 
 public:

  CATMathSystemSpecialPointsConeApex(       CATSoftwareConfiguration * iConfig         ,
                                      const CATTolerance             & iTolObject      ,
                                      const CATMathFunctionXY        * iFunctionSur1[3],
                                      const CATMathFunctionXY        * iFunctionSur2[3],
                                      const double                     iScale          ,
                                      const double                     iAxis[3]        ,
                                      const CATMathAttrList          * attributes      = NULL);



  ~CATMathSystemSpecialPointsConeApex();

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

  virtual void           Eval                  (const double               * iSX,
                                                      double               * oFX);

  virtual void           EvalJacobian          (const double               * iX,
                                                      CATMathNxNFullMatrix * oJacobianFX); 

  virtual void           Eval                  (const double               * iSX        ,
                                                      double               * oFX        ,
                                                      CATMathNxNFullMatrix * oJacobianFX);

  virtual CATMathOption  ImplementsDerivs       ();
  virtual double         EvalFirstDerivEquation (const CATLONG32             iEquationIndex ,
                                                 const CATLONG32             iVariableIndex ,
                                                 const double              * iX             );
  virtual double         EvalSecondDerivEquation(const CATLONG32             iEquationIndex ,
                                                 const CATLONG32             iVariableIndex1,
                                                 const CATLONG32             iVariableIndex2,
                                                 const double              * iX             );

private:

          void           UpdateUsingAxis        (const double             [],
                                                 const double               ,
                                                       double             []); // output is axis ^ input

          double         DotProduct             (const double             [],
                                                 const double             []);

          void           CrossProduct           (const double             [],
                                                 const double             [],
                                                       double             []);
          void           AddCrossProduct        (const double             [],
                                                 const double             [],
                                                       double             []);

          void           SetNormalisation       (const double               ,
                                                       double             []);

          double _Axis[3];
          double _Scale;

  // Eq-0: is diff . fv
  // Eq-1: is diff . _Axis
  // Eq-2: is fv . (gr x gs)
  // Eq-3: is not used
};



#endif  
