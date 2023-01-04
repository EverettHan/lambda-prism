#ifndef CATGMVolatileSetOfObjects_H
#define CATGMVolatileSetOfObjects_H

#include "CATListOfCATCells.h"
#include "ListPOfCATBody.h"
#include "CATCDMEnum.h"

class CATGMVolatileSetOfObjects
{
public:

  virtual ~CATGMVolatileSetOfObjects() {};

  virtual void GetTypeOfSet(CATCDMEnum::CDMVolatileSetOfObjectsEnum& oTypeOfSet) = 0;

  // renvoie la liste des objets contenus dans le groupe ainsi que leur body associé
  virtual void GetListOfObjects(CATListPtrCATCell& oListCells, CATLISTP(CATBody)& oListOfBody) = 0;

protected:

  CATGMVolatileSetOfObjects() {};

private:

  // The copy constructor and the equal operator must not be implemented
  CATGMVolatileSetOfObjects(CATGMVolatileSetOfObjects &) {};
  CATGMVolatileSetOfObjects& operator=(CATGMVolatileSetOfObjects&) {};

};

#endif
