/* -*-c++-*- */
#ifndef CATCGMDynObject_H
#define CATCGMDynObject_H
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
// CATCGMDynObject : Gestion des attributs 
//=============================================================================
#include "ExportedByGeometricObjects.h"
#include "CATListOfCATCGMAttribute.h"
#include "CATCGMNewArray.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATCGMFusion.h"
#include "CATCGMOwner.h"
#include "CATICGMObject.h"
#include "CATCGMObjectOwner.h"


class CATCGMNickName;
class CATCGMOutput;
class CATCGMContainer;
class CATCGMObject;
class CATCGMFusion;
 

//--------------------------------------------------------------------
// Les 8 octets suivants (en adressage 32 bits) sont occupes par 
//  couleur (16 bits = 2 octets) + 2 octets libres + gros UseCount)
//-------------------------------------------------------------------- 
struct CATCGMDynBits
{
  unsigned int	lock         : 1;
  unsigned int	noNeedToSave : 1;
  unsigned int	smart        : 1;
  unsigned int	unsmart      : 1;

  unsigned int  linkable     : 2;
  unsigned int  datum        : 1;
  unsigned int	rolled       : 1;
  
  unsigned int _HasTempoULONGPTR  : 1 ; 
  unsigned int _withColor         : 1 ;           
  unsigned int _Rep_NCGM          : 1 ;   


  unsigned int _IsDifferentialSaved : 1 ; 
  unsigned int _IsDifferential_ToModify  : 1 ;
	unsigned int _IsUndoLogged : 1;

  unsigned int _ToUnStreamedWithSharpness : 1 ;    
  unsigned int _ToUnStreamedWithLying : 1 ;    

  unsigned int _available           : 2 ;           

  unsigned int _red          : 4;             // Couleur atelier NCGM
  unsigned int _blue         : 4;             // Couleur atelier NCGM
  unsigned int _green        : 4;             // Couleur atelier NCGM
  unsigned int _alpha        : 4;             // Couleur atelier NCGM  
};


class ExportedByGeometricObjects CATCGMDynObject 
{
public :
  
  //--------------------------------------------------------------------
  // Les premiers 8 octets (en adressage 32 bits) sont occupes par 
  //    pointeur fonction virtuel + pointeur liste attribut
  //-------------------------------------------------------------------- 
  CATCGMDynObject(CATCGMFusion *iHolder);


  void ClearAllAttributes();

  virtual void    Clear();
  virtual size_t  GetDynamicMemoryBytes() const;   
  virtual size_t  GetStaticMemoryBytes() const;   

  CATCGMNewClassArrayDeclare;

    /** GetOwner  */
  CATCGMObjectOwner *GetOwner(CATBoolean iRequired = TRUE);

  /** Dump */
  virtual void  Dump( CATCGMOutput& os );

  /** GetGeoListCGMAttr */
  INLINE CATLISTP(CATCGMAttribute)  *GetGeoListCGMAttr();

  CATCGMDynBits       DynBits;
  
  CATULONG32         _BigUseCount;      // Nombre de références sur l'objet
  
  unsigned short     _StrongTopoLinkCount;
  unsigned short     _WeakTopoLinkCount;

  CATULONGPTR        _TempoULONGPTR; // Transaction CATCGMTempoULONGPTR

  CATCGMFusion     * _Holder;

  CATCGMObjectOwner * _Extension;


protected :

  virtual ~CATCGMDynObject();

  
private :

  CATLISTP(CATCGMAttribute)  *_GeoListCGMAttr; // Pointeur vers le premier attribut

  friend class CATCGMContainer;
  friend class CATCGMObject;

 
  CATCGMDynObject(const CATCGMDynObject&);
  CATCGMDynObject& operator = (const CATCGMDynObject&);
};

INLINE CATLISTP(CATCGMAttribute)  *CATCGMDynObject::GetGeoListCGMAttr() { return _GeoListCGMAttr; }

#endif

