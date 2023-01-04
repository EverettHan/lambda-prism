/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// CATManifoldModificationCGM
//
// Date of Creation : March 2019
// Reponsible : QF2
//
// DESCRIPTION  : Instanciable child class.
//                It is Streamable and should not be used directly.
//                This class is interfaced by CATManifoldModification ( GMModelInterfaces )
//
//=============================================================================
#ifndef CATManifoldModificationCGM_H
#define CATManifoldModificationCGM_H

#include "PersistentCell.h"
#include "CATManifoldModification.h"
#include "CATDRepLabelRequestCGM.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATBody.h"
#include "CATMathInline.h"


class CATDRepLabel;
class CATManifoldParamId;
class CATManifoldModification;
class CATICGMContainer;
class CATManifold;
class CATSoftwareConfiguration;
class CATBody;
class CATCGMOutput;
class CATOneDRepModification;

// class ExportedByPersistentCell CATManifoldModificationCGM : public CATManifoldModification 

// #pragma warning( disable : 4250)

class ExportedByPersistentCell CATManifoldModificationCGM : public CATDRepLabelRequestCGM, public CATManifoldModification
{
public :

  //-------------------------------------------------------------------------
  // Constructeur unique
  //   - Construit sans Manifold dans l'interactif (clientele)
  //   - Construit avac Manifold en CGMReplay.
  //-------------------------------------------------------------------------
  CATManifoldModificationCGM(const ListPOfCATBody &iSystemBodies, 
                             CATBody              *ipRightBody,
                             const CATDRepLabel   *ipDRepLabel, 
                             CATManifold          *ipManifold, // can be nul 
                             CATManifoldParamId   *ipManifoldParamId, 
                             CATSoftwareConfiguration *iConfig = NULL); // should not be nul


  virtual ~CATManifoldModificationCGM();

  // surchage du new et du delete
  CATCGMNewClassArrayDeclare;



  //-------------------------------------------------------------------------
  // Implementation des methodes virtuelles pures
  //-------------------------------------------------------------------------
  INLINE virtual const CATDRepLabel      * GetDRepLabel()  const { return CATDRepLabelRequestCGM::GetDRepLabel() ; }
  INLINE virtual CATBody                 * GetBody()       const { return CATDRepLabelRequestCGM::GetBody() ; }
  INLINE virtual CATManifold             * GetManifold()   const { return CATDRepLabelRequestCGM::GetManifold() ; }
  INLINE virtual CATManifoldModification * GetAsManifoldModification() const { return CATManifoldModification::GetAsManifoldModification(); }

  virtual CATManifoldParamId  * GetManifoldParamId() const;

  virtual HRESULT GetBodies(ListPOfCATBody & oSystemBodies) const;


  // (without ParamId value)
  virtual HRESULT StreamWithoutParamValue(CATMathStream & ioStream) const;
  
  // For CGMReplay
  virtual void Dump(CATCGMOutput& Output) const;
  virtual HRESULT Stream(CATMathStream & ioStream) const;

  // Internal Use only
  virtual const CATOneDRepModification * GetAsOneDRepModification() const;
  virtual const CATManifoldModificationCGM & GetImpl() const;

  //-------------------------------------------------------------------------
  // CGM Methodes
  //-------------------------------------------------------------------------
  CATLONG32  GetKey() const;
  CATBoolean IsReplicatedParam() const;

protected:

  friend CATManifoldModificationCGM * CATCreateManifoldModificationCGM( const ListPOfCATBody &iSystemBodies, 
                                                                        const CATDRepLabel   *ipDRepLabel, 
                                                                        CATManifold          *ipManifold, 
                                                                        CATManifoldParamId   *ipManifoldParamId, 
                                                                        CATSoftwareConfiguration *iConfig);

  // Constructeur pour OneDRepModif
  CATManifoldModificationCGM(CATBody *ipBody, CATManifold *ipManifold, CATManifoldParamId *ipManifoldParamId, CATSoftwareConfiguration *iConfig);

  void SetModification(CATManifoldParamId *ipManifoldParamId);
  void SetModification(CATBody *ipBody, CATManifoldParamId *ipManifoldParamId);

  virtual const ListPOfCATBody & GetBodies() const;

  /**
	* Copy constructor. 
	**/
	CATManifoldModificationCGM(CATManifoldModificationCGM const& iOther);
	
	/**
	* Assignment operator.
	**/
	CATManifoldModificationCGM& operator=(CATManifoldModificationCGM const& iOther); 


private:
  //-------------------------------------------------------------------------
  // Data
  //-------------------------------------------------------------------------
  CATManifoldParamId        * _ManifoldParamId;
  ListPOfCATBody              _SystemBodies;

  CATBoolean                  _ReplicatedParam;
};


//INLINE CATSoftwareConfiguration * CATManifoldModificationCGM::GetSoftwareConfiguration() const {
//  return _Config; }
//
//INLINE CATManifold * CATManifoldModificationCGM::GetManifold () const {
//  return _Manifold; }

//-------------------------------------------------------------------------
// CATCreate for CGM
//-------------------------------------------------------------------------
CATManifoldModificationCGM * CATCreateManifoldModificationCGM(const ListPOfCATBody &iSystemBodies, 
                                                              const CATDRepLabel   *ipDRepLabel, 
                                                              CATManifold          *ipManifold, 
                                                              CATManifoldParamId   *ipManifoldParamId, 
                                                              CATSoftwareConfiguration *iConfig);

//-------------------------------------------------------------------------
// Official unstream SPEC methode (without paramid value)
//-------------------------------------------------------------------------
HRESULT CATLoadManifoldModifWithoutValueCGM(CATMathStream & ioStream, CATICGMContainer *iFactory, CATManifoldModification *& oUnStreamManifoldModif);

// UnStream for CGMReplay
CATManifoldModification * CATLoadManifoldModificationCGM(CATCGMStream &ioStream, CATICGMContainer *iFactory, CATSoftwareConfiguration *iConfig);

#endif

