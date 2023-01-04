#ifndef CATKNOTVECTOR_H
#define CATKNOTVECTOR_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include <stdio.h> 
#include "YP00IMPL.h"

#include "CATIACGMLevel.h"

#include "CATCGMVirtual.h"
#include "CATCGMNewArray.h"
#include "CATTolerance.h"

#include "CATMathDef.h"
#include "CATMathInline.h"

class     CATMathPolynomX ;
class     CATCGMStream; 
class     CATError;

#define CATKnotVectorWithTolerance
#define CATKnotVectorNewConstructorR18

/**
 * Class containing all the data necessary to define 
 * a uniform or non uniform, non periodic basis. PERIODIC NURBS ARE NOT SUPPORTED.
 * The maximum degree of a NURBS is 15.
 * <br> A <b>basis</b> is a set of piecewise polynomial functions
 * (of a given <b> degree</b>), called 
 * <b>basis functions</b>. The pieces are the <b>arcs</b>. 
 * They  define the parameter domains between
 * two distincts successive <b> knot values</b> (global parameters at the
 * arc extremities). Then, the number of knots is the number of arcs plus 1.
 * The matching between arc number and Knot vector rank follows the rules ;
 *  <tt>(i - IndexOffset)-th Arc starts at Knots(i-1) and ends at Knots(i) </tt>,
 * There is one polynom per arc for each basis function.  
 * The <b>continuity order</b> between arcs is equal to the degree minus the
 * multiplicity of the corresponding knot value.
 * <table>
 * <tr><td></td><td>Multiplicity</td><td>Continuity order</td></tr>
 * <tr><td>single knot value</td><td><tt>1</tt></td><td><tt>Degree-1</tt></td></tr>
 * <tr><td>internal knot values</td><td><tt>1<=m<=degree</tt></td>
 *     <td><tt>Degree-m</tt></td></tr>
 * <tr><td>extreme knot values for a non periodic basis</td>
 *     <td><tt>degree+1 </tt>(by convention)</td><td><tt>(-1)</tt></td></tr>
 * <tr><td>same first and last knot values for a periodic basis</td>
 *     <td><tt>1<=m<=degree</tt></td><td><tt>Degree-m </tt></td></tr>
 * </table>
 * The number of arcs where 
 * the polynom is not null depends on the knot vector mutiplicities.
 * <br>Associating each basis
 * function to a <b> control point</b> (also called <b>vertex</b>),
 * allows the definition of Nurbs geometric
 * elements. A basis function represents the influence of one control point.
 * Note that vertices are not data of the knot vector, but of
 * the Nurbs polynomial element. Nevertheless, vertex ranks are handled in
 * methods of this class, because they are equivalent to the polynomial
 * basis ranks.
 * <br>A CATKnotVector is a transient object, it can be  saved as private data of a
 *  curve or a surface. 
 * A CATKnotVector is defined with:
 * <table>
 * <tr><td>CATLONG32</td> <td>Degree</td>
 *        <td> The degree of the B-Spline basis functions</td></tr>
 * <tr><td>CATBoolean</td> <td>IsPeriodic</td>
 *        <td> 1 for a periodic basis: the parameter domain is unlimited.
 * If <tt>Delta= LastKnotValue - FirstKnotValue</tt>,
 * the evaluations at <tt>Parameter + Delta</tt> and <tt>Parameter</tt> are
 * the same.
 *        <br> 0 otherwise</td></tr>
 * <tr><td>CATBoolean</td> <td>IsUniform</td>
 *        <td> 1 in case of equally spaced knot values.
 *         <br>0 otherwise.</td></tr>
 * <tr><td>CATLONG32</td> <td>NbOfKnots</td>
 *        <td> The number of knot values ( <tt>=NbOfArcs + 1</tt></td></tr>
 * <tr><td>CATLONG32</td> <td>Knots</td>
 *        <td> The array of the knots values </td></tr>
 * <tr><td>CATLONG32</td> <td>Multiplicities</td>
 *        <td> The array of the multiplicity of a knot value</td></tr>
 * </table>
 * <br>Sample of a non periodic non uniform knot vector, with C2 continuity:
 * <table>
 * <tr><td>CATLONG32</td> <td>Degree</td>
 *        <td> 3 </td></tr>
 * <tr><td>CATBoolean</td> <td>IsPeriodic</td>
 *        <td>  0 </td></tr>
 * <tr><td>CATBoolean</td> <td>IsUniform</td>
 *        <td> 0 </td></tr>
 * <tr><td>CATLONG32</td> <td>NbOfKnots</td>
 *        <td> 4</td></tr>
 * <tr><td>CATLONG32</td> <td>Knots</td>
 *        <td> 0 , 2 , 8 , 9 </td></tr>
 * <tr><td>CATLONG32</td> <td>Multiplicities</td>
 *        <td> 4 , 1 , 1 , 4</td></tr>
 * </table>
 */
class ExportedByYP00IMPL CATKnotVector : public CATCGMVirtual
{
public:

