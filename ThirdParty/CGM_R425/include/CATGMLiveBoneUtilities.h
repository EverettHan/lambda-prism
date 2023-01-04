#ifndef CATGMLiveBoneUtilities_H
#define CATGMLiveBoneUtilities_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATCellManifold.h"

class CATSoftwareConfiguration;
class CATBoneManifold;
class CATContextualManifold;

class ExportedByPersistentCell CATGMLiveBoneUtilities
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATGMLiveBoneUtilities(CATSoftwareConfiguration * iConfig);
  virtual ~CATGMLiveBoneUtilities();

  void GetBoneTracks(const CATBoneManifold& iBone, ListPOfCATEdge oTracks[2]) const;

  void ChangeDRepContext(CATContextualManifold *ipContextualManifoldToModify, const ListPOfCATCellManifold &iNewContextCMList, const CATListOfInt & iTypeList) const;

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  protected:
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  CATSoftwareConfiguration* _SoftwareConfiguration;

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  private:
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
};

#endif 

