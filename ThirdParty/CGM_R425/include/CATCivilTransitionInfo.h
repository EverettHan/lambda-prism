//===================================================================
// COPYRIGHT Dassault Systemes 2017/03/23
//===================================================================
// CATComputeCivilTransitions.h
// Header definition of class CATCivilTransitionInfo
//===================================================================
//
// Usage notes: Civil transition curve information
//
//===================================================================
// Historic:
// 23/03/17 F1Z : Creation
// 30/07/18 KJD : In the frame of the extension of the CivilTransition 
//                operators to new input, the class becomes protected 
//                to store the specificated data.
//                => New architecture of the class : 
//                new APIs for the exchanges with users (new ctor, new get...) 
//                + split between a protected part (CATCivilTransitionInfo)
//                 and a local part (CATCivilTransitionData).
//                Previously, CATCivilTransitionInfo was a pure virtual local class
//                without any attributes whose specializations were  
//                CATCivilLineCircleLineTransitionInfo and CATCivilLineLineTransitionInfo.
//                Now CATCivilTransitionInfo is a protected class with as attributes
//                the type of the transition and a new structure enabling to store
//                different types of data CATCivilTransitionData 
//                (local class very similar to the previous CATCivilTransitionInfo).
//                The classes CATCivilLineCircleLineTransitionInfo and CATCivilLineLineTransitionInfo
//                were also migrated in the new local class  CATCivilTransitionData.
// 23/12/21 Q48 : File tidy and add Clone to ease creation
//===================================================================

#ifndef CATCivilTransitionInfo_H
#define CATCivilTransitionInfo_H

// Base class
#include "CATPGMCivilTransitionInfo.h"

// ExportedBy
#include "GeoAdvCurves.h"

// C++11
#include "CATGeoOpVirtual.h"

// System
#include "CATBoolean.h"

// Mathematics
#include "CATMathConstant.h"

// Advanced Mathematics
#include "CATMathIdentifierMacros.h"

// GMModelInterfaces
#include "CATCivilCurveDef.h"

class CATCGMOutput;
class CATCGMStream;
class CATGeoODTScaleManager;
class CATCivilTransitionData;

// ============================================================================================================================= //
//                                                    CATCivilTransitionInfo                                                     //
// ============================================================================================================================= //
class ExportedByGeoAdvCurves CATCivilTransitionInfo  : public CATPGMCivilTransitionInfo
{
public:
   //-----------------------------------------------------------------------------
   // Object Management
   //-----------------------------------------------------------------------------
   
  CATCivilTransitionInfo();
  
  CATCivilTransitionInfo(const CATCivilTransitionType iTransitionType, 
                         const double                 iL1, 
                         const double                 iL2,
                         const double                 iR);

  CATCivilTransitionInfo(const CATCivilTransitionType     iTransitionType, 
                         const CATCivilTransitionInfoType iTransitionTypeInfo,
                         const double                     iVal);

  CATCivilTransitionInfo(const CATCivilTransitionInfo & iCivilTransitionInfo);
  
  virtual ~CATCivilTransitionInfo();
  
  //-----------------------------------------------------------------------------
  // Clone
  //-----------------------------------------------------------------------------

  static CATCivilTransitionInfo* Clone(const CATPGMCivilTransitionInfo & iCivilTransitionInfo);

  //-----------------------------------------------------------------------------
  // Get
  //-----------------------------------------------------------------------------
  
  virtual CATCivilTransitionType GetTransitionType() const CATGEOOverride CATGEOFinal;

  // in case of CATCivilTransition_LineCircleLine,
  // input is iTransitionTypeInfo (CATCivilTransitionInfo_R / _L1 / _L2)
  // output is the associated value
  virtual HRESULT GetLineCircleLineInfo(const CATCivilTransitionInfoType   iTransitionTypeInfo ,
                                              double                     & oVal) const CATGEOOverride CATGEOFinal;

  // in case of CATCivilTransition_LineLine
  // output are oTransitionTypeInfo (CATCivilTransitionInfo_L / _VerticalL / _K) and the associated value
  virtual HRESULT GetLineLineInfo(CATCivilTransitionInfoType & oTransitionTypeInfo ,
                                  double                     & oVal) const CATGEOOverride CATGEOFinal;

  //-----------------------------------------------------------------------
  //- Stream
  //-----------------------------------------------------------------------   
  //@nocgmitf
  virtual void Stream(CATCGMStream & ioStream) const CATGEOFinal;

  //@nocgmitf
  virtual void UnStream(CATCGMStream          & iStream,
                        CATGeoODTScaleManager * iScaleManager) CATGEOFinal;

  //@nocgmitf
  virtual void Dump(CATCGMOutput & ioStream) const CATGEOFinal;
   
private:
  
  //-----------------------------------------------------------------------------
  // Attributs (private)
  //-----------------------------------------------------------------------------
  CATCivilTransitionType    _Type;
  CATCivilTransitionData *  _pData;
};

// ============================================================================================================================= //
/**
* Create 
*/
ExportedByGeoAdvCurves CATCivilTransitionInfo * CATCreateCATCivilTransitionInfo(const CATCivilTransitionType iTransitionType, 
                                                                            const double iL1,
                                                                            const double iL2,
                                                                            const double iR );

ExportedByGeoAdvCurves CATCivilTransitionInfo * CATCreateCATCivilTransitionInfo(const CATCivilTransitionType     iTransitionType, 
                                                                            const CATCivilTransitionInfoType iTransitionTypeInfo,
                                                                            const double iVal);


/**
* @nodoc
* @nocgmitf
*/
ExportedByGeoAdvCurves void Remove (CATCivilTransitionInfo * & ioCivilTransitionInfo);

#endif
