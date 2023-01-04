#ifndef CATICGMLengthFromBodyOnWire_h_
#define CATICGMLengthFromBodyOnWire_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
* @CAA2Level L1
* @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATMathDef.h"
#include "CATSkillValue.h"

class CATBody;
class CATEdge;
class CATGeoFactory;
class CATVertex;
class CATWire;
class CATMathPoint;
class CATTopData;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMLengthFromBodyOnWire;

/**
* Class defining the operator that computes the length between two point bodies.
* This operator can be used in two modes.
* In BASIC mode, the operation is run at the operator creation. In this mode,
* you have to read the resulting distance, and release the operator, as in the following 
* example:
* <pre>CATICGMLengthFromBodyOnWire * Op =  CATICGMLengthFromBodyOnWire (factory,vertex1,vertex2); 
* double distance = Op->GetDistance(NULL,NULL);
* Op->Release();</pre>
* If you need specific parameters, use the ADVANCED mode:
* <ul>
* <li> Create the operator ,
* <li> Set parameters,
* <li> Run,
* <li> Get the resulting distance,
* <li> Delete the operator.
* </ul>
* Example:
* <pre> 
* CATICGMLengthFromBodyOnWire * Op =  CATICGMLengthFromBodyOnWire (factory,vertex1,vertex2); 
* Op->SetSupport(Wire); // on a wire
* Op->Run();
* CATMathPoint Point1, Point2;
* double distance = Op->GetDistance(&Point1,&Point2);
* Op->Release();
* </pre>
*/
class ExportedByCATGMModelInterfaces CATICGMLengthFromBodyOnWire: public CATICGMTopOperator
{
public:
	/**
	* Constructor
	*/
	CATICGMLengthFromBodyOnWire();

	/**
	* Runs the operator in <tt>ADVANCED</tt> mode.
	* @return
	* A diagnosis.
	* <br>Legal values</tt>: 0 if some arguments of the operator are invalid, 1 otherwise.
	*/
	virtual int Run() = 0;

	/**
	* Returns the computed distance.
	* @param iMathPoint1
	* A pointer to the mathematical definition of the first point. 
	* <br>If <tt>NULL</tt>, this argument is not computed.
	* @param iMathPoint2
	* A pointer to the mathematical definition of the second point.
	* <br>If <tt>NULL</tt>, this argument is not computed.
	* @return
	* The computed distance.
	* <br>Sample: to retrieve the distance and the mathematical definition of the first point:
	* <pre>CATMathPoint Point1;
	* double distance = Op->GetDistance(&Point1,NULL);</pre>
	*/
	virtual CATLength GetDistance(
		CATMathPoint *iMathPoint1 = NULL,
		CATMathPoint *iMathPoint2 = NULL) const = 0;

	/** 
	* Defines the new vertices between which the distance is computed.
	* <br>To use in <tt>ADVANCED</tt> mode.
	* @param iNewVertex1
	* A pointer to the first vertex.
	* @param iNewVertex2
	* A pointer to the second vertex.
	*/
	virtual void SetVertices(CATVertex *iNewVertex1, CATVertex *iNewVertex2) = 0;

	/** 
	* Defines the new vertices between which the distance is computed.
	* <br>To use in <tt>ADVANCED</tt> mode.
	* @param iNewVertex1
	* A pointer to the first vertex.
	* @param iNewVertex2
	* A pointer to the second vertex.
	*/
	virtual void SetVertices(CATBody *iNewVertex1, CATBody *iNewVertex2) = 0;

	/**
	* Defines a new edge along which the distance is computed.
	* <br>To use in <tt>ADVANCED</tt> mode.
	* @param iNewEdge
	* A pointer to the edge along which the distance is computed.
	*/
	virtual void SetEdge(CATEdge *iNewEdge) = 0;

	/**
	* Defines a new wire body along which the distance is computed.
	* <br>To use in <tt>ADVANCED</tt> mode.
	* @param iNewEdge
	* A pointer to the wire body along which which the distance is computed.
	*/
	virtual void SetEdge(CATBody *iNewEdge) = 0;

protected:
	/**
	* Destructor
	*/
	virtual ~CATICGMLengthFromBodyOnWire(); // -> delete can't be called
};

/**
* Constructs an operator that computes the distance between two vertices along a wire.
* @param iFactory
* The factory that creates the resulting body.
* @param iData
* The pointer to the data defining the software configuration.
* @param iVertex1
* A pointer to the first vertex.
* @param iVertex2
* A pointer to the second vertex.
* @param iWire
* A pointer to the wire on which the distance is computed.
* @param iMode
* The operator mode.
* <dl><dt><tt>BASIC</tt> The operation is performed at the operator creation.
*     <dt><tt>ADVANCED</tt>Use the Run method. 
* </dl>
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMLengthFromBodyOnWire *CATCGMCreateLengthFromBodyOnWire(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATVertex *iVertex1,
	CATVertex *iVertex2,
	CATWire *iWire,
	CATSkillValue iMode = BASIC);

/**
* Constructs an operator that computes the distance between two vertices along a wire body.
* @param iFactory
* The factory that creates the resulting body.
* @param iData
* The pointer to the data defining the software configuration.
* @param iVertex1
* A pointer to the first body point.
* @param iVertex2
* A pointer to the second body point.
* @param iWire
* A pointer to the wire body on which the distance is computed.
* @param iMode
* The operator mode.
* <dl><dt><tt>BASIC</tt> The operation is performed at the operator creation.
*     <dt><tt>ADVANCED</tt>Use the Run method. </dl>
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMLengthFromBodyOnWire *CATCGMCreateLengthFromBodyOnWire(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iVertex1,
	CATBody *iVertex2,
	CATBody *iWire,
	CATSkillValue iMode = BASIC);

/**
* Constructs an operator that computes the distance between two vertices along a wire body.
* @param iFactory
* The factory that creates the resulting body.
* @param iVertex1
* A pointer to the first body point.
* @param iVertex2
* A pointer to the second body point.
* @param iWire
* A pointer to the wire body on which the distance is computed.
* @param iMode
* The operator mode.
* <dl><dt><tt>BASIC</tt> The operation is performed at the operator creation.
*     <dt><tt>ADVANCED</tt>Use the Run method. </dl>
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMLengthFromBodyOnWire *CATCGMCreateLengthFromBodyOnWire(
	CATGeoFactory *iFactory,
	CATBody *iVertex1,
	CATBody *iVertex2,
	CATBody *iWire,
	CATSkillValue iMode = BASIC);

/**
* Constructs an operator that computes the distance between two vertices along a wire.
* @param iFactory
* The factory that creates the resulting body.
* @param iVertex1
* A pointer to the first vertex.
* @param iVertex2
* A pointer to the second vertex.
* @param iWire
* A pointer to the wire on which the distance is computed.
* @param iMode
* The operator mode.
* <dl><dt><tt>BASIC</tt> The operation is performed at the operator creation.
*     <dt><tt>ADVANCED</tt>Use the Run method. </dl>
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMLengthFromBodyOnWire *CATCGMCreateLengthFromBodyOnWire(
	CATGeoFactory *iFactory,
	CATVertex *iVertex1,
	CATVertex *iVertex2,
	CATWire *iWire,
	CATSkillValue iMode = BASIC);

#endif /* CATICGMLengthFromBodyOnWire_h_ */
