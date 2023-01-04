#ifndef CATTopologicalFillType_h_
#define CATTopologicalFillType_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

/**
  * Defines the fill type.
  * @param CATTopologicalFillType_analytic
  * The edges of the domain to fill are isoparametric  curves of the final surfaces. The number
  *  of generated faces is depending on the number of wires.
  *	Use it for simple domain to fill, as rectangular area.
  * @param CATTopologicalFillType_power   
  * The area is filled with a single surface. This allows you to manage wires which describe 
  * a complex topology.
  * @param CATTopologicalFillType_powerplane  
  * The area is filled with a single surface which is obtained by deforming a plane. 
  * @param CATTopologicalFillType_automatic
  * Automatically determines the most suitable method according to the input topology.
  */
enum CATTopologicalFillType
{
  CATTopologicalFillType_analytic,
  CATTopologicalFillType_power,
  CATTopologicalFillType_automatic,
  CATTopologicalFillType_powerfill,
  CATTopologicalFillType_powerplane,
  CATTopologicalFillType_autofillnosingular,
  CATTopologicalFillType_autofill_level1,
  CATTopologicalFillType_autofill_level2
};

#endif /* CATTopologicalFillType_h_ */
