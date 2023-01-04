#ifndef CATTopBlendCouplingMode_h_
#define CATTopBlendCouplingMode_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

/**
 * Coupling modes.
 * @param CATTopBlendCouplingMode_DomainG0
 * Standard coupling: by curvilinear length.
 * @param CATTopBlendCouplingMode_DomainG1
 * G1 coupling: in each domain, coupling of the vertices of G0 and
 * not G1 continuity.
 * @param CATTopBlendCouplingMode_DomainG2
 * G1 and then G2 coupling: after a G1 coupling, the
 * G2 coupling is done (vertices of G1 and not G2 continuity) in
 * each domain defined by the G1 coupling.
 * @param CATTopBlendCouplingMode_Edge
 * Vertex coupling: coupling is carried out edge-by-edge. You must 
 * have the same number of vertices on each wire.
 * @param CATTopBlendCouplingMode_Develop
 * Points are coupling to minimize Gaussian Curvature of the surface
 * Only with Blend G0G0 continuity
 * @param CATTopBlendCouplingMode_Spine
 * NOT TO BE USED.
 */

typedef enum 
  {
  CATTopBlendCouplingMode_DomainG0=0,
  CATTopBlendCouplingMode_DomainG1,
  CATTopBlendCouplingMode_DomainG2,
  CATTopBlendCouplingMode_Edge,
  CATTopBlendCouplingMode_Spine,
  CATTopBlendCouplingMode_Develop,
  CATTopBlendCouplingMode_NoTwist
  } 
CATTopBlendCouplingMode ;

#endif /* CATTopBlendCouplingMode_h_ */
