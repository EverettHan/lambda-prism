/* -*-c++-*- */
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//-----------------------------------------------------------------------------
// Usage :
//
//   Pour check G0 :
// 
//   CATEdgeCheckAttribute*  attr = CATCreateCheckAttribute(Edge);
//   attr->SetMax(CATG0, maxgap );
//
//   Pour check G1 (besoin des faces)
//   (si l'edge ne borde que 2 faces dans le body)
//   CATEdgeCheckAttribute*  attr = CATCreateCheckAttribute(Edge,Body);
//   attr->SetMax(CATG1, maxangle );
//   attr->SetMax(CATG0, maxgap );
//
//=============================================================================

#ifndef CATEdgeCheckAttribute_H
#define CATEdgeCheckAttribute_H

#include "CXMODEL.h"                    
#include "CATCGMStreamAttribute.h"                                 
#include "CATMathDef.h"                                     
#include "CATTopDef.h"
//#include "CATTopCheckError.h"                                     

class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATPCurve;
class CATGeoFactory;
class CATEdge;
class CATFace;
class CATBody;
class CATEdgeCheckAttribute;
class CATError;




ExportedByCXMODEL CATEdgeCheckAttribute*  CATCreateCheckAttribute(CATEdge*,CATBody* iBody=NULL);
ExportedByCXMODEL CATEdgeCheckAttribute*  CATCreateCheckAttribute(CATEdge*,CATFace* iFaces[2]);

class ExportedByCXMODEL CATEdgeCheckAttribute : public CATCGMStreamAttribute
{
public :
  CATEdgeCheckAttribute();
  CATEdgeCheckAttribute(CATEdge* iEdge, CATBody* iBody = NULL);
  CATEdgeCheckAttribute(CATEdge* iEdge, CATFace* iFaces[2]);
  ~CATEdgeCheckAttribute();

  /**
   * Activation de check avec critere d'erreur (valeur max)
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

  CATCGMDeclareAttribute (CATEdgeCheckAttribute,CATCGMStreamAttribute);
  virtual void Stream   (CATCGMStream&) const;
  virtual void UnStream (CATCGMStream&);

  int GetObjects (CATGeoFactory             *&  oFactory,
                  CATEdgeCurve              *&  oEdgeCurve,
                  CATPointOnEdgeCurve *   oPoecs[2],
                  CATPCurve           *   oPCurves[2]);
private :

  unsigned char     _G0;
  unsigned char     _G1;
  unsigned char     _G2;

  unsigned char     _Val;

  CATPositiveLength _G0Max;
  CATAngle          _G1Max;

  CATPositiveLength _G0Val;
  CATAngle          _G1Val;

  CATEdge*          _Edge;
  CATFace*          _Faces[2];
};

#endif
