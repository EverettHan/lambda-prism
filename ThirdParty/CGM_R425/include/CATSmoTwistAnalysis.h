
//=================================================================================
// Copyright Dassault Systemes Provence 2007, All Rights Reserved 
//=================================================================================
//=============================================================================
//
// CATSmoTwistAnalysis:
// Locate twists on a surface
//
//=============================================================================
// Usage notes:
// 1) Detection des Tips ie ||fu^fv||<=ObjectTol.EpsgForRelativeTest() sur le milieu du bord de chaque face
// 2) Option Detection des Twist ie Courbure>=CurvatureThreshold
// 3) Calcul du MaxOffset
// 
// Les 3 operations sont effectues en une seule fois et le cout CPU est a peu pres le meme quelque soit les options
// Ce cout depend essentiellement de la resolution de discretization choisie via les level
//
//=============================================================================
// 03/2009 : RBD : Modifs suite refonte CATSmoMultiEvaluator qui est maintenant une interface
// 09/2007 : RNO : Creation en s'inspirant de CATTwistAnalysis & CATMaxOffset                       
//=============================================================================

#ifndef CATSmoTwistAnalysis_H
#define CATSmoTwistAnalysis_H 

// Pour l'export
#include "CATSmoOperators.h"

// Objets CGM
#include "CATTolerance.h"
#include "CATMathBox.h"
#include "CATBoolean.h"

// Objets Subdivisions
#include "CATSobListOfFace.h"
#include "CATSobFace.h"
#include "CATSmoListOfLocation.h"
#include "CATSmoEvalCommand.h"
#include "CATSmoMultiEvaluator.h"
#include "CATSobDiag.h"

class CATSobMesh;
class CATSobEdge;

typedef  enum    
{  
  CATSmoMXOFF_NOTSET=0,  
  CATSmoMXOFF_SINGULAR=1,  
  CATSmoMXOFF_FINITE=2,  
  CATSmoMXOFF_INFINITE=3  
}  CATSmoThresholdType;  


typedef  enum  
{  
  CATSmoMXOFF_NEG=-1,  
  CATSmoMXOFF_POS=1,  
  CATSmoMXOFF_BOTH=0,  
}  CATSmoMaxOffsetType;  


class ExportedByCATSmoOperators CATSmoTwistAnalysis
{
public :
  //Advice Level=4 is nice
  CATSmoTwistAnalysis(const CATTolerance & iObjectTol, CATSobMesh* iMesh, int iLevel);
  virtual ~CATSmoTwistAnalysis();
  
  //Allow a specific discretization level for the edges..
  // Default : same as face's inner points
  // Advice Level=6 is nice
  // WARNING NOT COMPATIBLE WITH SetProceedOnlyThoseFaces
  void SetDiscretizationLevelForEdges(int iLevel);

  //Restrict the Analysis to a SubSet of the SobMesh (by default all the Mesh's faces are Analysed)  
  // WARNING NOT COMPATIBLE WITH SetDiscretizationLevelForEdges
  void SetProceedOnlyThoseFaces(CATLISTP(CATSobFace) * FacesToCheck);

  //Curvature over iCurvatureThreshold are added to the Twist (and Shout) List
  void SetCurvatureThreshold(double iCurvatureThreshold = 1.e3);
  
  //Curvature over (iCurvatureThreshold / diagonal distance of the Limit surface )are added to the Twist (and Shout) List
  // The Box of the Limit Surface is computed using a set of point corresponding to iLevelBox
  void SetAutoCurvatureThreshold(double iCurvatureThreshold = 1.e3, const int iLevelBox=2);
  

  /**
   * In SetCurvatureThreshold mode, specifies that the caller wants to know
   * the maximal curvature computed at potentially twisted points (see usage notes
   * above).
   */
  void SetRecordMaxCurvature ();

  CATSobDiag Run();

  CATBoolean IsTwisted();

  /**
   * Returns 0 if not relevant, 1 otherwise.
   * The result is relevant only if the following conditions are fulfilled :
   *  - CurvatureThreshold and RecordMaxCurvature modes have been set up
   *  - IsTwisted has returned FALSE
   *  - Sufficient CGMLevel ( >= 96 )
   * In this case, retrives the maximal curvature computed. This is a
   * positive value not greater than the specified threshold.
   */
  CATSmoEvalLocation GetMaxCurvature (double & MaxCurvature);
  
  void GetTwistedFaces(CATLISTP(CATSobFace)& oTwistedFace);
  void GetTwistLocations(CATLISTV(CATSmoEvalLocation) & oTwistLocation);
  void GetTipsLocations(CATLISTV(CATSmoEvalLocation) & oTipsLocation);
  
///Methodes Orientees MaxOffset
  
