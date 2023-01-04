// ----------------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// ZUS: Feature recognition -- Hole Navigator Implementation -- | Agent navigator |
// ----------------------------------------------------------------------------------------------//

#ifndef CATCellManifoldHoleNavigator_H
#define CATCellManifoldHoleNavigator_H

#include "CATPersistentCell.h"

#include "CATCellManifoldHoleNavigatorInterface.h"

#include "CATCellManifoldGroupNavigator.h"
#include "CATDRepNavigator.h"
#include "CATExtrusionType.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATlsoBodyUtil.h"

class CATMathLine;
class CATLiveBody;
class CATCellManifold;
class CATCellManifoldGroup;
class CATHoleManifoldAttribute;
class CATCellManifoldExtrusionNavigatorData;

class ExportedByPersistentCell CATCellManifoldHoleNavigator : public CATCellManifoldHoleNavigatorInterface
{
public:

  typedef enum
  {
    UnknownHoleType = 0,
    Simple = 1,
    CounterBored = 2,
    CounterSunk = 3,
    CounterDrilled = 4,
    General = 5,
    Tapered = 6  //RL1
  }
  CATHoleType;


  // Constructor
  CATCellManifoldHoleNavigator(); 
  CATCellManifoldHoleNavigator(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup); 
  CATCellManifoldHoleNavigator(CATDRepNavigator * iDrepNavigator, CATCellManifoldGroup * iNetworkGroup); 

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  // Attribute Declaration
  CATCGMDeclareManifoldNavigator(CATCellManifoldHoleNavigator, CATCellManifoldHoleNavigatorInterface);
  //CATCGMNewClassArrayDeclare;      // Pool allocation

  // Destructor
  virtual ~CATCellManifoldHoleNavigator();

  CATCellManifoldHoleNavigator * GetAsHoleNavigator();

  //Interface methods

  // Implement pure virtual methods from CATCellManifoldExtrusionNavigatorInterface
  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const;

  virtual HRESULT GetDeclarativeType(CATDeclarativeType &oType) const;
  virtual HRESULT GetExtrusionType(CATExtrusionType & oType) const;
  //NOTE: do not use GetExtrusionDirection to get the hole axis/direction. Use GetHoleAxis method instead
  virtual HRESULT GetExtrusionDirection(CATMathVector & oDir) const;
  virtual HRESULT GetExtrusionFaces(ListPOfCATCellManifold & oCMFaces) const;
  virtual HRESULT GetExtrusionSupports(ListPOfCATCellManifold & oCMFaces) const;
  virtual HRESULT GetExtrusionEnds(ListPOfCATCellManifold & oCMFaces) const;
  virtual HRESULT GetExtrusionExits(ListPOfCATCellManifold & oCMFaces) const;

  virtual HRESULT GetExtrusionSupportDeco(ListPOfCATCellManifold & oCMFaces) const; 
  virtual HRESULT GetExtrusionEndDeco(ListPOfCATCellManifold & oCMFaces) const;

  virtual HRESULT GetAllCellManifolds(ListPOfCATCellManifold & oCellManifolds) const;

  virtual CATBoolean BelongsToExtrusion(CATCellManifold * iCM) const;

	virtual CATLiveBody& GetLiveBody() const;

  // Implement pure virtual methods from CATCellManifoldHoleNavigatorInterface
  virtual HRESULT GetClogType(CATHoleClogType &oClogType, CATAngle &oAngle) const;

  //NOTE: do not use GetExtrusionDirection to get the hole axis/direction. Use this method instead
	/**
	* Returns the axis of this hole feature, encapsulated as a <tt>CATMathLine</tt>  
	* object. 
	* <br><b>Role</b>: The origin of the axis is a projection from the 
	* point on the hole entrance furthest away from the end of the hole.
	* Its direction is a unit vector oriented from the support to the end
	* of the hole.
	* @param oAxis
	* The axis.
	* @param oIsAmbiguous
	* TRUE if the orientation of the hole is ambiguous; FALSE if otherwise, in which case the orienation is provided by oAxis.
	**/
  virtual HRESULT GetHoleAxis(CATMathLine &oAxis, CATBoolean & oIsAmbiguous) const;

