// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
//===================================================================
//
// CATMathConicDeformationFolded
// Implementation class of 3x3 systems with coupled variables 
// used in the SheetMetal Application (SMC)
//
//===================================================================
// 23/11/01 dr  Ajout EvalFGH(), EvalUpToFirstDerivFGH()
// 16/06/16 NLD Detabulation
//              Ajout constructeur avec configuration (CATMathConicDeformationFolded_Constructor3)
// 20/06/16 NLD Ajout FixC()
// 21/06/16 NLD Ajout ControlTheta()
// 22/06/16 NLD Regroupement des evaluateurs par intervalles
//===================================================================
//===================================================================

#ifndef CATMathConicDeformationFolded_H
#define CATMathConicDeformationFolded_H

#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathSystem.h"
#include "CATMathConicDeformation.h"
#include "CATMathNonLinearTransfoType.h"
#include "CATMathInterval.h"

class CATMathNxNFullMatrix;

class ExportedByYN000FUN CATMathConicDeformationFolded : public CATMathConicDeformation
{
   
public:
   //-----------------------------------------------------------------
   // Constructor
   //-----------------------------------------------------------------
   //-------------------------------------------------------------------------- CATMathConicDeformationFolded_Constructor3 (NLD160616)
   // arctanLimit is in the interval ]-pi;pi]
    CATMathConicDeformationFolded(      CATSoftwareConfiguration*  iConfig     ,
                                  const CATTolerance             & iTolObject  ,
                                        double                     iAlpha      ,
                                        double                     arctanLimit = CATPI,
                                        double                     iC          = 1.);

    // DEPRECATED   
    //-------------------------------------------------------------------------- CATMathConicDeformationFolded_Constructor0
    CATMathConicDeformationFolded(double iAlpha,                                 const CATTolerance & iTolObject = CATGetDefaultTolerance());

    // DEPRECATED   
    //-------------------------------------------------------------------------- CATMathConicDeformationFolded_Constructor1
    // arctanLimit is in the interval ]-pi;pi]
    CATMathConicDeformationFolded(double iAlpha, double arctanLimit,             const CATTolerance & iTolObject = CATGetDefaultTolerance());

    // DEPRECATED   
    //-------------------------------------------------------------------------- CATMathConicDeformationFolded_Constructor2
    CATMathConicDeformationFolded(double iAlpha, double arctanLimit, double iC , const CATTolerance & iTolObject = CATGetDefaultTolerance());
   
   ~CATMathConicDeformationFolded();
   
   //-----------------------------------------------------------------
   // Information methods
   //-----------------------------------------------------------------
   
   CATMathClassId IsA() const ;
   
   CATMathNonLinearTransfoType GetType() const;
   
   //-----------------------------------------------------------------
   // Modifications and reading of coefficients 
   //-----------------------------------------------------------------
   CATMathNonLinearTransformation * Duplicate() const;
   
   double EvalF             (const CATMathVector & MPX);
   double EvalFirstDerivFX  (const CATMathVector & MPX);
   double EvalFirstDerivFY  (const CATMathVector & MPX);
   double EvalFirstDerivFZ  (const CATMathVector & MPX);
   double EvalSecondDerivFX2(const CATMathVector & MPX);
   double EvalSecondDerivFXY(const CATMathVector & MPX);
   double EvalSecondDerivFXZ(const CATMathVector & MPX);
   double EvalSecondDerivFY2(const CATMathVector & MPX);
   double EvalSecondDerivFYZ(const CATMathVector & MPX);
   double EvalSecondDerivFZ2(const CATMathVector & MPX);
   double EvalG(const CATMathVector & MPX, const double iArctanLimit=0.);
   double EvalFirstDerivGX  (const CATMathVector & MPX);
   double EvalFirstDerivGY  (const CATMathVector & MPX);
   double EvalFirstDerivGZ  (const CATMathVector & MPX);
   double EvalSecondDerivGX2(const CATMathVector & MPX);
   double EvalSecondDerivGXY(const CATMathVector & MPX);
   double EvalSecondDerivGXZ(const CATMathVector & MPX);
   double EvalSecondDerivGY2(const CATMathVector & MPX);
   double EvalSecondDerivGYZ(const CATMathVector & MPX);
   double EvalSecondDerivGZ2(const CATMathVector & MPX);
   
