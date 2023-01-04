#ifndef CATCGMTempoULONGPTR_H
#define CATCGMTempoULONGPTR_H
// COPYRIGHT DASSAULT SYSTEMES 2001
//=====================================================================================
//
// For temporary transaction, allow performant quick attribute on V5 geometry
// But no overlapping are allowed on this kind of transaction
// Auteurs: TCX   
// Date: 14/11/2002
//
//
//=====================================================================================
#include "CATGeometricObjects.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATBoolean.h"

class CATGeoFactory;
class CATICGMUnknown;

class ExportedByCATGeometricObjects CATCGMTempoULONGPTR : public CATCGMVirtual
{
public:
  //=================================================================
  //  Begin transaction  (autorisation des actions Set/Unset/Get)
  //=================================================================
  static CATCGMTempoULONGPTR * Create(CATGeoFactory *iFactory);

  //=================================================================
  //  End transaction    (nettoyage des attributs)
  //=================================================================
  // destructeur 

  //=================================================================
  //  Analyse
  //=================================================================
  virtual CATGeoFactory* Factory() const = 0;

  //=====================================================================
  // Transaction Affectation/Reinitialisation/Lecture Valeur d'attribut
  //=====================================================================
  virtual void       Set   ( CATICGMUnknown *iObject , CATULONGPTR   iValue )  = 0;
  virtual void       Unset ( CATICGMUnknown *iObject )                         = 0;
  virtual CATBoolean Get   ( CATICGMUnknown *iObject , CATULONGPTR & ioValue)  = 0;


protected :

  CATCGMTempoULONGPTR(CATGeoFactory *iFactory);
};


#endif