  /** @nodoc */
  CATCGMNewClassArrayDeclare;
 
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//
//- Constructors
//
/**
 * Constructs a Bezier CATKnotVector.
 * <br>It corresponds to one arc of degree <tt>iDegree</tt>.
 * <br>Parameterization on [0.0, 1.0], not Extreme Scale compliant.
 * @param iDegree
 * The degree of the polynomial basis.
 */
                                       CATKnotVector           (const CATLONG32                   iDegree            = 3);

/**
 * Constructs a Bezier CATKnotVector.
 * <br>It corresponds to one arc of degree <tt>iDegree</tt>.
 * <br>Parameterization on [0.0, Scale], Extreme Scale compliant (Scale being factory scale, read in <tt>iTolObject</tt>).
 * @param iTolObject
 * The set of geometric and mathematical tolerances.
 * @param iDegree
 * The degree of the polynomial basis.
 */
                                       CATKnotVector           (const CATTolerance              & iTolObject         ,
                                                                const CATLONG32                   iDegree            = 3);


/**
 * Constructs a uniform CATKnotVector.
 * @param iTolObject
 * The set of geometric and mathematical tolerances.
 * @param oError
 * (output argument) The Error to raise if invalid data given to constructor.
 * @param iDegree
 * The degree of the polynomial basis.
 * @param iIsPeriodic
 * The periodicity. So far, periodic basis are not supported.
 * <br><b>Legal values</b>  0.
 * @param iNbOfArcs
 * The number of arcs.
 * @param iKnotStart
 * The parameter value of the first knot.
 * @param iStep
 * The uniform step value between two knots.
 * @param iIndexOffset
 * The index for the first arc.
 */
                                       CATKnotVector           (const CATTolerance              & iTolObject         ,
                                                                      CATError                 *& oError             ,
                                                                const CATLONG32                 & iDegree            ,
                                                                const CATLONG32                 & iIsPeriodic        ,
                                                                const CATLONG32                 & iNbOfArcs          ,
                                                                const double                      iKnotStart         = 0.,
                                                                const double                      iStep              = 1.,
                                                                const CATLONG32                   iIndexOffset       = 0
                                                               );

/**
 * Constructs a uniform CATKnotVector.
 * @param iDegree
 * The degree of the polynomial basis.
 * @param iIsPeriodic
 * The periodicity. So far, periodic basis are not supported.
 * <br><b>Legal values</b>  0.
 * @param iNbOfArcs
 * The number of arcs.
 * @param iKnotStart
 * The parameter value of the first knot.
 * @param iStep
 * The uniform step value between two knots.
 * @param iIndexOffset
 * The index for the first arc.
 */
                                       CATKnotVector           (const CATLONG32                 & iDegree            ,
                                                                const CATLONG32                 & iIsPeriodic        ,
                                                                const CATLONG32                 & iNbOfArcs          ,
                                                                const double                      iKnotStart         = 0.,
                                                                const double                      iStep              = 1.,
                                                                const CATLONG32                   iIndexOffset       = 0
                                                               );
/**
 * Constructs a non-uniform CATKnotVector.
 * @param iTolObject
 * The set of geometric and mathematical tolerances.
 * @param oError
 * (output argument) The Error to raise if invalid data given to constructor.
 * @param iDegree
 * The degree of the polynomial basis.
 * @param iIsPeriodic
 * The periodicity.
 * <br><b>Legal values</b> 0. 
 * @param iNbOfKnots
 * The number of knot values specified for the knot vector. The number of arcs
 * is <tt>iNbOfKnots - 1</tt>.
 * @param iKnots
 * The array of the global parameter values at the end of each arc.
 * @param iMultiplicities
 * The array of the corresponding multiplicities.
 * @param iIndexOffset
 * The index for the first arc. 
 */
                                       CATKnotVector           (const CATTolerance              & iTolObject         ,
                                                                      CATError                 *& oError             ,
                                                                const CATLONG32                 & iDegree            ,
                                                                const CATLONG32                 & iIsPeriodic        ,
                                                                const CATLONG32                 & iNbOfKnots         ,
                                                                const double                   *  iKnots             ,
                                                                const CATLONG32                *  iMultiplicities    ,
                                                                const CATLONG32                   iIndexOffset       = 0
                                                               );

/**
 * Constructs a non-uniform CATKnotVector.
 * @param iDegree
 * The degree of the polynomial basis.
 * @param iIsPeriodic
 * The periodicity.
 * <br><b>Legal values</b> 0. 
 * @param iNbOfKnots
 * The number of knot values specified for the knot vector. The number of arcs
 * is <tt>iNbOfKnots - 1</tt>.
 * @param iKnots
 * The array of the global parameter values at the end of each arc.
 * @param iMultiplicities
 * The array of the corresponding multiplicities.
 * @param iIndexOffset
 * The index for the first arc. 
 */
                                       CATKnotVector           (const CATLONG32                 & iDegree            ,
                                                                const CATLONG32                 & iIsPeriodic        ,
                                                                const CATLONG32                 & iNbOfKnots         ,
                                                                const double                   *  iKnots             ,
                                                                const CATLONG32                *  iMultiplicities    ,
                                                                const CATLONG32                   iIndexOffset       = 0
                                                               );

/**
 * Constructs a non-uniform CATKnotVector from a parameter array and 
 * a general continuity order.
 * @param iIsPeriodic
 * The periodicity.
 * <br><b>Legal values</b>0.
 * @param iNbOfParameters
 * The number of knot values specified for the knot vector. The number of arcs
 * is <tt>iNbOfParameters - 1</tt>.
 * @param iParameters
 * The array of the global parameter values at the end of each arc.
 * @param iContinuityOrder
 * The global continuity (0,1,2) of the curve. The degree of the polynomial basis
 * is <tt>iContinuityOrder + 1</tt>.
 * @param iIndexOffset
 * The index for the first arc.
 * @param iTolObject
 * The set of geometric and mathematical tolerances.
 */
                                       CATKnotVector           (const CATLONG32                 & iIsPeriodic        ,
                                                                const CATLONG32                 & iNbOfParameters    ,
                                                                const double                   *  iParameters        ,
                                                                const CATLONG32                 & iContinuityOrder   ,
                                                                const CATLONG32                   iIndexOffset       = 0,
                                                                const CATTolerance              & iTolObject         = CATGetDefaultTolerance()
                                                               );
/**
 * Copy Constructor.
 * <br>A linear transformation of the parameterization can be applied (optional)
 *  <tt>New parameter= iCoefficient * Old parameter + iShift</tt>,
 * @param iKnotVectorToCopy
 * The knot vector to copy.
 * @param iCoefficient
 * The coeficient of the transformation.
 * @param iShift
 * The shift of the transformation.
 * @param iTolObject
 * The set of geometric and mathematical tolerances.
 */
                                       CATKnotVector           (const CATKnotVector             & iKnotVectorToCopy  ,
                                                                      double                      iCoefficient       = 1.,
                                                                      double                      iShift             = 0.,
                                                                const CATTolerance              & iTolObject         = CATGetDefaultTolerance()
                                                               ); 

/** 
 * Assignment operator.
 *<br>Desallocates and reallocates the left operand, except if it is the
 * same object as the right operand (<tt>iKnotVectorToAffect</tt>).
 */
                       CATKnotVector & operator =              (const CATKnotVector             & iKnotVectorToAffect);

/**
 * Destructor.
 */
    virtual                           ~CATKnotVector           ();

//
//-----Read
//
/**
 * Tests if a CATKnotVector defines a periodic basis.
 * @return
 * <dl> <dt> <tt>FALSE</tt><dd> if the basis is not periodic
 *      <dt> <tt>TRUE</tt> <dd> if the basis is periodic (NOT SUPPORTED)</dl>
 */
    INLINE CATBoolean                  IsPeriodic              ()                                                      const ;

/**
 * Tests if a CATKnotVector defines a uniform basis.
 * @return
 * <dl> <dt> <tt>FALSE</tt> <dd> if the basis is not uniform
 *      <dt> <tt>TRUE</tt> <dd> if the basis is uniform </dl>
 */
    INLINE CATBoolean                  IsUniform               ()                                                      const ;

/**
 * Returns the degree of the basis defined by <tt>this</tt> CATKnotVector.
 * @return
 * The degree.
 */
    INLINE short                       GetDegree               ()                                                      const ;

/**
 * Returns the number of necessary control points for a nurbs using <tt>this</tt>
 * CATKnotVector.
 * @return
 * The number of control points.
 */
    INLINE short                       GetNumberOfControlPoints()                                                      const ;

/**
 * Returns the number of arcs of a nurbs using <tt>this</tt> CATKnotVector.
 * @return
 * The number of arcs.
 */
    INLINE short                       GetNumberOfArcs         ()                                                      const ;

/**
 * Returns the number of distinct knot values of <tt>this</tt> CATKnotVector.
 * @return
 * The number of distinct knot values.
 */
    INLINE short                       GetNumberOfKnots        ()                                                      const ;

/**
 * Returns the multiplicity of <tt>this</tt> CATKnotVector knot value.
 * @param iKnotNum
 * The knot number ( from 1 to <tt>KnotVector.GetNumberOfKnots </tt>)
 */
           CATLONG32                   GetKnotMultiplicity     (const CATLONG32                 & iKnotNum           ) const ;

/**
 * Returns the pointer to the knot values array of <tt>this</tt> CATKnotVector.
 * @param oKnots
 * The array of the knots. As part of the knot vector, it is deleted at the knot vector deletion.
 */
     INLINE void                       GetKnots                (const double                   *& oKnots             ) const ;

/** 
 * Returns the arc index offset.
 * @return
 * The arc index offset.
 */
     INLINE short                      GetIndexOffset          ()                                                      const;


/**
 * Returns the local parameters on the arc <tt>iArc</tt>.
 * @param iArc
 * The arc number. Begins at <tt>CATKnotVector::GetIndexOffset</tt>.
 * @param ioLocalStart
 * The parameter value at the begining of the arc.
 * @param ioLocalEnd
 * The parameter value at the end of the arc.
 */
            void                       GetInternalExtremities  (const CATLONG32                   iArc               ,
                                                                      double                    & ioLocalStart       ,
                                                                      double                    & ioLocalEnd         ) const;

/**
 * Returns the maximum local parameters and arc number of <tt>this</tt> Knot vector.
 * @param ioStartArc
 * The start arc. 
 * @param ioLocalStart
 * The parameter value at the begining of <tt>ioStartArc</tt>.
 * @param ioEndArc
 * The end arc. 
 * @param ioLocalEnd
 * The parameter value at the end of the arc of <tt>ioEndArc</tt>. 
 */
            void                       GetMaxExtremities       (      CATLONG32                 & ioStartArc         ,
                                                                      double                    & ioLocalStart       ,
                                                                      CATLONG32                 & ioEndArc           ,
                                                                      double                    & ioLocalEnd         ) const;


//
//- Set
//

