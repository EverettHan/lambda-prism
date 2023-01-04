/* -*-C++-*- */
#ifndef CATDumpAsBodies_H
#define CATDumpAsBodies_H
// COPYRIGHT DASSAULT SYSTEMES 2016

//===================================================================
//===================================================================
//
// Class dedicated to dump topologies on disk 
//
//===================================================================
//===================================================================
// June 2016    Creation                         R. Rorato
//===================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMVirtual.h"
#include "CATListOfCATICGMObjects.h"
#include "ListPOfCATTopology.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATFace.h"
#include "CATUnicodeString.h"
#include "CATCGMNewArray.h"
//#include "CATBoolean.h"

class CATGeoFactory;

class ExportedByCATTopologicalObjects CATDumpAsBodies : public CATCGMVirtual
{
public:
  //------------------------------------------------------------------------------
  // Constructor
  //------------------------------------------------------------------------------
  CATDumpAsBodies(CATGeoFactory* iFactory, CATUnicodeString iFileName); // File is written at deletion
  CATCGMNewClassArrayDeclare;             // Pool allocation

  //------------------------------------------------------------------------------
  // Destructor
  //------------------------------------------------------------------------------
  ~CATDumpAsBodies();

  //------------------------------------------------------------------------------
  // Save on disk
  //------------------------------------------------------------------------------
  void Save(const ListPOfCATFace& iFaces, CATUnicodeString iBodyName);
  void Save(const ListPOfCATCell& iCells, CATUnicodeString iBodyName);
  void Save(ListPOfCATTopology& iTopologies, CATUnicodeString iBodyName);
  void Save(CATTopology* iTopology, CATUnicodeString iBodyName);

  //------------------------------------------------------------------------------
  // Member data
  //------------------------------------------------------------------------------
private:
  CATLISTP(CATICGMObject)   _ToSave;
  CATUnicodeString          _FileName;
  CATGeoFactory*            _Factory;
};

#endif
