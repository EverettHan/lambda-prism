#ifndef CATSpatialHashTableBase_h
#define CATSpatialHashTableBase_h

/**
* class CATSpatialHashTableBase
* ----------------------------------------------------------------------------------------------------
* Class representing a 3D grid that can be used for spatial hashing of points/vertices.
*
* !!! ******** IMPORTANT RULE ******** !!!
* NO #include MUST BE ADDED TO .h OR .cpp
* EXCEPT IF IT POINTS TO "Mathematics" OR "System" FRAMEWORKS.
* ----------------------------------------------------------------------------------------------------
* 2014 WEEK 06 * LD2 * Creation
* 2014 WEEK 47 * LD2 * Generalization
*/

/** Export dll */
#include "ExportedByCATTopologicalObjects.h"

/** Inclusions from "System" framework */
#include "CATBoolean.h"
#include "CATListOfInt.h"

/** Inclusions from "Mathematics" framework */
#include "CATMathInline.h"

/** Forward declarations */
class CATMathPoint;
class CATListValCATMathPoint;
class CATMathBox;

class ExportedByCATTopologicalObjects CATSpatialHashTableBase
{
public:

  /**
  * Creates the internal structure
  */
  void BuildGrid(CATMathBox & iBox, double iTolerance, int iEstimatedNbElements);

  /**
  * Creates the internal structure
  */
  void BuildGridBigEnough(CATListValCATMathPoint & iMathPoints, double iTolerance, int iEstimatedNbElements);

  /**
  * Destructor
  */
  virtual ~CATSpatialHashTableBase();

  /**
  * Static tool to compute the containing mathbox for a set of mathpoints
  */
  static void GetRange(CATListValCATMathPoint & iPoints, CATMathBox & oBox);

protected:

  /**
  * Protected constructors
  */

  CATSpatialHashTableBase();

  /**
  * Virtual methods to overload in children classes
  */

  virtual void Construct(int iNbIntervalX, int iNbIntervalY, int iNbIntervalZ,
    double iMinX, double iMaxX,
    double iMinY, double iMaxY,
    double iMinZ, double iMaxZ) = 0;

  /**
  * Static tools for internal use only
  */

  static void ComputeConstructionValues(CATMathBox & iBox, double iTolerance, int iEstimatedNbElements,
    int & oNbIntervalX, int & oNbIntervalY, int & oNbIntervalZ,
    double & oMinX, double & oMaxX,
    double & oMinY, double & oMaxY,
    double & oMinZ, double & oMaxZ);

  static void GetRange(CATListValCATMathPoint & iPoints,
    double & oMinX, double & oMaxX,
    double & oMinY, double & oMaxY,
    double & oMinZ, double & oMaxZ);

  static int ReportToRange(int iInput, int iMin, int iMax);

  /**
  * Protected methods used by children classes
  */

  int ComputeSlotFromPoint(CATMathPoint & iPoint);

  void RetrieveNeighbourSlots(CATMathPoint & iPoint, CATListOfInt & oNeighbourSlots);

  INLINE int GetNbSlots() {return _NbSlots;}

  INLINE double GetTolerance() {return _Tolerance;}

  INLINE double GetSquareTolerance() {return _SquareTolerance;}

private:

  /**
  * Forbidden copy constructor
  */

  CATSpatialHashTableBase(const CATSpatialHashTableBase & iOther);

  /**
  * Internal methods
  */

  void InitOptimizationValues();

  void ComputeCenterInterval(CATMathPoint & iPoint, int & oIntervalX, int & oIntervalY, int & oIntervalZ);

  void ComputeLeftInterval(CATMathPoint & iPoint, int & oIntervalX, int & oIntervalY, int & oIntervalZ);

  int ComputeSlotFromCoordinates(int iIntervalX, int iIntervalY, int iIntervalZ);

  /**
  * Internal data
  */

  double _Tolerance;
  double _SquareTolerance;

  double _MinX;
  double _MaxX;
  double _MinY;
  double _MaxY;
  double _MinZ;
  double _MaxZ;

  int _NbIntervalX;
  int _NbIntervalY;
  int _NbIntervalZ;
  int _NbIntervalYZ;

  int _NbSlots;

  double _1OverIntervalLengthX;
  double _1OverIntervalLengthY;
  double _1OverIntervalLengthZ;

  CATBoolean _GridHasBeenBuilt;
};

#endif

