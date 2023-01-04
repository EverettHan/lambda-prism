/* -*-C++-*- */

#ifndef CATSlotManifoldCreator_H
#define CATSlotManifoldCreator_H

// COPYRIGHT DASSAULT SYSTEMES 2012

//=============================================================================
//=============================================================================
//
// CATSlotManifoldCreator : Agent de creation/reconnaissance des Slots.
//
//=============================================================================

//=============================================================================
// Sep  2012  Creation                                                    PRL
//
// Responsible is PRL, do not modify without permission
//
//=============================================================================
//=============================================================================

// Derivation
#include "CATExtrusionManifoldCreatorBase.h"

// DReps, agents
#include "CATDeclarativeManifoldAgent.h"
#include "CATCellManifoldGroupOperator.h"

// Primitives
#include "ListPOfCATGMLiveExtrusionPrimitive.h"
#include "CATGMLiveExtrusionPrimitivesContainer.h"

// Infra
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"

// Operateurs
class CATFaceAnalyzer;


class ExportedByPersistentCell CATSlotManifoldCreator : public CATExtrusionManifoldCreatorBase
{
public: 
//===========================================================================================================

  CATCGMDeclareManifoldAgent(CATSlotManifoldCreator, CATDeclarativeManifoldAgent); // Decl attribut + alloc pool

  //------------------------------------------------------------------------------
  // Ctor/Dtor
  //------------------------------------------------------------------------------     
  CATSlotManifoldCreator();
  CATSlotManifoldCreator(CATGMLiveExtrusionPrimitivesContainer * iExtrusionContainer);
	
	virtual ~CATSlotManifoldCreator();

  //------------------------------------------------------------------------------
  // Methodes issues de la classe mere, reprises telles quelles + GetAs
  // Non virtuelles, pas de derivation voulue pour les slots aujourd'hui.
  //------------------------------------------------------------------------------     
  int     GetPriority();
  HRESULT CreateImageManifolds();

  INLINE  CATDeclarativeManifoldAgent* Clone();
  INLINE  CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  
  CATSlotManifoldCreator* GetAsSlotManifoldCreator();


protected:
//===========================================================================================================

  //------------------------------------------------------------------------------
  // Methode qui va peut-etre disparaitre: aujourd'hui on appelle juste la mere
  //------------------------------------------------------------------------------     
  HRESULT BuildExtrusionPrimitiveSets(CATBody                               & iInputBody,
                                      ListPOfCATFace                        & ioFacesToBeRecognized,
                                      CATGMLiveExtrusionPrimitivesContainer & ioExtrusionPrimitivesContainer);

  //------------------------------------------------------------------------------
  // Identification + typage d'un slot a partir d'une primitive d'extrusion  
  //------------------------------------------------------------------------------     
  HRESULT IdentifySlotFeature        (CATBody                               & iInputBody, 
	                                    CATGMLiveExtrusionPrimitive           * iExtrusionPrimitive);

  HRESULT CreateSlotCMGroup          (CATCellManifoldGroupOperator          * iCMGroupOperator,
                                      CATLiveBody                           * iInputLiveBody,
                                      CATGMLiveExtrusionPrimitive           * iExtrusionPrimitive);

private:
//===========================================================================================================

  //------------------------------------------------------------------------------
  // Corps des fonctions precedentes 
  //------------------------------------------------------------------------------     
  void CreateImageManifolds_c        (int                                   & oNbPrimitives, 
                                      int                                   & oNbRecogPrims);

  void IdentifySlotFeature_c         (CATBody                               & iInputBody, 
	                                    CATGMLiveExtrusionPrimitive           * iExtrusionPrimitive,
                                      CATBoolean                            & oIsASlot);

  void CreateSlotCMGroup_c           (CATCellManifoldGroupOperator          * iCMGroupOperator,
                                      CATLiveBody                           * iInputLiveBody,
                                      CATGMLiveExtrusionPrimitive           * iExtrusionPrimitive,
                                      CATBoolean                            & oGroupHasBeenCreated);
  
  //------------------------------------------------------------------------------
  // Services de IdentifySlotFeature_c
  //------------------------------------------------------------------------------     
  void IdentifySlot_PlnCase          (ListPOfCATCellManifold                & iCMFs, 
                                      CATBoolean                            & oIsASlot);

  void IdentifySlot_CylCase          (ListPOfCATCellManifold                & iCMFs, 
                                      CATBoolean                            & oIsASlot);

  void IdentifySlot_TtgCase          (ListPOfCATCellManifold                & iCMFs, 
                                      CATBoolean                            & oIsASlot);
 

  //------------------------------------------------------------------------------
  // Utilitaire pour la migration des primitives d'extrusion
  //------------------------------------------------------------------------------     
  void SortAdjFaceLists              (CATGMLiveExtrusionPrimitive           * iExtrusionPrimitive,
                                      CATBoolean                            & oSlotConfig,
                                      ListPOfCATFace                        & oSupportFaces,
                                      ListPOfCATFace                        & oSupportDecoFaces,
                                      ListPOfCATFace                        & oExitFaces,
                                      ListPOfCATFace                        & oExitDecoFaces,
                                      ListPOfCATFace                        & oClogFaces,
                                      ListPOfCATFace                        & oClogDecoFaces,
                                      int                                   & oClogPos); // 0: pas de clog, 1: clog en 1ere pos, 2: clog en 2nde pos

private:
//===========================================================================================================

  // MLKs
  CATCellManifoldGroupOperator*      _CMGroupOper;

  // Tolerances
  CATAngle                           _TolAg;

  // Use with caution (Donnees de travail: pour eviter de modifier les signatures... )
  short                              _CurBlindType;    
  short                              _CurDeclaType;    
  double                             _CurWidth;
  double                             _CurLength;

  // Operateurs
  CATFaceAnalyzer                   *_FacAnalyzer;     

  // Versionning
  CATGeoFactory*                     _GeoFac;
  CATSoftwareConfiguration*          _Config;
  short                              _CGMLevel;

  //------------------------------------------------------------------------------
  // Juste pour eviter que le compilo ne definisse par lui-meme ces operateurs
  //------------------------------------------------------------------------------  
  CATSlotManifoldCreator(CATSlotManifoldCreator& iObj);
  CATSlotManifoldCreator& operator=(const CATSlotManifoldCreator & iObj);

};

// Methodes INLINE
//===========================================================================================================

INLINE CATDeclarativeManifoldAgent* CATSlotManifoldCreator::Clone()
{
  //return new CATSlotManifoldCreator();
  return NULL; 
}

INLINE CATBoolean CATSlotManifoldCreator::IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold()
{
  return TRUE; // pour ne pas se singulariser ...
}

#endif


// Ne rien ecrire sous cette ligne
//===========================================================================================================

