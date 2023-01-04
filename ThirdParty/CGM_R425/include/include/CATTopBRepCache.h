#ifndef CATTopBRepCache_h
#define CATTopBRepCache_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/**
      As a status,  main services (or operations)  have been specified and implemented 
         on generic topological configurations mainly based upon at most 2-manifold  solid modeling.

      This generic helpers is proposed as transient cache (short term lifespan) on a current working body    
          for advanced programming coding with best relimitation impact management.

      According to statistic of possible ocurrences and usage,  either explicit  FILTERING or EXPOSURE 
          following tiny extensible characterisation dedicated to GM V5 topological implementation.
      Implementation of this model extension should have less footprint as possible on running implementation.
           (dynamic transient but yet not redondant with an already advanced internal data structure )
*/
//------------------------------------------------------------ 

#include "ExportedByCATTopologicalObjects.h"
#include "CATDataType.h"
#include "CATUnicodeString.h"
#include "CATMathInline.h"
#include "CATCGMExclusive.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"
 


class CATBody;
class CATCell;
  
//------------------------------------------------------------ 
//  Advanced analysis of untrivial connectivity
//------------------------------------------------------------ 
 

/**
*  Specific diagnosis designed as short transaction helper for untrivial cell connectivity management .
*       to be consumed quickly in context of current "active" working frozen body 
*           invalidated by multiple bodies management (smart management) 
*           and  not inside bodies operator (because completion not achieved)
*  each instance represent a particular context of non trivial connectivity relative to a body
*     
*/



class ExportedByCATTopologicalObjects CATTopBRepCache  : public CATCGMExclusive 
{
public :


  /**
  *  GetBRepCache , computed (or retrieve cache) untrivial connectivity
  *     Do not forget to resulting oConfiguration->Release()  after usage     
  */
  static CATBoolean  GetBRepCache( CATBody *iBody,  CATCell * iCell,  CATTopBRepCache * & oConfiguration , CATBoolean   iAllocate  = TRUE)  ;
  
 
  /**
  * IsValid (provided with weak reference AddRef()/Release() and diagnosis against LifeCycle of ownerships
  *    As this transient status is volatile  To be used during the transaction of working active body
  */
  CATBoolean IsValid()  ;


  /**
  * GetCell (...)
  */
  CATCell * GetCell()  ;

  /**
  * GetBody (...)
  */
  CATBody * GetBody()  ;


  //-------------------------------------------------------------------------------------------------------------- 
  //  GetMeta
  //-------------------------------------------------------------------------------------------------------------- 

    /** @nodoc (to implement with static method variable , type enabler ) */
  virtual  void * GetMeta();

 /** @nodoc (to implement with static method variable , type enabler ) */
  static  void * _GetMeta();

  
  /** @nodoc */
  INLINE CATLONG32   __stdcall  AddRef (void*  iReferencing = NULL);
  /** @nodoc */
  INLINE CATLONG32   __stdcall  Release(void*  iReferencing = NULL);

    /**
  * @nodoc
  */
  CATCGMNewClassArrayDeclare;


  
  int         _CellNeighboursSize;
  CATCell  ** _CellNeighboursArray;



protected :

  /** @nodoc  */
  CATTopBRepCache( CATBody *iBody, CATCell * iCell );

  /** @nodoc  */
  virtual ~CATTopBRepCache();

  /** @nodoc  */
   CATBody         * _Body ;
   CATCell         * _Cell ;

private :

  CATTopBRepCache(const CATTopBRepCache &iCopy);
  CATTopBRepCache& operator=(const CATTopBRepCache &iCopy);

};


  //----------------------------------------------------------------------------
  //  CATTopBRepFaceCellNeighbours 
  //---------------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATTopBRepFaceCellNeighbours
{
public :
  static        void SetFaceCellNeighbours(int iMode); 
  static INLINE int  GetFaceCellNeighbours(); 
private:
  static        void InitFaceCellNeighbours(); 
  static        int _Behavior;
};

INLINE int CATTopBRepFaceCellNeighbours::GetFaceCellNeighbours()
{ if (-1 == _Behavior ) InitFaceCellNeighbours(); return _Behavior; }


/** @nodoc */
INLINE CATLONG32   __stdcall  CATTopBRepCache::AddRef (void*  iReferencing) { return this->CATCGMExclusive::AddRef(iReferencing); } 
/** @nodoc */
INLINE CATLONG32   __stdcall  CATTopBRepCache::Release(void*  iReferencing) { return this->CATCGMExclusive::Release(iReferencing); } 

#endif
