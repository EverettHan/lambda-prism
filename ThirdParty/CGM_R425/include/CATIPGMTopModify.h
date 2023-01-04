#ifndef CATIPGMTopModify_h_
#define CATIPGMTopModify_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATTopGeometricalMapType.h"

class CATBody;
class CATTopology;
class CATCell;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopModify;

class ExportedByCATGMModelInterfaces CATIPGMTopModify: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopModify();

  //=======================================================================================================
  // Rajout d'une reference externe qui n'appartient pas au Body
  //  et qui porte les informations de Pose-Sur que l'on souhaite injecter sur le Body ...
  // Par un mapping geometrique, on doit retrouver des equivalents topologiques f 
  //========================================================================================================
  virtual void AddExternalReference(CATTopology *iExternalReference) = 0;

  //=======================================================================================
  // Specification d'un traitement de rajout de liens Pose Sur, On demande la recopie/report 
  //    des liens pose sur iBody (une tierce partie) portes par les references externes
  //    sur leur constituant equivalent du Body
  //=======================================================================================
  virtual void SetAddCopyLyingOnLinksFrom(CATBody *iBody) = 0;

  //=======================================================================================
  // Pour debug : verification du mapping de body
  //=======================================================================================
  virtual const CATCell *GetExtRefMappedCell(const CATCell *ipCell) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopModify(); // -> delete can't be called
};

//========================================================================================
// Creation de l'operateur en identifiant le Body en Input (mode Copy)
// argument iVertexMapType : CatTopGeometricalMap_VertexAsSinglePoint ou CatTopGeometricalMap_VertexAsCloudOfPoints
// => voir CATTopGeometricalMapType.h
//========================================================================================
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopModify *CATPGMCreateModify(
  CATBody *iCopyBody,
  const CATTopData &iTopData,
  CATTopGeometricalMapType iVertexMapType);

#endif /* CATIPGMTopModify_h_ */
