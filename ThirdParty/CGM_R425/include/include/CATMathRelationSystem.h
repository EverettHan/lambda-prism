//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATMathRelationSystem :
//  Implement a CATMathSystem made of CATMathRelation
//
//=============================================================================
//
// Usage notes:
// 
//
//=============================================================================
//   /06/00 dad Creation
// 07/06/16 NLD Changement de signature du constructeur qui recoit une configuration
// 01/07/16 NLD Changement de notations:
//              - iEquationIndex  remplace iEquationNumber
//              - iVariableIndex  remplace iVariableNumber
//=============================================================================
#ifndef CATMathRelationSystem_H
#define CATMathRelationSystem_H

#include "YN000FUN.h"

#include <stdlib.h>

#include "CATMathSystem.h"


class CATMathRelation;
class CATMathSetOfPointsND;

class CATMathBooleanConstraint;

class CATSoftwareConfiguration;

struct CATMathBooleanConstraintVar;
struct CATMathEquationToRelation
{
   CATLONG32 _Relation;
   CATLONG32 _Equation;
};

class CATMathPoint2D;
class CATMathNxNFullMatrix;

//-------------------------------------------------------------------
class ExportedByYN000FUN CATMathRelationSystem : public CATMathSystem
 {
   // public methods
public:
   //-----------------------------------------------------------------
   // Object management
   //-----------------------------------------------------------------
   // iNbOfRelations = Nb of relations = Nb of Interior Vars
   // iExteriorDim = Nb of Exterior Vars = Sum of Nb of Exterior Vars of each relation
   // => _N = Nb of variabes = iNbOfRelations+iExteriorDim
   CATMathRelationSystem(      CATSoftwareConfiguration     *  iConfig           ,
                         const CATTolerance                  & iTolObject        ,
                               CATMathRelation             **  iRelationArray    ,
                         const CATLONG32                       iNbOfRelations    ,
                         const CATLONG32                       iExteriorDim      ,
                               CATMathBooleanConstraint    **  iBConstraintArray = NULL,
                               CATMathBooleanConstraintVar **  iBConstraintData  = NULL,
                         const CATLONG32                       iNbOfConstraints  = 0
                        );
   
   ~CATMathRelationSystem();
   
   
   //-----------------------------------------------------------------
   // Public Evaluators
   //-----------------------------------------------------------------
   void              Eval         (const double *iX, double *oFX);
   void              EvalJacobian (const double *iX,              CATMathNxNFullMatrix * oJacobianFX);
   void              Eval         (const double *iX, double *oFX, CATMathNxNFullMatrix * oJacobianFX);
   
   CATMathDiagnostic Solve (const CATMathIntervalND    & iDomain, 
                                  CATMathSetOfPointsND & oSolutions,
                            const CATMathAttrList      * iAttributes = NULL);
   
protected:
   //-----------------------------------------------------------------
   // Protected Evaluators
   //-----------------------------------------------------------------
   double EvalEquation          (const CATLONG32  iEquationIndex ,
                                 const double   * iX             );
   double EvalFirstDerivEquation(const CATLONG32  iEquationIndex ,
                                 const CATLONG32  iVariableIndex ,
                                 const double   * iX             );
   
   void EvalFirstDerivEquation  (const CATLONG32  iEquationIndex ,
                                 const double   * iX             ,
                                       double   * oDFX           );
   void EvalEquation            (const CATLONG32  iEquationIndex ,
                                 const double   * iX             ,
                                       double   & oFX            ,
                                       double   * oDFX           );
   
   
private:
   CATLONG32                      _InteriorDim;
   CATLONG32                      _ExteriorDim;
   
   CATMathRelation             ** _Relations;
   
   // Boolean Constraints to relimit the solutions
   CATMathBooleanConstraint    ** _BConstraints;
   // Array of size _NbOfBConstraints that define the position of the exterior vars of the constraints
   CATMathBooleanConstraintVar ** _BConstraintVar;
   CATLONG32                      _NbOfBConstraints;
   
   // For the relation i, its  j-th external variable is _ExteriorVar[i][j]
   CATLONG32                   ** _ExteriorVar;
   
   // The equation i corresponds to the equation _EquationToRelation[i]._Equation
   // of the  Relation _EquationToRelation[i]._Relation
   CATMathEquationToRelation    * _EquationToRelation;
};


#endif


