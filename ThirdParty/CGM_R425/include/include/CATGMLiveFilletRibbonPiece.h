#ifndef CATGMLiveFilletRibbonPiece_H
#define CATGMLiveFilletRibbonPiece_H

#include "CATIACGMLevel.h"

#include "CATGMLiveFilletPiece.h"
#include "CATSurfaceRecognizer.h"
#include "CATTopDefine.h"
#include "CATBoolean.h"
#include "ListPOfCATEdge.h"
#include "CATIsoParameter.h"
#include "CATMathInline.h"
#include "CATGMLiveFilletPieceData.h"
#include "CATGMFilletBorderAnalyzer.h"

class CATBody;

class CATGMLiveFilletRibbonPiece: public CATGMLiveFilletPiece
{
public: 
  enum DetectionType {Undefined=0, Measured=1, Canonic=2, Logic=3};
  enum RadiusType {Rad_Undefined=0, Rad_Constant=1, Rad_Variable=2, Rad_Tritangent=3};

  CATGMLiveFilletRibbonPiece(ListPOfCATFace &iRepFaces, 
                             ListPOfCATFace &iSupportFaces1, 
                             ListPOfCATFace &iSupportFaces2,
                             CATGMLiveFilletPieceData const & iFilletData,
                             double *iMaxAngle = NULL); 
  virtual ~CATGMLiveFilletRibbonPiece();

  void SetData(ListPOfCATFace &iRepFaces, 
               ListPOfCATFace &iSupportFaces1, 
               ListPOfCATFace &iSupportFaces2);
  double GetRadius();
  void GetFilletPieceData(CATGMLiveFilletPieceData & oFilletData) const;
  virtual CATGMLiveFilletRibbonPiece * GetAsFilletRibbonPiece();

  void SetMaxAngle(double iMaxAngle);
  CATBoolean GetMaxAngle(double &oMaxAngle);

  void SetConvexity(const CATTopConvexity iConvexity, CATBody &iBody);
  CATTopConvexity GetConvexity(CATBody &iBody);

  void SetRepType(CATSurfaceRecognizer::SurfaceType iRepType);
  CATSurfaceRecognizer::SurfaceType GetRepType();

  void SetDetectionType(DetectionType iDetection);
  CATGMLiveFilletRibbonPiece::DetectionType GetDetectionType();

  void GetSupports(ListPOfCATFace &oSupportFaces1, ListPOfCATFace &oSupportFaces2);

  void SetTransversalEdges(ListPOfCATEdge &iStartEdges, ListPOfCATEdge &iEndEdges);
  CATBoolean GetTransversalEdges(ListPOfCATEdge &oStartEdges, ListPOfCATEdge &oEndEdges);

  void SetUndefBorderEdges(ListPOfCATEdge &iUndefBrdrEdges);
  CATBoolean GetUndefBorderEdges(ListPOfCATEdge &iUndefBrdrEdges);

  void SetClosedTube();
  CATBoolean IsClosedTube();

  void SetRadiusType(RadiusType iRadiusType);

  void AddCrossedFace(CATFace &iCrossedFace);
  void AddCrossedFace(ListPOfCATFace &iCrossedFaces);
  void GetCrossedFaces(ListPOfCATFace &oCrossedFaces);

  void AddAllowedJointSupport(CATFace &iAllowedJointSupport);
  void AddAllowedJointSupport(ListPOfCATFace &iAllowedJointSupports);
  void GetAllowedJointSupport(ListPOfCATFace &oAllowedJointSupports);

  INLINE CATIsoParameter GetCircularIsopar() const { CATIsoParameter Isoparam = CATIsoParNoDir; _FilletData.GetCircularIsopar(Isoparam); return Isoparam; };
  INLINE void SetCircularIsopar(CATIsoParameter iIsoparam) { _FilletData.SetCircularIsopar(iIsoparam); }

  INLINE CATBoolean HasInSupport(const int iSupportIndex, CATFace* iFace) { return 0!=_SupportFaces[iSupportIndex].Locate(iFace); };
  CATBoolean HasInSupport(const int iSupportIndex, ListPOfCATFace &iFaces);
  CATBoolean HasInSupport(ListPOfCATFace &iFaces);

  virtual void FlagAsVariable();
  virtual CATBoolean IsConstant();
  virtual CATBoolean IsVariable();

  virtual void FlagAsTriTangent();
  virtual CATBoolean IsTriTangent();
  
  INLINE void FlagAsChordal(double &iChordLength) { _Chordal = TRUE; _ChordLength = iChordLength; };
  INLINE CATBoolean IsChordal() { return _Chordal; };
  INLINE double GetChordLength() { return _ChordLength; };

  void SetBorderAnalyzer(CATGMFilletBorderAnalyzer *iBorderAnalyzer);
  void GetBorderAnalyzer(CATGMFilletBorderAnalyzer *&oBorderAnalyzer);

  void SetPreciseExtremityRadii(double iExtrRadius[2]);
  CATBoolean GetPreciseExtremityRadii(double oExtrRadius[2]);

private:
  ListPOfCATFace _SupportFaces[2];
  ListPOfCATEdge *_TransversalEdges[2];
  ListPOfCATEdge _UndefBrdrEdges;
  //CATPositiveLength _VarRadii[2];
  //// Equal to MaxRadius for VariableFillet
  double _Radius;
  double *_MaxAngle;
  CATGMLiveFilletPieceData _FilletData;
  CATBody *_CurrentWorkingBody;
  CATTopConvexity *_Convexity;
  CATSurfaceRecognizer::SurfaceType _RepType;
  //CATIsoParameter _CircularIsopar;
  DetectionType _DetectionType;
  RadiusType _RadiusType;
  CATBoolean _ClosedTube;
  
  ListPOfCATFace _CrossedFaces;
  ListPOfCATFace _AllowedJointSupports;

  CATGMFilletBorderAnalyzer *_BorderAnalyzer;

  CATBoolean _Chordal;
  double _ChordLength;
};


#endif

