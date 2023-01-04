
#ifndef __CATTopPropagationEdgeOpe_H__
#define __CATTopPropagationEdgeOpe_H__

// COPYRIGHT DASSAULT SYSTEMES 2002

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 


#include "CATIACGMLevel.h" 
#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATBody.h"
#include "CATCGMNewArray.h"
#include "CATIACGMLevel.h"

class CATEdge;
class CATLISTP(CATEdge);
class CATCell;
class CATLISTP(CATCell);

class CATUnicodeString ;


class ExportedByCATTopologicalObjects CATTopPropagationEdge : public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopPropagationEdge);
protected:
  
/**
* @nodoc
* Constructor - not to be used
*/
  CATTopPropagationEdge(CATGeoFactory * iFactory,
                        CATTopData * iTopData,
                        CATBody * iBody,
                        CATLISTP(CATCell) * iInitialEdges,
                        CATBody::CATPropagationTypePr3 iPropagationType,
                        CATLISTP(CATEdge) * iRollingEdges);
  
public:
  
  virtual ~CATTopPropagationEdge();
/**
* @nodoc
*/
  CATCGMNewClassArrayDeclare;
  
/**
* Runs the operator
*/
  virtual int Run() = 0;
  
/**
* Returns the list of cells tangent to the initial edges.
*/
  virtual void GetResultListEdges(CATLISTP(CATCell) & ioListEdges) = 0;
/**
* @nodoc
*/
  virtual void SetRollingEdges(CATLISTP(CATEdge) * iRollingEdges) = 0;

/**
* @nodoc
*/
  virtual void SetSameConvexityRollingEdges() = 0;

/**
* @nodoc
*/
  virtual void AllowPropagationOnDifferentConvexity() = 0;

/**
* @nodoc
*/
  virtual void SetPropagationType(CATBody::CATPropagationTypePr3  iPropagationType) = 0;
/**
* @nodoc
*/
  virtual void SetBody(CATBody* iBody) = 0;
/**
* @nodoc
*/
  virtual void SetShell(CATShell* iShell) = 0;
/**
* @nodoc
*/
  virtual ListPOfCATEdge* GetListOfEdge() = 0;
/**
* @nodoc
*/
  virtual ListPOfCATFace* GetListOfFace1() = 0;
/**
* @nodoc
*/
  virtual ListPOfCATFace* GetListOfFace2() = 0;
/**
* @nodoc
*/
  virtual CATListOfInt* GetListOfOrientation() = 0;
/**
* @nodoc
*/
  virtual CATVertex* GetStartVertex() = 0;
/**
* @nodoc
*/
  virtual CATVertex* GetEndVertex() = 0;
/**
* @nodoc
*/
  virtual CATBody* GetBody() = 0;
/**
* @nodoc
*/
  virtual CATShell* GetShell() = 0;
/**
* @nodoc
*/
  virtual CATTopSharpness GetSharpness() = 0;
/**
* @nodoc
*/
  virtual CATBody::CATPropagationTypePr3 GetPropagationType() = 0;
/**
* @nodoc
*/
  virtual void DumpInterne( CATUnicodeString Commentaire ) = 0 ;
/**
* @nodoc
*/
  virtual void InitShell() = 0;
/**
* @nodoc
*/
  virtual void AddFirstEdge(CATBody* Body,CATEdge * iEdge,CATBody::CATPropagationTypePr3 iPropagationType, CATShell *iShell=NULL) = 0;
/**
* @nodoc
*/
  virtual void AddFirstEdge(CATEdge * iEdge) = 0;
/**
* @nodoc
* oPlace= 0 , leading edge.
* oPlace= 1 , trailing edge.
* oPlace= 2 , other.
*/
  virtual int AddEdge(CATEdge * iEdge, int oPlace=2) = 0;
/**
* @nodoc
*/
  virtual void RemoveEdge(CATEdge *iEdge) = 0;
/**
* @nodoc
*/
  virtual CATTopPropagationEdge* Clone() = 0;
#ifdef CATIACGMR214CAA
/**
* @nodoc
*/
  virtual CATAngle GetAverageSharpnessAngle( CATEdge * iEdge = 0 ) = 0;
/**
* @nodoc
*/
  virtual void RequestDetailedInfoAboutSharpnessAngles() = 0;
/**
* @nodoc
*/
  virtual void GetDetailedInfoAboutSharpnessAngles(CATListOfDouble &ioAngles, CATListOfDouble &ioCrvParams) = 0;
#endif  
};

#endif
