/* -*-c++-*- */
#ifndef CATMacBuildCGM_H
#define CATMacBuildCGM_H
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// Macro pour les objets CGM
//
//=============================================================================
//
// Usage notes:
//
//   Ces macros doivent etre appelee dans le constructeur par defaut de tout objet CGM
//   
//   si votre classe implemente l'interface native :
//         CATMacBuildCGM( implementation , interface )
//   si une extension implemente l'interface native :
//         CATMacBuildCGM( extension , interfac )
//
//=============================================================================
// Jun.  97 RR,                                                       R. Rorato
//          RAD Creation                                              R. Aymard
// Mar.  98 RAD Ajout du Asked_Interface
//              Le Asked_Interface est tres important , sa remise a NULL aussi
//                                                         dixit lme.
//-----------------------------------------------------------------------------
// Dec.  98 RAD Enlevement du Asked_Interface
//              Ca marchera pas en V5R2 et il n'y en a plus besoin en V5R1
//                                                         dixit lme (le meme)
//-----------------------------------------------------------------------------
// Jan.  99 RAD Cast car CreateTIExxx retourne un IUnknown
//              Tu casses tout au build en CXR2
//                                                         dixit lme & smm
//-----------------------------------------------------------------------------
// Jun.  99 RAD Une nouvelle Macro pour les TIE car entre 
//              chain et pas chain, mon coeur balance
//-----------------------------------------------------------------------------
// 02/03/21 NLD Mise au propre
//=============================================================================
//
// Notes :
//
//   Un CreateTIExxx cree le tie avec m_cRef=1 (compteur de ref System)
//   Les compteurs sur implementation (eventuellement extension) sont mis a jour
//
//
//
//=============================================================================
class CATBaseUnknown;
#include "CATCGMObject.h"
#include "CATCGMCompactObject.h"
#include "CATCGMNewArray.h"
#include "CATCGMBOAObject.h"
#include "CATMathInline.h"
#include "CATIAV5Level.h"

// ------------ DECLARE ----------------
#define TIE_CGM_DECLARE(CGMitf,CGMimpl)                                                 \
class TIECGM##CGMitf: public CGMitf                                                     \
{                                                                                       \
 private:                                                                               \
  static CATBaseUnknown * ptstat;                                                       \
 public:                                                                                \
                                      TIECGM##CGMitf(CATBaseUnknown *pt      = NULL,    \
                                                     CATBaseUnknown *delegue = NULL);   \
  virtual                            ~TIECGM##CGMitf();                                 \
          CATCGMNewClassArrayDeclare;                                                   \
          CATBaseUnknown  * __stdcall GetImpl       (int             iFlag   = 0) const \
        { return (CATBaseUnknown*) this;};                                              \
  virtual ULONG             __stdcall AddRef        ();                                 \
  virtual ULONG             __stdcall Release       ();                                 \
  virtual HRESULT           __stdcall QueryInterface(const IID      &iid     ,          \
                                                           void    **ppv     );         \
  virtual CATBaseUnknown *            QueryInterface(CATClassId      iInterface)  const;\
          CATDeclareClass;                                                              \
          ENVTIEdeclare_##CGMitf(TIECGM##CGMitf,CGMimpl,_CGM_object);                   \
  INLINE  CGMimpl        *            GetData       ()                                  \
        { return (CGMimpl *) &_CGM_object;};                                            \
                                                                                        \
          CGMimpl                     _CGM_object;                                      \
        };



// ------------ REDEFINE ------------------------------------------------------
//   For evalution of CATImplementClass of TIECGM derivated from Interface  
//      without side effect of overloaded  IsA() / ClassName()
// ---------------------------------------------------------------------------
#define CATCGMBOAImplementClass(Class,Typeofclass,Basemeta,Impmeta)                 \
                                                                                    \
CATMetaClass * __stdcall Class::GetMetaObject() const                               \
{                                                                                   \
   return(meta_object?meta_object:MetaObject());                                    \
}                                                                                   \
                                                                                    \
const CLSID & __stdcall Class::ClassId()                                            \
{                                                                                   \
   return(meta_object?meta_object->GetClassId():MetaObject()->GetClassId());        \
}                                                                                   \
                                                                                    \
const char * __stdcall Class::ClassName()                                           \
{                                                                                   \
   return (meta_object?meta_object->IsA():MetaObject()->IsA());                     \
}                                                                                   \
                                                                                    \
const char *Class::IsA() const                                                      \
{                                                                                   \
   return(meta_object ?(meta_object->GetMetaObjectOfBaseClass() ? (meta_object->GetMetaObjectOfBaseClass())->IsA()\
                                                                :  meta_object->IsA()) \
                      : MetaObject()->IsA());                                       \
}                                                                                   \
                                                                                    \
int Class::IsAKindOf(const char *ident) const                                       \
{                                                                                   \
   return(meta_object ? meta_object->IsAKindOf(ident)                               \
                      : MetaObject()->IsAKindOf(ident));                            \
}                                                                                   \
                                                                                    \
CATBaseUnknown *Class::CreateItself()                                               \
{                                                                                   \
   MacCreate##Typeofclass(Class)                                                    \
}                                                                                   \
                                                                                    \