            void                       SetTolerance            (const CATTolerance              & iTolObject          =CATGetDefaultTolerance());

/**
 * Copies a knot vector.
 * <br>Optionally, redefines the parameterization by a linear transformation:
 *  <tt>New parameter= iCoefficient * Old parameter + iShift</tt>.
 * @param iKnotVectorToCopy
 * The knot vector to copy.
 * @param iCoefficient
 * The coefficient of the transformation.
 * @param iShift
 * The shift of the transformation.
 */
            void                       Set                     (const CATKnotVector             & iKnotVectorToCopy  ,
                                                                      double                      iCoefficient       = 1.,
                                                                      double                      iShift             = 0.,
                                                                const CATTolerance              & iTolObject         = CATGetDefaultTolerance()
                                                               ); 

/**
 * Redefines <tt>this</tt> as a non uniform CATKnotVector.
 * @param iDegree
 * The new degree of the polynomial basis.
 * @param iIsPeriodic
 * The new periodicity.
 * <br><b>legal values</b>0.
 * @param iKnotsCount
 * The new number of knot values specified for the knot vector. The number of arcs
 * is <tt>iKnotsCount - 1</tt>.
 * @param iKnots
 * The array of the new global parameter values at the end of each arc.
 * @param iMultiplicities
 * The array of the new corresponding multiplicities.
 * @param iIndexOffset
 * The new index for the first arc. 
 */
             void                      SetNonUniformKnotVector (const CATLONG32                 & iDegree            ,
                                                                const CATLONG32                 & iIsPeriodic        ,
                                                                const CATLONG32                 & iKnotsCount        ,
                                                                const double                   *  iKnots             ,
                                                                const CATLONG32                *  iMultiplicities    ,
                                                                const CATLONG32                   iIndexOffset       = 0);

/**
 * Redefines <tt>this</tt> as a uniform CATKnotVector .
 * @param iDegree
 * The new degree of the polynomial basis.
 * @param iIsPeriodic
 * The new periodicity.
 * <br><b>legal values</b>0.
 * @param iArcsCount
 * The new number of arcs.
 * @param iKnotStart
 * The new parameter value of the first knot.
 * @param iStep
 * The new uniform step value between two knots.
 * @param iIndexOffset
 * The new index for the first arc.
 */
            void                       SetUniformKnotVector    (const CATLONG32                 & iDegree            ,
                                                                const CATLONG32                 & iIsPeriodic        ,
                                                                const CATLONG32                 & iArcsCount         ,
                                                                const double                      iKnotStart         = 0.,
                                                                const double                      iStep              = 1.,
                                                                const CATLONG32                   iIndexOffset       = 0
                                                               );

/**
 * Modifies a knot value of <tt>this</tt> CATKnotVector.
 * @param iKnotNum
 * The knot number ( from 1 to <tt>KnotVector.GetNumberOfKnots</tt> )
 * @param iNewKnotValue
 * The new knot value.
 */
            void                       SetKnotValue            (const CATLONG32                 & iKnotNum           ,
                                                                const double                    & iNewKnotValue      ,
                                                                const CATTolerance              & iTolObject         = CATGetDefaultTolerance()
                                                               );

/**
 * Modifies a knot value multiplicity of <tt>this</tt> CATKnotVector.
 * @param iKnotNum
 * The knot number ( from 1 to <tt>KnotVector.GetNumberOfKnots</tt> ).
 * @param iNewKnotMultiplicity
 * The new knot multiplicity.
 */
            void                       SetKnotMultiplicity     (const CATLONG32                 & iKnotNum           ,
                                                                const CATLONG32                 & iNewKnotMultiplicity);

/**
 * Modifies the degree.
 * @param iDegree
 * The new degree value. If it is
 * higher, the continuity order between arcs remains unchanged.
 * If it is lower, the continuity order between arcs is limited to <tt>Degree -1</tt>.
 */
            void                       SetDegree               (const CATLONG32                 & iDegree            );

/** 
 * Modifies the arc index offset.
 * @param iOffset
 * The new value of the arc offset.
 */
     INLINE void                       SetIndexOffset          (const CATLONG32                 & iOffset            );

/**
 * Adds knots at the left or the right of <tt>this</tt> KnotVector.
 * @param iNbOfParameters
 * The number of knots to add.
 * @param iParameters
 * The array of parameters to add. These parameters must be either all strictly lower than the first knot, 
 * or all strictly  greater than the last knot.
 * @param iContinuityOrders
 * The <tt>iContinuityOrders</tt> at the additionnal arc limits ( shift of one with the parameters array)
 * This method returns an error when <tt>this</tt> is periodic.
 */
            void                       Extrapol                (const CATLONG32                 & iNbOfParameters    ,
                                                                const double                   *  iParameters        ,
                                                                const CATLONG32                *  iContinuityOrders  = 0
                                                               );


//
//- Utilities
//
//
//--->  positionning of one general parameter in knot vector interval
/**
 * Returns the arc number of this CATKnotVector global parameter.
 * @return
 * The arc numbers start at 1.
 */
            CATLONG32                  SearchArcFromParameter  (const double                    & iGlobalParameter   )       const;
//--->  convert Global parameter to local parameter ( each arc has
//              Local parameter between [0 and 1] ) 
/**
 * Retrieves the local parameter and the arc number of
 * this CATKnotVector global parameter.
 * @param ioLocalParameter
 * The local parameter on <tt>oArcNum</tt>.
 * @param ioArcNum
 * The arc number starting at 1.
 */
    virtual void                       ConvertGlobalToLocalParameter
                                                               (const double                    & iGlobalParameter   ,
                                                                      double                    & ioLocalParameter   ,
                                                                      CATLONG32                 & ioArcNum           )       const  ;
//--->  convert Local parameter to global parameter ( each arc has
//              Local parameter between [0 and 1] ) 
 /**
 * Retrieves the global parameter associated with a local parameter and an
 * arc number of <tt>this</tt> CATKnotVector.
 * @param iLocalParameter
 * The local parameter on <tt>iArcNum</tt>.
 * @param iArcNum
 * The arc number.
 * @param ioGlobalParameter
 * The corresponding global parameter.
 */
    virtual void                       ConvertLocalToGlobalParameter
                                                               (const double                    & iLocalParameter    ,
                                                                const CATLONG32                 & iArcNum            ,
                                                                      double                    & ioParameter        )       const;
//
//--->  Give minimum continuity on a domain
/**
 * Tests whether a given continuity order of the related basis
 * is garanteed on a subparameter domain.
 * @param iContinuityOrder
 * The global continuity (0,1,2) to test.
 * @param iStartArcNum
 * The number of the first arc of the domain.
 * @param iEndArcNum
 * The number of the last arc of the domain.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if the continuity is garanteed, <tt>FALSE</tt> otherwise.
 */
            CATBoolean                 IsContinuousOnDomain    (const CATLONG32                 & iContinuityOrder   ,
                                                                const CATLONG32                 & iStartArcNum       ,
                                                                const CATLONG32                 & iEndArcNum         )       const;
//
// Advanced Utilities
//
/**
 * Retrieves an array of pointers on the polynoms defined by <tt>this</tt> CATKnotVector
 * involved in one arc.
 *<br>For advanced use.
 * @param iArcNum
 * The arc number.
 * @param ioPolynom
 * The array of <tt>KnotVector.GetDegree + 1</tt>
 * pointers on polynoms of degree <tt>KnotVector.GetDegree</tt>.
 * These polynoms are reparametrized in <tt>[0,Knots[iArcNum +IndexOffset-1]-Knots[iArcNum +IndexOffset]]</tt>
 * If a pointer is NULL in the array, the polynom is created and you then have to deleted it after use. 
 */
            void                       PolynomialBasisForOneArc(const CATLONG32                 & iArcNum            ,
                                                                      CATMathPolynomX         **  ioPolynom          )       const;

/**
 * Retrieves a bi-dimensional array of pointers on the polynoms defined by
 * <tt>this</tt> CATKnotVector.
 *<br>For advanced use.
 * @param ioPolynom
 * The array of <tt>KnotVector.GetNumberOfArcs</tt>
 * pointers on array of <tt>KnotVector.GetDegree + 1</tt>
 * pointers on polynoms of degree <tt>KnotVector.GetDegree</tt>.
 * These polynoms are reparametrized in <tt>[0,Knots[ArcNum]-Knots[ArcNum-1]]</tt> where Arcnum
 * is the current arc number in array.
 * If a pointer is NULL in the array, the polynom is created and you then have to deleted it after use.
 */
            void                       PolynomialBasisForAllArcs(     CATMathPolynomX        ***  ioPolynom          )       const;

/**
 * Returns the array of pointers on the polynoms defined by <tt>this</tt> CATKnotVector
 * involved in one arc.
 *<br>For advanced use.
 * @param iArcNum
 * The arc number starting at 1.
 *<br>The returned array pointer is part of  CATKnotVector local data.
 *<br>This method must be recalled after any non const method applied on the CATKnotvector
 *<br>The array consists of <tt>KnotVector.GetDegree + 1</tt>
 * pointers on polynoms of degree <tt>KnotVector.GetDegree</tt>.
 * These polynoms are reparametrized in <tt>[0,Knots[iArcNum +IndexOffset-1]-Knots[iArcNum +IndexOffset]]</tt>.
 */
      const CATMathPolynomX* const * GetPolynomialBasisForOneArc(const CATLONG32                & iArcNum            )       const;

/**
 * Returns the array of pointers on the polynoms defined by <tt>this</tt> CATKnotVector.
 *<br>For advanced use.
 *<br>The returned array pointer is part of  CATKnotVector local data.
 *<br>This method must be recalled after any non const method applied on the CATKnotvector
 * The array consists of  <tt>KnotVector.GetNumberOfArcs *( KnotVector.GetDegree + 1)</tt>
 * pointers on polynoms of degree <tt>KnotVector.GetDegree</tt>.
 * These polynoms are reparametrized in <tt>[0,Knots[ArcNum]-Knots[ArcNum-1]]</tt> where Arcnum
 * is the current arc number in array.
 */
      const CATMathPolynomX* const * GetPolynomialBasisForAllArcs()                                                          const;

/**
 * Shifts a position into the expanded CATKnotVector.
 *<br>For advanced use.
 *<br>The extented knot vector is the array of knot values as many repeated as
 * the multiplicity order. The expanded vector of the introduction sample is
 * the following series:
 *<dl><dt>expanded knot<dd><tt> 0, 0, 0, 0, 2, 8, 9, 9, 9, 9</tt>
 *    <dt>knot repetition<dd><tt> 1, 2, 3, 4, 1, 1, 1, 2, 3, 4</tt></dl>
 * @param ioKnotIndex
 * The index (starting at 0) of the knot value of a CATKnotVector to shift 
 *(resp being shifted).
 * @param ioKnotRep
 * The corresponding knot repetition value to shift (resp being shifted).
 * @param iMove
 * The shift to operate to the corresponding point into the expanded knot
 * vector.
 *<pre>
 * CATLONG32 ioKnotIndex = 0, ioKnotRep = 2, iMove = 5;
 * KnotVector.MoveInExtendedKnotVector(ioKnotIndex,ioKnotRep,iMove)
 * cout << "new knot index=" << ioKnotIndex << endl; 
 * cout << "corresponding knot repetition=" << ioKnotRep << endl;</pre>
 * gives
 * <pre><i>
 * new knot index= 3
 * corresponding knot repetition= 1</i></pre>
 */
            void                       MoveInExtendedKnotVector(      CATLONG32                 & ioKnotIndex        ,
                                                                      CATLONG32                 & ioKnotRep          ,
                                                                const CATLONG32                 & iMove              )       const;




  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/** 
 * @nodoc
 * Returns the right index offset.
 * @return
 * The value of the right index offset.
 * WARNING : this data is not streamed.
 */
    INLINE  short                      GetRightIndexOffset     ()                                                            const;

/** 
 * @nodoc
 * Returns the original degree.
 * @return
 * The value of the original degree.
 * WARNING : this data is not streamed.
 */
    INLINE  short                      GetOriginalDegree       ()                                                            const;

/** 
 * @nodoc
 * Modifies the right index offset.
 * @param iRightOffset
 * The new value of the right index offset.
 * WARNING : this data is not streamed.
 */
    INLINE void                        SetRightIndexOffset     (      short                       iRightOffset       );

/** 
 * @nodoc
 * Modifies the original degree.
 * @param iOriginalDegree
 * The new value of the Original Degree.
 * WARNING : this data is not streamed.
 */
    INLINE  void                       SetOriginalDegree       (      short                       iOriginalDegree    );


/**
 * @nodoc
 * Returns the array of pointers on the Shifted polynoms defined by this CATKnotVector
 * involved in one arc.
 *<br>For advanced use.
 * It works exactely as equivalent non shifted method except the output type
 * The advantage of shifted polynom is a more accurate evaluation .  
 */
     const  CATMathPolynomX * const *  GetShiftedPolynomialBasisForOneArc (const CATLONG32      & iArcNum             )      const;

/**
 * @nodoc
 * Returns the array of pointers on the Shifted polynoms defined by this CATKnotVector.
 *<br>For advanced use.
 * It works exactely as equivalent non shifted method except the output type
 * The advantage of shifted polynom is a more accurate evaluation .  
 */ 
    const   CATMathPolynomX * const *  GetShiftedPolynomialBasisForAllArcs()                                                 const;

/**
 * @nodoc
 * Returns the global parameter corresponding approximatively to
 * a control point.
 *<br>For advanced use. A control point does not belong to the curve, it is the
 * raison why the parameter is approximated.
 *<br>The number of the control point starts from 1.
 */
            double                     ParameterAssociatedToVertexRank (const CATLONG32         & iExpandedKnotNum   )       const;

/**
 * @nodoc
 * Retrieves the arcs where a basis function is not equal to 0.
 *<br>The numbers start at 1.
 *<br>For advanced use.
 */
            void                       ArcsDependingOnOneVertex        (const CATLONG32         & iExpandedKnotNum   ,
                                                                              CATLONG32         & oFirstArcNum       ,
                                                                              CATLONG32         & oLastArcNum        )       const;

/**
 * Retrieves the first control point which acts on an arc.
 *<br>There is always <tt>Degree+1</tt> control points acting on one arc. The
 * last point to act is then <tt>FirstVertexNum+Degree</tt>.
 *<br>For advanced use.
 *<br>The numbers start at 1.
 */
            void                       FirstVertexForOneArc            (const CATLONG32         & iArcNum            ,
                                                                              CATLONG32         & oFirstVertexNum    )       const;

/**
 * @nodoc
 * Returns the knot index from the virtual knot index.
 *<br>For advanced use.This method allows to access actual storage index when 
 * working in periodic case. In this case, the knots values are periodic, 
 * but only  one period is stored.
 * @param iVirtualKnotIndex
 * The index (starting at 0) into the virtual knot values array. 
 * @return 
 * The real index (starting start at 0) of the knot value .
 */
            CATLONG32                  VirtualToReal           (const CATLONG32                 & iVirtualKnotIndex  )       const;
//--->  Give real Vertex Index from Virtual Vertex index
/**
 * @nodoc
 * Returns the vertex index from the expanded virtual vertex index
 *<br>For advanced use. This method allows to access actual storage index when 
 * working in periodic case. In this case, the control points are periodic, 
 * but only  one period is stored.
 * @param iExpandedVirtualKnotIndex
 * The index (starting at 0) into the expanded virtual vertices array.
 * @return 
 * The real index (starting at 0) of the vertex.
 */
            CATLONG32                  VirtualToRealVertex     (const CATLONG32                 & iExpandedVirtualKnotIndex) const;

/**
 * @nodoc
 * This is a service method to the method "PolynomialsDiffByKnots". 
 * oSmallSize: Tells the needed size for each of ioKnotIndices,
 *             ioVertIndices and ioLocalNrOfPoly.
 * oBigSize:   Tells the number of differentiated polynomials. 
 */

