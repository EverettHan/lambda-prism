#ifndef CATTopRibTraceObject_H
#define CATTopRibTraceObject_H
//=============================================================================
// COPYRIGHT Dassault Systemes 2003, 2004
//=============================================================================
//
// CATTopRibTraceObject.h
// 		
//=============================================================================
//  Oct 2003  Creation: JHG
//=============================================================================

#include "PersistentCell.h"
#include "CATTopRibObject.h"
#include "CATThrowForNullPointer.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATTopRibTraceObjects.h"
//#include "CATTopRibDef.h"
#include "CATAutoBaseColor.h"
#include "CATDerefMacros.h"

#define UNDEF_CallFilletOnUnfilletedParts

class CATMathPoint;
class CATMathVector;
class CATMathBox;
class CATMathTransformation;

class CATCartesianPoint;
class CATLine;
class CATSphere;
class CATBody;

class CATUnicodeString;

class CATAutoBaseGeometryContainer;

class ExportedByPersistentCell CATTopRibTraceObject: public CATTopRibObject
{
public:
  CATCGMNewClassArrayDeclare; // Pool allocation

public:
  CATTopRibTraceObject();
  virtual ~CATTopRibTraceObject();

  DEFINE_ADVOP_CLASS(CATTopRibTraceObject)

public:
  void Trace(CATUnicodeString &iFormatedString, ListPOfCATTopRibTraceObjects *iObjects = 0, int iVerboseLevel = 0);
  void Trace(const char *iFormatedText, ListPOfCATTopRibTraceObjects *iObjects = 0, int iVerboseLevel = 0);

  CATCartesianPoint *ShowPoint(CATGeoFactory &iFactory, CATSoftwareConfiguration *iConfig, const CATMathPoint &iPoint, const CATAutoBaseColor &iColor);
  CATLine *ShowLine(CATGeoFactory &iFactory, CATSoftwareConfiguration *iConfig, const CATMathPoint &iStart, const CATMathPoint &iEnd, const CATAutoBaseColor &iColor);
  CATAutoBaseGeometryContainer *ShowVector(CATGeoFactory &iFactory, CATSoftwareConfiguration *iConfig, const CATMathPoint &iPoint, const CATMathVector &iVector, const CATAutoBaseColor &iColor, CATBoolean iDisplayCone = 1);
  CATAutoBaseGeometryContainer *ShowTriangle(CATGeoFactory &iFactory, CATSoftwareConfiguration *iConfig, const CATMathPoint &iP0, const CATMathPoint &iP1, const CATMathPoint &iP2, const CATAutoBaseColor &iColor);
  CATSphere *ShowSphere(CATGeoFactory &iFactory, CATSoftwareConfiguration *iConfig, const CATMathPoint &iPoint, double iRadius, const CATAutoBaseColor &iColor);
  CATAutoBaseGeometryContainer *ShowAABB(CATGeoFactory &iFactory, CATSoftwareConfiguration *iConfig, const CATMathBox &iAABB, const CATAutoBaseColor &iColor);
  CATAutoBaseGeometryContainer *ShowOBB(CATGeoFactory &iFactory, CATSoftwareConfiguration *iConfig, const CATMathBox &iAABB, const CATMathTransformation &iLocalToGlobal, const CATAutoBaseColor &iColor);

  int GetVerboseLevel();

private:
  void CreateTraceText(CATUnicodeString &iFormatedString, CATUnicodeString &oString, ListPOfCATTopRibTraceObjects *iObjects);
  void CreateObjectTraceText(CATUnicodeString &oString);
};


#endif // !CATTopRibTraceObject_H
