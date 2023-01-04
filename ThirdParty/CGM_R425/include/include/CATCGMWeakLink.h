/* -*-c++-*- */
#ifndef CATCGMWeakLink_h
#define CATCGMWeakLink_h
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//============================================================================
#include "ExportedByCATCGMFusion.h"
#include "CATDataType.h"

class CATCGMContainer;
class CATCGMObject;
class CATCGMOutput;
class CATSubdOccurence;

#ifndef NULL
#define NULL 0
#endif

class ExportedByCATCGMFusion CATCGMWeakLink 
{
public:
  CATCGMWeakLink(CATCGMContainer *master);

  //---------------------------------------------------------------------------
  // Gestion du dechainage de la CATGeoFactory d'un object reference par des Weak-Links
  //            (synchronisation voulue pour eviter les pointeurs invalides)
  //---------------------------------------------------------------------------
   virtual void ChainRemove(CATCGMObject *obj, CATSubdOccurence* iRef = NULL) = 0; 

  //---------------------------------------------------------------------------
  // Enumeration des objects references par liens Faibles
  //---------------------------------------------------------------------------
   virtual void Dump( CATCGMOutput& os ) = 0;

  //---------------------------------------------------------------------------
  // Detection de la presence de liens Faibles (liens PoseSur)
  //---------------------------------------------------------------------------
   virtual CATLONG32 GetNumberOfWeakLinks() const = 0;


protected :

  //---------------------------------------------------------------------------
  // Seul le Close de Factory peut permettre le declenchement du delete
  //---------------------------------------------------------------------------
  virtual ~CATCGMWeakLink();

  friend class CATCGMContainer;
  friend class CATRootSharedDataCGM;

private:
  //---------------------------------------------------------------------------
  // proprietaires (le CATRootContainerCGM implicite)
  //---------------------------------------------------------------------------
  CATCGMContainer *_master;

};

#endif


