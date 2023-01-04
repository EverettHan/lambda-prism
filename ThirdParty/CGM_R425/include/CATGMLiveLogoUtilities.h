#ifndef CATGMLiveLogoUtilities_H
#define CATGMLiveLogoUtilities_H

#include "CATCGMNewArray.h"

#include "PersistentCell.h"
//#include "ListPOfCATDRepSeed.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "CATErrorDef.h"

#include "CATBoolean.h"
//#include "CATLISTV_CATMathVector.h"
//#include "CATMathConstant.h"

//class CATGeoFactory;
class CATSoftwareConfiguration;
class CATBody;
//class CATFace;
//class CATEdge;
//class CATCurve;
//class CATPCurve;
//class CATSurface;
//class CATMathVector;
//class CATMathDirection;
class CATCGMHashTableWithAssoc;
class CATMathLine;

class ExportedByPersistentCell CATGMLiveLogoUtilities
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATGMLiveLogoUtilities(CATSoftwareConfiguration * iConfig);
  virtual ~CATGMLiveLogoUtilities();

static CATBoolean GetCandidateBorderEdges(
      CATBody         & iBody,
      ListPOfCATFace  & iLogoCandidateFaces,
      ListPOfCATEdge  & oBorderEdges);

static CATBoolean GetCandidateBorderEdgesAssocFaces(
      CATBody                   & iBody,
      ListPOfCATFace            & iLogoCandidateFaces,
      ListPOfCATEdge            & oBorderEdges,
      CATCGMHashTableWithAssoc *& oBorderEdgesToAdjacentFaces);

static CATBoolean GetCandidateData(
      CATBody                   & iBody,
      ListPOfCATFace            & iLogoCandidateFaces,
      ListPOfCATFace            & iLogoCandidateSupportFaces,
      ListPOfCATEdge            & oBorderEdges,
      CATCGMHashTableWithAssoc *& oBorderEdgesToAdjacentFaces,
      CATMathLine               & oAxis);

CATBoolean GetCandidateSizeAndHeight(
      CATBody         & iBody,
      ListPOfCATFace  & iLogoCandidateFaces,
      ListPOfCATFace  & iLogoCandidateSupportFaces,
      double          & oSize,
      double          & oHeight);

CATBoolean HasConsistentConvexity(
      CATBody         & iBody,
      ListPOfCATFace  & iLogoCandidateFaces);

protected:
  CATSoftwareConfiguration * _SoftwareConfiguration;
};

#endif 

