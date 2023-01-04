#ifndef CATGMLiveShapeGlobalButtonNavigatorInterface_H
#define CATGMLiveShapeGlobalButtonNavigatorInterface_H

#include "CATGMModelInterfaces.h"
#include "CATManifoldNavigator.h"
#include "CATGMLiveShapeGlobalButtonNavigatorEnumInterface.h"
#include "ListPOfCATGMLiveShapeButtonNavigatorInterface.h"

class CATLiveBody;
class CATCellManifold;
class CATGMLiveShapeButtonNavigator;
class CATFace;
class CATGMLiveShapeButtonNavigatorInterface;

class ExportedByCATGMModelInterfaces CATGMLiveShapeGlobalButtonNavigatorInterface : public CATManifoldNavigator
{
public:

  // Constructor
  CATGMLiveShapeGlobalButtonNavigatorInterface(); 

  // Destructor
  virtual ~CATGMLiveShapeGlobalButtonNavigatorInterface();

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATGMLiveShapeGlobalButtonNavigatorInterface * GetAsGlobalButtonNavigatorInterface();

  
  //Get methods

  //VB7 - W09 - Méthodes obsolètes
  virtual CATBoolean BelongsToButton(CATCellManifold * iCM, CATGMLiveShapeButtonNavigatorInterface *& oButtonNavigatorInterface)=0;
  virtual CATBoolean BelongsToButton(CATFace * iFace, CATGMLiveShapeButtonNavigatorInterface *& oButtonNavigatorInterface)=0;

  //VB7 - W09 - Méthodes à utilisées
  virtual CATBoolean BelongsToButton(CATCellManifold * iCM, ListPOfCATGMLiveShapeButtonNavigatorInterface & oButtonNavigatorInterfaceList)=0;
  virtual CATBoolean BelongsToButton(CATFace * iFace, ListPOfCATGMLiveShapeButtonNavigatorInterface & oButtonNavigatorInterfaceList)=0;

  virtual void Dump(CATCGMOutput& Output);

private:


};


#endif