  // To Enable MaxOffset Computation either use SetOffsetType or SetCurvatureThreshold or SetCurvatureThreshold
  
  
  // use this to set the RunOption (i.e. look for positive/negative/both/ maxoffsets)
  //- the default RunOption is CATSmoMXOFF_BOTH so you need this
  // method only if you want to switch to CATSmoMXOFF_NEG or CATSmoMXOFF_POS
  void SetOffsetType(const CATSmoMaxOffsetType iType);
  
  // Check whether an offset is allowable.
  // NOTE: the values for singularity are a closed set.  Thus the
  //   threshold values cannot be used for offsets; the size of an
  //   offset must fall between the negative and positive thresholds.
  CATBoolean CheckOffset(double &i_Offset) const;
  
    /////////////////////////////////////////////////
  // ..for flags and thresholds :
  //
  //  The following get methods indicate the CATThresholdType found by the operator.
  //  According to the offset direction required (positive or negative), it could take the following values:
  //
  //  Specific cases:
  //    CATMXOFF_NOTSET   : no computation has been performed (Run has not been called, or the associated RunOption has not been asked).
  //    CATMXOFF_SINGULAR : the input surface has already reached its offsetability threshold (ie. offset radius = 0.).
  //    CATMXOFF_INFINITE : the input surface has no offset threshold (ex. like a plane, or a sphere for its centrifugal direction).
  //
  //  Regular case:
  //    CATMXOFF_FINITE   : the input surface is offsetable until a given limit gaved by the GetPositiveThreshold / GetNegativeThreshold according to case.
  CATSmoThresholdType GetPositiveFlag() const;
  CATSmoThresholdType GetNegativeFlag() const;

  //  The following get methods provide the offset threshold computed by the operator, according to the offset direction required.
  double GetPositiveThreshold() const;
  double GetNegativeThreshold() const;
  /////////////////////////////////////////////////


  // --- A Little Utilities that can be used externally
  //Return the MathBox of the i-th face (1<=i<=N) in the specified list of Faces
  CATMathBox GetBox(int iIndex);

private :
  CATSobDiag RunForInnerPoints(double ioMinMax[2]);
  CATSobDiag RunForEdgesPoints(double ioMinMax[2]);
  CATBoolean EdgeCheckerHelper(CATSobFace *  Face,CATSmoEvalLocation & WhereToEval, 
                               double ioMinMax[2],int EndSub,int Sub[2], int Lockers[2], int Cste[2], int UVMax, int TipsedEdge=0);
  CATSobDiag CheckForFoldedFaces();
  int CheckTipsedEdge(CATSobEdge * OneEdge);
  CATMathBox * _BoxManager;
  

  CATSobMesh*            _Mesh;
  int                    _Level;
  int                    _LevelForBox;
  int                    _DiscLevelForEdge;
  const CATTolerance &   _ObjectTol;
  double                 _CurvatureThreshold,
                         _AutoCurvatureThreshold;
  CATLISTP(CATSobFace) * _FacesToCheck;
  int                    _NbFaces;
  CATLISTV(CATSmoEvalLocation) _TipsLocation;
  CATLISTV(CATSmoEvalLocation) _TwistLocation;
  CATLISTP(CATSobFace)  _FacesWithTipsOrTwist;
 
  double     _MaxCurvature;
  CATSmoEvalLocation _MaxCurvatureLocation;
  CATSmoEvalLocation _MinCurvatureLocation;
  double _Res, _Res2;

  CATSmoEvalCommand _MyCommand;
  CATSmoMultiEvaluator* _Evaluator;
  CATULONG32 _NbSkippedEval;
  CATSobDiag _Diag;
  CATSobDiag SetDiag(const CATSobDiag & iDiag){_Diag=iDiag; return(_Diag);};
  CATSmoMaxOffsetType _RunOption;
  double _PositiveThreshold;
  double _NegativeThreshold;
  CATLISTV(CATSmoEvalLocation) _OverCurLocation;
  //   FINITE (use the threshold), INFINITE (any offset works),
  //   SINGULAR (no offset works)
  CATSmoThresholdType _PositiveTFlag;
  CATSmoThresholdType _NegativeTFlag;


  CATBoolean _UseCurvatureThreshold;
  CATBoolean _AdaptiveCurvatureTest;

  CATBoolean _RecordMaxCurvature;
  CATBoolean _AutoScaleCurvature;
  CATBoolean _MeshSubset;


};





#endif

