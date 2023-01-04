/* -*-c++-*- */
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//-----------------------------------------------------------------------------
// Usage :
//
//   Pour check G0 :
// 
//   CATVertexCheckAttribute*  attr = CATCreateCheckAttribute(Vertex);
//   attr->SetMax(CATG0, maxgap );
//
//   Pour check G1 (besoin des edges)
//   (si le Vertex ne borde que 2 edges dans le body)
//   CATVertexCheckAttribute*  attr = CATCreateCheckAttribute(Vertex,Body);
//   attr->SetMax(CATG1, maxangle );
//   attr->SetMax(CATG0, maxgap );
//
//=============================================================================

#ifndef CATVertexCheckAttribute_H
#define CATVertexCheckAttribute_H

#include "CXMODEL.h"                    
#include "CATCGMStreamAttribute.h"                                 
#include "CATMathDef.h"                                     
#include "CATTopDef.h"
//#include "CATTopCheckError.h"                                     

class CATGeoFactory;
class CATVertex;
class CATEdge;
class CATBody;
class CATVertexCheckAttribute;
class CATPointOnEdgeCurve;
class CATError;


ExportedByCXMODEL CATVertexCheckAttribute*  CATCreateCheckAttribute(CATVertex*,CATBody* iBody=NULL);
ExportedByCXMODEL CATVertexCheckAttribute*  CATCreateCheckAttribute(CATVertex*,CATEdge* iEdges[2]);

class ExportedByCXMODEL CATVertexCheckAttribute : public CATCGMStreamAttribute
{
public :
  CATVertexCheckAttribute();
  CATVertexCheckAttribute(CATVertex* iVertex, CATBody* iBody = NULL);
  CATVertexCheckAttribute(CATVertex* iVertex, CATEdge* iEdges[2]);
  ~CATVertexCheckAttribute();

  /**
   * Activation de check avec critere d'erreur (valeur max
   *   iCriteria = CATG0,    CATG1
   *   iMaxValue = distance, angle
   */
  void SetMax(CATTopGeoContinuity iCriteria, double iMaxValue);

  /**
   *  Check method : to be called by The Ketchup 
   *  Array of errors pointers is returned (0 is no error found)
   *  This array must be deleted by the caller. 
   */
  virtual CATError** Check(int& oNbErrors);

  CATCGMDeclareAttribute (CATVertexCheckAttribute,CATCGMStreamAttribute);
  virtual void Stream   (CATCGMStream&) const;
  virtual void UnStream (CATCGMStream&);

  int GetObjects (CATPointOnEdgeCurve  *   oPoecs[2]);

private :

  unsigned char     _G0;
  unsigned char     _G1;

  unsigned char     _Val;

  CATPositiveLength _G0Max;
  CATAngle          _G1Max;

  CATPositiveLength _G0Val;
  CATAngle          _G1Val;

  CATVertex*        _Vertex;
  CATEdge*          _Edges[2];
};

#endif
