#ifndef CATCGMArrayOfOrientedObjects_H
#define CATCGMArrayOfOrientedObjects_H
// COPYRIGHT DASSAULT SYSTEMES  2002
//=============================================================================
//
// Tableau d'objets avec orientation incluse
//
//=============================================================================
// February 2002  Creation                                T. Chailloux
//=============================================================================
#include "ExportedByGeometricObjects.h"
#include "CATDataType.h"
#include "CATGeometryType.h"
#include "CATCGMNewArray.h"
#include "CATCGMIndexOutOfRange.h"
#include "CATCGMArrayManagement.h"
#include "CATMathInline.h"

class CATICGMObject;

#define CATCGMArrayOfOrientedObjectstaticSize 4
#ifdef PLATEFORME_DS64
#define CATCGMOrientationHigh  ((CATULONGPTR) 0xFFFFFFFFFFFFFFF8)
#define CATCGMOrientationLow   ((CATULONGPTR) 0x0000000000000007)
#else
#define CATCGMOrientationHigh  ((CATULONGPTR) 0xFFFFFFF8)
#define CATCGMOrientationLow   ((CATULONGPTR) 0x00000007)
#endif



class  ExportedByGeometricObjects CATCGMArrayOfOrientedObjects
{
public:
  CATCGMArrayOfOrientedObjects(CATCGMArrayManagement iManage, CATGeometricType iControlType = CATUnknownGeometryType);

  CATCGMArrayOfOrientedObjects(const CATCGMArrayOfOrientedObjects& iOneOf); 
  CATCGMArrayOfOrientedObjects& operator =(const CATCGMArrayOfOrientedObjects& iOneOf);
  ~CATCGMArrayOfOrientedObjects();

  CATCGMNewClassArrayDeclare;

  //-------------------------------------------------------------------------------
  // Analyse du tableau (si N=Size() alors parcours [ 0, N-1 ])
  //-------------------------------------------------------------------------------
  INLINE int Size() const;

  INLINE CATICGMObject* operator[](const int idx) const; 
  INLINE int operator[](CATICGMObject *iObject) const; 

  INLINE CATICGMObject* Get(const int idx, short &ioOrientation) const; 
  INLINE int            Find(CATICGMObject *iObject,const short ioOrientation) const; 
  
  CATCGMArrayManagement GetManagement() const;

  //-------------------------------------------------------------------------------
  // Ajout, renvoie l'index d'insertion de l'element
  //-------------------------------------------------------------------------------
  int Add(CATICGMObject *iObject, const short iOrientation);

  //-------------------------------------------------------------------------------
  // Modification
  //-------------------------------------------------------------------------------
  int Modify(const int idx, CATICGMObject *iObject, const short iOrientation);

  //-------------------------------------------------------------------------------
  // Remove
  //-------------------------------------------------------------------------------
  int Remove(CATICGMObject *iObject, const short iOrientation );

  //-------------------------------------------------------------------------------
  // RemoveByIdx
  //-------------------------------------------------------------------------------
  CATICGMObject* RemoveByIdx(const int idx);

  //-------------------------------------------------------------------------------
  // Clear
  //-------------------------------------------------------------------------------
  void Clear();
  
  //-------------------------------------------------------------------------------
  // Perfo Memoire
  //-------------------------------------------------------------------------------
  void RequireMemory(const int nbObjects) const; 
  void PackMemory() const; 


  //-------------------------------------------------------------------------------
  // Analyse du choix de gestion du Tableau
  //-------------------------------------------------------------------------------
  INLINE short             IsDuplicationAuthorized() const;
  INLINE short             IsNullAuthorized()        const;
  INLINE short             IsAddRefReleaseManage()   const;
  INLINE short             IsControllingType()       const;
  INLINE CATGeometricType  GetGeometryType()         const;

  //-------------------------------------------------------------------------------
  // Messagerie d'erreur
  //-------------------------------------------------------------------------------
  void InvalidInput() const;
  
  
  //-------------------------------------------------------------------------------
  // Perfo CPU Sur les controles d'unicite DuplicationAuthorized
  // 
  //  A utiliser dans les transactions ou l'unicite est explicitement garantie en ajout
  //  Les controles internes sont alors temporairement desactive (perfo CPU)
  //  L'ancien mode de gestion est renvoye pour reaffectation en fin de transaction
  //-------------------------------------------------------------------------------
  CATBoolean SetDuplicationAuthorized(const CATBoolean iAuthorized); 

private:
  
