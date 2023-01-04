#ifndef CATPGMWireStatus_h_
#define CATPGMWireStatus_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATTopDefine.h"
#include "CATDataType.h"
#include "CATMathDef.h"
#include "CATCollec.h"

#ifndef NULL
#define NULL 0
#endif

class CATMathVector;
class CATEdge;
class CATVertex;
class CATMathPoint;
class CATCrvParam;
class CATMathBox;
class CATWire;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATPGMWireStatus
{
public:
  /**
   * Constructor
   */
  CATPGMWireStatus();
  /**
   * Destructor
   */
  virtual ~CATPGMWireStatus();

  //-------------------------------------------------------------------------
  // Elements Access
  //-------------------------------------------------------------------------
  virtual CATEdge *GetFirstEdge(CATOrientation *oOri = NULL) = 0;

  virtual CATEdge *GetLastEdge(CATOrientation *oOri = NULL) = 0;

  virtual CATVertex *GetFirstVertex() = 0;

  virtual CATVertex *GetVertex(CATLONG32 iRank) = 0;

  virtual CATVertex *GetLastVertex() = 0;

  //-------------------------------------------------------------------------
  // Coordinates Access
  //-------------------------------------------------------------------------
  virtual CATMathPoint GetFirstCoord() = 0;

  virtual CATMathPoint GetVertexCoord(CATLONG32 iRank) = 0;

  virtual CATMathPoint GetLastCoord() = 0;

  //-------------------------------------------------------------------------
  // Geometry Data Access
  //-------------------------------------------------------------------------
  virtual CATCrvParam GetFirstParamOnEdgeCurve() = 0;

  virtual CATCrvParam GetLastParamOnEdgeCurve() = 0;

  virtual void GetVertexParamOnEdgeCurve(CATLONG32 iRank, CATCrvParam *oParam) = 0;

  virtual CATMathVector GetFirstTangent() = 0;

  virtual CATMathVector GetLastTangent() = 0;

  virtual void GetTangent(CATLONG32 iRank, CATMathVector *oVector) = 0;

  virtual CATPositiveLength GetLength() = 0;

  //    CATWire * DoInvert(CATBody *iTargetBody);
  virtual CATMathBox GetBoundingBox(CATLONG32 iRank) = 0;

  virtual CATMathBox GetBoundingBox() = 0;

  virtual double GetMaxDimension() = 0;
};

ExportedByCATGMOperatorsInterfaces CATPGMWireStatus *CATPGMCreateWireStatus(CATWire *iWire);

#endif /* CATPGMWireStatus_h_ */
