/* -*-c++-*- */
#ifndef CATCGMLimitsManagement_H
#define CATCGMLimitsManagement_H
// COPYRIGHT DASSAULT SYSTEMES  2002
//============================================================================
//  Determine le mode de gestion d'un objet parametrique Curve/Surface
//============================================================================
typedef unsigned int CATCGMLimitsManagement;

// Par default aucune specificite n'est defini sur une Curve/Surface
#define CATCGMLimitsManagement_Default                          0x00000000

// MaxLimits are dynamically computed (from GeometricRep)
#define CATCGMLimitsManagement_DynamicMaxLimits                 0x00000001

// Curve/Surface is specified with original limits to take into account
#define CATCGMLimitsManagement_OriginalLimits                   0x00000002

// Curve/Surface holding KnotVector (core of extrapolation)
#define CATCGMLimitsManagement_HoldingKnotVector                0x00000004

// Curve/Surface Not Unextrapolable
#define CATCGMLimitsManagement_NotUnextrapolable                0x00000008

//  Curve/Surface certified as Okay for Propagation of Analysis
//  If Not Okay, direct dependancies are ForceMaxLimits 
#define CATCGMLimitsManagement_Certified_PropagationOfLimits    0x00000010

//  Curve/Surface certified as Okay for unextrapolate
//  It means analysis and action of unextrapolation 
#define CATCGMLimitsManagement_Certified_Unextrapolable         0x00000020


//   EdgeCurve / FilletSurface
//  requiert une validation posterieurement a l'analyse
//  pour conforter la validite de l'analyse
#define CATCGMLimitsManagement_NeedValidationOfAnalysis         0x00000040

//   Loop (boite UV)
//  revelation sur la necessite d'une Mise a Jour 
//  suite a des actions de desextrapolations
#define CATCGMLimitsManagement_NeedUpdateAfterUnextrapolate     0x00000080


enum CATCGMLimitsRequest 
{
  CatCGMLimitsRequest_AnalysisValidation       = +1, 
  CatCGMLimitsRequest_UpdateAfterUnextrapolate = +2
};

enum CATCGMLimits_DisableCGMObjectType
{
  CATCGMLimits_DisableCGMObjectType_None		= 0x00000000,	// All CGM Objects Type are checked for their Limits
  CATCGMLimits_DisableCGMObjectType_Curve		= 0x00000001,			// DisdabType are checked for their Limits
  // Add here other flags ..
};

#endif
