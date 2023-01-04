/*-*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATMathNurbsBipar:
// Mathematical class of bi-parametric NURBS.
// This class allows working on non C2 NURBS because of its mathematical 
// definition. It can also be regarded as an advanced NURBS library.
//
// Basic methods :     - GetDegreeU
//                     - GetDegreeV
//                     - GetKnotVectorU
//                     - GetKnotVectorV
//                     - GetIndexOffsetU
//                     - GetIndexOffsetV
//                     - GetNumberOfCPsU
//                     - GetNumberOfCPsV
//                     - GetOneControlPoint
//                     - GetOneWeight
//                     - IsRational
//                     - SetOneControlPoint
//                     - SetOneWeight
//                     - SetIndexOffsetU
//                     - SetIndexOffsetV
//                     - SetGlobal (with a multiform)
//                     - SetGlobalFromForm (with a CATMathTabOfForm. [Private] )  
//                     - GetMeanPolygonLengthU
//                     - GetMeanPolygonLengthV
//                     - SetLimits (U and V)
//                     - GetLimits (U and V)
//
// Advanced methods :  - ActiveSplit
//                     - DecreaseDegreeU
//                     - DecreaseDegreeV
//                     - Explode
//                     - KnotInsertionU
//                     - KnotInsertionV
//                     - IncreaseDegreeU
//                     - IncreaseDegreeV
//                     - InvertU
//                     - InvertV
//                     - RemoveWeights
//                     - SetWeights
//                     - ExchangeUV
//
// Geometric methods : - ConvertToNurbsSurface
//                     - SetGlobalNurbsSurface
//
// Debug methods :     - Dump
//
// Other methods :     - Constructor with a CATNurbsSurface
//                     - Constructor with a CATMathNurbsMultiForm
//                     - Constructor with equations in U and V for each patch
//
//==========================================================================
// General remark : in this header, the possible values for direction are :
//  iDir=1 -> U direction
//  iDir=2 -> V direction
//==========================================================================
// Juin. 97 DHN Creation
//   /06/04 EAB Versionning Interne
// 24/04/12 NLD Numérotation stable des constructeurs
//              Mise au propre et colonnage
//              Ajout InitWithSurface()
//              Ajout ChangeParametricSpaceUOrV() pour factorisation
//              Ajout ChangeParametricSpaceLimitsUOrV() pour factorisation
// 26/04/12 NLD Ajout Copy()
// 21/05/12 pmg Ajout GetSoftwareConfiguration()
// 01/04/14 NLD Ajout Clear()
//              Smart indent
// 20/07/15 NLD Ajout de Dump() sur sortie quelconque, pour CGMReplay
// 21/01/16 JSX Ajout de SetGlobalFromForm
// 27/04/16 NLD CATMathTabOfForm remplace TabOfForm
// 17/05/16 NLD Ajout argument optionnel oError a MultipleKnotInsertion()
// 26/11/21 JSX Ajout operateur + et *
//==========================================================================

#ifndef CATMathNurbsBipar_H
#define CATMathNurbsBipar_H

#include "CATIACGMLevel.h"
#include "YP00IMPL.h"

#include "CATDataType.h"

#include "CATMathPoint.h"
#include "CATMathSetOfPoints.h"
#include "CATMathPolynomXY.h"
#include "CATMathFunctionXY.h"

#include "CATMathNurbsMultiForm.h"
#include "CATKnotVector.h"

#include "CATNurbsSurface.h"
#include "CATSurLimits.h"
#include "CATGeoFactory.h"

#include "CATParameterizationOption.h"

#include "CATCGMVirtual.h"
#include "CATCGMOutput.h"

class CATSoftwareConfiguration;
class CATMathTabOfForm;
class CATError;

//-----------------------------------------------------------------------------
class ExportedByYP00IMPL CATMathNurbsBipar : public CATCGMVirtual
{
  public :

    //
    //-------------------  Basic Methods -------------------
    //
    //-------------------------------------------------------------------
    //               (Nota: CATMathNurbsBipar_* is a stable numbering in implementation file,
    //                not to be changed; adds may be done, no renumbering allowed
    //                consistency must be kept with header and previous versions; NLD240412)
    // Default Constructor
    //                                               CATMathNurbsBipar_02
                            CATMathNurbsBipar();
    //                                               CATMathNurbsBipar_01
                            CATMathNurbsBipar    (      CATSoftwareConfiguration *  iConfig              ,
                                                  const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                                                 );
    //------------------------------------------------------------
    // Standard Constructor
    //                                               CATMathNurbsBipar_03
                            CATMathNurbsBipar    (      CATSoftwareConfiguration *  iConfig              ,
                                                  const CATMathSetOfPoints       *  iSetOfPoints         ,
                                                  const CATLONG32                   iIsRational          ,
                                                  const CATKnotVector            *  iKnotVectorU         ,
                                                  const CATKnotVector            *  iKnotVectorV         ,
                                                  const CATLONG32                 & iNbPolesU            ,
                                                  const CATLONG32                 & iNbPolesV            ,
                                                  const double                   *  iWeights             = NULL ,
                                                  const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                                                 );
    ////////Do not use
    //                                               CATMathNurbsBipar_04
    //////                  CATMathNurbsBipar(const CATMathSetOfPoints *iSetOfPoints,const CATLONG32 iIsRational,
    //////                                    const CATKnotVector *iKnotVectorU, const CATKnotVector *iKnotVectorV,
    //////                                    const CATLONG32 &iNbPolesU, const CATLONG32 &iNbPolesV,
    //////                                    const double *iWeights =NULL,const CATTolerance & iTolObject =CATGetDefaultTolerance());

    //------------------------------------------------------------
    // Copy-Constructor
    //                                               CATMathNurbsBipar_07
                            CATMathNurbsBipar    (const CATMathNurbsBipar         &iNurbsBipar           );

    //------------------------------------------------------------
    // Destructor
    virtual                ~CATMathNurbsBipar();

    //------------------------------------------------------------
    // Operator '=' (overloaded)
    virtual                 CATMathNurbsBipar & operator = (const CATMathNurbsBipar &iNurbsBipar);

    // Operator '+' 
    virtual                 CATMathNurbsBipar & operator + (const CATMathNurbsBipar &iNurbsBipar);

    // Operator '+' 

    virtual                 CATMathNurbsBipar & operator + (const CATMathVector &iVect);

    // Operator '*' 
    virtual                 CATMathNurbsBipar & operator * (const double &K);

    //
    //------------------- Data Access Methods -------------------
    //
    // Is the bipar rationnal ?
    virtual CATLONG32       IsRational() const // 0 -> no , 1 -> yes
      {
       return _IsRational;
      };

    //------------------------------------------------------------
    // Read the degree 
    virtual CATLONG32       GetDegreeU() const;
    virtual CATLONG32       GetDegreeV() const;

    //------------------------------------------------------------
    // Read the number of control points
    virtual CATLONG32       GetNumberOfCPsU() const
      {
       return _NbPolesU;
      };
    virtual CATLONG32       GetNumberOfCPsV() const
      {
       return _NbPolesV;
      };

    //------------------------------------------------------------
    // Read the control points
    virtual CATMathPoint  * GetOneControlPoint(CATLONG32 iRankU,CATLONG32 iRankV) const
      {
       return &(_tabOfCPs[_NbPolesV*(iRankU-1) + iRankV - 1]);
      };
    virtual CATMathPoint  * GetControlPoints() const
      {
       return _tabOfCPs;
      };

    //------------------------------------------------------------
    // Read the knot vectors
    virtual CATKnotVector * GetKnotVectorU() const
      {
       return _KnotVectorU;
      };
    virtual CATKnotVector * GetKnotVectorV() const
      {
       return _KnotVectorV;
      };

    //------------------------------------------------------------
    virtual CATLONG32       GetIndexOffsetU() const
      {
       return _OffsetU;
      };
    virtual CATLONG32       GetIndexOffsetV() const
      {
       return _OffsetV;
      };

    //------------------------------------------------------------
    // Read the weights (if the bipar is rational)
    virtual double        * GetWeights() const
      {
       return _Weights;
      } ;

    virtual double          GetOneWeight(const CATLONG32 &iRankU,
                                         const CATLONG32 &iRankV) const;

    //------------------------------------------------------------
    virtual void            GetLimitsU  (      double &oStartU,
                                               double &oEndU) const
      {
       oStartU = oEndU = 0.0;
       if (_IsLimitedU)
         {
          oStartU = _StartU;
          oEndU   = _EndU;
         }
       else
         {
          const double * Knots = NULL;
          _KnotVectorU->GetKnots(Knots);
          CATLONG32 NbKnots = _KnotVectorU->GetNumberOfKnots();
          if (Knots)
            {
             oStartU = Knots[0];
             oEndU   = Knots[NbKnots-1];
            }
         }
      };

    virtual void            GetLimitsV(double &oStartV,
                                       double &oEndV) const
      {
       oStartV = oEndV = 0.0;
       if (_IsLimitedV)
         {
          oStartV = _StartV;
          oEndV   = _EndV;
         }
       else
         {
          const double * Knots = NULL;
          _KnotVectorV->GetKnots(Knots);
          CATLONG32 NbKnots = _KnotVectorV->GetNumberOfKnots();
          if (Knots)
            {
             oStartV = Knots[0];
             oEndV   = Knots[NbKnots-1];
            }
         }
      };

    //------------------------------------------------------------
    virtual CATLONG32       IsLimitedU() const
      {
       return _IsLimitedU;
      };

    virtual CATLONG32       IsLimitedV() const
      {
       return _IsLimitedV;
      };


    // 
    //------------ Data Modification Methods ---------------------
    // 
    virtual void            SetLimitsU     (const double &StartU,
                                            const double &EndU)
      {
       _IsLimitedU = 1;
       _StartU     = StartU;
       _EndU       = EndU;
      };

    virtual void            SetLimitsV     (const double &StartV,
                                            const double &EndV)
      {
       _IsLimitedV = 1;
       _StartV     = StartV;
       _EndV       = EndV;
      };

    //------------------------------------------------------------
    virtual void            SetIndexOffsetU(const CATLONG32 & iNewOffsetU)
      {
       _OffsetU = iNewOffsetU;
      };

    virtual void            SetIndexOffsetV(const CATLONG32 & iNewOffsetV)
      {
       _OffsetV = iNewOffsetV;
      };

    //------------------------------------------------------------
    // Set one weight (if the bipar is rational)
    virtual void            SetOneWeight   (const CATLONG32 & iRankU,
                                            const CATLONG32 & iRankV,
                                                  double      iWeight);

    //------------------------------------------------------------
    // Transform a non-rational Nurbs into a rational one,
    // all weights are set to 1.
    // If it is already rational, nothing is done.
    virtual void            BecomesRational();

    //------------------------------------------------------------
    // Set the control points 
    virtual void            SetOneControlPoint(const CATLONG32     & iRankU       ,
                                               const CATLONG32     & iRankV       ,
                                               const CATMathPoint *  iControlPoint);



    //
    //------------ Basic Methods ---------------------
    //
    // Compute the length of the mean polygon made of the control points in U
    virtual double GetMeanPolygonLengthU() const;

    // Compute the length of the mean polygon made of the control points in V 
    virtual double GetMeanPolygonLengthV() const;

    //
    //--------- Advanced Constructors and basic modifiers ---------
    //
    // Constructor with a Nurbs Surface
    //                                               CATMathNurbsBipar_05
                            CATMathNurbsBipar    (      CATSoftwareConfiguration *  iConfig              ,
                                                  const CATNurbsSurface          *  iSurface             ,
                                                  const CATSurLimits             *  iSurLimits           = NULL,
                                                  const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                                                 );
    //Do not use
    //                                               CATMathNurbsBipar_06
                            CATMathNurbsBipar    (const CATNurbsSurface          *  iSurface             ,
                                                  const CATSurLimits             *  iSurLimits           = NULL,
                                                  const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                                                 );

    // Modify a bipar with a multiform and a direction
    virtual void            SetGlobal            (const CATMathNurbsMultiForm    *  iFrFNurbsMult        ,
                                                  const CATLONG32                   iDir                 );

    //
    //------------------- Advanced Methods -------------------
    //
    // Reverse the orientation
    virtual void            InvertU              ();
    virtual void            InvertV              ();
    virtual void            Invert               (const CATLONG32                 & iDir);

    // Exchange U and V
    void ExchangeUV();

    // Increase the degree
    virtual void            IncreaseDegreeU     (const CATLONG32                  & iDelta_degU);
    virtual void            IncreaseDegreeV     (const CATLONG32                  & iDelta_degV);
    virtual void            IncreaseDegree      (      CATLONG32                    iDelta_deg,
                                                       CATLONG32                    iDir);


    // Decrease the degree
    // WARNING : This method can lead to important deviation.
    //           ioContinuityLeft and ioContinuityLeft = 0,1,2.
    // ioContinuity is the continuity you want to keep at the end.
    // Left is the beginnig (in parameter), Right the end.
    // IF THERE ISN'T ENOUGH FREEDOM DEGREE, NOTHING IS DONE.
    virtual void            DecreaseDegreeU     (const CATLONG32                  & DeltaU            ,
                                                       CATLONG32                    ioContinuityLeftU  = 0,
                                                       CATLONG32                    ioContinuityRightU = 0);
    virtual void            DecreaseDegreeV     (const CATLONG32                  & DeltaV             ,
                                                       CATLONG32                    ioContinuityLeftV  = 0,
                                                       CATLONG32                    ioContinuityRightV = 0);

    // Modify the degree
    // WARNING : if the new degree is smaller than the current degree, this 
    //           method can lead to important deviation.
    //           ioContinuityLeft and ioContinuityLeft = 0,1,2
    // Usefull only if you want to decrease the degree.
    // ioContinuity is the continuity you want to keep at the end.
    // Left is the beginnig (in parameter), Right the end.
    // IF THERE ISN'T ENOUGH FREEDOM DEGREE, NOTHING IS DONE.
    virtual void            SetDegreeU          (const CATLONG32                  & NewDegreeU         ,
                                                       CATLONG32                    ioContinuityLeftU  = 0,
                                                       CATLONG32                    ioContinuityRightU = 0);

    virtual void            SetDegreeV          (const CATLONG32                  & NewDegreeV         ,
                                                       CATLONG32                    ioContinuityLeftV  = 0,
                                                       CATLONG32                    ioContinuityRightV = 0);

    // Insert a Knot
    // If the knot value already exists in the knot vector, its multiplicity
    // is increased until the specified multiplicity.
    // Note that the CATEpsg tolerance is used in order to test the equality
    // of two knot values.
    //
    virtual void            KnotInsertionU      (const double                     & iKnotValue         ,
                                                 const CATLONG32                  & iMultiplicity      );
    virtual void            KnotInsertionV      (const double                     & iKnotValue         ,
                                                 const CATLONG32                  & iMultiplicity      );
    virtual void            KnotInsertion       (const double                     & iKnotValue         ,
                                                 const CATLONG32                  & iMultiplicity      ,
                                                 const CATLONG32                  & iDir               );

    // Knot Removal
    //
    virtual void            KnotRemovalU        (const double                     & iKnotValue         ,
                                                 const CATLONG32                  & iMultiplicity      );
    virtual void            KnotRemovalV        (const double                     & iKnotValue         ,
                                                 const CATLONG32                  & iMultiplicity      );
    virtual void            KnotRemoval         (const double                     & iKnotValue         ,
                                                 const CATLONG32                  & iMultiplicity      ,
                                                 const CATLONG32                  & iDir               );

    // Active Split  (break)
    // The user specifies two couples of knot values, one couple for
    // each direction. The bipar is splitted with a new parametrisation 
    // beginning at the first knot value and ending at the second. 
    // The algorithm is based on knot insertion.
    // 
    virtual void            ActiveSplit         (const double                    *  LimitsU            ,
                                                 const double                    *  LimitsV            );

    // Explode  (multiple break)
    // The bipar is exploded into n new bipars, the user specifies
    // the (n-1) knot values where the original multiform is to be broken in
    // the given direction.
    // The knot values must be given in the increasing parameter order.
    // The new bipars are returned via an array of multiforms. The algorithm 
    // is based on knot insertion.
    // 
            CATMathNurbsBipar **Explode         (const double                    *  iBreakKnotValues   ,
                                                 const CATLONG32                  & iNumberOfBreakKnotValues,
                                                 const CATLONG32                  & iDir               );

    // RemoveWeights
    // This method removes the weigths of the bipar
    // if iCheckWeights=0, this method removes the weigths of the multiform
    // if iCheckWeights=1, this method checks if all the weights are the same
    // before removing the weigths of the multiform. If all the weights are not
    // the same this method does nothing and returns 1
    // Returns 0 if the weigths are removed.
    virtual int             RemoveWeights       (      int                          iCheckWeights      = 0);

    // SetWeights
    // This method adds weigths to a non rational multiform
    // For a rational multiform, this method changes the weigths
    // if iWeights=NULL the weigths are equal to 1.
            void            SetWeights          (      double                    *  iWeights           = NULL);

    // ChangeParametricSpaceU
    // these method enables us to perform a linear transformation
    // of the u knots.
    // if the return value is not zero, the algorithm has failed.
    virtual CATLONG32       ChangeParametricSpaceLimitsU
                                                (const double                     & iNewFirstKnotValue  ,
                                                 const double                     & iNewLastKnotValue   );
    virtual CATLONG32       ChangeParametricSpaceLimitsV
                                                (const double                     & iNewFirstKnotValue  ,
                                                 const double                     & iNewLastKnotValue   );

    virtual CATLONG32       ChangeParametricSpaceU(    double                       iRatio              ,
                                                       double                       iShift              = 0.0);
    virtual CATLONG32       ChangeParametricSpaceV(    double                       iRatio              ,
                                                       double                       iShift              = 0.0);

    //
    //--------------- Creation or Modification of Geometry -------------------
    //
    // Create a Nurbs Surface with a Bipar
            CATNurbsSurface*ConvertToNurbsSurface
                                                (      CATGeoFactory             *  iFactory            ,
                                                       CATParameterizationOption    iParameterizationOption = CatKeepParameterization);

    // Modify an existing Nurbs Surface with a Bipar
    // By default, the parameterization of the NURBS is modified to better
    // fit internal criteria. CatKeepParameterization will keep the original
    // parametrization.
            void            SetGlobalNurbsSurface(     CATNurbsSurface           *  MyNurbs             ,
                                                       CATParameterizationOption    iParameterizationOption = CatAutomaticParameterization); 

//==========================================================================
// Get the GlobalEquation of the  NurbsBipar
//==========================================================================

    virtual void             GetGlobalEquation   (     CATMathFunctionXY         *& oFx                 ,
                                                       CATMathFunctionXY         *& oFy                 ,
                                                       CATMathFunctionXY         *& oFz                 ) const ;

//==========================================================================
// Get the homogenous polynomial equations  W*X ,W*Y,W*Z ,W (if Fw is not NULL) 
// or the polynomial equation X , Y, Z  (if Fw is NULL). In this case the weights 
// are ignored
//===================================================================

    virtual void             GetEquations        (     CATMathPolynomXY         **  Fx                  ,
                                                       CATMathPolynomXY         **  Fy                  ,
                                                       CATMathPolynomXY         **  Fz                  ,
                                                       CATMathPolynomXY         **  Fw                  = NULL) const;

    //
    //--------------- Debug methods -------------------
    //
    virtual void             Dump                ();

    virtual void             Dump                (      CATCGMOutput              & os                 );

    // Insert many Knots
    // If one of the knot values already exists in the knot vector,
    // its multiplicity increases until the specified multiplicity.
    // Note that the CATEpsg tolerance is used in order to test the equality
    // of two knot values.
    //
    // The error is given back in *oError if non null address given in input in oError;
    // (if null, exception is raised as previoulsy). (added optional argument NLD170516)
    virtual void             MultipleKnotInsertion
                                                 (const double                   *  iKnotValues         ,
                                                  const CATLONG32                *  iMultiplicities     ,
                                                  const CATLONG32                 & iNbOfInsertions     ,
                                                  const CATLONG32                 & idir                ,
                                                        CATError                **  oError              = NULL);

    // Method that checks if a multiform is rational or not.
    // It returns 0 if no error has occured during the analysis.
    // The diagnostic equals :
    //    - 0 if the nurbs is not built as rational (_IsRational==0)
    //    - a positive value otherwise :
    //            1 if the weights are all the same
    //            2 if the weights are the same in U (not rational in u)
    //            3 if the weights are the same in V (not rational in v)
    //            4 if the weights are different in both directions
            CATLONG32        CheckRationality   (      CATLONG32                  & diagnostic          ,
                                                 const double                       precision           );

    // methode statique pour les multiformes
    static  CATLONG32        CheckRationality   (      double                    *  weights             ,
                                                       CATLONG32                    nbCPsU              ,
                                                       CATLONG32                    nbCPsV              , 
                                                       CATLONG32                  & iDiag               ,
                                                 const double                       precision           );

    // methode statique qui sera aussi utilise par les multiformes.
    // statique car on aurait pu en faire une fonction globale,
    // elle n'utilise que les arguments, pas les membres de la classe,
    // elle peut etre appelee avec la syntaxe : CATMathNurbsBipar::AnalyseOneSetOfWeights
    // meme si l'object n'est pas instancie.
    static CATLONG32 AnalyseOneSetOfWeights     (       double                   *  weights             ,
                                                        CATLONG32                   nbCPs               ,
                                                        CATLONG32                   deltaSize           , // distance entre 2 points consecutifs dans le tableau de CPs
                                                        CATLONG32                 & iSame               ,
                                                 const  double                      Precision           );
 
    // methode qui permet d'avoir le bloc d'encombrement d'un patch de bipare
    // rend 0 si le traitement se passe correctement
    // iNumPatchU commence a 1
    // iNumPatchV commence a 1
    // tolerance est le gras a ajouter a la boite d'encombrement
    // makeMeasureOnC0Geom : vaut 0 par defaut, la mesure est alors faite
    //  sur les points de controle intervenant sur chaque arc, mais n'est pas la
    //  plus precise possible. En revanche, la mesure est tres rapide.
    //  Par contre, si on active la variable makeMeasureOnC0Geom a 1, on va inserer
    //  des noeuds C0 au niveau des limites d'arc et la mesure sera alors plus precise.
    //  Demander une evolution si utilisation massive (centraliser ce service dans une 
    //  classe afin d'optimiser les perfos (knotInsersions massives))
    virtual CATLONG32        PatchBox           (       CATLONG32                   iNumPatchU          ,
                                                        CATLONG32                   iNumPatchV          ,
                                                        double                      tolerance           ,
                                                        CATMathBox                & box                 ,
                                                        CATLONG32                   makeMeasureOnC0Geom = 0);

    // isClosed is set to :
    //    1 if the element is closed and not degenerated to the tolerance in the given direction,
    //    0 if it is not closed to the tolerance (and degenerated)
    //    -1 if it may be degenerated to the given tolerance.
    //    -2 if the method has failed
    virtual CATLONG32        IsClosed            (     double                       tolerance           ,
                                                       CATLONG32                  & isClosedU           ,
                                                       CATLONG32                  & isClosedV           );
            void             GetTolerance        (const CATTolerance             *& oTol                );

            CATSoftwareConfiguration*
                             GetSoftwareConfiguration() const
      {
       return _Config;
      };

    const CATTolerance  *_TolObject ;

  protected :
            void             Init                (      CATSoftwareConfiguration *  iConfig             );
            void             InitWithSurface     (      CATSoftwareConfiguration *  iConfig             ,
                                                  const CATNurbsSurface          *  iSurface            ,
                                                  const CATSurLimits             *  iSurLimits
                                                 );


    //--------------------------------------------------------------------------
    //  Recopie
    //--------------------------------------------------------------------------
    //  ATTENTION:  gere toutes les données sauf
    //    - _TolObject
    //    - _Config
    //--------------------------------------------------------------------------
            void             Copy                (const CATMathNurbsBipar         & iNurbsBipar         );

    //--------------------------------------------------------------------------
    // Nettoyage
            void             Clear               ();

            CATLONG32        AnalyseOneSetOfWeights(    CATLONG32                 & diagnostic          );

    // Relimitation element geometrique equivalent
            void             Relimit             (      CATNurbsSurface          *  MyNurbsSur          );

            CATLONG32        MyPlaceIsNotOk      (      CATLONG32                   ivaleur             ,
                                                        CATLONG32                *  ioldtab             );

            CATLONG32        ChangeParametricSpaceUOrV
                                                 (      double                      iRatio              ,
                                                        double                      iShift              ,
                                                        CATKnotVector            *& ioKnotVector        ,
                                                        CATLONG32                 & ioIsLimited         ,
                                                        double                    & ioStart             ,
                                                        double                    & ioEnd
                                                 );

            CATLONG32        ChangeParametricSpaceLimitsUOrV
                                                 (const double                    & iNewFirstKnotValue  ,
                                                  const double                    & iNewLastKnotValue   ,
                                                        CATKnotVector            *& ioKnotVector        ,
                                                        CATLONG32                 & ioIsLimited         ,
                                                        double                    & ioStart             ,
                                                        double                    & ioEnd
                                                 );
private:
            void             SetGlobalFromForm   (      CATLONG32                   iDir                , 
                                                        CATKnotVector             * iKuv                , 
                                                        CATMathTabOfForm          * iTabOfForms
                                                 );
    //
    //------------------- Datas -------------------
    //
protected :
    CATSoftwareConfiguration * _Config;

    double                   * _Weights;

    CATMathPoint             * _tabOfCPs;

    CATKnotVector            * _KnotVectorU;
    CATKnotVector            * _KnotVectorV;

    CATLONG32                  _NbPolesU;
    CATLONG32                  _NbPolesV;
    CATLONG32                  _OffsetU;
    CATLONG32                  _OffsetV;
    CATLONG32                  _IsRational;    // 0 : No, 1 : Yes
    // -- Limits (not mandatory) --
    CATLONG32                  _IsLimitedU;    // 0:no , 1:yes,
                                               // 2:yes and empty domain of validity in U
    double                     _StartU;        // if limitedU and the domain of validity 
                                               // is not empty in U
    double                     _EndU;          // if limitedU and the domain of validity 
                                               // is not empty in U
    CATLONG32                  _IsLimitedV;    // 0:no , 1:yes,
                                               // 2:yes and empty domain of validity in V
    double                     _StartV;        // if limitedV and the domain of validity 
                                               // is not empty in V
    double                     _EndV;          // if limitedV and the domain of validity 
                                               // is not empty in V

};

#endif
