#ifndef CATOGMHistory_H
#define CATOGMHistory_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2009
/**
* @level Private
* @usage U1
*
* Contents : Interface for externalisation of build-in  and  on demand indicators
*
*  Main specification of FootPrint is about virtual graph 
*       initial defined by internal collect (various synthetic operational relationships) accoring to algorithms
*       extended by overview manipulation for the best control over GM modelisation  
*
*  Originally conceived from a request of explicit check of recycling rate of internal states over operations  
*    But abusing  reuse over history without any simplification-reduction (as "datumiser" )
*    may lead to overweight and complex formula of data structure
*
*
* About packaging :  New kind of packaging under single namespace
*    mre appropriate to multiple Release management hoping it will reduce dispersion of multiple files 
*    a litlle antagonist with Mac Cabe point of view
*     concerning source - file associativy  (dedicated Class and limited number of lines per file !)
*/

#include "ExportedByCATOGMCore.h"
#include "CATBoolean.h"
#include "CATMathInline.h"
#include "CATDataType.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

class CATOGMHistoryKey;
class CATechAttribute;


/**
* Utility - Interface for externalisation of build-in  and  on demand indicators
*/

namespace CATOGMHistory
{


  /**
  * Activation Management
  *    indirectly activated through 
  */
  #define CATOGMHistory_Management_GMLocalEdit    0x0000000000000001ULL
  #define CATOGMHistory_Management_GMDagScar      0x0000000000000002ULL

  class ExportedByCATOGMCore Management
  {
  public :
   /** 
    * nodoc
    */           
    static INLINE CATULONG64 IsActive(CATULONG64 iMask)        { return (iMask & CATOGMHistory::Management::_Mask) ; }

    /** 
    * nodoc
    */           
    static INLINE CATULONG64 AddActivation(CATULONG64 iMask)   { CATOGMHistory::Management::_Mask |= iMask; return CATOGMHistory::Management::_Mask; }
    /** 
    * nodoc
    */           
    static INLINE CATULONG64 ResetActivation(CATULONG64 iMask) { CATOGMHistory::Management::_Mask &= ~ iMask; return CATOGMHistory::Management::_Mask; }

    /** 
    * nodoc
    */           
    static void EndOfLifeCycle()  ;


  private :
    static CATULONG64  _Mask;
    Management(const Management &iCopy);
    Management& operator=(const Management &iCopy);
  };


  
  /**
  * Variable and relationships 
  *     
  */



  
  /** --------------------------------------------------------------------------------
  * Key Binding, about footprint reference on heterogenous modeling working form weak link  
  *   it also enable some symbol management 
  -------------------------------------------------------------------------------- */
  #define CATOGMHistory_Key_CATBaseUnknown    0x0000000000000010ULL
  #define CATOGMHistory_Key_GMOperator        0x0000000000000020ULL
  #define CATOGMHistory_Key_GMObject          0x0000000000000040ULL

  class ExportedByCATOGMCore Key
  {
  public :

    /** --------------------------------------------------------------------------------
    *   WOKING FORM :  Binding with running algorithms 
    * -------------------------------------------------------------------------------- **/

    INLINE Key() : _KeyImpl(NULL) {};
    ~Key() ;

    Key(const Key &iCopy);
    Key& operator=(const Key &iCopy);

    INLINE CATBoolean IsNull() const { return  _KeyImpl ? TRUE : FALSE; }


    /** 
    * nodoc, with available weak LifeCycle management (as Object Interface)
    */           
    static void FindOrCreate(CATBaseUnknown * iByAddress,  CATOGMHistory::Key & oKey );

    /** 
    * nodoc, with complementary local identifier (as CATCGMOperator with local history)
    */           
    static void FindOrCreate(void *  iByKey,             const CATULONG64      iType,  // CATOGMHistory_Key_XXX
                             const CATULONG64  iValue,   CATOGMHistory::Key &  oKey);


    /** 
    * nodoc, RFU  with available weak LifeCycle management (as Object Interface)
    */         
    void EndOfWorkingObject();
 
    /** 
    * nodoc, RFU  IsWorking
    */  
    void * IsWorking();


    /** --------------------------------------------------------------------------------
    *   Local  ATTRIBUTE 
    * -------------------------------------------------------------------------------- **/

    /** 
    * nodoc, allow extend definition with open attribute definition
    */           
    void FindOrCreate(const CATUnicodeString  & iForCreation, CATechAttribute * & oAttribute );

    /** 
    * nodoc, RFU  with available weak LifeCycle management (as Object Interface)
    */         
    void EndOfExtensions();



  private :
    Key(CATOGMHistoryKey *iKeyImpl);

    CATOGMHistoryKey *  _KeyImpl;

  };

 

};






#endif
