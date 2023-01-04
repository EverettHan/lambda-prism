#ifndef CATCGMObjectOwner_H
#define CATCGMObjectOwner_H
// COPYRIGHT DASSAULT SYSTEMES 1999
/** @CAA2Required */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
/** @nodoc */

//====================================================================================
// CATCGMObjectOwner 
//====================================================================================
#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "CATCGMOwner.h"
#include "ExportedByGeometricObjects.h"


class CATCGMObject;
class CATCGMDynObject;
class CATCGMNickName;


/** @nodoc */
class ExportedByGeometricObjects CATCGMObjectOwner  : public CATCGMOwner
{
public :

  /** @nodoc */
  CATCGMObjectOwner(CATCGMDynObject *iDynObject) ;

  /** @nodoc */
  CATCGMNewClassArrayDeclare;

  /** @nodoc */
  CATICGMUnknown     *GetInterface(); 

  /** @nodoc Release By Meta */
  CATBoolean  ReleaseByMeta( void * iMeta);

protected :

  /** @nodoc */
  virtual  ~CATCGMObjectOwner() ;
 

#if defined ( CATIACGMR215CAA )
    /** @nodoc (to implement with static method variable , type enabler ) */
  virtual  void * GetMeta();

 /** @nodoc (to implement with static method variable , type enabler ) */
  static  void * _GetMeta();

#endif


private :

  /** @nodoc */
  CATCGMDynObject *  _DynObject;

  /** @nodoc */
  CATCGMNickName   * _NickName;

  /** @nodoc */
  CATCGMObjectOwner(const CATCGMObjectOwner &iCopy);

  /** @nodoc */
  CATCGMObjectOwner& operator=(const CATCGMObjectOwner &iCopy);

  friend class CATCGMObject;
  friend class CATCGMDynObject;
};


#endif

