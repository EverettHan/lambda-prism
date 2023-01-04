#ifndef CATlsoListOfCATDRepNavigator_H
#define CATlsoListOfCATDRepNavigator_H

#include "PersistentCell.h"
#include "CATGMList.h"
#include "CATBoolean.h"
#include "CATCellManifoldPatternNavigator.h"

class CATDRepNavigator;
class CATCellManifoldGroup;

class ExportedByPersistentCell CATlsoListOfCATDRepNavigator : public CATGMList<CATDRepNavigator>
{
public : 

   CATlsoListOfCATDRepNavigator(int iSize = 0);
   virtual ~CATlsoListOfCATDRepNavigator();

   CATDRepNavigator * Get(int iPos) const;
   CATDRepNavigator*  operator[](int iPos) const;
   void Append(CATLiveBody* iLiveBody);
   void RemoveAll();
   CATBoolean BelongsToCellManifoldPattern(CATCellManifoldGroup * iGroup);
   CATBoolean BelongsToCellManifoldPattern(CATCellManifoldGroup * iGroup, CATCellManifoldPatternNavigator *& opPatternNavigator);
};

#endif
