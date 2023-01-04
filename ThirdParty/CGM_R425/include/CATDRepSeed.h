// ----------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// ST5: Feature recognition -- Recognition Primitive -- | Generic Level |
// ----------------------------------------------------------------------------//

#ifndef CATDRepSeed_H
#define CATDRepSeed_H

#include "CATMathInline.h"

#include "CATGMModelInterfaces.h"

#include "ListPOfCATFace.h"
#include "ListPOfCATDRepSeed.h"
#include "CATBoolean.h"

class CATFace;
class CATGMLiveFilletPiece;
class CATGMLiveExtrusionPrimitive;
class CATGMLiveFilletRibbonPiece;
class CATGMLiveFilletSphericalPiece;
class CATGMLiveFilletCompleteSkeletonPiece;
class CATGMLiveChamferRibbonPiece;
class CATGMLiveDraftPiece;
class CATGMLiveLogoCandidate;
class CATWallBendDRepSeed;

class ExportedByCATGMModelInterfaces CATDRepSeed
{
public: 
  CATDRepSeed(ListPOfCATFace &iRepFaces); 
  virtual ~CATDRepSeed();

  void GetRep(ListPOfCATFace &oRepFaces);

  INLINE CATBoolean HasInRep(CATFace &iFace) const;

  virtual CATGMLiveFilletPiece * GetAsFilletPiece();

  virtual CATGMLiveFilletRibbonPiece * GetAsFilletRibbonPiece();
  virtual CATGMLiveFilletSphericalPiece * GetAsFilletSphericalPiece();
  virtual CATGMLiveFilletCompleteSkeletonPiece * GetAsFilletCompleteSkeletonPiece();
  virtual CATGMLiveChamferRibbonPiece * GetAsChamferRibbonPiece();
  virtual CATGMLiveDraftPiece * GetAsDraftPiece();
  virtual CATGMLiveLogoCandidate * GetAsLogoCandidate();
  virtual CATWallBendDRepSeed * GetAsWallBendDRepSeed();

  virtual CATGMLiveExtrusionPrimitive * GetAsExtrusionPrimitive();

  static CATDRepSeed * Locate(CATFace &iFace, ListPOfCATDRepSeed &iPrimitives);
  static void GetAllPieces(ListPOfCATFace iFaces, ListPOfCATDRepSeed &iPrimitives, ListPOfCATDRepSeed &oPrimitivesWithFaces);
  static void GetAllReps(ListPOfCATDRepSeed &iPrimitives, ListPOfCATFace &ioReps);

  CATBoolean HasSameRepAs(CATDRepSeed &iPrimitive);
  static void RemoveDuplicates(ListPOfCATDRepSeed &iPrimitives);

protected:
  void SetRep(ListPOfCATFace &iRepFaces);

private:
  int _FacesCount;
  CATFace** _Faces;
};

INLINE CATBoolean CATDRepSeed::HasInRep(CATFace &iFace) const
{
  for ( int i=0; i<_FacesCount; i++ )
    if ( _Faces[i]==&iFace )
      return TRUE;

  return FALSE;
}

#endif

