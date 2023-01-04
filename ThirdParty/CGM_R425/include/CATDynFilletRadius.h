#ifndef CATDynFilletRadius_h_
#define CATDynFilletRadius_h_

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1 
 */ 

#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"
#include "CATIAV5Level.h"
#include "CATIACGMLevel.h"
class CATCell;
class CATCGMStream;
class CATCGMJournalList;
class CATBody;
class CATTopData;
class CATDynLiveFilletRadius;

#ifndef NULL
#define NULL 0
#endif

/**
 * Class defining the radius properties of an edge in a ribbon.
 * <br> A CATDynFilletRadius is defined by a cell and a radius value.
 * The cell is either a vertex, or an edge. In case of an edge, a ratio
 * on this edge can be given to detail the location of the point on which
 * the radius value is given. This is especially used for variable radius ribbon.
 * In case of variable radius ribbon moreover, several CATDynFilletRadius must 
 * be created, referencing the same edge with different radius and locations. 
 */
class ExportedByCATGMOperatorsInterfaces CATDynFilletRadius
{
  public :
		/**
		 * Constructs a radius definition.
		 * @param iRadius
		 * The value of the radius.
		 * @param iLocation
		 * The pointer to the cell (vertex, edge) on which the radius applies.
		 * @param iRatio
		 * The pointer to the ratio of the edge length which defines the point where the radius is defined.
		 * <br><b>Legal values</b>:
		 * <tt>0 <= iRatio <= 1</tt>. If <tt>NULL</tt>, the radius applies on the start vertex of the edge.
		 * @param iDirection
		 * The pointer to the tangent to the radius law at <tt>iLocation</tt>. If <tt>NULL</tt>, this is
		 * not taken into account. 
		 */
  CATDynFilletRadius(double    iRadius, 
		                 CATCell*  iLocation, 
		                 double*   iRatio     = NULL,
		                 CATAngle* iDirection = NULL);

  virtual ~CATDynFilletRadius();

	/**
	 * Returns the radius value associated with the edge of a ribbon.
	 * @return
	 * The radius value.
	 */
  double  GetRadius()   const;
  
  /**
	 * @param iRadii
	 * Set the radius value.
	 */
  void  SetRadius(const double iRadii);
	/**
	 * Returns the cell on which the radius is defined.
	 * @return
   * The pointer to the cell.
   */
  CATCell* GetLocation() const;

  /**
   * @param iCell
   * set the Location Cell.
   */
  void  SetLocation(CATCell * iCell);
  
	/**
	 * Returns the ratio defining the location of the point on the edge.
	 * @return
	 * The ratio value, if there is one defined. Use first <tt>HasRatio</tt>, to test whether this value is defined.
	 */
  double     GetRatio()  const;

  /**
   * @param iRatio
   * set the ratio.
   */
  void  SetRatio(const double iRatio);

   	/**
	 * Tests whether a ratio is defined to precise the location of the point on the edge.
	 * @return
	 * The result of the test
	 * <br><b>Legal values</b>: <tt>TRUE</tt> if it is defined, <tt>FALSE</tt> otherwise.
	 */
  CATBoolean HasRatio()  const;

	/**
	 * Returns the angle defining the radius variation at the point on the edge.
	 * @return
	 * The angle value, if there is one defined. Use first <tt>HasDirection</tt>, to test whether this angle is defined.
	 */
  CATAngle   GetDirection() const;

  /**
   * @param iDirection
   * set direction.
   */
  void  SetDirection(const CATAngle iDirection);

	/**
	 * Tests whether an angle is defined to precise the radius variation at the point on the edge.
	 * @return
	 * The result of the test
	 * <br><b>Legal values</b>: <tt>TRUE</tt> if it is defined, <tt>FALSE</tt> otherwise.
	 */
  CATBoolean HasDirection() const;


  /**
   * @nodoc
	 */
  virtual CATDynLiveFilletRadius * GetAsCATDynLiveFilletRadius();

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

private:

  /** @nodoc*/
  void  UpdateInputs (CATTopData *iTopData, CATCGMJournalList& iJournal, CATBody* InputBody, CATBody* iCreationBody);

  /** @nodoc*/
  void  Stream(CATCGMStream& Str);

  /** @nodoc*/
  static CATDynFilletRadius *UnStream(CATCGMStream & iStr);

  /** @nodoc*/
  private:
  double             _radius ;
  CATCell*           _location ;  
  double*            _ratio ;     
  CATAngle*          _direction ; 

  friend class CATDynRemoveFaceFilletRibbon;
  friend class CATDynFaceFaceFilletRibbon;
  friend class CATDynEdgeFilletRibbon;
  friend class CATDynLiveFilletRadius;
};

/** 
 * @collection CATLISTP(CATDynFilletRadius)
 * Collection class for pointers to the radius definition in a ribbon.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include <CATLISTP_Clean.h>
#include <CATLISTP_PublicInterface.h>
#include <CATLISTP_Declare.h>
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy    ExportedByCATGMOperatorsInterfaces
CATLISTP_DECLARE( CATDynFilletRadius )


#endif
