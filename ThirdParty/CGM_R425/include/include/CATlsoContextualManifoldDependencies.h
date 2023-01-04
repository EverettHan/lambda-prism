// ----------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2018
// ................................
//
// VB7
// To store data in an attribute linked to a CellManifold :
//    - a Contextual Manifold list whose the CellManifold is context
// ----------------------------------------------------------------------------//
//==========================================================
// !!!!!!!!!!!!!!!!!!!!!!DO NOT USE!!!!!!!!!!!!!!!!!!!!!!!!!
//==========================================================
// WORK IN PROGRESS VB7 W12 2018


#ifndef CATlsoContextualManifoldDependencies_H
#define CATlsoContextualManifoldDependencies_H

#include "CATPersistentCell.h"
#include "CATCGMAttribute.h"
#include "ListPOfCATContextualManifold.h"

class CATContextualManifold;
class CATCellManifold;

//@nocgmitf
class ExportedByPersistentCell CATlsoContextualManifoldDependencies : public CATCGMAttribute
{

public: 

  CATCGMDeclareAttribute(CATlsoContextualManifoldDependencies, CATCGMAttribute);

  CATlsoContextualManifoldDependencies(CATCellManifold & iCellManifold); 
  virtual ~CATlsoContextualManifoldDependencies();

  void Insert(CATContextualManifold * iContextualManifold);

  void GetDependencies(ListPOfCATContextualManifold & oContextualManifoldList);

  void RemoveDependency(CATContextualManifold * iContextualManifold);

  CATBoolean IsEmpty();

  void Dump( CATCGMOutput & os );

protected:
  //Default constructor
  CATlsoContextualManifoldDependencies(); 

private:

  ListPOfCATContextualManifold _ContextualManifoldList;

};

#endif

