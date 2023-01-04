#ifndef CATContextualManifold_h
#define CATContextualManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATDeclarativeManifold.h"
#include "ListPOfCATCellManifold.h"
class CATLISTP(CATHGeometry);
class CATLiveBody;

#include "YI00IMPL.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByYI00IMPL IID IID_CATContextualManifold ;
#else
extern "C" const IID IID_CATContextualManifold ;
#endif

class ExportedByYI00IMPL CATContextualManifold : public CATDeclarativeManifold
{
  CATDeclareInterface;

public:

  virtual void GetTypeWithDuplicates(CATListOfInt &oType) const = 0;

  // iIncludeHGeometries (CGM private use only): includes Links through HGeometries 
  // iLiveBodyForConnexion (CGM private use only): includes connected CellManifolds whenever this Declarative Manifold is not fully specified by its surfaces geometry type (such as a BoneFillet lying on a nurbs)  
  virtual void GetContext(ListPOfCATCellManifold &oContextCellManifold, const CATBoolean iIncludeHGeometries = FALSE, CATLiveBody* iLiveBodyForConnexion = NULL) const = 0;

  virtual void GetContextWithoutJointSupports(ListPOfCATCellManifold &oContextCellManifold, CATListOfInt *oTypes = NULL) const = 0;

  virtual CATBoolean HasSimilarData(const CATDeclarativeManifold *iOtherDeclarativeManifold, double iLengthTol) const = 0;

  virtual void GetHGeometries(CATLISTP(CATHGeometry) &oHGeometries) const = 0;
};
  
CATDeclareHandler(CATContextualManifold,CATDeclarativeManifold);

#endif
