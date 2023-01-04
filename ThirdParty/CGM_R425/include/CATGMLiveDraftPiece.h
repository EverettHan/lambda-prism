#ifndef CATGMLiveDraftPiece_H
#define CATGMLiveDraftPiece_H

#include "CATMathInline.h"

#include "CATGMModelInterfaces.h"
#include "CATDRepSeed.h"

#include "ListPOfCATFace.h"
#include "ListPOfCATGMLiveDraftPiece.h"
#include "CATBoolean.h"
#include "CATMathDirection.h"
#include "CATListOfCATCells.h"
#include "CATListOfCATCurves.h"
#include "CATIsoParameter.h"
#include "CATListOfDouble.h"
#include "CATListValCATMathDirection.h"

class CATCell;
class CATSurface;
class CATCurve;
class CATCellManifold;
class CATMathPlane;

class ExportedByCATGMModelInterfaces CATGMLiveDraftPiece : public CATDRepSeed
{
public: 
  CATGMLiveDraftPiece(
          CATIsoParameter   iIsoParDir,
          ListPOfCATFace  & iRepFaces);
  CATGMLiveDraftPiece(
          ListPOfCATFace  & iRepFaces); // deprecated

  virtual ~CATGMLiveDraftPiece();

  enum DetectionType {Undefined = 0, Logical = 1, Geometric = 2};

  void SetData(CATAngle iAngle, 
               CATMathDirection const & iPullingDirection, 
               ListPOfCATCell & iNeutralCells);

  void GetNeutralCurves(CATLISTP(CATCurve) & oNeutralCurves, ListPOfCATCell & oNeutralCells) const;
  void SetNeutralCurves(CATLISTP(CATCurve) & iNeutralCurves, ListPOfCATCell & iNeutralCells);

  CATBoolean HasAngle(CATAngle & oAngle) const;
  void SetAngle(CATAngle iAngle);
  void DeleteAngle();

  CATBoolean HasPullingDirection(CATMathDirection & oPullingDirection) const;
  void SetPullingDirection(CATMathDirection const & iPullingDirection);
  void DeletePullingDirection();

  CATBoolean HasNeutralCells(ListPOfCATCell & oNeutralCells) const;
  void SetNeutralCells(ListPOfCATCell & iNeutralCells);
  void AppendNeutralCells(ListPOfCATCell & iNeutralCells);
  void DeleteNeutralCells();

  void AddInvalidNeutralCellCandidate(CATCell & iFace);
  void GetInvalidNeutralCellCandidates(ListPOfCATCell & oFaces);

  //DSH1 Start Nov,2018
  CATBoolean HasUnAffectedFacesToDraft(ListPOfCATFace & oUnAffectedFacesToDraft) const;
  void SetUnAffectedFacesToDraft(ListPOfCATFace & iUnAffectedFacesToDraft);
  //DSH1 End Nov,2018

  DetectionType GetDetectionType();

  CATMathPlane* GetDraftPlane();
  void SetIsPlanarGeometry(CATBoolean iIsPlanarGeometry);
  void SetHasLocalData(CATBoolean iHasLocalData);
  void SetDraftPlane(CATMathPlane& iMathPlane);
  void SetAngleSignNeedsValidation(CATBoolean iNeedsValidation);
  void SetDetectionType(DetectionType iDetectionType);
  void SetIsoParDir(CATIsoParameter iIsoParDir);
  void AppendPullingDirectionSourceFace(CATFace * iSourceFace);
  CATIsoParameter GetIsoParDir() const;
  CATBoolean AngleSignNeedsValidation() const;
  CATBoolean IsPlanarGeometry() const;
  CATBoolean HasLocalData() const;
  CATBoolean IsComplete() const;
  void GetPullingDirectionSourceFaces(ListPOfCATFace & oSourceFaces);

  void ClearProvisionalData() const;
  void AppendProvisionalData(CATAngle iAngle, CATMathDirection & iPullingDirection) const;
  CATBoolean ResolveProvisionalData(double iAngleTol, double iLargeEpsgForAngleTest);

  CATBoolean IsCompatible(CATGMLiveDraftPiece & iOtherDraftPiece, double iAngleTol, CATBoolean oReverseAngle);

  virtual CATGMLiveDraftPiece * GetAsDraftPiece();


protected:

private:
  CATLISTP(CATCurve) _NeutralCurves; // If an offset of a draft surface, this is the reference's neutral curve.
  CATMathPlane* _DraftPlane;
  CATBoolean _IsPlanarGeometry;
  CATBoolean _HasLocalData;
  CATBoolean _AngleSignNeedsValidation;
  DetectionType _DetectionType;
  CATIsoParameter _IsoParDir;

  CATAngle * _Angle;
  CATMathDirection * _PullingDirection;
  ListPOfCATCell * _NeutralCells;
  ListPOfCATFace * _UnAffectedFacesToDraft; //DSH1 Nov 2018

  ListPOfCATCell _NeutralCellsFromNeutralCurves;
  ListPOfCATCell _InvalidNeutralCellCandidates;
  ListPOfCATFace _PullingDirectionSourceFaces;

  mutable CATListOfDouble _ProvisionalDraftAngles;
  mutable CATLISTV(CATMathDirection) _ProvisionalPullingDirections;
};

#endif

