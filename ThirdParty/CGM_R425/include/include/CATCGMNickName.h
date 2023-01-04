/* -*-c++-*- */
/**
* @COPYRIGHT DASSAULT SYSTEMES 2009
*/
#ifndef CATCGMNickName_H 
#define CATCGMNickName_H 
//=============================================================================
// DESCRIPTION : Symbolic Name On demand  
//=============================================================================
// Feb. 09	Symbolic Name On demand , 
//             (volatile structure Helpers for  Journal/CellTracking)
//          Associativity/equivalency management through operation
//=============================================================================
#include "CATGeoFactory.h"
#include "CATCGMHashTable.h"
#include "CATListOfCATICGMUnknowns.h"
#include "CATICGMUnknown.h"
#include "YP0LOGRP.h"
 
class CATCGMOutput;
class CATCGMNickName;
class CATBody;
class CATTopOperator;


 
/**
*  NickNaming Services 
*/
class ExportedByYP0LOGRP CATCGMNickNaming
{
public :

  static CATCGMNickNaming*  IsActive();

  /**
  * NameAfterRun .
  */
  virtual void NameAfterRun(CATTopOperator *iOperator) = 0;

  /**
  */
  virtual ~CATCGMNickNaming();

  /**
  * IsNickName .
  */
  virtual CATCGMNickName *IsNickName(CATICGMUnknown *iObject) = 0;

  /**
  * GenerateNickName
  */
  virtual CATCGMNickName * GenerateNickName(CATICGMUnknown *iObject) = 0;


protected  :
  //------------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------------
  CATCGMNickNaming();


private :
  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGMNickNaming(const CATCGMNickNaming &iCopy);
  CATCGMNickNaming& operator=(const CATCGMNickNaming &iCopy);
 
};




typedef		unsigned short CATCGMNickNameType;

#define CATCGMNickNameCompoundStaticSIZE 4 
#define CATCGMNickNameTypeAtomicStaticSIZE  16 

#define CATCGMNickNameTypeAtomic   1 
#define CATCGMNickNameTypeCompound 2 

/**
*  Class defining a symbolic name on request.
*
*  LifeCycle may be protected by a counter.
*    As soon this counter is engaged, lifecycle is under its control
*    Last decrease of counter leading to zero value .
*
*   Object logical LifeCycle is not integrated.
*     
*/
class ExportedByYP0LOGRP CATCGMNickName
{
public :

  /**
  * Destructor .
  */
  virtual ~CATCGMNickName();

  /**
  * Get CGM Objects currently holding the NickName.
  */
 void GetCGMObjects(CATLISTP(CATICGMUnknown) & oCGMObjects, const CATBoolean iWithAssociated = FALSE) const;

  /**
  * Reserved to CGM Management, not to be called explicitly
  *   Add a subsriction on an object.
  */
  void Subscribe(CATICGMUnknown * iObject);

  /**
   * Reserved to CGM Management, not to be called explicitly
   *   Remove a subsriction on an object.
  */
  void Unsubscribe(CATICGMUnknown * iObject);


  /**
  * Reserved to weak associativity.
  */
  void AddAssociated(CATICGMUnknown * iObject);

  
/** LifeCycle protection  */
  INLINE unsigned short IncreaseCounter();

/** LifeCycle protection */
  INLINE unsigned short DecreaseCounter();


  /** Dump */
  virtual void  Dump( CATCGMOutput& os );

  /** GetName */
  virtual void  GetName( CATUnicodeString& oName) = 0;
   

/** GetType */
  virtual CATCGMNickNameType  GetType() = 0;

/** HashKey */
  INLINE unsigned int  HashKey();

/** Compare */
  virtual int  Compare(CATCGMNickName* ipNickName) = 0;

  CATCGMNewClassArrayDeclare;

protected  :

  CATCGMNickName(CATICGMUnknown * iBootObject);

