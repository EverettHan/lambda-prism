#ifndef CATPCurve_h
#define CATPCurve_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"
#include "CATCurve.h"
class CATMathTransformation2D;
class CATMathTransformation1D;
class CATMathFunctionX ;
class CATMathVector2D ;
class CATSurParam ;
class CATSurface ;
class CATSurLimits ;
class CATSetOfCrvParams;
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATPCurve ;
#else
extern "C" const IID IID_CATPCurve ;
#endif
 //CAA_Exposed CATGemPCurve
/**
 * Interface of the parametric curves defined 
 * in the space parameter of a surface.
 *<br>A CATPCurve is then always associated with a CATSurface element.
 * If the curve is parameterized by the function <tt>(U,V) = F(W)</tt>,
 * and the surface is parameterized by the function <tt>(X,Y,Z) = G(U,V)</tt>,
 * the CATPCurve is parameterized by the function <tt>(X,Y,Z) = G(F(W))</tt>.
 */
class ExportedByCATGMGeometricInterfaces CATPCurve : public CATCurve
{
  CATDeclareInterface;

public:
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  //CAA_Exposed 
/**
 * Returns a pointer to the underlying CATSurface of <tt>this</tt> CATPCurve.
 * @return
 * A pointer to the surface.
 */
  virtual CATSurface *GetSurface() const = 0;

   //CAA_Exposed 
/**
 * Changes the underlying CATSurface of <tt>this</tt> CATPCurve.
 * @param iNewSupport
 * The new underluing surface.
 */
  virtual void SetSurface( CATSurface* iNewSupport ) = 0;

  //CAA_Exposed 
/**
 * Retrieves the multi-evaluation of <tt>this</tt> CATPCurve point on the underlying CATSurface.
 * @param iParam
 * The parameter where to evaluate.
 * @param iCommand
 * The type of evaluation. The corresponding output pointer must be allocated.
 * @param iPoint
 * A pointer to the resulting CATSurParam.
 * @param iFirstDeriv 
 * A pointer to the resulting first derivative.
 * @param iSecondDeriv 
 * A pointer to the resulting second derivative.
 * @param iThirdDeriv 
 * A pointer to the resulting third derivative.
 */
  virtual void EvalUV                           (const CATCrvParam        & iParam             ,
                                                 const CATCrvEvalCommand  & iCommand           ,
                                                       CATSurParam       *  iPoint             ,
                                                       CATMathVector2D   *  iFirstDeriv        = NULL,
                                                       CATMathVector2D   *  iSecondDeriv       = NULL,
                                                       CATMathVector2D   *  iThirdDeriv        = NULL) const = 0;

  //CAA_Exposed 
/**
 * Retrieves the equation of <tt>this</tt> CATPCurve arc in the space parameter of the
 * underlying CATSurface.
 * @param iArc
 * The arc number.
 * @param oFx
 * A pointer to the equation of the first coordinate <tt>U=oFx(w)</tt>.
 * @param oFy
 * A pointer to the equation of the second coordinate <tt>V=oFy(w)</tt>.
 */
  virtual void GetEquationUV                    (const CATLONG32            iArc               ,
                                                 const CATMathFunctionX  *& oFx                ,
                                                 const CATMathFunctionX  *& oFy                )       const = 0;

  //CAA_Exposed 
/**
 * Retrieves the equation of <tt>this</tt> CATPCurve in the space parameter of the
 * underlying CATSurface.
 * @param oFx
 * A pointer to the equation of the first coordinate <tt>U=oFx(w)</tt>.
 * @param oFy
 * A pointer to the equation of the second coordinate <tt>V=oFy(w)</tt>.
 */
  virtual void        GetGlobalEquationUV       (const CATMathFunctionX  *& oFx                ,
                                                 const CATMathFunctionX  *& oFy                )       const = 0;


  
 //CAA_Exposed 
  /**
 * Retrieves the CATSurLimits including <tt>this</tt> CATPCurve.
 * @param
 * The box on the surface.
 */
  virtual void        GetBoundingBoxUV          (      CATSurLimits       & ioUVBox            )       const = 0 ;

/**
 * Retrieves the CATSurLimits including a part of <tt>this</tt> CATPCurve.
 * @param iSubset
 * A subset of the curve.
 * @param ioUVBox
 * The corresponding bounding box on the surface.
 */
  virtual void          GetBoundingBoxUV       ( const CATCrvLimits       & iSubset            ,
                                                       CATSurLimits       & ioUVBox            )       const = 0 ;

/**
 * Retrieves the CATSurLimits including <tt>this</tt> CATPCurve arc.
 * @param iArc
 * The arc number.
 * @param ioUVBox
 * The corresponding bounding box on the surface.
 */ 
  virtual void        GetInternalBoundingBoxUV   (const CATLONG32            iArc              ,
                                                        CATSurLimits       & ioUVBox           )        const = 0 ;
  
/**
 * Retrieves the CATSurLimits including <tt>this</tt> CATPCurve arc, independently of the current limitations.
 * @param iArc
 * The arc number.
 * @param ioLimits
 * The corresponding bounding box on the surface.
 */ 
  virtual void        GetInternalMaxBoundingBoxUV(const CATLONG32            iArc              ,
                                                        CATSurLimits       & ioLimits          ) const = 0 ;

/**
 * Retrieves the calcul precision on <tt>this</tt> CATCrvLimits bloc.
 * @param iLimits
 * The CATPCurve limitation.
 */ 
  virtual double      GetPrecisionUV             (const CATCrvLimits       & iLimits           ) const = 0 ;

  
/**
 * @nodoc
 * Creates a new Curve in 3D space, geometrically identical to <tt>this</tt> CATPCurve.
 * @param iWhere
 * The factory for the creation.
 * @param iIndexOnPCurve
 * A pointer to a set of parameters on <tt>this</tt> CATPCurve.
 * @param ioIndexOnCurve
 * A pointer to the set of corresponding parameters on the resulting curve.
 * <br>If <tt>NULL</tt>, the corresponding parameters are nor computed.
 * @return
 * The created 3D curve.
 * May return a null pointer if creation is not possible or not available yet.
 */
  virtual CATCurve* Create3DCurve                (      CATGeoFactory     *  iWhere            ,
                                                        CATSetOfCrvParams *  iIndexOnPCurve    = NULL,
                                                        CATSetOfCrvParams *  ioIndexOnCurve    = NULL) const = 0;

/**
* @nodoc
 * Returns the evaluation of <tt>this</tt> CATPCurve on the underlying CATSurface.
 * @param iLocation
 * The parameter on the surface
 * @param ioIndex
 * The corresponding parameter on the curve.
 * @return
 * The diagnosis of the evaluation.
 */
  virtual CATCurve::CATSolutionDiagnostic GetParamFromUV(const CATSurParam  & iLocation,
                                                               CATCrvParam  & ioIndex  ) const = 0;


/** @nodoc */
  virtual void OpenEquationUV()const = 0;

/** @nodoc */
  virtual void CloseEquationUV()const = 0;

