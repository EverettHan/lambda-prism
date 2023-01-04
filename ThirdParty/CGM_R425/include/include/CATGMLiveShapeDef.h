#ifndef CATGMLiveShapeDef_H
#define CATGMLiveShapeDef_H

// ----------------------------------------------------------------------------
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// Do not use outside CGM. This file is only for CGM developpers.
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// ----------------------------------------------------------------------------
// CATManifoldParameters Keys
// ----------------------------------------------------------------------------

#include "CATTopDef.h"

// Bone Fillet Parameters Keys
// ------------
#define BoneFilletRadiusKey 0  

// Cylinder manifold Parameters Keys
// ------------
#define CylinderManifoldRadiusKey 1  
#define CylinderManifoldAxisKey 2     

// Sphere manifold Parameters Keys
// ------------
#define SphereManifoldRadiusKey 3   
#define SphereManifoldAxisKey 4    

// Plane manifold Parameters Keys
// ------------
#define PlaneManifoldOffsetKey 5   
#define PlaneManifoldPlaneKey 6   

//Bone Chamfer Parameters Keys
//---------------------------
#define BoneChamferDistance1Key 7
#define BoneChamferDistance2Key 8
#define BoneChamferChordKey 9
#define BoneChamferAngle1Key 10
#define BoneChamferTypeKey 11
#define BoneChamferSwitchSupportKey 30
//Pattern Editor Parameters Keys
//---------------------------
#define PatternNumberOfInstancesKey 12
#define PatternTransfoVectorKey 13
#define PatternOriginPointKey 14
#define PatternRotationAngleKey 15
#define PatternRotationAxisKey 16
#define PatternActivationInstanceKey 17
#define PatternCompleteKey 18
#define PatternSecondaryTransfoKey 19
#define PatternReferenceKey 20

//More Bone Chamfer Parameters Keys
//---------------------------
#define BoneChamferAngle2Key 21

// Bone Fillet Parameters Keys
// ---------------------------
#define BoneFilletHRadiusKey 22
#define BoneFilletRadiusTypeKey 24
#define BoneFilletSectionTypeKey 25

// HVertex Parameters Keys
// -----------------------
#define HVertexRatioKey 26
#define HVertexDistanceKey 27

// Cone manifold Parameters Keys
// ------------

// Torus manifold Parameters Keys
// ------------

// Offset manifold Parameters Keys
// ------------
#define OffsetValueKey 28
#define OffsetGlobalValueKey 29

// Feature Type parameter Keys
// ------------
#define FeatureTypeKey 31
#define FeatureTypeForbiddenKey 32

// Draft manifold Parameter keys
#define DraftAngleKey 33
#define DraftPullingDirKey 34

// Button manifold Parameter keys
#define ButtonSphereRadiusKey 35
#define ButtonHeightKey 36

// Patter transfo edition - (will replace PatternTransfoVectorKey)
#define PatternUnitaryTransfoKey 37

// For Constraint on DREp
#define ConstraintOnDRepKey 38

// Keep Top for TMC (Advanced Stamp technology)
#define KeepTop1Key 39
#define KeepTop2Key 40

// ------------
#define ManifoldParameterKeyCount 42 // Please Maintain this value to the highest + 2 (due to the initialization at 0)
// ------------


// ------------
// IZE Another list of Defines is the exposed Feature types for Redeclaration
#define UndefFeatureType          0  
#define DatumFeatureType          1  
#define CanonicFeatureType        2  
#define BoneFilletFeatureType     3 
#define JointFilletFeatureType    4 
#define ChamferFeatureType        5
#define ButtonManifoldFeatureType 6

enum {
  MANIFOLDPARAMETER_HASNOTCHANGED = 0,
  MANIFOLDPARAMETER_HASCHANGED_USER,
  MANIFOLDPARAMETER_HASCHANGED_SYSTEM,
  MANIFOLDPARAMETER_HASCHANGED_SIMILAR,
};

#endif


