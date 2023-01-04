#include "CATThrowForNullPointer.h"
#include "CATString.h"
#include "CATAssert.h"

// ---------- Constructors, destructors

CATCGM_ITF_IMPL_CLASS::CATCGM_ITF_IMPL_CLASS(CATCGM_ITF_CONCRETE_CLASS &iHandledObject, CATCGMItfDestrBehavior iItfDestrBehavior)
{
  _RefCnt = 1;
  _InternalData.Initialize(*this, iHandledObject, iItfDestrBehavior);

#ifdef CATCGM_ITF_CGMVirtualConstructorCompl
  CATCGM_ITF_CGMVirtualConstructorCompl;
#endif
}

CATCGM_ITF_IMPL_CLASS::CATCGM_ITF_IMPL_CLASS(CATCGMVirtualItf &iPreviousItf)
{
  _RefCnt = 1;
  _InternalData.Initialize(*this, iPreviousItf);
}

CATCGM_ITF_IMPL_CLASS::~CATCGM_ITF_IMPL_CLASS()
{
  CATCGM_ITF_CONCRETE_CLASS *pHandledObjectToDel = NULL;
  _InternalData.Remove(*this, (CATCGMVirtual *&)pHandledObjectToDel);
  if (pHandledObjectToDel != NULL)
  {
#ifdef CATCGM_ITF_IMPL_REMOVE_OBJ
    // If no Remove() exists for your operator, please remove #define CATCGM_ITF_IMPL_REMOVE_OBJ
    // in CATICGMxxxImpl.cpp and/or CATIPGMxxxImpl.cpp.
    // The following "# make-ERROR:" indicates which source you have to modify.
    Remove(pHandledObjectToDel);
#else
    delete (CATCGMVirtual *)pHandledObjectToDel; // OVERRIDEN IN CATEnergyDeformableModel
#endif
    pHandledObjectToDel = NULL;
  }
}

CATCGMVirtualItf *CATCGM_ITF_IMPL_CLASS::MakeRootItf(CATCGMVirtual &iHandledObject, CATCGMItfDestrBehavior iItfDestrBehavior)
{
  return new CATCGM_ITF_IMPL_CLASS((CATCGM_ITF_CONCRETE_CLASS &)iHandledObject, iItfDestrBehavior);
}

CATCGMVirtualItf *CATCGM_ITF_IMPL_CLASS::MakeLinkedItf(CATCGMVirtualItf &iPreviousItf)
{
  return new CATCGM_ITF_IMPL_CLASS(iPreviousItf);
}

// ---------- IUnknown

HRESULT __stdcall CATCGM_ITF_IMPL_CLASS::QueryInterface(const IID &iIID, void **oPPV)
{
  return _InternalData.OwnerQueryInterface(*this, iIID, oPPV);
}

ULONG __stdcall CATCGM_ITF_IMPL_CLASS::AddRef()
{
  _RefCnt++;
  return _RefCnt;
}

ULONG __stdcall CATCGM_ITF_IMPL_CLASS::Release()
{
  _RefCnt--;
  if (_RefCnt == 0)
  {
     delete this;
     return 0;
  }
  return _RefCnt;
}

// ---------- CATCGMVirtualItf

CATCGMItfInternalData &CATCGM_ITF_IMPL_CLASS::GetInternalData()
{
  return _InternalData;
}

#ifndef CATCGM_ITF_PARENT_ITF_METACLASS

CATCGMItfMetaClass CATCGM_ITF_IMPL_CLASS::_ItfMetaClass(
  CATCGM_ITF_CLASS_IID,
  NULL, // Root interface
  CATCGM_ITF_CONCRETE_CLASS::CATCGM_ITF_CONCRETE_METACLASS(),
  CATCGM_ITF_IMPL_CLASS::MakeRootItf,
  CATCGM_ITF_IMPL_CLASS::MakeLinkedItf);

#else

CATCGMItfMetaClass CATCGM_ITF_IMPL_CLASS::_ItfMetaClass(
  CATCGM_ITF_CLASS_IID,
  &CATCGM_ITF_PARENT_ITF_METACLASS(),
  CATCGM_ITF_CONCRETE_CLASS::CATCGM_ITF_CONCRETE_METACLASS(),
  CATCGM_ITF_IMPL_CLASS::MakeRootItf,
  CATCGM_ITF_IMPL_CLASS::MakeLinkedItf);

#endif

const CATCGMItfMetaClass &CATCGM_ITF_IMPL_CLASS::CATCGM_ITF_METACLASS()
{
  return _ItfMetaClass;
}

const CATCGMItfMetaClass &CATCGM_ITF_IMPL_CLASS::GetItfMetaClass() const
{
  return _ItfMetaClass;
}
