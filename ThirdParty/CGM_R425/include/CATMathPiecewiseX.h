#ifndef CATMathPiecewiseX_h
#define CATMathPiecewiseX_h
// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathPiecewiseX :
// Class of piecewise functions of one variable
//
//===================================================================
// 01/12/05 NLD Ajout de _ValidOptions pour memorisation dans IsOption()
//              et ajout de _LastInvalidOption
// 17/07/08 NLD Definition de tableaux statiques pour les cas usuels:
//              CATMathPieceWiseX_StaticSize (4)
//              _FStatic, _BordersStatic,
//              _ImageStatic, _IsImageStatic,
//              _ImageDStatic, _IsImageDStatic,
//              Allocate() et Desallocate()ne sont plus statiques
// 21/07/08 NLD Retour arriere provisoire sur tableaux statiques
// 25/07/08 NLD Reactivation des tableaux statiques
// 23/12/08 NLD Ajout CATMathPiecewiseXGlobalToLocalSpy
//              et _SpyGlobalToLocal
// 30/09/11 R1Y Added access functions (for comparing geometries).
// 19/07/13 NLD Ajout Init()
//              Ajout DeepDuplicator() pour legitime reunification DeepDuplicate()/DeepDuplicateWithTol()
//              Smart indent
//===================================================================
#include "CATIACGMLevel.h"

#include "YN000FUN.h"

class CATMathStream;

#include "CATMathCommand.h"
#include "CATMathFoundationX.h"

class CATMathPiecewiseXDel;
class CATMathPiecewiseXGlobalToLocalSpy;

class ExportedByYN000FUN CATMathPiecewiseX : public CATMathFoundationX
{

// public methods
 public:
  //-----------------------------------------------------------------
  // Object management
  //-----------------------------------------------------------------
  CATMathPiecewiseX(const CATMathPiecewiseX & f);
  CATMathPiecewiseX(const CATLONG32           N        ,
                    const double            * borders  ,
                    const CATMathFunctionX ** functions);
  CATMathPiecewiseX & operator = (const CATMathPiecewiseX & p);
  virtual ~CATMathPiecewiseX();
  CATCGMNewClassArrayDeclare;

  void Extrapol(const CATLONG32           dir     ,
                const CATLONG32           N        ,
                const double            * borders  ,
                const CATMathFunctionX ** functions);

/*  void Unextrapol(const double minborder,
                  const double maxborder);*/
  void Unextrapol(CATLONG32 NLeft, CATLONG32 NRight);

  void ChangeFirstFunction (double iParamStart, CATMathFunctionX * iF);
  void ChangeLastBorder (double iParamEnd);

  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
  CATMathClassId IsA                () const;
  int            GetDirectComponents(const int                       iSizeOfComponents,
                                     const CATMathFunctionGeneral ** ioComponents     ) const;
  CATBoolean     IsAKindOf          (const CATMathClassId         iClassId            ) const;
  CATBoolean     IsATypeOf          (const CATMathFunctionXTypeId iType               ) const; 
  CATBoolean     IsOption           (const CATMathOption          iOption             ) const;

  CATLONG32      GetNumberOfPieces  ()                                                  const;
  void           GetFunction        (const CATLONG32              iIndex,
                                     const CATMathFunctionX    *& oF                  ,
                                           CATMathInterval      & oI                  ) const;

  const double          * GetBorders     () const;
  const CATMathInterval * GetImages      () const;
  const CATBoolean      * GetIsImages    () const;
  const CATMathInterval * GetImagesD     () const;
  const CATBoolean      * GetIsImagesD   () const;
        CATMathOption     GetValidOptions() const;


  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------   
  double Eval           (const double & t) const;
  double EvalFirstDeriv (const double & t) const;
  double EvalSecondDeriv(const double & t) const;
  double EvalThirdDeriv (const double & t) const;
  
  //
  // Evaluator of function and derivatives at the same time :
  //
  void   Eval           (const double   t,
                         const CATMathOption iOption,
                              double * f, double * df = 0, double * d2f = 0) const;

  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------
  CATMathInterval Eval           (const CATMathInterval & Dx) const;
  CATMathInterval EvalFirstDeriv (const CATMathInterval & Dx) const;
  CATMathInterval EvalSecondDeriv(const CATMathInterval & Dx) const;
  CATMathInterval EvalThirdDeriv (const CATMathInterval & Dx) const;
  void            Eval           (const CATMathInterval & I,
                                  const CATMathOption     iOptions,
                                        CATMathInterval * f   ,
                                        CATMathInterval * df  = 0, 
                                        CATMathInterval * d2f = 0) const;

