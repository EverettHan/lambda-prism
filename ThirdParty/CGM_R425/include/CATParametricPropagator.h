#ifndef CATParametricPropagator_H
#define CATParametricPropagator_H

#include "PersistentCell.h"
#include "ListPOfCATFace.h"
#include "CATListOfCATPCurves.h"
#include "CATListOfCATCrvLimits.h"
#include "CATListOfInt.h"
#include "CATMathDef.h"
#include "CATSysErrorDef.h"
#include "CATBoolean.h"
class CATGeoFactory;
class CATEdge;
class CATPCurve;
class CATCrvParam;
class CATSurParam;
class CATMathVector;
class CATSoftwareConfiguration;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
class ExportedByPersistentCell CATParametricPropagator
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
{
public:

  CATParametricPropagator(CATGeoFactory& iFactory, CATSoftwareConfiguration& iConfig, const ListPOfCATFace& iFaces); // Support Faces
  ~CATParametricPropagator();

  HRESULT Run(const int iFaceIndex, const CATSurParam& iStartLocationOnFace, const double iDUV[2], const CATBoolean iBothSide=FALSE);

  CATPositiveLength GetLength() const;

  // Created PCurves, Their Limits, PCurves Orientation, supporting Face indexes
  void GetResult(CATLISTP(CATPCurve)& oPCurves, CATListOfInt& oOrns, CATListOfInt& oFaceIndexes);

  void Reset(); // To allow a new Run

private:
  HRESULT Propagate(int& ioFaceIndex, CATEdge*& ioCrossedEdge, CATSurParam& ioUV, double ioDUV[2]);
  HRESULT PropagateAccrossEdge(CATEdge& iEdge, CATFace& iFace, CATCrvParam& iParam, CATMathVector& iVector, int& oNewFaceIndex, CATSurParam& oUV, double oDUV[2]);

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  ListPOfCATFace            _Faces;
  CATGeoFactory&            _Factory;
  CATSoftwareConfiguration& _Config;
  CATBoolean                _Run;
  CATLISTP(CATPCurve)       _PCurves;
  CATListOfInt              _PCurveOrns;
  CATListOfInt              _FaceIndexes; 
};
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif 

