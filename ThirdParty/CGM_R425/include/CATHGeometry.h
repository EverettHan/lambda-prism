#ifndef CATHGeometry_h
#define CATHGeometry_h

// COPYRIGHT DASSAULT SYSTEMES  2009

#include "CATGeometry.h"
#include "ListPOfCATCellManifold.h"

class CATLiveBody;
class CATDeclarativeManifoldCarrierBase;

#include "CATGMModelInterfaces.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATHGeometry ;
#else
extern "C" const IID IID_CATHGeometry ;
#endif

class CATHEdge;
class CATHVertex;
class CATIntersectionHVertex;
class CATRatioHVertex;
class CATDistanceHVertex;
class CATCGMOutput;

class ExportedByCATGMModelInterfaces CATHGeometry : public CATGeometry
{
  CATDeclareInterface;

public:

  virtual CATBoolean IsInside(ListPOfCATCellManifold iSupport[], const int iSupportCount, ListPOfCATCellManifold iLimiting[], const int iLimitingCount) const = 0;
  virtual int GetNumberOfContexts() const = 0;
  virtual int GetContext(int iContext, ListPOfCATCellManifold& oContext) const = 0; // returns the context type
  virtual CATBoolean HasSimilarData(const CATHGeometry* iOtherHGeometry, double iLengthTol) const = 0;
  virtual CATHGeometry* CreateImage(CATLiveBody& iLiveBody, CATDeclarativeManifoldCarrierBase& iCarrier, CATLONG32 iOrder=-2) const = 0;

  virtual CATHEdge*                 GetAsHEdge() = 0;
  virtual CATHVertex*               GetAsHVertex() = 0;
  virtual CATIntersectionHVertex*   GetAsIntersectionHVertex() = 0;
  virtual CATRatioHVertex*          GetAsRatioHVertex() = 0;
  virtual CATDistanceHVertex*       GetAsDistanceHVertex() = 0;

  // --------------------------------------------------------------------------
  // Debug only
  // --------------------------------------------------------------------------
  virtual void Dump(CATCGMOutput& os) = 0;


  // --------------------------------------------------------------------------
  // Do not use, not consolidated yet
  // --------------------------------------------------------------------------
  enum Status {Pending = 0, Active = 1};
  //virtual CATHGeometry::Status   GetStatus() = 0;
  enum Propagation {PropagationOff = 0, PropagationOn = 1};
  //virtual CATHGeometry::Propagation  GetPropagation() = 0;
};
  
CATDeclareHandler(CATHGeometry,CATGeometry);

#endif
