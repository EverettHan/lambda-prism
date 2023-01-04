// COPYRIGHT DASSAULT SYSTEMES 1998
//===================================================================
//===================================================================
//
// CATMathCylindricDeformationFolded
// Implementation class of 3x3 systems with coupled variables 
// used in the SheetMetal Application (SMC)
//
//===================================================================


//===================================================================
// Usage notes:
//               
//             C = (Length of the neutral fiber / Bend Allowance)
//
//===================================================================
// 14/06/16 NLD Detabulation
//              Numerotation des constructeurs
//              Ajout constructeur avec configuration (CATMathCylindricDeformationFolded_Constructor2)
//              Reordonnancement des methodes
//              Ajout RecalageXY
//===================================================================

#ifndef CATMathCylindricDeformationFolded_H
#define CATMathCylindricDeformationFolded_H

#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathSystem.h"
#include "CATMathCylindricDeformation.h"
#include "CATMathNonLinearTransfoType.h"
#include "CATTolerance.h"
#include "CATMathInterval.h"

class CATMathNxNFullMatrix;

class ExportedByYN000FUN CATMathCylindricDeformationFolded : public CATMathCylindricDeformation
{
 
 public:
  //-----------------------------------------------------------------
  // Constructor
  //-----------------------------------------------------------------

  //                                                                  CATMathCylindricDeformationFolded_Constructor2  (2016)(STRONGLY RECOMMENDED)
  CATMathCylindricDeformationFolded(      CATSoftwareConfiguration*  iConfig     ,
                                    const CATTolerance             & iTolObject  ,
                                          double                     C           ,
                                          double                     arctanLimit = CATPI
                                   );
  
  //                                                                  CATMathCylindricDeformationFolded_Constructor0 (historique)
  CATMathCylindricDeformationFolded(      double                     C           ,
                                    const CATTolerance             & iTolObject  = CATGetDefaultTolerance());

  //                                                                  CATMathCylindricDeformationFolded_Constructor1 (2011)
  CATMathCylindricDeformationFolded(      double                     C           ,
                                          double                     arctanLimit ,
                                    const CATTolerance             & iTolObject  = CATGetDefaultTolerance());
  
  ~CATMathCylindricDeformationFolded();
  
  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
  
  CATMathClassId IsA() const ;
  
  CATMathNonLinearTransfoType GetType() const;
  
  //-----------------------------------------------------------------
  // Modifications and reading of coefficients 
  //-----------------------------------------------------------------
  CATMathNonLinearTransformation * Duplicate() const;
  
          double          EvalF                (const double X,const double Y);
          double          EvalFirstDerivFX     (const double X,const double Y);
          double          EvalFirstDerivFY     (const double X,const double Y);
          double          EvalSecondDerivFX2   (const double X,const double Y);
          double          EvalSecondDerivFXY   (const double X,const double Y);
          double          EvalSecondDerivFY2   (const double X,const double Y);
          double          EvalG                (const double X,const double Y, const double iArctanLimit=0.);
          double          EvalFirstDerivGX     (const double X,const double Y);
          double          EvalFirstDerivGY     (const double X,const double Y);
          double          EvalSecondDerivGX2   (const double X,const double Y);
          double          EvalSecondDerivGXY   (const double X,const double Y);
          double          EvalSecondDerivGY2   (const double X,const double Y);

          void            EvalF                (const double u, const double v,
                                                const CATMathOption iOption,
                                                      double * F,
                                                      double * Fu, double * Fv,
                                                      double * Fu2, double * Fuv, double * Fv2);

          void            EvalG                (const double u, const double v,
                                                const CATMathOption iOption,
                                                      double * G,
                                                      double * Gu, double * Gv,
                                                      double * Gu2, double * Guv, double * Gv2, const double iArctanLimit=0.);
  virtual void            EvalFGH              (const CATMathVector & MPX,
                                                      double & F, double & G, double & H) ;

  virtual void            EvalUpToFirstDerivFGH(const CATMathVector & MPX,   
                                                      double & F, double & G, double & H,
                                                      double & Fu, double & Fv, double & Fw,
                                                      double & Gu, double & Gv, double & Gw,
                                                      double & Hu, double & Hv, double & Hw) ;

          CATMathInterval EvalF    (const CATMathInterval & X,const CATMathInterval & Y);
          CATMathInterval EvalG    (const CATMathInterval & X,const CATMathInterval & Y, const double iArctanLimit=0.);

           CATMathPlane * GetRipPlane(); 

   //-----------------------------------------------------------------
   // Stream/Unstream specific management
   //-----------------------------------------------------------------
   virtual short          GetStreamTransfoType() const;
   virtual CATBoolean     IsStreamable        ( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;
   virtual void           Stream              (       CATMathStream& Str, const char iLabelReserved[] = "", CATBoolean iStreamAllEvenIfTooOld = 0 ) const;
private:

           void           RecalageXY          (double & X,
                                               double & Y);
private:
  const CATTolerance & _TolObject;
};

#endif
