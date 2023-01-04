/* -*-c++-*- */
#ifndef CATExtCGMEventPublisher_h
#define CATExtCGMEventPublisher_h
//============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997  
//============================================================================

#include "CATCGMNewArray.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATCGMObject.h"
#include "CATCGMEventType.h"
#include "CATListOfCATCGMEvents.h"

class CATExtCGMEventPublisher
{
public :
  //---------------------------------------------------------------------------
  // Basics
  //---------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;

  CATExtCGMEventPublisher();
  ~CATExtCGMEventPublisher () ;  
  
  //---------------------------------------------------------------------------
  // Fonctionnalite.
  //---------------------------------------------------------------------------
  inline CATBoolean isEmpty() const;
  inline CATBoolean isSubscribed(const CATCGMEventType itp) const;
  void GetSubscribed(const CATCGMEventType itp,  CATLISTP(CATCGMEvents) & ioSubcribers) const;

  short AddSubscriber(CATCGMObject *iObj, CATCGMEvents *iEvent);
  short RemoveSubscriber(CATCGMObject *iObj, CATCGMEvents *iEvent);
 
  static int GetKey();

protected:
  CATLISTP(CATCGMEvents) _Subscribers;
  CATULONG32           _Types;

private:
  CATExtCGMEventPublisher (const CATExtCGMEventPublisher& from);
  CATExtCGMEventPublisher& operator= (const CATExtCGMEventPublisher& from);
};

//---------------------------------------------------------------------------
// isEmpty.
//---------------------------------------------------------------------------
inline CATBoolean CATExtCGMEventPublisher::isEmpty() const
{
  return (_Types == 0);
}

//---------------------------------------------------------------------------
// isSubscribed.
//---------------------------------------------------------------------------
inline CATBoolean CATExtCGMEventPublisher::isSubscribed(const CATCGMEventType itp) const
{
  return (_Types  & (CATULONG32 ) itp) ? TRUE : FALSE;
}

#endif
