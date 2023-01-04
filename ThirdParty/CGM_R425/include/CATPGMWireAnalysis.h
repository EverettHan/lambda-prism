#ifndef CATPGMWireAnalysis_h_
#define CATPGMWireAnalysis_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATTopDefine.h"
#include "CATCollec.h"

#ifndef NULL
#define NULL 0
#endif

class CATBody;
class CATCompositeLaw;
class CATGeoFactory;
class CATLaw;
class CATSelectCurveTool;
class CATVariableParallelLaw;
class CATWire;
class CATEdge;

// End : SUH : 2003:2:10
class ExportedByCATGMOperatorsInterfaces CATPGMWireAnalysis
{
public:
  /**
   * Constructor
   */
  CATPGMWireAnalysis();

  /**
   * Destructor
   */
  virtual ~CATPGMWireAnalysis();

  //---------------------------------------------------------------------------
  // Check wire is G1 continuous ( after offset if option law activated ) 
  //---------------------------------------------------------------------------
  virtual int IsG1(const double iTolAngle = CATTopSharpAngle) = 0;

  //---------------------------------------------------------------------------
  // Check 2 Edges is G1 continuous 
  //---------------------------------------------------------------------------
  virtual int IsEdgesG1(
    CATEdge *EdgePrec,
    CATOrientation OriPrec,
    int iNum1,
    CATEdge *EdgeSuiv,
    CATOrientation OriSuiv,
    int iNum2,
    const double iTolAngle = CATTopSharpAngle) = 0;

  //---------------------------------------------------------------------------
  // Split G0 Wire into G1 wire   
  //---------------------------------------------------------------------------
  virtual CATBody *SplitToG1Wires(
    CATGeoFactory *iFactory,
    const double iTolAngle = CATTopSharpAngle) = 0;

  //OU :
  virtual CATBody *SplitWireToG1Wires(
    CATGeoFactory *iFactory,
    const double iTolAngle = CATTopSharpAngle) = 0;

  //---------------------------------------------------------------------------
  // Extract One G1 Wire From one edge int the wire 
  //---------------------------------------------------------------------------
  virtual CATBody *ExtractG1WireFromEdge(
    CATGeoFactory *iFactory,
    CATEdge *iEdge,
    const double iTolAngle = CATTopSharpAngle) = 0;

  //---------------------------------------------------------------------------
  // aov wk 10 2003
  // Extract One G2 Wire From one edge int the wire 
  //---------------------------------------------------------------------------
  virtual CATBody *ExtractG2WireFromEdge(
    CATGeoFactory *iFactory,
    CATEdge *iEdge,
    double iCurvatureThreshold = 0.98) = 0;

  //---------------------------------------------------------------------------
  // alv wk 13 2003
  // Check wire is G2 continuous ( after offset if option law activated ) 
  //---------------------------------------------------------------------------
  virtual int IsG2(double iCurvatureThreshold = 0.98) = 0;

  // Start : SUH : 2003:2:10
  //---------------------------------------------------------------------------
  // Initialize SelectCurveTool
  //---------------------------------------------------------------------------
  virtual void SetSelectTool(CATSelectCurveTool *iTool) = 0;

  // End : SUH : 2003:2:10
  // Start : SUH : 2003:5:21
  virtual void AcceptSmoothVertices(CATBoolean iAccept) = 0;

  // End : SUH : 2003:5:21
  virtual void SetCircleTreatmentOn(CATCompositeLaw *iLaw) = 0;
};

//---------------------------------------------------------------------------
// Constructor 
//---------------------------------------------------------------------------
/**
 * @return [out, delete]
 */
ExportedByCATGMOperatorsInterfaces CATPGMWireAnalysis *CATPGMCreateWireAnalysis(
  CATWire *iWire,
  CATCompositeLaw *iOffset = NULL,
  CATLONG32 ilevel = 0);

#endif /* CATPGMWireAnalysis_h_ */
