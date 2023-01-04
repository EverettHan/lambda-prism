//====================================================================
// Copyright Dassault Systemes Provence 2008, all rights reserved 
//====================================================================
//
//======================================================================
// June,     17 th 2008 : RNO : Suppression IsPeriodic et methodes pas utiles
// Jan,      29 th 2008 Creation                                    ANR
//======================================================================
#ifndef CATSapKnotVector_H
#define CATSapKnotVector_H 

#include "CATSapApprox.h"

#include <stdio.h>  

#include "CATIACGMLevel.h"

#ifdef CATIACGMV5R18
//#define CATSapKnotVectorWithTolerance 
#include "CATCGMVirtual.h"
#include "CATCGMNewArray.h"
#endif
#include "CATTolerance.h"

#include "CATMathDef.h"
#include "CATMathInline.h"

class CATMathPolynomX ;
class CATCGMStream; 
class CATError;

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
/*#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
*/

/**
 * Class containing all the data necessary to define 
 * a uniform or non uniform, non periodic basis.
 *----------------------------------------
 * NOTE: PERIODIC NURBS ARE NOT SUPPORTED IN SAPKnotVector.
 *----------------------------------------
 *<br> A <b>basis</b> is a set of piecewise polynomial functions
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
 *<table>
 * <tr><td></td><td>Multiplicity</td><td>Continuity order</td></tr>
 * <tr><td>single knot value</td><td><tt>1</tt></td><td><tt>Degree-1</tt></td></tr>
 * <tr><td>internal knot values</td><td><tt>1<=m<=degree</tt></td>
 *     <td><tt>Degree-m</tt></td></tr>
 * <tr><td>extreme knot values for a non periodic basis</td>
 *     <td><tt>degree+1 </tt>(by convention)</td><td><tt>(-1)</tt></td></tr>
 * <tr><td>same first and last knot values for a periodic basis</td>
 *     <td><tt>1<=m<=degree</tt></td><td><tt>Degree-m </tt></td></tr>
 *</table>
 * The number of arcs where 
 * the polynom is not null depends on the knot vector mutiplicities.
 *<br>Associating each basis
 * function to a <b> control point</b> (also called <b>vertex</b>),
 * allows the definition of Nurbs geometric
 * elements. A basis function represents the influence of one control point.
 * Note that vertices are not data of the knot vector, but of
 * the Nurbs polynomial element. Nevertheless, vertex ranks are handled in
 * methods of this class, because they are equivalent to the polynomial
 * basis ranks.
 *<br>A CATSapKnotVector is a transient object, it can be  saved as private data of a
 *  curve or a surface. 
 *A CATSapKnotVector is defined with:
 *<table>
 *<tr><td>CATLONG32</td> <td>Degree</td>
 *        <td> The degree of the B-Spline basis functions</td></tr>
 *<tr><td>CATBoolean</td> <td>IsPeriodic</td>
 *        <td> 1 for a periodic basis: the parameter domain is unlimited.
 * If <tt>Delta= LastKnotValue - FirstKnotValue</tt>,
 * the evaluations at <tt>Parameter + Delta</tt> and <tt>Parameter</tt> are
 * the same.
 *        <br> 0 otherwise</td></tr>
 *<tr><td>CATBoolean</td> <td>IsUniform</td>
 *        <td> 1 in case of equally spaced knot values.
 *         <br>0 otherwise.</td></tr>
 *<tr><td>CATLONG32</td> <td>NbOfKnots</td>
 *        <td> The number of knot values ( <tt>=NbOfArcs + 1</tt></td></tr>
 *<tr><td>CATLONG32</td> <td>Knots</td>
 *        <td> The array of the knots values </td></tr>
 *<tr><td>CATLONG32</td> <td>Multiplicities</td>
 *        <td> The array of the multiplicity of a knot value</td></tr>
 *</table>
 *<br>Sample of a non periodic non uniform knot vector, with C2 continuity:
 *<table>
 *<tr><td>CATLONG32</td> <td>Degree</td>
 *        <td> 3 </td></tr>
 *<tr><td>CATBoolean</td> <td>IsPeriodic</td>
 *        <td>  0 </td></tr>
 *<tr><td>CATBoolean</td> <td>IsUniform</td>
 *        <td> 0 </td></tr>
 *<tr><td>CATLONG32</td> <td>NbOfKnots</td>
 *        <td> 4</td></tr>
 *<tr><td>CATLONG32</td> <td>Knots</td>
 *        <td> 0 , 2 , 8 , 9 </td></tr>
 *<tr><td>CATLONG32</td> <td>Multiplicities</td>
 *        <td> 4 , 1 , 1 , 4</td></tr>
 *</table>
 */
 
