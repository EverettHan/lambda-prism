// COPYRIGHT DASSAULT SYSTEMES 2018
//=============================================================================
//
// CATGeoOctreeSolver:
// Given a body  find a multi grid with the rules
// A voxel is subdivided if the sphere (2D: circle) around the voxel contains any of the input geometry.
// A voxel is not subdivided below a predefined depth.
// For each voxel of the maximal depth: Define the 13 (2D: 4) line segments through the centre that are parallel or diagonal relative
// to the coordinate system. Find all intersections between these line segments and the input geometry.
//

//=============================================================================
//   /09/18 SMT1 Creation
// 12/03/20 Q48  Small file tidy for math versioning
//=============================================================================
#ifndef CATGeoOctreeSolver_H
#define CATGeoOctreeSolver_H

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

// Basic data
#include "CATBoolean.h"
#include "CATDataType.h"

// GM ModelInterfaces
class CATPGMGeoFace;

// Mathematics
#include "CATMath.h"
#include "CATMathPoint.h"
#include "CATMathDirection.h"
class CATTolerance;
class CATSoftwareConfiguration;

// Advanced Mathematics
class CATMathCombinationXY;
class CATMathSystemXYc;
class CATMathSetOfPointsND;

// Geometric Objects
#include "CATListOfCATSurfaces.h"
#include "CATListOfCATSurLimits.h"
#include "CATListValCATSurParam.h"
#include "ListPOfCATBody.h"
class CATFace;
class CATPlane;
class CATCartesianPoint;

// Geometric Operators
//#include "CATPositionPtLoop.h"

// Debug
#include "CATGeoOpDebug.h"

class CATGeoFace;
class CATLISTP(CATVoxel);
class CATVoxel;

class ExportedByY30C3XGG CATGeoOctreeSolver : public CATGeoOperator
{
    CATCGMVirtualDeclareClass(CATGeoOctreeSolver); 
public:


  CATGeoOctreeSolver (CATGeoFactory            * Factory,
                      CATSoftwareConfiguration * iConfig,
                      CATBody                  * iBody,
                      CATLONG32                  iMaxLevel);

  CATGeoOctreeSolver (      CATGeoFactory            * Factory,
                            CATSoftwareConfiguration * iConfig,
                      const CATLISTP(CATBody)        & iBodies,
                            CATLONG32                  iMaxLevel);


  ~CATGeoOctreeSolver ();

  /** @nodoc @nocgmitf */
  virtual int RunOperator();

  /** @nodoc @nocgmitf */
  const CATMathSetOfPointsND * GetIntPoints();

  /** @nodoc @nocgmitf */
  void ReadOption(CATCGMStream & Str, const short VersionOfStream);

  virtual CATLONG32 CreateGeoFaces(CATPGMGeoFace **&ioGeoFaces);

private:

    void FindAllLines(CATLONG32 iId);
    void ComputeClosestLine(CATLONG32 i,const CATMathPoint &iPoint, CATMathPoint &ioOrigin);
    void ComputeClosestLineIndex(CATLONG32 i,const CATMathPoint &iPoint, CATLONG32 &iInd0, CATLONG32 &iInd1);
    void ComputeLineFromIndex(CATLONG32 i,CATLONG32 iInd0, CATLONG32 iInd1, CATMathPoint &ioOrigin);
    void FindCubesAndIntersection(CATGeoFace *iGeoFace);
    void AddPointToCube(CATGeoFace *iGeoFace, CATLONG32 iId, const CATMathPoint &iPoint, const CATSurParam& isp);

    GEOPDEBUG_CMD(void Debug_PrintSolution(const CATLISTP(CATVoxel)& VoxelList) const);

    //CATGeoFactory            * _Factory;
    CATSoftwareConfiguration *_Config;
    //CATBody  * _Body;
    CATLISTP(CATBody)   _Bodies;
    CATLONG32 _MaxLevel;
    CATPlane * _RefPlane;
    CATLISTP(CATICGMObject) _VisualizeGrid;

    int _NbBodies, _NbOfCells;
    double _FullSize, _SmallCubeSize, _InvSmallCubeSize;
    CATFace ** _Faces;
    CATGeoFace ** _GeoFaces;

    const CATMathBox** _Boxes;
    CATMathBox _FullBox;
    CATVoxel * _StartVoxel;

    CATMathSetOfPointsND *_IntPoints;

    CATLONG32 _NbSmallCubes;
    CATVoxel ** _LocalGrid;
    CATLONG32 _LocalSize[3];

    CATLONG32 _LineMin[2];
    CATLONG32 _LineMax[2];

    double _GlobalMin[3], _GlobalMax[3];
    double _LocalMin[3], _LocalMax[3];

    CATMathPoint _RefOrigin;

    CATMathCombinationXY * _f[2];
    CATMathSystemXYc * _sysXY;

    static CATMathDirection _LightLine[13];
    static CATMathDirection _Axis1[13];
    static CATMathDirection _Axis2[13];
    

    CATLONG32 _Version; 

public:
  static CATString _OperatorId;
  /** @nodoc @nocgmitf */
  const CATString * GetOperatorId(); 
  /** @nodoc @nocgmitf */
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  virtual void WriteInput(CATCGMStream  & os);
  /** @nodoc @nocgmitf */
  virtual void WriteOutput(CATCGMStream & os);
  /** @nodoc @nocgmitf */
  virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual void Dump( CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  virtual void DumpOutput(CATCGMOutput & os);
  /** @nodoc @nocgmitf */
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);

private:

    CATCartesianPoint ** _DisplayPoints;

    const CATTolerance & _TolObject;

};

CATGeoOctreeSolver *CreateGeoOctreeSolver(CATGeoFactory * Factory,      
                                             CATSoftwareConfiguration * iConfig,
                                             CATBody                  * iBody );

// @nocgmitf
ExportedByY30C3XGG void Remove (CATGeoOctreeSolver* & iSolver);

#endif



