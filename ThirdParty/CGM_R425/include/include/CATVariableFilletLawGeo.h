//=============================================================================
// Copyright Dassault Systemes 1997-2017, all rights reserved
//=============================================================================
//
// CATVariableFilletLawGeo:
//
//=============================================================================
// Usage notes:
//=============================================================================
// March 2017      Creation (SMT1)
//=============================================================================
#ifndef CATVariableFilletLawGeo_h
#define CATVariableFilletLawGeo_h

#include "Connect.h"
#include "CATCGMOperator.h"
#include "CATSoftwareConfiguration.h"
#include "CATCollec.h"
#include "ListPOfCATEdge.h"
#include "CATSplineLawOp.h"
#include "CATSurLimits.h"
#include "CATMathInterval.h"
#include "CATMathFP.h"

#include "CATLISTV_Clean.h"
#define CATLISTV_RemoveDuplicatesCount
#define CATLISTV_QuickSort
#include "CATLISTV_Declare.h"
#include "CATLISTV_Define.h"

CATLISTV_DECLARE(CATMathInterval);

class InputValue;
class CATMathIntervalND;
class CATFace;

class SupportData{
  friend class InputValue;

protected: 

  SupportData(CATGeoFactory * iFactory,
              CATSoftwareConfiguration * iConfig);

   ~SupportData();

  void ComputeSupports(CATEdge *iEdge, const double &iParam, CATBody * iBody);

  void ComputeDomain(const CATCurve * iSpine);

  void ComputeInitPoint(CATLaw * iMapping, double Param, double iRadius);

  CATBoolean ComputeSolvedParam(CATBody * iBody, CATCurve * iSpine, double &iRadius, CATLONG32 iClose, double &ioSolvedParam, CATLaw * iMapping,CATLaw * iRadiusLaw);

private:

  void SolveParamDebug(double id[4],const CATPCurve * iContact, const CATSurface *iSurface );

  CATSoftwareConfiguration * _Config;
  CATGeoFactory * _Factory;

  CATEdge * _Edge;
  double _InputParam;
  const CATEdgeCurve * _EdgeCrv;
  short _EdgeVsCurve;
  short _EdgeOnFace1, _EdgeOnFace2;
  const CATPCurve *_PC1, *_PC2;
  CATFace * _Face1,* _Face2;
  CATSurface * _Supp1,* _Supp2;
  CATSurLimits _Lim1,_Lim2;
  CATMathIntervalND *_Domain;
  short _Orientation[2];
  double _FixPoint[3];
  double _Init[8];
  double _Center1[2], _Center2[2];
};

class InputValue{
public:
  InputValue(double    iParameter,
             double    iCurveLinParam,
             double    iRadius,
             CATLONG32 iSlopeDefined,
             double    iSlope,
             CATEdge   *iEdge);

  ~InputValue();
 
  int operator ==(const InputValue& iValue) const
  {
      return CATCompare(_Parameter,iValue._Parameter)==0 ;
  };
 
  int operator !=(const InputValue& iValue) const
  {
    return CATCompare(_Parameter,iValue._Parameter) !=0;
  };

  int Compare(const InputValue &iValue);
 
  CATBoolean ComputeSolvedParam(CATGeoFactory * iFactory,
                          CATSoftwareConfiguration * iConfig,
                          CATBody * iBody,
                          CATCurve* iSpine,
                          CATLaw * iMapping,
                          CATLaw * iRadiusLaw,
                          CATLONG32 iClose);
 
  void GetValues(double  &ioParameter, double &ioRadius, CATLONG32 &ioSlopeDefined, double & ioSlope);
  double GetSolvedParam();

private:

    double _Parameter;
    double _SolvedParam;
    double _CurveLinParam;
    double _Radius;
    CATLONG32 _SlopeDefined;
    double _Slope;
    SupportData * _Data;
    CATEdge * _Edge;
};

CATLISTV_DECLARE(InputValue);
typedef CATLISTV(InputValue) InputTable;

class ExportedByConnect CATVariableFilletLawGeo :public CATCGMOperator
{
public:
  CATVariableFilletLawGeo(CATGeoFactory * iFactory,
    CATSoftwareConfiguration * iConfig,
    CATLONG32 iNumberOfEdges,
    CATLISTP (CATEdge) & iEdges,
    CATLONG32 * iOrientations,
    CATLONG32 iNumberOfImpositions,  
    CATLONG32 * iEdgeIndex, 
    double * iCurvilinearParams, 
    double * iRadii,
    CATLONG32 * iSlopeDefined, 
    double * iSlope,
    CATLONG32 iClose
    );

  ~CATVariableFilletLawGeo();

  CATBoolean GetDeviation(double & ioDeviation);
  int RunOperator();
  void SetCleanCurve(CATCurve *iCleanCurve, CATLaw* iMapping, CATBody* iCurrentBody);
  CATSplineLaw  * GetRadiusLaw();
  void GetRadiiExtrema(double &ioMin, double & ioFirst, double & ioLast);
  void SetRadiusLawMode(int iRadiusLawMode);

  CATLaw ** GetMultiRadiusLaw(int &ioNumberMultiLaw/*, CATCrvLimits * &ioRadiusLawLimits*/);
  int GetLawIndex(CATSurface *iSurface1, CATSurface *iSurface2);

private:

  void ComputePartialLengths();
  void CreateSortedTable();
  void FindTwistEdges();
  CATSplineLaw* CreateLawFromTable(InputTable *iTable);
  void SplitTable(CATLISTV(CATMathInterval) &iOldIntervals, CATLISTV(CATMathInterval) &iNewIntervals, CATLISTV(CATMathInterval) &iRadiusRange);

  CATSoftwareConfiguration * _Config;

  CATCurve *_CleanCurve;
  CATSplineLaw   * _RadiusLaw;
  CATSplineLawOp * _SplineLawOp;

  CATLONG32 _NumberOfEdges;
  CATLISTP(CATEdge) * _Edges;
  CATLISTP(CATEdge)  _MyEdges;
  CATLONG32 * _Orientations;

  CATLONG32 _NumberOfImpositions; 
  CATLONG32 * _EdgeIndex; 
  double * _CurvelinearParams; 
  double * _Radii;
  CATLONG32 * _SlopeDefined;
  double * _Slope;

  CATLONG32 _Close;
  int _RadiusLawMode;

  CATLaw  * _MappingLaw;
  CATBody * _Body;

  double * _LengthsOnEdgeTrain; 
  double * _PartialLengthsOnEdgeTrain;

  double _Deviation;
  double _RadiusMin, _FirstRadius, _LastRadius;

  InputTable *_Table;

  int _NumberOfMultiLaws;
  InputTable *_MultiTable;
  CATSplineLaw   ** _MultiRadiusLaw;
  CATMathSetOfLongs * _EdgeToMultiLaw;

  CATBoolean _InitialLawComputed;
  CATBoolean _InvertDirection;
};

#endif
