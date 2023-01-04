#ifndef CATGMAdvancedStampData_H
#define CATGMAdvancedStampData_H

//VB7
//===========================================================================
//Computed by advancedStamp operator to send data to creator agents
//CAN BE STREAMED
//===========================================================================

#include "CATPersistentCell.h"
#include "ListPOfCATFace.h"
#include "CATCGMVirtual.h"
#include "CATListOfShort.h"

class CATBody;
class CATGMAdvancedStampLiveData;
class CATLiveBody;

/*
Type :
1 : Top
2 : Fillet
3 : Draft
*/

class ExportedByPersistentCell CATGMAdvancedStampData : public CATCGMVirtual
{
public:

  // Constructor
  CATGMAdvancedStampData(
    CATBody                * iBody,
    ListPOfCATFace         & iTopFaceList,
    ListPOfCATFace         & iDraftedFaceList,
    ListPOfCATFace         & iFilletedFaceList,
    CATBoolean               iFilletRepresentation,
    double                   iFilletRadius);

  CATGMAdvancedStampData(CATGMAdvancedStampData & iInputAdvancedStampData);

  // Destructor
  virtual ~CATGMAdvancedStampData();

  //@nocgmitf
  CATBody * GetInputBody() const;
  //@nocgmitf
  void GetFilletedFaceList(ListPOfCATFace & oFilletedFaceList);
  //@nocgmitf
  void GetDraftedFaceList(ListPOfCATFace & oDraftedFaceList);
  //@nocgmitf
  void GetTopFaceList(ListPOfCATFace & oTopFaceList);
  //@nocgmitf
  double GetFilletRadius() const;
  //@nocgmitf
  CATBoolean GetFilletRepresentation() const;

  // @nocgmitf
  CATBoolean IsEqual(CATGMAdvancedStampData * iAdvancedStampData, CATGeoFactory & iFactory);

  // @nocgmitf
  CATGMAdvancedStampLiveData * ComputeAdvancedStampLiveData(CATLiveBody * iLiveBody);

  // @nocgmitf
  void Dump(CATCGMOutput& Output);

  // @nocgmitf
  void Stream(CATCGMStream & ioStream);

  // @nocgmitf
  static CATGMAdvancedStampData * UnStream(CATCGMStream & ioStream, CATGeoFactory * iFactory);

private :


private :

  CATBody            * _InputBody;
  ListPOfCATFace       _TopFaceList;
  ListPOfCATFace       _DraftedFaceList;
  ListPOfCATFace       _FilletedFaceList;
  double               _FilletRadius;
  CATBoolean           _FilletRepresentation;
};

#endif
