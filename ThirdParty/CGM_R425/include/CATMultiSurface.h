#ifndef CATMultiSurface_h
#define CATMultiSurface_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===================================================
// XXX XX/XX/XXXX : HAHA
// JSX 20/11/2011 : Ajouts arg CATLISTP(CATSurLimits)au constructeur
// PKC    Jul. 13 : CreatePLine
// JSX    Nov. 14 : SetName
// Q48    May  15 : Extrapolation / limits functions
// R1Y    Dec. 15 : Modified and added functions for limits.
// R1Y    Jan. 16 : Added Stream() and UnStream().
// R1Y    Apr. 16 : Added XCAD_SetCurrentLimits().
// R1Y    May  17 : Added a factory argument to UnStream().
// R1Y    Jul. 17 : Added GetSurfaceExtremities().
// LJL2   Sep. 19 : Added EvalPoint(), EvalFirstDeriv(), EvalNormal(), CreateParam()
//===================================================

// Basic types
#include "CATDataType.h"
#include "CATBoolean.h"

#include "CATSurLimits.h"
#include "CATSurParam.h"
#include "YP00IMPL.h"
#include "CATListOfCATSurfaces.h"
#include "CATListOfCATSurLimits.h"
#include "CATListOfCATPCurves.h"
#include "CATCGMVirtual.h"
#include "CATCGMOutput.h"
#include "CATErrorDef.h"
#include "CATString.h"
#include "CATCGMStream.h"
#include "CATMultiSurParam.h"

class CATSurface;
class CATMathFunctionXY;
class CATGeoFactory;

class ExportedByYP00IMPL CATMultiSurface : public CATCGMVirtual
{
  //
  // Class representing a rectangular matrix of surfaces
  // with Nu and Nv surfaces in U and in V respectively.
  //
public:
  //
  // Construction of the empty matrix
  //
  CATMultiSurface (const CATLONG32 iNu, 
                   const CATLONG32 iNv);

  // Constructor with one surface => Nu = Nv = 1
  CATMultiSurface (const CATLONG32      iNu, 
                   const CATLONG32      iNv,
                         CATSurface   * iSurface, 
                         CATSurLimits & iLimits);

  // Constructor with a list of Surface
  CATMultiSurface (const CATLONG32                iNu,
                   const CATLONG32                iNv,
                         CATLISTP(CATSurface)   * iSurList,
                         CATLISTP(CATSurLimits) * iLimitsList = NULL);
  
  //
  // Destructor
  //

  ~CATMultiSurface ();
  
  //
  // Set one surface of the matrix (0<=iIndexU<Nu and 0<=iIndexV<Nv)
  //

  void SetSurface (const CATLONG32      iIndexU, 
                   const CATLONG32      iIndexV, 
                         CATSurface   * iSurface, 
                   const CATSurLimits & iLimits);
  
  void SetClosedU(CATBoolean iClosedU = TRUE);
  void SetClosedV(CATBoolean iClosedV = TRUE);
  
  //
  // Number of surfaces in U and in V
  //

  CATLONG32 GetNumberOfSurfacesU() const;
  CATLONG32 GetNumberOfSurfacesV() const;
  
  //
  // Retrieve one surface of the matrix
  //
  
  CATSurface* GetSurface (const CATLONG32      iIndexU, 
                          const CATLONG32      iIndexV) const;

  CATSurface* GetSurface (const CATLONG32      iIndexU, 
                          const CATLONG32      iIndexV, 
                                CATSurLimits & oLimits) const;
  
  void GetIndexesSurface (const CATSurface * iSurface, 
                                CATLONG32  & oIndexU, 
                                CATLONG32  & oIndexV) const;
  
  //
  // Retrieve the extremities of the limits of one surface of the multi-sirface
  //
  
  void GetSurfaceExtremities (const CATLONG32   iIndexU, 
                              const CATLONG32   iIndexV,
                                    double    & oMinU,
                                    double    & oMinV,
                                    double    & oMaxU,
                                    double    & oMaxV) const;
//
  // Get a function representing the multisurface with it's global limitations
  //

  void GetGlobalLimits(double & oUmin, 
                       double & oVmin,
                       double & oUmax,
                       double & oVmax) const;

  void GetInternalGlobalLimits(const CATLONG32   iIndexU, 
                               const CATLONG32   iIndexV,
                                     double    & oUmin,
                                     double    & oVmin,
                                     double    & oUmax,
                                     double    & oVmax) const;

  void GetGlobalEquation(const CATMathFunctionXY *& oXuv,
                         const CATMathFunctionXY *& oYuv,
                         const CATMathFunctionXY *& oZuv) const;
  
  //
  // Conversions of general global parameters to local Surface parameter
  //

  void ConvertGlobalToLocal(const double        iU,
                            const double        iV, 
                                  CATSurParam & oUV, 
                                  CATLONG32   & oIndexU, 
                                  CATLONG32   & oIndexV) const;

  void ConvertGlobalToLocal(const double      iU, 
                            const double      iV, 
                                  double    & oU,
                                  double    & oV, 
                                  CATLONG32 & oIndexU, 
                                  CATLONG32 & oIndexV) const;

  void ConvertLocalToGlobal(const CATSurParam & iUV, 
                            const CATLONG32     iIndexU,
                            const CATLONG32     iIndexV,
                                  double      & oU, 
                                  double      & oV) const;

