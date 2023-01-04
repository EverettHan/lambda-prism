#ifndef CATIPGMTopGeometricalMapping_h_
#define CATIPGMTopGeometricalMapping_h_

// COPYRIGHT DASSAULT SYSTEMES 2009

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"
#include "CATGeoFactory.h"
#include "CATTopGeometricalMapType.h"
#include "CATTopGeoMapping_QueryType.h"

class CATBody;
class CATLISTP(CATICGMUnknown);
class CATTopology;
class CATLISTP(CATCGMArrayOfOrientedObjects);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopGeometricalMapping;

class ExportedByCATGMModelInterfaces CATIPGMTopGeometricalMapping: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopGeometricalMapping();

  //=======================================================================================================
  // Obtention du Mapping
  //========================================================================================================
  virtual void GetMapping(
    CATLISTP(CATCGMArrayOfOrientedObjects) &ioMapped,
    double **ioGapOfMapped = NULL,
    CATLISTP(CATICGMObject) *ioIsolated = NULL,
    CATLISTP(CATICGMObject) *ioFailed = NULL) = 0;

  //=======================================================================================================
  // Parametrages des resolutions
  //========================================================================================================
  virtual void GetResolution(
    double &resolution,
    const CATResolutionType iResolutionType = CatC0) const = 0;

  virtual void SetResolution(
    const double &resolution,
    const CATResolutionType iResolutionType = CatC0) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopGeometricalMapping(); // -> delete can't be called
};

//========================================================================================
// Creation de l'operateur de mapping geometrique
//========================================================================================
ExportedByCATGMModelInterfaces CATIPGMTopGeometricalMapping *CATPGMCreateTopGeometricalMapping(
  const CATTopData &iTopData,
  const CATLISTP(CATICGMUnknown) &iInputs,
  const CATTopGeometricalMapType iStrategy,
  const CATTopGeoMapping_QueryType iQueries,
  CATGeometricType iFilter);

ExportedByCATGMModelInterfaces CATIPGMTopGeometricalMapping *CATPGMCreateTopGeometricalMapping(
  const CATTopData &iTopData,
  CATBody *iBody,
  const CATTopGeometricalMapType iStrategy,
  const CATTopGeoMapping_QueryType iQueries,
  CATGeometricType iFilter);

#endif /* CATIPGMTopGeometricalMapping_h_ */
