//====================================================================
// Copyright Dassault Systemes Provence 2003, all rights reserved 
//====================================================================
//
// CATSobSubdivisionOperator.h
//
//====================================================================
//
// Usage notes:
//
//====================================================================
// June,      2005 : RAQ : Desactivation du code
// January,   2004 : RAQ : Changement d'architecture des subdivisions
// September, 2003 : JCV : Gestion Diag
// Marsh,     2003 : JCV : Creation
//====================================================================
#ifndef CATSobSubdivisionOperator_H
#define CATSobSubdivisionOperator_H

/********************************************************************************************/
//                                                                                          //
// RAQ: 10.06.05: Ce code n'est plus actif, il reste là au cas où.....                      //
//                Pour activation voir USE_OLD_SUBDIV_OPE dans CATSobSubdivisionOperator.h  //
//                                                                                          //
/********************************************************************************************/

//#define USE_OLD_SUBDIV_OPE

#ifdef USE_OLD_SUBDIV_OPE




#include "CATSobOperators.h"

#include "CATSobDiag.h"

class CATSobMesh;


class ExportedByCATSobOperators CATSobSubdivisionOperator
{
public:
  
  CATSobSubdivisionOperator(CATSobMesh* iMesh);

  virtual ~CATSobSubdivisionOperator();
};

ExportedByCATSobOperators 
CATSobDiag CATSobCreateSubdivision(CATSobMesh* iMesh,
                                   const int   iLevel,
                                   const int   iVersionLevel=0);




#endif    //USE_OLD_SUBDIV_OPE



#endif
