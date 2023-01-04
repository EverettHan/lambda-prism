// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATIntersectionVertexSur :
// Interface class for intersection of an vertex with a Surface
//
//=============================================================================
// Usage notes:
// The vertex is represented by a loop of points (there a two kind of points
// the Vertex Bounding Edge points (VBE) and Vertex Bounding Face points (VBF).
// The VBF points are on the same face and the VBE points are on two merged
// faces.
//
//                       |    |
//                       |  1 |
//                       S++++S
//            Face12    o      o    Face13
//                     o        o
//            --------S          S-----------
//                     +        +
//                2     SoooooS      3 
//                    |          |
//                  |    Face23    |
//
//=============================================================================
// Nov. 97  Creation                          P. Sebah & X. Gourdon
//=============================================================================
#ifndef CATIntersectionVertexSur_H 
#define CATIntersectionVertexSur_H 

#include "CATMathDef.h"
#include "CATIntersectionSign.h"
#include "CATSurLimits.h"
#include "CATSkillValue.h"
#include "Y30A3HGG.h"
#include "CATCGMVirtual.h"
#include "CATCreateIntersectionVertexSur.h" 

class CATGeoFactory;
class CATEdgeCurve; 
class CATSurface;
class CATCurve;
class CATCrvLimits;
class CATSurParam;
class CATMathPoint;
class CATSoftwareConfiguration;

class ExportedByY30A3HGG CATIntersectionVertexSur   : public CATCGMVirtual
{
  public:

  CATIntersectionVertexSur(CATGeoFactory *iFactory,
         CATSoftwareConfiguration * iConfig,
			   CATLONG32 iNbSurface,
			   CATSurface **iListOfSurface,
			   CATSurParam *iListOfCoupleOfParamUV,
			   CATSurface *iSurface);

  CATIntersectionVertexSur(CATGeoFactory *iFactory,
			   CATLONG32 iNbSurface,
			   CATSurface **iListOfSurface,
			   CATSurParam *iListOfCoupleOfParamUV,
			   CATSurface *iSurface);

  ~CATIntersectionVertexSur();
  
  // Set the limits of the intersecting surface
  void SetLimits(const CATSurLimits & iSurLimits);
  
  // Running the operator

  void Run();

  //
  // Case where the vertex is numerically a point :
  //
  CATBoolean IsVertexSolution(CATSurParam & oParamOniSurface) const;

  //
  //  Getting the VBF points
  //
  
  CATLONG32                  GetNumberOfVBFPoints() const;
  void                  BeginningVBFPoint();
  CATBoolean            NextVBFPoint();
  void                  GetSurfaceParam (CATSurParam & oParamOniSurface,
					 CATLONG32 & oIndexInList,
					 CATSurParam & oParamOnSurfaceOfList) const;
  CATIntersectionSign   GetSignatureVBF() const;

  //
  //  Getting the VBE points
  //
  CATLONG32                  GetNumberOfVBEPoints() const;
  void                  BeginningVBEPoint();
  CATBoolean            NextVBEPoint();
  void                  GetSurfaceParam (CATLONG32 & oIndexInList, CATSurParam & oParamOniSurface) const;
  CATIntersectionSign   GetSignatureVBE() const;

  // Getting the Mixed points
  CATLONG32                  GetNumberOfMixedPoints() const;
  void                  BeginningMixedPoint();
  CATBoolean            NextMixedPoint();
  void                  GetSurfaceParamMixed (CATLONG32 & oIndexPoint, CATSurParam & oParamOniSurface) const;
  CATIntersectionSign   GetSignatureMixed() const;
  

private:
  // Input datas
  CATGeoFactory * _Factory;
  CATSoftwareConfiguration * _Config;
  CATLONG32 _NbSurf;
  CATSurface ** _ListOfSurf;
  CATSurParam * _ListOfSurParam;
  CATSurface * _Surf;
  
  CATSurLimits _SurLim;

  // Transformed input datas
  CATMathPoint * _Pt3D;
  CATSurParam * _IncludedPt;
  double * _SignedDistance;

  // datas for output when the vertex is solution
  CATBoolean _IsVertexSolution;
  CATSurParam _VertexSolution;

  // datas for output on faces
  CATLONG32 _IndexVBF, _NbVBF;
  CATLONG32 * _ListIndexVBF;
  CATIntersectionSign * _SignatureVBF;
  CATSurParam * _VBFSurParam, * _ParamOnSurfOfList;
  
  // datas for output on edges
  CATLONG32 _IndexVBE, _NbVBE;
  CATLONG32 * _ListIndexVBE;
  CATIntersectionSign * _SignatureVBE;
  CATSurParam * _VBESurParam;

  // datas for mixed solutions
  CATLONG32 _IndexMixed, _NbMixed;
  CATLONG32 * _PointIndexMixed;
  CATIntersectionSign * _SignatureMixed;
  CATSurParam * _MixedSurParam;

};
ExportedByY30A3HGG 
CATIntersectionVertexSur * CreateIntersection (CATGeoFactory *iFactory,
					       CATLONG32 iNbSurface,
					       CATSurface **iListOfSurface,
					       CATSurParam *iListOfCoupledParamUV,
					       CATSurface *iSurface,
					       CATSkillValue  iMode=BASIC); 

ExportedByY30A3HGG void Remove(CATIntersectionVertexSur * ioOper);

#endif
