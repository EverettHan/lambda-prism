/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// CATDRepLabelRequestCGM
//
// Date of Creation : March 2019
// Reponsible : QF2
//
// DESCRIPTION  : Instanciable child class.
//                It is Streamable and should not be used directly.
//                This class is interfaced by CATDRepLabelRequest ( GMModelInterfaces )
//
//=============================================================================
#ifndef CATDRepLabelRequestCGM_H
#define CATDRepLabelRequestCGM_H

#include "PersistentCell.h"
#include "CATDRepLabelRequest.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"


class CATDRepLabel;
class CATICGMContainer;
class CATManifold;
class CATSoftwareConfiguration;
class CATBody;
class CATCGMOutput;
class CATMathStream;

class ExportedByPersistentCell CATDRepLabelRequestCGM : virtual public CATDRepLabelRequest 
{
public :

  //-------------------------------------------------------------------------
  // Constructeur unique
  //   - Construit sans Manifold dans l'interactif (clientele)
  //   - Construit avac Manifold en CGMReplay.
  //-------------------------------------------------------------------------
  CATDRepLabelRequestCGM(CATBody                  * ipBody, 
                        const CATDRepLabel        * ipDRepLabel, 
                        CATManifold               * ipManifold,
                        CATSoftwareConfiguration  * iConfig); 


  virtual ~CATDRepLabelRequestCGM();

  // surchage du new et du delete
  CATCGMNewClassArrayDeclare;

  //-------------------------------------------------------------------------
  // Implementation des methodes virtuelles pures
  //-------------------------------------------------------------------------
  virtual const CATDRepLabel  * GetDRepLabel()  const;
  virtual CATBody             * GetBody()       const;
  virtual CATManifold         * GetManifold()   const;

  // For CGMReplay
  virtual void    Dump(CATCGMOutput& Output) const;
  virtual HRESULT Stream(CATMathStream & ioStream) const;

  // Internal Use only  
  // virtual const CATDRepLabelRequestCGM & GetImpl() const;

  //-------------------------------------------------------------------------
  // CGM Methodes
  //-------------------------------------------------------------------------
  INLINE CATSoftwareConfiguration * GetSoftwareConfiguration() const;

protected:

  //friend CATDRepLabelRequestCGM * CATCreateDRepLabelRequestCGM( CATBody                  * ipBody, 
  //                                                              const CATDRepLabel       * ipDRepLabel, 
  //                                                              CATManifold              * ipManifold,  // can be null 
  //                                                              CATSoftwareConfiguration * iConfig);


  /**
	* Copy constructor. 
	**/
	CATDRepLabelRequestCGM(CATDRepLabelRequestCGM const& iOther);
	
	/**
	* Assignment operator.
	**/
	CATDRepLabelRequestCGM& operator=(CATDRepLabelRequestCGM const& iOther); 


protected :
  //-------------------------------------------------------------------------
  // Data
  //-------------------------------------------------------------------------
  CATManifold               * _Manifold;
  const CATDRepLabel        * _DRepLabel;
  CATBody                   * _pBody;
  CATSoftwareConfiguration  * _Config;

};

// ----------------------------------------------------------------------------------------------
INLINE CATSoftwareConfiguration * CATDRepLabelRequestCGM::GetSoftwareConfiguration() const {
// ----------------------------------------------------------------------------------------------
  return _Config; }

//-------------------------------------------------------------------------
// CATCreate for CGM
//-------------------------------------------------------------------------
CATDRepLabelRequestCGM * CATCreateDRepLabelRequestCGM(CATBody                   * ipBody, 
                                                      const CATDRepLabel        * ipDRepLabel, 
                                                      CATManifold               * ipManifold, // can be null
                                                      CATSoftwareConfiguration  * iConfig);


// UnStream for CGMReplay
CATDRepLabelRequestCGM * CATLoadDRepLabelRequestCGM(CATMathStream &iStream, CATICGMContainer *iFactory, CATSoftwareConfiguration *iConfig);

#endif

