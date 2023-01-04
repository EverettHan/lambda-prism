//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATMathRelationSolver :
//  Class used to Solve a system of CATMathRelation
//
//=============================================================================
//
// Usage notes:
//
//
//=============================================================================
// June  00 DAD Creation                                            D. Allemand
// 07/06/16 NLD Ajout de _Config et reception de la configuration dans le constructeur
//=============================================================================
#ifndef CATMathRelationSolver_H
#define CATMathRelationSolver_H

#include "YN000FUN.h"


#include <stdlib.h>

#include "CATBoolean.h"
#include "CATMathDiagnostic.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATTolerance.h"

class CATMathRelation;
class CATMathBooleanConstraint;

struct CATMathBooleanConstraintVar;


class CATMathIntervalND;
class CATMathRelationSystem;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;

//-------------------------------------------------------------------
class ExportedByYN000FUN CATMathRelationSolver : public CATCGMVirtual
{
   // public methods
public:
   //-----------------------------------------------------------------
   // Object management
   //-----------------------------------------------------------------
   CATMathRelationSolver (CATSoftwareConfiguration* iConfig    ,
                          CATLONG32                 InteriorDim);
   ~CATMathRelationSolver();
   
   
   //-----------------------------------------------------------------
   // Add and Get Methods
   //-----------------------------------------------------------------
   // return an array oPosition of size 2:
   //   - 0 <= oPosition[0] < _NbRelations : is the position of the Relation
   //   - 0 <= oPosition[1] < _ExteriorDim : the position of the first exterior Var
   void                       AddRelation         (CATMathRelation          * iRelation,
                                                   CATLONG32                * oPosition    = NULL);
   void                       AddBooleanConstraint(CATMathBooleanConstraint * iBConstraint,
                                                   CATLONG32                * iExtVarPlace = NULL);
   
   // 0 <= iRelationIndex <= _NbRelations -1
   CATMathRelation          * GetRelation(CATLONG32 iRelationIndex);
   
   // 0 <= iBooleanConstraintIndex <= _NbBConstraints -1
   CATMathBooleanConstraint * GetBooleanConstraint(CATLONG32 iBooleanConstraintIndex);
   
   CATLONG32                  GetExteriorDimension();
   
   
   
   CATBoolean IsSquare();
   
   //-----------------------------------------------------------------
   // Solve Method
   //-----------------------------------------------------------------
   // Domain = 0 if no need of Domain
   CATMathDiagnostic Solve(      CATMathIntervalND    * iDomain    ,
                                 CATMathSetOfPointsND & oSols      ,
                           const CATTolerance         & iTolObject = CATGetDefaultTolerance());
   
protected :
   void GetDomain(CATMathIntervalND *oDomain);
   
   
private:
   CATLONG32                      _InteriorDim;
   
   // Sum the relations'Exterior Dimension
   CATLONG32                      _ExteriorDim;
   
   // Nb Of relations
   CATLONG32                      _NbRelations;
   
   // Number of Constraints
   CATLONG32                      _NbBConstraints;
   
   // Relations to be put in the CATMathRelationSystem *_Sys
   CATMathRelation             ** _Relations;
   
   // Boolean Constraints to relimit the solutions
   CATMathBooleanConstraint    ** _BConstraints;
   // Boolean Constraint Var Position
   CATMathBooleanConstraintVar ** _BConstraintsVar;

   CATSoftwareConfiguration     * _Config; 
};

#endif