  //-------------------------------------------------------------------------
  //- Check if a PCurve is invariant in UV space
  //-------------------------------------------------------------------------
  /** @nodoc */
  virtual CATBoolean IsInvariantUV(const CATMathTransformation2D & iTransfo2D ,
                                         CATMathTransformation1D*  oTransfo1D = NULL) const = 0;

  //----------------------------------------------------------------------
  //- CreateEquivalentPCurve
  //----------------------------------------------------------------------
  /** @nodoc */
  enum CATCreationDiagnostic { CreationDone, 
                               CreationNotAvailableYet, 
                               CreationFailed } ;

 /** @nodoc */
  virtual CATPCurve::CATCreationDiagnostic
  CreateEquivalentPCurve(CATMathTransformation2D *  iTransfo2D ,
                         CATSurface              *  iNewSupport,
                         CATPCurve               *& oPCurve    ,
                         CATMathTransformation1D  & oTransfo1D ) = 0;

  // deprecated
/** @nodoc */
  virtual CATCurve *GetCurve() const = 0;

 /**
 * Returns the CATSurParam of <tt>this</tt> CATPCurve.
 * Use preferably the EvalUV method.
 * @param iParam
 * The input CAtCrvParam parameter 
 * @return
 * The CATSurParam.
 */
  virtual CATSurParam EvalPointUV(const CATCrvParam & iParam) const = 0;

/**
 * Returns the first derivative of <tt>this</tt> CATPCurve for a given CATCrvParam.
 * Use preferably the EvalUV method.
 * @param iParam
 * The input CATCrvParam parameter 
 * @return
 * The first derivative.
 */
  virtual CATMathVector2D EvalFirstDerivUV(const CATCrvParam & iParam) const = 0;

/**
 * Returns the second derivative of <tt>this</tt> CATPCurve for a given CATCrvParam.
 * Use preferably the EvalUV method.
 * @param iParam
 * The input CATCrvParam parameter 
 * @return
 * The second derivative.
 */
  virtual CATMathVector2D EvalSecondDerivUV(const CATCrvParam & iParam) const = 0;

/**
 * Returns the third derivative of <tt>this</tt> CATPCurve for a given CATCrvParam.
 * Use preferably the EvalUV method.
 * @param iParam
 * The input CATCrvParam parameter 
 * @return
 * The third derivative.
 */
  virtual CATMathVector2D EvalThirdDerivUV(const CATCrvParam & iParam) const = 0;

/**
 * Retrieves the CATSurLimits including <tt>this</tt> CATPCurve.
 * Use preferably the signature which returns the CATSurLimitsin output argument.
 * @return
 * The CATSurLimits including the CATPCurve.
 */
  virtual CATSurLimits GetBoundingBoxUV( ) const = 0 ;

/**
 * Retrieves the CATSurLimits including a portion of <tt>this</tt> CATPCurve.
 * Use preferably the signature which returns the CATSurLimits in output argument.
 * @param iSubset
 * The CATCrvLimits defining a subset of the CATPCurve.
 * @return
 * The CATSurLimits including the CATPCurve.
 */
  virtual CATSurLimits GetBoundingBoxUV( const CATCrvLimits & iSubset ) const = 0 ;

/**
 * Retrieves the CATSurLimits including <tt>this</tt> CATPCurve arc.
 * Use preferably the signature which returns the CATSurLimits in output argument.
 * @param iArc
 * The arc number.
 * @return
 * The corresponding bounding box on the surface.
 */
  virtual CATSurLimits GetInternalBoundingBoxUV( const CATLONG32 iArc ) const = 0 ;


};
  CATDeclareHandler(CATPCurve,CATCurve);

#endif
