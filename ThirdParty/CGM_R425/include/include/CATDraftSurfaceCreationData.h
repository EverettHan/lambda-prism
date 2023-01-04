/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATDraftSurfaceCreationData:
// Data for creation of Draft surfaces.
//
//=============================================================================
// Usage notes:
//
//
//=============================================================================
// Aug. 99   Creation                                          NDN
// Dec. 00   Modif. variable/equerre                           NDN
// Apr. 03   Separation en deux classes derivees               PFV
//=============================================================================
#ifndef CATDraftSurfaceCreationData_H
#define CATDraftSurfaceCreationData_H

#include "YP00IMPL.h"
#include "CATSurface.h"
#include "CATMathDirection.h"
#include "CATListOfCATCrvParams.h"
#include "CATCGMVirtual.h"

class ExportedByYP00IMPL CATDraftSurfaceCreationData : public CATCGMVirtual
{
public:
  enum DraftDataType { SimpleDraft, DraftBothSides, Unknown, DraftBothSidesNeutralNeutral };
  DraftDataType DataType;

  CATDraftSurfaceCreationData();
  virtual ~CATDraftSurfaceCreationData();

  virtual int IsEqualTo(CATDraftSurfaceCreationData * DataToCompare, double LengthTol=0, double AngleTol=0) const;
  virtual CATDraftSurfaceCreationData::DraftDataType GetDataType() const;
  
  CATSurface* DraftSurface;
  CATMathDirection direction;
  const CATLISTP(CATCrvParam) * params; //Only used if Type=GenericRuledSurface
  double angle;
  
};
#endif
