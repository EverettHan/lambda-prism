#ifndef CATIPGMTopPropagationEdge_h_
#define CATIPGMTopPropagationEdge_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"
#include "CATBody.h"

class CATCell;
class CATEdge;
class CATLISTP_CATCell_;
class CATLISTP_CATEdge_;
class CATUnicodeString;
class CATShell;
class CATVertex;
class CATLISTP(CATEdge);
class CATLISTP(CATCell);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopPropagationEdge;

class ExportedByCATGMModelInterfaces CATIPGMTopPropagationEdge: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopPropagationEdge();

  /**
* Runs the operator
*/
  virtual int Run() = 0;

  /**
* Returns the list of cells tangent to the initial edges.
*/
  virtual void GetResultListEdges(CATLISTP(CATCell) &ioListEdges) = 0;

  /**
* @nodoc
*/
  virtual void SetRollingEdges(CATLISTP(CATEdge) *iRollingEdges) = 0;

  /**
* @nodoc
*/
  virtual void SetPropagationType(
    CATBody ::CATPropagationTypePr3 iPropagationType) = 0;

  /**
* @nodoc
*/
  virtual void SetBody(CATBody *iBody) = 0;

  /**
* @nodoc
*/
  virtual void SetShell(CATShell *iShell) = 0;

  /**
* @nodoc
*/
  virtual CATLISTP(CATEdge) *GetListOfEdge() = 0;

  /**
* @nodoc
*/
  virtual CATLISTP(CATFace) *GetListOfFace1() = 0;

  /**
* @nodoc
*/
  virtual CATLISTP(CATFace) *GetListOfFace2() = 0;

  /**
* @nodoc
*/
  virtual CATListOfInt *GetListOfOrientation() = 0;

  /**
* @nodoc
*/
  virtual CATVertex *GetStartVertex() = 0;

  /**
* @nodoc
*/
  virtual CATVertex *GetEndVertex() = 0;

  /**
* @nodoc
*/
  virtual CATBody *GetBody() = 0;

  /**
* @nodoc
*/
  virtual CATShell *GetShell() = 0;

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
  virtual void DumpInterne(CATUnicodeString Commentaire) = 0;

  /**
* @nodoc
*/
  virtual void InitShell() = 0;

  /**
* @nodoc
*/
  virtual void AddFirstEdge(
    CATBody *Body,
    CATEdge *iEdge,
    CATBody ::CATPropagationTypePr3 iPropagationType,
    CATShell *iShell = NULL) = 0;

  /**
* @nodoc
*/
  virtual void AddFirstEdge(CATEdge *iEdge) = 0;

  /**
* @nodoc
* oPlace= 0 , leading edge.
* oPlace= 1 , trailing edge.
* oPlace= 2 , other.
*/
  virtual int AddEdge(CATEdge *iEdge, int oPlace = 2) = 0;

  /**
* @nodoc
*/
  virtual void RemoveEdge(CATEdge *iEdge) = 0;

  /**
* @nodoc
* @return [out, IUnknown#Release]
*/
  virtual CATIPGMTopPropagationEdge *Clone() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopPropagationEdge(); // -> delete can't be called
};

#endif /* CATIPGMTopPropagationEdge_h_ */
