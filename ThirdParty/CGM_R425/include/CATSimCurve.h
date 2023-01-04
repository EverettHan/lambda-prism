#ifndef CATSimCurve_h
#define CATSimCurve_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATEdgeCurve.h"
#include "CATListOfCATCurves.h"      
#include "CATListOfCATCrvLimits.h"      
#include "CATListOfInt.h" 
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATSimCurve ;
#else
extern "C" const IID IID_CATSimCurve ;
#endif

//CAA_Exposed  CATIGemSimCurve
/** 
 * Interface representing the aggregating curve of two identical curves.
 *<br> The CATSimCurve is created by the <tt>CreateSimCurve</tt>
 * method of the <tt>CATGeoFactory</tt> interface and deleted with the <tt>Remove</tt> method.
 * Their parameterization must be linearly mapped and they must have the same limits. 
 *If they do not,
 * use the @href CATEdgeCurveComputation operator. The number of curves of a 
 * CATSimCurve is not limitated.
 */
class ExportedByCATGMGeometricInterfaces CATSimCurve : public CATEdgeCurve
{
  CATDeclareInterface;

public:
 //CAA_Exposed  
/**
 * Replaces all the curves of <tt>this</tt> CATSimCurve.
 * @param iNewCurves
 * The list of the curves.
 * @param iLimits
 * The list of limitations on each curve.
 * @param iOrns
 * The list of relative orientation of the curves.
 * <br><b>Legal values</b>:
 * 1 for the same orientation, -1 for the opposite orientation.
 * @param iGap
 * The maximum authorized gap between the curves.
 */
  virtual void Set( CATLISTP(CATCurve) & iNewCurves,
                   CATLISTP(CATCrvLimits) & iLimits,
                  CATListOfInt           & iOrns,
            const double iGap       ) = 0 ;

  //CAA_Exposed 
/**
 * Adds a new curve to <tt>this</tt> CATSimCurve.
 * @param iNewSubElement
 * A pointer to the new curve to add.
 * @param iNewGap
 * The new value of the maximum authorized gap between the curves.
 * @param iOrnVsEdgeCurve
 * The relative orientation of the curve to add with respect to the edge curve orientation.
 * <br><b>Legal values</b>:
 * 1 for the same orientation, -1 for the opposite orientation.
 */
  virtual void Append ( CATCurve* iNewSubElement, 
                       const double iNewGap, 
                       const short iOrnVsEdgeCurve = 1) = 0 ;



/** @nodoc */
  virtual void Append ( CATCurve* NewSubElement ) = 0 ;

};

CATDeclareHandler(CATSimCurve,CATEdgeCurve);

#endif
