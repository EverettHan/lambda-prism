#ifndef __CATBaseUnknown_var
#define __CATBaseUnknown_var

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include <stdio.h>
#include "CATBaseUnknown.h"

/**
 * @nodoc
 */
typedef IUnknown *  IUnknown_ptr;

/**
 * @nodoc
 */
#define NULL_var (static_cast<CATBaseUnknown*>(nullptr))

/**
 * Base class for handler.
 * <b>Role</b>: Base class for the CORBA's object reference variable type for an
 * interface, also known as handler, and smart interface pointer with COM.
 */
class ExportedByJS0CORBA CATBaseUnknown_var
{
   public:
/**
 * Constructs an empty handler. 
 */
      inline CATBaseUnknown_var();

      inline ~CATBaseUnknown_var();

/**
 * Constructs a handler from a pointer.
 * @param iPtr The pointer to the @href CATBaseUnknown instance to use. 
 */
      inline CATBaseUnknown_var(CATBaseUnknown * iPtr);

/**
 * Copy constructor.
 * @param iRef The reference of the CATBaseUnknown_var instance to copy.
 */
      inline CATBaseUnknown_var(const CATBaseUnknown_var & iRef);

/**
 * Assignment operator from CATBaseUnknown_var reference.
 * @param iRef The reference of the CATBaseUnknown_var instance to copy.
 * @return The reference of the CATBaseUnknown_var instance valued.
 */
      CATBaseUnknown_var & __stdcall operator=(const CATBaseUnknown_var & iRef);

      // Comparison operators
/**
 * Equality operator.
 * @param iPt A pointer to a @href CATBaseUnknown to compare.
 * @return
 * <b>Legal values</b>:
 * <dl>
 * <dt>0</dt><dd> The handler and iPt are pointing the same object</dd>
 * <dt>1</dt><dd> The handler and iPt are not pointing the same object</dd>
 * </dl>
 */
      int __stdcall operator==(CATBaseUnknown *iPt) const;
/**
 * Inequality operator.
 * @param iPt Pointer to be compared with the internal pointer.
 * @return
 * <b>Legal values</b>:
 * <dl>
 * <dt>0</dt><dd> The handler and iPt are not pointing the same object</dd>
 * <dt>1</dt><dd> The handler and iPt are pointing the same object</dd>
 * </dl>
 */
      int __stdcall operator!=(CATBaseUnknown *iPt) const;

/**
 * Logical not operator.
 * @return
 * <b>Legal values</b>:
 * <dl>
 * <dt>0</dt><dd> The handler points on a valid object</dd>
 * <dt>1</dt><dd> The handler does not point on a valid object</dd>
 * </dl>
 */
      int __stdcall operator!() const;

/**
 * Type cast operator to a CATBaseUnknown instance pointer.
 */
      inline __stdcall operator CATBaseUnknown*() const;

/**
 * Pointer to member operator.
 */
      inline CATBaseUnknown * __stdcall operator->() const;

/**
 * For illegal operation.
 */
      void ThrowErrorNullVar() const;
   protected:
/**
 * @nodoc
 */
      void __stdcall CastTo(IUnknown *ipt, const GUID &guid);

#ifdef _WINDOWS_SOURCE
/**
 * @nodoc Windows-only to make sure apps don't call this nodoc member function
 */
      IUnknown * __stdcall GetPointer() const;
#endif

   private:
/**
 * @nodoc
 */
      IUnknown *pointer;
};

/**
 * @nodoc
 */
inline CATBaseUnknown_var::CATBaseUnknown_var() : pointer(nullptr)
{
  //CATINSTRUM_CONST( CATBaseUnknown_var);
}
inline CATBaseUnknown_var::~CATBaseUnknown_var()
{
  //CATINSTRUM_DEST( CATBaseUnknown_var);
  if (pointer) pointer->Release();
  pointer = nullptr;
}
inline CATBaseUnknown_var::CATBaseUnknown_var(CATBaseUnknown * iPtr): pointer(iPtr)
{
  //CATINSTRUM_CONST( CATBaseUnknown_var);
  if (pointer) pointer->AddRef();
}
inline CATBaseUnknown_var::CATBaseUnknown_var(const CATBaseUnknown_var & iRef): pointer(iRef.pointer)
{
  //CATINSTRUM_CONST( CATBaseUnknown_var);
  if (pointer) pointer->AddRef();
}
inline __stdcall CATBaseUnknown_var::operator CATBaseUnknown*() const
{
  return((CATBaseUnknown *)pointer);
}
inline CATBaseUnknown * __stdcall CATBaseUnknown_var::operator->() const
{
  if (!pointer)
    {
      ThrowErrorNullVar();
    }
  return((CATBaseUnknown *)pointer);
}


/**
 * @nodoc
 */
