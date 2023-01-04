#ifndef CATLoop_H
#define CATLoop_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATEdgeDomain.h"    
class CATEdge;

//-----------------------------------------------------------------------------
#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATLoop ;
#else
extern "C" const IID IID_CATLoop ;
#endif

/**
 * Interface representing a set of connected
 * edges of a face.
 *<br> The connected edges are the boundaries of a face, or
 * immersed into a face, depending on the <tt>CATLocation</tt> 
 * attribute. A CATLoop is created with the @href CATBody#CreateLoop or @href CATBody#CreateDomain methods
 * and deleted with the 
 * @href CATICGMContainer#Remove method. It can be open or not.
 */ 
class ExportedByCATGMModelInterfaces CATLoop : public CATEdgeDomain
{

  CATDeclareInterface;

  public :

  /**
    * States that <tt>this</tt> CATLoop construction is finished.
		* <br> Checks are run to
    * detect topological problems. To call after the geometric supports have been defined.
    */
  virtual void Done() = 0;
  
  /**
  * @nodoc
  * @deprecated V5R14 @href CATDynMassProperties3D#GetWetArea
  */
  virtual double CalcArea() = 0;
  
};

CATDeclareHandler(CATLoop,CATEdgeDomain);

#endif // CATLoop_H