            void                       SizeOfDiffByKnots       (      CATLONG32                 & oSmallSize         ,
                                                                      CATLONG32                 & oBigSize           ,
                                                                const CATLONG32                *  iVariableKnots     = NULL,
                                                                const CATLONG32                *  iArcs              = NULL ) const ;

/**
 * @nodoc
 * Polynomials (Poly) differentiated with respect to knots (Knot).
 * (Conceptually: D(Poly)/D(Knot).) 
 * 
 * GENERAL:         Arc, vertex and knot indices are supposed to 
 *                  start at zero, both at input and output!
 *                  The shift value, at reulting polynomials, are
 *                  set to the centre of the parameter inteval of
 *                  the corresponding arc.
 *
 * IN ( optional ):
 * 
 * iArcs:           The arcs where the polynomials are calculated. 
 *                  If not given we consider all = 1, 1, ..., 1.
 *
 * iVariableKnots:  The variable knots. If not given we consider 
 *                  all except the ends = 0, 1, 1, ..., 1, 0.
 * 
 * OUT ( allocate all objects first! See the method
 *                  "SizeOfDiffByKnots" ) :
 *     
 * ioDPolyDKnot:    The differentiated polynoms.
 * 
 * For variable knots, not being at the arc end points, less than 
 * _degree+1 poynomials and vertices are relevant. To store only 
 * non zero polynomials and keep order, we use the following 
 * arrays. To examplify, we suppose that iArc[i] = 1:
 *
 * ioLocalNrAtArc:  At the i:th arc this tells the number of 
 *                  relevant knots. The succesive acumulation of
 *                  these numbers tells, for this arc, the start 
 *                  and end index in the following three arrays:
 * 
 * ioKnotIndices    The indices of the relevant knots at this arc. 
 *                  
 * ioLocalNrOfPoly: The number of non zero polynomials for each
 *                  knot at this arc.
 *
 * ioVertIndices:   The indices of the first vertices related to   
 *                  each knot at this arc.
 * 
 * OPTIONS: ioPoly: During the differentiation, also all steps in
 *                  the calculation of the non differentiated 
 *                  polynomials must be done. However, this do not
 *                  update the private data of "this" knot vector. 
 *
 *      iWorkArray: For repeated use a repeated internal allocation 
 *                  may be avoided by supporting this array. A safe 
 *                  size is: ( order*order + 1 )*( 2*order - 1 ).
 *
 */

