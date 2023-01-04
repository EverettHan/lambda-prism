//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//=============================================================================
//
// CATExtrapolAndReconvergeSharpCrvSur.h
//=============================================================================
// Usage Notes:
//    Cette operateur permet d'extrapoler une surface jusqu'a une ligne objectif
// ou des lignes objectifs.
// Il permet de plus de retrouver (par reconvergence) l'intersection entre cette
// ligne (ou ces lignes) et la surface.
// Rm : la surface peut etre extrapoler plus que neccessaire, on n'extrapol pas
// que jusqu'a la droite objectif.
//
//=============================================================================
//   /03/04     Creation                                   E. Malgras
//   /06/05 CQI Switch on RunNew
// 12/03/20 Q48 Headers etc for math versioning
//=============================================================================


#ifndef CATExtrapolAndReconvergeSharpCrvSur_H
#define CATExtrapolAndReconvergeSharpCrvSur_H

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATCreateExtrapolAndReconvergeSharpCrvSur.h"
#include "CATSurParam.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurface;
class CATMathLine;

class ExportedByY30C3XGG
CATExtrapolAndReconvergeSharpCrvSur:public CATGeoOperator
{
public :

  // Constructor
  // iSurface = Surface a extrapoler
  // iSurParam = l'init sur la surface a extrapoler
  // iLine = ligne objectif
  // MinExtrapol = distance min d'extrapolation si il y a extrapolation
  CATExtrapolAndReconvergeSharpCrvSur(CATGeoFactory * iFactory,
                                   CATSoftwareConfiguration * iConfig,
                                   CATSurface * iSurface,
                                   CATSurParam & iSurParam,
                                   CATMathLine * iLine,
                                   double MinExtrapol = 0);

  CATExtrapolAndReconvergeSharpCrvSur(CATGeoFactory * iFactory,
                                   CATSoftwareConfiguration * iConfig,
                                   CATSurface * iSurface,
                                   CATSurParam *& iSurfParam,
                                   int iNbLine,
                                   CATMathLine ** iLine,
                                   double iDistMinExtrapol);
                                         
  // Destructor
	~CATExtrapolAndReconvergeSharpCrvSur();

  /*
   * This method allows caller to get result, ie. the reconverged SurParam.
   * It returns TRUE if Run has been performed with success, and FALSE if
   * a severe problem occured during Run (throw, null pointer, etc.)
   */
  CATBoolean GetReconvergedSurParam(CATSurParam & oParamOnSurf);
  /*
   * This method is similar to previous one: it allows to get all the reconverged
   * SurParam in oParamOnSurf tab. oNbSurParam is filled with the number of result
   * (eg. NbLine).
   *
   * PLEASE NOTE : memory is allocated for oParamOnSurf. Caller must manage deletion.
   */
  CATBoolean GetReconvergedSurParam(int & oNbSurParam,CATSurParam *& oParamOnSurf);

  /*
   * It returns TRUE if the surface has been extrapolated.
   */
  CATBoolean SurfaceHasBeenExtrapolated();

  /*
   * This method allows caller to know if reconvergence for line 'iIndexLine'
   * has been performed with success. It returns TRUE if 'iIndexLine' has 
   * succeeded, FALSE otherwise.
   *
   * IMPORTANT :
   *        We insist on the fact that if FALSE is returned, parameter 
   *        returned by GetReconvergedSurParam method will be the BEST
   *        found but will not strictly ensure a reconverged intersection.
   *
   * PLEASE NOTE :
   *      - This method is significant only with a CGMLevel >= ExtrapolAndReconvergeSharpCrvSur_NewRun
   *      - iIndexLine is element of [ 0 , iNbLine-1 ]
   *      - The method throws if iIndexLine < 0 or iIndexLine >= iNbLine
   */
  CATBoolean IsReconverged(int iIndexLine = 0);

   /*
    * This method should be used if caller wants to manage singular angle tolerance.
    *
    *     iSingularAngle = sinus of the angle limit (or the angle limit itself in radians
    *     if sufficiently small) below which the system is singular.
    *     If not explicitly set, default singular angle tolerance is 8.726e-4 radians (~= 0.05 degrees).
    *
    * DETAILS :
    *
    * Let L_i be one of the input lines of direction U_i, S the input surface, and N its normal
    * at init point.
    * Reconvergence is SINGULAR at init point, and nothing can be done, if:
    * 
    * U_i is tangent to surface at init point at tolerance angle_sing <===> U_i * N < sin( angle_sing ) 
    *
    * PLEASE NOTE :
    *      - This method is significant only with a CGMLevel >= ExtrapolAndReconvergeSharpCrvSur_NewRun
    */
  void SetSingularAngle(double iSingularAngle);

  /*
   * Prevents too big extrapolations, that could be done otherwise in the neighborhood of singularities
   */
  void AvoidExtrapolatationOnSingularity();
    
 protected:

   int RunOperator();

   int RunOld();
   int RunNew();

   CATSoftwareConfiguration * _Config;

   // Input data
   CATSurface * _Surface;
   CATSurParam * _SurParam;
   int _NbLine;
   CATMathLine  ** _Line;
   double _DistMinExtrapol;
   CATBoolean _AvoidSingularExtr;

   // Output data
   CATBoolean    _Extrapol;
   CATSurParam * _ParamReconv;
   CATBoolean  * _IsReconverged;

   // Internal data
   CATBoolean   _RunOK;
   CATBoolean   _ListOption;
   CATBoolean   _DefaultSingAngle;
   double       _SingularAngle;


//========================================================================
// CGMReplay
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString _OperatorId;

public:
	const CATString * GetOperatorId();

  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  virtual void WriteInput(CATCGMStream  & os);
  virtual void WriteOutput(CATCGMStream & os);
	virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  virtual void Dump( CATCGMOutput& os ) ;
  virtual void DumpOutput(CATCGMOutput & os);
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  virtual CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};

#endif




