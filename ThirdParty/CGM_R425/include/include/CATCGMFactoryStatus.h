/* -*-c++-*- */
#ifndef CATCGMFactoryStatus_H
#define CATCGMFactoryStatus_H
// COPYRIGHT DASSAULT SYSTEMES  2002
//============================================================================
//  Detection d'operation singuliere sur la Factory
//  Utilisation de technologies recentes (pour remontee RCA)
//============================================================================

enum CATCGMFactoryStatus
{
  CatCGMFactoryStatus_C1                           = 0x00000001,

  CatCGMFactoryStatus_LightDesignMode              = 0x00000002,

  CatCGMFactoryStatus_WithGeometryInjection        = 0x00000004,

  CatCGMFactoryStatus_Cleaned_FatVertex            = 0x00000008,

  CatCGMFactoryStatus_Cleaned_FatEdge              = 0x00000010,

  CatCGMFactoryStatus_Cleaned_FatExtrapol          = 0x00000020,

  CatCGMFactoryStatus_TopologicalPropagateHiddenSeam = 0x00000040,

  CatCGMFactoryStatus_TopologicalPropagateImprintAttribute = 0x00000080
};


#endif
