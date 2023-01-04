/* -*-c++-*- */
#ifndef CATHLRBodyInput_Get_h
#define CATHLRBodyInput_Get_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
//-------------------------------------------------------------------------------------------------
// HLR replay
//   Needs multiple and heterogeneous bodies management
//-------------------------------------------------------------------------------------------------
 
#include "CATechGet.h"
#include "CATechGetValues.h"

class CAT3DRep;
class CATPolyBody;
class CATBaseUnknown;

/**
* Interface to manage persistency with CATMathStream/CACGMStream infrastructure
*/
class ExportedByCATTechTools CATHLRBodyInput_Get : public CATechGetValues
{ 
  CATDeclareClass;

public:

  CATHLRBodyInput_Get();
  ~CATHLRBodyInput_Get();

  //------------------------------------------------------------------------
  //  CATechGet  adhesion  
  //------------------------------------------------------------------------

  /**
  * GetSchema .
  */
  virtual HRESULT GetSchema(CATechSchema  & oSchema) const;

  /**
  * Get Value.
  */
  virtual HRESULT GetTechValue(const CATechMeta & iRole, 
                           void *ioValue) const  ;

  /**
  * Get3DValue .
  *    iRole  : 
  *    oXMath : 
  *    iReferenceToRelease : Must be released after usage
  */
  virtual HRESULT GetTech3DValue(const CATechMeta & iRole, CATMathTransformation * oXMath, CATechGet ** oReferenceToRelease) const;

  virtual HRESULT CopyTechValue(const CATechGet * iAttribute, const CATBoolean iEmptyBefore);
 
  virtual HRESULT IsCopyTechValueImplemented() const;

  inline void setRep(CAT3DRep* iRep);
  inline void getRep(CAT3DRep*& oRep);

  inline void setPolyBody(CATPolyBody* iRep);
  inline void getPolyBody(CATPolyBody*& oRep);

  inline void setModelV4(CATBaseUnknown* iRep);
  inline void getModelV4(CATBaseUnknown*& oRep);

  /**
  * IsASet : return S_OK if current instance if a Set
  */
  virtual CATechSet * IsASet() const  ; 
  virtual CATechAttribute * IsAttribute() const ; 

 
private :

  CAT3DRep       * _Input3DRep;
  CATPolyBody    * _InputPolyBody;
  CATBaseUnknown * _InputModelV4;

private :

   //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATHLRBodyInput_Get(const CATHLRBodyInput_Get &iCopy);
  CATHLRBodyInput_Get& operator=(const CATHLRBodyInput_Get &iCopy);
};

inline void CATHLRBodyInput_Get::setRep(CAT3DRep* iRep)
{
  _Input3DRep = iRep;
}
inline void CATHLRBodyInput_Get::getRep(CAT3DRep*& oRep)
{
  oRep = _Input3DRep;
}
inline void CATHLRBodyInput_Get::setPolyBody(CATPolyBody* iRep)
{
  _InputPolyBody = iRep;
}
inline void CATHLRBodyInput_Get::getPolyBody(CATPolyBody*& oRep)
{
  oRep = _InputPolyBody;
}

inline void CATHLRBodyInput_Get::setModelV4(CATBaseUnknown* iModel)
{
  _InputModelV4 = iModel;
}
inline void CATHLRBodyInput_Get::getModelV4(CATBaseUnknown*& oModel)
{
  oModel = _InputModelV4;
}
 

#endif



