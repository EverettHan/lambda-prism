#ifndef CATlsoGraphTransfoEdge_H
#define CATlsoGraphTransfoEdge_H

#ifdef COVERAGE_REMOVE_CODE

#include "CATPersistentCell.h"
#include "CATlsoGraphEdge.h"
#include "CATMathTransformation.h"
#include "CATlsoGraphFactory.h"
    
class ExportedByPersistentCell CATlsoGraphTransfoEdge : public CATlsoGraphEdge
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

   virtual CATlsoGraphTransfoEdge * GetAsTransfoEdge();
   virtual CATBoolean Equals( CATlsoGraphEdge * iEdgeToCompare );
   virtual void Dump( CATCGMOutput & Output, int iColor );

  void GetTransfo(CATMathTransformation & oTransfo);
  void SetTransfo( CATMathTransformation & iTransfo );

  CATBoolean IsEquivalentTo( CATlsoGraphTransfoEdge * iEdgeToCompare, CATBoolean iStrictEquivalence = FALSE );

protected : 
  CATlsoGraphTransfoEdge(
    CATlsoGraphNode * iStartNode,
    CATlsoGraphNode * iEndNode,
    CATBoolean IsOriented,
    CATMathTransformation & iTransfo,
    CATlsoGraphFactory  * iLsoGraphFactory
    );

  ~CATlsoGraphTransfoEdge();

  double GetPseudoRadius();


private : 

 CATMathTransformation _Transfo;

friend class CATlsoGraphFactory;

};

#endif // #ifdef COVERAGE_REMOVE_CODE

#endif
