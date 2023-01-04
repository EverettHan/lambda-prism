/* -*-C++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
// CATCurvesArrange :
// Operator offers a quick way to manage the order of a set of curves.
// It offers 3 possibilities :
// - check if the orientations given by user are coherent with
//   the list of pcurves.
// - computes th orientations of the list of pcurves given by user.
// - computes the orientations of the curves and re-order the list
//   if necessary.
//=============================================================================
//  Notes : user has to give the CATCrvLimits of the curves. If NULL,
//          operator uses current limits by default.
//=============================================================================
// Mar. 99   Creation                                   L. Mahe
// Apr. 99   Modification:                              L. Mahe
//           user must give CATCrvLimits
// Jul. 99   Correction:                                L. Mahe
//           bad allocation in ComputeOrientationMode
// Aug. 05   I replace show_trace by a define in .cpp   A. Louis
//           + suppression of non used methods for 
//           a better Coverage.
//=============================================================================
#ifndef CATCurvesArrange_h
#define CATCurvesArrange_h

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopDef.h"
#include "CATListOfCATCurves.h"
#include "CATListOfCATCrvLimits.h"
#include "CATDataType.h"

class CATCurve;
class CATMathPoint;
class CATCrvLimits;
class CATCrvParam;
class CATTopData;

enum CATArrangeMode { CheckOrientations,
                      ComputeOrientations,
                      ComputeOrientationsNoTolerance,
                      ArrangeCurves };

//-----------------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATCurvesArrange
{
  public :
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CATCurvesArrange(CATTopData      *iTopData,
                     CATLONG32        iNbCurves,
                     CATCurve       **iCurves,
                     CATCrvLimits    *iLimits,
                     double           iTolerance,
                     short           *iOrientations=NULL,
                     CATArrangeMode   iMode=ArrangeCurves);
    
    virtual ~CATCurvesArrange();     
    void    Run();

    //-------------------------------------------------------------------------
    // Result Access
    //-------------------------------------------------------------------------
    short   IsOrientationValid();
    void    GetComputedOrientations(short ** oOrientations);
    void    GetArrangedCurves(CATCurve *** oCurves,short ** oOrientations);


  private :

    // Private Data
    CATLONG32          _nb_curves;
    CATCurve        ** _curves;
    CATCurve        ** _input_curves;
    CATCrvLimits    *  _limits;
    CATCrvLimits    *  _input_limits;
    double             _tolerance;
    short            * _orientations;
    short              _CGMVersionNumber;
    CATArrangeMode     _mode;
    short              _validity;
    // Supression de show_trace remplacé par un define dans le .cpp ALV 24/08/05 coverage
    //short              show_trace; // while debugging, set this value to 1 and ...
    //                               // you will see .. heaven

    // Private Methods
    void  RunArrangement();
    void  RunOrientation();
    void  ComputeCurvesOrientation(short *& oOrientations);
    void  GetIndices(CATMathPoint  iMPoints [4],
                     CATCrvParam   iCrvParam[4],
                     CATCurve    * iCurves  [2],
                     int         & i,
                     int         & j);
    void  MakeChainFromScratch(double *&oGaps);
    double ComputeGap(CATCurve *iRefCurve, const CATCrvLimits &iRefLimit,
                      CATCurve *iTestedCurve, const CATCrvLimits &iTestedLimit,
                      int &ioRefOri,int &oTestedOri);
    void  RollCurves(double *iGaps);
    /*void  FindExtremity(CATLONG32 iNbCurves,
                        CATCurve **iCurves,CATCrvLimits *iLimits,
                        CATCurve *&oCurve,CATCrvLimits &oLimit);
    void  FindNeighbour(CATCurve *iCurve,CATCrvLimits iLim,
                        CATLISTP(CATCurve) iList,
                        CATLISTP(CATCrvLimits) iLimits,
                        CATLONG32 & oRank);
    short GetConnection(CATCurve *iCurve1,CATCrvLimits iLim1,
                        CATCurve *iCurve2,CATCrvLimits iLim2);
    void  CheckUVCloseness(CATCurve *iCurve1,CATCrvLimits iLim1,
                           CATCurve *iCurve2,CATCrvLimits iLim2,
                           int i,int j);*/ //Methode non utilisé.
};
#endif










