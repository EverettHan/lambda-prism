/* -*-C++-*- */

#ifndef CATlsoDynMetaData_H
#define CATlsoDynMetaData_H

#include "CATThrowForNullPointer.h"
#include "CATTopOpInError.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATMathInline.h"
#include "PersistentCell.h"
#include "CATGMQueue.h"


//#define LAP_REMOVE_FOR_COVERAGE ?? Pour rebrancher les subcriptions

class CATCGMOutput;
class CATCGMHashTableWithAssoc;
class CATCGMStream;


// Fixed correspondance for CGM Data Type
enum DynMetaData_OBJECT_TYPE
{
  META_DATA_Undefined = -1,

  // uniq type
  META_DATA_Boolean = 1,
  META_DATA_MathTransfo = 2,
  META_DATA_Geometry = 3,
  META_DATA_Cell = 4,
  META_DATA_Face = 5,
  META_DATA_Edge = 6,
  META_DATA_Vertex = 7,
  META_DATA_Double = 8,
  META_DATA_Interger = 9,


  // list type
  META_DATA_MathTransfoList = 22,
  META_DATA_GeometryList = 33,
  META_DATA_CellList = 44,
  META_DATA_FaceList = 55,
  META_DATA_EdgeList = 66,
  META_DATA_VertexList = 77,
  META_DATA_DoubleList = 88,
  META_DATA_IntergerList = 99,

  META_DATA_Struct = 101
};


class ExportedByPersistentCell CATlsoDynMetaData : public CATCGMVirtual
{

public:

  CATlsoDynMetaData();

  // Copy-constructeur et operateur = (affectation) dans la meme chaine
  // Attention, ces methodes n'etant pas heritees, elles devront etre
  // explicitement appelees dans les classes derivees (via les listes
  // d'initialisation pour les constructeurs, de base ou de copie)
  CATlsoDynMetaData(CATlsoDynMetaData& iOrig);
  //CATlsoDynMetaData& operator= (const CATlsoDynMetaData& iRight);

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;

  // Destructeur: ote l'element de la chaine mais ne decremente pas le compteur
  // afin de ne pas risquer de re-attribuer un vieux numero a un futur objet
  virtual ~CATlsoDynMetaData();


  // Attach method 
  // -----------------------------------------------------------------------------------------------------

  /* Attach new Data of any type
  *  @ iValue : the new Data
  *  @ METADATA : type of iValue (see enum DynMetaData_METADATA)
  *  @ iDataDescription : short describing (optionnal)

  * Return incremental KeyValue (int). It will be necessary to retrive your Data
  */
  int   AttachData (void *iValue, DynMetaData_OBJECT_TYPE iObjectType);

  /* Attach new Data of any type
  *  @ iValue : the new Data
  *  @ iKeyValue : Assign by yoursel the key storage. Carefull, you may overwrite a previous Data
  *  @ METADATA : type of iValue (see enum DynMetaData_METADATA)
  */
  void  AttachData (void *iValue, int iKeyValue, DynMetaData_OBJECT_TYPE iObjectType);


  // Finding data method
  // -----------------------------------------------------------------------------------------------------
  INLINE int  Size();

  void * GetData (int iKeyValue);
  int    GetType (int iKeyValue);
  void   GetDataAndType(int iKeyValue, void **oValue, DynMetaData_OBJECT_TYPE &oObjectType);

  // ========================================
  // Steam - UnStream 
  // ========================================
  virtual void Stream (CATCGMStream & ioStr);
  virtual void UnStream (CATCGMStream & iStr);

protected:

  CATCGMHashTableWithAssoc * _DynamicMetaData;
  CATCGMHashTableWithAssoc * _TypeCorrespondence; // parallel to _DynamicMetaData
  
  CATGMQueue<int>           _KeyManager; // stock les clés
  int                        _MaxKey;
};


// INLINE METHODS
INLINE int  CATlsoDynMetaData::Size() {
  return _KeyManager.Size(); }


#endif
  
