#ifndef CATPGMCreateSplitBySkin_h_
#define CATPGMCreateSplitBySkin_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"

class CATBody;
class CATGeoFactory;
class CATPlane;
class CATSurLimits;
class CATSurface;
class CATTopData;
class CATIPGMTopSplitBySkin;



/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopSplitBySkin *CATPGMCreateSplitBySkin(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iSolidBody,
  CATPlane *iInfinitePlane);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopSplitBySkin *CATPGMCreateSplitBySkin(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iSolidBody,
  CATSurface *iSurface,
  CATSurLimits *iSurLimits = (CATSurLimits*)0);

//--------------------------------------------------------------------------
//
// Methode: CATPGMCreateSplitBySkin
//
// Auteurs: EDS        Date: 25/07/2001
//
// Description: 
//   Creation d'une instance de l'operateur de split d'un body solide par
//   un body surfacique. L'element surfacique coupant est soit un body
//   multi-shells (iSkinBody), soit un plan considere infini (iInfinitePlane).
//   
//   Le mode de selection des parties a conserver pour constituer le 
//   resultat est specifiable par le biais de methodes sur l'operateur.
//
//   L'operateur cree est MULTI-RUN, c'est a dire que la methode Run() et la
//   methode GetJournal() associee peuvent etre appelees plusieus fois, 
//   notamment avec des options de selection differentes. Seules les 
//   mthodes de construction du resultat sont appelees systematiquement,
//   la decoupe mutuelle des deux bodys etant effectuee une seule fois.
//   
//   En mode (solide+skin), le cote conserve n'est pas defini a priori 
//   (il est donc necessaire de le specifier via SetSelectionSide) en 
//   revanche, le mode de selection des lumps non decoupes est KEEP par 
//   defaut (utiliser SetSelectionMode pour le modifier). 
//
//   En mode (solide+plan), le cote conserve n'est pas defini a priori 
//   (il est donc necessaire de le specifier via SetSelectionSide) en 
//   revanche, le mode de selection des lumps non decoupes est PositionVsPlane
//   (il n'est pas possible de le le modifier).
//
//   ==============================================================================
//   =  SelectionMode  = SelectionSide = iSolidBody = iSolidBody =   iSolidBody   =
//   =                 =               = iSkinBody  =  iSurface  = iInfinitePlane =
//   ==============================================================================
//   =                 =  UnderSkin    =            =            =                =
//   =     Keep        =  OverSkin     =      X     =      X     =                =
//   ==============================================================================
//   =                 =  UnderSkin    =            =            =                =
//   =    Remove       =  OverSkin     =      X     =      X     =                =
//   ==============================================================================
//   =                 =  UnderSkin    =            =            =                =
//   = PositionVsPlane =  OverSkin     =            =            =        X       =
//   ==============================================================================
//
//   Cf. CATTopSplitBySkin.h
//
// Arguments:
//   iFactory              Container geometrique de iSolidBody et de iSkinBody
//   iTopData              Configuration pour le versionning + journaling
//   iSolidBody            Body multi-lumps a decouper
//                         (tous les domaines doivent etre des lumps)
//   iSkinBody             Body multi-shells coupant le(s) solide(s)
//                         (tous les domaines doivent etre des shells)
//   iInfinitePlane        Plan de decoupe
//   iSuface               Surface de decoupe
//   iSurLimits            Limites considerees pour iSurface
//
// Retour:
//     Pointeur sur une instance d'operateur topologique
//   
//--------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopSplitBySkin *CATPGMCreateSplitBySkin(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iSolidBody,
  CATBody *iSkinBody);

#endif /* CATPGMCreateSplitBySkin_h_ */
