
//===============================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved 
//===============================================================================
//
//
// CATSmoLevelNEvaluator.h
//
//===================================================================================
//
// Usage notes: Eval sur une surface de subdivision a un level N
//
//===================================================================================
// 28/04/2009 RBD : Creation de CATSmoLevelNEvaluator
//===============================================================================
#ifndef CATSmoLevelNEvaluator_H
#define CATSmoLevelNEvaluator_H

//Pour l'export
#include "CATSmoOperators.h"

#include "CATSmoEvalCommand.h"
#include "CATSmoEvalResult.h"
#include "CATSmoEvalLocation.h"

#include "CATSobDiag.h"

#include "CATMathPoint.h"
class CATSobFace;
class CATMathVector;

class ExportedByCATSmoOperators CATSmoLevelNEvaluator
{
public:

  // A SUPPRIMER
//  CATSmoLevelNEvaluator( const CATSmoEvalCommand &iCommand);

  //Destructeur
  virtual ~CATSmoLevelNEvaluator();

  //Obtention du diag
  virtual CATSobDiag GetDiag() const = 0;

  // Eval
  //  Input : - iListOfEdges : A pointer of a list of pointers of edges.
  //  Output: - oNbEdges     : the number of DIFFERENT edges in the input list
  //  Return : void 
  // 
  virtual CATSobDiag Eval(const CATSmoEvalLocation & iLocation, CATSmoEvalResult & oEval) = 0; //This can be used several time

  // Set Command
  //  Input : - iListOfEdges : A pointer of a list of pointers of edges.
  //  Output: - oNbEdges     : the number of DIFFERENT edges in the input list
  //  Return : void 
  // 
  virtual void SetCommand(const CATSmoEvalCommand &iCommand) = 0;

 ///
 // Gets all the points of the face at the given level.
 // The points are arranged the following way:
 //
 //          4             The edges are indexes in the face by 1, 2, 3, 4.
 //     <-----------       The points are given from left to right and from up to down
 //   |  ......... /|\
 //   |  .........  |
 // 1 |  .........  | 3
 //   |  .........  |
 //  \|/ .........  |
 //     ----------->
 //          2
 //
 // @return
 // The array of CATMathPoint containing all the points of the
 // face at the given level.
 // If the array has been allocated by the user, it returns this array.
 ///
  virtual int PointsOfFace(CATSobFace*   iFace,
                           CATMathPoint* ioPointsOfFace,
                           const int     iNbPoints,
                           const int     iLevel,
                           const int     iIndexOfDaughterFace = 0) = 0;

 ///
 // Retreives all the points and the corresponding normals for a face,
 // at a given subdivision level.
 // The array of points and normals must be allocated by the user:
 // - If the face is quadrangular, their size is (2^Level+1) * (2^Level+1).
 // - If the face is not quad, their size is (2^(Level-1)+1) * (2^(Level-1)+1).
 //
 // WARNING: If the face is not quad, the level must be at least 1
 //
 // The points are arranged the following way:
 //
 //          4             The edges are indexes in the face by 1, 2, 3, 4.
 //     <-----------       The points are given from left to right and from up to down
 //   |  ......... /|\
 //   |  .........  |
 // 1 |  .........  | 3
 //   |  .........  |
 //  \|/ .........  |
 //     ----------->
 //          2
 //
 // @param iFace
 // The face
 // @param ioPointsOfFace
 // A pointer to the array of points of the face, allocated by the user
 // @param ioNormals
 // A pointer to the array of normalized normals associated with the points,
 // allocated by the user
 // @param iNbPoints
 // The number of points in the face, this value is checked to verify
 // the user has given the good size for the array
 // @param iLevel
 // The subdivision level for which the normals are to be computed,
 // iLevel must be >= 1
 // @param iIndexOfDaughterFace
 // If the face is triangular, the index of the quad face contained in this
 // triangular face must be given with: 1 <= iIndexOfDaughterFace <= 3 (see CATSobFace.h)
 // If the face is quad, iIndexOfDaughterFace must be 0 (default value)
 //
 // @return
 // 0 if no problems occured, else 1
 ///
  virtual int PointsAndNormalsOfFace(CATSobFace*    iFace,
                                     CATMathPoint*  ioPointsOfFace,
                                     CATMathVector* ioNormals,
                                     int            iNbPoints,
                                     const int      iLevel,
                                     const int      iIndexOfDaughterFace=0) = 0;



protected:

  //Constructeur (NE PAS UTILISER). Utilisez la methode de creation ci dessous.
  CATSmoLevelNEvaluator();

};

//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoLevelNEvaluator* CATSmoCreateLevelNEvaluator(const CATSmoEvalCommand &iCommand);

#endif



