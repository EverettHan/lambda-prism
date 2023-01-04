// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCouplingEdgeCrvSur :
// Class for coupling intersections between an EdgeCurve and a Surface
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Feb. 98  Creation                          X. Gourdon
// 18/04/11 NLD Utilisation de CATCGMOperatorDebug pour instrumentation
// 15/02/18 JSX je debranche les methodes non utilisées ActiveDeformation
// #define ActiveDeformation
//         CheckAndInsertPoint(double,class CATMathSetOfPo...
//         DeformOnePCurve(class CATPSpline * &,class CATM...
//         DeformTracks(void)
//         GetDataFromPSpline(class CATPSpline const *,cla...
//         SetInputDataForDeformation(class CATPCurve *,cl...
//         UpdateEdgeCurve(class CATCurve *,class CATCurve...
//         UpdateParameter(class CATCurve const *,class CA...
// 26/05/21 Q48 Migrate to CATGeoOperator (and some CGMReplay changes)
//=============================================================================
#ifndef CATCouplingEdgeCrvSur_H
#define CATCouplingEdgeCrvSur_H

// Base class
//#include "CATCGMOperator.h"
#include "CATGeoOperator.h"

// ExportedBy
#include "Y30C3XGG.h"

#include "CATSurParam.h"

#include "CATMathDef.h"

#include "CATMathIntervalND.h"
#include "CATCGMOperatorDebug.h"

class CATCurve;
class CATPCurve;
class CATCrvParam;
class CATSurParam;
class CATGeoFactory;
class CATSurface;
class CATPointOnEdgeCurve;
class CATEdgeCurve;
class CATMathPoint;
class CATMathFunctionX;
class CATMathFunctionXY;
class CATMathSetOfPointsND;
class CATPSpline;
class CATSoftwareConfiguration;

// Q48 26/05/21: Migrate to CATGeoOperator
//class ExportedByY30C3XGG CATCouplingEdgeCrvSur : public CATCGMOperator
class ExportedByY30C3XGG CATCouplingEdgeCrvSur : public CATGeoOperator
{
public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

  CATCouplingEdgeCrvSur(      CATGeoFactory            * iFactory,
                              CATSoftwareConfiguration * iConfig,
                              CATEdgeCurve             * iECrv,
                        const CATPointOnEdgeCurve      * iECrvStart,
                        const CATPointOnEdgeCurve      * iECrvEnd,
                              CATCurve                 * iCrv0,
                              CATCurve                 * iCrv1,
                              CATSurface               * iSurface);

  ~CATCouplingEdgeCrvSur();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------


  //-----------------------------------------------------------------------
  //- Setting Methods
  //-----------------------------------------------------------------------

  void SetInputData(const CATPointOnEdgeCurve * iPOEC0, CATCurve * iCrv0, const CATSurParam & iParam0,
                    const CATPointOnEdgeCurve * iPOEC1, CATCurve * iCrv1, const CATSurParam & iParam1 );

  #ifdef ActiveDeformation
  //Optional set if you want to try to deform instead of calling GetMergedCurve().
  //PC1bis et PC2bis sont posees sur la surface coupante, leur equivalent sur les deux surfaces coupees etant les
  //courbes PC1 et PC2. PC1 et PC1bis appartiennent a l'edgecurve EC1, idem pour PC2 et PC2bis avec EC2bis.
  //PC1bis et PC2bis peuvent pointer vers la meme courbe.
  //POEC1 et POEC2 sont les points a deplacer poses sur EC1 et EC2.
  //Les ClampPOEC  sont des points fixes, ou la deformation doit s'arreter.
  //Bord1bis et Bord2bis correspondent aux bords des surfaces coupantes si il y a des bords.
  //Egalement leur POEC associes. Si il n'y a rien, on prend la surface du constructeur comme
  //unique coupante.
  //Le booleen Duplicate indique si on duplique les courbes deformees, par defaut oui.
  //Continuity indique la continuite souhaite apres deformation entre les courbes : 0 -> C0, 1 -> G1. Peut ne pas etre respecte.
  //DeformSide indique quel cote l'on prefere deforme. Par defaut ( 3 ) on deforme les deux cotes en meme temps,
  //1 pour deformer le debut et 2 pour ne deformer que la fin.
  void SetInputDataForDeformation(CATPCurve * PC1,CATPCurve * PC2,CATPCurve * PC1bis,CATPCurve * PC2bis,
                                      CATEdgeCurve * EC1,CATEdgeCurve * EC2,
                                      CATPointOnEdgeCurve * POEC1,CATPointOnEdgeCurve * POEC2,
                                      CATPointOnEdgeCurve * ClampPOEC1,CATPointOnEdgeCurve * ClampPOEC2,
                                      const CATPCurve * Bord1bis=0,const CATPCurve * Bord2bis=0,
                                      const CATPointOnEdgeCurve * POEC1bis=0,const CATPointOnEdgeCurve * POEC2bis=0,
                                      CATBoolean Duplicate=1,CATLONG32 Continuity=0,CATLONG32 DeformSide=3);
#endif

// Optional set to use before run : specify the fact that a poec in SetInputData comes
// from a confusion and the homotopy should not start from this point
  void SetConfusionPoint(const CATPointOnEdgeCurve * iPOEC);
  

