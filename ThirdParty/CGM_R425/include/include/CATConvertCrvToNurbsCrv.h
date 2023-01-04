#ifndef CATConvertCrvToNurbsCrv_H
#define CATConvertCrvToNurbsCrv_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

class CATNurbsCurve;
class CATPNurbs;
class CATFrFNurbsMultiForm;
class CATCrvParam;

#include "CATDataType.h"
#include "CATPGMCreateConvertCrvToNurbsCrv.h"
#include "CATListOfCATCurves.h"
#include "CATListOfCATFrFNurbsMultiForm.h"

#include "CATGMOperatorsInterfaces.h"
#include "CATIAV5Level.h"
#include "CATCGMVirtual.h"

/**
 * @deprecated V5R10 CATCrvFittingToNurbsCrv
 * Class defining a geometric operator that computes the NURBS representation of a CATCurve.
 * <br>The following conversions are available:
 * <ul>
 * <li>An input CATNurbsCurve or CATPNurbs is directly output: 
 * the <tt>GetResult</tt> method outputs the same pointer.
 * <li>A CATCircle and CATEllipse give a rational CATNurbsCurve.
 * <li>A CATSplineCurve and CATLine give a CATNurbsCurve.
 * <li>A CATPNurbs, CATPCircle, CATPEllipse, CATPSpline, CATPLine can always be converted into a CATPNurbs,
 * that is rational for a CATPCircle and a CATPEllipse.
 * Moreover, if the supporting surface is a CATPlane they can also be converted into a CATNurbsCurve.
 * <li>A CATPLine can be converted in a CATNurbsCurve, if it is an iso-parametric curve that can be retrieved
 * by its supporting surface (<tt>ExtractIsopar</tt>) as a curve of an other type than a CATPLine.
 * <li>The CATEdgeCurve is converted according to the types of its inside curves.
 * </ul>
 * The CATConvertCrvToNurbsCrv operator follows the global frame of the geometric operators: 
 *<ul>
 * <li>A CATConvertCrvToNurbsCrv operator is created with the <tt>CreateConvertCrvToNurbsCrv</tt> global method 
 * and must be
 * directly <tt>delete</tt>d with the usual C++ delete operator after use.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>In both cases, the result is accessed with the <tt>Getxxx</tt> methods. 
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATConvertCrvToNurbsCrv : public CATCGMVirtual
{
  public :

    virtual ~CATConvertCrvToNurbsCrv();

/**
 * Runs <tt>this</tt> operator (<tt>ADVANCED</tt> mode).
 */
    virtual void Run()=0;

/**
 * Runs <tt>this</tt> operator by keeping the same parameterization for the input
 * and resulting curve (<tt>ADVANCED</tt> mode).
 * @return
 * <tt>0</tt> if the the parameterization is not kept, <tt>1</tt> if it is kept.
 */
    virtual int RunWithSameParametrisation()=0;

/**
 * Defines the dimension of the output Nurbs (<tt>ADVANCED</tt> mode).
 * @param iOutputDim
 * The dimension of the output Nurbs. By default (<tt>BASIC</tt> mode), the output dimension is 3.
 * <br><b>Legal values</b>:
 * <dl>
 * <dt>2</dt><dd> The result is a CATPNurbs. In this case, use the
 * <tt>GetPNurbs</tt> method to retrieve it.
 * <dt>3</dt><dd> The result is a CATNurbsCurve. In this case, use the
 * <tt>GetNurbsCurve</tt> method to retrieve it.
 * </dl>
 */
    virtual void SetOutputDimension(const CATLONG32 &iOutputDim)=0;

/**
 * Returns the corresponding CATPNurbs, if the output dimension is 2.
 * @return
 * The pointer to the created CATPNurbs. Use the @href CATICGMContainer#Remove if you do not want
 * to keep it in the geometric factory.
 */
    virtual CATPNurbs *GetPNurbs() const=0;

/**
 * @nodoc
 * Returns the list of CATPNurbs, if the output dimension is 2.
 * @return
 * The pointer to list of the created CATPNurbs. Use the @href CATICGMContainer#Remove if you do not want
 * to keep the nurbs in the geometric factory, and <tt>delete</tt> the created list.
 */
    virtual CATLISTP(CATCurve) *GetListOfPNurbs()=0;
 
/**
 * Returns the corresponding CATNurbsCurve, if the output dimension is 3.
 * @return
 * The pointer to the created CATNurbsCurve. Use the @href CATICGMContainer#Remove if you do not want
 * to keep it in the geometric factory.
 */
    virtual CATNurbsCurve *GetNurbsCurve() const=0;
		
/**
 * @nodoc
 * Returns the list of CATNurbsCurve, if the output dimension is 3.
 * @return
 * The pointer to list of the created CATNurbsCurve. Use the @href CATICGMContainer#Remove if you do not want
 * to keep the nurbs in the geometric factory, and <tt>delete</tt> the created list.
 */ 
    virtual CATLISTP(CATCurve) *GetListOfNurbsCurves()=0;
 
/**
 * @nodoc
 */
    virtual CATFrFNurbsMultiForm *GetNurbsMultiForm() const=0;

/**
 * @nodoc
 */ 
    virtual CATLISTP(CATFrFNurbsMultiForm) *GetListOfNurbsMultiForm()=0;

/**
 * Maps a parameter on the initial curve to the corresponding parameter on the computed Nurbs representation.
 * @param iParamOnCurve
 * The parameter on the initial curve.
 * @return
 * The parameter on the computed Nurbs representation.
 */
    virtual CATCrvParam ComputeNewParameter(const CATCrvParam &iParamOnCurve)= 0;

/**
 * Avoids to create periodic Nurbs representation.
 * <br>By default, periodic representations can be created.
 */
    virtual void ForbidPeriodicity()= 0;

/**
 * Sets the Nurbs degree to 5 for input circle or ellipse.
 */
    virtual void ImposeQuinticConversion()= 0;
};

#endif
