//=======================================================================
// Copyright Dassault Systemes Provence 2005, All Rights Reserved 
//=======================================================================
//
// CATSobAttributesId.h
//
//=======================================================================
// November,  2007 : RBD : Destructeur virtual (Art. 22 DS C++ Programming Rules)
// November   2007 : RNO : Creation Nouvelle Gestion des Attributs (Support du Multi Attribut)


#ifndef CATSobAttributesID_H
#define CATSobAttributesID_H

#include "CATSobObjects.h"

#include "CATBoolean.h"

#include "CATDataType.h"


//static char * const CATSobAttributesType_Modifier="Modifier";




class ExportedByCATSobObjects CATSobAttributesId
{
public:
  //Constructeur
  CATSobAttributesId(char * const IdName);
  //Gestion références
  virtual int AddRef();
  virtual int Release();
  /**
  * Equality operator.
  * @return
  * The result of the test.
  * <tt>1</tt> if true, <tt>0</tt> otherwise.
  */
  int operator==(const CATSobAttributesId &iToCompare);
  int IsSimilarTo(CATSobAttributesId *) const ;
  /**
  * Inequality operator.
  * @return
  * <tt>1</tt> if they are different, <tt>0</tt> otherwise.
  */
  int operator!=(const CATSobAttributesId &iToCompare);
  
  CATSobAttributesId& operator=(CATSobAttributesId&);
  
protected:

  
  //Destructeur
  virtual ~CATSobAttributesId();
    
  CATSobAttributesId(CATSobAttributesId&);
  inline char * const GetType(){return(_Type);}
 private:
  char * const _Type;
  
  //Copy construct and equal operator
  CATSobAttributesId();
  
  char * const CopyType() const;
  
  int _RefCounter;

};

//---------------------
// Gestion références
//---------------------
inline int CATSobAttributesId::AddRef()
{
  return ++_RefCounter;
}


inline int CATSobAttributesId::Release()
{
  int RefCount= --_RefCounter;
  if(RefCount<=0) delete this;
  return(RefCount);
}


class ExportedByCATSobObjects CATSobAttributesIdStatic
{
public:
  //Constructeur
  CATSobAttributesIdStatic(char * const IdName);//Will Build a CATSobAttributesId 
  CATSobAttributesIdStatic(CATSobAttributesId* iD);
  virtual ~CATSobAttributesIdStatic();
  CATSobAttributesId * GetId();
  void SetId(CATSobAttributesId * iD);
private:
  CATSobAttributesId *_Id;
  
};

/*Our Nice Global Var*/ 
/*Function Implementation*/
/*Build the static Handler*/
/*Return the pointer of CATSobAttributesId that is inside the static Handler !*/




#define   CATDECLARESOBATTRIBUTE(itype, VAR) \
static  CATSobAttributesId * itype##IDInitializer(); \
static  CATSobAttributesId * itype##IDInitializer() \
{ \
return(new CATSobAttributesId(#itype));\
} \
static CATSobAttributesId * VAR=itype##IDInitializer() ; \
static  CATSobAttributesIdStatic VAR##IDStatic(VAR);



/*
static CATSobAttributesId * CATSobModifierAttributesIDInitializer()
{
return(new CATSobAttributesId("CATSobModifierAttributes"));
}
static CATSobAttributesId * CATSobModifierAttributesID=CATSobModifierAttributesIDInitializer() ;
static CATSobAttributesIdStatic CATSobModifierAttributesIDStatic(CATSobModifierAttributesID);
*/


#endif
