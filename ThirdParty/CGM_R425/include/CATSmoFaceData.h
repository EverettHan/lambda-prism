//=========================================================================================
// Copyright Dassault Systemes Provence 2003, all rights reserved 
//=========================================================================================
//
// CATSobFaceData.h
//
//=========================================================================================
//
// Usage notes:
//
//=========================================================================================
// September, 2005 : RAQ : Migration totale sur structure multires + Nettoyage code
// February,  2004 : RAQ : _TabOfPoints peut être alloué par le user
// January,   2004 : RAQ : Changement d'architecture des subdivisions
// October,	  2003 : RAQ : Rajout du niveau de subdivision pour la recherche
// September, 2003 : JCV : Gestion erreur (run rend int)
// Marsh,     2003 : JCV : Creation CATSobFaceData
///========================================================================================
#ifndef CATSmoFaceData_H
#define CATSmoFaceData_H

#include "CATSobDefine.h"
#include "CATSmoOperators.h"
#include "CATBoolean.h"

class CATSobMesh;
class CATSobFace;
class CATMathPoint;
class CATMathSetOfPoints;

class ExportedByCATSmoOperators CATSmoFaceData
{
public:

/**
 * Build a CATSmoFaceData object,
 * the array of CATMathPoint returned by GetTabPoints is allocated by the user
 * and will have to be deleted by the user.
 *
 * @param iFace
 * The face to get the points from.
 *
 * @param ioTabOfPoints
 * The array of CATMathPoint (created by the user) that will contain all
 * the coordinates after running the operator.
 * The size of this array is given by the following rule:
 * Size := (2^Level+1) * (2^Level+1)
 *
 * @param iSizeOfTab
 * The size of the array given the user: ioTabOfPoints.
 * This param only verifies that the array has the good size.
 *
 * @param iLevel
 * The level for which the points have to be computed
 *
 * @param iIndexOfDaughterFace
 * If the face is triangular, the index of the quad face contained in this
 * triangular face must be given with: 1 <= iIndexOfDaughterFace <= 3 (see picture in CATSobFace.h)
 * If the face is quad, iIndexOfDaughterFace must be 0 (default value)
 **/
  CATSmoFaceData(CATSobFace*   iFace,
                 CATMathPoint* ioTabOfPoints,
                 const int     iSizeOfTab,
                 const int     iLevel,
                 const int     iIndexOfDaughterFace = 0);

/**
 * @nodoc
 **/
  ~CATSmoFaceData();

/**
 * ******** DEPRECATED: Now MultiresMode is default mode *********
 * Run the operator with multires data structure.
 * This method must be called just after the constructor.
 **/
  void SetMultiresMode();
  
/**
 * Run operator.
 *
 * @return
 * 1 if an error occured, 0 else.
 **/
	int InitRun();

/**
 * Run operator.
 *
 * @return
 * 1 if an error occured, 0 else.
 **/
	int Run();

/**
 * Gets all the points of the face at the given level.
 * The points are arranged the following way:
 *
 *          4             The edges are indexes in the face by 1, 2, 3, 4.
 *     <-----------       The points are given from left to right and from up to down
 *   |  ......... /|\
 *   |  .........  |
 * 1 |  .........  | 3
 *   |  .........  |
 *  \|/ .........  |
 *     ----------->
 *          2
 *
 * @return
 * The array of CATMathPoint containing all the points of the
 * face at the given level.
 * If the array has been allocated by the user, it returns this array.
 **/
	CATMathPoint* GetTabPoints() const;

/**
 * Gets the number of points for this face at the given level.
 *
 * @return
 * The number of points.
 */
  int GetNbPoints() const;

/**
 * Get a row of points in an adjacent face
 *
 *                     -------------------
 *                     |                 |         The points are organized respect to
 *                     |                 |         the orientation of edge seen in the adjancent face
 *                     |                 |
 *                     |  CATSobSide_UP  |
 *                     |                 |
 *                     ...................
 *   -----------------.-------------------.------------------
 *  |                 .|     4 <---      |.                  |
 *  |                 .| |            /|\|.                  |
 *  |                 .| | 1  iFace  3 | |.                  |
 *  | CATSobSide_LEFT .|\|/            | |. CATSobSide_RIGHT |
 *  |                 .|                 |.                  |
 *  |                 .|     2 --->      |.                  |
 *   -----------------.-------------------.------------------
 *                     ...................
 *                     |                 |
 *                     | CATSobSide_DOWN |
 *                     |                 |
 *                     |                 |
 *                     |                 |
 *                     -------------------
 *
 * @param iIndexOfEdge
 * The edge common to the current face and the adjancent face
 * @param iSetOfPoints
 * A set of points which size is the number of vertices in the row
 * @param iIndexOfDaughterFace
 * If the face is triangular, the index of the quad face contained in this
 * triangular face must be given with: 1 <= iIndexOfDaughterFace <= 3 (see picture in CATSobFace.h)
 * If the face is quad, iIndexOfDaughterFace must be 0 (default value)
 *
 * @return
 * 0 if no problems occured, 1 else
 **/
  int GetNeighbourLineInMultiresMode(const int iIndexOfEdge, CATMathSetOfPoints* iSetOfPoints, const int iIndexOfDaughterFace = 0);


/**
 * Get all points in a face around a corner vertex of the face.
 *
 * @param iFace
 * A face
 * @param ison
 * A corner id
 * @param iSubLevel
 * The level in which the points are to be retrieved
 * @param oPoints
 * An array of CATMathPoint, created by the user
 * @param iIndexOfDaughterFace
 * If the face is triangular, the index of the quad face contained in this
 * triangular face must be given with: 1 <= iIndexOfDaughterFace <= 3 (see picture above)
 * If the face is quad, iIndexOfDaughterFace must be 0 (default value)
 *
 * @return
 * 0 if no problem occured, else 1
 **/
  int GetPointsAroundVertex(CATSobFace*   iFace,
                           CATSobSonFace ison,
                           const int     iSubLevel,
                           CATMathPoint* oPoints,
                           const int     iIndexOfDaughterFace = 0);


private:

  int GetFacePointInMultiresMode();

  int GetNeighbourFace(CATSobFace* iFace, const int iDaughterFaceIndex, const int iEdgeIndex,
                       CATSobFace*& oSideFace, int& iSideDaughterFace, int& iSideEdgeIndex);


  int UtilitaireForGetNeighbourLine(const int           iIndexOfEdge,
                                    CATMathSetOfPoints* ioSetOfPoints,
                                    const int           iIndexOfDaughterFace,
                                    CATSobFace        * iSideFace,
                                    int                 iSideEdgeIndex) ;

  //Data
	CATSobFace* _Face;
  short _IndexOfDaughterFace;
	int _Level;
	int _Size;                             //Nbre de points par rangées
	CATMathPoint* _TabPoints;
  CATBoolean _AlreadyRun;                //TRUE si le run a déjà été fait
};


#endif

