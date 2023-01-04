/*-*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 2002
//==========================================================================
//
// CATBreakPCurveImport :
//
// This class is first designed to insert knots on P-Multiform
// to enable us to adapt it to the new piecewise linear surface parametrization
//==========================================================================
#ifndef CATBreakPCurveImport_H
#define CATBreakPCurveImport_H

#include "CATDataType.h"
#include "Interfaces.h"

#include "CATListOfDouble.h"
#include "CATCreateBreakPCurveImport.h"
#include "CATPGMBreakPCurveImport.h"
#include "CATTolerance.h"

class CATFrFNurbsMultiForm;
class CATMathPoint;
class CATKnotVector;
class CATMathPolynomX;
class CATSoftwareConfiguration;

class CATPCurve;
class CATSurfaceImport;

//-----------------------------------------------------------------------------
class ExportedByInterfaces CATBreakPCurveImport: public CATPGMBreakPCurveImport
{
public :
  CATBreakPCurveImport(CATSoftwareConfiguration * iConfig,
                       CATFrFNurbsMultiForm* mf,
                       CATLONG32 nbKnotsU, double* knotsU,
                       CATLONG32 nbKnotsV, double* knotsV,
                       const CATTolerance & iTolObject = CATGetDefaultTolerance()); // idem, le dernier param ne sera pas utilise, mais peut etre initialise a -1.
  
  CATBreakPCurveImport(CATSoftwareConfiguration * iConfig,
                       CATPCurve* initialPCurve,
                       CATSurfaceImport* surfaceImport);

  virtual ~CATBreakPCurveImport();
  
  CATLONG32 Run();
  
  CATFrFNurbsMultiForm* GetNewMF();
  
  // attention, ces MF sont des donnees membres de la classe et
  // sont detruites par le destructeur de la classe.
  void GetResultingMultiForms(CATLONG32& nbNewMFs, 
                              CATFrFNurbsMultiForm**& newMFs,
                              CATLONG32*& iNumSupportingSurf);
  
  
  void GetResultingPCurves(CATLONG32& nbNewPCurves, CATPCurve**& newPCurves);
  
private : 
		void DataInitialization();
    
    CATLONG32 RunCanonicalPCurveBreak();
    
    CATLONG32 RunMFBreak();
    
    CATLONG32 ComputeBreakParametersOnArc(CATMathPoint* CPs,  
                                          CATKnotVector* initialKnotVector,
                                          CATLONG32 degree,
                                          CATLONG32 iArc, 
                                          CATListOfDouble& breakParams);
    
    CATLONG32 CheckKnotsToInsert(CATListOfDouble& breakParams);
    
    CATLONG32 MakeKnotInsertionsOnMF(CATListOfDouble& breakParams,
                                     CATLONG32 degree);
    
    CATLONG32 ReadMFEquations();
    
    CATLONG32 ComputeNbPossibleIntersections(CATMathPoint* arcCPs, 
                                             CATLONG32 degree, 
                                             CATLONG32& nbPossibleIntersectionsAlongU, CATLONG32& iFirstKnotAlongU,
                                             CATLONG32& nbPossibleIntersectionsAlongV, CATLONG32& iFirstKnotAlongV);
    
    CATLONG32 FindIntersectionParameters(double paramMin, double paramMax, 
                                         CATLONG32 nbKnots, double* Knots,
                                         CATLONG32& nbPossibleIntersections, CATLONG32& iFirstNumCrossingParam);
    
    CATLONG32 ComputeAccurateIntersections(CATLONG32 iArc,
                                           CATLONG32 nbPossibleIntersectionsAlongU, 
                                           CATLONG32 iFirstKnotAlongU,
                                           CATLONG32 nbPossibleIntersectionsAlongV, 
                                           CATLONG32 iFirstKnotAlongV,
                                           CATListOfDouble& breakParams);
    
    CATLONG32 ComputeOneWayAccurateIntersection(CATMathPolynomX* px,
                                                CATLONG32 iArc,
                                                CATLONG32 nbPossibleCrossing,
                                                CATLONG32 iFirstKnot, 
                                                double* knots, 
                                                CATListOfDouble& breakParams);
    
    CATLONG32 FinalMFBreak(const CATListOfDouble& breakParams, 
                           CATFrFNurbsMultiForm* newMF, 
                           CATLONG32& nbNewMFs, 
                           CATFrFNurbsMultiForm**& newMFs, 
                           CATLONG32*& iNumSupportingSurf);
    
    
    CATLONG32 ComputeINumSupportingSurface(CATLONG32 nbBreaksU, double* uBreaks,
                                           CATLONG32 nbBreaksV, double* vBreaks,
                                           CATLONG32 nbNewMFs, CATFrFNurbsMultiForm** newMFs,
                                           CATLONG32* iNumSupportingSurf);
    
    CATLONG32 FindPosition(const double& u, CATLONG32 nbBreaksU, double* uBreaks, 
                           CATLONG32& iPosUI, CATLONG32& iPointUIOnTheBoundary);
    
    CATFrFNurbsMultiForm* _mf;
    CATLONG32             _nbKnotsU;
    double*               _knotsU;
    CATLONG32             _nbKnotsV;
    double*               _knotsV;
    CATFrFNurbsMultiForm* _newMF;
    
    CATLONG32     _initialPCurveNbKnots;
    const double* _PCurveKnots;
    
    CATMathPolynomX** _Fx;
    CATMathPolynomX** _Fy;
    CATMathPolynomX** _Fz;
    CATMathPolynomX** _Fw;
    
    CATLONG32 _isRational;
    CATLONG32 _equationsRead;
    
    CATLONG32 _isCanonic;
    
    CATPCurve*        _initialPCurve;
    CATSurfaceImport* _surfaceImport;
    CATLONG32   _nbNewPCurves;
    CATPCurve** _newPCurves;
    
    CATLONG32              _nbNewMFs;
    CATFrFNurbsMultiForm** _newMFs;
    CATLONG32*             _iNumSupportingSurf;
    CATSoftwareConfiguration * _Config;

    CATLONG32 _GetNewMFDone;
    const CATTolerance & _TolObject;
};
#endif









