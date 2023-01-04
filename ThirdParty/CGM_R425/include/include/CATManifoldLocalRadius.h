#ifndef CATManifoldLocalRadius_h
#define CATManifoldLocalRadius_h
// ----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2013
// ----------------------------------------------------------------------------
// Persistent modelisation of a radius applying at a HVertex
// ----------------------------------------------------------------------------
#include "CATPersistentCell.h"
#include "CATManifoldLocalSpec.h"
#include "ListPOfCATCellManifold.h"
#include "CATMathDef.h"
#include "CATMathConstant.h"
#include "CATCGMNewArray.h"

class CATHVertex;
class CATDeclarativeManifold;

class ExportedByPersistentCell CATManifoldLocalRadius : public CATManifoldLocalSpec
{
public:
  CATCGMDeclareAttribute (CATManifoldLocalRadius,CATManifoldLocalSpec); 
  CATCGMNewClassArrayDeclare;     
  CATManifoldLocalRadius();

  static CATManifoldLocalRadius* Create(CATDeclarativeManifold* iOwner, CATHVertex* iLocation, const CATPositiveLength iRadius, CATAngle* iAngle, const CATULONG32 iId=0); // CGM internal use only

  virtual ~CATManifoldLocalRadius();

  CATHVertex*       GetLocation() const;
  CATPositiveLength GetRadius  () const;
  CATAngle*         GetAngle   () const;

  virtual CATBoolean HasSimilarData(const CATManifoldLocalSpec* iManifoldLocalSpec, const double iLengthTol) const;

  virtual CATManifoldLocalSpec* CloneAndMove3D(CATTransfoManager& iManager);
  virtual CATManifoldLocalSpec* Clone(CATCloneManager& iManager);
  virtual CATManifoldLocalSpec* Clone(CATDeclarativeManifold& iOwner, const CATBoolean iAllowSameId=FALSE);

  virtual void Dump(CATCGMOutput& os) const;

  // ----------------------------------------------------------------------------
  // Protected & private section
  // ----------------------------------------------------------------------------
  // Tell this that this.Context[iContextIndex] has been transfered through Joint
  // Will allow IsInside to filter out specs transfered through Joint
  // ----------------------------------------------------------------------------
  void SetThroughJointContext(const int iContextIndex);
  CATBoolean IsInside(ListPOfCATCellManifold iSupport[], const int iSupportCount) const;

protected:
  CATManifoldLocalRadius(CATHVertex* iLocation, const CATPositiveLength iRadius, CATAngle* iAngle, const CATULONG32 iId);
  virtual void Stream(CATCGMStream& ioStream) const;
  virtual void UnStream(CATCGMStream& ioStr);
// ----------------------------------------------------------------------------
private:
  virtual CATManifoldLocalRadius* GetAsManifoldLocalRadius() const;

  CATPositiveLength _Radius;
  CATAngle*         _Angle;
  int               _ThroughJointContext; // Not streamed data, for communication between Redo & rebuild DRep, indicates whether & which HVertex context has crossed a Joint
// ----------------------------------------------------------------------------
};

#endif

