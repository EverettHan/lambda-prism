#ifndef CATVertexOperatorExt_h
#define CATVertexOperatorExt_h

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "CATGeoToTopOperatorExt.h"

class CATDomain;
class CATVertex;
class CATLoop;
class CATVertex;
class CATPoint;
class CATSurface;
class CATGeoFactory;
class CATBody;
class CATCGMJournalList;

/** 
 * Deprecated. Use now @href CATTopPointOperator .
* Class representing the operator that creates a point body from one point. 
* <br>To use the CATVertexOperatorExt:
* <ul><li>Create it with the available constructor. 
* <li>If needed, tune some parameters with the <tt>SetXxx</tt> methods.
* <li> <tt>Run</tt> the operator
* <li>Retrieve the created body (frozen by default) with the <tt>GetResult</tt> method. 
* <li><tt>delete</tt> the operator after use.
* </ul>
*/

class ExportedByCATTopologicalObjects CATVertexOperatorExt :public CATGeoToTopOperatorExt
{
public:
  CATCGMNewClassArrayDeclare;

 /** @nodoc */
  CATVertexOperatorExt(CATGeoFactory*	iFactory,
		    CATPoint*	    	iPoint,
		    CATBody*          	iTargetBody=NULL,
		    CATBodyFreezeMode   iBodyfreezemode=CATBodyFreezeOn,
		    CATCGMJournalList*	iReport=NULL);
/**
	* Creates an operator to build a point body from one point.
	* @param iFactory
	* The pointer to the factory of the geometry.
	* @param iPoint
	* The pointer to the point used to define the vertex.
	*/
  CATVertexOperatorExt(CATGeoFactory*	iFactory,
		CATTopData * iData,
		    CATPoint*	    	iPoint);
  
  ~CATVertexOperatorExt();

  /* @nodoc @nocgmitf */
  int RunOperator();

 /**
	* Returns the pointer to the vertex of the resulting body.
	* @return
	* The pointer to the vertex of the resulting body. Remember that the whole body is retrieved with
	* the <tt>GetResult</tt> method, and you must manage its deletion if you do not want to keep it.
	*/ 
  CATVertex*     GetVertex() const;

  //***************************************************************************************
  // CGMReplay
  //***************************************************************************************

  void               RDOIAOO(CATTopOperator & iOperator);
  

  //***************************************************************************************

protected:
  // Methods for CGMReplay recording.  We need to use the Ext naming because we've used that in CATGeoToTopOperatorExt.
  // If more of these methods are implemented, they should also use the new naming convention.
  virtual void WriteInputExt(CATCGMStream &ioStream);
  virtual void DumpExt(CATCGMOutput& os);

  // Polyhedral body Management 
  virtual CATBoolean Is_PolyInputs_Allowed();
  virtual CATBoolean Is_MixedPolyExactInputs_Allowed();

private:

  void	         MakeVertex();
 
  CATVertex      *  _vertex;
  CATPoint       *  _point;
  int               _makevertexdone;
  
};



#endif
