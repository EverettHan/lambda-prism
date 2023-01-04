//=======================================================================
// Copyright Dassault Systemes Provence 2005, All Rights Reserved 
//=======================================================================
//
// CATSobAttributes.h
//
//=======================================================================
//
// Usage notes: Classe mère pour accrocher des attributs aux éléments
//              de structure de la subdivision
//              Les classes sont definis par famille (nom de famille) c'est a dire le CATSobAttributesType
//              on peut completer l'identification par une methode GetSecondName() (prenom) pour avoir plusieurs instances de la meme famille.
//              Ce second nom optionnel est defini par un void * par la methode GetScondName();
//
//=======================================================================
// November,    2007 : RBD : Destructeur virtual (Art. 22 DS C++ Programming Rules)
// November,    2007 : RNO : Creation Nouvelle Gestion des Attributs (Support du Multi Attribut)
//                         Lazy Attributes Type not as powerfull CATCGMAttributes but by far easier to implement
//                          and no need to modify any .dic file
// September,   2007 : RAQ : Destruction par release
// January,     2005 : RAQ : Creation
//=======================================================================
#ifndef CATSobAttributes_H
#define CATSobAttributes_H

#include "CATSobObjects.h"

#include "CATBoolean.h"

#include "CATDataType.h"
#include "CATSobAttributesId.h"





class ExportedByCATSobObjects CATSobAttributes
{
public:
  
  //Gestion références
  virtual int AddRef();
  virtual int Release();
 
  inline CATLONGPTR GetName() const {return(_Name);};
  
  inline CATSobAttributesId * GetAttrId() const {return(_AttrId);};
  /**
  * Equality operator.
  * @return
  * The result of the test.
  * <tt>1</tt> if true, <tt>0</tt> otherwise.
  */
  int operator==(const CATSobAttributes &iToCompare);

  /**
  * Inequality operator.
  * @return
  * <tt>1</tt> if they are different, <tt>0</tt> otherwise.
  */
  int operator!=(const CATSobAttributes &iToCompare);
  
  int IsSame(CATSobAttributesId * iAttrID, CATLONGPTR iName) const;
protected:
  //Constructeur
  CATSobAttributes(CATSobAttributesId * iAttrID, CATLONGPTR iName=0);
  
  //Destructeur
  virtual ~CATSobAttributes();
    
  CATSobAttributes(CATSobAttributes&);
  
 private:
  CATLONGPTR _Name;
  CATSobAttributesId * _AttrId;
  //Copy construct and equal operator
  CATSobAttributes();
  CATSobAttributes& operator=(CATSobAttributes&);
  
  int _RefCounter;

};

//---------------------
// Gestion références
//---------------------
inline int CATSobAttributes::AddRef()
{
  return ++_RefCounter;
}


inline int CATSobAttributes::Release()
{
  int RefCounter=--_RefCounter;
  if(RefCounter<=0) delete this;
  return RefCounter;
}





 
//CATDECLARESOBATTRIBUTE(CATSobModifierAttributes, CATSobModifierAttributesID)

ExportedByCATSobObjects CATSobAttributesId * GetModifierID();
#define CATSobModifierAttributesID GetModifierID()

class ExportedByCATSobObjects CATSobModifierAttributes : public CATSobAttributes
{


public :
  //Gestion des infos de modifications de la cellule
  virtual CATBoolean IsModified() const;
  virtual void SetModified(const CATBoolean iIsModified = TRUE);

protected:

  //Constructeur
  CATSobModifierAttributes();

 
  
  //Destructeur
  virtual ~CATSobModifierAttributes() {};



  //----- Data
  unsigned char _BinaryInfos;
  /*
  * Bit 1: Not Modified (0) / Modified (1)
  * Bit 2: Not used
  * Bit 3: Not used
  * Bit 4: Not used
  * Bit 5: Not used
  * Bit 6: Not used
  * Bit 7: Not used
  * Bit 8: Not used
  */
  private:
 //Constructeur (For Derived Classes
  CATSobModifierAttributes(CATSobAttributesId * iType, CATLONGPTR iName=0);

//CATDECLAREASOBATTRID(CATSobModifierAttributes,CATSobAttributesType_Modifier);
};


//----------------------------------------------------
// Gestion des infos de modifications de la cellule
//----------------------------------------------------
inline CATBoolean CATSobModifierAttributes::IsModified() const
{
  return (_BinaryInfos&0x01) ? TRUE : FALSE;
}


inline void CATSobModifierAttributes::SetModified(const CATBoolean iIsModified)
{
  if(iIsModified)
    _BinaryInfos|=0x01;
  else
    _BinaryInfos&=0xFE;
}



//static char * const CATSobAttributesType_Rank="Rank";

//CATDECLARESOBATTRIBUTE(CATSobSafeRankAttr, CATSobSafeRankAttrID)
//#define CATSobAttributesType_Rank CATSobSafeRankAttrID

ExportedByCATSobObjects CATSobAttributesId * GetRankID();
#define CATSobAttributesType_Rank GetRankID()
class ExportedByCATSobObjects CATSobSafeRankAttr : public CATSobAttributes
{
  
public :
  //Gestion des infos de modifications de la cellule
  inline CATSobSafeRankAttr(CATLONGPTR iName):CATSobAttributes(CATSobAttributesType_Rank,iName),_Rank(0){};
  
  //Constructor for derived Classes
  inline CATSobSafeRankAttr(CATSobAttributesId * iType, CATLONGPTR iName=0):CATSobAttributes(iType,iName),_Rank(0){};
  inline void SetRank(unsigned int iRank){_Rank=iRank;};
  inline unsigned int GetRank(){return(_Rank);};

  //Destructeur
  virtual ~CATSobSafeRankAttr() {};
  private:
  unsigned int _Rank;
};

#endif




