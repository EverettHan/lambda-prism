#ifndef CATIPGMTessellationItfBldr_h
#define CATIPGMTessellationItfBldr_h

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATDataType.h"
#include "CATCGMTessBodyList.h"
#include "CATCGMScaleCategoryDef.h"

class CATICGMBodyTessellator;
class CATGeoFactory;
class CATBody;
class CATCell;
class CATVertex;
class CATEdge;
class CATFace;
class CATICGMCellTessellator;
class CATICGMCurveTessellator;
class CATICGMSurfaceTessellator;
class CATCGMTessBody;
class CATPGMTessBody;
class CATCGMTessParam;
class CATCGMTessellateParam;
class CATCGMTessBodyEdgeSerializer;
class CATCGMTessBodyFaceSerializer;
class CATCGMTessBodyVertexSerializer;
class CATCGMTessBodySerializer;
class CATPGMTessParamAccess;
class CATSoftwareConfiguration;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTessellationItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework BasicTopologicalOpe.
 */
class ExportedByCATGMModelInterfaces CATIPGMTessellationItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual CATICGMBodyTessellator *CATCGMCreateBodyTessellator(
    CATBody *iBody,
    double iSag,
    double iAngle) = 0;

  virtual CATICGMCellTessellator *CATCGMCreateCellTessellator(
    CATCell *iCell,
    double iSag,
    double iAngle) = 0;

  virtual CATICGMCellTessellator *CATCGMCreateCellTessellator(double iSag, double iAngle) = 0;

  virtual CATICGMCellTessellator *CATCGMCreateCellTessellator(
    CATBody *iReferenceBody,
    CATCell *iCell,
    double iSag,
    double iAngle) = 0;

  virtual CATICGMCellTessellator *CATCGMCreateCellTessellator(
    CATBody *iReferenceBody,
    double iSag,
    double iAngle) = 0;

  virtual CATICGMCurveTessellator *CATCGMCreateCurveTessellator(
    double iSag,
    double iAngle) = 0;

  virtual CATICGMCurveTessellator* CATCGMCreateCurveTessellator(
      CATSoftwareConfiguration * iSoftwareConfig,
      double iSag,
      double iAngle) = 0;

  virtual CATICGMSurfaceTessellator *CATCGMCreateSurfaceTessellator(
    double iSag,
    double iAngle) = 0;

  // Get rid of me.
  virtual CATCGMTessBody *CATCGMCreateTessBody(
    CATBody &iBody,
    double iSag,
    double iStep,
    double iMaxAngle) = 0;

  // Get rid of me.
  virtual CATCGMTessBody *CATCGMCreateTessBody(CATBody &iBody, const CATCGMTessParam &iTessParam) = 0;

  // Get rid of me.
  virtual CATCGMTessBody *CATCGMCreateTessBody(CATBody &iBody, CATSoftwareConfiguration* iSoftwareConfig, const CATCGMTessellateParam &iTessParam, int iMode=0, int iPrecision=0) = 0;

  // Get rid of me.
  virtual CATCGMTessBody *CATCGMCreateTessBody(CATBody &iBody, CATCGMTessBody &iTessBody) = 0;

  // Get rid of me.
  virtual CATCGMTessBody *CATCGMCreateTessBody(
    CATBody &iBody,
    const CATCGMTessBodyList &iTessBodyList) = 0;

  virtual CATCGMTessBodyEdgeSerializer *CATCGMCreateTessBodyEdgeSerializer(
    CATCGMTessBody &iTessBody,
    CATEdge &iEdge) = 0;

  virtual CATCGMTessBodyFaceSerializer *CATCGMCreateTessBodyFaceSerializer(
    CATCGMTessBody &iTessBody,
    CATFace &iFace) = 0;

  virtual CATCGMTessBodyVertexSerializer *CATCGMCreateTessBodyVertexSerializer(
    CATCGMTessBody &iTessBody,
    CATVertex &iVertex) = 0;

  virtual CATCGMTessBodySerializer *CATCGMCreateTessBodySerializer(CATCGMTessBody &iTessBody) = 0;

  virtual CATPGMTessParamAccess * CATPGMCreateTessParamAccess(CATGeoFactory * iGeoFactory, CATSoftwareConfiguration * iConfig) = 0;
  virtual CATPGMTessParamAccess * CATPGMCreateTessParamAccess(CATCGMScaleCategory iScaleCategory) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework BasicTopologicalOpe.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMTessellationItfBldr *CATCGMGetTessellationItfBldr();

#endif /* CATIPGMTessellationItfBldr_h */
