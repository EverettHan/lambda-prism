#ifndef CATExtrudeLimitThicknessOrOffsetType_H
#define CATExtrudeLimitThicknessOrOffsetType_H

/** @CAA2Required */ 
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
// COPYRIGHT DASSAULT SYSTEMES  2012

/**
 * @nodoc
 * defines the type of thickness or Offset to apply: 
 * an offset of the limit computed before extrusion
 * or a thickness applied on the resulting extrusion
 * @param  CATExtrudeLimitOffsetType
 * The Extrusion is made to or from the offset profile. Default value.
 * @param  CATExtrudeLimitThicknessAfterExtrudeType
 * The extrusion is made to or from the contextual limit first, and then the thickness is applied to the resulting extrusion
 * Restricted to a contextual limit
 * @param  CATExtrudeLimitThicknessBeforeExtrudeType
 * The thickness is applied to the contextual limit first, and then the offset Limit replace the original limit.
 * Restricted to a contextual limit
 */
typedef enum  
{ 
  CATExtrudeLimitOffsetType = 0, 
  CATExtrudeLimitThicknessAfterExtrudeType = 1,
  CATExtrudeLimitThicknessBeforeExtrudeType = 2,
}
CATExtrudeLimitThicknessOrOffsetType;

#endif
