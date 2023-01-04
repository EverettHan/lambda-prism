#ifndef CATTopPropagationType_H
#define CATTopPropagationType_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 



/**
 * Specifies the management of the propagation algorithm .
 * @param  CatPropagSingle
 * No propagation is performed.
 * @param  CatPropagExtrapolated
 * The specified geometry is extrapolated.
 * @param  CatPropagClosing
 * Adjacent topological cells are agregated within a skin.
 * @param  CatPropagAllowPartial
 * Allow limit to partially block the extrusion and select the first volume of intersection
 * between the extruded body and the limiting body.
 */ 
enum CATTopPropagationType
{ CatPropagSingle, CatPropagExtrapolated, CatPropagClosing, CatPropagAllowPartial};

#endif



