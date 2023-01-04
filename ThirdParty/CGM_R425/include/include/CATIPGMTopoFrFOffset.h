#ifndef CATIPGMTopoFrFOffset_h_
#define CATIPGMTopoFrFOffset_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

//=============================================================================
// 10/01/18 NLD Suppression des vieux CATPGMCreateTopoFrFOffset sans configuration (1/2 par option de precompilation)
// 15/01/18 NLD Suppression des vieux CATPGMCreateTopoFrFOffset sans configuration (2/2 par suppression effective)
//=============================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATSkillValue.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATNurbsSurface;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopoFrFOffset;

//
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATIPGMTopoFrFOffset: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopoFrFOffset();

  virtual int               Run            () = 0;

  //-------------------------------------------------------------
  //GET Methods
  //-------------------------------------------------------------
  //Getting the result surface
  virtual CATBody *         GetResult      () = 0;

  //Getting the max error between real and result offset
  virtual double            GetMaxDeviation() = 0;

  //-------------------------------------------------------------
  //SET Methods - In order to call this method, you should create
  //this operator with an ADVANCED CATSkillValue, make your Set
  //and then call the Run method.
  //-------------------------------------------------------------
  //If you want to set the max degree allowed
  virtual void              SetMaxDegree   (      CATLONG32 MaxDegreeU  ,
                                                  CATLONG32 MaxDegreeV  ) = 0;

  virtual void              SetOffsetValues(const double    iOffsetLaw[]) = 0;

  //To get the geometric result (previsu)
  virtual CATNurbsSurface * LightRun       () = 0;

  //To set the input tolerance
  virtual void              SetTolerance   (      double    iTolerance) = 0;

protected:
  /**
   * Destructor
   */
  virtual                  ~CATIPGMTopoFrFOffset(); // -> delete can't be called
};

//-----------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopoFrFOffset *CATPGMCreateTopoFrFOffset(
        CATGeoFactory * iFactory,
        CATTopData    * iTopData,
  const CATBody       * iSurface,
  const double          iOffsetLaw[],
        double          iTol,
        CATLONG32       iKeepKnots,
        CATSkillValue   iMode = BASIC);

#endif /* CATIPGMTopoFrFOffset_h_ */
