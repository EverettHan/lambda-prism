#ifndef CATlsoIndex_H
#define CATlsoIndex_H

#include "CATPersistentCell.h"

#include "CATCollec.h"
#include "ListPOfCATCellManifold.h"
#include "CATListOfCATCGMAttribute.h"

class CATHashTableWithIntAssoc;


class ExportedByPersistentCell CATlsoIndex
{
public:

  // Contructor
  CATlsoIndex(CATLISTP(CATCellManifold) & iList);
  CATlsoIndex(CATLISTP(CATCell) & iList);

  // Destructor
  ~CATlsoIndex();

  // The only method. 
  int Locate(void * iElem) const;

private:

  void Init();
  CATHashTableWithIntAssoc * _IndexHT;


};

#endif
