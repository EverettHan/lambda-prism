#ifndef CATDynDraftParam_h
#define CATDynDraftParam_h

// COPYRIGHT DASSAULT SYSTEMES  2000

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"

#include "CATIAV5Level.h"
#include "CATCGMVirtual.h"

class CATCell;

/**
* Class defining the angle properties of an edge in a draft.
* <br> A CATDynDraftParam is defined by an edge and an angle value.
* A ratio on this edge can be given to detail the location of the point on which
* the radius value is given. This is especially used for variable angle draft.
* In case of variable draft moreover, several CATDynDraftParam must 
* be created, referencing different edges, radius and locations. 
* @see CATDynDraftDomain, CATDynDraftRibbon, CATICGMDynDraft
*/
class ExportedByCATGMOperatorsInterfaces CATDynDraftParam : public CATCGMVirtual
{
  public:  

  /**
  * Constructs a draft parameter definition.
  * @param iLocation
  * The pointer to the cell (edge) on which the angle applies.
  * @param iRatio
  * The pointer to the ratio of the edge length which defines the point where the angle is defined.
  * <br><b>Legal values</b>:
  * <tt>0 <= iRatio <= 1</tt>.
  * @param iAngle
  * The value of the angle.
  */
  CATDynDraftParam (CATCell  * iLocation,
                    double   & iRatio,
                    CATAngle & iAngle);

  /**
  * @nodoc
  */
  ~CATDynDraftParam ();

  /**
  * Returns the cell on which the angle is defined.
  * @return
  * The pointer to the cell.
  */
  CATCell * GetLocation() const;
    
  /**
  * Returns the ratio defining the location of the point on the edge.
  * @return
  * The ratio value, if there is one defined. Use first <tt>HasRatio</tt>, to test whether this value is defined.
  */
  double GetRatio() const;

  /**
  * Returns the angle value associated with the edge of a draft ribbon.
  * @return
  * The angle value.
  */
  CATAngle GetAngle() const;

  private:

  // Internal datas
  CATCell  * _Location ;  
  double     _Ratio ;     
  CATAngle   _Angle ; 
};


/** 
 * @collection CATLISTP(CATDynDraftParam)
 * Collection class for pointers to elementary draft parameters.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include <CATLISTP_Clean.h>
#include <CATLISTP_PublicInterface.h>
#include <CATLISTP_Declare.h>
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy    ExportedByCATGMOperatorsInterfaces
CATLISTP_DECLARE(CATDynDraftParam)


#endif