CATMetaClass * __stdcall Class::MetaObject()                                        \
{                                                                                   \
   /* function that finds a meta-object */                                          \
   ExportedByJS0CORBA CATMetaClass *fct_FindMetaObject    (const char *);           \
                                                                                    \
   /* function that creates a meta-object */                                        \
   ExportedByJS0CORBA CATMetaClass *fct_RetrieveMetaObject(const char         *,    \
                                                                 TypeOfClass   ,    \
                                                                 CATMetaClass *,    \
                                                           const char         *,    \
                                                           const char         *,    \
                                                                 long          );   \
                                                                                    \
   if (!meta_object)                                                                \
   {                                                                                \
      ToCreateMetaObject(Class,Typeofclass,Basemeta,Impmeta);                       \
   }                                                                                \
   return(meta_object);                                                             \
}                                                                                   \
                                                                                    \
CATMetaClass *Class::meta_object = NULL


// ------------ DEFINE ----------------
#define TIE_CGM_DEFINE(CGMitf,CGMimpl)                                              \
CATBaseUnknown *TIECGM##CGMitf::ptstat = NULL;                                      \
CATCGMBOAImplementClass(TIECGM##CGMitf,Implementation,CGMitf,CATNull);              \
                                                                                    \
TIECGM##CGMitf::TIECGM##CGMitf(CATBaseUnknown *pt,CATBaseUnknown *delegue)          \
{                                                                                   \
  MetaObject();                                                                     \
  _CGM_object.SetInterface(this);                                                   \
}                                                                                   \
                                                                                    \
TIECGM##CGMitf::~TIECGM##CGMitf()                                                   \
{                                                                                   \
}                                                                                   \
                                                                                    \
ULONG __stdcall TIECGM##CGMitf::AddRef()                                            \
{                                                                                   \
    _CGM_object.CheckAddRef(m_cRef);                                                \
    return( m_cRef++ );                                                             \
}                                                                                   \
                                                                                    \
ULONG __stdcall TIECGM##CGMitf::Release()                                           \
{                                                                                   \
   _CGM_object.CheckRelease(m_cRef);                                                \
   if (m_cRef > 1 )                                                                 \
      return (m_cRef--);                                                            \
   else                                                                             \
   {                                                                                \
      _CGM_object.CheckEndOfLife(m_cRef);                                           \
      return CATBaseUnknown::Release();                                             \
   }                                                                                \
}                                                                                   \
                                                                                    \
HRESULT   __stdcall TIECGM##CGMitf::QueryInterface(const IID &iid,void **ppv)       \
{                                                                                   \
   HRESULT rc =  _CGM_object.QueryInterface(iid, ppv);                              \
   if ( rc == S_OK )                                                                \
      return rc;                                                                    \
   else                                                                             \
      return Tie_Query(this, NULL, NULL, MetaObject(), 1, iid, ppv);                \
}                                                                                   \
                                                                                    \
CATBaseUnknown *  TIECGM##CGMitf::QueryInterface(CATClassId iInterface) const       \
{                                                                                   \
   return _CGM_object.QueryInterface(iInterface);                                   \
}                                                                                   \
                                                                                    \
ENVTIEdefine_##CGMitf(TIECGM##CGMitf,CGMimpl ,_CGM_object);                         \
extern "C" Exported IUnknown *CreateTIECGM##CGMitf(CATBaseUnknown *pt      = NULL,  \
                                                   CATBaseUnknown *delegue = NULL)  \
{                                                                                   \
   if ( pt && delegue)                                                              \
   {                                                                                \
      CATBaseUnknown* result = NULL;                                                \
      pt->QueryInterface( CGMitf::MetaObject()->GetClassId(),                       \
                          (void **)&result);                                        \
      if (result)                                                                   \
      {                                                                             \
         result->AddRef();                                                          \
         return result;                                                             \
      }                                                                             \
   }                                                                                \
   return((IUnknown *) new TIECGM##CGMitf(pt, delegue));                            \
}                                                                                   \
                                                                                    \
static CATFillDictionary Dic##CGMitf##CGMimpl(TIECGM##CGMitf::MetaObject(),         \
                                              CGMitf::MetaObject        (),         \
                                             (void *)CreateTIECGM##CGMitf);

 

#if defined ( CATCGMCompactObject )

#define CATMacBuildCGM( implementation , interfac )                                                  \
{                                                                                                    \
   CATCGMCompactObjectImplement  *allocateur = (CATCGMCompactObjectImplement *)this;                 \
   TIE##interfac##implementation *iTie       = new (allocateur) TIE##interfac##implementation(this); \
   SetInterface( iTie );                                                                             \
}

#ifdef CATIAR214
#define TIECGM(XXX,YYY)      TIE_Deprecated_##XXX(YYY)
#else
#define TIECGM(XXX,YYY)      TIE_##XXX(YYY)
#endif

#else
#include "CATMacBuildCGM_CATCGMBOAObject.h"
#endif

#define OLDTIECGM(XXX,YYY)   TIE_##XXX(YYY)

#endif
