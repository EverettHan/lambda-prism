// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
//===================================================================
//
// CATMathConicDeformation
//  virtual Class
//
//===================================================================

//===================================================================
// Sep.  11 R1Y Added access functions (for comparing geometries).
// 16/06/16 NLD Detabulation
//              Numerotation definitive des constructeurs
//              Ajout CATMathConicDeformation_Constructor3
//              (constructeur avec configuration)
//              Suppression de tous les anciens constructeurs (par flag de precompilation)
//              pour memoire
//              - CATMathConicDeformation_Constructor0 (historic)     avec iAlpha
//              - CATMathConicDeformation_Constructor1 (29/03/02 TCX) avec iAlpha et arctanLimit
//              - CATMathConicDeformation_Constructor2 (26/11/03 DR)  avec iAlpha et arctanLimit et iC
//              - Ajout de iTolObject en argument optionnel final a chacun de ces constructeurs (03/08/06 S9L) 
//              - CATMathConicDeformation_Constructor3 (16/06/16 NLD) avec iAlpha et arctanLimit et iC
//                precedes de iConfig et iTolObject (obligatoire)
// 22/06/16 NLD Regroupement des evaluateurs par intervalles
// 24/06/16 NLD Suppression definitive des anciens constructeurs
//===================================================================

#ifndef CATMathConicDeformation_H
#define CATMathConicDeformation_H

#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathSystem.h"
#include "CATMathNonLinearTransformation.h"
#include "CATMathNonLinearTransfoType.h"
#include "CATMathInterval.h"

class CATMathNxNFullMatrix;
class CATSoftwareConfiguration;

class ExportedByYN000FUN CATMathConicDeformation : public CATMathNonLinearTransformation
{
   
public:
   //-----------------------------------------------------------------
   // Constructor
   //-----------------------------------------------------------------


   //----------------------------------------------------------------- CATMathConicDeformation_Constructor3 (16/06/16 NLD)
   CATMathConicDeformation(      CATSoftwareConfiguration* iConfig     ,
                           const CATTolerance            & iTolObject  ,
                                 double                    iAlpha      ,
                                 double                    arctanLimit = CATPI,
                                 double                    iC          = 1.
                          );
   
  ~CATMathConicDeformation();
   
   //-----------------------------------------------------------------
   // Information methods
   //-----------------------------------------------------------------
   
   virtual CATMathClassId              IsA    () const = 0;
   
   virtual CATMathNonLinearTransfoType GetType() const = 0;
   
   //-----------------------------------------------------------------
   // Evaluation Methods
   //-----------------------------------------------------------------
   
           void Eval         (const double *iX, double *oFX);
           void Eval         (const double *iX, double *oFX,                                    const double iArctanLimit);
           void EvalJacobian (const double *iX,              CATMathNxNFullMatrix *oJacobianFX);
           void EvalJacobian (const double *iX,              CATMathNxNFullMatrix *oJacobianFX, const double iArctanLimit);
           void EvalJacobian (const double *iX,              double               *oJacobianFX);
           void EvalJacobian (const double *iX,              double               *oJacobianFX, const double iArctanLimit);
           void Eval         (const double *iX, double *oFX, CATMathNxNFullMatrix *oJacobianFX);
           void Eval         (const double *iX, double *oFX, CATMathNxNFullMatrix *oJacobianFX,       double iArctanLimit);
           void Eval         (const double *iX, double *oFX,   double *oFY,   double *oFZ,
                                                double *doFX,  double *doFY,  double *doFZ,
                                                double *d2oFX, double *d2oFY, double *d2oFZ, double iArctanLimit);
   
   //-----------------------------------------------------------------
   // Modifications and reading of coefficients 
   //-----------------------------------------------------------------
   virtual CATMathNonLinearTransformation * Duplicate() const =0;
   
           CATLONG32 GetNumberOfCoef() const;
   
           void      GetCoef        (double oCoef[]) const;
   
           void      SetCoef        (double iCoef[]);

           double    GetArctanLimit () const;
           double    GetC           () const;
   
