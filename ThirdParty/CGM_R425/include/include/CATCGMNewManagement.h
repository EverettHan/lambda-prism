#ifndef CATCGMNewManagement_H
#define CATCGMNewManagement_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2001
// CATCGMNewManagement : internal use for overloaded new/delete
//=============================================================================
class CATCGMMutex;
class CATCGMemoryPOOL;

  //----------------------------------------------------------------------------
  // Valeurs courantes de gestion des paquets d'objects
  //----------------------------------------------------------------------------  
  //   blocs         Chainage des blocs d'allocation de la meme famille
  //                 le pointeur du bloc suivant est indique a la fin du bloc
  //
  //   next       Indication de case disponible dans le bloc courant.
  //                  En cas de valeur nulle, le bloc a ete epuise
  //
  //   hole       Chainage des trous d'objects
  //             
  //----------------------------------------------------------------------------  

struct CATCGMNewManagement
{
  double       *blocs;   
  double       *next;  
  double       *hole; 
  CATCGMMutex  *mutex;
};



void catcgmnewStartLock(CATCGMemoryPOOL  *MemoryManager, CATCGMMutex  * & mutex);

void catcgmnewEndLock(CATCGMMutex  * & mutex);

#undef mkCheckSource_For_NullPointer_Equivalent_ToCoreDump_InAnyCase

#endif