             void                      PolynomialsDiffByKnots  (      CATMathPolynomX         **  ioDPolyDKnot       ,
                                                                      CATLONG32                *  ioLocalNrAtArc     ,
                                                                      CATLONG32                *  ioKnotIndices      ,
                                                                      CATLONG32                *  ioLocalNrOfPoly    ,
                                                                      CATLONG32                *  ioVertIndices      ,
                                                                      CATLONG32                *  iVariableKnots     = NULL,
                                                                      CATLONG32                *  iArcs              = NULL,
                                                                      CATMathPolynomX         **  ioPoly             = NULL,
                                                                      double                   *  iWorkArray         = NULL ) const ;

/** @nodoc */
     INLINE  CATULONG32                GetSize                 ()                                                             const;

/** @nodoc  */
             size_t                    GetEstimatedMemoryBytes ()                                                             const;

/** @nodoc  */
    virtual  size_t                    GetDynamicMemoryBytes   ()                                                             const;

/** @nodoc  */
    virtual size_t                     GetStaticMemoryBytes    ()                                                             const;

// Pour stream compact

/** @nodoc  */
            int                        GetStreamSortingKey     (      CATCGMStream              & Str                )        const;

/** @nodoc  */
            int                        HasCommonStreamData     (const CATKnotVector            *  ipKVToCompare      ,
                                                                      CATCGMStream              & Str                )        const;

/** @nodoc  */
            size_t                     EstimateCommonStreamDataSize(  int                         iSimilarityLevel   ,
                                                                      CATCGMStream              & Str                )        const;

/** @nodoc  */
            void                       CopyCommonStreamData    (const CATKnotVector            *  ipKVToCompare      ,
                                                                      int                         iSimilarityLevel   ,
                                                                      CATCGMStream              & Str                );


private:

//========Data==================
            short                      _Degree            ;
            CATBoolean                 _IsPeriodic        ;
            CATBoolean                 _IsUniform         ;
            short                      _KnotsCount        ;
            short                      _VerticesCount     ;
            short                      _CurrentLoop       ;
            short                      _CurrentArcRank    ;
            double                   * _Knots             ; // [KnotsCount]
            short                    * _Multiplicities    ; // [KnotsCount]
            short                      _Offset            ; //
            short                      _RightOffset       ; // (Not streamed)
            short                      _OriginalDegree    ; // (Not streamed)
            //                         ---> Optimization data (Not streamed)
            short                      _Optimization_Data ; // =1 if Optimization data allocated and initialized
            short                    * _IsUpToDate        ; // basis for arc are up to date
            CATMathPolynomX         ** _Polynoms          ; // basis for arc (_Polynoms[ArcsCount*Order])
            short                    * _IsUpToDateShifted ; // basis for arc are up to date
            CATMathPolynomX         ** _ShiftedPolynoms   ; // basis for arc (_Polynoms[ArcsCount*Order])

