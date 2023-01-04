/* -*-C++-*- */
/* COPYRIGHT DASSAULT SYSTEMES 1997                                      */
/*=======================================================================*/
#ifndef __CATThrMessage_var
#define __CATThrMessage_var

#include "CATThrMessage.h"
#ifdef _WINDOWS_SOURCE
#define CATThr__stdcall  __stdcall
#else
#define CATThr__stdcall  
#endif

#define NULL_Msg_var ((CATThrMessage_var)0)

class ExportedByJS0MT CATThrMessage_var
{
   public:
   CATThrMessage_var() ;
   ~CATThrMessage_var();
   CATThrMessage_var(CATThrMessage *ipt);
   CATThrMessage_var(const CATThrMessage_var &iref);
   CATThrMessage_var & CATThr__stdcall operator= (const CATThrMessage_var &iref);
   int CATThr__stdcall operator==(CATThrMessage *ipt) const ;
   int CATThr__stdcall operator!=(CATThrMessage *ipt) const;
   int CATThr__stdcall operator!() const;
   CATThr__stdcall operator CATThrMessage*() const;
   CATThrMessage * CATThr__stdcall operator->() const;
   CATThrMessage * CATThr__stdcall GetPointer() const;
   private:
   CATThrMessage *_Pointer;
};
#endif
