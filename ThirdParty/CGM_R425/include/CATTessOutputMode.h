#ifndef CATTessOutputMode_h
#define CATTessOutputMode_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 


/**
 * Specifies the type of tessellation output objects preferred.
 * @param CATTessOutputMixed
 * Stripes, Fans, Polygons, and isolated triangles requested. The default.
 * @param CATTessOutputTriangles
 * Only isolated triangles requested.
 * @param CATTessOutputStrips
 * Only stripes requested.
 */
enum CATTessOutputMode
{
  CATTessOutputMixed,
  CATTessOutputTriangles,
  CATTessOutputStrips  
};

#endif