  // i49 - Do not use in any new evolutions (Use GetTransitionFaces instead)
  virtual HRESULT GetHoleIntermediateFaces(ListPOfCATCellManifold & oCMFaces) const;
  virtual HRESULT GetTransitionFaces(ListPOfCATCellManifold & oCMFaces) const;

  // Simple Hole
  virtual HRESULT GetSimpleHoleParameters(double & oDiameter, double & oDepth) const;
  virtual HRESULT GetSimpleHoleParameters(double & oDiameter) const;

  //Tapered Hole RL1
  virtual HRESULT GetTaperedHoleParameters( double & oDiameter, 
                                            double & oDepth, 
                                            CATAngle & oTaperedAngle) const;
  virtual HRESULT GetTaperedHoleParameters( double & oDiameter,
                                            double & oTaperedAngle) const;

  // Countersunk Hole
  virtual HRESULT GetCountersunkHoleParameters( double & oPrimaryDiameter, 
                                                double & oDepth, 
                                                double & oCountersinkDepth, 
                                                CATAngle & oCountersinkAngle) const;
  virtual HRESULT GetCountersunkHoleParameters( double & oPrimaryDiameter, 
                                                CATAngle & oCountersinkAngle) const;
  
  // Counterbored Hole
  virtual HRESULT GetCounterboredHoleParameters(double & oPrimaryDiameter, 
                                                double & oCounterboreDiameter, 
                                                double & oDepth, 
                                                double & oCounterboreDepth) const;
  virtual HRESULT GetCounterboredHoleParameters(double & oPrimaryDiameter, 
                                                double & oCounterboreDiameter) const;
  
  // Counterdrilled Hole
  virtual HRESULT GetCounterdrilledHoleParameters(double & oPrimaryDiameter, 
                                                double & oCounterdrillDiameter, 
                                                double & oDepth, 
                                                double & oCounterdrillDepth,
                                                CATAngle & oCounterdrillAngle) const;
  virtual HRESULT GetCounterdrilledHoleParameters(double & oPrimaryDiameter, 
                                                double & oCounterdrillDiameter, 
                                                CATAngle & oCounterdrillAngle) const;

  virtual HRESULT GetHoleSignature( CATLISTV(CATFeaturePiece) & oHolePieces) const;

  virtual HRESULT GetMinDiameter(double & oMinDiameter) const;
  virtual HRESULT GetMaxDiameter(double & oMaxDiameter) const;
  virtual HRESULT GetDepth(double & oDepth) const;

  virtual HRESULT IsCompatible(CATCellManifoldPadPocketNavigatorInterface const* ipPad, CATHolePadFitType & oFitType, double iFitTolerance) const;

  //-------------------------------------------------
  //   Stream / Unstream 
  //-------------------------------------------------

  // @nocgmitf
  //-------------------------------------------------------------------------------------------------
  void Stream(CATCGMStream& ioStr,CATGeoFactory * iFactory) const;
  void UnStream(CATCGMStream& ioStr,CATGeoFactory * iFactory);

  virtual void Dump(CATCGMOutput& Output);

protected:
  virtual HRESULT GetHoleType(CATHoleType & oType) const;

  void Init();

private:
  CATCellManifoldExtrusionNavigatorData *_pExtrusionNavigatorData;
  CATHoleManifoldAttribute * _HoleAttr; // this is an 'ease of use' data member. its value is retrieved from _pExtrusionNavigatorData

};

// ---------------------------------------
// CATCreateCellManifoldHoleNavigator
// ---------------------------------------
ExportedByPersistentCell CATCellManifoldHoleNavigator * CATCreateCellManifoldHoleNavigator(CATLiveBody          * iLiveBody,
																									 CATCellManifoldGroup * iNetworkGroup); 
#endif
