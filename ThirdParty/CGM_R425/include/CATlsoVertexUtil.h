#ifndef CATlsoVertexUtil_H
#define CATlsoVertexUtil_H

// ++++ Includes ++++
#include "PersistentCell.h"
#include "CATBoolean.h"
#include "ListPOfCATVertex.h"
#include "ListPOfCATCell.h"

// ++++ Predeclarations ++++
class CATGeoFactory;
class CATCGMStream;
class CATFace;
class CATSurface;
class CATMathTransformation;
class CATSurLimits;
class CATMathVector;
class CATSoftwareConfiguration;
class CATVertex;
class CATlsoContext;
class CATMathPoint;
class CATVertexHashTable;

//=============================================================================
// CATlsoVertexUtil
// 
// responsable: QF2
// 
// Classe utilitaire pour l'object Body. Elle ne contient que des methodes
// statiques pour le steram de body.
//=============================================================================

class ExportedByPersistentCell CATlsoVertexUtil
{
public:
  //---------------------------------------------------------------------------
  // METHODES STATIC
  //---------------------------------------------------------------------------
  static CATMathPoint GetMathPoint(CATVertex * iVertex);

  static CATBoolean AreConfused2Vertices( CATVertex     * iVertex1,
                                          CATVertex     * iVertex2, 
                                          CATlsoContext * iContext);

  static CATBoolean AreConfused2Vertices( CATVertex     * iVertex1,
                                          CATVertex     * iVertex2, 
                                          double          iTolerance);

  static CATVertex * FindConfusedVertexInHT(CATVertex *iVtxToFind, const CATVertexHashTable &iVtxHTToSearch, double &iTolerance);

  static void ComputeMiddleMathPoint(CATVertex * iVertexA, CATVertex * iVertexB, CATMathPoint &oMiddlePoint);

  static double DistanceBetweenVertices(CATVertex * iVertexA, CATVertex * iVertexB);


  static void KeepOnlyTheClosestVertexInList(CATVertex * iVertexA, ListPOfCATVertex & ioVertexBList);

  static CATVertex * GetTheClosestVertexFromList(CATVertex * iVertexA, const ListPOfCATVertex & iVertexBList);

  static void DeleteConfusedVertices(ListPOfCATCell & ioRefCellList, ListPOfCATCell & iSecondCellList, CATGeoFactory & iFactory);

  static void SetVertexSymbol(CATVertex * iVertex, unsigned int iSymbol);

  static void SetVertexVisibility(CATVertex * iVertex, unsigned int iVisible);//1 : Show : 0 : Hide

  //-------------------------------------------------------------------------------------------------------
  // ListPOfCATVertex
  //-------------------------------------------------------------------------------------------------------
  // Stream(List)
  static void StreamVertexList(const ListPOfCATVertex & iVertexList, CATCGMStream& ioStr);
  static void StreamVertex(const CATVertex * iVertex, CATCGMStream& ioStr);
  static void PutColorOnVertexList(const ListPOfCATVertex & iVertexList, int red, int green, int blue);

  // UnStream(List)
  static void UnStreamVertexList(ListPOfCATVertex & oVertexList, CATCGMStream& ioStr, CATGeoFactory * iFactory);
  static CATVertex * UnStreamVertex(CATCGMStream& ioStr, CATGeoFactory * iFactory);

  //Symbol
  static void SetVertexListSymbol(ListPOfCATVertex & iVertexList, unsigned int iSymbol);

};

#endif /* CATlsoVertexUtil_H */