  //-----------------------------------------------------------------
  // Duplicator
  //-----------------------------------------------------------------
  CATMathFunctionX * Duplicate() const;
  CATMathFunctionX * DeepDuplicate() const;
  CATMathFunctionX * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
  //-----------------------------------------------------------------
  // Stream 
  //-----------------------------------------------------------------
   virtual short      GetStreamDomainType(char ioDomain[3]) const;
           void       Stream               ( CATMathStream& Str, const char iLabelReserved[] = "" ) const;
  virtual  size_t     GetStaticMemoryBytes () const;
  virtual  size_t     GetDynamicMemoryBytes() const;
  /** @nodoc */
  virtual  CATBoolean _IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

  //-----------------------------------------------------------------
  // Local parameter 
  //-----------------------------------------------------------------
           void               GlobalToLocal    (const double            & x     ,
                                                      CATLONG32         & indexf,
                                                      double            & t     ) const;

  //---------------------------------------------------------------------
  // Formal combination creation : 
  //---------------------------------------------------------------------
  virtual  CATMathFunctionX * FormalCombination(const CATLONG32           iN       ,
                                                const CATMathFunctionX ** iFunc    ,
                                                const double            * iCoef    ,
                                                const double              iConstant) const;
 
 private:

           void               Init();

           CATMathFunctionX * DeepDuplicator   (      int                 iWithTol   ,
                                                const CATTolerance      * ipTolObject) const;


           CATMathInterval    Eval          (const CATMathInterval & Dx     ,
                                             const CATMathCommand  & command) const;


/* static */void              Allocate      (const CATLONG32                   iSizeTab     ,
                                                   CATLONG32                 & ioNewSize    ,
                                             const CATMathFunctionX       ** & ioNewF       ,
                                                   CATMathInterval         * & ioNewImage   ,
                                                   CATBoolean              * & ioNewIsImage ,
                                                   double                  * & ioNewBorders ,
                                                   CATMathInterval         * & ioNewImageD  ,
                                                   CATBoolean              * & ioNewIsImageD);

  /* static */ void           Desallocate   (const CATLONG32                   iSizeTab     ,
                                             const CATMathFunctionX       ** & ioNewF       ,
                                                   CATMathInterval         * & ioNewImage   ,
                                                   CATBoolean              * & ioNewIsImage ,
                                                   double                  * & ioNewBorders ,
                                                   CATMathInterval         * & ioNewImageD  ,
                                                   CATBoolean              * & ioNewIsImageD);


        CATLONG32           _CurrentIdx ;
        CATLONG32           _N;
  const CATMathFunctionX ** _F;
        //                                   evaluating for t in [_Borders[i], _Borders[i+1]] means evaluating _F[i] at point t-_Borders[i]
        double            * _Borders;     // array of _N+1 points :
        //                                   Contains _F[i]->Eval([ Borders[i],Borders[i+1] ]) if _IsImage[i]!=0
        CATMathInterval   * _Image;
        CATBoolean        * _IsImage;
        //                                   Contains _F[i]->EvalFirstDeriv([ Borders[i],Borders[i+1] ]) if _IsImageD[i]!=0
        CATMathInterval   * _ImageD;
        CATBoolean        * _IsImageD;
        CATMathOption       _ValidOptions;
        CATMathOption       _LastInvalidOption;

  //                                         N.B une immense majorite d'objets de cette classe demandent une taille statique de 1
  //                                             seulement. Sinon, 2, 4 en general.   NLD170708
#define CATMathPieceWiseX_StaticSize 4
 #ifdef CATMathPieceWiseX_StaticSize
  const CATMathFunctionX* _FStatic       [CATMathPieceWiseX_StaticSize];
  double                  _BordersStatic [CATMathPieceWiseX_StaticSize + 1];// attention piege
  CATMathInterval         _ImageStatic   [CATMathPieceWiseX_StaticSize];
  CATMathInterval         _ImageDStatic  [CATMathPieceWiseX_StaticSize];
  CATBoolean              _IsImageStatic [CATMathPieceWiseX_StaticSize];
  CATBoolean              _IsImageDStatic[CATMathPieceWiseX_StaticSize];
 #endif

  CATMathPiecewiseXGlobalToLocalSpy* _SpyGlobalToLocal ;//see implementation of CATMathPiecewiseX
  
  friend class CATMathPiecewiseXGlobalToLocalSpy;
  friend class CATMathPiecewiseXDel; 


};

#endif
