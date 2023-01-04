// ----------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2018
// ................................
//
// VB7
// services on CATlsoContextualManifoldDependencies
// ----------------------------------------------------------------------------//


#ifndef CATlsoContextualManifoldDependencyServices_H
#define CATlsoContextualManifoldDependencyServices_H

#include "CATPersistentCell.h"
#include "ListPOfCATContextualManifold.h"
#include "ListPOfCATCellManifold.h"

class CATCellManifold;
class CATContextualManifold;

//@nocgmitf
class ExportedByPersistentCell CATlsoContextualManifoldDependencyServices : public CATCGMVirtual
{

public: 

  //@nocgmitf
  static void SetDependency(CATCellManifold * iCM, CATContextualManifold * iContextualManifold);

  //@nocgmitf
  static void GetDependencies(CATCellManifold * iCM, ListPOfCATContextualManifold & oContextualManifoldList);

  //@nocgmitf
  static void RemoveDependencies(const ListPOfCATCellManifold & iCMList, CATContextualManifold * iContextualManifold);

  //@nocgmitf
  static void RemoveDependency(CATCellManifold * iCM, CATContextualManifold * iContextualManifold);
};

#endif

