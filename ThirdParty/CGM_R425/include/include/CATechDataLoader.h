#ifndef CATechDataLoader_H
#define CATechDataLoader_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/**
 * @level Private
 * @usage U1
 */
//------------------------------------------------------------ 
// area(s) of data
//------------------------------------------------------------ 
#include "ExportedByCATTechTools.h"
#include "CATDataType.h"
#include "CATUnicodeString.h"
#include "CATechData.h"
#include "CATLISTV_CATechMeta.h"

class CATCGMVirtualItf;
class CATICGMUnknown;
class CATechData;
class CATechAttribute;
class CATechMeta;
class CATGeoFactory;


/**
* Class to define a loader.
*/

class ExportedByCATTechTools CATechDataLoader
{
public :

  /**
  * LoadObjects  
  */
  virtual HRESULT LoadObjects(CATechDataNumber & oDataLoadedNumber) = 0;

  /**
  *   QueryLoadedGMOperator  
  */
  virtual CATCGMVirtualItf *  QueryLoadedGMOperator(const IID &iIID) = 0;

  /**
  *   QueryLoadedGMObject  
  */
  virtual CATICGMUnknown   *  QueryLoadedGMObject(const unsigned int iCATGeometricType, const int iIndex) = 0;
 
  /**
  *   QueryInterface : access to genuine Interface
  */
  virtual HRESULT  __stdcall QueryInterface(const IID &iid,void **ppv) = 0;


   /**
  * ReplayObjects  
  */
  virtual HRESULT ReplayObjects() = 0;

  /**
  * DumpObjects  
  */
  virtual HRESULT DumpObjects(const CATechDataDumpOptions iOptions, CATechAttribute * iOutput, CATechSet * iJournaling) = 0;

  /**
  * UnloadObjects  
  */
  virtual HRESULT UnloadAllObjects() = 0;

  /**
  * AddFactoryToNotClose  : request to not close a given factory
  */
  virtual HRESULT AddFactoryToNotClose(CATGeoFactory *piFactory);

  /**
  * @nodoc 
  *   destructor : ...
  */
  virtual ~CATechDataLoader() ;

 
  /**
  * SetDifferedContext  
  */
  virtual HRESULT SetDifferedContext(CATechSet  * iSet, CATechAttribute  * iAttribute)  ;


  /**
  * GetDataLoader  
  */
 static CATechDataLoader *GetDataLoader(const CATUnicodeString & iDataType, CATechData *iData, CATechSet  * iSet, CATechAttribute  * iAttribute); 

  /**
  * @nodoc GetNCGMDataLoader  
  */
 static CATechDataLoader *GetNCGMDataLoader();

  /**
  * @nodoc GetNCGMDataLoader  
  */
 static void CleanNCGMDataLoader();

 /**
  * @nodoc / SaveObjects  
  */
  virtual HRESULT SaveObjects(CATechSet  * iSet, CATechAttribute *iAttribute, const CATechMetas & iNCGMRoles) const = 0;

  /**
  * @nodoc / PrepareLinksFromObjects 
  */
  virtual HRESULT PrepareLinksFromObjects(int  nbElems,  IUnknown **iIUnknowns, CATLONG64 *iTags ) const = 0;

  /**
  * @nodoc / UpdateLinksAfterLoad 
  */
  virtual HRESULT UpdateLinksAfterLoad(int  nbElems, CATLONG64 *iTags, IUnknown **iIUnknowns ) const = 0;
   /**
  * @nodoc 
  */
  INLINE CATechData * GetCATechData();

protected :

  CATechDataLoader(CATechData *iData, CATechSet  * iSet, CATechAttribute  * iAttribute ) ; 
  CATechData * _Data;
  static CATechDataLoader *_NCGMDataLoader;

  CATechSet           * _Set;
  CATechAttribute     * _Attribute;

  int               _Num;
  static int        _NumAll;

private :

  CATechDataLoader(const CATechDataLoader &iCopy);
  CATechDataLoader& operator=(const CATechDataLoader &iCopy);

};
 
INLINE CATechData * CATechDataLoader::GetCATechData() { return _Data; }

extern "C" { typedef CATechDataLoader * CATechDataLoading(CATechData *iData, CATechSet  * iSet, CATechAttribute  * iAttribute); }  

#endif
