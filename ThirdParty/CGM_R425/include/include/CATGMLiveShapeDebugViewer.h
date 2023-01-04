// --------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// ST5: -- Visualize Declarative Manifolds -- Only for Debug
// --------------------------------------------------------------------------------------//

#ifndef CATGMLiveShapeDebugViewer_H
#define CATGMLiveShapeDebugViewer_H

#include "CATCGMNewArray.h"

#include "ListPOfCATBody.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "CATBoolean.h"

class CATSoftwareConfiguration;
class CATGeoFactory;
class CATDeclarativeManifold;
class CATLiveBody;
class CATBody;

class CATGMLiveShapeDebugViewer
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATGMLiveShapeDebugViewer(CATSoftwareConfiguration * iConfig, CATGeoFactory &iFactory);
  virtual ~CATGMLiveShapeDebugViewer();

  void ShowDeclarativeManifold(CATDeclarativeManifold *iDeclMan, CATLiveBody &iLiveBody, int ired, int igreen, int iblue,
                               CATBoolean iStopAfterShow=FALSE, char * iStringToDisplay=NULL);
  void ShowDeclarativeManifold(ListPOfCATDeclarativeManifold iListOfDeclMan, CATLiveBody &iLiveBody, int ired, int igreen, int iblue,
                               CATBoolean iStopAfterShow=FALSE, char * iStringToDisplay=NULL);

  //ST5: Add Show Extrusion Primitives, Show Pads, Show Pockets, Show Holes etc.


private:
  CATSoftwareConfiguration * _SoftwareConfiguration;
  CATGeoFactory &_Factory;

  ListPOfCATBody _CreatedBodies;
};

#endif 

