#ifndef CATMATHATTRSCALEOPTION_H
#define CATMATHATTRSCALEOPTION_H

// 30/10/06 SKA Creation
// 07/01/08 NLD Ajout SetOKReviewed() GetOKReviewed() _OKReviewed
// 10/01/08 JSX Ajout operator =
// 28/01/08 NLD Changement signature operator =
// 29/01/08 NLD Ajout argument pour SetOKReviewed()
// 01/02/08 NLD Valeurs par defaut (1,1) pour les arguments du constructeur
// 11/02/08 NLD Ajout CATMathAttrScaleOption_PrivateStaticSize (2)
//              Alloc() et Free()
// 31/07/08 NLD CATMathAttrScaleOption_PrivateStaticSize passe a 4
// 29/09/11 R1Y Changed SetOKReviewed() to be a const function (for comparing geometries).
// 03/02/16 F1Z Add few methods to have a direct access to dimension and scale power.
//              IsEqual(),
//              GetDimF(), GetDimX(), GetDimG(),
//              GetCoordPowerScaleF(), GetCoordPowerScaleX(), GetCoordPowerScaleG()
// 27/05/16 NLD Smart indent
// DD/MM/YY
//----------------------------------------------------------------------------------------------
#include "YN000FUN.h"
#include "CATMathAttribute.h"
#include "CATMathInline.h"

#define CATMathAttrScaleOption_PrivateStaticSize 4

class ExportedByYN000FUN CATMathAttrScaleOption : public CATMathAttribute
{
public:

  // Dedicated attribute used to describe the homogeneity of a function (or a system of equation) F and its variable(s) (or variable vector) X,
  // with regards to factory scale.
  
  // The description is expressed with a relative integer power of the factory scale.
  // Exemple: we need to solve f(x) = 0 (monodimensional function). Notations:
  //  f homogeneity is denoted [F], and x homogeneity is denoted [X]. Here we suppose that:
  //  [F]     = Scale^2
  //  [X] = 1 = Scale^0 (ie. not dependent on scale)
  // So we will construct the attribute scale option as following :
  //
  // CATMathAttrScaleOption AttrScale(2,0);

  // NB.: fractional power of scale is not supported yet (for instance : [F] = Scale^(1/3) is not managed yet).
  // If needed, a new constructor will be provided.

  ////////////////////////////////////////////////////////////////
  // Monodimensional functions : f(x)
  ////////////////////////////////////////////////////////////////
  // iPowerScaleF = is the relative integer power of scale used to describe [F] homegeneity.
  // iPowerScaleX = is the relative integer power of scale used to describe [X] homegeneity.
                             CATMathAttrScaleOption           (const CATLONG32                   iPowerScaleF = 1,
                                                               const CATLONG32                   iPowerScaleX = 1);
  
  ////////////////////////////////////////////////////////////////
  // Multi-dimensional functions or systems : f(X),
  // (f1(X), ..., fp(X)), etc. where p > 1 and X = (x1, ..., xn)
  ////////////////////////////////////////////////////////////////
  // idimF = p    = number of component equations (p = 1 if monodimensional function, e.g. f(x,y,z)) = size of iScalePowerF
  // idimX = n    = number of variables = size of iScalePowerX
  // idimG = g    = number of constraints = size of iPowerScaleG
  // iPowerScaleF = is the relative vector of integer power(s) of scale used to describe [F] homegeneity.
  // iPowerScaleX = is the relative vector of integer power(s) of scale used to describe [X] homegeneity. 
  // iPowerScaleG = is the relative vector of integer power(s) of scale used to describe [G] homegeneity. 
                             CATMathAttrScaleOption           (      CATLONG32                   idimF        ,
                                                               const CATLONG32                *  iPowerScaleF ,
                                                                     CATLONG32                   idimX        ,
                                                               const CATLONG32                *  iPowerScaleX ,
                                                                     CATLONG32                   idimG        = 0,
                                                               const CATLONG32                *  iPowerScaleG = 0);

  // copy constructor
                             CATMathAttrScaleOption              (const CATMathAttrScaleOption & iAttrToCopy);
  // et operateur =  
                             CATMathAttrScaleOption & operator = (const CATMathAttrScaleOption & iAttrToCopy);

                            ~CATMathAttrScaleOption              ();

               CATBoolean    IsEqual                             (const CATMathAttrScaleOption & iToCompare ) const;

               CATMathAttrId GetType                             () const;

               CATBoolean    IsExclusive                         () const;

         const CATLONG32   * GetPowerScaleF                      (      CATLONG32  & oDimF    ) const;
         const CATLONG32   * GetPowerScaleX                      (      CATLONG32  & oDimX    ) const;
         const CATLONG32   * GetPowerScaleG                      (      CATLONG32  & oDimG    ) const;

               CATLONG32     GetDimF                             ()                       const;
               CATLONG32     GetDimX                             ()                       const;
               CATLONG32     GetDimG                             ()                       const;

               CATLONG32     GetCoordPowerScaleF                 (      CATLONG32    iCoordIdF) const;
               CATLONG32     GetCoordPowerScaleX                 (      CATLONG32    iCoordIdX) const;
               CATLONG32     GetCoordPowerScaleG                 (      CATLONG32    iCoordIdG) const;

    // Pour exclusion du systeme de controle/traces des attributs duement certifies. NLD070108
  INLINE       void          SetOKReviewed                       (      CATLONG32    iOkReviewed=1) ;
  INLINE       CATLONG32     GetOKReviewed                       () const;

protected:
               void          Alloc                               () ;
               void          Free                                () ;

private:
    CATLONG32   _DimF,
                _DimX,
                _DimG;
    CATLONG32 * _PowerScaleF ;
    CATLONG32 * _PowerScaleX ;
    CATLONG32 * _PowerScaleG ;
    // NLD110208 evitons les allocations
    CATLONG32   _StaticPowerScaleF[CATMathAttrScaleOption_PrivateStaticSize] ;
    CATLONG32   _StaticPowerScaleX[CATMathAttrScaleOption_PrivateStaticSize] ;
    CATLONG32   _StaticPowerScaleG[CATMathAttrScaleOption_PrivateStaticSize] ;
    int         _OKReviewed ;
};

//----------------------------------------------------------------------------------------------
// INLINE
//----------------------------------------------------------------------------------------------
INLINE void      CATMathAttrScaleOption::SetOKReviewed(CATLONG32 iOkReviewed)
{
  _OKReviewed = iOkReviewed ;
}

//----------------------------------------------------------------------------------------------
INLINE CATLONG32 CATMathAttrScaleOption::GetOKReviewed() const
{
  return _OKReviewed ;
}
//----------------------------------------------------------------------------------------------

#endif

