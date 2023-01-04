#ifndef CATFedEx_H
#define CATFedEx_H
/**
* @quickReview NLD 08:02:04
* @fullReview NLD 08:02:04
*/
// COPYRIGHT DASSAULT SYSTEMES 2008
//=============================================================================
//
// CATFedEx : General mail stack management for temporary data transmission
//
// FedEx: Distinguished fast and secured mail transmission
//
// A tribute to Roger Federer Express
//=============================================================================
// Usage notes:
//  
//  dedicated to data transmission to non modifiable CAA objects
//  or data transmission in hotfix environment
// 
// sample of use :
//
//   see dedicated mail boxes such as CTAR19CGMMail
//  
//=============================================================================
// 04/02/08 NLD Creation
// 29/01/09 NLD Ajout _Fedex_FirstFree pour optimisation
//=============================================================================
#include <CATMathematics.h>


typedef enum
  {
   CATFedEx_NoMail,
   CATFedEx_NotRead,
   CATFedEx_Read
  } CATFedEx_MailStatus ;

class ExportedByCATMathematics CATFedEx
  {
   private :
   //copy  constructor  
   CATFedEx(const CATFedEx&  iToCopy);  
   //  and operator =
   CATFedEx  &operator=(CATFedEx& iToCopy);  

   public :

   CATFedEx();
   ~CATFedEx();

   // Put mail on top of mailbox with ident, sender and receiver, and optional related data
   // iFrom: mail sender
   // iTo  : mail receiver
   // iData: mail data
   void Put(int iIdent, void* iFrom, void* iTo, void* iData) ;

   // Search mail in mail box stack from its ident and receiver
   // iPreview=1 : mail will remain unread
   int Get(int iIdent, void* iTo, int iPreview,
            void*& oFrom, void*& oData, CATFedEx_MailStatus& oStatus) ;

   // Empty stack until mail given by ident and sender 
   void UnstackUntil(int iIdent, void* iFrom) ;

   private : 
   void* _Fedex_First ;
   void* _Fedex_Last ;
   void* _Fedex_FirstFree ;
   int _Dump ;
   
   void Dump(char* texte) ;
  } ;

// static default mail stack
extern ExportedByCATMathematics CATFedEx _FedEx_DefaultMailBox ;

#define CATFedex_DefaultMailIdent 0

#endif
