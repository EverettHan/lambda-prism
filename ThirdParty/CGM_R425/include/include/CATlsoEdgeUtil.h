#ifndef CATlsoEdgeUtil_H
#define CATlsoEdgeUtil_H

// ++++ Includes ++++
#include "PersistentCell.h"
#include "CATBoolean.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATFace.h"
#include "ListPOfListPOfCATEdge.h"
#include "CATSysErrorDef.h"
#include "CATMathConstant.h"
#include "CATEdgeHashTable.h"

// ++++ Predeclarations ++++
class CATGeoFactory;
class CATCGMStream;
class CATFace;
class CATSurface;
class CATMathTransformation;
class CATSurLimits;
class CATMathVector;
class CATSoftwareConfiguration;
class CATEdge;
class CATlsoContext;
class CATCircle;
class CATLine;
class CATEllipse;
class CATBody;
class CATMathPoint;
class CATVertex;
class CATWire;

//=============================================================================
// CATlsoEdgeUtil
// 
// responsable: VB7
// 
// Classe utilitaire pour l'object Body. Elle ne contient que des methodes
// statiques pour le stream de body.
//=============================================================================

class ExportedByPersistentCell CATlsoEdgeUtil
{
public:
  //---------------------------------------------------------------------------
  // METHODES STATIC
  //---------------------------------------------------------------------------

  static CATBoolean AreConfused2Edges(CATEdge * iEdge1,
                                      CATEdge * iEdge2, 
                                      CATlsoContext * iContext);

  static CATBoolean SameCircle(CATCircle * iFirstCircle, CATCircle * iSecondCircle, CATMathTransformation & iMathTransfo, CATGeoFactory * iFactory);
  static CATBoolean SameLine(CATLine * iFirstLine, CATLine * iSecondLine, CATMathTransformation & iMathTransfo, CATGeoFactory * iFactory);
  static CATBoolean SameEllipse(CATEllipse * iFirstEllipse, CATEllipse * iSecondEllipse, CATMathTransformation & iMathTransfo, CATGeoFactory * iFactory);

  static HRESULT    IsCircular(CATEdge *iEdge, CATSoftwareConfiguration *iConfig, CATMathPoint &oOrigin, CATMathVector &oNormal, double &oRadius);

  // GlobalThicknessAnalyzer
  // ------------------------------------------------------------------------------------------------------  
  static double     DistanceBetweenExtremities(CATEdge *iEdge);
  static CATBoolean IsStraightEdge (CATEdge *iEdge, CATSoftwareConfiguration *iConfig); 

  //-------------------------------------------------------------------------------------------------------
  // ListPOfCATEdge
  //-------------------------------------------------------------------------------------------------------
  // Stream(List)
  static void StreamEdgeList(const ListPOfCATEdge & iEdgeList, CATCGMStream& ioStr);
  static void StreamEdge(const CATEdge * iEdge, CATCGMStream& ioStr);
  static void StreamListOfEdgeList(const ListPOfListPOfCATEdge & iEdgeListOfList, CATCGMStream& ioStr);
  static void PutColorOnEdgeList(const ListPOfCATEdge & iEdgeList, int red, int green, int blue);
  static void PutColorOnEdgeHT(const CATEdgeHashTable & iEdgeHT, int red, int green, int blue);

  // UnStream(List)
  static void UnStreamEdgeList(ListPOfCATEdge & oEdgeList, CATCGMStream& ioStr, CATGeoFactory * iFactory, CATBoolean iPutColor=FALSE);
  static CATEdge * UnStreamEdge(CATCGMStream& ioStr, CATGeoFactory * iFactory);
  static void UnStreamListOfEdgeList(ListPOfListPOfCATEdge &oListOfEdgeList, CATCGMStream& ioStr, CATGeoFactory * iFactory);

  //Creation
  static CATEdge * CreateEdgeFromMathPoints(CATMathPoint & iStartMathPoint, CATMathPoint & iEndMathPoint, CATBody & iBody, CATGeoFactory & iFactory);

  static int IsContinuous (CATVertex * iVertex, CATEdge * iFirstEdge, CATEdge * iSecondEdge, CATGeoFactory * iFactory); // 0 : no, 1 : C1, 2 : C2

  // UTILITIES
  //==============================================================================
  static CATAngle   ComputeRadianAngleEdge(CATEdge *iWorkingEdge, CATBody *iInputBody, CATSoftwareConfiguration *iConfig, CATFace *iAdjacentFace = NULL);
  static CATBoolean Is90DegreesEdge(CATEdge *iWorkingEdge, CATBody *iInputBody, CATSoftwareConfiguration *iConfig, CATFace *iAdjacentFace = NULL, double iTolAngle = -1.);
  static CATBoolean Is90DegreesEdgeOnVertex(CATEdge *iWorkingEdge, CATBody *iInputBody, CATSoftwareConfiguration *iConfig, CATVertex *ipVertex, double iTolAngle = -1);
  static void GetAdjacentEdgesOnFace(CATEdge &iEdge, CATFace &iFace, CATSoftwareConfiguration *iConfig, CATBody &iBody, ListPOfCATEdge &oAdjacentEdges);

  //-------------------------------------------------------------------------------------------------------
  // DEBUG
  //-------------------------------------------------------------------------------------------------------
  static int ComputeMiddlePoint(CATEdge *ipEdge, CATMathPoint &oMiddleMathPoint);
  
  //Edge visu in NCGM
  //-----------------------------
  //A. Thickness
  // 1 <= iThickness <= 8 otherwise throw
  // 1=0.13f
  // 2=0.35f;
  // 3=0.70f;
  // 4=1.00f;
  // 5=1.40f;
  // 6=2.00f;
  // 7=2.30f;
  // 8=2.60f;
  //-----------------------------
  //B. Type
  // 1 :  solid</li>
  // 2 :  dotted</li>
  // 3 :  dashed</li>
  // 4 :  dot-dashed</li>
  // 5 :  phantom</li>
  static void SetEdgeListThickness(ListPOfCATEdge & iEdgeList, unsigned int iThickness, unsigned int iLineType = 1);
  static void SetEdgeHTThickness(CATEdgeHashTable & iEdgeHT, unsigned int iThickness, unsigned int iLineType = 1);
  static void SetEdgeThickness(CATEdge * iEdge, unsigned int iThickness, unsigned int iLineType = 1);
  static void ReleaseCATlsoEdgeRepAttribute (CATEdge * iEdge);

  static CATWire * GetWireFromEdgeInALineicBody(CATBody & iLineicBody, CATEdge & iEdge);
};

#endif /* CATlsoEdgeUtil_H */
