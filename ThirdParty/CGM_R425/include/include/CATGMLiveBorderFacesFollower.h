#ifndef CATGMLiveBorderFacesFollower_H
#define CATGMLiveBorderFacesFollower_H

#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATBoolean.h"
#include "ListPOfCATPersistentFaces.h"

class CATGeoFactory;
class CATCGMStream;
class CATPersistentCellInfra;

class ExportedByPersistentCell CATGMLiveBorderFacesFollower 
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATGMLiveBorderFacesFollower(CATPersistentCellInfra &iInfra, CATPersistentBody * iInitialPersistentBody, ListPOfCATPersistentFaces & iBorderPersistentFaceList, CATPersistentBody * iOtherPersistentBody, int iNumOperatorIDForFollower);

  // Copy Constructor
  CATGMLiveBorderFacesFollower(CATGMLiveBorderFacesFollower & iFollower);

  // Destructor
  virtual ~CATGMLiveBorderFacesFollower();

  // Get/Set Method
  int GetNumOperatorIdForFollowers();
  CATPersistentCellInfra *GetPersistentInfra() const;
  
  void SetInitialPersistentBody(CATPersistentBody * iInitialPersistentBody);

  void Stream(CATCGMStream& ioStr,CATGeoFactory * iFactory) const;
  void UnStream(CATCGMStream& ioStr,CATGeoFactory * iFactory);

  void GetBorderPersistentFaceList(ListPOfCATPersistentFaces  & oBorderPersistentFaceList) const;
  CATPersistentBody * GetOtherPersistentBody() const;

protected:

  void SetInitialBodyWithContextualFeature(CATPersistentBody * iPersistentBody);

protected:
  CATPersistentCellInfra         * _Infra;
  int                              _NumOperatorIDForFollower;
  ListPOfCATPersistentFaces        _BorderPersistentFaceList;
  CATPersistentBody              * _InitialPersistentBody;
  CATPersistentBody              * _OtherPersistentBody;

};

#endif

