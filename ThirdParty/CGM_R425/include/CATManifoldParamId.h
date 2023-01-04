#ifndef CATManifoldParamId_H
#define CATManifoldParamId_H

// ======================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015
// ======================================================================================
//
// Created on october 2015
//
// Responsable LAP/QF2
//
// --------------------------------------------------------------------------------------
/* DESCRIPTION  :  Abstract child class representing shared object beethween CDM and CGM departement. 
*                  It carries data for Intergration Knowledge project in NaturalShape Application.
*
*
* Warning : Users have to respect the LifeCycle of this object.
* Delete operand is forbidden and cannot be called. Use AddRef and Release().
*
**/

#include "CATGMModelInterfaces.h"
#include "CATManifoldBaseParameter.h"
#ifdef CATIAR213
#include "CATSysBoolean.h"
#endif
#include "CATMathLimits.h"

class CATUnicodeString;
class CATManifold;
class CATDoubleManifoldParam;
class CATIntManifoldParam;
class CATCGMStream;
class CATCDMType;
class CATMathStream;
class CATManifoldParameter;
class CATVectorManifoldParam;
class CATTransfoManifoldParam;
class CATTolerance;
class CATNullManifoldParam;


#define ParamID_NoValue CATMathInfinite;


class ExportedByCATGMModelInterfaces CATManifoldParamId : public CATManifoldBaseParameter
{
  CATDeclareClass;

public:
  // ------------------------------------------------------------------------------------------------------------------
  // The string is a key to the catalog : CATTopologicalOperators
  // TopologicalOperators\TopologicalOperatorsRscCNext.m\src\CNext\resources\msgcatalog\CATTopologicalOperators.CATNls
  //
  // TopOpKwePublicationName_DraftAngle="Draft Angle";
  // TopOpKwePublicationName_FilletRadius="Fillet Radius";
  // ------------------------------------------------------------------------------------------------------------------
  virtual CATUnicodeString GetAlias (CATManifold *iManifold) const = 0;
  
#ifdef CATIAR211
  virtual HRESULT GetMagnitude(CATCDMType *&oMagnitude) const = 0;
#endif

  virtual CATBoolean IsEquivalent(const CATManifoldParamId &iParamID) const = 0;

  virtual CATBoolean GetActive() const;

  // Create a ParamId alway with value
  virtual HRESULT Clone(CATManifoldParamId *& oClonedParamId) const = 0;
  // Creates a ParamId 'without value'
  virtual HRESULT CloneWithoutValue(CATManifoldParamId *& oCloneParamId) const = 0;

  // Set this Value to Manifold Parameter
  virtual HRESULT SetThisValueTo(CATManifoldParameter *ioManifoldParameter) const = 0;

  virtual CATBoolean GetHasChanged() const = 0;

  // ---------------------------------------------------------------
  // GetAs safe methods
  // ---------------------------------------------------------------
  virtual CATManifoldParamId      * GetAsManifoldParamId()      const;
  virtual CATDoubleManifoldParam  * GetAsDoubleManifoldParam()  const;
  virtual CATIntManifoldParam     * GetAsIntManifoldParam()     const;
  virtual CATVectorManifoldParam  * GetAsVectorManifoldParam()  const;
  virtual CATTransfoManifoldParam * GetAsTransfoManifoldParam() const;
  virtual CATNullManifoldParam    * GetAsNullManifoldParam()    const;
 
  // ODT - CGMReplay
  virtual CATBoolean IsEqual(const CATManifoldParamId &iParamID, const CATTolerance &iTolerance) const = 0;

  /**
  *  Stream
  * (see global methode below for UnStream)
  */
  virtual void Stream(CATMathStream &ioStr) const = 0;
  
  virtual HRESULT StreamWithoutValue(CATMathStream &ioStr) const = 0;

  // static CATManifoldParamId * UnStreamWithoutValue(CATCGMStream &ioStr);

 /* ------------------------------------------------------------------
  *    Life Cycle Object Management
  *  -----------------------------------------------------------------
  *   - ULONG  AddRef()  
  *   - ULONG  Release()   
  **/

protected :

  /**
  * Default constructor.
  * <br><b>Role:</b> Constructs object in an invalid state - needed so that instances of this class can be streamed.
  **/
  CATManifoldParamId();

  /**
  * Copy constructor. 
  **/
  CATManifoldParamId(CATManifoldParamId const& iOther);
  
  /**
  * Assignment operator.
  **/
  CATManifoldParamId& operator=(CATManifoldParamId const& iOther); 

  /**
  * Destructor.
  * Strictly Forbiden.
  **/
  virtual ~CATManifoldParamId();

};

// ----------------------------------------------------------------------------------------------
//   << Official Unsteaming method >>
// ----------------------------------------------------------------------------------------------
ExportedByCATGMModelInterfaces CATManifoldParamId * CATLoadManifoldParamId(CATMathStream &ioStr);

ExportedByCATGMModelInterfaces HRESULT CATLoadManifoldParamIdWithoutValue(CATMathStream &ioStr, CATManifoldParamId *& oLoadManifoldParamId);

#endif 

