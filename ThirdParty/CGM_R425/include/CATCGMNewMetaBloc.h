#ifndef CATCGMNewMetaBloc_H
#define CATCGMNewMetaBloc_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  1999
// CATCGMNewMetaBloc : internal use for overloaded new/delete
//=============================================================================
#include <stdlib.h>
#include <stddef.h>
#include "CATMathematics.h"
#include "CATCGMNewArray.h"
#include "CATCGMNewManagement.h"
#include "CATBooleanDef.h"
#include "CATDataType.h"

class CATCGAMEM;
class CATCGMemoryPOOL;
class CATCGMPageAllocator;
class CATMathDebugCGM;
class CATMathODT;
class CATMathODTCGM;
class CATCGAMeasure;
 

class CATGemmemory;
class CATMVCDataFrmDialog;
class PDQFrmDialog;
 
class ExportedByCATMathematics CATCGMNewMetaBloc 
{
public :
  CATCGMNewClassArrayDeclare;
  
  CATCGMNewMetaBloc(const char *iClassname, size_t iInitialSize, const int iNBOBJ, 
                    CATCGMNewMetaBloc *&ioMyClass, CATCGMemoryPOOL *iPOOL);
  ~CATCGMNewMetaBloc();

  //----------------------------------------------------------------------------
  // Pouvoir identifier le CATCGMNewMetaBloc de gestion de lui-meme
  //----------------------------------------------------------------------------  
 static void Boot();


  //----------------------------------------------------------------------------
  // Constantes associees a la gestion de la classe 
  //----------------------------------------------------------------------------  
  char                 * _ClassName;   // nom de la classe (commodite)
  
  int                    _ObjDoubles;  // taille d'un object en nombre de 8 octets
  
  int                    _BlockObjs;  // taille allouee en nombre de 8 octets par blocs pour les objets
                                      // l'allocation est effectuee avec une ligne supplementaire de 8 octets

  //----------------------------------------------------------------------------
  // Statistiques de session
  //----------------------------------------------------------------------------  
  CATLONG64              _killed;     // nombre d'objects ayant vecu au cours de la session
  CATLONG64              _born;       // nombre d'objects ayant eu une existence au cours de la session
  CATLONG64              _maxintime;  // nombre simultanee d'objects en session
  CATLONG64              _allbytes;   // cumul des longueurs des zones d'allocations
  
  //----------------------------------------------------------------------------
  // Gestion de la donnee statique de Classe
  //----------------------------------------------------------------------------
  CATCGMNewManagement  * _CurManager;

  //----------------------------------------------------------------------------
  // POOL APPLICATIF DE GESTION MEMOIRE
  //----------------------------------------------------------------------------
  CATCGMemoryPOOL      * _POOL;    

  short                  _CurStatus;   /** @win64 fbq : 64-bit structure padding **/
  
  unsigned  short        _FirstSize;   // limitation (petits objets)
  
private :
  
  int                    _BlockNumberObj;   // Nombre d'objets par zone d'allocation
  

   void Init(const char *iClassname, size_t iInitialSize, const int iNBOBJ,
             CATCGMNewMetaBloc *&ioMyClass, CATCGMemoryPOOL *iPOOL);
   
  //------------------------------------------------------------------------
   // Famille = les objects de la meme classe
   //------------------------------------------------------------------------  
   CATCGMNewManagement    _DedicatedArrayByClass;    
   
   //----------------------------------------------------------------------------
   // Gestion de l'ensemble des classes ayant fait l'object d'une surcharge New 
   //----------------------------------------------------------------------------
   CATCGMNewMetaBloc   *  _NextClass;  // chainage des classes surchargees en new un MetaBloc par gestion de Classe
   
   //----------------------------------------------------------------------------
   //Variable statique de Classe servant a l'implementation du new/delete
   //----------------------------------------------------------------------------
   CATCGMNewMetaBloc   ** _ForDelete;

  //-----------------------------------------------------------------------
  // Debug management of all the class names
  //-----------------------------------------------------------------------

  friend class CATCGAMEM;
  friend class CATCGMemoryPOOL;
  friend class CATCGMPageAllocator;
  friend class CATMathDebugCGM;
  friend class CATMathODT;
  friend class CATMathODTCGM;
  friend class CATCGAMeasure;

  friend class CATGemmemory;
  friend class CATMVCDataFrmDialog;

  friend class PDQFrmDialog;
};

#endif

