#ifndef CATVolume_H
#define CATVolume_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATCell.h"
#include "CATMathBox.h"
#include "ListPOfCATFace.h"

class CATDomain;
class CATBoundaryIterator;
class CATBoundedCellsIterator;
#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATVolume ;
#else
extern "C" const IID IID_CATVolume ;
#endif

/**
 * Interface representing a topological volume.
 * <br>A volume is a topological cell which geometry 
 * is a 3D-space. It is bounded by faces, edges and vertices.
 * <br>A CATVolume is created with the @href CATBody#CreateCell or @href CATBody#CreateVolume methods and
 * deleted with the @href CATICGMContainer#Remove method.
 */ 
class ExportedByCATGMModelInterfaces CATVolume : public CATCell
{

  CATDeclareInterface;

  public :
};

CATDeclareHandler(CATVolume,CATCell);

#endif // CATVolume_H
