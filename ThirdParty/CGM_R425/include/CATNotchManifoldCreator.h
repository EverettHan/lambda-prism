/* -*-C++-*- */

#ifndef CATNotchManifoldCreator_H
#define CATNotchManifoldCreator_H

// COPYRIGHT DASSAULT SYSTEMES 2012

//=============================================================================
//=============================================================================
//
// CATNotchManifoldCreator : Agent de creation/reconnaissance des Notches.
//
//=============================================================================

//=============================================================================
// Sep  2012  Creation                                                    PRL
// Nov  2016  Modification sans prévenir et buggee                        I49
// Jul  2017  Remise au carre/bugs introduits                             PRL
//
// Responsible is PRL, do not modify without permission
//
//=============================================================================
//=============================================================================

// Derivation
#include "CATExtrusionManifoldCreatorBase.h"

// Autres
#include "PersistentCell.h"
//#include "CATMathInline.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"
#include "CATDeclarativeManifoldAgent.h"
#include "CATCellManifoldGroupOperator.h"
#include "ListPOfCATGMLiveExtrusionPrimitive.h"
#include "CATGMLiveExtrusionPrimitivesContainer.h"
#include "CATCellManifoldNotchNavigatorInterface.h"

class ExportedByPersistentCell CATNotchManifoldCreator : public CATExtrusionManifoldCreatorBase
{
public: 
//===========================================================================================================

  CATCGMDeclareManifoldAgent(CATNotchManifoldCreator, CATDeclarativeManifoldAgent); // Decl attribut + alloc pool

  //------------------------------------------------------------------------------
  // Ctor/Dtor
  //------------------------------------------------------------------------------     
  CATNotchManifoldCreator();
  CATNotchManifoldCreator(CATGMLiveExtrusionPrimitivesContainer * iExtrusionContainer);
	
	virtual ~CATNotchManifoldCreator();

  //------------------------------------------------------------------------------
  // Methodes issues de la classe mere, reprises telles quelles
  // Non virtuelles, pas de derivation voulue pour les Notches aujourd'hui.
  //------------------------------------------------------------------------------     
  int     GetPriority();
  HRESULT CreateImageManifolds();

  INLINE  CATDeclarativeManifoldAgent* Clone();
  INLINE  CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();

  CATNotchManifoldCreator* GetAsNotchManifoldCreator();


protected:
//===========================================================================================================

  //------------------------------------------------------------------------------
  // Methode qui va peut-etre disparaitre: aujourd'hui on appelle juste la mere
  //------------------------------------------------------------------------------     
  HRESULT BuildExtrusionPrimitiveSets(CATBody                               & iInputBody,
                                      ListPOfCATFace                        & ioFacesToBeRecognized,
                                      CATGMLiveExtrusionPrimitivesContainer & ioExtrusionPrimitivesContainer);

  //------------------------------------------------------------------------------
  // Identification + typage d'un Notch a partir d'une primitive d'extrusion  
  //------------------------------------------------------------------------------     
  HRESULT IdentifyNotchFeature       (CATBody                               & iInputBody, 
	                                    CATGMLiveExtrusionPrimitive           * iExtrusionPrimitive);

  HRESULT CreateNotchCMGroup         (CATCellManifoldGroupOperator          * iCMGroupOperator,
                                      CATLiveBody                           * iInputLiveBody,
                                      CATGMLiveExtrusionPrimitive           * iExtrusionPrimitive);

private:
//===========================================================================================================

  //------------------------------------------------------------------------------
  // Corps des fonctions precedentes 
  //------------------------------------------------------------------------------     
  void CreateImageManifolds_c        (int                                   & oNbPrimitives, 
                                      int                                   & oNbRecogPrims);

  void IdentifyNotchFeature_c        (CATBody                               & iInputBody, 
	                                    CATGMLiveExtrusionPrimitive           * iExtrusionPrimitive,
                                      CATBoolean                            & oIsANotch);

  void CreateNotchCMGroup_c          (CATCellManifoldGroupOperator          * iCMGroupOperator,
                                      CATLiveBody                           * iInputLiveBody,
                                      CATGMLiveExtrusionPrimitive           * iExtrusionPrimitive,
                                      CATBoolean                            & oGroupHasBeenCreated);

  //------------------------------------------------------------------------------
  // Modification intempestive et buggee qu'on doit garder pour le versionning :-((((
  // Suite discussion RR 28/08/2017: on ne conserve pas l'ancienne version, 
  //  car on n'est pas dans un feature qui s'update
  //------------------------------------------------------------------------------     
  //void Identify_UnauthorizedPoorDesign   (CATBody                            & iInputBody, 
	//                                        CATGMLiveExtrusionPrimitive        * iExtrusionPrimitive,
  //                                        CATBoolean                         & oIsANotch);

  //------------------------------------------------------------------------------
  // Utilitaire pour la migration des primitives d'extrusion
  //------------------------------------------------------------------------------     
  void SortAdjFaceLists              (CATGMLiveExtrusionPrimitive           * iExtrusionPrimitive,
                                      CATBoolean                            & oNotchConfig,
                                      ListPOfCATFace                        & oSupportFaces,
                                      ListPOfCATFace                        & oSupportDecoFaces,
                                      ListPOfCATFace                        & oExitFaces,
                                      ListPOfCATFace                        & oExitDecoFaces,
                                      ListPOfCATFace                        & oClogFaces,
                                      ListPOfCATFace                        & oClogDecoFaces);

private:
//===========================================================================================================

  // MLKs
  CATCellManifoldGroupOperator*      _CMGroupOper;

  // Versionning
  CATGeoFactory*                     _GeoFac;
  CATSoftwareConfiguration*          _Config;
  short                              _CGMLevel;

  // temporary cached data 
  CATCellManifoldNotchNavigatorInterface::EndWallType                      _CurEndWallType;
};

// Methodes INLINE
//===========================================================================================================

INLINE CATDeclarativeManifoldAgent* CATNotchManifoldCreator::Clone()
{
  //return new CATNotchManifoldCreator();
  return NULL; 
}

INLINE CATBoolean CATNotchManifoldCreator::IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold()
{
  return TRUE; // pour ne pas se singulariser ...
}

#endif


// Ne rien ecrire sous cette ligne
//===========================================================================================================