  // Optional call to specify that we are logically in a tangent case. Will ensure a more stable behavior
  void SetTangentCase(CATBoolean iTangentCase=TRUE);
  void SetGapVertex(double iGap);

  //-----------------------------------------------------------------------
  //- Running the operator
  //-----------------------------------------------------------------------
  //
  //void Run();
  CATCGMOperatorDebugDeclareRun(CATCouplingEdgeCrvSur,CATGeoOperator);
  int RunOperator();
  //
  
  //-----------------------------------------------------------------------
  //- Reading the results
  //-----------------------------------------------------------------------

  // Returns 1 if points are considered as coupled, 0 else
  CATBoolean GetCoupling();
  // If points are coupled and a merged curve should be created between the two input
  // POECS, return this EdgeCurve together with the PCurve on the surface.
  // 0 is returned if no such EdgeCurve exists.
  // If iPCurveOnSurfaceIsRefCurve=1, then the refCurve of the returned EdgeCurve is the PCurve
  // on the surface
  CATEdgeCurve * GetMergedCurve(CATPCurve * & oPCrv);
  // Returns the extremity on the returned EdgeCurve corresponding to a given input POEC
  CATPointOnEdgeCurve * GetCorrespondingPOEC(const CATPointOnEdgeCurve * iInputPOEC);

  // In the case of only one POEC as an input, return :
  // Input POEC if no output POEC exists (case of a tangential solution alone)
  // _ECrvStart if the output is at the Starting POEC of _ECrv
  // _ECrvEnd if the output is at the Ending POEC of _ECrv
  const CATPointOnEdgeCurve * GetOutputPOEC();


#ifdef ActiveDeformation
  //To get the deformed EdgeCurve and their inner PCurves. 
  //The order is the same than the one used in SetInputDataForDeformation().
  void GetDeformedEdgeCurve(CATPCurve *& DefPC1   , CATPCurve *& DefPC2, 
                            CATPCurve *& DefPC1bis, CATPCurve *& DefPC2bis,
                            CATEdgeCurve *& DefEC1, CATEdgeCurve *& DefEC2  )
  {
    if (_TryToDeform)   {  DefPC1    = _PC1     ; DefPC2    =_PC2;  
                           DefPC1bis = _PC1bis  ; DefPC2bis =_PC2bis;
                           DefEC1    = _EC1     ; DefEC2    =_EC2;    }
  };
#endif


  //-----------------------------------------------------------------------
  //
    // CGMReplay
  const CATString * GetOperatorId();
  void WriteInput(CATCGMStream  & os);
  void WriteOutput(CATCGMStream & os);

  virtual void Dump( CATCGMOutput& os ) ;
  virtual void DumpOutput(CATCGMOutput & os);
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  
  CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  static const CATString * GetDefaultOperatorId() { return & _OperatorId; };                          
  //

  //#######################################################################
  //- data
  //#######################################################################

private:
   //
   // Input
   CATSoftwareConfiguration * _SoftwareConfiguration;

   CATEdgeCurve * _ECrv;
   const CATPointOnEdgeCurve * _StartECrv;
   const CATPointOnEdgeCurve * _EndECrv;
   CATCurve     * _Crv[2];
   CATSurface   * _Surface;
   
   //SetInputData
   const CATPointOnEdgeCurve * _POEC[2];
   int _Index[2];
   CATSurParam _InputSurParam[2];

