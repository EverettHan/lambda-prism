// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyPhoenixMouchard.h
//
//===================================================================
//
// Usage note: Debug only, don't use
//===================================================================
//
// Nov 2011 Creation: JXO
//===================================================================

#ifndef CATIPolyPhoenixMouchard_h
#define CATIPolyPhoenixMouchard_h

// ExportedBy
#include "PolyBodyBVH.h"

// Poly
#include "CATRefCounted.h"
#include "CATMapOfPtrToPtr.h"

// System
#include "CATMutex.h"
#include "CATBoolean.h"

class CATPolyPhoenixMetaMouchard;
class CATBVHTreeSet;
class CATPolyBodyBVHTreeSet;
class CATPolyVisuBVHTreeSet;
class CATPolyInterferenceOper;
class CATPolyVisuInterferenceOper;
class CATPolyBodyRayCastingOper;
class CATechExt;
class CATPolyPPPathSmoothing;
class CATPolyPathPlanningSolver;

class ExportedByPolyBodyBVH CATIPolyPhoenixMouchard : public CATRefCounted
{
public:
  CATIPolyPhoenixMouchard(){}

  // BVHTrees
  virtual void Register(CATBVHTreeSet * ts) = 0;
  virtual void Unregister(CATBVHTreeSet * ts) = 0;
  virtual void RegisterPoly(CATPolyBodyBVHTreeSet * ts) = 0;
  virtual void UnregisterPoly(CATPolyBodyBVHTreeSet * ts) = 0;
  virtual void RegisterVisu(CATPolyVisuBVHTreeSet * ts) = 0;
  virtual void UnregisterVisu(CATPolyVisuBVHTreeSet * ts) = 0;
  // Operators
  virtual void Register(CATPolyInterferenceOper * op) = 0;
  virtual void Unregister(CATPolyInterferenceOper * op) = 0;
  virtual void RegisterVisu(CATPolyVisuInterferenceOper * op) = 0;
  virtual void UnregisterVisu(CATPolyVisuInterferenceOper * op) = 0;
  virtual void Register(CATPolyBodyRayCastingOper * op) = 0;
  virtual void Unregister(CATPolyBodyRayCastingOper * op) = 0;
  virtual void Register(CATPolyPPPathSmoothing * op) = 0;
  virtual void Unregister(CATPolyPPPathSmoothing * op) = 0;
  virtual void Register(CATPolyPathPlanningSolver * op) = 0;
  virtual void Unregister(CATPolyPathPlanningSolver * op) = 0;

protected:
  virtual ~CATIPolyPhoenixMouchard(){}
};

class ExportedByPolyBodyBVH CATPolyPhoenixMouchard : public CATIPolyPhoenixMouchard
{
public:
  CATPolyPhoenixMouchard();

  // Not virtual (To be called in constructor)
  void AddMouchard(CATIPolyPhoenixMouchard * m);
  void SetInterferencePhoenixExtension(CATechExt *iExtension);
  void SetRayCastingPhoenixExtension(CATechExt *iExtension);
  void SetPathSmoothingPhoenixExtension(CATechExt *iExtension);
  void SetPathPlanningPhoenixExtension(CATechExt *iExtension);

  // Virtual:
  // BVHTrees
  virtual void Register(CATBVHTreeSet * ts);
  virtual void Unregister(CATBVHTreeSet * ts);
  virtual void RegisterPoly(CATPolyBodyBVHTreeSet * ts);
  virtual void UnregisterPoly(CATPolyBodyBVHTreeSet * ts);
  virtual void RegisterVisu(CATPolyVisuBVHTreeSet * ts);
  virtual void UnregisterVisu(CATPolyVisuBVHTreeSet * ts);
  // Operators
  virtual void Register(CATPolyInterferenceOper * op);
  virtual void Unregister(CATPolyInterferenceOper * op);
  virtual void RegisterVisu(CATPolyVisuInterferenceOper * op);
  virtual void UnregisterVisu(CATPolyVisuInterferenceOper * op);
  virtual void Register(CATPolyBodyRayCastingOper * op);
  virtual void Unregister(CATPolyBodyRayCastingOper * op);
  virtual void Register(CATPolyPPPathSmoothing * op);
  virtual void Unregister(CATPolyPPPathSmoothing * op);
  virtual void Register(CATPolyPathPlanningSolver * op);
  virtual void Unregister(CATPolyPathPlanningSolver * op);

  CATBoolean IsEmpty();
public:
  static CATPolyPhoenixMouchard * s_Singleton;
  static CATMutex s_Mutex;

protected:
  ~CATPolyPhoenixMouchard();

private:
  CATMapOfPtrToPtr m_ListOfTS;
  CATMapOfPtrToPtr m_ListOfOP;
  CATPolyPhoenixMetaMouchard * m_MyMouchard;
  CATechExt * m_Pegase;
  CATechExt * m_Andromede;
  CATechExt * m_PathSmoothExt;
  CATechExt * m_PathPlanningExt;
};

#endif /* CATIPolyPhoenixMouchard_h */