class ExportedByJS0CORBA IUnknown_var : public CATBaseUnknown_var
{
   private:
      void __CastTo(IUnknown*pt);
   public:
      inline IUnknown_var();
      inline IUnknown_var(CATBaseUnknown *base);
      inline IUnknown_var(IUnknown *base);
      inline ~IUnknown_var();
      inline IUnknown_var(const CATBaseUnknown_var &base);
      inline IUnknown_var(const IUnknown_var &base);
      inline IUnknown * __stdcall operator->() const;
      inline __stdcall operator IUnknown *() const;
      inline IUnknown_var& __stdcall operator=(const CATBaseUnknown_var &base);
      inline IUnknown_var & __stdcall operator=(const CATBaseUnknown *base);
};

/**
 * @nodoc
 */
inline IUnknown_var::IUnknown_var() {}
inline IUnknown_var::IUnknown_var(CATBaseUnknown *base) : CATBaseUnknown_var(base) {}
inline IUnknown_var::IUnknown_var(IUnknown *base) : CATBaseUnknown_var((CATBaseUnknown*)base) {}
inline IUnknown_var::~IUnknown_var() {}
inline IUnknown_var::IUnknown_var(const CATBaseUnknown_var &base) : CATBaseUnknown_var()
{
  __CastTo((IUnknown *)base);
}
inline IUnknown_var::IUnknown_var(const IUnknown_var &base) : CATBaseUnknown_var((CATBaseUnknown*)base)
{
  __CastTo((CATBaseUnknown *)base);
}
inline IUnknown * __stdcall IUnknown_var::operator->() const
{
  return((IUnknown *)CATBaseUnknown_var::operator->());
}
inline __stdcall IUnknown_var::operator IUnknown *() const
{
#ifdef _WINDOWS_SOURCE
  return((IUnknown *)CATBaseUnknown_var::GetPointer());
#else
  return((IUnknown *)CATBaseUnknown_var::operator CATBaseUnknown *());
#endif
}
inline IUnknown_var& __stdcall IUnknown_var::operator=(const CATBaseUnknown_var &base)
{
  __CastTo((IUnknown *)base);
  return(*this);
}
inline IUnknown_var & __stdcall IUnknown_var::operator=(const CATBaseUnknown *base)
{
  __CastTo((IUnknown *)base);
  return(*this);
}

/**
 * @nodoc
 */
typedef IUnknown *IUnknown_ptr;


/**
 * @nodoc
 */
class ExportedByJS0CORBA IDispatch_var : public IUnknown_var
{
   private:
      void __CastTo(IUnknown*pt);
   public:
      inline IDispatch_var();
      inline IDispatch_var(CATBaseUnknown *base);
      inline IDispatch_var(IDispatch *base);
      inline ~IDispatch_var();
      inline IDispatch_var(const IDispatch_var &base);
      inline IDispatch_var(const CATBaseUnknown_var &base);
      inline IDispatch * __stdcall operator->() const;
      inline __stdcall operator IDispatch *() const;
      inline IDispatch_var& __stdcall operator=(const CATBaseUnknown_var &base);
      inline IDispatch_var & __stdcall operator=(const CATBaseUnknown *base);
};

/**
 * @nodoc
 */
inline IDispatch_var::IDispatch_var() {}
inline IDispatch_var::IDispatch_var(CATBaseUnknown *base) : IUnknown_var(base) {}
inline IDispatch_var::IDispatch_var(IDispatch *base):IUnknown_var((IUnknown*)base) {}
inline IDispatch_var::~IDispatch_var() {}
inline IDispatch_var::IDispatch_var(const IDispatch_var &base) : IUnknown_var((CATBaseUnknown *)base)
{
  __CastTo((CATBaseUnknown *)base);
}
inline IDispatch_var::IDispatch_var(const CATBaseUnknown_var &base) : IUnknown_var()
{
  __CastTo((IUnknown *)base);
}
inline IDispatch * __stdcall IDispatch_var::operator->() const
{
  return((IDispatch *)CATBaseUnknown_var::operator->());
}
inline __stdcall IDispatch_var::operator IDispatch *() const
{
#ifdef _WINDOWS_SOURCE
  return((IDispatch *)CATBaseUnknown_var::GetPointer());
#else
  return((IDispatch *)CATBaseUnknown_var::operator CATBaseUnknown *());
#endif
}
inline IDispatch_var& __stdcall IDispatch_var::operator=(const CATBaseUnknown_var &base)
{
  __CastTo((IUnknown *)base);
  return(*this);
}
inline IDispatch_var & __stdcall IDispatch_var::operator=(const CATBaseUnknown *base)
{
  __CastTo((IUnknown *)base);
  return(*this);
}

/**
 * @nodoc
 */
typedef IDispatch *IDispatch_ptr;


/**
 * @nodoc
 * for interfaces migration
 */
typedef CATBaseUnknown_var CATInterfaceObject_var;

#endif
