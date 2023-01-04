#ifndef CATTopBlendBehaviour_Mode_h_
#define CATTopBlendBehaviour_Mode_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
* Not to be used.	
*/

enum CATTopBlendBehaviour_Mode
{
  CATTopBlendBehaviour_AllDefaultBehaviour                     = 0,  // Reset to defaut
  CATTopBlendBehaviour_TopologicalDefaultOrientation           ,     // GetDefaultWireOrientation uses Topological Information
  CATTopBlendBehaviour_GeometricalDefaultOrientation           ,     // GetDefaultWireOrientation uses Geometrical Information
  CATTopBlendBehaviour_AutorizeNonG0ConstraintOnMonoPCurveWire       // FSS only : No Journal :    
//CATTopBlendBehaviour_PlanarSurfacesDetection                       // see SetPlanesDetection()          on internal interface (DS only)           ,
//CATTopBlendBehaviour_CanonicSurfacesDetection                      // see SetCanonicSurfacesDetection() on internal interface (DS only)        
};

#endif /* CATTopBlendBehaviour_Mode_h_ */
