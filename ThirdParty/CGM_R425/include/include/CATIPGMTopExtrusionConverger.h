#ifndef CATIPGMTopExtrusionConverger_h_
#define CATIPGMTopExtrusionConverger_h_

// COPYRIGHT DASSAULT SYSTEMES 2022

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCGMConvergerDef.h"

class CATBody;
class CATGMLiveExtrusionPrimitive;
class CATGeoFactory;
class CATShell;
class CATSoftwareConfiguration;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopExtrusionConverger;


class ExportedByCATGMOperatorsInterfaces CATIPGMTopExtrusionConverger: public CATIPGMTopOperator
{

  public:

  /**
   * Constructor
   */
  CATIPGMTopExtrusionConverger();

  //------------------------------------------------------------------------------
  // Input
  //------------------------------------------------------------------------------       
  virtual void SetShell     (CATShell *iShell) = 0;

  virtual void SetAppli     (CATCVG_ApplicationName iName) = 0;

  virtual void SetRefType   (CATCVG_CreationType    iType) = 0;

  virtual void SetRunType   (CATCVG_CreationType    iType) = 0;

  virtual void AddRefFeature(CATCVG_FeatureType     iType) = 0;

  virtual void SetPrimShape (CATCVG_PrimShapeType   iType) = 0;

  virtual void AddExtrusion (CATGMLiveExtrusionPrimitive *iExtPrim) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopExtrusionConverger(); // -> delete can't be called
};

/**
 * Creates a <tt>CATIPGMTopExtrusionConverger</tt> operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iBody
 * The pointer to the body where the recognition will be performed.
 * @param iShell
 * The pointer to the shell where the recognition will be performed.
 * @return
 * The pointer to the created operator. To delete after use with the usual C++ <tt>delete</tt> operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopExtrusionConverger *CATPGMCreateTopExtrusionConverger(
  CATGeoFactory *iFactory,
  CATTopData    *iData,
  CATBody       *iBody);

#endif /* CATIPGMTopExtrusionConverger_h_ */
