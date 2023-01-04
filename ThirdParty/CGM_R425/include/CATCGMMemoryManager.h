/* -*-C++-*-*/
#ifndef CATCGMMemoryManager_H
#define CATCGMMemoryManager_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 1997
//
// CATCGMMemoryManager 
//
// DESCRIPTION :
/**
  * This object handle the allocations of all the temporary objects.
  * All these objects are deleted with this object, so that it flushes the memory
  * with all the temporary objects.
  * <BR> This file contains also an overloaded form of the operator new that uses
  * a CATCGMMemoryManager to obtain its datas.
  * <BR> The method Reset() might be used when the object has been finished used.
  * The ojbects that have allready been allocated are then lost, and the memory
  * is reused for further allocations. 
  */
//
// Main Methods :
//  
//=============================================================================
// Abstract Class     : No
// Inline Functions   : No
//=============================================================================
//
// History
//
// Dec. 97 JCH Creation            
// Sep. 99 HLK Added the manager name
// Juin 2002 TPD amelioration du Dump de "CATCGMMemoryManager"
// Jan. 2005 TPD On calcule le VRAI point sur l'edge (RI489565)
//
//=============================================================================

//=============================================================================
// System include
//-----------------------------------------------------------------------------
#include <stddef.h>

//=============================================================================
// For Windows NT
//-----------------------------------------------------------------------------
#include "CATMathematics.h"

#include "CATMathRefCounted.h"
#include "CATCGMNewArray.h"
#include "CATDataType.h"

//=============================================================================
// Forward declarations
//-----------------------------------------------------------------------------

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

struct CATCGMHeader;

//=============================================================================
// CLASS DEFINITION
//=============================================================================
class ExportedByCATMathematics CATCGMMemoryManager : public CATMathRefCounted
{
public:
//=============================================================================
// CONSTRUCTORS AND DESTRUCTOR
//=============================================================================
/**
 * Default Constructor
 */
  CATCGMMemoryManager(const char *iName = "Unknown");

/**
 * Destructor
 */
  virtual ~CATCGMMemoryManager();

  /** @nodoc */
  CATCGMNewClassArrayDeclare;
  
  //=============================================================================
  // ALLOCATION METHODS
  //=============================================================================
  /** Returns a pointer on a block of the appropriated size.
  * @iSizeInBytes : size of the block. The type size_t is defined in "stddef.h". 
  */
  virtual void * AllocateWithSizeInBytes(size_t iSizeInBytes);
    
  /** Resets the memory manager.
 * <BR> All the objects that have been allready allocated are lost( as deleted).
 * The memory they took is used to allocates the new objects.
 */
  void Reset();


/** For debug: dumps the informations in a stream.
 */
  void DumpStream(CATLONG32 iLevel = 0, CATLONG32 iSpace = 0);


/** For debug: dumps the informations in a the standard output.
 */
  void Dump(CATLONG32 iLevel = 0, CATLONG32 iSpace = 0);

  inline const char * GiveName() const;
  void SetName( const char * iName );
//=============================================================================
// INTERNAL DATAS
//=============================================================================
protected :

  // First buffer.
  CATCGMHeader * _FirstBlock;

  // Current Memory Size of Allocator
  size_t   _CurrentSize;

  // Name of allocator
  char     _ManagerName[24];

};

#if defined ( _WINDOWS_SOURCE )
#define CATCGMMemoryManagerWithDelete
#else
#undef  CATCGMMemoryManagerWithDelete
#endif

//------------------------------------------------------------
// Overloaded operator new to use the CATCGMMemoryManager to 
// allocate the objects.
//------------------------------------------------------------
inline ExportedByCATMathematics void * operator new (size_t iSize, CATCGMMemoryManager * iMemoryManager);
inline void * operator new (size_t Size, CATCGMMemoryManager * MemoryManager)
{
  return MemoryManager->AllocateWithSizeInBytes(Size);
}

//=============================================================================
// Uniquement pour eviter la TETANISATION par des message de Warning
//=============================================================================
#if defined (CATCGMMemoryManagerWithDelete )
inline  ExportedByCATMathematics void operator delete (void *iBuffer, CATCGMMemoryManager * iMemoryManager);

inline void operator delete (void *iBuffer, CATCGMMemoryManager * iMemoryManager)
{
}
#endif

//=============================================================================
// For Class
//=============================================================================
#if defined ( CATCGMMemoryManagerWithDelete )

#define CATCGMMemoryManagerNewDel \
inline void * operator new (size_t Size, CATCGMMemoryManager * MemoryManager) \
{ return MemoryManager->AllocateWithSizeInBytes(Size); }; \
inline void operator delete (void *iBuffer, CATCGMMemoryManager * iMemoryManager) {}

#else

#define CATCGMMemoryManagerNewDel \
inline void * operator new (size_t Size, CATCGMMemoryManager * MemoryManager) \
{ return MemoryManager->AllocateWithSizeInBytes(Size); }

#endif

inline const char * CATCGMMemoryManager::GiveName() const
{
  return _ManagerName;
}
#endif
