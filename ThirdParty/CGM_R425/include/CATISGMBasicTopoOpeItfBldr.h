#ifndef CATISGMBasicTopoOpeItfBldr_h
#define CATISGMBasicTopoOpeItfBldr_h

#include "CATSGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATParameterizationOption.h"
#include "CATDataType.h"
#include "CATMathDef.h"

class CATGeoFactory;
class CATNurbsCurve;
class CATKnotVector;
class CATMathSetOfPoints;
class CATNurbsSurface;
class CATMathGridOfPoints;
class CATBody;
class CATTopData;
class CATISGMShellOperatorPlus;
class CATPickOperator;
class CATSoftwareConfiguration;
class CATISGMThickSurfacePlus;

extern ExportedByCATSGMOperatorsInterfaces IID IID_CATISGMBasicTopoOpeItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework TopologicalOperatorsLight.
 */
class ExportedByCATSGMOperatorsInterfaces CATISGMBasicTopoOpeItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual CATISGMShellOperatorPlus *CATSGMCreateShellOperatorPlus(
    CATBody *iBody,
    CATTopData *iTopData,
    CATLength iInternalOffsetValue,
    CATLength iExternalOffsetValue) = 0;

  virtual CATISGMThickSurfacePlus *CATSGMCreateThickSurfacePlus(
    CATTopData *iTopData,
    CATBody *iBodyToThick,
    double iOffset_1,
    double iOffset_2) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework TopologicalOperators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATSGMOperatorsInterfaces CATISGMBasicTopoOpeItfBldr *CATSGMGetBasicTopoOpeItfBldr();

#endif /* CATISGMBasicTopoOpeItfBldr_h */
