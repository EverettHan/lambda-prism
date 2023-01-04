#ifndef CATlsoAdvancedStampInputData_H
#define CATlsoAdvancedStampInputData_H
/* -*-C++-*- */
//VB7
//NOT STREAMED

#include "CATCGMVirtual.h"
#include "CATBoolean.h"
#include "CATMathConstant.h"
#include "CATMathDirection.h"
#include "PersistentCell.h"
#include "CATTopDefine.h"

class CATGMAdvancedStampOpe;
class CATBody;
class CATCGMOutput;
class CATIPGMAdvancedStampOpe;
class CATPersistentBody;
class CATlsoAdvancedStampInputSpecificData;

// @nocgmitf (this class doesn't need a CATIPGM interface)
class ExportedByPersistentCell CATlsoAdvancedStampInputData : public CATCGMVirtual
{

public:

  // Constructor for CATlsoCircularShapeInputData
  CATlsoAdvancedStampInputData(CATPersistentBody * iInputShapePBody,
                               CATOrientation      iTopBottomOrientation,
                               double              iFilletRadius, 
                               CATBoolean          iFilletRepresentation,
                               const CATMathDirection & iDraftDirection,
                               CATAngle            iDraftAngle,/*degree*/
                               double              iHeight,
                               int                 iDimensionType,
                               CATBoolean          iTrimSupportMode,
                               CATBoolean          iCurveRepresentation);

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;
  
  // Destructeur
  ~CATlsoAdvancedStampInputData();

  CATPersistentBody & GetInputShapePBody();
  CATlsoAdvancedStampInputSpecificData & GetSpecificData();

  //Get
  void GetData(CATOrientation    &  oTopBottomOrientation,
               double            &  oFilletRadius, 
               CATBoolean        &  oFilletRepresentation,
               CATMathDirection  &  oDraftDirection,
               CATAngle          &  oDraftAngle,
               double            &  oHeight,
               int               &  oDimensionType,
               CATBoolean        &  oTrimSupportMode,
               CATBoolean        &  oCurveRepresentation);

  // --------
  // Dump
  // --------
  void DumpObj(CATCGMOutput& os) const;

protected:


private: 

  CATPersistentBody * _InputShapePBody;
  CATlsoAdvancedStampInputSpecificData * _SpecificData;

};

#endif


