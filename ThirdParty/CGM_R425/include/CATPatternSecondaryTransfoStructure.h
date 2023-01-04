#ifndef CATPatternSecondaryTransfoStructure_H
#define CATPatternSecondaryTransfoStructure_H

#include "CATCGMNewArray.h"


//#include "CATPersistentCell.h"
#include "CATGMModelInterfaces.h"
#include "CATMathTransformation.h"


class /*ExportedByPersistentCell*/ExportedByCATGMModelInterfaces CATPatternSecondaryTransfoStructure
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATPatternSecondaryTransfoStructure();
  
  virtual ~CATPatternSecondaryTransfoStructure();

  //Methods
  void SetInstanceNumber(short &iInstanceNumber);
  short GetInstanceNumber();

  HRESULT SetSecondaryTransfo(CATMathTransformation * iSecondaryTransfo);
  HRESULT GetSecondaryTransfo(CATMathTransformation *& ioSecondaryTransfo);

public:
  short  _InstanceNumber;
  CATMathTransformation  _SecondaryTransfo;
 
};

#endif 