    const   CATTolerance             * _TolObject         ;

  // Debug and management. Do not move this data *_R18Restricted in R18:
  // must be extraneous data at the end of the class, after all old data already used in CAA applications
            int                        _KnotVectorNumber_R18Restricted ;
            int                        _InternalUse_R18Restricted ;
public:
            int                        _PrivateDoNotUseNotScaled_R18Restricted ;

private:

  //int _SpecialCaseStandardScaleAssumed ; //NLD180108
//========Private Methods==================
  //--->  Control of data consistency.
            CATError*                  ControlKnotVector       (      int                         iFreeDataIfError   ,
                                                                const CATTolerance             *  iTolObject         = 0,
                                                                      int                         iSpecialCaseStandardScaleAssumed = 0);

  //--->  Optimization Data Management
            void                       InitOptimizationData    ();

            void                       DelOptimizationData     (); // CAUTION: direct call from some friend classes

            void                       UpdatePolynomsForOneArc (      CATLONG32                   iIsShifted         ,
                                                                      CATLONG32                   iArcIndex          )       const;

            void                       UpdatePolynomsForAllArcs(      CATLONG32                   iIsShifted         )       const;

            void                       InitData                ();

            // Set Data for Uniform KnotVector
            void                       SetData                 (const CATTolerance              & iTolObject         ,
                                                                      CATError                 *& oError             ,
                                                                const CATLONG32                 & iDegree            ,
                                                                const CATLONG32                 & iIsPeriodic        ,
                                                                const CATLONG32                 & iArcsCount         ,
                                                                const double                      iKnotStart         ,
                                                                const double                      iStep              ,
                                                                const CATLONG32                   iIndexOffset       );

