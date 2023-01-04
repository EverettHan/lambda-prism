#ifndef CATManifoldLocalSpec_h
#define CATManifoldLocalSpec_h
// ----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2013
// ----------------------------------------------------------------------------
// Persistent modelisation of a specification applying locally on DRep
// ----------------------------------------------------------------------------
#include "CATPersistentCell.h"
#include "CATCGMStreamAttribute.h"
#include "ListPOfCATManifoldLocalSpec.h"
#include "CATCGMNewArray.h"

class CATHGeometry;
class CATDeclarativeManifold;
class CATManifoldLocalRadius;
class CATTransfoManager;
class CATCGMOutput;
class CATCloneManager;

class ExportedByPersistentCell CATManifoldLocalSpec : protected CATCGMStreamAttribute
{
public:
  CATCGMDeclareAttribute (CATManifoldLocalSpec,CATCGMStreamAttribute); 
  CATCGMNewClassArrayDeclare;     

  virtual ~CATManifoldLocalSpec();

  CATHGeometry* GetLocation() const;

  CATULONG32 GetSpecId() const;

  virtual CATBoolean HasSimilarData(const CATManifoldLocalSpec* iManifoldLocalSpec, const double iLengthTol) const;

  virtual void Dump(CATCGMOutput& os) const;

  virtual CATManifoldLocalRadius* GetAsManifoldLocalRadius() const;

// ----------------------------------------------------------------------------
// CGM DRep model internal use only
// ----------------------------------------------------------------------------
  static CATBoolean HasOwnedSpecs(CATDeclarativeManifold* iOwner);
  static void GetOwnedBy(CATDeclarativeManifold* iOwner, ListPOfCATManifoldLocalSpec& oOwnedSpecs);
  void SetOwner(CATDeclarativeManifold* iOwner); 
  static CATULONG32 GetNewId(CATDeclarativeManifold* iOwner, const CATULONG32 iPreferredIdToUse = 0); // Returns 1 whenever no Id exist, iPreferredIdToUse if not 0 and not already used
  static CATManifoldLocalSpec* RetreiveFromId(CATDeclarativeManifold* iOwner, const CATULONG32 iId);

  virtual CATManifoldLocalSpec* CloneAndMove3D(CATTransfoManager& iManager) = 0;
  virtual CATManifoldLocalSpec* Clone(CATCloneManager& iManager) = 0;
  virtual CATManifoldLocalSpec* Clone(CATDeclarativeManifold& iOwner, const CATBoolean iAllowSameId=FALSE) = 0;

// ----------------------------------------------------------------------------
// Protected & private section
// ----------------------------------------------------------------------------
protected:
  CATManifoldLocalSpec(CATHGeometry* iLocation, const CATULONG32 iId);
  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStr, CATManifoldLocalSpec& oSpec);
// ----------------------------------------------------------------------------
private:
  CATULONG32         _Id;
// ----------------------------------------------------------------------------
};

#endif

