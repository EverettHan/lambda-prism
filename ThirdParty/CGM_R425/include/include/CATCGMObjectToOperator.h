/* -*-c++-*- */
/**
* @COPYRIGHT DASSAULT SYSTEMES 2009
*/
#ifndef CATCGMObjectToOperator_H 
#define CATCGMObjectToOperator_H 
//=============================================================================
// DESCRIPTION : For Knowledge or ignorance of operator's generating data
/*
    

 Specification
    Reporting de liaison entre creation objets CGM et les operateurs associes 
    (sous format initial CSV)

 Declenchement 
    set/export CATCGMObjectToOperator=directory
    Outil de debug (CATDevelopmentStage=TRUE)
    Prereq : FIXPART ou sinon BSFTST en phase II

 Integration
 	 ODT
      specifique sur ODT CATCGMStream.tst   ds_site -operator   "Update  "
   Interactivement 
      c:cgm et File/Report
     	Fichier Report_1.CGMObjectToOperator.CSV

 Implementation :
   Interface : GeometricObjects\ProtectedInterfaces\CATCGMObjectToOperator.h
   Implement : CATGem\CATCXDebug.m

   Pour autre Integration snapshot au vol  (autre moteur ODT)
     CATCGMObjectToOperator* ObjectToOperator =  CATCGMObjectToOperator::IsActive();
     if ( ObjectToOperator )
       ObjectToOperator->DumpReport(ReportName);


*/
//=============================================================================
#include "YP0LOGRP.h"
#include "CATICGMUnknown.h"
#include "CATMathInline.h"
#include "CATCGMHashTable.h"
 

class CATCGMOperator;
class CATCGMReportByType;
class CATUnicodeString;

#define CATCGMObjectToOperatorStatistics
 
/**
*  CATCGMObjectToOperator Mapping 
*/
class CATCGMObjectToOperator;

class ExportedByYP0LOGRP CATCGMObjectToOperator
{
public :

  /**
  * IsActive.
  */
  INLINE static  CATCGMObjectToOperator*  IsActive();

  /**
  * Push : Start of Operator Run .
  */
  virtual void Push(CATCGMOperator *iOperator) = 0;

  /**
  * Pop : End of Operator Run .
  */
  virtual void Pop(CATCGMOperator *iOperator) = 0;

  /**
  * ReportCreation : AddStatistics .
  *  GeometricObjectsCGM\ProtectedInterfaces\ObjectTypesCGM.h
  */
  virtual void ReportCreation(const int iObjectTypesCGM) = 0;


  /**
  * DumpReport .
  */
  virtual void DumpReport(const char iPartName[]) = 0;



protected  :
  //------------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------------
  CATCGMObjectToOperator();
  ~CATCGMObjectToOperator();


private :
  static  CATCGMObjectToOperator*  Init();

  static CATCGMObjectToOperator* _result ;
  static CATBoolean              _initialized ;

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGMObjectToOperator(const CATCGMObjectToOperator &iCopy);
  CATCGMObjectToOperator& operator=(const CATCGMObjectToOperator &iCopy);
 
};

 
INLINE CATCGMObjectToOperator*  CATCGMObjectToOperator::IsActive()
{ return  ! _initialized ?  CATCGMObjectToOperator::Init() : _result; }


/**
*  Class defining a symbolic name on request.
*/
#define CATCGMOperatorNameStaticSIZE  32 

class CATCGMOperatorNames;

/**
*  CATCGMOperatorName.
*/
class ExportedByYP0LOGRP CATCGMOperatorName
{
public :
  CATCGMOperatorName(char  *iName );

  /**
  * Destructor .
  */
  ~CATCGMOperatorName();

  /**
  * GetReportByType.
  */
  INLINE CATCGMReportByType * GetReportByType();

  /**
  * SetReportByType.
  */
  INLINE  void SetReportByType(CATCGMReportByType * iStatistics);

  /** GetName */
 void  GetName( CATUnicodeString& oName);

  /** HashKey */
  INLINE unsigned int  HashKey();

  /** Compare */
  int  Compare(CATCGMOperatorName* ipName) ;

  /** AddCaller */
  void  AddCaller(char  *iName) ;

  /** GetCallers */
  CATCGMOperatorNames *  GetCallers() ;


  CATCGMNewClassArrayDeclare;
  
/** LifeCycle protection  */
  INLINE unsigned short IncreaseCounter();

  INLINE unsigned short DecreaseCounter();



  /** NumberOfCalls  */
  INLINE unsigned int IncreaseNumberOfCalls();

  INLINE unsigned int GetNumberOfCalls();

  INLINE CATBoolean    IsDuplicatorLike();


protected  :
  /** Name */
  char                         _StaticName[CATCGMOperatorNameStaticSIZE+1];  
  char                       * _Name;
  unsigned int                  _Hashkey;

  /** LifeCycle */
  unsigned int                 _Counter;
  CATBoolean                   _IsDuplicatorLike;

  /** Statistics */
  CATCGMReportByType          *_Statistics;
  unsigned int                 _NumberOfCalls;
  CATCGMOperatorNames         *_Callers;


   /** ComputeHashKey */
  unsigned int   ComputeHashKey() ;

private :
  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGMOperatorName(const CATCGMOperatorName &iCopy);
  CATCGMOperatorName& operator=(const CATCGMOperatorName &iCopy);
};

//------------------------------------------------------------------------
// Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
//------------------------------------------------------------------------
INLINE unsigned int  CATCGMOperatorName::HashKey()
{ return _Hashkey; }

INLINE CATCGMReportByType * CATCGMOperatorName::GetReportByType() 
{ return _Statistics; }

INLINE  void CATCGMOperatorName::SetReportByType(CATCGMReportByType * iStatistics) 
{  _Statistics = iStatistics; }

INLINE  unsigned short CATCGMOperatorName::IncreaseCounter()
{ return ++_Counter; }

INLINE  unsigned short CATCGMOperatorName::DecreaseCounter()
{ unsigned short rc = --_Counter; if ( 0 == rc ) delete this; return rc; }

  /** NumberOfCalls  */
  INLINE unsigned int  CATCGMOperatorName::IncreaseNumberOfCalls() 
{ return ++_NumberOfCalls; }

  INLINE unsigned int  CATCGMOperatorName::GetNumberOfCalls() 
{ return _NumberOfCalls; }

  INLINE CATBoolean  CATCGMOperatorName::IsDuplicatorLike() 
{ return _IsDuplicatorLike; }
 


/**
*  Dictionnary of CATCGMOperatorName.
*/

class   ExportedByYP0LOGRP  CATCGMOperatorNames  : protected  CATCGMHashTable
{
public:
  CATCGMOperatorNames (int iEstimatedSize = 0);
  ~CATCGMOperatorNames();
  CATCGMNewClassArrayDeclare;
  
  int                 Insert(CATCGMOperatorName* ipCGMObject);
  CATCGMOperatorName* Locate(CATCGMOperatorName* ipCGMObject) const;

  int                 Remove(CATCGMOperatorName* ipCGMObject);
  CATCGMOperatorName* Next(int& ioNumBucket, int& ioPos) const;

  int                 Size() const;
  CATCGMOperatorName* Get(int iPos) const;
};


 
/**
* @nodoc
*/
extern "C" { typedef CATCGMObjectToOperator* CATCGMObjectToOperator_Creator(const char *ipCATCGMObjectToOperator); }  

#endif
