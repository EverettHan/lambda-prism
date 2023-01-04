/* Generated from CATTopObjErrors.msg on Fri Jan  9 08:47:16 1998
 */
#ifndef _CATTOPOBJERRORS_INCLUDE
#define _CATTOPOBJERRORS_INCLUDE

// COPYRIGHT DASSAULT SYSTEMES 1999

typedef enum {

   TopObjInputErr_InvalidPointer = 0x00020001u,
 TopObjInputErr_BadCellDimension = 0x00020002u,
TopObjInputErr_BadDomainDimension = 0x00020003u,
TopObjInputErr_CellDimensionTooSmall = 0x00020004u,
TopObjInputErr_CellDimensionTooLarge = 0x00020005u,
 TopObjInputErr_AmbiguousRequest = 0x00020006u,
 TopObjInputErr_InvalidInputType = 0x00020007u,
      TopObjInputErr_NULLElement = 0x00020008u,
   TopObjInputErr_InvalidElement = 0x00020009u,
     TopObjInputErr_EmptyElement = 0x0002000au,
TopObjInputErr_BadOrientationValue = 0x0002000bu,
TopObjInputErr_BadMatterSideValue = 0x0002000cu,
 TopObjInputErr_BadLocationValue = 0x0002000du,
     TopObjInputErr_BadSideValue = 0x0002000eu,
  TopObjInputErr_IndexOutOfRange = 0x0002000fu,
TopObjInputErr_NonCompatibleElement = 0x00020010u,
TopObjInputErr_InvalidElementNonModifiable = 0x00020011u,
TopObjInputErr_NotInitializedIterator = 0x00020012u,
       TopObjInputErr_NoGeometry = 0x00020013u,
       TopObjInputErr_Incomplete = 0x00020014u,

TopObjInternalErr_UnavailableMethod = 0x00020001u,
TopObjInternalErr_ObjectCreationFailed = 0x00020002u,
TopObjInternalErr_InterfaceBindingFailed = 0x00020003u,
TopObjInternalErr_ImplBindingFailed = 0x00020004u,
TopObjInternalErr_InvalidOrderMethodCall = 0x00020005u,
TopObjInternalErr_InvalidObjectType = 0x00020006u,
   TopObjInternalErr_BadTopology = 0x00020007u,
TopObjInternalErr_AllocationProblem = 0x00020008u,
TopObjInternalErr_ImpossibleWriting = 0x00020009u,
TopObjInternalErr_InvalidElementNoSubdVolume = 0x0002000au,
TopObjInternalErr_InvalidElementNoSubdFace = 0x0002000bu,
TopObjInternalErr_InvalidElementNoSubdEdge = 0x0002000cu,
TopObjInternalErr_InvalidElementNoSubdVertex = 0x0002000du

} NewTopologicalObjectsErrors;

#endif