  struct CATCGMOrientationCtrl
  {
    unsigned  int  _Unicity   :  1;  // Controle de redondance
    unsigned  int  _NoNull    :  1;  // Controle de nullite
    unsigned  int  _AddRef    :  1;  // Protection invalidite de pointeur
    unsigned  int  _Type      :  1;  // Controle de type des elements inseres
    unsigned  int  _Allocated : 28;  // Nombre d'element Maximal
  }
  _Ctrl;
  
  int               _Used;
  CATGeometricType  _GeoType; 
  
  
  CATULONGPTR *_Array;
  CATULONGPTR  _StaticArray[CATCGMArrayOfOrientedObjectstaticSize];
  
};

//----------------------------------------------------
// Denombrement 
//----------------------------------------------------
INLINE int CATCGMArrayOfOrientedObjects::Size() const
{
  return _Used;
}

//-------------------------------------------------------------------------------
// Idx 
//-------------------------------------------------------------------------------
INLINE CATICGMObject* CATCGMArrayOfOrientedObjects::Get(const int idx, short &ioOrientation) const
{
  CATCGMValidateRange(idx,0,_Used);

  CATULONGPTR value = _Array[idx];
  ioOrientation      = (short)(value & CATCGMOrientationLow) - 1;
  CATICGMObject *ptr = (CATICGMObject *) (value & CATCGMOrientationHigh);
  return  ptr;
}

//-------------------------------------------------------------------------------
// Find 
//-------------------------------------------------------------------------------
INLINE int CATCGMArrayOfOrientedObjects::Find(CATICGMObject *iObject,const short iOrientation) const 
{
  if ( (iOrientation < -1) || (iOrientation > 2) ) InvalidInput();
  CATULONGPTR seek = ((CATULONGPTR)iObject) | ((CATULONGPTR)(iOrientation + 1) );
  int idx = _Used;
  for ( ; (idx-- > 0) && (_Array[idx] != seek);  )
    ;
  return idx;
}

//-------------------------------------------------------------------------------
// CATICGMObject*    <--  [ const int idx ] 
//-------------------------------------------------------------------------------
INLINE CATICGMObject* CATCGMArrayOfOrientedObjects::operator[](const int idx) const
{
  CATCGMValidateRange(idx,0,_Used);

  CATULONGPTR value = _Array[idx];
  CATICGMObject *ptr = (CATICGMObject *) (value & CATCGMOrientationHigh);
  return  ptr;
}

//-------------------------------------------------------------------------------
//  const int idx   <--  [ CATICGMObject*  ] 
//-------------------------------------------------------------------------------
INLINE int CATCGMArrayOfOrientedObjects::operator[](CATICGMObject *iObject) const
{
  CATULONGPTR seek = (CATULONGPTR)iObject;
  int idx = _Used;
  for ( ; (idx-- > 0) && ((_Array[idx] & CATCGMOrientationHigh)  != seek) ; )
    ;
  return idx;
}

//-------------------------------------------------------------------------------
// Analyse du choix de gestion du Tableau
//-------------------------------------------------------------------------------
INLINE short             CATCGMArrayOfOrientedObjects::IsDuplicationAuthorized() const
{
  return (_Ctrl._Unicity) ? 0 : 1;
}

INLINE short             CATCGMArrayOfOrientedObjects::IsNullAuthorized()        const
{
  return (_Ctrl._NoNull) ? 0 : 1;
}


INLINE short             CATCGMArrayOfOrientedObjects::IsAddRefReleaseManage()   const
{
  return (_Ctrl._AddRef) ? 1 : 0;
}

INLINE short            CATCGMArrayOfOrientedObjects::IsControllingType()       const
{
  return (_Ctrl._Type) ? 1 : 0;
}

INLINE CATGeometricType  CATCGMArrayOfOrientedObjects::GetGeometryType()         const
{
  return (_Ctrl._Type) ? _GeoType : CATGeometryType;
}
  

#endif