   // Evaluators
   // ----------
   virtual double          EvalF             (const CATMathVector & MPX) = 0;
   virtual double          EvalFirstDerivFX  (const CATMathVector & MPX) = 0;
   virtual double          EvalFirstDerivFY  (const CATMathVector & MPX) = 0;
   virtual double          EvalFirstDerivFZ  (const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivFX2(const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivFXY(const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivFXZ(const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivFY2(const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivFYZ(const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivFZ2(const CATMathVector & MPX) = 0;
   
   virtual double          EvalG             (const CATMathVector & MPX, const double iArctanLimit=0.) = 0;
   virtual double          EvalFirstDerivGX  (const CATMathVector & MPX) = 0;
   virtual double          EvalFirstDerivGY  (const CATMathVector & MPX) = 0;
   virtual double          EvalFirstDerivGZ  (const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivGX2(const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivGXY(const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivGXZ(const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivGY2(const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivGYZ(const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivGZ2(const CATMathVector & MPX) = 0;
   
   virtual double          EvalH             (const CATMathVector & MPX) = 0;
   virtual double          EvalFirstDerivHX  (const CATMathVector & MPX) = 0;
   virtual double          EvalFirstDerivHY  (const CATMathVector & MPX) = 0;
   virtual double          EvalFirstDerivHZ  (const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivHX2(const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivHXY(const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivHXZ(const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivHY2(const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivHYZ(const CATMathVector & MPX) = 0;
   virtual double          EvalSecondDerivHZ2(const CATMathVector & MPX) = 0;
   
   virtual void EvalF(const CATMathVector & MPX,
                      const CATMathOption iOption,
                            double * F  =NULL,
                            double * Fu =NULL, double * Fv =NULL, double * Fw =NULL,
                            double * Fu2=NULL, double * Fuv=NULL, double * Fuw=NULL, double * Fv2=NULL, double * Fvw=NULL, double * Fw2=NULL) = 0;
   
   virtual void EvalG(const CATMathVector & MPX,
                      const CATMathOption iOption,const double iArctanLimit=0.,
                            double * G  =NULL,
                            double * Gu =NULL, double * Gv =NULL, double * Gw =NULL,
                            double * Gu2=NULL, double * Guv=NULL, double * Guw=NULL, double * Gv2=NULL, double * Gvw=NULL, double * Gw2=NULL) = 0;
   
   virtual void EvalH(const CATMathVector & MPX,
                      const CATMathOption iOption,
                            double * H  =NULL,
                            double * Hu =NULL, double * Hv =NULL, double * Hw =NULL,
                            double * Hu2=NULL, double * Huv=NULL, double * Huw=NULL, double * Hv2=NULL, double * Hvw=NULL, double * Hw2=NULL) = 0;

  
  virtual void EvalFGH(const CATMathVector &  MPX,
                       double & F, double & G, double & H) =0;

  virtual void EvalUpToFirstDerivFGH(const CATMathVector & MPX,
                                             
                                     double & F , double & G , double & H ,
                                     double & Fu, double & Fv, double & Fw,
                                     double & Gu, double & Gv, double & Gw,
                                     double & Hu, double & Hv, double & Hw) =0;
   
   // Interval evaluators
   // -------------------
   virtual CATMathInterval EvalF             (const CATMathInterval & X,const CATMathInterval & Y, const CATMathInterval & Z) = 0;
   virtual CATMathInterval EvalG             (const CATMathInterval & X,const CATMathInterval & Y, const CATMathInterval & Z,
                                              const double            iArctanLimit = 0.)                                      = 0;
   virtual CATMathInterval EvalH             (const CATMathInterval & X,const CATMathInterval & Y, const CATMathInterval & Z) = 0;

           CATMathInterval EvalInterval      (      CATMathInterval * iIntervalArray,
                                                    CATLONG32         iNumCoord     ,
                                                    double            iArctanLimit  = 0. );
   
protected:
   //-----------------------------------------------------------------
   // Data 
   //-----------------------------------------------------------------
   double alpha;
   double _arctanLimit; 
   double _C;
   double SinAlph;       // ATTENTION: pas toujours en phase avec alpha si appel de SetCoef(). NLD220616
   double CosAlph;       // ATTENTION: pas toujours en phase avec alpha si appel de SetCoef(). NLD220616
};

#endif
