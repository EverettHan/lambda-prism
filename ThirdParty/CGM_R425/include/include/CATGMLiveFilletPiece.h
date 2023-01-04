#ifndef CATGMLiveFilletPiece_H
#define CATGMLiveFilletPiece_H

#include "CATMathInline.h"

#include "CATGMModelInterfaces.h"
#include "CATDRepSeed.h"

#include "ListPOfCATFace.h"
#include "ListPOfCATGMLiveFilletPiece.h"
#include "CATBoolean.h"

class CATGMLiveFilletRibbonPiece;
class CATGMLiveFilletSphericalPiece;
class CATGMLiveFilletCompleteSkeletonPiece;
class CATGMLiveChamferRibbonPiece;
class CATFace;

class ExportedByCATGMModelInterfaces CATGMLiveFilletPiece: public CATDRepSeed
{
public: 
  CATGMLiveFilletPiece(ListPOfCATFace &iRepFaces); 
  virtual ~CATGMLiveFilletPiece();

  virtual CATGMLiveFilletPiece * GetAsFilletPiece();

  virtual CATGMLiveFilletRibbonPiece * GetAsFilletRibbonPiece();
  virtual CATGMLiveFilletSphericalPiece * GetAsFilletSphericalPiece();
  virtual CATGMLiveFilletCompleteSkeletonPiece * GetAsFilletCompleteSkeletonPiece();
  virtual CATGMLiveChamferRibbonPiece * GetAsChamferRibbonPiece();

  virtual void FlagAsTriTangent();
  virtual void FlagAsVariable();

  virtual CATBoolean IsConstant();
  virtual CATBoolean IsVariable();
  virtual CATBoolean IsTriTangent();

protected:

private:

};

#endif

