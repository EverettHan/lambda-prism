#ifndef CATIPGMCreateLawOnWire_h_
#define CATIPGMCreateLawOnWire_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCompositeLaw;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMCreateLawOnWire;

class ExportedByCATGMOperatorsInterfaces CATIPGMCreateLawOnWire: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCreateLawOnWire();

  // SetValueForConstantLaw : Cette methode permet de donner les valeurs des contraintes
  //a imposer sur l'edge pour obtenir une loi constante.
  virtual void SetValueForConstantLaw(double *iValues, CATLONG32 nb_Values) = 0;

  // SetValueForLinearLaw : Cette methode permet de donner les valeurs des contraintes
  //a imposer sur l'edge pour obtenir une loi linéaire.
  // donner une valeur de plus que le nombre d'edges
  virtual void SetValueForLinearLaw(double *iValues, CATLONG32 nb_Values) = 0;

  //Methode Run Calcul de la compositeLaw
  virtual int Run() = 0;

  virtual CATCompositeLaw *GetLaw() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCreateLawOnWire(); // -> delete can't be called
};

/**
* @nodoc
* Constructor 
* @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMCreateLawOnWire *CATPGMCreateCreateLawOnWire(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iWire);

#endif /* CATIPGMCreateLawOnWire_h_ */
