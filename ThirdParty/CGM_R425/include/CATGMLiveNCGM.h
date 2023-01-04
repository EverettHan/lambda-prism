/* -*-C++-*- */
#ifndef CATGMLiveNCGM_H
#define CATGMLiveNCGM_H
// COPYRIGHT DASSAULT SYSTEMES 2015

//===================================================================
//===================================================================
//
// CATGMLiveNCGM: Debug tool. Save on disk persistent data
//
//===================================================================
//===================================================================
// Jan 2015    Creation                         R. Rorato
//===================================================================

#include "CATPersistentCell.h"
#include "CATListOfCATICGMObjects.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCell.h"
#include "CATBoolean.h"

class CATSoftwareConfiguration;
class CATGeoFactory;

class ExportedByPersistentCell CATGMLiveNCGM 
{
public:
  //------------------------------------------------------------------------------
  // Returns whether CATCX_NCGM is setup
  //------------------------------------------------------------------------------
  static CATBoolean IsActive();

  //------------------------------------------------------------------------------
  // Constructor
  //------------------------------------------------------------------------------
  CATGMLiveNCGM(CATGeoFactory& iFactory);

  //------------------------------------------------------------------------------
  // Destructor
  //------------------------------------------------------------------------------
  ~CATGMLiveNCGM();

  //------------------------------------------------------------------------------
  // Save objects
  //------------------------------------------------------------------------------
  void Save(const ListPOfCATCellManifold& iCellManifolds, const char* iBodyName = NULL); // iCellManifolds will be saved as a separate body, named iBodyName, in the Container named iFileName when this is flushed
  void Save(const ListPOfCATCell& iCells, const char* iBodyName = NULL); 
  void Save(const CATICGMObject* iObjectToSave, const char* iBodyName = NULL); // iObjectToSave will be saved, named iBodyName if it is a Body, in the Container named iFileName when flushed or this is deleted
  void Flush(const char* iFileName);

  //------------------------------------------------------------------------------
  // Data
  //------------------------------------------------------------------------------
private:
  CATBoolean                _Active;
  CATSoftwareConfiguration* _Config;
  CATGeoFactory&            _Factory;
  CATLISTP(CATICGMObject)   _ToSave;
};

#endif
