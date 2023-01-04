#ifndef CATMathCircle_H
#define CATMathCircle_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATIACGMLevel.h"

#include "CATMathematics.h"

#include "CATTolerance.h"
#include "CATMathPoint.h"
#include "CATMathDirection.h"
#include "CATMathCurve.h"
#include "CATMathConstant.h"

#include "CATErrorDef.h" //HRESULT

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATMathLine;
 
/**
 * Class representing a 3D mathematical circle.
 * <br>A CATMathCircle has a <tt>_Center</tt> (CATMathPoint),
 * a <tt>_Radius</tt>, and two
 * orthonormalized vectors defining the plane
 * where it is lying on. It can be defined with a _Scale and a _Shift, such that its
 * parametric equation is:
 *<br>
 * <tt>Circle(Param) = _Center + _Radius * [cos(_Scale*Param + _Shift) * _iFirstAxis + sin(_Scale*Param + _Shift) * _SecondAxis]</tt>.
 * where <tt>Param</tt> is the circle parameter.
 */
class ExportedByCATMathematics CATMathCircle : public CATMathCurve
{
 public:
//============================================================================
//- Constructor
//============================================================================

/**
 * Constructs a CATMathCircle of radius 1 of center <tt>(0,0,0)</tt> lying on 
 * the plane of directions <tt>(1,0,0)</tt> and </tt>(0,1,0)</tt>.
 */
                      CATMathCircle      ();

/**
 * @nodoc
 * @deprecated V5R20 Set
 * Constructs a CATMathCircle of given radius and center.
 *<br>The two vectors must be orthogonal and not null,
 * but this is not checked. If the vectors are not normed, the method
 * normalizes them.
 */
                      CATMathCircle      (const CATMathPoint  & iCenter            ,
                                          const CATMathVector & iFirstAxis         ,
                                          const CATMathVector & iSecondAxis        ,
                                                double          iRadius            ,
                                                double          iScale             = 1.,
                                                double          iShift             = 0.);

/**
 * Copy constructor.
 */
                      CATMathCircle      (const CATMathCircle & iCircleToCopy      ) ;



//============================================================================
//- Get/Set
//============================================================================
/**
* Constructs a CATMathCircle of given radius and center.
* @return 
* <tt>E_FAIL</tt> if the two vectors are not orthogonal or null, <tt>S_OK</tt> otherwise. 
* Note that if he vectors are not normed, the method normalizes them.
*/
    HRESULT           Set                (const CATMathPoint  & iCenter            ,
                                          const CATMathVector & iFirstAxis         ,
                                          const CATMathVector & iSecondAxis        ,
                                                double          iRadius            ,
                                                double          iScale             = 1.,
                                                double          iShift             = 0.);

/**
* Returns the class name CATMathCircle.
*/
    CATMathClassId    IsA                ()                                          const;
//

/**
 * Returns the mathematical type.
 * @return
 * The CATMathematicType.
 */
    CATMathematicType GetMathType        ()                                          const;



/**
 * Returns the (orthonormalized) directions of <tt>this</tt> CATMathCircle. 
 */
    void              GetDirections      (      CATMathVector & ioDirection1       ,
                                                CATMathVector & ioDirection2       ) const;

/**
 * Returns the center of <tt>this</tt> CATMathCircle. 
 */
    void              GetCenter          (      CATMathPoint  & oCenter            ) const; 

/**
 * Returns the radius of <tt>this</tt> CATMathCircle. 
 */
    double            GetRadius          ()                                          const ;

/**
 * Returns the scale of <tt>this</tt> CATMathCircle. 
 */
    double            GetScale           ()                                          const;

/**
 * Changes the scale of <tt>this</tt> CATMathCircle. 
 */
    void              SetScale           (const double          iScale             );

/**
 * Returns the shift of <tt>this</tt> CATMathCircle. 
 */
    double            GetShift           ()                                          const;

/**
 * Changes the shift of <tt>this</tt> CATMathCircle. 
 */
    void              SetShift           (const double          iShift             );

/**
 * Returns the point of <tt>this</tt> CATMathCircle corresponding to a given parameter
 */
    void              EvalPoint          (const double          iParam             ,
                                                CATMathPoint  & ioPoint            ) const;

/**
 * Retrieves the param on <tt>this</tt> CATMathCircle corresponding to a CATMathPoint
 * inside limitations.
 * @param iPoint
 * The CATMathPoint which coordinates are to be transformed as a param.
 * @param ioParam
 * The table of parameters corresponding to iPoint 
 * (must be allocate with size = 2).
 * @param iTol
 * Tolerance 3D
 * @param iStartParam/iEndParam
 * The limits to take into account for trimming the CATMathCircle.
 * @return
 * The number of parameters that can be evaluated on this point.
 * <dl><dt> 0  <dd>No parameter corresponds to this point.
 *     <dt> 1  <dd>Only one parameter corresponds to this point.
 *     <dt> 2  <dd>Two parameters correspond to this point (at the closure of the circle).
 *</dl>
 */
    int               GetParam           (const CATMathPoint  & iPoint             ,
                                          const double          iStartParam        ,
                                          const double          iEndParam          ,
                                          const double          iTol               ,
                                          const CATTolerance  & iTolObject         ,
                                                double       *  oParam
                                         )                                           const;
 /**
 * @nodoc
 * @deprecated V5R25 GetParam with CATTolerance object and reordered arguments (XScale compliant)
 */
    int               GetParam           (const CATMathPoint  & iPoint             ,
                                                double       *  oParam             ,
                                          const double          iTol               ,
                                          const double          iStartParam        ,
                                          const double          iEndParam          ) const;
    
/**
 * Projects a CATMathPoint on <tt>this</tt> CATMathCircle.
 * @return
 * FALSE if <tt>iPointToProject</tt> is the center of the circle, TRUE otherwise. 
  * <tt>ioProjectedPoint</tt> is only computed in the first case.
 */
    CATBoolean        Project            (const CATMathPoint  & iPointToProject    ,
                                                double        & ioParamAtProjection) const;

/**
 * Projects a CATMathPoint on  <tt>this</tt> CATMathCircle.
 * @return
 * FALSE if <tt>iPointToProject</tt> is the center of the circle, TRUE otherwise. 
 * <tt>ioParamAtProjection</tt> is only computed in the first case.
 */
    CATBoolean        Project            (const CATMathPoint  & iPointToProject    ,
                                                CATMathPoint  & ioProjectedPoint   ) const;

/**
 * Converts a parameter on <tt>this</tt> CATMathCircle to an angle in radians.
 */
    double            ConvertParamToAngle(const double          iParam             ) const;

/**
 * Converts an angle in radians to a parameter on <tt>this</tt> CATMathCircle.
 */
    double            ConvertAngleToParam(const double          iAngle             ) const;


