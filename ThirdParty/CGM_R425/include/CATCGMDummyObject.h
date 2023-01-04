#ifndef CATCGMDummyObject_H
#define CATCGMDummyObject_H
// COPYRIGHT DASSAULT SYSTEMES 2003
//==========================================================================
#include "LesBonnesRecettesDuPereLochard.h"
LesBonnesRecettesDuPereLochard(_DummyObject120209,"Use CATCGMDummyObject for non symetric allocation/destruction debug");
//
// CATCGMDummyObject: Dummy object with pool management for check symetric allocation/destruction and code 77 error generation
// Allows fast and easy debug of MLKs problems by turning them into code 77 problems
//==========================================================================
//
// Usage notes:
//
//    CreateCGMDummyObject((void*) this) ;// for instance in constructor. creates a dummy object associated to current object
//    ....
//    DeleteCGMDummyObject((void*) this) ;// for instance in destructor.  deletes a dummy object associated to current object
//
// test object will return with code 77 if destructor not called, and, thus, CATCGMDummyObject remaining 
// code77 to be debugged with usual tools (set CATCX_MEMORY=follow, breakpoint catcxfollow)
// 
//==========================================================================
// *** N.B Not optimized list scan; not to use in industrial context ***
// *** Debug purpose only                                            ***
//==========================================================================
// 26/07/06 NLD Creation
// 08/06/07 NLD Utilisation du systeme de debug des AddRef/Release par callbacks vers frameworks geometriques
//              Ajout AddRefCGMDummyObject() et ReleaseCGMDummyObject()
//              Ajout CATCGMDummyObject_Action
//              Ajout SetCGMDummyObjectCallBack()
// 21/06/07 NLD Ajout argument iDummyObject au CallBack
//==========================================================================
//
//
#include <CATMathematics.h>
#include <CATCGMNewArray.h>
#include <CATDataType.h>

class ExportedByCATMathematics CATCGMDummyObject
  {
   public :
   CATCGMDummyObject(void* iKeyPointer);
   ~CATCGMDummyObject();

   CATCGMNewClassArrayDeclare;

   protected : 
   void* _KeyPointer;
    
  };
typedef enum
  {
   CATCGMDummyObject_Create = 1,
   CATCGMDummyObject_AddRef,
   CATCGMDummyObject_Release,
   CATCGMDummyObject_Delete
  }CATCGMDummyObject_Action ;

extern "C" ExportedByCATMathematics void CreateCGMDummyObject(void* iKeyPointer) ;
extern "C" ExportedByCATMathematics void AddRefCGMDummyObject(void* iKeyPointer) ;
extern "C" ExportedByCATMathematics void ReleaseCGMDummyObject(void* iKeyPointer) ;
extern "C" ExportedByCATMathematics void CreateCGMDummyObject(void* iKeyPointer) ;
extern "C" ExportedByCATMathematics void DeleteCGMDummyObject(void* iKeyPointer) ;
// Donnees de callback
extern "C" ExportedByCATMathematics void SetCGMDummyObjectCallBack
  (void(*ReCall)(CATCGMDummyObject_Action Action,
                 void* iDummyObject,
                 void* iKeyPointer,
                 CATLONG32 icount,
                 void* iDataForCall
                )=NULL,
   void* ioDataForCall=NULL) ;
#endif

