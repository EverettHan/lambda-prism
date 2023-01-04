#ifndef CATICGMSpecialHandler_H
#define CATICGMSpecialHandler_H

// COPYRIGHT DASSAULT SYSTEMES 2017
/** @CAA2Required */
//**********************************************************************
//* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS *
//* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME *
//**********************************************************************    

//==========================================================================
// Specific handler declaration macros for CGM objects
// ---------------------------------------------------
//
// - inspired from CATBaseUnknown_var (copy October 4th 2017)
// - with added destructor declaration
// - with additional dedicated memory check leak spyer CATCGMSpecialHandlerSpyer()
//   (for _WINDOWS_SOURCE only)
// - spyer automatically activated in MEMORYCHECK replay
// - spyer may also be activated through environment variable
//
// Use:
// ---
// - replace CATDeclareHandler(CATICGMUnknown,CATBaseUnknown) 
//   by      CATCGMSpecialHandlerDeclare(CATICGMUnknown,CATBaseUnknown) 
//   in declaration file
// - replace CATImplementHandler(CATICGMUnknown,CATBaseUnknown) 
//   by      CATCGMSpecialHandlerImplement(CATICGMUnknown,CATBaseUnknown) 
//   in implementation file
//
// Note: 
// ---
// - read output traces for numbers of handlers in memory leak
// - use breakpoint on CATCGMSpecialHandlerSpyerBreakPoint() 
//   for target definition/reach on handler number
// - use export CATCGMSpecialHandler=1 for spyer activation (automatic in MemoryCheck replay)
// - use export CATCGMSpecialHandler=2 for spyer activation and traces
//
//==========================================================================
// 13/10/17 NLD Creation
// 18/10/17 NLD Split    de CATCGMSpecialHandler et creation de CATCGMSpecialHandlerSpyer
//              pour deport du spyer dans Mathematics afin de resoudre divers
//              problemes de link dans des frameworks utilisant les handlers CGM
//              sans declarer ce framework dans leur ImakeFile
// 21/02/20 NLD Remplacement de l'appel direct à la méthode CATCGMSpecialHandlerSpyer()
//              par un appel de macro CATCGMSpecialHandlerSpyerMacro()
//              avec aiguillage eventuel vers CATCGMSpecialHandlerSpyerGeo
//==========================================================================

//==========================================================================
#include "ExportedByCATGMGeometricInterfaces.h"
//==========================================================================

//==========================================================================
// Precompilation options
//==========================================================================
   #define CATCGMSpecialHandler_Available // "En attente NLD161017"

#ifdef     CATCGMSpecialHandler_Available
 #ifdef    _WINDOWS_SOURCE
   #define CATCGMSpecialHandler_Active
 #endif
#endif

// Protection. Des frameworks applicatifs peuvent ne pas avoir Mathematics
// dans leur Imakefile?
// on se dit que si l'inclusion a déjà été faite on utilise, sinon on débranche
// ou alors on branche sur un spyer intermediaire CATCGMSpecialHandlerSpyerGeo de ce framework
// mais attention, rien que pour CATCGMSpecialHandler.cpp lui-meme on entrait ici
// trop tot sans avoir defini Mathematics. Je retouche quelques headers pour les reordonner
// NLD210220
#ifdef CATCGMSpecialHandler_Active
 #ifdef ExportedByCATMathematics
  #define CATCGMSpecialHandlerSpyerMacro(var, base) CATCGMSpecialHandlerSpyer(var, base)
 #else
  #define CATCGMSpecialHandlerSpyerMacro(var, base) CATCGMSpecialHandlerSpyerGeo(var, base)
  //#undef CATCGMSpecialHandler_Active
  //#include "InclusionBidonPourTest.h" // pour detection des softs CGM dans ce cas
  // #define CATCGMSpecialHandlerSpyerMacro(var, base) // macro vide
 #endif
#endif

//==========================================================================
// spyer for a handler on a base class instance
// DO NOT USE DIRECTLY
#ifdef CATCGMSpecialHandler_Active
extern "C" ExportedByCATGMGeometricInterfaces
void CATCGMSpecialHandlerSpyerGeo(void* var, void *base);
#endif

//==========================================================================
// Macros declarations
//==========================================================================

#ifndef CATCGMSpecialHandler_Active
#include "CATMacForIUnknown.h" // standard macro definition for CATDeclareHandler and prerequisite
#define CATCGMSpecialHandlerDeclare(interfac,baseclass)   CATDeclareHandler(interfac,baseclass)
#define CATCGMSpecialHandlerImplement(interfac,baseclass) CATImplementHandler(interfac,baseclass)

#else

// remplacement de inline par CATCGMSpecialHandlerSpyerInline ?
// #define CATCGMSpecialHandlerSpyerInline
//-------------------------------------------------------------------------- HandlerSpecialDefinition_Begin
// spyer for a handler on a base class instance
// DO NOT USE DIRECTLY
// extern "C" ExportedByCATGMGeometricInterfaces
// void CATCGMSpecialHandlerSpyer(void* var, void *base);
#include "CATCGMSpecialHandlerSpyer.h"

