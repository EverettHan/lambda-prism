#ifndef CATThrMessage_H
#define CATThrMessage_H


// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CATMutex.h"
#include "CATDataType.h"
typedef CATLONG32 CATThrResult;
#define CATThrResult CATLONG32

#define CATThrExported DSYExport
#include "DSYExport.h"

#define CATImplementMsgClass( NewMsgClass, ParentMsgClass )  \
extern "C" CATThrExported NewMsgClass * CATThrMsgCreate##NewMsgClass() { return new NewMsgClass();} \
const char  * NewMsgClass::ClassName() { return #NewMsgClass ;} \
const char  * NewMsgClass::IsA() { return NewMsgClass::ClassName() ;} \
int        NewMsgClass::IsAKindOf(const char *iIsA) { \
      if ( ClassName() == iIsA ) return -1; \
      else return ParentMsgClass::IsAKindOf(iIsA) ;  } 

#define CATDeclareMsgClass \
  static const char *ClassName();            \
  virtual const char *IsA();            \
  virtual const char * GetLoadName();  \
  virtual int IsAKindOf(const char *);            \
  virtual CATThrResult StreamData( void **oBuffer , CATLONG32 *oLong);\
  virtual CATThrResult UnstreamData( const void  *iBuffer,  CATLONG32 iLong)

class ExportedByJS0MT CATThrMessage
{
  public:

  CATDeclareMsgClass;

  CATThrMessage();
  virtual ~CATThrMessage();
  virtual  CATULONG32 AddRef();
  virtual  CATULONG32 Release();
  virtual CATThrResult Stream( void **oBuffer , CATLONG32 *oLong);
  virtual CATThrResult Unstream( const  void *iBuffer,  CATLONG32 iLong);
  void SetVersion(unsigned short iVerNumer);
  void GetVersion(unsigned short &oVerNumer);
  private:
  CATLONG32 _Counter;
  unsigned short _VerNumber; /** @win64 fbq : 64-bit structure padding **/
  CATMutex _CounterLocker;
};
#include "CATThrMessage_var.h"
#endif
