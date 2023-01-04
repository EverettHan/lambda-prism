// COPYRIGHT DASSAULT SYSTEMES 2003
//==========================================================================
//
// CATFrFConfiguration:
// Store CATSoftwareConfiguration + Specific FreeForm Data ( Tol etc ...)
//
//==========================================================================
//
// Usage notes:
//
//==========================================================================
// 10/10/03 JSX Creation
// 02/03/07 NLD Mise en prive du copy constructeur et de l'operateur = 
//              qui s'ils sont appeles dans l'implementation par defaut
//              assuree par C++ vont recopier les donnees
//              sans faire de AddRef et entrainer des Release surnumeraires
//              Je crois qu'il faudra carrement supprimer cet objet
//==========================================================================
//
#ifndef CATFrFConfiguration_H
#define CATFrFConfiguration_H
//
#include "CATGMOperatorsInterfaces.h"
#include "CATCGMVirtual.h"

class CATSoftwareConfiguration;

class ExportedByCATGMOperatorsInterfaces CATFrFConfiguration : public CATCGMVirtual
  {
  public :

    CATFrFConfiguration();
    CATFrFConfiguration(CATSoftwareConfiguration *iConfig);
    virtual ~CATFrFConfiguration();
    int SetSoftwareConfiguration(CATSoftwareConfiguration *iConfig);
  private : 
     // NLD020307 on rend impossible les affectations qui sinon
     // sont gerees directement par C++ et se font sans AddRef
     CATFrFConfiguration(const CATFrFConfiguration& iFrFConfiguration) ;
     void operator = (const CATFrFConfiguration& iFrFConfiguration) ;

  public :
    CATSoftwareConfiguration *_SoftwareConfiguration;
    
  };
#endif

