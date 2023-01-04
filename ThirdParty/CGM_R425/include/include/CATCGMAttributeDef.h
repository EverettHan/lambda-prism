/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCGMAttributeDef
//   this class describes the behavior af on attribute class which is 
//   recognized by a CATCGMAttrId
//=============================================================================
// Nov. 98 Creation                                                       JHN
// Apr. 03 MustUnstreamForLightBRepMode                                   HCN
// Apr. 03 MustStreamForStreamCompact                                     HCN 
// Apr. 05  Migration de CATMathStream\CATCGMStream vers la classe
//            d'implementation CATMathStreamImpl\CATCGMStreamImpl         HCN
//=============================================================================
#ifndef CATCGMAttributeDef_H
#define CATCGMAttributeDef_H


#include "CATCGMAttrId.h"
#include "YP0LOGRP.h"



class CATCGMAttributeDef; 
class CATCGMStreamCGMImpl;

typedef struct descdef
{
  // Identification par couple de Nom
  const char         * AppliName;
  const char         * DefName;

  // Identification par meta-classe RunTime d'attribut
  CATCGMAttributeDef * curdef;

  CATCGMConstrAttr     Creator;
}
DefAttr;


extern CATCGMAttributeDef * CATCGMAttribute__description;

//-----------------------------------------------------------------------------
class CATCGMAttributeDef 
{
  
public :
  
  
  static void       Search(const char * , const char *, const CATCGMAttributeDef * &, const int NoDynamicLoad = 0);
  static CATULONG32 Access( DefAttr * &tabdefs, short iAppend=0);
  static void       LostFiltered(char * iAppChar, char * iAttrDefChar);
 
  int  IsPersistent();  // 1 if attribute is streamable 0 else

  int  MustUnstreamForLightBRepMode() const; 

  int  MustStreamForStreamCompact() const;

  int  CATCGMStreamAttributeDirectoryBlackBox() const;
 
  inline const CATCGMAttrId * GetCGMAttrId() const ; // get the ID of attributes
  
  inline CATCGMConstrAttr     GetAttrFunc() const;   // get the construction function
  
  int                  IsATypeOf(const CATCGMAttrId * ); // 1 if current attribute is of the 
  // type recognized by CATCGMAttrId
  //
  // constructor-destructor
  //
  CATCGMAttributeDef(); 

  CATCGMAttributeDef(const CATCGMAttrId* localuaid,
                     CATCGMConstrAttr    CreateFunction,
                     CATCGMAttributeDef* fatherDef);

  CATCGMAttributeDef(const CATCGMAttrId* localuaid,
                     CATCGMConstrAttr    CreateFunction,
                     CATCGMAttributeDef* fatherDef,
                     int                 iMustUnstreamForLightBRepMode,
                     int                 iMustStreamForStreamCompact);
  ~CATCGMAttributeDef();          // destructor
  
    CATCGMNewClassArrayDeclare;  

		// 
		CATBoolean SingleOwnershipSingleAttribute();


private :
  
  friend class CATCGMStream;
  friend class CATCGMStreamAttribute;
  friend class CATCGMStreamCGMImpl;

  static void  Lost(char * AppChar, char * AttrDefChar);

  /** @nodoc */
  struct  CATCGMAttributeDefData
  {
    signed int    Persistent                   :  2;
    signed int    MustUnstreamForLightBRepMode :  2;
    signed int    MustStreamForStreamCompact   :  2;
    unsigned int  CATCGMStreamAttributeDirectoryDefined  :  1;
    unsigned int  CATCGMStreamAttributeDirectoryBlackBox :  1;

    unsigned int  SingleOwnershipSingleAttribute_Checked :  1;
    unsigned int  SingleOwnershipSingleAttribute         :  1;

    unsigned int  RFU                          : 22;

    int           IsStreaming;
    
    const CATCGMAttrId * ID;  // UAID of this type
    CATCGMAttributeDef * From; // class which is a father
    
    CATCGMConstrAttr     Create;   // Creation function of Attribute
  } 
  _CGM;
};


const CATCGMAttrId * CATCGMAttributeDef::GetCGMAttrId() const
{
  return _CGM.ID;
}

CATCGMConstrAttr CATCGMAttributeDef::GetAttrFunc() const 
{
  return _CGM.Create;
}



#endif








