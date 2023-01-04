// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// JSX 050110 Split de FrFUtiPoint :
//            On ne garde ici que les methodes necessaires aux multiformes
//            il n'est pas necessaire que le reste, specifique a FreeForm soit dans 
//            GeometricObject
//
//=============================================================================
// Usage notes:
// sample of use :
// to provide
//
//=============================================================================
//    09/97 tpg Creation                                             Tuan Phung
//    07/98 alm Optimisation d2s/du2                      Paul-Alexandre Lourme
//    12/98 alm Factorisation de la matrice optimisation  Paul-Alexandre Lourme
//    10/05 JSX Ajout de EvalFilletTensionForBlend                  Jean SALOUX
// 13/03/08 NLD XScale. ComputeG2OptimumMatrix() recoit un objet CATTolerance
// 21/10/09 FDS Perfo , passage par valeur suite
// 06/01/10 JSX Split de FrFUtiPoint
// 11/01/15 JSX Ajout des methodes non caa MultipleKnotInsertion_MathLoop_ForBipar 
//              sur la Multiforme pour l'InsertKnot de la bipar
// 27/04/16 NLD Remise au propre
//              - CATMathTabOfForm remplace TabOfForm
//              - mise a la nomenclature des variables et methodes de CATMathTabOfForm
// 11/07/19 JSX Ajout de la methode NurbsUtil_QuinticInterpolToBipar
//              !! C'est un decoupage de la methode QuinticInterpolToNurbsSurface de FrFNurbsMultiform
//              L'implementation reste pour l'instant dans le cpp des multiform pour
//              faciliter les comparaisons.
//              Usage "geometrie" Only
//=============================================================================
#ifndef FrFUtiPoint_H 
#define FrFUtiPoint_H 

#include "YP00IMPL.h"
#include "CATDataType.h"
#include "CATTolerance.h"
#ifndef NULL
#define NULL 0
#endif

class CATMathPoint;
class CATMathDirection;
class CATKnotVector;
class CATMathVector;
class CATMathNxNFullSymMatrix;
class CATGeoFactory;

class CATNurbsSurface;
class CATFrFNurbsMultiForm;
class CATMathSetOfPointsND;
class CATFrFNurbsBipar;
//-----------------------------------------------------------------------------
//  Extract Peigne de tangence  
//-----------------------------------------------------------------------------

ExportedByYP00IMPL
void C2BezPt(const CATMathPoint & ip1,
             const CATMathPoint & ip2,
             const CATMathPoint & ip3,
             const CATMathPoint & ip4,
                   CATMathPoint & op5,
             const CATTolerance & iTolObject);
 

//-----------------------------------------------------------------------------
//  Compute the optimal norm of the tangent between two directions
//-----------------------------------------------------------------------------

ExportedByYP00IMPL
double CalculNormTg(CATMathPoint *Extr1,CATMathPoint *Extr2);

//
// JSX 17/12/15
 // Local Class for control points management
 //
 class CATMathTabOfForm
    {
    public:

       CATMathTabOfForm(int inbMAXform, int sizeOfForm , CATBoolean isRational);
       virtual ~CATMathTabOfForm();

       HRESULT FeedWithTabOfMathPoint( CATLONG32 IDIR, CATMathPoint *tabofpt, double *tabweight, int inbform);

       void           InsertFormBefore    (int       index    ,
                                           int       nbNewform);

       CATMathPoint * CreateTabOfMathPoint(CATLONG32 IDIR  , CATMathPoint *);
       double       * CreateTabOfWeight   (CATLONG32 IDIR  , double *) ;

       INLINE double *GetForm(int index) 
          {
          return &_Points[3*_FormIndex[index]];
          };

       INLINE double *GetWeight(int index) 
          {
          return &_Weights[_FormIndex[index]];
          };

       INLINE CATLONG32 GetNumberOfForms()
          {
          return _NbForm;
          };

       INLINE CATLONG32 GetSizeOfForms()
          {
          return _NbPtByForm;
          };

       INLINE CATLONG32 IsRational() 
          {
          if (_IsR)
             return 1;
          else 
             return 0;
          }
    //
    // DATA 
    //
    private:
       int         _NbPtByForm;    // nombre de points de controle d'une colonne
       CATBoolean  _IsR;           // flag en cas de rationelle
       double    * _Points;        // tableau brut des points de controle.       // NLD270416 (respect des notations standard) anciennement _Pts
       double    * _Weights;       // tableau brut des poids                     // NLD270416 (respect des notations standard) anciennement _Wgt
       CATLONG32 * _FormIndex;     // index des colonnes
       int         _NbForm ;       // nombre de colonnes remplies
       int         _NbMaxForm ;    // nombre maximum de colonnes utilisables
    };


 //
 // Insertion de noeuds dans une CATMathTabOfForm
 // iTolKnotConfusion : distance min pour la creation d'un arc
 // sortie en erreur sauf si 
 // le pt a inserer est suffisamment proche ( tolerance interne) pour etre confondu avec le knot !
 // parametres a inserer
 //   iNbInsertions 
 //   iKnotValues
 //   iMultiplicities
 // Vecteur nodal resultat
 //   nbNewKnots  
 //   newKnots   
 //   newMultiplicities 
 // les pts de control ( Entree/Sortiee)
 //
ExportedByYP00IMPL
 HRESULT MultipleKnotInsertion_MathLoop_ForBipar( const   CATTolerance * _TolObject, 
                                                          double         iTolKnotConfusion,
                                                          CATKnotVector* _KnotVector, 
                                                          CATLONG32      iNbInsertions,
                                                  const   double       * iKnotValues,
                                                  const   CATLONG32    * iMultiplicities,
                                                          CATLONG32    & nbNewKnots     ,
                                                          double       * newKnots       ,
                                                          CATLONG32    * newMultiplicities, 
                                                          CATMathTabOfForm    * FormOfCPS
                                                 );


//
// !! Le code est reste dans CATFrFNurbsMultiform pour favoriser les comparaisons !
//    il faudra le bouger quand tout sera certifer
// 
ExportedByYP00IMPL
CATNurbsSurface* NurbsUtil_QuinticInterpolToBipar(CATGeoFactory         * iFactory,
                                                  CATFrFNurbsMultiForm  * iFrFMultiForm,
                                                  CATMathSetOfPointsND *& iparams,
                                                  CATMathSetOfPointsND *& iFirstDer,
                                                  CATMathSetOfPointsND *& iSecondDer,
                                                  CATNurbsSurface       * iNurbsSur,
                                                  int                     iDimOfPoint,
                                                  int                   * iCont,
                                                  CATBoolean              iKindOFOutput_Surface_0 = 0,
                                                  CATFrFNurbsBipar     ** oBipar = NULL  
                                                  );




#endif