// CATDeclareHandler(CATICGMUnknown,CATBaseUnknown);

// copy of WINDOWS implementation of macro  CATDeclareInlineAffect
/** @nodoc */
#define CATDeclareInlineAffectCGM(interfac)                                                        \
inline interfac##_var & __stdcall operator=(const CATBaseUnknown *base);                           //

// - copy of WINDOWS implementation of macro  CATImplementInlineAffectCGM
// - ajout CATCGMSpecialHandlerSpyer
/** @nodoc */
#define CATImplementInlineAffectCGM(interfac)                                                      \
inline interfac##_var & __stdcall interfac##_var::operator=(const CATBaseUnknown *base)            \
{                                                                                                  \
   __CastTo((IUnknown *)base);                                                                     \
   CATCGMSpecialHandlerSpyerMacro(this, (void*)base);                                              \
   return(*this);                                                                                  \
}                                                                                                  //

// - copy of WINDOWS implementation of macro  CATDeclareHandler
// - ajout CATCGMSpecialHandlerSpyerMacro
/**
 * Declares a handler.
 * <b>Role</b>: Declares a handler, or smart pointer, for an interface,
 * in the interface header file.
 * @param interfac
 *   Interface name
 * @param baseclass
 *   Class from which the interface class derives.
 */
#define CATCGMSpecialHandlerDeclare(interfac,baseclass)                                            \
                                                                                                   \
class interfac##_var : public baseclass##_var                                                      \
{                                                                                                  \
   private:                                                                                        \
      Exported void __stdcall __CastTo(IUnknown*pt);                                               \
   public:                                                                                         \
      inline ~interfac##_var();                                                                    \
      inline  interfac##_var();                                                                    \
      inline  interfac##_var(      CATBaseUnknown    *  base);                                     \
      inline  interfac##_var(      interfac          *  base);                                     \
      inline  interfac##_var(const interfac##_var     & base);                                     \
      inline  interfac##_var(const CATBaseUnknown_var & base);                                     \
      inline  interfac * __stdcall operator->() const;                                             \
      inline  __stdcall operator interfac *() const;                                               \
      inline  interfac##_var& __stdcall operator=(const CATBaseUnknown_var &base);                 \
      CATDeclareInlineAffectCGM(interfac)                                                          \
};                                                                                                 \
                                                                                                   \
inline interfac##_var::~interfac##_var()                                                           \
{                                                                                                  \
    CATCGMSpecialHandlerSpyerMacro(this, NULL);                                                    \
}                                                                                                  \
inline interfac##_var::interfac##_var():baseclass##_var()                                          \
{                                                                                                  \
}                                                                                                  \
inline interfac##_var::interfac##_var(CATBaseUnknown *base) : baseclass##_var()                    \
{                                                                                                  \
    CATCGMSpecialHandlerSpyerMacro(this, base);                                                    \
    __CastTo(base);                                                                                \
}                                                                                                  \
inline interfac##_var::interfac##_var(interfac *base):baseclass##_var((baseclass *)base)           \
{                                                                                                  \
    CATCGMSpecialHandlerSpyerMacro(this, base);                                                    \
}                                                                                                  \
inline interfac##_var::interfac##_var(const interfac##_var &base):baseclass##_var((baseclass*)base)\
{                                                                                                  \
    CATCGMSpecialHandlerSpyerMacro(this, base);                                                    \
    __CastTo((CATBaseUnknown *)base);                                                              \
}                                                                                                  \
inline interfac##_var::interfac##_var(const CATBaseUnknown_var &base): baseclass##_var()           \
{                                                                                                  \
    CATCGMSpecialHandlerSpyerMacro(this, base);                                                    \
    __CastTo((IUnknown *)base);                                                                    \
}                                                                                                  \
inline interfac * __stdcall interfac##_var::operator->() const                                     \
{                                                                                                  \
    return((interfac *)CATBaseUnknown_var::operator->());                                          \
}                                                                                                  \
inline __stdcall interfac##_var::operator interfac *() const                                       \
{                                                                                                  \
    CATImplementConv(interfac);                                                                    \
}                                                                                                  \
inline interfac##_var& __stdcall interfac##_var::operator=(const CATBaseUnknown_var &base)         \
{                                                                                                  \
    CATCGMSpecialHandlerSpyerMacro(this, base);                                                    \
    __CastTo((IUnknown *)base);                                                                    \
    return(*this);                                                                                 \
}                                                                                                  \
CATImplementInlineAffectCGM(interfac)                                                              \
                                                                                                   \
typedef interfac *interfac##_ptr                                                                   //


#define CATCGMSpecialHandlerImplement(interfac,baseclass)                                          \
void interfac##_var::__CastTo(IUnknown*pt)                                                         \
{                                                                                                  \
   CastTo(pt,IID_##interfac);                                                                      \
}                                                                                                  //


//-------------------------------------------------------------------------- HandlerSpecialDefinition_End
#endif

#endif
