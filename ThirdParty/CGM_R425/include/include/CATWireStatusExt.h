#ifndef CATWireStatusExt_h
#define CATWireStatusExt_h

#include "ExportedByCATTopologicalObjects.h"
//#include "CATHybDef.h"
#include "CATTopDef.h"
#include "CATMathDef.h"
#include "CATCrvParam.h"
#include "CATDataType.h"
#include "CATMathPoint.h"
#include "CATMathBox.h"

class CATMathVector;
class CATWire;
class CATEdge;
class CATVertex;
class CATBody;

//-----------------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATWireStatusExt
{
  public :
    //-------------------------------------------------------------------------
    // Constrcutor/Destructor
    //-------------------------------------------------------------------------
    CATWireStatusExt(CATWire *iWire);
    ~CATWireStatusExt();     

    //-------------------------------------------------------------------------
    // Elements Access
    //-------------------------------------------------------------------------
    CATEdge * GetFirstEdge(CATOrientation *oOri=NULL);
    CATEdge * GetLastEdge(CATOrientation *oOri=NULL);

    CATVertex * GetFirstVertex();
    CATVertex * GetVertex(CATLONG32 iRank);
    CATVertex * GetLastVertex();

    //-------------------------------------------------------------------------
    // Coordinates Access
    //-------------------------------------------------------------------------
    CATMathPoint  GetFirstCoord();
    CATMathPoint  GetVertexCoord(CATLONG32 iRank);
    CATMathPoint  GetLastCoord();

    //-------------------------------------------------------------------------
    // Geometry Data Access
    //-------------------------------------------------------------------------
    CATCrvParam  GetFirstParamOnEdgeCurve();
    CATCrvParam  GetLastParamOnEdgeCurve();
    void  GetVertexParamOnEdgeCurve(CATLONG32 iRank,CATCrvParam * oParam);

    CATMathVector  GetFirstTangent();
    CATMathVector  GetLastTangent();
    void  GetTangent(CATLONG32 iRank,CATMathVector * oVector);

    CATPositiveLength GetLength();
//    CATWire * DoInvert(CATBody *iTargetBody);
    CATMathBox GetBoundingBox(CATLONG32 iRank);
    CATMathBox GetBoundingBox();
    double GetMaxDimension();// max(Xmax-Xmin, Ymax-Ymin, Zmax-Zmin)

  
  private:

    short IsBodyValid(CATBody *iBody);

    // Private Data
    CATWire   *_Wire;
    CATLONG32       _NbEdge;

};
#endif










