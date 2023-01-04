#ifndef CATNavigatorPseudoVertex_H
#define CATNavigatorPseudoVertex_H

#include "CATPersistentCell.h"
#include "CATCollecRoot.h"
#include "ListPOfCATCellManifold.h"
#include "CATMathPoint.h"

class CATCellManifold;
class CATLISTP(CATCell);

class ExportedByPersistentCell CATNavigatorPseudoVertex
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATNavigatorPseudoVertex(); 

  // Destructor
  ~CATNavigatorPseudoVertex();
  
  //Get methods
  void GetMathPoint(CATMathPoint &oPositionMathPoint);
  void GetCells(CATLISTP(CATCell) &oAdjacentCells) const;
  void GetCellManifolds(CATLISTP(CATCellManifold) &oAdjacentCellManifolds);
  CATGeometry* GetId();

  // Set methods
//protected:
  void SetMathPoint(CATMathPoint &iPositionMathPoint);
  void SetCells(CATLISTP(CATCell) &iAdjacentCells);
  void SetCellManifolds(CATLISTP(CATCellManifold) &iAdjacentCellManifolds);
  void SetId(CATGeometry* iIdentificationGeometry);

private:
  CATNavigatorPseudoVertex(const CATNavigatorPseudoVertex&);  
  CATNavigatorPseudoVertex& operator=(const CATNavigatorPseudoVertex&);  

protected:
  ListPOfCATCell _AdjacentCells;
  ListPOfCATCellManifold _AdjacentCellManifolds;
  CATMathPoint _PositionMathPoint;
  CATGeometry* _IdentificationGeometry;
};

#endif
