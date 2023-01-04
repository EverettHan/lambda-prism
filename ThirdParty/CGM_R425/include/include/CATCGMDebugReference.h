// COPYRIGHT DASSAULT SYSTEMES 2003
//==========================================================================
//
// CATCGMDebugReference: Helps debug non symmetric AddRef/Release reference
//
// CATCGMDebugReference object will remain if mismatch between calls
// to CreateCGMDebugReference() and DeleteCGMDebugReference
//==========================================================================
//
// Usage notes:
//
// *** N.B Not optimized list scan; not to use in industrial context ***
// *** Debug purpose only                                            ***
//==========================================================================
// 11/06/07 NLD Creation
// 04/10/07 NLD FindCGMDebugReference() devient externe
// 12/02/09 NLD Ajout _ObjectCount
//              le constructeur recoit iObjectCount
//              _Count devient _RefCount
// 19/02/09 NLD Ajout CATCGMDebugReferenceErrorBreakPoint()
// 25/02/09 NLD Ajout FindAnyCGMDebugReference()
// 08/07/10 NLD Ajout _CumulatedRefCount
//==========================================================================
//
#ifndef CATCGMDebugReference_H
#define CATCGMDebugReference_H
//
#include <CATMathematics.h>
#include <CATCGMNewArray.h>
#include <CATDataType.h>

class ExportedByCATMathematics CATCGMDebugReference
  {
   public :
   CATCGMDebugReference(void* iReferenced  ,
                        void* iReferencing = NULL,
                        int   iObjectCount = 0,
                        int   iEventCount  = 0);
   ~CATCGMDebugReference();

   CATCGMNewClassArrayDeclare;

   public : 
   void                * _Referenced;
   void                * _Referencing;
   CATCGMDebugReference* _Next ;
   CATCGMDebugReference* _Prev ;
   int                   _RefCount;             // designe le compteur de references en cours a cet objet
   int                   _ObjectCount;          // designe le numero de l'objet
   int                   _EventCount;           // designe le numero d'evenement a la creation de l'objet
   int                   _CumulatedRefCount;    // designe le compteur de references cumule a cet objet    
  };
// Creation of reference of one object on another object
// (Implementation allowing management of several identical references)
extern "C" ExportedByCATMathematics void                  CreateCGMDebugReference (void* iReferenced, void* iReferencing = NULL) ;
// Destruction of reference of one object on another object
extern "C" ExportedByCATMathematics void                  DeleteCGMDebugReference (void* iReferenced, void* iReferencing = NULL) ;
// Find any reference
extern "C" ExportedByCATMathematics CATCGMDebugReference* FindAnyCGMDebugReference(void* iReferenced) ;
// Find of a reference
extern "C" ExportedByCATMathematics CATCGMDebugReference* FindCGMDebugReference   (void* iReferenced, void* iReferencing) ;
// BreakPoint at error creation or flush
// iCreate=1 for error creation, 0 for error flush
extern "C" ExportedByCATMathematics void                  CATCGMDebugReferenceErrorBreakPoint(int iCreate=1, int iForceTrace=0);

#endif

