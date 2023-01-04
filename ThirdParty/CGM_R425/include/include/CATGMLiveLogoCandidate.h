#ifndef CATGMLiveLogoCandidate_H
#define CATGMLiveLogoCandidate_H

#include "CATIACGMLevel.h"

#include "CATGMModelInterfaces.h"

#include "CATDRepSeed.h"

#include "CATBoolean.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "CATMathInline.h"
#include "CATMathLine.h"

class CATBody;
class CATCGMHashTableWithAssoc;
class CATMathLine;

class ExportedByCATGMModelInterfaces CATGMLiveLogoCandidate : public CATDRepSeed
{
public: 
  CATGMLiveLogoCandidate(
      ListPOfCATFace & iRepFaces, 
      ListPOfCATFace & iSupportFaces); 

  virtual ~CATGMLiveLogoCandidate();

  void SetData(
      ListPOfCATEdge            & iBorderEdges, 
      CATCGMHashTableWithAssoc  * iBorderEdgesToAdjacentFaces,
      CATMathLine               & iAxis);

  void GetSupport(ListPOfCATFace & oSupportFaces);
  CATBoolean GetBorderEdges(CATBody & iBody, ListPOfCATEdge & oBorderEdges);
  CATBoolean GetBorderEdgesAssocFaces(CATBody & iBody, CATCGMHashTableWithAssoc *& oBorderEdgesToAdjacentFaces);
  CATBoolean GetAxis(CATBody & iBody, CATMathLine & oAxis);

  virtual CATGMLiveLogoCandidate * GetAsLogoCandidate();

  INLINE CATBoolean HasInSupport(CATFace * iFace) { return 0 != _SupportFaces.Locate(iFace); };
  
private:
  ListPOfCATFace _SupportFaces;
  ListPOfCATEdge _BorderEdges;
  ListPOfCATEdge * _OldBorderEdges; // deprecated
  CATCGMHashTableWithAssoc* _BorderEdgesToAdjacentFaces;
  CATMathLine _Axis;
  CATBody *_CurrentWorkingBody;
};


#endif

