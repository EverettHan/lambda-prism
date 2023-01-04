/*-*-c++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// CATGSDOptimizeSurf :
// Implementation class for global deformation and optimizing of surfaces. 
//
//=============================================================================
// Dec 2000 DJ  Creation                                       Daniel Johansson
// 18/01/18 NLD Detabulation et mise au propre
//=============================================================================

#ifndef CATGSDOptimizeSurf_H  
#define CATGSDOptimizeSurf_H 

#include "CATSurface.h"
#include "CATNurbsSurface.h"
#include "CATGeoFactory.h"
#include "CATCGMVirtual.h"
#include "CATEvalSurfPtAndDeriv.h"
#include "CATEvalCrvSurf.h"
#include "CATSoftwareConfiguration.h"

class CATGSDBase;
class CATMapFunctionXYZ;

class ExportedByCATGMOperatorsInterfaces CATGSDOptimizeSurf : public CATCGMVirtual

{
public:
    
/**
 * Destructor 
 */
    virtual ~CATGSDOptimizeSurf ();

/**
 * Before run: 
 * If start knot vectors are not given, the knot vectors of ioSurf is used.
 * For efficiency, a preliminary refinement of the knot vectors, using some
 * minimal number of konots are recomended.
 */
    virtual void SetSurfToModify(      CATSurface    *iSurf,
                                 const CATKnotVector *iStartKvU = NULL, 
                                 const CATKnotVector *iStartKvV = NULL ) = 0 ;

/**
 * Set duplicate mode. If iFactory is NOT given (this is default) the
 * given surface, *iSurf, is just replaced and, in this case, the only
 * interesting use of "GetModifiedSurf(...)" is to check the return value.  
 */
    virtual void SetDuplicateMode( CATGeoFactory *iFactory = NULL ) = 0 ;

/**
 * Set level of knot refinement and reduction (only used at maximal degree) 
 * 0: (faster) Fitting errors in arcs (knot intervals) are only treated 
 *    by dividing each such arc in two. 
 * 1: After dividig of arcs, as above, the numbers of knots are (itteratively
 *    reduced by around 15% by "combining neighbours".
 * 2: The repeated reductions are tried by around 25%.
 * The non zero values leads to fewer knots but more itterations are needed
 * to reach tolerance.
 */
    virtual void SetReductionLevel( const CATLONG32 iReductionLevel = 0 ) = 0 ;

/**
 * Set number of start curves for knot vector test. 
 * In U- and V- direction a few curves are made to set a preliminary
 * refinement of the knot vectors. 
 * Default setting (by (0, 0)) :
 * Suppose that the start knot vectors has NBKU and NBKV numbers of knots
 * respectively. Then, max ( 3, NKNV ), max ( 3, NKNU ) is used  .
 */
    virtual void SetNbCrvForKVRefinement( const CATLONG32 iNbAlongU = 0, 
        const CATLONG32 iNbAlongV = 0  ) = 0 ;

/**
 * Other synthesis operator
 */
    virtual void UseOtherSynthOpe( const CATLONG32 iIndSynOpe ) = 0 ;  

/**
 * Use Golbal def as biparametric offset law. 
 * iYes:   shoud be zero or one. Zero deactivates the offset again.
 * iOrientation: Set to -1 if the normal of the surface is not in
 * the expected offset direction. Oterwise, set 1. 
 */
    virtual void SetMakeOffset(CATLONG32 iYes, CATLONG32 iOrientation, CATGeoFactory *iFactory) = 0 ; 
    
/**
 * Creates a surface defined by this evaluation 
 * If iKVU is given and if reduction level is set to zero, the knots of iKVU
 * will  appear in the U-knot vector of the result.
 * the result is in ioSurf, that must exist.
 * Empty argument list or iYes = 0 deletes this option
 */
    virtual void SetEvaluator(CATLONG32              iYes    = 0,
                              CATEvalSurfPtAndDeriv *iEvalCS = NULL, 
                              CATKnotVector         *iKVU    = NULL,
                              CATKnotVector         *iKVV    = NULL,
                              CATNurbsSurface       *ioSurf  = NULL ) = 0 ;