//#define DBGSAPCONTROLKNOT "Verife a la creation des KNOTVector"
class CATSapKnotVector;
//Duplicate iToCopy if iToCopy is not a AutoSap else return the AutoSapPtr
ExportedByCATSapApprox
CATSapKnotVector * CATSapKnotVectorSmartCopy(CATSapKnotVector * iToCopy);
//Delete  iToCopy if it's not a AutoSap else simply nullify iToDel
ExportedByCATSapApprox
void CATSapKnotVectorSmartDelete(CATSapKnotVector *& iToDel);

class ExportedByCATSapApprox CATSapKnotVector : public CATCGMVirtual
{
public:

//
//- Constructors
//    
  /**
 * Constructs a Bezier CATSapKnotVector.
 * <br>It corresponds to one arc of degree <tt>iDegree</tt>.
 * @param iDegree
 * The degree of the polynomial basis.
 */
  CATSapKnotVector ( const CATLONG32 iDegree=3); 
  

/**
 * Constructs a non-uniform CATSapKnotVector.
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
 
CATSapKnotVector (const CATLONG32 &iDegree,
	       const CATLONG32 &iIsPeriodic,
	       const CATLONG32 &iNbOfKnots,
	       const double * iKnots,
	       const CATLONG32* iMultiplicities,
         const CATLONG32 iIndexOffset=0 );


//Copy Ctor
CATSapKnotVector (const CATSapKnotVector & iKnotVector);

/** 
 * Assignment operator.
 *<br>Desallocates and reallocates the left operand, except if it is the
 * same object as the right operand (<tt>iKnotVectorToAffect</tt>).
 */
CATSapKnotVector & operator = (const CATSapKnotVector & iKnotVectorToAffect);

/**
 * Destructor.
 */
 virtual ~CATSapKnotVector();

