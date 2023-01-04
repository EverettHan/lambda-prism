#ifndef CATBlendBuildMode_h_
#define CATBlendBuildMode_h_

// COPYRIGHT DASSAULT SYSTEMES 2006 

/**
* @CAA2Level L1
* @CAA2Usage U1
*/ 

/**
* Defines the mode of creation of the blend surface.	
* @param GeometricBlendMode
* The blend surface is computed by tracing (or marching) the solution 
* along the wire.
* @param AnalyticBlendMode
* Analytical mode: the control points of the wire are taken to build the blend surface.
*/
enum CATBlendBuildMode {GeometricBlendMode,AnalyticBlendMode};

#endif /* CATBlendBuildMode_h_ */
