#ifndef CATPatternActivationInstanceStructure_H
#define CATPatternActivationInstanceStructure_H

#include "CATCGMNewArray.h"


//#include "CATPersistentCell.h"
#include "CATGMModelInterfaces.h"
#include "CATPatternActivationStatus.h"


class /*ExportedByPersistentCell*/ExportedByCATGMModelInterfaces CATPatternActivationInstanceStructure
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATPatternActivationInstanceStructure();
  
  virtual ~CATPatternActivationInstanceStructure();

  //Methods
  void SetInstanceNumber(short &iInstanceNumber);
  short GetInstanceNumber();

  void SetActivationMode(const CATPatternActivationStatus & iActivationMode);
  CATPatternActivationStatus GetActivationMode();


  // Copy constructor 
  CATPatternActivationInstanceStructure (const CATPatternActivationInstanceStructure &iOtherInstanceStructure);
  // Operator =
  CATPatternActivationInstanceStructure & operator = (const CATPatternActivationInstanceStructure &iOtherInstanceStructure);

public:
  short  _InstanceNumber;
  CATPatternActivationStatus  _ActivationMode;
 
};

#endif 

