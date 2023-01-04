#ifndef CATIPGMVolumeMergerOpe_h_
#define CATIPGMVolumeMergerOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2021

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMPersistentOperator.h"

class CATCellHashTable;
class CATFaceHashTable;
class CATGMVolumeMergerImpl;
class CATVolume;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMVolumeMergerOpe;

class ExportedByCATGMOperatorsInterfaces CATIPGMVolumeMergerOpe: public CATIPGMPersistentOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMVolumeMergerOpe();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMVolumeMergerOpe(); // -> delete can't be called
};

ExportedByCATGMOperatorsInterfaces CATIPGMVolumeMergerOpe *CATPGMCreateGMVolumeMergerOpe(
  CATGeoFactory &iFactory,
  CATTopData &iTopData,
  CATBody &iBody,
  CATVolume &iFirstVolume,
  CATVolume &iSecondVolume);

ExportedByCATGMOperatorsInterfaces CATIPGMVolumeMergerOpe *CATPGMCreateGMVolumeMergerOpe(
  CATGeoFactory &iFactory,
  CATTopData &iTopData,
  CATBody &iBody,
  CATLISTP(CATCell) &iVolumeList);

ExportedByCATGMOperatorsInterfaces CATIPGMVolumeMergerOpe *CATPGMCreateGMVolumeMergerOpe(
  CATGeoFactory &iFactory,
  CATTopData &iTopData,
  CATBody &iBody,
  CATCellHashTable &iVolumeHT);

ExportedByCATGMOperatorsInterfaces CATIPGMVolumeMergerOpe *CATPGMCreateGMVolumeMergerOpe(
  CATGeoFactory &iFactory,
  CATTopData &iTopData,
  CATBody &iBody,
  CATCellHashTable &iVolumeHT,
  CATFaceHashTable &iInterfaceHT);

#endif /* CATIPGMVolumeMergerOpe_h_ */
