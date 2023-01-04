#ifndef CATCGMFromFileToObjects_H
#define CATCGMFromFileToObjects_H
// COPYRIGHT DASSAULT SYSTEMES 2001
//=====================================================================================
//
// Dynamic Access to geometrical modelisation V5
//    from CATPart document 
//    from NCGM file
//    from CATCGMReplay document
//
// Auteurs: TCX   
// Date: 15/02/2002
//
//
//=====================================================================================
#include "CATGeometricObjects.h"
#include "CATListOfCATICGMObjects.h"
#include "CATListOfCATCGMFromFileToObjects.h"

#include "CATGeometryType.h"
#include "CATCGMFederatorsFilter.h"
#include "CATCGMVirtual.h"

class CATGeoFactory;

class ExportedByCATGeometricObjects CATCGMFromFileToObjects : public CATCGMVirtual
{
public:
  //=================================================================
  //  Load  (document or file with V5 geometry)
  //=================================================================
  static CATCGMFromFileToObjects * Create(const char iFilename[]);

  //=================================================================
  //  AnyOne : Close 
  //=================================================================
  virtual ~CATCGMFromFileToObjects();

  //=================================================================
  // AnyOne  Access to Filename
  //=================================================================
  const char *Filename() const;


  //=================================================================
  //  CATPart/NCGM   : Access to main Factory
  //=================================================================
  virtual CATGeoFactory* Factory() const = 0;

  //=================================================================
  //  CATPart/NCGM   : Access to federator Objects of modelisation
  //=================================================================
  virtual void Objects(CATLISTP(CATICGMObject) &ioFederators,
                       CATCGMFederatorsFilter    iFilterSpec = CATCGMFederatorsFilter_SpecifiedByDocument,
                       CATGeometricType          iFilterType = CATBodyType ) const = 0;

  //======================================================================
  // CATProduct/CATPart : Obtention et Chargement des references externes
  //======================================================================
  virtual void GetReferencedDocuments(CATLISTP(CATCGMFromFileToObjects) &ioReferenced) const = 0;


protected :

  CATCGMFromFileToObjects(const char iFilename[]);
  char *_Filename;
};


//=================================================================
//  Extract Main CATGeoFactory from File
//=================================================================
ExportedByCATGeometricObjects CATGeoFactory* CATExtractNCGMFromFile(const CATUnicodeString & iFileName ); 
 


#endif