  unsigned int                 _Hashkey;
  unsigned int                 _Counter;
  CATLISTP(CATICGMUnknown)     _Holders;
  CATLISTP(CATICGMUnknown)    *_Associated;

private :
  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGMNickName(const CATCGMNickName &iCopy);
  CATCGMNickName& operator=(const CATCGMNickName &iCopy);
};


unsigned short CATCGMNickName::IncreaseCounter()
{ return ++_Counter; }

unsigned short CATCGMNickName::DecreaseCounter()
{ unsigned short rc = --_Counter; if ( 0 == rc ) delete this; return rc; }

INLINE unsigned int  CATCGMNickName::HashKey()
{ return _Hashkey; }



/**
*  Atomic NickName.
*/
class ExportedByYP0LOGRP CATCGMNickNameAtomic : public CATCGMNickName 
{
public :

  /**
  * Destructor .
  */
  virtual ~CATCGMNickNameAtomic();


/** GetType */
  virtual CATCGMNickNameType  GetType()  ;

/** Compare */
  virtual int  Compare(CATCGMNickName* ipNickName)  ;

  CATCGMNewClassArrayDeclare;

  // if ( ! Name)  automatic Name generation by CATCGMName 
  CATCGMNickNameAtomic(char  *iName, CATICGMUnknown * iBootObject);

protected  :

/** ComputeHashKey */
  unsigned int   ComputeHashKey() ;

  /** Dump */
  virtual void  Dump( CATCGMOutput& os );

  /** GetName */
  virtual void  GetName( CATUnicodeString& oName);

   char   _StaticNickName[CATCGMNickNameTypeAtomicStaticSIZE];  
   char  *_NickName;

private :
  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGMNickNameAtomic(const CATCGMNickNameAtomic &iCopy);
  CATCGMNickNameAtomic& operator=(const CATCGMNickNameAtomic &iCopy);
};




/**
*  Compound NickName.
*/
class ExportedByYP0LOGRP CATCGMNickNameCompound : public CATCGMNickName
{
public :

  /**
  * Destructor .
  */
  virtual ~CATCGMNickNameCompound();


/** GetType */
  virtual CATCGMNickNameType  GetType()  ;

/** Compare */
  virtual int  Compare(CATCGMNickName* ipNickName)  ;

  CATCGMNewClassArrayDeclare;

  CATCGMNickNameCompound(CATLONG32 iNbNickNames, CATCGMNickName *iNickNames[]);

protected  :

  /** ComputeHashKey */
  unsigned int   ComputeHashKey() ;

  /** Dump */
  virtual void  Dump( CATCGMOutput& os );

  /** GetName */
  virtual void  GetName( CATUnicodeString& oName);



  CATLONG32            _NbNickNames;
  CATLONG32            _MaxArraySize;
  CATCGMNickName     * _NickNames[CATCGMNickNameCompoundStaticSIZE];

private :
  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGMNickNameCompound(const CATCGMNickNameCompound &iCopy);
  CATCGMNickNameCompound& operator=(const CATCGMNickNameCompound &iCopy);
};



/**
*  Dictionnary of CATCGMNickName.
*/

class   ExportedByYP0LOGRP  CATCGMNickNames  : protected  CATCGMHashTable
{
public:
  CATCGMNickNames (int iEstimatedSize = 0);
  ~CATCGMNickNames();
  CATCGMNewClassArrayDeclare;
  
  int             Insert(CATCGMNickName* ipCGMObject);
  CATCGMNickName* Locate(CATCGMNickName* ipCGMObject) const;

  int             Remove(CATCGMNickName* ipCGMObject);
  CATCGMNickName* Next(int& ioNumBucket, int& ioPos) const;

  int             Size() const;
  CATCGMNickName* Get(int iPos) const;
};




 
/**
* @nodoc
*/
extern "C" { typedef CATCGMNickNaming* CATCGMNickNaming_Creator(const char *ipCATCGMNickNaming); }  

#endif
