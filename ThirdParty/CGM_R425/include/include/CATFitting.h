// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATFitting:
// Interface class of the Approximation Operator 
//
//==========================================================================
//
// Usage notes:
//  
//	Convert a set of points into a curve or s a surface
//      Attention !!!!!!!
//      Lors de la Creation en mode Advanced , il FAUT OBLIGATOIREMENT
//      faire un SetDataForms , puis des SetForm .
//
//========================================================================== 
// December. 97     Creation                  cen-nld
//========================================================================== 



/*****************************************************************************
 
   NE PLUS UTILISER - UTILISER CATLISS - NE PLUS UTILISER - UTILISER CATLISS

  ATTENTION  !!! L'ERREUR ENVOYEE est de type MATHEMATIQUE ( pb de sepration de modules )
 
*******************************************************************************/

#ifndef CATFitting_H
#define CATFitting_H

#include "CATGMOperatorsInterfaces.h"
#include "CATCGMVirtual.h"

#include "CATMathDef.h"
#include "CreateFitting.h"

class CATFrFNurbsMultiForm;
class CATMathFunctionX;
class CATNurbsSurface;
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATFitting : public CATCGMVirtual
{
  public :

    virtual ~CATFitting();

    virtual void Run()=0;
//
//  	Input structure : Points
//
/*-----------------------------------------------------------------------------
   nform est le nombre total de formes prises en compte
   nbforef est le nombre de formes de reference:
   Ces formes peuvent etre soit :
   - de reference et a lisser
   - de reference uniquement
  Le nombre total de formes effectivement lissees est donc 
  nbform - nbforef <= nbformes lissees <= nbform
  nbpt est le nombre de points par forme
----------------------------------------------------------------------------- */
   
     virtual void SetDataForms(int nbform,int nbpt,int nbforef)=0;
     
/*-----------------------------------------------------------------------------
   IFormNumber est le numero de sa forme ( et non son indice )
   IFormNumber >= 1
   iytp est le type de cette forme :
   Si ityp = 0 -> juste a lisser
   Si ityp = 1 -> de reference et a lisser 
   Si ityp = 2 -> uniquement de reference 

   Il faut ajouter la forme de reference qui ne serait pas a lisser a la fin
----------------------------------------------------------------------------- */
          
     virtual void SetForm(CATLONG32 iFormNumber ,CATMathSetOfPointsNDTwoTangents &Pt,CATLONG32 ityp)=0;

/*----------------------------------------------------------------------------
  Dimension des points a lisser                
----------------------------------------------------------------------------- */                        
    virtual void SetDimension(int dim)=0;
//
//  	Set options
//
/*-----------------------------------------------------------------------------
  Le premier double * est la tangente extremite 1 
  Le second double * est la tangente extremite 2
  si on recoit un pointeur null , alors on considere que la tangente ne doit pas etre
  imposee 
----------------------------------------------------------------------------- */
 
     virtual void SetTangencyCondition(CATLONG32 iFormNumber,double * tg1 ,double * tg2)=0;

/*-----------------------------------------------------------------------------
  iNbOfRanks est le nombre d'impositions molles 
  iRank est la liste des rangs demandes
  iContinuityOrder est la liste de la continuite demandee en chaque iRank
  avec    0->C0
	  1->C1
	  2->C2	
----------------------------------------------------------------------------- */
    virtual void SetSoftContinuity(int INbOfRanks,int *iRank,int *iContinuityOrder)=0;

/*-----------------------------------------------------------------------------
  Si cette option est activee , les seules limites d'arcs sont celles demandees
  par le biais des impositions molles 
----------------------------------------------------------------------------- */
    virtual void SetTwinOption()=0;

    virtual void SetDegree(CATLONG32 degree)=0;

    virtual void SetMaxNumberOfArcs(CATLONG32 iNbArc) = 0;

    virtual void SetImposedParametrization(double *iParameter)=0;

    virtual void SetFreeParametrization()=0;
    virtual void SetSmoothingFactor(double iSmoothingFactor)=0;

//
//	Get Results
//	
/*-----------------------------------------------------------------------------
  La method GetResult rend un pointeur a detruire une fois les operations
  terminees .
-----------------------------------------------------------------------------*/
    virtual CATFrFNurbsMultiForm *GetResult()=0;
    virtual CATMathFunctionX *GetResultAsFunction()=0;
	
//
//	Get Additional Informations on Result
//	
    virtual double * GetParameters()=0;
    virtual double   GetMaxDeviation()=0;
    virtual int      GetMaxDevRank()=0;
	
};
#endif