 //Is this Sap Knot Vector an Auto one (so you must not not delete it)
 virtual INLINE CATBoolean IsAKnotVectorAuto() const;

//
//-----Read
//
/**
 * Tests if a CATSapKnotVector defines a periodic basis.
 * @return
 * <dl> <dt> <tt>FALSE</tt><dd> if the basis is not periodic
 *      <dt> <tt>TRUE</tt> <dd> if the basis is periodic (NOT SUPPORTED)</dl>
 */
//INLINE CATBoolean IsPeriodic () const ;

/**
 * Tests if a CATSapKnotVector defines a uniform basis.
 * @return
 * <dl> <dt> <tt>FALSE</tt> <dd> if the basis is not uniform
 *      <dt> <tt>TRUE</tt> <dd> if the basis is uniform </dl>
 */
INLINE CATBoolean IsUniform () const ;

/**
 * Returns the degree of the basis defined by <tt>this</tt> CATSapKnotVector.
 * @return
 * The degree.
 */
INLINE short GetDegree () const ;

/**
 * Returns the number of necessary control points for a nurbs using <tt>this</tt>
 * CATSapKnotVector.
 * @return
 * The number of control points.
 */
INLINE short GetNumberOfControlPoints () const ;

/**
 * Returns the number of arcs of a nurbs using <tt>this</tt> CATSapKnotVector.
 * @return
 * The number of arcs.
 */
INLINE short GetNumberOfArcs () const ;

/**
 * Returns the number of distinct knot values of <tt>this</tt> CATSapKnotVector.
 * @return
 * The number of distinct knot values.
 */
INLINE short GetNumberOfKnots () const ;

/**
 * Returns the multiplicity of <tt>this</tt> CATSapKnotVector knot value.
 * @param iKnotNum
 * The knot number ( from 1 to <tt>KnotVector.GetNumberOfKnots </tt>)
 */
CATLONG32 GetKnotMultiplicity (const CATLONG32 &iKnotNum) const ;

/**
 * Returns the pointer to the knot values array of <tt>this</tt> CATSapKnotVector.
 * @param oKnots
 * The array of the knots. As part of the knot vector, it is deleted at the knot vector deletion.
 */
INLINE void GetKnots (const double *&oKnots) const ;  

void GetMultiplicities(const short *& oMultiplicities) const;
// 
//
// Advanced Utilities
// 

/**
 * Retrieves a bi-dimensional array of pointers on the polynoms defined by
 * <tt>this</tt> CATSapKnotVector.
 *<br>For advanced use.
 * @param ioPolynom
 * The array of <tt>KnotVector.GetNumberOfArcs</tt>
 * pointers on array of <tt>KnotVector.GetDegree + 1</tt>
 * pointers on polynoms of degree <tt>KnotVector.GetDegree</tt>.
 * These polynoms are reparametrized in <tt>[0,Knots[ArcNum]-Knots[ArcNum-1]]</tt> where Arcnum
 * is the current arc number in array.
 * If a pointer is NULL in the array, the polynom is created and you then have to deleted it after use.
 */
/*
//PAs besoin desactivation
void PolynomialBasisForAllArcs (CATMathPolynomX *** ioPolynom )const;
 */

/**
 * Returns the array of pointers on the polynoms defined by <tt>this</tt> CATSapKnotVector.
 *<br>For advanced use.
 *<br>The returned array pointer is part of  CATSapKnotVector local data.
 *<br>This method must be recalled after any non const method applied on the CATSapKnotVector
 * The array consists of  <tt>KnotVector.GetNumberOfArcs *( KnotVector.GetDegree + 1)</tt>
 * pointers on polynoms of degree <tt>KnotVector.GetDegree</tt>.
 * These polynoms are reparametrized in <tt>[0,Knots[ArcNum]-Knots[ArcNum-1]]</tt> where Arcnum
 * is the current arc number in array.
 */
const CATMathPolynomX * const * GetPolynomialBasisForAllArcs ()const;

const CATMathPolynomX * const * GetShiftedPolynomialBasisForAllArcs ()const;

/**
 * Shifts a position into the expanded CATSapKnotVector.
 *<br>For advanced use.
 *<br>The extented knot vector is the array of knot values as many repeated as
 * the multiplicity order. The expanded vector of the introduction sample is
 * the following series:
 *<dl><dt>expanded knot<dd><tt> 0, 0, 0, 0, 2, 8, 9, 9, 9, 9</tt>
 *    <dt>knot repetition<dd><tt> 1, 2, 3, 4, 1, 1, 1, 2, 3, 4</tt></dl>
 * @param ioKnotIndex
 * The index (starting at 0) of the knot value of a CATSapKnotVector to shift 
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
void MoveInExtendedKnotVector(CATLONG32 &ioKnotIndex,CATLONG32 &ioKnotRep,const CATLONG32 &iMove) const;

 
 

/**
 * @nodoc
 * Returns the array of pointers on the Shifted polynoms defined by this CATSapKnotVector.
 *<br>For advanced use.
 * It works exactely as equivalent non shifted method except the output type
 * The advantage of shifted polynom is a more accurate evaluation .  
 */ 
/*
//SapKNOtVector CAN NOT BE SHIFTED !!!
const CATMathPolynomX * const * GetShiftedPolynomialBasisForAllArcs ()const;
*/  

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
//Pas utilise on coupe
//CATLONG32 VirtualToReal(const CATLONG32 &iVirtualKnotIndex)const;
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
//Pas utilise on coupe
//CATLONG32 VirtualToRealVertex(const CATLONG32 &iExpandedVirtualKnotIndex)const;
  

  //Necessaire pour RNO :
  // ------------------------------------------------------------------------------
  //--->  Give Vertices involved in one Arc computation ( Ordre vertices from FirstVertexRank)
  void FirstVertexForOneArc(const CATLONG32 &iArcNum, CATLONG32 &oFirstVertexRank) const;
  const CATMathPolynomX * const * GetShiftedPolynomialBasisForOneArc (const CATLONG32 &iArcNum)const;
  const CATMathPolynomX * const * GetPolynomialBasisForOneArc (const CATLONG32 &iArcNum)const;
  void UpdatePolynomsForOneArc(CATLONG32 iIsShifted,CATLONG32 iArcIndex)const ;