   double EvalH( const CATMathVector & MPX);
   double EvalFirstDerivHX  (const CATMathVector & MPX);
   double EvalFirstDerivHY  (const CATMathVector & MPX);
   double EvalFirstDerivHZ  (const CATMathVector & MPX);
   double EvalSecondDerivHX2(const CATMathVector & MPX);
   double EvalSecondDerivHXY(const CATMathVector & MPX);
   double EvalSecondDerivHXZ(const CATMathVector & MPX);
   double EvalSecondDerivHY2(const CATMathVector & MPX);
   double EvalSecondDerivHYZ(const CATMathVector & MPX);
   double EvalSecondDerivHZ2(const CATMathVector & MPX);
   
   void EvalF(const CATMathVector & MPX,
              const CATMathOption iOption,
              double * F  =NULL,
              double * Fu =NULL, double * Fv =NULL, double * Fw =NULL,
              double * Fu2=NULL, double * Fuv=NULL, double * Fuw=NULL,double * Fv2=NULL,double * Fvw=NULL, double * Fw2=NULL);
   
   void EvalG(const CATMathVector & MPX,
              const CATMathOption iOption,const double iArctanLimit=0.,
              double * G  =NULL,
              double * Gu =NULL, double * Gv =NULL, double * Gw =NULL,
              double * Gu2=NULL, double * Guv=NULL, double * Guw=NULL, double * Gv2=NULL, double * Gvw=NULL, double * Gw2=NULL);
   
   void EvalH(const CATMathVector & MPX,
              const CATMathOption iOption,
              double * H  =NULL,
              double * Hu =NULL, double * Hv =NULL, double * Hw =NULL,
              double * Hu2=NULL, double * Huv=NULL, double * Huw=NULL,double * Hv2=NULL,double * Hvw=NULL, double * Hw2=NULL);

   CATMathInterval EvalF    (const CATMathInterval & X,const CATMathInterval & Y,const CATMathInterval & Z);
   CATMathInterval EvalG    (const CATMathInterval & X,const CATMathInterval & Y, const CATMathInterval & Z, const double iArctanLimit=0.);
   CATMathInterval EvalH    (const CATMathInterval & X,const CATMathInterval & Y, const CATMathInterval & Z);

// DR : pour un tir groupe des evaluations 
  void EvalFGH              (const CATMathVector & MPX,
                                   double & F,  double & G,  double & H) ;

  void EvalUpToFirstDerivFGH(const CATMathVector & MPX,
                                   double & F,  double & G,  double & H,
                                   double & Fu, double & Fv, double & Fw,
                                   double & Gu, double & Gv, double & Gw,
                                   double & Hu, double & Hv, double & Hw) ; 
   
   //-------------------------------------------
   // Editions de la partie Folded de la transfo  
   //------------------------------------------------
    CATMathPlane  * GetRipPlane(); 

private:
    double          FixC(); // get _C value with versionning management, for wrong evaluators to fix.                NLD200616

    //                      // controls Theta using _arctanLimit.         for wrong evaluators to fix. and good ones. NLD210616                                      
    void            ControlTheta(double & ioTheta       ,
                                 int      iForceControl = 0 // sinon controle active par versionning
                                );
   //-----------------------------------------------------------------
   // Stream/Unstream specific management
   //-----------------------------------------------------------------
   virtual short      GetStreamTransfoType() const;
   virtual CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;
   virtual void       Stream( CATMathStream& Str, const char iLabelReserved[] = "", CATBoolean iStreamAllEvenIfTooOld = 0 ) const;


};

#endif
