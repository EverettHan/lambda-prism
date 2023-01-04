#ifndef CATCGMIndex_h_
#define CATCGMIndex_h_
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//    INTERDICTION D'INCLURE DANS HEADER CAA
//    HEADER IMPLEMENTATION : PERMETTRE EVOLUTION VUE IMPLEMENTATIVE
//=============================================================================
  /**
    * -------------------------------------------------------------------------------------------------------
    *  TOPIC  :  Persistency Cache Tool for Seamless management of geometries from different CATGeoFactory
    * -------------------------------------------------------------------------------------------------------
 */
#include "CATMathInline.h"
#include "CATListPV.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATMathStreamVersionDef.h"
#include "CATCGMStreamControl.h"

#include "ExportedByGeometricObjects.h"
#include "CATCGMStream.h"
#include "CATICGMUnknown.h"
 
class CATCGMIndexTable;
class CATExtCGMReplay;
class CATCGMIndexes;
class CATCGMOutput;


class ExportedByGeometricObjects CATCGMIndex  
{
public:
  CATCGMNewClassArrayDeclare;

  CATCGMIndex();
  
  INLINE ULONG __stdcall AddRef();

  INLINE ULONG __stdcall Release();

  //----------------------------------------
  // Operational management (Full loaded)
  //    No AddRef()/Release() Management 
  //----------------------------------------
  HRESULT InsertGeometryAndGetIndex(CATICGMUnknown * iGeometry, CATULONG32 & ioIndex) ;
  HRESULT FromIndexToGeometry(const CATULONG32 iIndex, CATICGMUnknown * & iGeometry) ;
  
  //----------------------------------------
  // Buffer Management with Indexes
  //    SaveIntoBuffer : from memory reference to an allocated standalone Buffer;
  //          to be used once all references are collected.
  //    LoadFromBuffer : from already defined Buffer to operational geometries;
  //----------------------------------------
  HRESULT SaveIndexesIntoBuffer(const CATCGMStreamVersion     iUnderForceVersion,
                                const CATCGMStreamControl   & iUnderCompressionOptions,
                                CATExtCGMReplay* ExtCGMReplay);

  HRESULT DumpIndexesFromBuffer( CATCGMOutput& os );

  HRESULT LoadIndexesFromBuffer();
 
    
  //----------------------------------------
  // Stream I/O Exchange
  //    SaveIntoBuffer : from memory reference to an allocated standalone Buffer;
  //    LoadFromBuffer : from already defined Buffer to operational geometries;
  //----------------------------------------
  HRESULT WriteBufferIntoStream(CATCGMStream & ioStr);
  HRESULT AllocatedAndReadBufferFromStream(CATExtCGMReplay* ExtCGMReplay,
                                           const CATULONG32 iBufferLength,
                                           CATCGMStream                & ioStr,
                                           const CATCGMStreamVersion     iUnderForceVersion,
                                           const CATCGMStreamControl   & iUnderCompressionOptions);

  CATULONG32 GetBufferLength();

  //------------------------------------------------
  // Explicit LifeCycle (For CGMReplay Integration
  //------------------------------------------------
  HRESULT CloseFactories();

protected :

  ~CATCGMIndex();

private :

  HRESULT DirectInsertAndGetIndex(CATCGMIndexes * iIndex, CATULONG32 & ioIndex) ;

  CATCGMIndex(const CATCGMIndex &iCopy);
  CATCGMIndex& operator=(const CATCGMIndex &iCopy);

  ULONG             _RefCounter;

  //------------------------------------------------
  // HashTable (Working memory)
  //------------------------------------------------

  CATCGMIndexTable * _Table;

  //------------------------------------------------
  // Internal cache managemet under persistency Control
  //------------------------------------------------
  short                   _BufferOrigin; // 0:Not allocated,   1:From Session reference (Save)  2:Dedicated to Replay (Load)
  CATCGMStream         *  _Buffer;
  CATCGMStreamVersion     _UnderForceVersion;
  CATCGMStreamControl     _UnderCompressionOptions;


};

 
INLINE ULONG __stdcall CATCGMIndex::AddRef()
{ _RefCounter++;  return _RefCounter; }

INLINE ULONG __stdcall CATCGMIndex::Release()
{
  _RefCounter--;
  if (_RefCounter == 0)  {  delete this;  return 0;  }
  return _RefCounter;
}

#endif
