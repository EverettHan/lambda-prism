#ifndef CATechGeoFactories_h
#define CATechGeoFactories_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//------------------------------------------------------------ 
// Small metadata for genuine Extract/Redo infrastructure
//------------------------------------------------------------ 
#include "CATGeometricObjects.h"
#include "CATSysSimpleHashTable.h"
#include "CATGeoFactory.h"
#include "CATCGMDebug.h"
 

class  ExportedByCATGeometricObjects CATechGeoFactory
{ 
public :
  CATechGeoFactory(CATGeoFactory  * iFactory)  : _Factory(iFactory), _Key(0)  
  {  _Key = CATCGMDebug::GetSessionIdNumber(iFactory); }

  CATechGeoFactory() : _Factory(NULL), _Key(0) {};

  ~CATechGeoFactory() { _Factory = NULL; _Key=0; };

  CATBoolean operator == (const CATechGeoFactory & iOther) const 
  {
    if (this == &iOther) return TRUE; 
    if ( _Key != iOther._Key ) return FALSE;
    if ( _Factory != iOther._Factory ) return FALSE;
    return TRUE;
  }

  CATUINTPTR HashValue()  
  { return _Key; }

  CATBoolean FrozenName(CATUnicodeString & oShemaName);

  CATLISTP(CATICGMObject)  _CATICGMObjects;
  CATGeoFactory          * _Factory;

private :
  
  friend class CATechGeoFactories;
  CATUINTPTR       _Key;  
 
  CATechGeoFactory (CATechGeoFactory &);    
  CATechGeoFactory& operator=(CATechGeoFactory&);  
};


//------------------------------------------------------------------------
// CATechGeoFactories
//------------------------------------------------------------------------
class  ExportedByCATGeometricObjects CATechGeoFactories : public CATSysSimpleHashTable
{
public:

  /** @nodoc */
  CATechGeoFactories(int dim=256);

  /** @nodoc */
  ~CATechGeoFactories();

  /** @nodoc */
  int                  Insert(CATechGeoFactory & iLocation);

  /** @nodoc */
  CATechGeoFactory      * Locate(CATechGeoFactory & iLocation) const;

  /** @nodoc */
  void ApplyDelete();

private:

  /** @nodoc */
  CATechGeoFactories(const CATechGeoFactories&);

  /** @nodoc */
  CATechGeoFactories& operator=(const CATechGeoFactories&);
};





//------------------------------------------------------------
// CATechGeoFactories_ XXX 
//------------------------------------------------------------

/** @nodoc */
ExportedByGeometricObjects unsigned int CATechGeoFactories_HashKey(void* inew); 

/** @nodoc */
ExportedByGeometricObjects int          CATechGeoFactories_Compare(void* i1, void *i2);


#endif
