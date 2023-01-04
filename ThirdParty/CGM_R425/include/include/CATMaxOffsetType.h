/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
// CATMaxOffsetType :
//=============================================================================
//=============================================================================
// Oct 03  Creation                          AAD OAU
//=============================================================================
#ifndef CATMaxOffsetType_H
#define CATMaxOffsetType_H


typedef enum 
{
  CATMXOFF_NOTSET=0,
  CATMXOFF_SINGULAR,
  CATMXOFF_FINITE,
  CATMXOFF_INFINITE
} CATThresholdType;

typedef enum
{
  CATMXOFF_RUNU = 1,
  CATMXOFF_RUNV
} CATProfileType;

typedef enum
{
	CATMXOFF_NEG=1,
	CATMXOFF_POS,
	CATMXOFF_BOTH
} CATMaxOffsetRunOption;

typedef enum
{
  CATMXOFF_PlaneType,
  CATMXOFF_SphereType,
  CATMXOFF_CylinderType,
  CATMXOFF_ConeType,
  CATMXOFF_TorusType,
  CATMXOFF_ProcOffsetSurfaceType,
  CATMXOFF_TabulatedCylinderType,
  CATMXOFF_RevolutionSurfaceType,
  CATMXOFF_GenericFilletType,
  CATMXOFF_GenericRuledSurfaceType,
  CATMXOFF_NoCanonicalType
} CATGeometricRepType;

#endif

