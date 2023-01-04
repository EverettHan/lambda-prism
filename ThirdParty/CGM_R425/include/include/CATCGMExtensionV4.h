// COPYRIGHT Dassault Systemes 2001
//===================================================================
//
// CATCGMExtensionV4.h Header definition of CATCGMExtensionV4
//
//===================================================================
//
// Usage notes: Default extension for CATGeometry Classes 
//               BUT Methods are not implemented
// CATGeometryV4 inherits from this class
//
//===================================================================
//
//  Nov 2001  Creation: Code generated by the CAA wizard  HCN
//===================================================================
#ifndef CATCGMExtensionV4_H
#define CATCGMExtensionV4_H

#include "YP00IMPL.h"
#include "CATCGMExtGeometry.h"
#include "CATCGMNewArray.h"

class ExportedByYP00IMPL CATCGMExtensionV4: public CATCGMExtGeometry
{
  
protected :
  
  //--------------------------------------------------------------------------------
  //  GetNativeInterface : A SURCHARGER IMPERATIVAMENT AVEC UN CODE DU STYLE :
  /*
    CATBaseUnknown *CATCartesianPointV4::GetNativeInterface() const
    {
      return RequiredNativeInterface(IID_CATCartesianPoint);
    }
  */
  //--------------------------------------------------------------------------------
  virtual  CATBaseUnknown *GetNativeInterface() const;
  

  CATBaseUnknown *RequiredNativeInterface(const IID & iNativeInterface) const;
  
  
public:
  
  CATDeclareClass;
  
  // Standard constructors and destructors
  // -------------------------------------
  CATCGMExtensionV4();
  virtual ~CATCGMExtensionV4();
  
  
  //-----------------------------------------------------------------------
  //  Surcharge de methodes  de CATBaseUnknown 
  //    AddRef, GetImpl : pour PERFOS
  //    Release         : pour PERFOS + pour controler les Release abusifs
  //    IsNull          : pour dire qu'un objet apres Clear est considere
  //                      comme detruit.
  //----------------------------------------------------------------------
  virtual ULONG           __stdcall AddRef();
  virtual ULONG           __stdcall Release();  
  virtual CATBaseUnknown* __stdcall GetImpl(int iFlag = 0) const;
  virtual int                       IsNull() const;
  virtual HRESULT         __stdcall QueryInterface(const IID &iid,void **ppv);
  virtual CATBaseUnknown*           QueryInterface(CATClassId iInterface) const;
  
  
private :
  CATBaseUnknown *_NativeInterface;
  IID             _InterfaceIID;
};

//-----------------------------------------------------------------------

#endif