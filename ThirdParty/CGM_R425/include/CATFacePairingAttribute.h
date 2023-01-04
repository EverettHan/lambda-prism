// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : ZUT
//
// DESCRIPTION  : Temporary attribute put on faces during the recognition step
//                It is used to memorize data such as opposite faces and face pairs
//
//=============================================================================
// Creation ZUT February 2021
//=============================================================================

#ifndef CATFacePairingAttribute_H
#define CATFacePairingAttribute_H

// ++++ Includes ++++
#include "PersistentCell.h"
#include "CATCGMAttribute.h"
#include "ListPOfCATFace.h"
#include "CATCGMNewArray.h"
#include "CATDataType.h"
#include "CATMathInline.h"

// ++++ Predeclarations ++++
class CATFace;
class CATCGMOutput;

// ++++ Enums ++++
enum CATPairingType
{
  CATPairingNotComputed = -1,
  CATPairingUnknown     = 0,
  CATPairingExactOffset = 1,
  CATPairingVariable    = 2 
};

class ExportedByPersistentCell CATFacePairingAttribute : public CATCGMAttribute
{
public:

  // Overload new & delete
  CATCGMDeclareAttribute(CATFacePairingAttribute, CATCGMAttribute);
  CATCGMNewClassArrayDeclare;

  /**
  * Constructor
  */
  CATFacePairingAttribute();

  /**
  * Constructor
  */
  CATFacePairingAttribute( CATFace * iFace );

  /**
  * Destructor
  */
  virtual ~CATFacePairingAttribute();

  //---------------------------------------------------------------------------
  // METHODS
  //---------------------------------------------------------------------------

  CATLONG32 AppendOppositeFace( CATFace * iOppositeFace, CATPairingType iPairingType = CATPairingNotComputed, double iMaxDistance = 0. );

  CATLONG32 FindPairing( CATFace * iOtherFace, CATPairingType & oPairingType, double * oMaxDistance = NULL ) const;

  CATLONG32 GetNbOppositeFaces( CATLISTP(CATFace) * oListOfOppositeFaces = NULL );

  CATLONG32 GetNbPairingFaces( CATLISTP(CATFace) * oListOfPairingFaces = NULL );

  void Dump( CATCGMOutput & oS );

  //---------------------------------------------------------------------------
  // INLINE METHODS
  //---------------------------------------------------------------------------

  void SetUsedMaxThickness( double iUsedMaxThickness );
  double GetUsedMaxThickness() const;

  void SetIsOppositeListComplete( CATBoolean iIsOppositeListComplete );
  CATBoolean GetIsOppositeListComplete() const;

  CATBoolean GetIsPairingComputationComplete() const;

  //---------------------------------------------------------------------------
  // STATIC METHODS
  //---------------------------------------------------------------------------

  static CATFacePairingAttribute * GetAttribute(CATFace * iFace, CATBoolean iCreateIfNecessary = FALSE);

protected:
  //---------------------------------------------------------------------------
  // INTERNAl STRUCT
  //---------------------------------------------------------------------------
  struct OppositeFace
  {
    CATFace        * _Face;
    CATPairingType   _PairingType;
    double           _MaxDistance;
  };

  //---------------------------------------------------------------------------
  // PROTECTED METHODS
  //---------------------------------------------------------------------------

  CATFacePairingAttribute(const CATFacePairingAttribute &);
  CATFacePairingAttribute & operator=(const CATFacePairingAttribute &);

  //---------------------------------------------------------------------------
  // PROTECTED DATA MEMBERS
  //---------------------------------------------------------------------------

  CATFace         * _Face;
  double            _UsedMaxThickness;

  CATBoolean        _IsOppositeListComplete;
  CATBoolean        _IsPairingComputationComplete;
  CATLONG32         _NbOppositeFaces;
  CATLONG32         _SizeOfTab;
  OppositeFace    * _TabOfOppositeFaces;
};

//-----------------------------------------------------------------------------
// INLINE IMPLEMENTATIONS
//-----------------------------------------------------------------------------

INLINE void CATFacePairingAttribute::SetUsedMaxThickness( double iUsedMaxThickness ) {
  _UsedMaxThickness = iUsedMaxThickness; }

INLINE double CATFacePairingAttribute::GetUsedMaxThickness() const {
  return _UsedMaxThickness; }

INLINE void CATFacePairingAttribute::SetIsOppositeListComplete( CATBoolean iIsOppositeListComplete ) {
  _IsOppositeListComplete = iIsOppositeListComplete; }

INLINE CATBoolean CATFacePairingAttribute::GetIsOppositeListComplete() const {
  return _IsOppositeListComplete; }

INLINE CATBoolean CATFacePairingAttribute::GetIsPairingComputationComplete() const {
  return _IsPairingComputationComplete; }

#endif /* CATFacePairingAttribute_H */