  double ParameterAssociatedToVertexRank (const CATLONG32 &iVertexRank) const;
  /*void ConvertLocalToGlobalParameter( const double &iLocalParameter,
                                                  const CATLONG32 &iArcNum,
                                                  double &oParameter) const ;
  void ConvertGlobalToLocalParameter(const double &iParameter,
                                                  double &oLocalParameter,
                                                  CATLONG32 &oArcNum ) const ;
  CATLONG32 SearchArcFromParameter(const double &iParameter) const ;
*/
      
  //Dump Dumper
  //void Dump(ostream * iStream=0L);
protected:

//========Data==================
  short _Degree ;
  //CATBoolean _IsPeriodic;
  CATBoolean _IsUniform;
  short _KnotsCount ;
  short _VerticesCount ;
  short _CurrentLoop;
  //short _CurrentArcRank ;
  double * _Knots ;  // [KnotsCount]
  short * _Multiplicities ;  // [KnotsCount]
  short _Offset ; // 
  short _RightOffset;    // (Not streamed)
  short _OriginalDegree; // (Not streamed)
//---> Optimization data (Not streamed)
  short _Optimization_Data ; // =1 if Optimization data allocated and initialized
  short * _IsUpToDate; // basis for arc are up to date
  CATMathPolynomX **_Polynoms ; // basis for arc (_Polynoms[ArcsCount*Order])
  short * _IsUpToDateShifted; // basis for arc are up to date
  CATMathPolynomX **_ShiftedPolynoms ; // basis for arc (_Polynoms[ArcsCount*Order])


  #ifdef CATSapKnotVectorWithTolerance
  const CATTolerance  *_TolObject ;
  #endif

  
  int _CheckMonotonyWithTolerance ;
  //int _SpecialCaseStandardScaleAssumed ; //NLD180108
//========Private Methods==================
  //--->  Control of data consistency.
#ifdef DBGSAPCONTROLKNOT
  int _CATMAXKnotsCount ;
  int ControlKnotVector (int iFreeDataIfError, 
                                 const CATTolerance* iTolObject=0,
                                 int iSpecialCaseStandardScaleAssumed=0);       
#endif
  //--->  Optimization Data Management
  void InitOptimizationData();
  void DelOptimizationData();          
  virtual void UpdatePolynomsForAllArcs(CATLONG32 iIsShifted) const;
  void InitData();
 #ifdef DBGSAPCONTROLKNOT
  int CATMAXKnotsCount() ;
#endif
  //void CATSetCheckKnotVectorMonotonyWithTolerance(int iSet, int& ioActive) ;

//--->  Initialize the number of control points.
void ComputeNumberOfControlPoints ();
				
};




//
// ------------------------------------------------------------------------------
//
// Inlines
//
// ------------------------------------------------------------------------------
//
/*
INLINE CATBoolean CATSapKnotVector::IsPeriodic() const 
{
  return _IsPeriodic;
}
*/
//
// ------------------------------------------------------------------------------
INLINE CATBoolean CATSapKnotVector::IsUniform() const 
{
  return _IsUniform;
}
//
// ------------------------------------------------------------------------------
INLINE short CATSapKnotVector::GetDegree() const 
{
  return _Degree;
}
//
// ------------------------------------------------------------------------------
INLINE short CATSapKnotVector::GetNumberOfControlPoints () const
{
  return  _VerticesCount;
}
//
// ------------------------------------------------------------------------------
INLINE short CATSapKnotVector::GetNumberOfArcs () const 
{
  return _KnotsCount-1;
}
//
// ------------------------------------------------------------------------------
INLINE short CATSapKnotVector::GetNumberOfKnots () const 
{
  return _KnotsCount;
}
//
// ------------------------------------------------------------------------------
INLINE void CATSapKnotVector::GetKnots ( const double *&ioKnots) const 
{
   ioKnots = _Knots;
} 

INLINE CATBoolean CATSapKnotVector::IsAKnotVectorAuto() const
{
  return(FALSE);
}

//  
#endif