  void ConvertLocalToGlobal(const double      iLocalU, 
                            const double      iLocalV, 
                            const CATLONG32   iIndexU, 
                            const CATLONG32   iIndexV,
                                  double    & oU, 
                                  double    & oV) const;

  //
  // Retrieve the point, the normal, or the first derivative associated with a CATMultiSurParam  
  //

  void EvalPoint(const CATMultiSurParam & iMultiSurParam,
	                   CATMathPoint     & oPoint) const;

  void EvalFirstDeriv(const CATMultiSurParam & iMultiSurParam,
	                        CATMathVector    & oDerivParamU,
	                        CATMathVector    & oDerivParamV) const;

  void EvalNormal(const CATMultiSurParam & iMultiSurParam,
	                    CATMathDirection & oNormal) const;

//
// Retrieve the CATMultiSurParam related to parameters U and V on the multisurface
//

  void CreateParam(double             iParamU,
	               double             iParamV,
	               CATMultiSurParam & oMultiSurParam) const;

  //
  // Check C0 closure
  //

  CATBoolean IsC0ClosedU() const;
  CATBoolean IsC0ClosedV() const;

  CATBoolean IsC0ClosedU(CATLONG32 *ioComputed);
  CATBoolean IsC0ClosedV(CATLONG32 *ioComputed);

  CATBoolean CanExtendLimits(const double iExtendFraction,
                             const CATBoolean iAbsoluteExtension = FALSE);
  void          ExtendLimits(const double iExtendFraction,
                             const CATBoolean iAbsoluteExtension = FALSE);
  CATBoolean CanExtendLimits(const double iExtMinU,
                             const double iExtMinV,
                             const double iExtMaxU,
                             const double iExtMaxV);
  void          ExtendLimits(const double iExtMinU,
                             const double iExtMinV,
                             const double iExtMaxU,
                             const double iExtMaxV);

  // Create a "Pline" on a MultiSurface
  // it fills an ordered list of CATPline 
  // corresponding to the parametric LINE between
  // iStart and iEnd in UV space of MultiSurface
  // options 
  //   * if iForceBorder is set to TRUE and if iStart and iEnd are defining an isparametric Line 
  //   we create the isoparametric line that is nearest to iStart and iEnd in UV space
  //   * if iStart3D and iEnd3D are provided they will be used to relimit the Line 
  //   (only if iForceBorder is Set to TRUE) 
  HRESULT CreatePLine(const CATMathPoint2D       & iStart,
                      const CATMathPoint2D       & iEnd,
                            CATLISTP(CATPCurve)  & ioListOfPlines,
                      const CATBoolean             iForceBorder = FALSE,
                      const CATMathPoint         * iStart3D = 0,
                      const CATMathPoint         * iEnd3D = 0);

  void Stream(CATCGMStream & ioStream) const;

  // When un-streaming is performed, it is usually necessary that all geometry be created in the same factory.
  // If, on entry, "ioFactory" is null then the multi-surface is created in an arbitrary factory (which is not returned, but can subsequently be obtained from any surface in the multi-surface).
  // If, on entry, "ioFactory" is not null but "*ioFactory" is null then the multi-surface is created in an arbitrary factory, and this factory is returned in "*ioFactory".
  // If, on entry, "ioFactory" and "*ioFactory" are not null then the multi-surface is created in the factory "*ioFactory" (which is not modified).
  static CATMultiSurface * UnStream(CATCGMStream           & ioStream,
                                    CATGeoFactory ** const   ioFactory = NULL);

  void Dump(CATCGMOutput& os);

  void SetColoursAndPlot(const int* iRGB1, const int* iRGB2);

  // set Name
  // used by intersection operator (Prefix of the cgmreplay ) 
  void SetName(CATString a);
  CATString GetName();

  // The following function is for use in XCAD only.
  void XCAD_SetCurrentLimits(CATLISTP(CATSurface) & oListOfSurface,
                             int                  & oNu,
                             int                  & oNv);
protected:
  void ClearGlobalEquations();
  void ClearBorderPoints();

  void ComputeGlobalEquation() const;
  void ComputeBorderPoints() const;

private:
  void Init();
  void ComputeClose() const;

  enum MultiSurfaceExtensionType {Absolute_Different, Absolute_Same, Fraction};  // different lengths for each side, the same amount on each side, the same fraction for the two U-parameter sides and the same fraction for the two V-parameter sides

  void TestAndExtendLimits(const MultiSurfaceExtensionType   iExtensionType,
                           const double                      iMinUOrAbsoluteOrFraction,  // used for all three extension types
                           const double                      iMinV,                      // used only for Absolute_Different
                           const double                      iMaxU,                      // used only for Absolute_Different
                           const double                      iMaxV,                      // used only for Absolute_Different
                           const CATBoolean                  iDoExtension,
                                 CATBoolean                & oRequireExtrapolation);

// DATA
protected:

  CATSurface **_GridSurface;
  
  const CATLONG32 _Nu;
  const CATLONG32 _Nv;

  mutable double* _BordersU;
  mutable double* _BordersV;

  mutable double* _ShiftU;
  mutable double* _ShiftV;

  CATSurLimits **_GridOfSurLimits;
  
  mutable CATMathFunctionXY *_X;
  mutable CATMathFunctionXY *_Y;
  mutable CATMathFunctionXY *_Z;

private:
  CATString  _Name;
  
  mutable CATLONG32 _CloseComputedU;
  mutable CATLONG32 _CloseComputedV;
  mutable CATBoolean _ClosedU;
  mutable CATBoolean _ClosedV;
};
#endif