            // Set Data for NonUniform KnotVector
            void                       SetData                 (const CATTolerance              & iTolObject         ,
                                                                      CATError                 *& oError             ,
                                                                const CATLONG32                 & iDegree            ,
                                                                const CATLONG32                 & iIsPeriodic        ,
                                                                const CATLONG32                 & iKnotsCount        ,
                                                                const double                   *  iKnots             ,
                                                                const CATLONG32                *  iMultiplicities    ,
                                                                const CATLONG32                   iIndexOffset
                                                               );



//--->  Initialize the number of control points.
            void                       ComputeNumberOfControlPoints ();


//////////////////////////////////////////////////////////////////////
// deBoor-Cox metod generalized to differentiation. Calculates 
// differentiated polynomials at one arc.
//
// Input:
// iK:       Let r be the degree. iK is a part of an extended knot 
//           vector such that [iK[r], iK[r+1]] is the relevant interval 
//           of evaluation. For optimal precision, iK is recomended to 
//           be "shifted", i.e. moved such that iK[r] = -iK[r+1].
// iNr:      The number of relevant indices in "iDiffInd" next.
// iDiffInd: The indices of variable knots in iK.
//
// Output:
// ioPoly:   The B-spline basis functions.
// ioDpol:   The basis functiond differentiated with respedt to the 
//           variable knots in iK.      
//////////////////////////////////////////////////////////////////////

