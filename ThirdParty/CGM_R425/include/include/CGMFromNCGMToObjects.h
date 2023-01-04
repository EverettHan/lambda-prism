#ifndef CGMFromNCGMToObjects_H
#define CGMFromNCGMToObjects_H
// COPYRIGHT DASSAULT SYSTEMES  2002
/** 
 * Utilitaire  
 */
//===================================================================================================
//  Le proxy d'implementation du fichier NCGM
//===================================================================================================
#include "CATCGMFromFileToObjects.h"


class CGMFromNCGMToObjects : public CATCGMFromFileToObjects
{
public :
  CGMFromNCGMToObjects(const char iFilename[], CATGeoFactory* iFactory);
  virtual ~CGMFromNCGMToObjects();

  //=================================================================
  //  CATPart/NCGM   : Access to main Factory
  //=================================================================
  virtual CATGeoFactory* Factory() const;

  //=================================================================
  //  CATPart/NCGM   : Access to federator Objects of modelisation
  //=================================================================
  virtual void Objects(CATLISTP(CATICGMObject) & ioFederators,
                       CATCGMFederatorsFilter    iFilterSpec = CATCGMFederatorsFilter_SpecifiedByDocument,
                       CATGeometricType          iFilterType = CATBodyType ) const;
  
  //======================================================================
  // CATProduct/CATPart : Obtention et Chargement des references externes
  //======================================================================
  virtual void GetReferencedDocuments(CATLISTP(CATCGMFromFileToObjects) &ioReferenced) const;
  

private :
  CATGeoFactory*_Factory;
};

#endif

