#ifndef CATCXTempoULONGPTR_H
#define CATCXTempoULONGPTR_H
// COPYRIGHT DASSAULT SYSTEMES 2001
//=====================================================================================
// For temporary transaction, allow performant quick attribute on V5 geometry
// But no overlapping are allowed on this kind of transaction
// Auteurs: TCX   
// Date: 14/11/2002
//=====================================================================================
#include "CATCGMTempoULONGPTR.h"
#include "ExportedByCATCGMFusion.h"

class CATCGMContainer;

class ExportedByCATCGMFusion CATCXTempoULONGPTR : public CATCGMTempoULONGPTR
{
public:
  //=================================================================
  //  Begin transaction  (autorisation des actions Set/Unset/Get)
  //=================================================================
  CATCXTempoULONGPTR(CATGeoFactory *iFactory);

  //=================================================================
  //  End transaction    (nettoyage des attributs)
  //=================================================================
  ~CATCXTempoULONGPTR();

  //=================================================================
  //  Analyse
  //=================================================================
  virtual CATGeoFactory* Factory() const ;

  //=====================================================================
  // Transaction Affectation/Reinitialisation/Lecture Valeur d'attribut
  //=====================================================================
  virtual void       Set   ( CATICGMUnknown *iObject , CATULONGPTR   iValue )  ;
  virtual void       Unset ( CATICGMUnknown *iObject )                         ;
  virtual CATBoolean Get   ( CATICGMUnknown *iObject , CATULONGPTR & ioValue)  ;

private :

  CATCGMContainer * const _Container;
};


#endif

