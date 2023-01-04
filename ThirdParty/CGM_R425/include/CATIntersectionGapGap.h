#ifndef CATINTERSECTIONGAPGAP_H
#define CATINTERSECTIONGAPGAP_H

// COPYRIGHT DASSAULT SYSTEMES 1999


// DESCRIPTION  : Intersection of a PCurve and a Gap.
// Versionning Interne - EAB - Octobre 2004

#include "Y30C1XMM.h"

#include "CATSurParam.h"
#include "CATSkillValue.h"
#include "CATCGMVirtual.h"

#include "CATConst2D.h"
#include "CATIntersectionPCrvPCrvSign.h"
#include "CATGeoFactory.h"

class CATSoftwareConfiguration;

class ExportedByY30C1XMM CATIntersectionGapGap  : public CATCGMVirtual
{
 private:
//- Private Data
  CATGeoFactory * _Factory;
  CATSoftwareConfiguration * _Config;

  // Data about the gap1.
  const CATSurParam *start1, *end1;

  // Data about the gap2.
  const CATSurParam *start2, *end2;

  // Data about the solution point.
  const CATSurParam * p1;
  const CATSurParam * p2;
  CATLONG32 index;
  CATIntersectionPCrvPCrvSign signature;

 public:
//- Constructor
  CATIntersectionGapGap (CATGeoFactory * Factory,
			 const CATSurParam * Start1,
			 const CATSurParam * End1,
			 const CATSurParam * Start2,
			 const CATSurParam * End2);

  CATIntersectionGapGap (CATGeoFactory * Factory,
       CATSoftwareConfiguration * iConfig,
			 const CATSurParam * Start1,
			 const CATSurParam * End1,
			 const CATSurParam * Start2,
			 const CATSurParam * End2);

  ~CATIntersectionGapGap();

//- Public methods
  void Run();

  void BeginningPoint();
  CATLONG32  NextPoint();
  CATLONG32  GetNumberOfPoints();
  const CATSurParam * GetSurParam(const CATSurParam * p);
  CATIntersectionPCrvPCrvSign GetPointSignature(const CATSurParam * P);
  CATIntersectionPCrvPCrvCrossing GetPointCrossing(const CATSurParam * P);
};

ExportedByY30C1XMM CATIntersectionGapGap*
CreateIntersection (CATGeoFactory * Factory,
		    const CATSurParam * Start1,
		    const CATSurParam * End1,
		    const CATSurParam * Start2,
		    const CATSurParam * End2,
		    const CATSkillValue skill = BASIC);

ExportedByY30C1XMM CATIntersectionGapGap*
CATCreateIntersection (CATGeoFactory * Factory,
        CATSoftwareConfiguration * iConfig,
		    const CATSurParam * Start1,
		    const CATSurParam * End1,
		    const CATSurParam * Start2,
		    const CATSurParam * End2,
		    const CATSkillValue skill = BASIC);

ExportedByY30C1XMM void Remove(CATIntersectionGapGap * Intersection);

#endif
