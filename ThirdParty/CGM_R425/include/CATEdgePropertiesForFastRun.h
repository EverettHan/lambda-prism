/**
 * @COPYRIGHT DASSAULT SYSTEMES 2009
 */
/* -*-c++-*- */
//===========================================================================
//
// Feb. 2010   Creation                            JJ3
//
//===========================================================================
/* CLASSE NON UTILISE POUR L'INSTANT
#ifndef  CATEdgePropertiesForFastRun_h
#define  CATEdgeProtertiesForFastRun_h

#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "CATEdge.h"


class ExportedByCATTopologicalObjects CATEdgePropertiesForFastRun
{
public:

  CATEdgePropertiesForFastRun();
  virtual ~CATEdgePropertiesForFastRun();

  void SetIsVirtual();
  void SetIsInNewResult();
  void SetAssocOIEdge(CATEdge * iAssocOIEdge);
  void SetAssocOREdge(CATEdge * iAssocOREdge);
  void SetAssocNIEdge(CATEdge * iAssocNIEdge);
  void SetAssocNREdge(CATEdge * iAssocNREdge);
  void SetAssocVirtualEdge1(CATEdge * iAssocVirtualEdge1);
  void SetAssocVirtualEdge2(CATEdge * iAssocVirtualEdge2);
  void SetAssocRealEdge(CATEdge * iAssocRealEdge);

  CATBoolean GetIsVirtual();
  CATBoolean GetIsInNewResult();
  CATEdge *  GetAssocOIEdge();
  CATEdge *  GetAssocOREdge();
  CATEdge *  GetAssocNIEdge();
  CATEdge *  GetAssocNREdge();
  CATEdge *  GetAssocVirtualEdge1();
  CATEdge *  GetAssocVirtualEdge2();
  CATEdge *  GetAssocRealEdge();

protected : 

  CATBoolean _IsVirtual;
  CATBoolean _IsInNewResult;
  CATEdge *  _AssocOIEdge;
  CATEdge *  _AssocOREdge;
  CATEdge *  _AssocNIEdge;
  CATEdge *  _AssocNREdge;
  CATEdge *  _AssocVirtualEdge1;
  CATEdge *  _AssocVirtualEdge2;
  CATEdge *  _AssocRealEdge;
 

};

#endif
*/

