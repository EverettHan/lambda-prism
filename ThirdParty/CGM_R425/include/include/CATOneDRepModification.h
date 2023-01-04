#ifndef CATOneDRepModification_H
#define CATOneDRepModification_H

//VB7
//===========================================================================
// Data of CATGlobalDRepModification
//CAN BE STREAMED
//===========================================================================

#include "CATPersistentCell.h"
#include "CATManifoldModificationCGM.h"
#include "CATCGMVirtual.h"
#include "CATMathInline.h"
#include "CATManifoldParameter.h"
// #include "CATSysMacros.h"


class CATManifold;
class CATBody;
class CATMathVector;
class CATPersistentCellInfra;
class CATSoftwareConfiguration;
class CATManifoldParamId;
class CATDRepLabel;
class CATDRepLabelRequest;


#ifndef RELEASE_ListPOfLabelRequest
#define RELEASE_ListPOfLabelRequest(iRequestList, iDeleteLabel) { \
  int ielem = 1; \
  for( ; ielem <= iRequestList.Size(); ielem++) \
  { \
    CATDRepLabelRequest * pCurRequest = ( CATDRepLabelRequest * ) iRequestList[ielem]; \
    if (pCurRequest) \
      { \
        CATDRepLabel * pLabel = (CATDRepLabel *) pCurRequest->GetDRepLabel(); \
        if (pLabel && iDeleteLabel) { delete pLabel; pLabel = 0; } \
        pCurRequest->Release(); \
        pCurRequest = NULL; \
      } \
  } \
  iRequestList.RemoveAll(); \
}
#endif

class ExportedByPersistentCell CATOneDRepModification : public CATManifoldModificationCGM
{
public:

  // contructor
  CATOneDRepModification(CATBody *ipBody, CATManifold *ipManifold, CATManifoldParamId * iParamId, CATSoftwareConfiguration *ipConfig);

  // New contructor
  CATOneDRepModification(const CATManifoldModification &iManifoldModif);
  // Copy Contructor
  CATOneDRepModification(const CATOneDRepModification & iOneDRepModification);

  // surchage du new et du delete
  CATCGMNewClassArrayDeclare;

  // @nocgmitf
  // INLINE CATBody * GetBody() const;

  // @nocgmitf
  CATBoolean SameKeyAndSameManifold(CATManifold * iManifold, CATBody * iBody, CATLONG32 iKey) const;

  // @nocgmitf
  virtual void GenerateParameter(CATPersistentCellInfra & iInfra, int iNumOperatorId) const;
  CATManifoldParameter * RetrieveParameter(CATPersistentCellInfra & iInfra, int iNumOperatorId) const;
  
  // @nocgmitf
  INLINE void SetSource(CATManifoldParameter::MPSource iSource);    
  // @nocgmitf
  INLINE const CATManifoldParameter::MPSource & GetSource() const;

  // @nocgmitf
  CATBoolean Compare(const CATOneDRepModification & iOneDRepModification, double iLengthTolerance=0., double iAngleTolerance=0.) const;

  
  // Implementation des Methodes Virtuelles 
  // ----------------------------------------------------------------------
  virtual const CATOneDRepModification * GetAsOneDRepModification() const;

  virtual void Dump(CATCGMOutput& Output) const;
  virtual void Stream(CATCGMStream & ioStream) const; 
  // virtual void UnStream(CATCGMStream & ioStream, CATGeoFactory * iFactory);

protected :  

  // default - to be removed
  CATOneDRepModification();
  // Destructor
  virtual ~CATOneDRepModification();

private :  
	/**
	* Assignment operator.
	**/
	CATOneDRepModification& operator=(CATOneDRepModification const& iOther); 

  // Source
  CATManifoldParameter::MPSource  _Source;
};


//INLINE CATBody * CATOneDRepModification::GetBody() const {
//  return this->GetRightBody(); }

INLINE  void CATOneDRepModification::SetSource(CATManifoldParameter::MPSource iSource) {
  _Source = iSource; }

INLINE const CATManifoldParameter::MPSource & CATOneDRepModification::GetSource() const {
  return _Source ; }

// ---------------------------------------------------------------------------
// UnStream for CGMReplay
// ---------------------------------------------------------------------------
CATOneDRepModification * CATLoadOneDRepModification(CATCGMStream &ioStream, CATICGMContainer *iFactory, CATSoftwareConfiguration *iConfig);


#endif
