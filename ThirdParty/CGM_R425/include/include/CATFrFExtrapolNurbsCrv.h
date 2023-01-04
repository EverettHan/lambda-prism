// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATFrFExtrapolNurbsCrv
// 
//==========================================================================
//
// Usage notes:
//
//========================================================================== 

// Oct. 2000     interface/implementation                    

//========================================================================== 
#ifndef CATFrFExtrapolNurbsCrv_H
#define CATFrFExtrapolNurbsCrv_H

#include "CATGMOperatorsInterfaces.h"
#include "CATCGMVirtual.h"

class CATGeoFactory;

class CATMathVector;
class CATCrvParam;

class CATMathPoint;
class CATMathVector;
class CATNurbsCurve;
class CATSoftwareConfiguration;

enum CATCurveSide { SideLeft=1, SideRight=2};
                      ;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATFrFExtrapolNurbsCrv : public CATCGMVirtual
{
  public :
  
  //-----------------------------------------------------------------------


  //-------------------  Destructeurs ------------------------- 
   virtual ~CATFrFExtrapolNurbsCrv();
  
  //-------------------  Methodes a la demande  ------------------------- 
  

  // * Gestion de la longueur effective d'extrapolation
  //   Dans le cas ou cette derniere longueur excederait la EstimatedMaxLength => on update cette derniere 
  //   ainsi que la surface de travail interne
  //
  // *  Methode 1: on donne la longueur 
   virtual void SetExtrapolationLength (const double TrueExtrapolationLength)=0;

/*
  // *  Methode 2: la longueur sera donnee par le point de projection sur la surface de travail 
   virtual void SetExtrapolationLength(CATMathPoint *iPointToProject)=0;
*/
  //------------------- Acces aux resultats -------------------
  // En mode Replace :les donnees de la courbe  ioCrv sont modifiees 
  // * Dans tous les cas elle se retrouve " Desextrapoleee " au sens du modele 
  // * on realise les activeSplit qu'il faut pour respecter les sens et les taux d'extrapolation 
   virtual void Run() = 0;

  // * Gestion de la symetrie (extrapolation des deux cotes opposes simultanement)
   virtual void ActiveSymetryMode()=0;
   virtual void NonActiveSymetryMode()=0;

  // * Gestion de la dupplication 
   virtual void ActiveDupplicateMode()=0;

  // * Gestion du mode replace  
   virtual void ActiveReplaceMode()=0;

  // * Obtention du resultat  
  virtual CATNurbsCurve * GetResult()=0;

};

//--------------------------------
// first global creation function :je me suis aligne sur ExtrapolSurface , si c'est pas bon 
// a toi de jouer 
// StartLimits indique le domaine de parametrisation initial : a peaufiner peut etre 
//-----------------------------------------------------------------------
 ExportedByCATGMOperatorsInterfaces CATFrFExtrapolNurbsCrv* 
 CATCreateFrFExtrapolNurbsCrv (CATGeoFactory *iFactory,
                               CATSoftwareConfiguration * iConfig,
                               CATNurbsCurve   * ioCrv,
                               CATCrvParam  *iStartParam,
                               const CATCurveSide iCurveSide, 
                               const double iEstimatedMaxLength);

//Do not use anymore. Use previous create instead
ExportedByCATGMOperatorsInterfaces CATFrFExtrapolNurbsCrv* 
 CreateFrFExtrapolNurbsCrv (CATGeoFactory *iFactory,
		                    CATNurbsCurve   * ioCrv,
                            CATCrvParam  *iStartParam,
                            const CATCurveSide iCurveSide, 
                            const double iEstimatedMaxLength);
			              
#endif








