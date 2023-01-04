#ifndef CATDRepCreator_H
#define CATDRepCreator_H

#include "CATErrorDefs.h"
#include "CATCGMVirtual.h"
#include "CATDRepSeed.h"
#include "ListPOfCATDRepSeed.h"
#include "CATGMModelInterfaces.h"
class CATLiveBody;


class ExportedByCATGMModelInterfaces CATDRepCreator : public CATCGMVirtual
{
public:	
	// Constructor
  CATDRepCreator();
    CATDRepCreator(ListPOfCATDRepSeed & iSeeds);

  // Destructor
	virtual ~CATDRepCreator();

  enum CATDrepType {
    CATWallBendDRepType
  };

  virtual HRESULT CreateDRep();

  //SET 
  INLINE void SetDRepSeeds(ListPOfCATDRepSeed & iSeeds);
  INLINE void SetLiveBody(CATLiveBody *iLiveBody);

  //GET
  virtual CATDRepCreator::CATDrepType GetDRepType()const =0;

protected:
  
  INLINE void GetDRepSeeds(ListPOfCATDRepSeed &oSeeds) const;
  INLINE CATLiveBody *GetLiveBody() const;

private:

  ListPOfCATDRepSeed _Seeds;
  CATLiveBody        *_LiveBody;

};
INLINE void CATDRepCreator::SetDRepSeeds(ListPOfCATDRepSeed & iSeeds)
{
  _Seeds = iSeeds;
}
INLINE void CATDRepCreator::SetLiveBody(CATLiveBody *iLiveBody)
{
  _LiveBody = iLiveBody;
}
INLINE void CATDRepCreator::GetDRepSeeds(ListPOfCATDRepSeed &oSeeds) const
{
  oSeeds=_Seeds;
}
INLINE CATLiveBody *CATDRepCreator::GetLiveBody() const
{
  return _LiveBody;
}
#endif