            void                       DiffOfBasePolynomials   (const double                   *  iK                 ,
                                                                const CATLONG32                   iNr                ,
                                                                const CATLONG32                *  iDiffInd           ,
                                                                      double                   *  ioPoly             ,
                                                                      double                   *  ioDpol             )       const ;

//////////////////////////////////////////////////////////////////
// Administrates the calculation of differentiated polynomials
// at one arc. 
// Interfaces between the public method "PolynomialsDiffByKnots" 
// and the private method "DiffOfBasePolynomials"
//
// iVariableKnots:   See "PolynomialsDiffByKnots".
// iArcNr:           Obvious.
// ioPoly & ioDpoly: See "DiffOfBasePolynomials"
// ioKnot:           Work area vector of size 2*_Degree 
// ioVariKnot:       Work area vector of size 2*_Degree 
//////////////////////////////////////////////////////////////////

            void                       DiffPolynomials         (const CATLONG32                *  iVariableKnots     ,
                                                                const CATLONG32                   iArcNr             ,
                                                                      double                   *  ioPoly             ,
                                                                      double                   *  ioDpoly            ,
                                                                      double                   *  ioKnot             ,
                                                                      CATLONG32                *  ioVariKnot         ) const ;


//friend class CATSurfaceCGM;
//friend class CATCurveCGM;
//friend class CATCGMDebugImpl;
  friend class CATKnotVectorInternal;

};

//
// ------------------------------------------------------------------------------
//
// Inlines
//
// ------------------------------------------------------------------------------
//
INLINE CATBoolean CATKnotVector::IsPeriodic               ()                                                      const
{
 return _IsPeriodic;
}
//
// ------------------------------------------------------------------------------
INLINE CATBoolean CATKnotVector::IsUniform                ()                                                      const
{
 return _IsUniform;
}
//
// ------------------------------------------------------------------------------
INLINE short      CATKnotVector::GetDegree                ()                                                      const
{
 return _Degree;
}
//
// ------------------------------------------------------------------------------
INLINE short      CATKnotVector::GetNumberOfControlPoints ()                                                      const
{
 return  _VerticesCount;
}
//
// ------------------------------------------------------------------------------
INLINE short      CATKnotVector::GetNumberOfArcs          ()                                                      const
{
 return _KnotsCount - 1;
}
//
// ------------------------------------------------------------------------------
INLINE short      CATKnotVector::GetNumberOfKnots         ()                                                      const
{
 return _KnotsCount;
}
//
// ------------------------------------------------------------------------------
INLINE void       CATKnotVector::GetKnots                 ( const double *&ioKnots)                               const
{
 ioKnots = _Knots;
}
// 
//---------------------------------------------
INLINE short      CATKnotVector::GetIndexOffset           ()                                                      const
{
 return _Offset;
}
// 
//--------------------------------------------------------------------------------
INLINE void       CATKnotVector::SetIndexOffset           (const CATLONG32 &iIndexOffset) 
{
 _Offset = (short)iIndexOffset;
}
//
//---------------------------------------------
INLINE short      CATKnotVector::GetRightIndexOffset      ()                                                      const
{
  return _RightOffset;
}
//
//--------------------------------------------------------------------------------
INLINE void       CATKnotVector::SetRightIndexOffset      (short iRightOffset)
{
  _RightOffset = iRightOffset;
}
//
//--------------------------------------------------------------------------------
INLINE short      CATKnotVector::GetOriginalDegree        ()                                                      const
{
  return _OriginalDegree;
}
//
//--------------------------------------------------------------------------------
INLINE void       CATKnotVector::SetOriginalDegree        (short iOriginalDegree)
{
 _OriginalDegree = iOriginalDegree;
}

//--------------------------------------------------------------------------------
INLINE CATULONG32 CATKnotVector::GetSize                  ()                                                      const
{
 return (CATULONG32 ) GetDynamicMemoryBytes();
}

// ------------------------------------------------------------------------------
// static methods
//--------------------------------------------------------------------------------
// avoids knot vector domain control for knot vectors not depending on scale
ExportedByYP00IMPL void SetNotScaledKnotVector(CATKnotVector& iKnotVector) ;


#endif
