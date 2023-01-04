#ifndef CATIPGMWireContinuity_h_
#define CATIPGMWireContinuity_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATDataType.h"
#include "CATFreeFormDef.h"
#include "CATMathDef.h"

class CATBody;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMWireContinuity;

class ExportedByCATGMOperatorsInterfaces CATIPGMWireContinuity: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMWireContinuity();

  //=========
  // Methods
  //=========
  //
  // Run : compute continuity informations on body wire
  //
  virtual int Run() = 0;

  //
  // Get the number of vertex of the wire
  // Vertex index ranges from 1 to NbVertex()
  virtual int NbVertex() = 0;

  // GetGOrder : returns G continuity order of vertex iVertex
  // iVertex = [1..NbVertex()]
  // returns 0 if OK, != on error
  virtual CATLONG32 GetGOrder(int iVertex, CATFrFContinuity &oGOrder) = 0;

  // GetDeltaPt : returns oL = G0 gap (between points) at vertex iVertex
  // iVertex = [1..NbVertex()]
  // returns 0 if OK, != on error
  virtual CATLONG32 GetDeltaPt(int iVertex, CATLength &oL) = 0;

  // GetDeltaTg : returns oA = G1 gap (between tangents) at vertex iVertex
  // iVertex = [1..NbVertex()]
  // returns 0 if OK, != on error
  virtual CATLONG32 GetDeltaTg(int iVertex, CATAngle &oA) = 0;

  // GetRatioCv : returns oRatioCv = G2 curvature ratio of curvature vectors at vertex iVertex
  // oRatioCv value is in ]0..1]
  // iVertex = [1..NbVertex()]
  // returns 0 if OK, != on error
  virtual CATLONG32 GetRatioCv(int iVertex, double &oRatioCv) = 0;

  // ------------------------------------
  //  To disappear
  // ------------------------------------
  // 
  // Get G continuity order of vertex iVertex 
  // WARNING : old style method, to disappear.
  // Use the Run() + GetGOrder(i),GetDeltaPt(i),GetDeltaTg(i) methods
  //
  virtual CATFrFContinuity GetResult(int iVertex) = 0;

  // Choose curvature measure implementation 
  // iMeasureMode = 1 or 2
  // In both implementations :
  //     - C0 measure based on standard C0 measure corresponding to CatC0
  //     - C1 measure based on standard C1 measure corresponding to CatC1
  // iMeasureMode = 1 to perform a C2 measure by comparison of 
  //                difference between curvature radii and CATEpsg
  // iMeasureMode = 2 to perform a standard C2 measure corresponding to CatC2
  // default (historical) value is 1.
  virtual void SetMeasureMode(CATLONG32 iMeasureMode) = 0;

  // Get curvature measure implementation 
  // MeasureMode = 1 or 2
  // In both implementations :
  //     - C0 measure based on standard C0 measure corresponding to CatC0
  //     - C1 measure based on standard C1 measure corresponding to CatC1
  // MeasureMode = 1  a C2 measure by comparison of 
  //                difference between curvature radii and CATEpsg
  // iMeasureMode = 2  a standard C2 measure corresponding to CatC2
  // default (historical) value is 1.
  virtual CATLONG32 GetMeasureMode() = 0;

  //-----------------------------------------------------------------------------
  // no doc
  virtual void SetTolPt(CATLength iTolPt) = 0;

  virtual void SetTolTg(CATAngle iTolTgDeg) = 0;

  virtual void SetTolCv(double iTolCv) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMWireContinuity(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMWireContinuity *CATPGMCreateWireContinuity(
  CATGeoFactory *iFactory,
  CATTopData *TopData,
  CATBody *iBodyWire);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMWireContinuity *CATPGMCreateWireContinuity(
  CATGeoFactory *iFactory,
  CATBody *iBodyWire);

#endif /* CATIPGMWireContinuity_h_ */
