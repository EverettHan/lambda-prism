/* -*-C++-*- */

#ifndef CATCellManifoldSlotNavigator_H
#define CATCellManifoldSlotNavigator_H

// ----------------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// PRL: Feature recognition -- Slot Navigator 
//      Simple repompage de CATCellManifoldPadPocketNavigator + qqs modifs
// ----------------------------------------------------------------------------------------------//

#include "CATPersistentCell.h"

#include "CATCellManifoldSlotNavigatorInterface.h"

#include "CATDRepNavigator.h"
#include "CATExtrusionType.h"
#include "CATPadPocketManifoldAttribute.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"

//typedef enum 
//{
//  Unknown_Slot  = 0,
//  Blind_Slot    = 1,  
//  Through_Slot  = 2
//}
//CATSlotType;

class CATLiveBody;
class CATCellManifold;
class CATCellManifoldGroup;
class CATCellManifoldExtrusionNavigatorData;


class ExportedByPersistentCell CATCellManifoldSlotNavigator : public CATCellManifoldSlotNavigatorInterface
{
public:

  // Constructor
	CATCellManifoldSlotNavigator();
  CATCellManifoldSlotNavigator(CATLiveBody          * iLiveBody, 
                               CATCellManifoldGroup * iNetworkGroup); 
  CATCellManifoldSlotNavigator(CATDRepNavigator     * iDrepNavigator, 
                               CATCellManifoldGroup * iNetworkGroup); 

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  // Attribute Declaration
  CATCGMDeclareManifoldNavigator(CATCellManifoldSlotNavigator, CATCellManifoldSlotNavigatorInterface);
  //CATCGMNewClassArrayDeclare;      // Pool allocation

  // Destructor
  virtual ~CATCellManifoldSlotNavigator();

  CATCellManifoldSlotNavigator * GetAsSlotNavigator();

  //Interface methods

  // Implement pure virtual methods from CATCellManifoldExtrusionNavigatorInterface
  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const;

  virtual HRESULT GetDeclarativeType(CATDeclarativeType &oType) const;
  virtual HRESULT GetExtrusionType(CATExtrusionType & oType) const;
  virtual HRESULT GetExtrusionDirection(CATMathVector & oDir) const;
  virtual HRESULT GetExtrusionFaces(ListPOfCATCellManifold & oCMFaces) const;
  virtual HRESULT GetExtrusionSupports(ListPOfCATCellManifold & oCMFaces) const;
  virtual HRESULT GetExtrusionEnds(ListPOfCATCellManifold & oCMFaces) const;
  virtual HRESULT GetExtrusionExits(ListPOfCATCellManifold & oCMFaces) const;

  virtual HRESULT GetExtrusionSupportDeco(ListPOfCATCellManifold & oCMFaces) const; 
  virtual HRESULT GetExtrusionEndDeco(ListPOfCATCellManifold & oCMFaces) const;

  virtual HRESULT GetAllCellManifolds(ListPOfCATCellManifold & oCellManifolds) const;
    virtual HRESULT GetTransitionFaces(ListPOfCATCellManifold & oCMFaces) const;

  virtual CATBoolean BelongsToExtrusion(CATCellManifold * iCM) const;

	virtual CATLiveBody& GetLiveBody() const;

	// Implement pure virtual methods from CATCellManifoldSlotNavigatorInterface
  virtual HRESULT IsBlind                         (CATBoolean &oIsBlind)    const;
  virtual HRESULT GetSlotWidth                    (double     &oWidth)      const; 
  virtual HRESULT GetSlotLength                   (double     &oLength)     const; // if round slot, length is the distance between the the two cylinder axis
  virtual HRESULT GetDepth(double & oDepth) const;

protected:

  //virtual HRESULT GetSlotType    (CATSlotType & oType) const;
  void Dump(CATCGMOutput& Output);
  void Init();

private:
  CATCellManifoldExtrusionNavigatorData *_pExtrusionNavigatorData;
  CATSlotManifoldAttribute * _SlotAttr;
};

// ---------------------------------------
// CATCreateCellManifoldSlotNavigator
// ---------------------------------------
ExportedByPersistentCell CATCellManifoldSlotNavigator * CATCreateCellManifoldSlotNavigator(CATLiveBody          * iLiveBody,
																						                                        			 CATCellManifoldGroup * iNetworkGroup); 


#endif