 /**
 * Changes the parameter orientation of <tt>this</tt> CATMathCircle. 
 */   
    void              ReverseDirection   () ;

/**
 * Intersects <tt>this</tt> CATMathCircle with a CATMathLine. 
 * @param iLine
 *   The CATMathLine to intersect.
 * @param iStartParamOnLine/iEndParamOnLine
 *   The limits to take into account for the <tt>iLine</tt>.
 * @param iStartParamOnThisCircle/iEndParamOnThisCircle
 *   The limits to take into account for <tt>this</tt> CATMathCircle. Must be allocated with size 2.
 * @param ioParamOnLine[2] 
 *   The parameter of the intersection on <tt>iLine</tt>.
 * @param ioParamOnThisCircle[2]
 *   The parameter of the intersection on <tt>this</tt> CATMathCircle. Must be allocated with size 2.
 * @param iTol
 *   Defines the distance between <tt>iLine</tt> and <tt>this</tt> CATMathCircle, below
 * which they are considered to be intersecting. 
 * @return
 *   The number of intersection points. Defines the number of value(s)
 * to read in <tt>oParamOnLine</tt> and <tt>oParamOnThisCircle</tt>
 */
    int               Intersect          (const CATMathLine   & iLine                  ,
                                                double          iStartParamOnLine      ,
                                                double          iEndParamOnLine        ,
                                                double          iStartParamOnThisCircle,
                                                double          iEndParamOnThisCircle  ,
                                                double          iTol                   ,
                                          const CATTolerance  & iTolObject             ,
                                                double          ioParamOnLine      [2] ,
                                                double          ioParamOnThisCircle[2] ) const;

 /**
 * @nodoc
 * @deprecated V5R25 Intersect with CATTolerance object (XScale compliant)
 */
    int               Intersect          (const CATMathLine   & iLine                  ,
                                                double          iStartParamOnLine      ,
                                                double          iEndParamOnLine        ,
                                                double          iStartParamOnThisCircle,
                                                double          iEndParamOnThisCircle  ,
                                                double          iTol                   ,
                                                double          ioParamOnLine      [2] ,
                                                double          ioParamOnThisCircle[2] ) const;