   //SetConfusionPoint
  CATBoolean _ConfusionPOEC[2];

  // SetTangentCase
  CATBoolean _LogicalTangentCase;

#ifdef ActiveDeformation
  //SetInputDataForDeformation
  CATLONG32 _TryToDeform;
  CATBoolean _Dup ;
  CATLONG32  _Cont ;
  CATLONG32  _DefSide;
  CATPCurve * _PC1 , * _PC1bis;
  CATEdgeCurve * _EC1;
  CATPCurve * _PC2 , * _PC2bis;
  CATEdgeCurve * _EC2;
  CATPointOnEdgeCurve * _ClampPOEC1 , * _ClampPOEC2;
  CATPointOnEdgeCurve * _POEC1 , * _POEC2;
  const CATPCurve * _Bord1bis , * _Bord2bis;
  const CATPointOnEdgeCurve * _POEC1bis , * _POEC2bis;
#endif

   // Internal
   static CATString _OperatorId;
   // computed
   double _wStart[2], _wEnd[2];
   int _RelativeOrientation;
   double _u[2], _v[2], _w[2], _Cow[2];
   CATMathIntervalND _Domain;

   CATBoolean _EquationsOpen;
   const CATMathFunctionXY * _FSur[3];
   const CATMathFunctionX * _FCrv[2][3];

   CATBoolean _MergedCurveToCreate ;
   CATBoolean _Pline ;

  //output
  const CATPointOnEdgeCurve * _OutputPOEC; // In the case of only one point in input
  CATPointOnEdgeCurve * _OutputMCrvPOEC[2];
  CATPCurve    * _OutputPCrv;
  CATEdgeCurve * _OutputECrv;
   CATBoolean _Coupling;

  //Data for deformation

  

  double _GapVertex;

  //-----------------------------------------------------------------------
  //- Private methods
  //-----------------------------------------------------------------------

  CATBoolean TestCouplingFromOnePoint();
  CATBoolean TestCouplingBetweenTwoCurves(const double det[2], const double SquareNormProd[2]);
  CATBoolean TestCouplingTangentBetweenTwoCurves();
  CATBoolean TestCouplingWithinSameCurve(const double det[2], const double SquareNormProd[2]);

  // Utility method : compute signed distance from a 3d point to a uv point on the surface
  CATBoolean ComputeSignedDistance(const CATMathPoint & iPt, const double u, const double v, double & oDist);


#ifdef ActiveDeformation
  //Methode de deformation des traces.
  CATBoolean DeformTracks();
  //Insertion d'une nouvelle valeur nodale dans une PSpline, avec Check au prealable pour ne pas generer d'arcs
  //trop petits.
  CATLONG32 CheckAndInsertPoint(double Parameter,
                              CATMathSetOfPointsND * Param,CATMathSetOfPointsND * Points,
                              CATMathSetOfPointsND * FirstDer,CATMathSetOfPointsND * SecDer,CATLONG32 & Insert) const;

  //Deformation d'une PSpline avec point fixe et point objectif. Directement appelee par DeformTracks().
  void DeformOnePCurve(CATPSpline *& Crv,
                          CATMathSetOfPointsND &Param,CATMathSetOfPointsND &Points,
                          CATMathSetOfPointsND &FirstDer,CATMathSetOfPointsND &SecDer,
                          CATLONG32 * Impo,CATMathSetOfPointsND &ImposePt,
                          CATMathSetOfPointsND &ImposeTg,CATMathSetOfPointsND &ImposeDs,
                          CATCrvParam &CrvInit,CATCrvParam &CrvClamp,CATSurParam &ParamTarget);
  //Recuperation des donnees d'une spline.
  void GetDataFromPSpline(const CATPSpline * Crv,
                             CATMathSetOfPointsND * Param,CATMathSetOfPointsND * Points,
                             CATMathSetOfPointsND * FirstDer,CATMathSetOfPointsND * SecDer) const;

  //Pour udater les deux EdgesCurves a deformer.
  void UpdateEdgeCurve(CATCurve * PC,CATCurve * PCbis,CATEdgeCurve *& EC);

  //Methode pour le report.
  void UpdateParameter(const CATCurve * NewCrv,CATCrvParam & ioParam) const;
#endif
};

#endif
