#ifndef CATCGMAttrInstance_H
#define CATCGMAttrInstance_H
// COPYRIGHT DASSAULT SYSTEMES  2001
//============================================================================
//  For Performance improvement on Pattern Replicated Objects management
//============================================================================
#include "CATCGMAttribute.h"
#include "YP0LOGRP.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"
#include "CATICGMObject.h"
#include "CATCGMInstance.h"

class ExportedByYP0LOGRP CATCGMAttrInstance : public CATCGMAttribute
{
public :
  CATCGMDeclareAttribute(CATCGMAttrInstance,CATCGMAttribute);
  CATCGMNewClassArrayDeclare;
//------------------------------------------------------------------------------
// Create an Instance Attribut
//------------------------------------------------------------------------------
public:
  static CATCGMAttrInstance *Create(CATICGMObject * iOwner,CATICGMObject * iReference=NULL, CATCGMInstance * iInstance=NULL);
  static CATCGMAttrInstance *GetInstanceLink     (CATICGMObject * iOwner);
  
  void   DumpChain();

  //------------------------------------------------------------------------------
  // Create Reference
  //------------------------------------------------------------------------------
protected:
  static CATCGMAttrInstance *CreateInstanceLink  (CATICGMObject * iOwner);
 
  //------------------------------------------------------------------------------
  // Set Linked Objects
  //------------------------------------------------------------------------------
  HRESULT    Set (CATICGMObject * iReference, CATCGMInstance * iInstance );
  
  //------------------------------------------------------------------------------
  // Linked Objects
  //------------------------------------------------------------------------------
public:
  INLINE     CATICGMObject  * GetReference();
  INLINE     CATICGMObject  * GetOwner    ();
  INLINE     CATCGMInstance * GetInstance ();

private:
  //------------------------------------------------------------------------------
  // Chain Management
  //------------------------------------------------------------------------------
  INLINE     CATCGMAttrInstance *Get_Reference_Prev ();
  INLINE     CATCGMAttrInstance *Get_Reference_Next ();

protected:
  CATCGMAttrInstance(CATICGMObject * iOwner=NULL);
  virtual ~CATCGMAttrInstance();
  
private:
  void InsertInChain(CATCGMAttrInstance * iPtr);
  void RemoveFromChain(); 
  void CleanUp(); 
 
private :
  CATCGMAttrInstance (const CATCGMAttrInstance & );//Necessary to prevent unwanted automatic creation by compiler
  void operator = (const CATCGMAttrInstance&);

private :
  CATICGMObject       * _Owner;
  CATICGMObject       * _Reference;
  CATCGMInstance      * _Instance;
  
  CATCGMAttrInstance  * _Attr_Prev; 
  CATCGMAttrInstance  * _Attr_Next;
};
//---------------------------------------------------------------------------------
INLINE   CATICGMObject  * CATCGMAttrInstance::GetReference() { return _Reference; }
INLINE   CATICGMObject  * CATCGMAttrInstance::GetOwner    () { return _Owner; }
INLINE   CATCGMInstance * CATCGMAttrInstance::GetInstance () { return _Instance; }
//---------------------------------------------------------------------------------
INLINE   CATCGMAttrInstance * CATCGMAttrInstance::Get_Reference_Prev() { return _Attr_Prev; }
INLINE   CATCGMAttrInstance * CATCGMAttrInstance::Get_Reference_Next() { return _Attr_Next; }

#endif

