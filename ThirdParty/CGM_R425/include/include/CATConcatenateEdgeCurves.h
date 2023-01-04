/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATConcatenateEdgeCurves.h
//=============================================================================
// Usage Notes: Operator used to concatenate EdgeCurves into one EdgeCurve
//              For internal topological use only (simplification).
//
// Specs (04/02/03) :
// * The operator takes in input a series of EdgeCurves ECrv[0..N-1] with corresponding
//   POECS that should be coincident along the curves.
// * IsConcatenable() should be called first with each pair ECrv[i] ECrv[i+1]
// * Simplification is done when :
//   1) All EdgeCrv have the same number of subcurves
//   2) Each subcurve SubCrv of each ECrv[i] can be simplified with one of the subcurve
//      ConfSubCrv of ECrv[0]. Simplifiable means one of the following :
//      a) equal (SubCrv=ConfSubCrv)
//      b) SubCrv and ConfSubCrv are two PLines on the same surface, 
//         numerically confused (lineartransformation is allowed on parameters)
//   3) The RefCurve of each ECrv[i] is either
//      a) simplifiable with the refcurve of ECrv[0]
//      b) in a linearmapx correspondance with SubCrv, with SubCrv simplifiable with
//         the RefCurve of ECrv[0]
//
//=============================================================================
// Sep. 01   Creation                                   X. Gourdon
// 04/11/08 NLD Ajout _OperatorId et GetOperatorId()
// 12/03/20 Q48 Headers etc for math versioning
//=============================================================================

#ifndef CATConcatenateEdgeCurves_H
#define CATConcatenateEdgeCurves_H

// ExportedBy
#include "GeoTopo.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATBoolean.h"
#include "CATListOfCATEdgeCurves.h"
#include "CATListOfCATPointOnEdgeCurves.h"
#include "CATCreateConcatenateEdgeCurves.h"

//BigScale Mod. #SKA
#include "CATTolerance.h"

class CATMathTransformation1D;
class CATEdgeCurve;
class CATGeoFactory;
class CATPointOnEdgeCurve;
class CATMapX;
class CATEdgeCurve;
class CATCurve;
class CATSoftwareConfiguration;

class ExportedByGeoTopo CATConcatenateEdgeCurves : public CATGeoOperator
{
  public:
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

  CATConcatenateEdgeCurves(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig=0);
  virtual ~CATConcatenateEdgeCurves();

  // Use this method to add successively the consecutive EdgeCurves to be concatenated.
  // The StartPOEC of the current AddInput() should be in the same vertex as the EndPOEC of the
  // previous AddInput()
  void AddInput(CATEdgeCurve * iECrv, CATPointOnEdgeCurve * iStartPOEC, CATPointOnEdgeCurve * iEndPOEC);

  int RunOperator();
  // Operator Id
  const  CATString  *  GetOperatorId();  
  //-----------------------------------------------------------------------
  //- Reading output
  //-----------------------------------------------------------------------
  CATEdgeCurve * GetResult();
  // Fill in oTransfo the transfo1D mapping iECrv (one of the input EdgeCrv) into the result EdgeCrv.
  void GetCorrespondingTransformation1D(CATEdgeCurve * iInputECrv, CATMathTransformation1D & oTransfo);

  // iInputECrv is one of the input EdgeCurve, iInputCrv one of its representant
  // return iOutputCrv, the corresponding representant in the result EdgeCurve,
  // and oTransfo the transfo1D mapping between iInputCrv and iOutputCrv
  void GetCorrespondingCurve(CATEdgeCurve * iInputECrv,
                             CATCurve * iInputCrv, CATCurve * &iOutputCrv, CATMathTransformation1D & oTransfo);

  // Static methods
  static int nbSubCrv;
  static CATBoolean IsConcatenable(CATEdgeCurve * iECrv1, 
                                  CATPointOnEdgeCurve * iStartPOEC1, CATPointOnEdgeCurve * iEndPOEC1,
                                  CATEdgeCurve * iECrv2, 
                                  CATPointOnEdgeCurve * iStartPOEC2, CATPointOnEdgeCurve * iEndPOEC2,
                                  CATSoftwareConfiguration * iConfig = NULL,
                                  CATCurve ** ioCorrespondingRefCurve2 = NULL,
								  CATCurve ** ioRefCurve1 = NULL,
								  int & ioNbSubCrv = nbSubCrv);
  
private:

	  // 0=not confused
	  // 1=confused, not same curve
	  // 2=iCrv1==iCrv2.
  static unsigned char IsConfused( CATSoftwareConfiguration * iConfig, CATBoolean iOldMode, CATBoolean iFatEdgeFixed,
                                const CATCurve * iCrv1, const CATCurve * iCrv2, 
                                CATMathTransformation1D & oTransfo);

 static CATBoolean IsConfused3DLine( CATSoftwareConfiguration * iConfig,
                                     const CATCurve           * iCrv1, 
                                     const CATCurve           * iCrv2, 
                                     CATMathTransformation1D  & oTransfo);


  static CATBoolean IsMapXLinear(const CATMapX * iMapX, double & alpha, double & beta);

  void AllocRepresentant();
  // returns TRUE on success.
  CATBoolean SetupRepresentantOld(short CGMLevel, int principalRank);
  // returns TRUE on success.
  CATBoolean SetupRepresentant(short CGMLevel, int principalRank);

  static int AreConcatenable(
    CATSoftwareConfiguration * iSoftwareConfiguration,
    CATLISTP(CATEdgeCurve) & iEdgeCrvs,
    CATLISTP(CATPointOnEdgeCurve) & iStartPoecs,
    CATLISTP(CATPointOnEdgeCurve) & iEndPoecs,
	int iPrincipalRank = 1,
	int & ioNbSubCrv = nbSubCrv);

  void InvertOrderOfInputs();

  CATSoftwareConfiguration * _SoftwareConfiguration;


  CATLISTP(CATEdgeCurve)        _EdgeCrvs;
  CATLISTP(CATPointOnEdgeCurve) _StartPoecs;
  CATLISTP(CATPointOnEdgeCurve) _EndPoecs;

  CATLONG32 _NbECrv, _NbSubCrvs, _PrincipalRank;
  CATCurve *** _Representant; // _Representant[i][j] is the j-th repr. of the i-th EdgeCrv
  CATMathTransformation1D ** _Transfo;

  CATEdgeCurve * _ResultECrv;

  //  private  static  data  
  static  CATString  _OperatorId;  

  //void FillNonLinearEdgeCurveRanks();
  CATListOfInt _nonLinearEdgeCrvRanks;
};

#endif
