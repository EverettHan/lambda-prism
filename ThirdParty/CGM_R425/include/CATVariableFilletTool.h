//=============================================================================
// Copyright Dassault Systemes 1997-2011, all rights reserved
//=============================================================================
//
// CATVariableFilletTool:
//
//=============================================================================
// Usage notes:
//=============================================================================
// Jan. 98      Creation (S. Royer)
// Nov. 99  PKC IsToolConstantAtPoint
// Nov. 04      Versionning Interne (E. Malgras)
// 28/04/11 HLN Add SetG2Section()
// 20/10/14 Q48 Implement X-scale in CGM-replay
// 22/04/2021 SME31 Implement GetCutterDimension()
//=============================================================================
#ifndef CATVariableFilletTool_h
#define CATVariableFilletTool_h

#include "Connect.h"

#include "CATConnectTool.h"
#include "CATMathDef.h"
#include "CATMathDiagnostic.h"
#include "CATString.h"
#include "CATCGMStream.h"
#include "CATListOfDouble.h"
#include "CATListOfInt.h"

class CATCurve;
class CATLaw;
class CATTolerance;
class CATMathFunctionX;
class CATMathInterval;
class CATSoftwareConfiguration;
class CATGeoODTScaleManager;
class CATMathSetOfPointsND;

class ExportedByConnect CATVariableFilletTool : public CATConnectTool
   {
   CATCGMVirtualDeclareClass(CATVariableFilletTool);
   public:

      enum ContinuityMode { G0Continuity, G1Continuity };

      CATVariableFilletTool(CATSoftwareConfiguration * iConfig, 
                            CATCurve                 * iSpine, 
                            CATLaw                   * iRadiusLaw, 
                            CATLaw                   * iMappingLaw);

      ~CATVariableFilletTool();

      CATLONG32 GetType() const;
      CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;

      CATCurve * GetSpine() const;

      const CATMathFunctionX * GetRadiusFunction() const;
      const CATLaw * GetRadius() const;
      const CATLaw * GetMapping() const;
      ContinuityMode GetContinuityMode() const;
      void SetContinuityMode( ContinuityMode iContinuityMode );

      CATBoolean IsToolConstantAtPoint(const double iSpineParam) const;
      CATBoolean IsToolConstantOnDomain(double &ioStartParam, double &ioEndParam) const;

      void SetConicalSection(double iConicParameter);

      void SetG2Section();
      CATLONG32 GetSectionType() const;
      double GetConicParameter() const;

      // ----------------------------------------------------------------------------------------------------
      // Renvoie la liste des parametres sur la spine correspondant a des contraintes de la loi de rayon 
      // (i.e. extremites des arcs de la loi de rayon)
      CATBoolean GetSpineParametersAtRadiusConstraints(CATListOfDouble & oSpineParameters);

      CATBoolean ComputeSpineParametersAtRadiusConstraints(CATListOfDouble &oSpineParameters, 
         CATListOfInt &oRadiusConstraintsIndices) const;

      // Renvoie les indices des parametres sur la spine correspondant a des contraintes de la loi de rayon
      // qui encadrent le parametre sur la spine iSpineParam.
      // Si oLowSpineParamIndex=HighSpineParamIndex: iSpineParam correspond a une constrainte et les 
      // indices renvoyes donnent son numero ( 1 <= index <= NumberOfConstraints)
      // Si oLowSpineParamIndex=0: iSpineParam < 1ere contrainte
      // Si oHighSpineParamIndex=0: iSpineParam > Derniere contrainte
      CATBoolean GetRadiusConstraintSpineParametersArc(double iSpineParam,
                                                       CATLONG32 &oLowSpineParamIndex, 
                                                       CATLONG32 &oHighSpineParamIndex);
      // Renvoie l'indice de la contrainte de la loi de rayon (au sens de la CATLaw) correspondant au parametre 
      // sur la spine d'indice iSpineParamIndex 
      // Attention: oRadiusConstraintIndex >= 0 alors que iSpineParameterIndex >= 1
      CATBoolean GetRadiusConstraintIndex(CATLONG32 iSpineParameterIndex, CATLONG32 & oRadiusConstraintIndex);

      // Indique si la loi de rayon est constante sur un arc donne.
      // iRadiusArc correspond a l'arc definie par les contraintes d'indices iRadiusArc-1 et iRadiusArc sur la 
      // de rayon et commence a 1.
      CATBoolean IsRadiusConstantOnArc(const CATLONG32 iRadiusArc) const;

      // Verifie qu'il n'y a pas d'arc correspondant a une zone de rayon variable entre les 2 points donnees en entree
      CATBoolean CheckIfNoRadiusVariationAreaHasBeenSkipped(double iSpineParam1, double iSpineParam2);

      // Met a jour la liste de points donnes en entree de maniere a ce qu'il y ait au moins un point dans chaque arc de 
      // de la loi de rayon. Cette liste de points est definie par des ratios correspondant aux parametres sur la spine par
      // rapport au DeltaParam de l'arc donne en entree.
      void UpdateSamplingForQualityCheck(const CATListOfDouble & iSpineParametersAtRadiusConstraints,
                                         double iSpineParam0, double iSpineParamDeriv0, double iSpineParamSecondDeriv0,
                                         double iSpineParam1, double iSpineParamDeriv1, double iSpineParamSecondDeriv1,
                                         double iDeltaParam,
                                         CATMathSetOfPointsND &ioSetOfRatio) const;

   private:

      CATMathDiagnostic GetSpineParamFromRadiusParam(const CATMathInterval &SpineDomain,
                                                     const double iRadiusParam,
                                                     double & oW,
                                                     const CATTolerance & iTol) const;

      CATBoolean ComputeSpineParametersAtRadiusConstraints();

     /***********************************************************/
      /* AHG :Methods to stream and unstream the tool for the    */
      /* CGMReplay                                               */
      /***********************************************************/
   public:
      static CATString _OperatorId;
      const CATString * GetOperatorId();
      CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
      void WriteInput(CATCGMStream  & ioStream);

      //==============================================================
      // DATA 
      //==============================================================
   private:
      CATLONG32 _SectionType;
      double    _ConicParameter;
      ContinuityMode _ContinuityMode;
      CATCurve  * _Spine;
      CATLaw    * _Radius;
      CATLaw    * _Mapping;
      CATMathFunctionX * _Composition;
      CATListOfDouble _SpineParametersAtRadiusConstraints;
      CATListOfInt    _RadiusConstraintsIndices;

   };

#endif
