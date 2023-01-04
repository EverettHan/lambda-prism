// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATFrFExtrapolNurbsSur
// 
//==========================================================================
//
// Usage notes:
//
//========================================================================== 

// Oct. 2000     interface/implementation                    

//========================================================================== 
#ifndef CATFrFExtrapolNurbsSur_H
#define CATFrFExtrapolNurbsSur_H

#include "CATGMOperatorsInterfaces.h"
#include "CATCGMVirtual.h"

class CATGeoFactory;
class CATNurbsSurface;
class CATMathVector;
class CATSurParam;

class CATMathPoint;
class CATMathVector;
class CATSoftwareConfiguration;


enum CATSurfaceSide { SideUMin=1, SideUMax, SideVMin, SideVMax };
                      ;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATFrFExtrapolNurbsSur : public CATCGMVirtual
{
  public :
  
  //-------------------  Destructeurs ------------------------- 
   ~CATFrFExtrapolNurbsSur();
  
  //-------------------  Methodes a la demande  ------------------------- 
  

  // * Gestion de la longueur effective d'extrapolation
  //   Dans le cas ou cette derniere longueur excederait la EstimatedMaxLength => on update cette derniere 
  //   ainsi que la surface de travail interne
  //
  // *  Methode 1: on donne la longueur (calculee sur un iso milieu ?)
   virtual void SetExtrapolationLength (const double TrueExtrapolationLength)=0;

  //------------------- Acces aux resultats -------------------
  // les donnees de la surfaces ioSur sont modifiees 
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
  virtual CATNurbsSurface* GetResult()=0;

};

//--------------------------------
// first global creation function :je me suis alignes sur ExtrapolSurface , si c'est pas bon 
// a toi de jouer 
// A la creation de l'operateur on balance une longueur d'extrapolation assez grande de maniere a pouvoir 
// generer en interne une surface de reference 
// La methode SetExtrapolationLength permet elle de preciser exactement la longueur d'extrapolation voulue 
// On peut ainsi iterer a moindres frais 

////- iSurfaceToExtrapolate est la surface a extrapoler.
  //- iSurfaceSide indique sur quel(s) bord(s) de la surface se trouve le
  //  point iStart (afin d'eviter des tests numeriques en parametres). 
  //  Convention : 0 = none, 1 = Umin, 2 = Umax, 3 = Vmin, 4 = Vmax 
  //  (c'est DPS qui a pris cette convention pour l'homotopie). 
  //  Il y a les flags pour les diagonales en plus.
  //-----------------------------------------------------------------------

ExportedByCATGMOperatorsInterfaces 
CATFrFExtrapolNurbsSur * CATCreateFrFExtrapolNurbsSur( CATGeoFactory             * iFactory,
                                                       CATSoftwareConfiguration  * iConfig,
                                                       CATNurbsSurface           * ioSur,
                                                       CATSurParam               * iStartParam,
                                                       const CATSurfaceSide        iSurfaceSide, 
                                                       const double                iEstimatedMaxLength);


//Do not use anymore. Use previous create instead
ExportedByCATGMOperatorsInterfaces 
CATFrFExtrapolNurbsSur *    CreateFrFExtrapolNurbsSur( CATGeoFactory             * iFactory,

                                                       CATNurbsSurface            * ioSur,
                                                       CATSurParam                * iStartParam,
                                                       const CATSurfaceSide         iSurfaceSide, 
                                                       const double                 iEstimatedMaxLength);

#endif








