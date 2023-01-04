#ifndef CATSysSHProtocol_H
#define CATSysSHProtocol_H
// COPYRIGHT DASSAULT-SYSTEMES 2003

#include "IUnknown.h"
#include "CATISysSockProtocols.h"
class CATSockets;


class ExportedByJS0MT CATSysSHProtocol  : public CATISysSockProtocols
{
public:
   CATSysSHProtocol();
   /*virtual*/ const char *GetProtocolId() override;
   /*virtual*/ CATSysSPResult Check(CATISysSockProtocolRq *iReq , CATSysSPOperation iOperation) override;

   /** 
    * for Protocol Send Message 
    **/

   /*virtual*/ CATSysSPResult StartSend(CATSockets *iSock,CATISysSockProtocolRq *iReq, int *oActionFlag, void **oBuffer, unsigned int *oLength, void **oBlackBox) override;

   /*virtual*/ CATSysSPResult Send(CATSockets *iSock, CATISysSockProtocolRq *iReq, int *ioActionFlag, void **ioBuffer, unsigned int *ioLength, void **ioBlackBox, int iPart) override;

   /*virtual*/ CATSysSPResult EndSend(CATSockets *iSock, CATISysSockProtocolRq *iReq, int *ioActionFlag, void **ioBuffer, unsigned int *ioLength, void **ioBlackBox, int iPart) override;

   /*virtual*/ CATSysSPResult ReleaseData(int iAction, void ** iBuffer, void ** iBlackBox, int iPart) override;

   /**
    * for Protocol Receive Message 
    **/
   /*virtual*/ CATSysSPResult Receive(CATSockets *, CATISysSockProtocolRq **ioReq, int *oActionFlag, CATSocketResult *oSocketResu) override;

   /**
     * for Protocol Connect 
    **/
   /*virtual*/ CATSysSPResult PreConnect(CATSockets *, CATISysSockProtocolRq *iReq,  int *oActionFlag, char *oHostName, unsigned short *oPort) override;
   /*virtual*/ CATSysSPResult PostConnect(CATSockets *, CATISysSockProtocolRq *iReq, int *oActionFlag) override;

   /** 
    * for protocol close
    **/
   /*virtual*/ CATSysSPResult Close(CATSockets *, int iAlreadyClosed) override;


   /**
    ** tells to CATSockets the wait policy of the protocol
    **/
   /*virtual*/ CATSysSPResult CheckPolicy (CATSysSPPolicy iFlags) override;

   /**
    ** must be implemented to replace the wait
    **/
   /*virtual*/ CATSysSPResult Wait(int /*iTimeOutMS*/, CATISysSockProtocolRq */*iReq*/ = NULL, CATSockets */*iSock*/ = NULL ) override { return CATSysSPResForbidden; };

   /*virtual*/ CATSysSPResult Operate(CATISysSockProtocolRq */*iReq*/ = NULL, int /*iFlag*/ = 0, void */*ioData*/ = NULL ) override { return CATSysSPResForbidden; };


   CATSysSPDeclare
 
   static const char *GetTheProtocolId();
};


#endif

