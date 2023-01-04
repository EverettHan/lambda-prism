#ifndef CATlsoAdvancedStampInputSpecificData_H
#define CATlsoAdvancedStampInputSpecificData_H
/* -*-C++-*- */
//VB7
//===========================================================================
//Inputs for advancedStamp (live and not) operators
//CAN BE STREAMED
//===========================================================================

#include "CATCGMVirtual.h"
#include "CATBoolean.h"
#include "CATMathConstant.h"
#include "CATMathDirection.h"
#include "PersistentCell.h"
#include "CATCGMStream.h"
#include "CATCGMOutput.h"
#include "CATTopDefine.h"

// @nocgmitf (this class doesn't need a CATIPGM interface)
class ExportedByPersistentCell CATlsoAdvancedStampInputSpecificData : public CATCGMVirtual
{

public:

  // Constructor for CATlsoCircularShapeInputData
  CATlsoAdvancedStampInputSpecificData(CATOrientation      iTopBottomOrientation,
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
  ~CATlsoAdvancedStampInputSpecificData();

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

  CATBoolean GetFilletRepresentation();
  double GetFilletRadius();

  // --------
  // Dump
  // --------
  void Dump(CATCGMOutput& os) const;

  void Stream(CATCGMStream  & Str);
  static CATlsoAdvancedStampInputSpecificData * UnStream(CATCGMStream  & Str);

protected:


private:
  CATOrientation      _TopBottomOrientation;
  double              _FilletRadius;
  CATBoolean          _FilletRepresentation;
  CATMathDirection    _DraftDirection;
  CATAngle            _DraftAngle;
  double              _Height;
  int                 _DimensionType;
  CATBoolean          _TrimSupportMode;
  CATBoolean          _CurveRepresentation;

};

#endif


