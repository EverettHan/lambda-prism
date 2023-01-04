#ifndef CATSpatialHashTable_h
#define CATSpatialHashTable_h

/**
* class CATSpatialHashTable
* ----------------------------------------------------------------------------------------------------
* Class representing a collection of couples (mathpoint, void *),
* with a fast access to elements spatially near a given location.
*
* !!! ******** IMPORTANT RULE ******** !!!
* NO #include MUST BE ADDED TO .h OR .cpp
* EXCEPT IF IT POINTS TO "Mathematics" OR "System" FRAMEWORKS.
* ----------------------------------------------------------------------------------------------------
* 2014 WEEK 47 * LD2 * Creation
*/

/** Mother class */
#include "CATSpatialHashTableBase.h"
#include "ExportedByCATTopologicalObjects.h"

/** Inclusions from "System" framework */
#include "CATListPV.h"

/** 
* DO NOT ADD ANY INLCUSION FROM A FRAMEWORK DIFFERENT THAN "Mathematics" OR "System".
* If you need something more specific, please add it to different .h/.cpp files.
*/

/** Forward declarations */
class CATMathPoint;

class ExportedByCATTopologicalObjects CATSpatialHashTable : public CATSpatialHashTableBase
{
public:

  /**
  * Constructor
  */
  CATSpatialHashTable();
  
  /**
  * Destructor
  */
  virtual ~CATSpatialHashTable();

  /**
  * Adds iMathPoint/iElem to the table.
  * This method throws an error if iMathPoint is outside the range defined in costructor.
  */
  void AddPoint(CATMathPoint & iMathPoint, void * iElem);

  /**
  * Returns the list of neighbours of iMathPoint.
  * This method throws an error if iMathPoint is outside the range defined in costructor.
  * If iStopAtFirst == TRUE, returns only the first neighbour found.
  */
  void RetrieveNeighbours(CATMathPoint & iMathPoint,
    CATListValCATMathPoint * oNeighbourPoints,
    CATListPV * oNeighbourElems,
    CATBoolean iStopAtFirst = FALSE);

  /**
  * Remove The point iElem from this SpatialHashtable
  */
  void RemovePoint(CATMathPoint & iMathPoint, void * iElem);

protected:

  /**
  * Virtual methods from mother class.
  */

  virtual void Construct(int iNbIntervalX, int iNbIntervalY, int iNbIntervalZ,
    double iMinX, double iMaxX,
    double iMinY, double iMaxY,
    double iMinZ, double iMaxZ);

private:

  /**
  * Internal methods.
  */

  void GetOrCreate(int iSlot, CATListValCATMathPoint *& oPoints, CATListPV *& oElements);
  void Get(int iSlot, CATListValCATMathPoint *& oPoints, CATListPV *& oElements);

  /**
  * Internal data
  */

  CATListPV _Points;
  CATListPV _Elements;
};

/**
* Macros SpatialTableNeighbourBegin/SpatialTableNeighbourEnd
* ----------------------------------------------------------------------------------------------------
* Example:
*
* SpatialTableNeighbourBegin (Table, MacroPoint, CurrentNeighbour, MyType)
* {
*   CurrentNeighbour->MyMethod();
* } SpatialTableNeighbourEnd;
*
*/

#define SpatialTableNeighbourBegin(TABLE, ELEMENT, NEIGHBOUR, TYPE) \
{ \
  CATListPV __##NEIGHBOUR##NeighbourElems; \
  (TABLE).RetrieveNeighbours(ELEMENT, NULL, &__##NEIGHBOUR##NeighbourElems, FALSE); \
  int __##NEIGHBOUR##Idx, __##NEIGHBOUR##Nb(__##NEIGHBOUR##NeighbourElems.Size()); \
  for (__##NEIGHBOUR##Idx = 1; __##NEIGHBOUR##Idx <= __##NEIGHBOUR##Nb; __##NEIGHBOUR##Idx++) \
  { \
    TYPE * NEIGHBOUR = (TYPE *)__##NEIGHBOUR##NeighbourElems[__##NEIGHBOUR##Idx]; \
    if (NEIGHBOUR) \
    {

#define SpatialTableNeighbourEnd \
    } \
  } \
}

/**
* Macros SpatialTableElementNeighbourBegin/SpatialTableElementNeighbourEnd
* ----------------------------------------------------------------------------------------------------
* Example:
*
* SpatialTableElementNeighbourBegin (Table, Object, CurrentNeighbour, ObjectInTable)
* {
*   ObjectInTable->ObjectInTableMethod();
* } SpatialTableElementNeighbourEnd;
*
* TO BE ABLE TO USE THIS MACROS FOR A GIVEN OBJECT TYPE,
* YOU HAVE TO DEFINE A MEHOD:
*
* void RetrieveMathPoint(ObjectType iObject, CATMathPoint & oMathPoint);
*
*/

#define SpatialTableElementNeighbourBegin(TABLE, ELEMENT, NEIGHBOUR, TYPE) \
{ \
  CATMathPoint __##NEIGHBOUR##InputPoint; \
  RetrieveMathPoint((ELEMENT), __##NEIGHBOUR##InputPoint); \
  SpatialTableNeighbourBegin(TABLE, __##NEIGHBOUR##InputPoint, NEIGHBOUR, TYPE) \
  {

#define SpatialTableElementNeighbourEnd \
  } SpatialTableNeighbourEnd; \
}

#endif