 /**
 * Intersects <tt>this</tt> CATMathCircle with another CATMathCircle. 
 * @param iOtherCircle 
 *   The other CATMathCircle to intersect. 
 * @param iStartParamOnOtherCircle/iEndParamOnOtherCircle
 *   The limits to take into account for <tt>iCircle</tt>.
 * @param iStartParamOnThisCircle/iEndParamOnThisCircle
 *   The limits to take into account for <tt>this</tt> CATMathCircle.
 * @param ioParamOnOtherCircle[2] 
 *   The parameter of the intersection on <tt>iCircle</tt>. Must be allocated with size 2.
 * @param ioParamOnThisCircle[2]
 *   The parameter of the intersection on <tt>this</tt> CATMathCircle. Must be allocated with size 2.
 * @param iTol
 *   Defines the distance between <tt>iCircle</tt> and <tt>this</tt> CATMathCircle, below
 * which they are considered to be intersecting.
 * @return
 *   The number of intersection points. Defines the number of value(s)
 * to read in <tt>oParamOnOtherCircle</tt> and <tt>oParamOnThisCircle</tt>
 */
    int               Intersect          (const CATMathCircle & iOtherCircle            ,
                                                double          iStartParamOnOtherCircle,
                                                double          iEndParamOnOtherCircle  ,
                                                double          iStartParamOnThisCircle ,
                                                double          iEndParamOnThisCircle   ,
                                                double          iTol                    ,
                                                double          ioParamOnOtherCircle [2],
                                                double          ioParamOnThisCircle  [2]) const;

/**
 * Computes the distance between a CATMathPoint and <tt>this</tt> CATMathCircle. 
 * @param iStartParamOnCircle
 * The start limit to take into account for <tt>this</tt> CATMathCircle.
 * @param iEndParamOnCircle
 * The end limit to take into account for <tt>this</tt> CATMathCircle.
 * @param oParamAtMin
 * The parameter of the point of <tt>this</tt> CATMathCircle which is the closest to <tt>iPt</tt>.
 * @return 
 * The distance between <tt>iPt</tt> and the point defined by <tt>oParamAtMin</tt>.
 **/
 double               DistanceMin        (      CATMathPoint  & iPt                     ,
                                                double          iStartParamOnCircle     ,
                                                double          iEndParamOnCircle       ,
                                                double        & oParamAtMin             );

 /**
 * @nodoc
 * @deprecated V5R20 Intersect
 */
 ExportedByCATMathematics
 friend int           Intersect          (const CATMathLine   & iLine                   ,
                                          const CATMathCircle & iCircle                 ,
                                                double          iStartParam1            ,
                                                double          iEndParam1              ,
                                                double          iStartParam2            ,
                                                double          iEndParam2              ,
                                                double          iTol                    ,
                                                double          oParamOnLine         [2],
                                                double          oParamOnCircle       [2]);

 /** 
 * @nodoc
 * @deprecated V5R20 Intersect
 */
 ExportedByCATMathematics
 friend int           Intersect          (const CATMathCircle & iCircle1                ,
                                          const CATMathCircle & iCircle2                ,
                                                double          iStartParam1            ,
                                                double          iEndParam1              ,
                                                double          iStartParam2            ,
                                                double          iEndParam2              ,
                                                double          iTol                    ,
                                                double          oParamOnCircle1      [2],
                                                double          oParamOnCircle2      [2]);

 /**
 * @nodoc
 * @deprecated V5R20 EvalPoint
 * Use the  signature which returns a CATMathPoint as an output argument. 
 */
        CATMathPoint  EvalPoint          (const double          iParam                  ) const;

/**
 * @nodoc
 * Projects a CATMathPoint on  <tt>this</tt> CATMathCircle.
 * @param iTol
 *   Defines the distance between <tt>iPointToProject</tt> and the center of <tt>this</tt> CATMathCircle, below
 * which they are considered to be confused. 
 * @return
 * FALSE if <tt>iPointToProject</tt> is the center of the circle, TRUE otherwise. 
 * <tt>ioParamAtProjection</tt> is only computed in the first case.
 */
        CATBoolean    Project            (const CATMathPoint  & iPointToProject         ,
                                                CATMathPoint  & ioProjectedPoint        ,
                                          const double          iTol                    ) const;

/**
 * @nodoc
 * @deprecated V5R20.
 * Dumps <tt>this</tt> CATMathCircle.
 * <br>This writes the following lines on the ostream:
 *<pre>
 * Origin    = ( OriginFirstCoord    , OriginSecondCoord    , OriginThirdCoord )
 * FirstDir  = ( FirstDirFirstCoord  , FirstDirSecondCoord  , FirstDirThirdCoord )
 * SecondDir = ( SecondDirFirstCoord , SecondDirSecondCoord , SecondDirThirdCoord )
 * Radius    = Radius
 *</pre>
 * @param iStream  
 * A pointer to the output. If <tt>0L</tt>, the method dumps the 
 * coordinates on the <tt>cout</tt> output.
 */
        void          Dump               (      ostream       * iStream                 = 0L) const;
 
 private :
   // normalized vectors
    CATMathVector _FirstAxis,
                  _SecondAxis;
    CATMathPoint  _Center;
    double        _Radius;
    double        _Scale ;
    double        _Shift ;

};

#endif


 
