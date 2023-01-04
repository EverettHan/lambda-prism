//#define CATFrFNurbsBiparMandatoryConfig "NLD a n'activer qu'apres migration complete des appelants"

/*-*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1997
//==========================================================================
//
// CATFrFNurbsBipar:
// Inherit from CATMathNurbsBipar
// Mathematical class of bi-parametric NURBS.
// This class allows working on non C2 NURBS because of its mathematical
// definition. It can also be regarded as an advanced NURBS library.
//
// For more details on Basic Operators/Constructor for NurbsBipar see CATMathNurbsBipar.h
//
// Basic methods :     - GetColumnV
//                     - GetRowsU
//
// Advanced methods :  - NormalReparametrisationForC1
//                     - OptimiseContinuities
//                     - OptimiseDegree
//
// Geometric methods : - ConvertToNurbsSurface
//                     - ConvertToC2NurbsSurfaces
//                     - SetGlobalNurbsSurface
//
// Debug methods :     - VisuPoles
//                     - Dump
//
// Other methods :     - Constructor with a CATNurbsSurface                   (CATFrFNurbsBipar_14)
//                     - Constructor with a CATMathNurbsMultiForm and a
//                       transversal knot vector.                             (CATFrFNurbsBipar_12)
//                     - Constructor with n CATMathNurbsMultiForm             (CATFrFNurbsBipar_10)
//                     - Constructor with equations in U and V for each patch (CATFrFNurbsBipar_02)
//
//==========================================================================
// General remark : in this header, the possible values for direction are :
//  iDir=1 -> U direction
//  iDir=2 -> V direction
//==========================================================================
// Juin. 97 DHN Creation
// Juin. 04 EAB Versionning Interne
// 18/03/08 NLD Ajout SetMultiForms() pour factorisation de code
// 18/04/12 NLD - Detabulation
//              - Ajout d'une numerotation stable des constructeurs
//              - Migration du copy constructor (et du faux avec CATMathNurbsBipar)
//                du destructeur et de Explode() dans l'implementation
//              - Ajout Init()
//              - Smart indentation
// 06/06/12 NLD Ajout ConvertToC2NurbsSurfacesCommon()
// 17/05/16 NLD Ajout argument optionnel oError a ChangeKnotVector()
// 17/05/21 SMT1 ReduceMultiplicities & IncreaseMultiplicities
//==========================================================================

#ifndef CATFrFNurbsBipar_H
#define CATFrFNurbsBipar_H

#include "CATMathPoint.h"
#include "CATKnotVector.h"
#include "CATMathSetOfPoints.h"
#include "CATNurbsSurface.h"
#include "CATSurLimits.h"
#include "CATGeoFactory.h"
#include "YP00IMPL.h"
#include "CATMathNurbsBipar.h"

class CATMathNurbsMultiForm;
class CATFrFNurbsMultiForm;
class CATSoftwareConfiguration;

//-----------------------------------------------------------------------------
class ExportedByYP00IMPL CATFrFNurbsBipar : public CATMathNurbsBipar
{
  public :

    //
    //-------------------  Basic Methods -------------------
    //
    //-------------------------------------------------------------------
    //               (Nota: CATFrFNurbsBipar_* is a stable numbering in implementation file,
    //                not to be changed; adds may be done, no renumbering allowed
    //                consistency must be kept with header and previous versions; NLD180412)
    //
    //-------------------------------------------------------------------
    //                                                CATFrFNurbsBipar_01
    // Default Constructor
    CATFrFNurbsBipar();

    //------------------------------------------------------------
    //                                                CATFrFNurbsBipar_08
    // Non-Rational and mono-patch Constructor
    CATFrFNurbsBipar     (      CATSoftwareConfiguration *  iConfig              ,
                          const CATMathSetOfPoints       *  iSetOfPoints         ,
                          const CATLONG32                 & iNbPolesU            ,
                          const CATLONG32                 & iNbPolesV            ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );
#ifndef CATFrFNurbsBiparMandatoryConfig
    //                                                CATFrFNurbsBipar_09
    //Do not use
    CATFrFNurbsBipar     (const CATMathSetOfPoints       *  iSetOfPoints         ,
                          const CATLONG32                 & iNbPolesU            ,
                          const CATLONG32                 & iNbPolesV            ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );
#endif
    //------------------------------------------------------------
    //                                                CATFrFNurbsBipar_06
    // Non-Rational Constructor
    CATFrFNurbsBipar     (      CATSoftwareConfiguration *  iConfig              ,
                          const CATMathSetOfPoints       *  iSetOfPoints         ,
                          const CATKnotVector            *  iKnotVectorU         ,
                          const CATKnotVector            *  iKnotVectorV         ,
                          const CATLONG32                 & iNbPolesU            ,
                          const CATLONG32                 & iNbPolesV            ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );
#ifndef CATFrFNurbsBiparMandatoryConfig
    //                                                CATFrFNurbsBipar_07
    //Do not use
    CATFrFNurbsBipar     (const CATMathSetOfPoints       *  iSetOfPoints         ,
                          const CATKnotVector            *  iKnotVectorU         ,
                          const CATKnotVector            *  iKnotVectorV         ,
                          const CATLONG32                 & iNbPolesU            ,
                          const CATLONG32                 & iNbPolesV            ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );
#endif

    //------------------------------------------------------------
    //                                                CATFrFNurbsBipar_04
    // Standard Constructor
    CATFrFNurbsBipar     (      CATSoftwareConfiguration *  iConfig              ,
                          const CATMathSetOfPoints       *  iSetOfPoints         ,
                          const CATLONG32                   iIsRational          ,
                          const CATKnotVector            *  iKnotVectorU         ,
                          const CATKnotVector            *  iKnotVectorV         ,
                          const CATLONG32                 & iNbPolesU            ,
                          const CATLONG32                 & iNbPolesV            ,
                          const double                   *  iWeights             = NULL ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );
#ifndef CATFrFNurbsBiparMandatoryConfig
    //                                                CATFrFNurbsBipar_05
    ///Do not use
    CATFrFNurbsBipar     (const CATMathSetOfPoints       *  iSetOfPoints         ,
                          const CATLONG32                   iIsRational          ,
                          const CATKnotVector            *  iKnotVectorU         ,
                          const CATKnotVector            *  iKnotVectorV         ,
                          const CATLONG32                 & iNbPolesU            ,
                          const CATLONG32                 & iNbPolesV            ,
                          const double                   *  iWeights             = NULL ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );
#endif

    //------------------------------------------------------------
    // Destructor
    virtual ~CATFrFNurbsBipar();

    //------------------------------------------------------------
    // Operator '=' (overloaded)
    CATFrFNurbsBipar & operator = (const CATFrFNurbsBipar &iNurbsBipar);

    //------------------------------------------------------------
    //                                                CATFrFNurbsBipar_16
    // Copy constructor
    CATFrFNurbsBipar     (const CATFrFNurbsBipar          & ToCopy               );

    //                                                CATFrFNurbsBipar_17
    // Fake copy constructor
    CATFrFNurbsBipar     (const CATMathNurbsBipar         & ToCopy               );

    //
    //------------------- Data Access Methods -------------------
    //
    // Read a row or a column
    void GetRowsU        (const CATLONG32                 & iRankU_start         ,
                          const CATLONG32                 & iRankU_end           ,
                                CATMathPoint                pt[]                 ,
                          const CATLONG32                 & isens                = 1);

    void GetColumnV      (const CATLONG32                 & iRankV_start         ,
                          const CATLONG32                 & iRankV_end           ,
                                CATMathPoint                pt[]                 ,
                          const CATLONG32                 & isens                = 1);


    //
    //--------- Advanced Constructors and basic modifiers ---------
    //                                                CATFrFNurbsBipar_02
    //
    //  Constructor with equations (U and V) for each patch.
    //  --> Result is a C0 uniform nurbs bipar
    //  PolCoef is the array giving all the coefficients of the polynomial
    //  equations for each patch and for each coordinate of the space.
    //  Those coefficients are given in local parametrisation.
    //  For example, for one cubic patch, the X equation is :
    //  X(u,v) = A+Bu+Cu2+Du3+Euv+Fu2V+...+Ru3v2+Su3v3. The coefficients are
    //  stocked in the array in the alphabetic order, coordinate by coordinate.
    //  When the three coordinates of the space are stocked, the following
    //  patch is stocked. Note that the patches ranks taken into account for
    //  the stockage in PolCoef is V ranks first, U ranks in second.
    //
    CATFrFNurbsBipar     (      CATSoftwareConfiguration *  iConfig              ,
                          const CATLONG32                 & iNbCarU              ,
                          const CATLONG32                 & iNbCarV              ,
                          const CATLONG32                 & iDegreeU             ,
                          const CATLONG32                 & iDegreeV             ,
                          const double                   *  PolCoef              ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );
#ifndef CATFrFNurbsBiparMandatoryConfig
    //                                                CATFrFNurbsBipar_03
    //Do not use
    CATFrFNurbsBipar     (const CATLONG32                 & iNbCarU              ,
                          const CATLONG32                 & iNbCarV              ,
                          const CATLONG32                 & iDegreeU             ,
                          const CATLONG32                 & iDegreeV             ,
                          const double                   *  PolCoef              ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );
#endif

    //                                                CATFrFNurbsBipar_14
    // Constructor with a Nurbs Surface
    CATFrFNurbsBipar     (      CATSoftwareConfiguration *  iConfig              ,
                          const CATNurbsSurface          *  iSurface             ,
                          const CATSurLimits             *  iSurLimits           = NULL,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );
#ifndef CATFrFNurbsBiparMandatoryConfig
    //                                                CATFrFNurbsBipar_15
    //Do not use
    CATFrFNurbsBipar     (const CATNurbsSurface          *  iSurface             ,
                          const CATSurLimits             *  iSurLimits           = NULL,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );
#endif

    //                                                CATFrFNurbsBipar_10
    // Constructor with n MultiForms
    // pile in iDir  ( MultiFormDir is the other direction)
    CATFrFNurbsBipar     (      CATSoftwareConfiguration *  iConfig              ,
                                CATMathNurbsMultiForm    *  ioMultiForm          ,
                          const CATLONG32                 & iNbOfMultiForms      ,
                          const CATLONG32                 & iDir                 ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );
#ifndef CATFrFNurbsBiparMandatoryConfig
    //                                                CATFrFNurbsBipar_11
    //do not use
    CATFrFNurbsBipar     (      CATMathNurbsMultiForm    *  ioMultiForm          ,
                          const CATLONG32                 & iNbOfMultiForms      ,
                          const CATLONG32                 & iDir                 ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );
#endif

    //                                                CATFrFNurbsBipar_12
    // Constructor with a MultiForm and a knot vector
    // iMultiFormDir is the direction of the bipar equivalent to the multiform,
    // iKnotVector is the knot vector of the other direction.
    CATFrFNurbsBipar     (      CATSoftwareConfiguration *  iConfig              ,
                          const CATMathNurbsMultiForm     & iMultiForm           ,
                          const CATKnotVector             & iKnotVector          ,
                          const CATLONG32                 & iMultiFormDir        ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );
#ifndef CATFrFNurbsBiparMandatoryConfig
    //                                                CATFrFNurbsBipar_13
    //do not use
    CATFrFNurbsBipar     (const CATMathNurbsMultiForm     & iMultiForm           ,
                          const CATKnotVector             & iKnotVector          ,
                          const CATLONG32                 & iMultiFormDir        ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );
#endif

    //
    //------------------- Advanced Methods -------------------
    //
    // NormalReparametrisationForC1
    // This method changes the parametrisation of a C0 bipar in order
    // to make possible C1, the parametric length of the bipar also
    // becomes equivalent with its geometric length (ds/du near 1.)
    void NormalReparametrisationForC1(CATLONG32    IsAlreadyC1U              = 0,
                                      CATLONG32    IsAlreadyC1V              = 0);

    // Optimise Continuities
    // (cf "Data Reduction Strategy for Splines" by Lyche and Morken)
    // This method optimises the multiplicities of the different knots
    // (A knot value can be removed) in the given tolerance. If OnlyC2mode
    // value is set to 1, the computation for a given knot value will be
    // stopped when C2 is obtained. 
    // return the ratio of deformation that has been done
    double OptimiseContinuities(const double     & iTolerance                ,
                                      CATLONG32    iOnlyC2Mode               = 0,
                                      CATLONG32    iNbOfUnoptimisedU         = 0,
                                      CATLONG32 *  iUnoptimisedKnotsIndicesU = NULL,
                                      CATLONG32    iNbOfUnoptimisedV         = 0,
                                      CATLONG32 *  iUnoptimisedKnotsIndicesV = NULL,
                                      CATLONG32    iMode                     = 0); // iMode set to 0 for the old mode, 1 otherwise

    // Optimise Degree
    // This method optimises the degree of the bipar in the given tole-
    // rance, the output degree will be greater than or equal to the given
    // min degree in each direction (U and V).
    // The deviation is returned.
    double OptimiseDegree      (const double     & iTolerance                ,
                                      CATLONG32    iMinDegreeU               = 1,
                                      CATLONG32    iMinDegreeV               = 1);

    // Change Knot Vector (cf CATFrFNurbsMultiForm)
    // The error is given back in *oError if non null address given in input in oError;
    // (if null, exception is raised as previoulsy). (added optional argument NLD170516)
    void   ChangeKnotVector    (const CATKnotVector* iNewKV                 ,
                                const CATLONG32  & idir                      ,
                                      CATLONG32    ioContinuityLeft          = 0,
                                      CATLONG32    ioContinuityRight         = 0,
                                      CATError  ** oError                    = NULL);

    void   ReduceMultiplicities    (const CATULONG32 * DeltaMultiplicity,
                                    const CATLONG32  & idir                      );

    void   IncreaseMultiplicities    (const CATULONG32 * DeltaMultiplicity,
                                    const CATLONG32  & idir                      );

    // Explode  (multiple break)
    // The bipar is exploded into n new bipars, the user specifies
    // the (n-1) knot values where the original multiform is to be broken in
    // the given direction.
    // The knot values must be given in the increasing parameter order.
    // The new bipars are returned via an array of multiforms. The algorithm
    // is based on knot insertion.
    //
    CATFrFNurbsBipar **Explode(const double     *  iBreakKnotValues          ,
                               const CATLONG32 &   iNumberOfBreakKnotValues  ,
                               const CATLONG32 &   iDir                      );

    //
    //--------------- Creation or Modification of Geometry -------------------
    //
    // Modifies a surface by extrapolation of its data.
    // Warning : the equations of the surface are not computed (they are
    // not supposed to change during the extrapolation).
    void ExtrapolANurbsSurface(CATNurbsSurface  * iNurbsToExtrapol           );

    CATLONG32 GetNumberOfC2NurbsSurfaces();

    // Create a set of Nurbs Surfaces with a Bipar
    // All the surfaces here created are at least C2 everywhere.
    // They are stocked in the returned array V direction first.
    CATNurbsSurface **ConvertToC2NurbsSurfaces(CATGeoFactory *,
                                               CATLONG32 &oNbSurfaces);

    // Create a set of Nurbs Surfaces with a Bipar
    // All the surfaces here created are at least C2 everywhere.
    // They are stocked in the returned array V direction first.
    // The option of repametrisation allows to adjust the global
    //  normal parametrisation between two consecutive non-C2 knots
    //(these portions are frequently independantly exploded )
    // iModeReparam =CatAutomaticReparameterization force the new parametrisation
    // The allocated size of oNonC2KnotIndexes  can be NbKnots -2
    // (NULL pointer if NbKnots =2)
    // The significant elements in output is for i=0 ; i<oNbSurface-1

    CATNurbsSurface **ConvertToC2NurbsSurfaces
                       (             CATGeoFactory *         ,
                                     CATLONG32      & oNbSurfaceU,
                                     CATLONG32      & oNbSurfaceV,
                               const CATParameterizationOption iParameterizationOption=CatKeepParameterization,
                                     CATLONG32     *  iNonC2KnotUIndexes = NULL,
                                     CATLONG32     *  iNonC2KnotVIndexes = NULL);

    // Cut the initial bipar into to a given continuous sub-bipares
    //  bipares[iU][iV] will be the iU th and iV bipare.
    //  this table is to be deleted by the user,
    //  as well as the new bipares
    //  (provided that the result is different from the input : if no cutting
    //  is needed, it is no use to copy the bipare).
    //  Careful : if you provide pre-allocated arrays iNumBreaksU and/or iNumBreaksV,
    //  they may be reallocated (in particular for closed surfaces).
    CATLONG32 ConvertToContinuousNurbsBipares(CATLONG32 expectedContinuityAlongU,
                                              CATLONG32 expectedContinuityAlongV,
                                              CATLONG32& nbBiparesAlongU,
                                              CATLONG32& nbBiparesAlongV,
                                              CATFrFNurbsBipar***& bipares,
                                              CATLONG32*& iNumBreaksU, // if not null, it has to be  allocated by the user. Otherwise, it is not filled.
                                              CATLONG32*& iNumBreaksV,  // idem
                                              CATLONG32  isNearlyContinuous=0,   // to set to 0 if we want analytical continuity,
                                                                                 // to 1 if we accept want to apply the "C1-MixteMode",
                                                                                 // to 2 if we accept G-continuity according to numerical criteria
                                                                                 // to 3 if we accept C-continuity according to numerical criteria
                                              int IsClosedU = 0,
                                              int IsClosedV = 0,
                                              double* paramC1 = 0,
                                              double* paramC2 = 0,
                                              CATLONG32 discretisationFactor = 1);
    //
    //--------------- Debug methods -------------------
    //
    void VisuPoles(CATGeoFactory* factory);

    // dans les methodes suivantes, au 1er appel, les variables
    // CATLine et CATCartesianPoint doivent etre initialisees a 0
    void VisuPoles(CATGeoFactory      *   ifactory ,
                   CATCartesianPoint ** & ioVisuPt  ,
                   CATLONG32            & ioNbVisuPt);

    // En plus des poles, les liens entre les poles sont aussi visualises
    void VisuPoles(CATGeoFactory      * ifactory,
                   CATCartesianPoint ** &ioVisuPt,
                   CATLONG32            &ioNbVisuPt,
                   CATLine           ** &ioVisuLine,
                   CATLONG32            &ioNbVisuLine);

    void VisuPoles(      CATGeoFactory* ifactory,
                   const CATLONG32      iRankU,
                   const CATLONG32      iRankV);

    void VisuPoles(CATGeoFactory      *   ifactory,
                   CATCartesianPoint ** & ioVisuPt,
                   CATLONG32            & ioNbVisuPt,
             const CATLONG32              iRankU,
             const CATLONG32              iRankV);

    protected:
    void Init();
    void SetMultiForms(      CATMathNurbsMultiForm * ioMultiForm,
                       const CATLONG32             & iNbOfMultiForms,
                       const CATLONG32             & iDir);

    CATLONG32 GetC2BreakKnots(const CATKnotVector * iKnotVector, double *ioBreakKnotValues = NULL);

    CATNurbsSurface ** ConvertToC2NurbsSurfacesCommon(CATGeoFactory *  iFactory,
                                                      int          iThrow,
                                                      CATLONG32    NbBreakU,
                                                      double    *  BreakKnotValuesU,
                                                      CATLONG32    NbBreakV,
                                                      double    *  BreakKnotValuesV,
                                                      CATLONG32  & oNbSurfacesU,
                                                      CATLONG32  & oNbSurfacesV,
                                                      CATLONG32  & oNbSurfaces
                                                     );
    private:
       void Init_ERROR_NOCONFIG();


};
#endif