/**
 * Creates a surface defined by iEvalCS. 
 * If iKVU is given and if reduction level is set to zero, the knots of iKVU
 * will  appear in the U-knot vector of the result.
 * the result is in ioSurf, that must exist.
 * Empty argument list or iYes = 0 deletes this option 
 ///////
 /// a corriger 
 // ajout prg 19 12 2002 pour que lgn puisse builder
 */
    virtual void SetMakeCrvSur(CATLONG32        iYes    = 0,
                               CATEvalCrvSurf  *iEvalCS = NULL, 
                               CATKnotVector   *iKVU    = NULL,
                               CATNurbsSurface *ioSurf  = NULL ){};


/**
 * Run:
 * Returns 1 if ok, else 0. 
 */
    virtual CATLONG32 Run () = 0 ;

/**
 * Pointwise diagnosis of transfosmation success (1) or not (0).
 * oAll  = 1 if all of oBOOLA and all of oBOOLS are one. 
 * oNone = 1 if all of oBOOLS are zero. 
 * oBOOLA: Analysis success 
 * oBOOLS: Analysis success and Synthesis success.
 * The booleran elements correspond to a parameter grid of size 
 * oNbU x oNbV in an obvious way.
 * The arrays belongs to "this" object and may not be deleted!
 */    
    virtual void Diagnosis (
              CATLONG32     &oAll,
              CATLONG32     &oNone,
              CATLONG32     &oNbBOOL,
        const unsigned int *&oBOOLA,
        const unsigned int *&oBOOLS,
              CATLONG32     &oNbU,
        const double       *&oParU,
              CATLONG32     &oNbV,
        const double       *&oParV ) = 0 ;
    
/**
 * Get modified surface. 
 * If zero is returned, or allways in replace mode, the pointer oSurf is
 * equal to the pointer ioSurf of "SetSurfToModify(...)" .
 * Returns one if the surface, *iSurf, is modified (i.e at least
 * some part of *iSurf is inside the modification domain). (The
 * surface, oSurf, is then a CATNurbsSurface.)
 */
    virtual CATLONG32 GetModifiedSurf ( CATSurface *&oSurf ) = 0 ;

/**
 * Diagnosis of result: maxErr is maximal POINT deviation,  
 */
    virtual void MaxErr ( double &maxErr ) = 0 ;

};

ExportedByCATGMOperatorsInterfaces
CATGSDOptimizeSurf* CreateCATGSDOptimizeSurf(   const CATLONG32                  iMaxDeg,
                                                const double                     iTolPt,
                                                const double                     iTolNormal = 0.0 ) ;

ExportedByCATGMOperatorsInterfaces
CATGSDOptimizeSurf* CreateCATGSDOptimizeSurf(         CATGSDBase               * iAnaOpe,
                                                const CATLONG32                  iNbSynOpe,
                                                      CATGSDBase              ** iSynOpe,
                                                const CATLONG32                  iIndSynOpe,
                                                const double                     iTolPt,
                                                const double                     iTolNormal,
                                                const CATLONG32                  iMaxDeg ) ;

ExportedByCATGMOperatorsInterfaces
CATGSDOptimizeSurf* CreateCATGSDOptimizeSurf(         CATMapFunctionXYZ        * iMap,
                                                const double                     iTolPt,
                                                const double                     iTolNormal,
                                                const CATLONG32                  iMaxDeg ) ;

ExportedByCATGMOperatorsInterfaces
CATGSDOptimizeSurf* CATCreateCATGSDOptimizeSurf(      CATSoftwareConfiguration * iSoftConf,
                                                const CATLONG32                  iMaxDeg,
                                                const double                     iTolPt,
                                                const double                     iTolNormal = 0.0 ) ;

ExportedByCATGMOperatorsInterfaces
CATGSDOptimizeSurf* CATCreateCATGSDOptimizeSurf(      CATSoftwareConfiguration * iSoftConf,
                                                      CATGSDBase               * iAnaOpe,
                                                const CATLONG32                  iNbSynOpe, 
                                                      CATGSDBase              ** iSynOpe, 
                                                const CATLONG32                  iIndSynOpe,
                                                const double                     iTolPt,
                                                const double                     iTolNormal,
                                                const CATLONG32                  iMaxDeg ) ;
ExportedByCATGMOperatorsInterfaces
CATGSDOptimizeSurf* CATCreateCATGSDOptimizeSurf(      CATSoftwareConfiguration * iSoftConf,
                                                      CATMapFunctionXYZ        * iMap,
                                                const double                     iTolPt,
                                                const double                     iTolNormal,
                                                const CATLONG32                  iMaxDeg ) ;

#endif
