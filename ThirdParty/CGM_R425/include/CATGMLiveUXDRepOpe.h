// COPYRIGHT DASSAULT SYSTEMES 2017, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : L. Marini 
//
// DESCRIPTION  : Class to Help the Application in showing symbolic representation of DelcarativeManifold and Parameters.
//
//=============================================================================
// Creation SOU March 2017
//
//=============================================================================
#ifndef CATGMLiveUXDRepOpe_H
#define CATGMLiveUXDRepOpe_H

#include "PersistentCell.h" // for dll
#include "CATDRepOperator.h"
//#include "CATTopOperator.h"
#include "CATBoolean.h"
#include "ListPOfCATManifold.h"
#include "ListPOfCATManifoldParameter.h" 
#include "CATMathPoint.h"

class CATGeoFactory;
class CATBody;
class CATCell;
class CATExtTopOperator;

//
// @nodoc @nocgmitf
class ExportedByPersistentCell  CATGMLiveUXDRepOpe : public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATGMLiveUXDRepOpe);
public:

  /**
  * @nodoc @nocgmitf
  * Constructor, don't access
  */
  CATGMLiveUXDRepOpe(CATGeoFactory* iFactory,  
                     CATTopData* iTopData,   
                     CATExtTopOperator* iImpl);

  /**
  * @nodoc @nocgmitf
  * Destructor
  */
  virtual ~CATGMLiveUXDRepOpe();

  void GetResultBodies(ListPOfCATBody& oUXPRepBodyList, ListPOfCATBody& oUXMRepBodyList);

  // -----------------------------------------------------------------------------------
  // CGM Internal Use
  // -----------------------------------------------------------------------------------
private:
  virtual const CATString * GetOperatorId(); 
  /** @nodoc @nocgmitf declaration integre au CGMReplay */
  void RequireDefinitionOfInputAndOutputObjects(); //
  /** @nodoc @nocgmitf */
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream); //
  /** @nodoc @nocgmitf */
  virtual void WriteInput(CATCGMStream  & os); //
  /** @nodoc @nocgmitf */
  virtual void Dump( CATCGMOutput& os ) ; //
  /** @nodoc @nocgmitf */
  virtual int RunOperator(); //
};

//Create the UXMRep and UXPRep only for the CATManifoldParameter and Manifold associated with iLocationCell of iCurrentBody
//update parameters corresponding to iLocationPoint
ExportedByPersistentCell HRESULT CATCreateUXDRepOpe(CATGeoFactory* iFactory, //to create result body in
                                                    CATSoftwareConfiguration* iConfig, //versionining
                                                    CATBody* iCurrentBody, //result body of ManifoldEditor, first time it is same than iFirstBody
                                                    CATCell* iLocationCell, //cell on which halo result bodies are expected
                                                    CATMathPoint* iLocationPoint, //optional point e.g in case of Variable fillet corresponding to ratio HVertex created by end user
                                                    ListPOfCATManifold& iCurrentManifoldList, //list of Manifolds in current body
                                                    CATBody* iFirstBody,  //input body of ManifoldEditor
                                                    ListPOfCATManifold& iFirstManifoldList, // list of Manifolds ( Declarative, CellManifoldGroup) in first Body
                                                    ListPOfCATManifoldParameter& ioParameterList, // list of parameters 
                                                    ListPOfCATBody& oUXPRepBodyList, //a body per parameter, one to one correspondance with input param list
                                                    ListPOfCATBody& oUXMRepBodyList); //a body per manifold, one to one correspondance with input Manifold Lists


#endif
