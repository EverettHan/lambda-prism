#ifndef CATMathCurve_H
#define CATMathCurve_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATMathematics.h"

#include "CATMathDef.h"
#include "CATMathInline.h"
#include "CATIACGMLevel.h"
#include "CATIAV5Level.h"
//#if defined ( CATIAV5R11 )
#include "CATCGMVirtual.h"
//#endif  

#include "CATMathematicType.h"

class CATMathPoint;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

/**
 * Base class representing a mathematical parametric curve
 * <tt> t -> M(t) </tt> from <tt>R</tt>  to <tt>R3</tt>.<br>
 *<b>Role</b>:
 * This class is really useful in the context of the GeometricObjects 
 * framework and helps to return the canonical form of a geometry if it exists.
 */
class ExportedByCATMathematics CATMathCurve : public CATCGMVirtual
{
  public:
/**
 * Returns the derived class name of <tt>this</tt> CATMathCurve.
 */
   virtual CATMathClassId IsA() const = 0;

   /**
 * Returns the mathematical type.
 * @return
 * The CATMathematicType.
 */
   virtual CATMathematicType GetMathType() const = 0;
   /**
 * Checks the type of the CATMathCurve.
 * @param TypeReference
 * The type to be checked.
 * @return
 * The CATMathematicType.
 */
   int     IsATypeOf(CATMathematicType TypeReference) const;

#ifdef CATIACGMV5R23
   INLINE virtual ~CATMathCurve() {};
#else
   virtual ~CATMathCurve();
#endif
 
 };
#endif





