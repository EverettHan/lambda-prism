#ifndef CATConvertSurToNurbsSur_H
#define CATConvertSurToNurbsSur_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

class CATNurbsSurface;
class CATSurParam;
class CATSurLimits;
class CATMathNurbsBipar;
class CATSoftwareConfiguration;

#include "CATPGMCreateConvertSurToNurbsSur.h"
#include "CATParameterizationOption.h"

#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"
#include "CATIAV5Level.h"
#include "CATCGMVirtual.h"

/** @nodoc */
enum CATFrFConvertionDiagnostic
{
  CatParameterizationKept = 0,
  CatParameterizationChanged = 1,
  CatNotConvertible = 2
};

/**
 * @deprecated V5R10 CATSurFittingToNurbsSur
 * Class defining a geometric operator that computes the NURBS representation of a CATSurface.
 *<br>The operator deals with the CATSphere, CATCylinder, CATTorus, CATCone and CATRevolution surfaces
 * and creates the corresponding rational CATNurbsSurface. CATPlane and CATTabulatedCylinder 
 * give a non rational CATNurbsSurface. For a CATNurbsSurface, the corresponding CATNurbsSurface
 * without extrapolation is created.
 * The CATConvertSurToNurbsSur operator follows the global frame of the geometric operators: 
 *<ul>
 * <li>A CATConvertSurToNurbsSur operator is created with the <tt>CreateConvertSurToNurbsSur</tt> global method 
 * and must be
 * directly <tt>delete</tt>d with the usual C++ operator after use.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>In both cases, the result is accessed with the <tt>Getxxx</tt> methods. 
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATConvertSurToNurbsSur : public CATCGMVirtual
{
  public :

    CATConvertSurToNurbsSur();
    virtual ~CATConvertSurToNurbsSur();

/**
 * @nodoc
 */
    virtual CATFrFConvertionDiagnostic IsConvertible(CATParameterizationOption iParameterizationOption)=0;

/**
 * @nodoc
 */
    virtual void SetMaxLimits(CATSurLimits &iMaxLimits)=0;

/**
 * Runs <tt>this</tt> operator (<tt>ADVANCED</tt> mode).
 */
    virtual void Run()=0;

/**
 * Runs <tt>this</tt> operator by keeping the same parameterization for the input
 * and resulting surface (<tt>ADVANCED</tt> mode).
 * @return
 * <tt>0</tt> if the the parameterization is not kept, <tt>1</tt> if it is kept.
 */
    virtual int RunWithSameParametrisation()=0;


/**
 * Returns the corresponding CATNurbsSurface.
 * @return
 * The pointer to the created CATNurbsSurface. Use the @href CATICGMContainer#Remove if you do not want
 * to keep it in the geometric factory.
 */
    virtual CATNurbsSurface *GetNurbsSurface() const=0;

/**
 * @nodoc
 */
    virtual CATMathNurbsBipar *GetNurbsBipar() const=0;
 
/**
 * Avoids to create periodic Nurbs representation.
 * <br>By default, periodic representations can be created.
 */
    virtual void ForbidPeriodicity()= 0;

/**
 * Maps a parameter on the initial surface to the corresponding parameter on the computed Nurbs representation.
 * @param iParamOnSurface
 * The parameter on the initial surface.
 * @return
 * The parameter on the computed Nurbs representation.
 */
  virtual CATSurParam ComputeNewParameter(const CATSurParam &iParamOnSurface)= 0;

/**
 * @nodoc
 * Maps a parameter on the initial surface to the corresponding parameter on the computed Nurbs representation.
 * @param iOldSurParam
 * The parameter on the initial surface.
 * @param ioNewSurParam
 * The parameter on the computed Nurbs representation.
 * @return
 * 0.
 */
  virtual int GetEquivalentParam(const CATSurParam & iOldSurParam,
                                       CATSurParam & ioNewSurParam) = 0;


/**
 * @nodoc
 */
  virtual CATLONG32 CheckResult() = 0;

/**
 * @nodoc
 */
  virtual void AllowPartialDesextrapolation() = 0;
/**
 * @nodoc
 */
  virtual void ForbidRational() = 0;

  /**
 * @nodoc
 */
	virtual void SetTrimOption(CATBoolean iTrimToLimits) = 0;

  private:

CATConvertSurToNurbsSur(const CATConvertSurToNurbsSur &);
void operator = (const CATConvertSurToNurbsSur &);

};

/**
 * @nodoc
 * Creates the geometric operator that computes the Nurbs representation of a CATSurface.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iSurface
 * The pointer to the surfacee to convert.
 * @param iMode
 * The mode of use.
 * @return
 * The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
 * @see CATConvertSurToNurbsSur
 */
ExportedByCATGMOperatorsInterfaces
 CATConvertSurToNurbsSur*  CATCreateConvertSurToNurbsSur( CATGeoFactory  *iFactory, 
 CATSoftwareConfiguration * iSoftwareConfiguration,
                                                     const CATSurface &iSurface);

#endif

