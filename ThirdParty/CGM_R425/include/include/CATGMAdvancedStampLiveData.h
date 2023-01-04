#ifndef CATGMAdvancedStampLiveData_H
#define CATGMAdvancedStampLiveData_H

//VB7
//===========================================================================
//Inputs for advancedStamp agents creator
//CAN BE STREAMED
//===========================================================================

#include "CATPersistentCell.h"
#include "ListPOfCATCellManifold.h"
#include "CATCGMVirtual.h"
#include "CATListOfShort.h"

class CATCellManifoldGroup;

/*
Type :
1 : Top
2 : Fillet
3 : Draft
*/

class ExportedByPersistentCell CATGMAdvancedStampLiveData : public CATCGMVirtual
{
public:

  // Constructor
  CATGMAdvancedStampLiveData(
    CATLiveBody            * iLiveBody,
    ListPOfCATCellManifold & iCellManifoldList,
    CATListOfShort         & iCellManifoldTypeList,
    CATBoolean               iFilletRepresentation,
    double                   iFilletRadius);

  // Destructor
  virtual ~CATGMAdvancedStampLiveData();

  //@nocgmitf
  CATLiveBody * GetInputLiveBody() const;
  //@nocgmitf
  void GetAllCellManifolds(ListPOfCATCellManifold & oCellManifoldList) const;
  //@nocgmitf
  void GetFilletedCellManifoldList(ListPOfCATCellManifold & oFilletedCellManifoldList);
  //@nocgmitf
  void GetDraftedCellManifoldList(ListPOfCATCellManifold & oDraftedCellManifoldList);
  //@nocgmitf
  void GetTopCellManifoldList(ListPOfCATCellManifold & oTopCellManifoldList);
  //@nocgmitf
  double GetFilletRadius() const;
  //@nocgmitf
  CATBoolean GetFiletRepresentation() const;

  // @nocgmitf
  CATCellManifoldGroup * CreateDRepAdvancedStampFromData(CATSoftwareConfiguration * iConfig, CATGeoFactory * iFactory);

  // @nocgmitf
  CATBoolean IsEqual(CATGMAdvancedStampLiveData * iAdvancedStampLiveData, CATGeoFactory & iFactory);

  // @nocgmitf
  void Dump(CATCGMOutput& Output);

  // @nocgmitf
  void Stream(CATCGMStream & ioStream);

  // @nocgmitf
  static CATGMAdvancedStampLiveData * UnStream(CATCGMStream & ioStream, CATGeoFactory * iFactory);

private :

  void GetCellManifoldListByType(int iType, ListPOfCATCellManifold & oCellManifoldList) const;

private :

  CATLiveBody            * _InputLiveBody;
  ListPOfCATCellManifold   _InputCellManifoldList;
  CATListOfShort           _InputCellManifoldTypeList;//parallel to _InputCellManifoldList initialized to -1; 1=>Top; 2=>Fillet; 3=>Draft
  double                   _FilletRadius;
  CATBoolean               _FilletRepresentation;
};

#endif
