// COPYRIGHT DASSAULT SYSTEMES 1998
//===================================================================
//===================================================================
//
// CATMathCylindricDeformation
//  virtual Class
//
//===================================================================


//===================================================================
// Usage notes:
//               
//             C = (Length of the neutral fiber / Bend Allowance)
//
//===================================================================

//===================================================================
//  Sep. 11 R1Y Added the function GetArctanLimit() (for comparing geometries).
// 14/06/16 NLD Ajout constructeur avec configuration (CATMathCylindricDeformation_Constructor2)
//              Detabulation
//              Numerotation des constructeurs
//===================================================================

#ifndef CATMathCylindricDeformation_H
#define CATMathCylindricDeformation_H

#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathSystem.h"
#include "CATMathNonLinearTransformation.h"
#include "CATMathNonLinearTransfoType.h"
#include "CATMathInterval.h"

class CATMathNxNFullMatrix;

class ExportedByYN000FUN CATMathCylindricDeformation : public CATMathNonLinearTransformation
{
 
 public:
  //-----------------------------------------------------------------
  // Constructor
  //-----------------------------------------------------------------
  //                                                                  CATMathCylindricDeformation_Constructor2  (2016)(STRONGLY RECOMMENDED)
  // arctanLimit is in the interval ]-pi;pi]
  CATMathCylindricDeformation(      CATSoftwareConfiguration*  iConfig     ,
                              const CATTolerance             & iTolObject  ,
                                    double                     C           ,
                                    double                     arctanLimit = CATPI
                             );
  
  //                                                                  CATMathCylindricDeformation_Constructor0 (historique)
  CATMathCylindricDeformation(      double         C          ,
                              const CATTolerance & iTolObject = CATGetDefaultTolerance());


  //                                                                  CATMathCylindricDeformation_Constructor1 (2011)
  // arctanLimit is in the interval ]-pi;pi]
  CATMathCylindricDeformation(      double         C          ,
                                    double         arctanLimit,
                              const CATTolerance & iTolObject = CATGetDefaultTolerance());
  
  ~CATMathCylindricDeformation();
  
  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
  
  virtual CATMathClassId IsA() const =0;
  
  virtual CATMathNonLinearTransfoType GetType() const = 0;
  
  //-----------------------------------------------------------------
  // Evaluation Methods
  //-----------------------------------------------------------------

  void Eval         (const double *iX, double *oFX);
  void Eval         (const double *iX, double *oFX, const double iArctanLimit );
  void EvalJacobian (const double *iX, CATMathNxNFullMatrix *oJacobianFX); 
  void EvalJacobian (const double *iX, CATMathNxNFullMatrix *oJacobianFX, const double iArctanLimit ); 
  void EvalJacobian (const double *iX, double *oJacobianFX);
  void EvalJacobian (const double *iX, double *oJacobianFX, const double iArctanLimit );
  void Eval         (const double *iX, double *oFX, CATMathNxNFullMatrix * oJacobianFX, double iArctanLimit );
  void Eval         (const double *iX, double *oFX,   double *oFY,   double *oFZ, 
                                       double *doFX,  double *doFY,  double *doFZ,
                                       double *d2oFX, double *d2oFY, double *d2oFZ, double iArctanLimit);
  
  //-----------------------------------------------------------------
  // Modifications and reading of coefficients 
  //-----------------------------------------------------------------
  virtual CATMathNonLinearTransformation * Duplicate() const =0;
  
  CATLONG32 GetNumberOfCoef() const;
  
  void GetCoef(double oCoef[]) const;
  
  void SetCoef(double iCoef[]);

  double GetArctanLimit() const;

  virtual double EvalF( const double X,const double Y)= 0;
  virtual CATMathInterval EvalF( const CATMathInterval & X,const CATMathInterval & Y)=0;
  virtual double EvalFirstDerivFX( const double X,const double Y)=0;
  virtual double EvalFirstDerivFY( const double X,const double Y)=0;
  virtual double EvalSecondDerivFX2( const double X,const double Y)=0;
  virtual double EvalSecondDerivFXY( const double X,const double Y)=0;
  virtual double EvalSecondDerivFY2( const double X,const double Y)=0;
  virtual double EvalG(const double X,const double Y, const double iArctanLimit=0.)=0;
  virtual CATMathInterval EvalG( const CATMathInterval & X,const CATMathInterval & Y, const double iArctanLimit=0.)=0;
  virtual double EvalFirstDerivGX( const double X,const double Y)=0;
  virtual double EvalFirstDerivGY(const double X,const double Y)=0;
  virtual double EvalSecondDerivGX2(const double X,const double Y)=0;
  virtual double EvalSecondDerivGXY( const double X,const double Y)=0;
  virtual double EvalSecondDerivGY2(const double X,const double Y)=0;

  virtual void EvalF(const double u, const double v,
                  const CATMathOption iOption,
                  double * F,
                  double * Fu, double * Fv,
                  double * Fu2, double * Fuv, double * Fv2)=0;

  virtual void EvalG(const double u, const double v,
                  const CATMathOption iOption,
                  double * G,
                  double * Gu, double * Gv,
                  double * Gu2, double * Guv, double * Gv2, const double iArctanLimit=0.)=0;

  virtual void EvalFGH(const CATMathVector & MPX,
                       double & F, double & G, double & H) =0;

  virtual void EvalUpToFirstDerivFGH(const CATMathVector & MPX,
                                             
                                     double & F, double & G, double & H,
                                     double & Fu, double & Fv, double & Fw,
                                     double & Gu, double & Gv, double & Gw,
                                     double & Hu, double & Hv, double & Hw) =0;
  CATMathInterval EvalInterval( CATMathInterval * iIntervalArray, CATLONG32  iNumCoord, double iArctanLimit=0. );
  
 protected:
  //-----------------------------------------------------------------
  // Data 
  //-----------------------------------------------------------------
  double _C; 
  double _arctanLimit; 

};

#endif
