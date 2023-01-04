#ifndef CATDynFilletVertexRibbonOrder_h_
#define CATDynFilletVertexRibbonOrder_h_

//-----------------------------------------------------------------------------
//
// CATDynFilletVertexRibbonOrder
// ------------------
// Definition of abstract class used for providing an edge order at a vertex
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// January   2011 JQS: Creation
//-----------------------------------------------------------------------------


#include "CATGMOperatorsInterfaces.h"
#include "CATCollec.h"

class CATCell;
class CATLISTP(CATCell);
class CATLISTP(ListPOfCATEdge);

class ExportedByCATGMOperatorsInterfaces CATDynFilletVertexRibbonOrder
{

public:
  CATDynFilletVertexRibbonOrder();
  virtual ~CATDynFilletVertexRibbonOrder();

};

ExportedByCATGMOperatorsInterfaces CATDynFilletVertexRibbonOrder* CATCreateDynFilletVertexRibbonOrder( CATCell *iVertex, CATCell *iLastEdge );
ExportedByCATGMOperatorsInterfaces CATDynFilletVertexRibbonOrder* CATCreateDynFilletVertexRibbonOrder( CATCell *iEdge, CATLISTP(CATCell) *iStopFaces );
ExportedByCATGMOperatorsInterfaces CATDynFilletVertexRibbonOrder* CATCreateDynFilletVertexRibbonOrder( CATCell *iVertex, const CATLISTP(ListPOfCATEdge) & iListsOfEdges );

#include "CATCGMLISTP_Declare.h"
CATCGMLISTP_DECLARE(CATDynFilletVertexRibbonOrder);

#endif

