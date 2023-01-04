#ifndef CATTopEdgePropagationCx3_H
#define CATTopEdgePropagationCx3_H

#include "CATTopEdgePropagation.h"
//
#include "CATTopDefine.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATWire.h"


class CATBody;
class CATVertex;
class CATDomain;
class CATWire;

enum CATTopEdgePropagationStatus { SELECTION_ABORTED     = 0 , 
  SELECTION_TO_CONTINUE = 1 ,
  SELECTION_ENDED       = 2 };


class CATTopEdgePropagationCx3 : public CATTopEdgePropagation
{


public :

  // Constructor
  CATTopEdgePropagationCx3 ( CATGeoFactory * iFactory     , 
    CATTopData    * iTopData     ,
    CATBody       * iBody        ,
    CATEdge       * iInitialEdge );

  // Destructor
  virtual ~CATTopEdgePropagationCx3();

  // SetReferenceFace
  virtual void SetReferenceFace ( CATFace      * iReferenceFace, 
    CATOrientation iReferenceOrientation = CATOrientationPositive );

  // SetBoundaryMode
  virtual void SetBoundaryMode ( const CATBoolean iBoundaryModeActive );

  // SetContinuityMode
  virtual void SetContinuityMode ( const CATResolutionType iContinuity );

  // SetTolerance
  virtual void SetTolerance ( const CATResolutionType   iContinuity , 
    const double            & iTolerance  );

  // GetDiagnoses
  void GetDiagnoses ( CATTopEdgePropagationDiagnosis oDiagnoses[2]          ,
    double                       * oDiagnosesValue = NULL );

  // ----------------------
  // methods for CGM Replay 
  // ----------------------
  static const CATString *GetDefaultOperatorId() { return &_OperatorId; }

protected :

  // Internal services
  void Clear();

  // RunOperatorForWire
  void InitOperatorForWire();

  // RunOperatorForShell
  void InitOperatorForShell();

  // EvalVertexGap
  double EvalVertexGap ( CATVertex * iCurVertex ,
    CATEdge   * iCurEdge1  ,
    CATEdge   * iCurEdge2  );

  // IsContinuous
  int IsContinuous ( CATVertex         * iFrontVertex                ,
    CATEdge           * iFrontEdge                  ,
    CATVertex         * iExtremityVertex            ,
    CATEdge           * iExtremityEdge              ,
    CATResolutionType * ioMaxContinuityFound = NULL ,
    double            * ioLowestValue        = NULL );

  // GetCurvature
  void GetCurvature ( const CATMathVector & iFirstDeriv  , 
    const CATMathVector & iSecondDeriv , 
    CATMathVector       & oCurvature   );

  // FindNextFunctionalEdge
  void FindNextFunctionalEdge ( const int                         iExtremity      ,
    CATVertex                      *  iFrontVertex    ,
    CATEdge                        *  iFrontEdge      ,
    CATVertex                      *& oNextVertex     ,
    CATEdge                        *& oNextEdge       ,
    CATTopEdgePropagationDiagnosis &  oDiagnosis      ,
    double                         &  oDiagnosisValue );

  // GetNextEligibleEdges
  void GetNextEligibleEdges ( CATVertex                      *  iFrontVertex      ,
    CATEdge                        *  iFrontEdge        ,
    CATVertex                      *  iExtremityVertex  ,
    CATEdge                        *  iExtremityEdge    ,
    CATLISTP(CATWire)              *  iWireList         ,
    CATTopEdgePropagationDiagnosis &  oDiagnosis        ,
    double                         &  oDiagnosisValue   ,
    CATLISTP(CATEdge)              &  oEligibleEdges    ,
    CATListOfInt                   &  oOrientationEdges ,
    CATListOfInt                   &  oIsSmallEdges     ,
    CATListOfDouble                &  oSmallEdgesLength ,
    CATWire                        *& ioSelectedWireOfSmallEdges,
    CATVertex                      *& ioSelectedSmallEdgeExtremity);

  // GetNextBoundedEdges
  void GetNextBoundedEdges ( CATVertex         * iExtremityVertex,
    CATEdge           * iExtremityEdge,  
    CATLISTP(CATWire) *  iWireList,
    CATLISTP(CATEdge) & oBoundedEdges,
    int               & oClosedSelection,
    int               & oNonManifoldCase);

  // MakeReport
  void MakeReport ();

  // MakeReport
  void DumpDiagnoses ( CATCGMOutput                 & os                 ,
    CATTopEdgePropagationDiagnosis iDiagnoses     [2] ,
    double                         iDiagnosesValue[2] );

  // ----------------------
  // methods for CGM Replay 
  // ----------------------
  static CATString  _OperatorId;

  const  CATString *GetOperatorId();

  CATExtCGMReplay  *IsRecordable( short &LevelOfRuntime, short &VersionOfStream );

  void              WriteInput( CATCGMStream  &ioStream );

  void              WriteOutput(CATCGMStream &ioStream);

  void              Dump( CATCGMOutput &os );

  void              DumpOutput(CATCGMOutput &os);

  void              DumpOutput(CATCGMStream &Str, CATCGMOutput &os, int VersionNumber=1);

  int               RunOperator();

  void              RequireDefinitionOfInputAndOutputObjects();

  CATBoolean        ValidateOutput(CATCGMStream &Str, CATCGMOutput &os, int VersionNumber=1);

  CATBoolean        ReadReferenceOutput(CATCGMStream &Str);

private:

  // IsExactContinuous
  int IsExactContinuous ( CATVertex         * iFrontVertex                ,
    CATEdge           * iFrontEdge                  ,
    CATVertex         * iExtremityVertex            ,
    CATEdge           * iExtremityEdge              ,
    CATResolutionType * ioMaxContinuityFound = NULL ,
    double            * ioLowestValue        = NULL );

  // IsPolyContinuous
  int IsPolyContinuous ( CATVertex         * iFrontVertex                ,
    CATEdge           * iFrontEdge                  ,
    CATVertex         * iExtremityVertex            ,
    CATEdge           * iExtremityEdge              ,
    CATResolutionType * ioMaxContinuityFound = NULL ,
    double            * ioLowestValue        = NULL );

protected :

  // Datas members
  // -------------
  CATBody                       * _InputBody;
  CATBody                       * _WorkingBody;
  CATEdge                       * _InitialEdge;
  CATFace                       * _InitialReferenceFace;
  CATFace                       * _ReferenceFace;
  CATDomain                     * _UpperDomain;
  CATWire                       * _OutputWire;
  CATSide                         _InitialSide;
  CATOrientation                  _InitialReferenceOrientation;
  CATBoolean                      _BoundaryMode;
  CATResolutionType               _Continuity;
  short                           _CGMVersionNumber;
  CATLONG32                       _CellsMaxDim;
  double                          _Tolerance[3];
  CATTopEdgePropagationDiagnosis  _Diagnoses        [2];
  double                          _DiagnosesValue   [2];
  CATTopEdgePropagationDiagnosis  _RefDiagnoses     [2];
  double                          _RefDiagnosesValue[2];

  CATBoolean                      _PolyhedralContext;

};

#endif
