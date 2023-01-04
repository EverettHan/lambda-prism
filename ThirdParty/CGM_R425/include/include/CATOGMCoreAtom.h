#ifndef CATOGMCoreAtom_H
#define CATOGMCoreAtom_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2009
/**
 * @level Private
 * @usage U1
 */

//-------------------------------------------------------------------------------------------------
// Be Carefull about limited scope of this interface
//   high performance computation could not rely on central main memory management 
//
// Short term local transaction (change set acquisition)   
//    for extended N1 Operators on statefull modelisation
// Not to used by applied integration 
//    Dedicated to core kernel GM Component based modeler
//
// Cf  Oxxx Geomerical Modeler 
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Core Persistent Structure  
//----------------------------------------------------------------------------------------------
#include "CATOGMCore.h"
#include "CATOGMCoreHead.h"
#include "CATBaseUnknown.h"
#include "CATOGMCoreData.h"
 
class CATOGMCoreData;

//------------ ----------- ---------- 
//    Atom is defined by 
//
//      [ MANDATORY ]
//         Head  
//
//      [ OPTIONAL ]
//         Data address
//         RunBind (void * ) depending from domain
//         and may be Links (between Atom)
//
//------------ ----------- ---------- 
 

class ExportedByCATOGMCore CATOGMCoreAtom 
{
public :

  //------------ ----------- ---------- 
  // LifeCycle
  //------------ ----------- ---------- 

  /** LifeCycle Creation  */
  static CATOGMCoreAtom *Create(CATBaseUnknown *iObject, const CATOGMCoreHead & iHead);


  /** LifeCycle protection and management */
  INLINE void DecreaseCounter();

  /** LifeCycle protection and management  */
  INLINE void IncreaseCounter();


  /** ProvideWithStatus : If currently not with associated State, duplication occured */
  INLINE CATOGMCoreAtom *ProvideWithStatus(const CATOGMCORE_INTENTSTATE iState);

  /** Duplicate */
  virtual CATOGMCoreAtom *Duplicate() = 0;

  /** May Be NULL  */
  virtual CATBaseUnknown *GetCATBaseUnknown() = 0;

  /**  nodoc */
  virtual void BindCATBaseUnknown(CATBaseUnknown * iCBU) = 0;

  /** nodoc */
  virtual void UnbindCATBaseUnknown() = 0;

  //------------ ----------- ---------- 
  // Analysis
  //------------ ----------- ---------- 

  /** GetHead */
  INLINE  void  GetHead(CATOGMCoreHead & oHead) const ;

  /** GetINTENT */
  INLINE  CATOGMCORE_INTENTSTATE  GetINTENT() const ;

  
  //------------ ----------- ---------- 
  // For Set Management
  //------------ ----------- ---------- 

  /** HashKey */
  INLINE unsigned int  HashKey();

  /** Compare */
  int  Compare(CATOGMCoreAtom* ipCoreAtom);
 
  
  //------------ ----------- ---------- 
  // For Basic Data Management
  //------------ ----------- ---------- 

  /** GetData */
  INLINE CATOGMCoreData *  GetData();

  /** SetData */
  INLINE void SetData(CATOGMCoreData *iData);
 
  /** CompareData   0:equal 1:distinct */
  int  CompareData(CATOGMCoreAtom* ipCoreAtom);


protected :

  CATOGMCoreAtom(const CATOGMCoreHead & iHead);

  virtual ~CATOGMCoreAtom();


  CATOGMCoreHead   _Head;

  // Hashkey
  unsigned int    _Hashkey;

  // 
  CATOGMCoreData *  _Data;

private :

  // Counter
  unsigned int    _Counter;

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATOGMCoreAtom(const CATOGMCoreAtom &iCopy);
  CATOGMCoreAtom& operator=(const CATOGMCoreAtom &iCopy);
};


INLINE unsigned int  CATOGMCoreAtom::HashKey()
{ return _Hashkey; }


INLINE void CATOGMCoreAtom::IncreaseCounter()
{ ++_Counter; }

INLINE void CATOGMCoreAtom::DecreaseCounter()
{ if (( 0 == _Counter ) || (0 == --_Counter)) delete this; }

/** GetHead */
INLINE  void  CATOGMCoreAtom::GetHead(CATOGMCoreHead & oHead)  const
{ oHead = _Head; }

/** GetINTENT */
INLINE  CATOGMCORE_INTENTSTATE   CATOGMCoreAtom::GetINTENT() const
{ return _Head._Todo ; }

/** ProvideWithStatus : If currently not with associated State, duplication occured */
INLINE CATOGMCoreAtom *CATOGMCoreAtom::ProvideWithStatus(const CATOGMCORE_INTENTSTATE iState)
{
  if ( _Head._Todo == iState ) return this;  
  CATOGMCoreAtom *result = Duplicate();
  if ( result ) result->_Head._Todo = iState;
  return result;
}

/** GetData */
INLINE CATOGMCoreData *  CATOGMCoreAtom::GetData() 
{ return _Data; }

/** SetData */
void CATOGMCoreAtom::SetData(CATOGMCoreData *iData) 
{ if ( iData != _Data ) { if (_Data) delete _Data; _Data = iData; } }



#endif
