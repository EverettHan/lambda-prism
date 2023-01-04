#ifndef CATGMSpecInfra_H
#define CATGMSpecInfra_H

//--------------------------------------//
//--------VB7 - 26 - 04 - 2016----------//
//--------------------------------------//
//-- To store Manifold parameters and --//
//-- carry them through our operators --//
//-- infrastructure. -------------------// 
//--------------------------------------//

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATManifoldBaseParameter.h"
#include "ListPOfCATExtTopOperators.h"
#include "CATMathDef.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "ListPOfCATManifoldParameter.h"
#include "CATListOfInt.h"
#include "CATManifoldParameter.h"

class CATGMLiveShapeOperator;
class CATDeclarativeManifold;
class CATCellManifoldGroup;
class CATManifold;

//@nocgmitf
class ExportedByPersistentCell CATGMSpecInfra
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  //@nocgmitf
  CATGMSpecInfra();

  //@nocgmitf
  ~CATGMSpecInfra();

  //Only give changed parameters
  //@nocgmitf
  void GetParameterList(CATDeclarativeManifold * iDM, int iNumOperatorId, ListPOfCATManifoldBaseParameter & oParameterList) const;

  //Only give changed parameters
  //@nocgmitf
  void GetParameterList(CATManifold * ipManifold, int iNumOperatorId, CATLONG32 iKey, ListPOfCATManifoldBaseParameter & oParameterList) const;

  //Only give changed parameters
  //@nocgmitf
  void GetParameterList(CATCellManifoldGroup * iCMG, int iNumOperatorId, ListPOfCATManifoldBaseParameter & oParameterList) const;
  
  //Only give changed parameters
  //@nocgmitf
  void GetParameterList(int iNumOperatorId, ListPOfCATManifoldBaseParameter & oParameterList) const;

  //Only give changed parameters
  //@nocgmitf
  void GetManifoldParamList(int iNumOperatorId, const CATManifoldParameter::MPSource iSource, ListPOfCATManifoldParameter & oParameterList) const;

  //@nocgmitf
  void SetParameterList(const ListPOfCATManifoldBaseParameter & iParameterList, int iNumOperatorId);

  //@nocgmitf
  void SetParameterList(const ListPOfCATManifoldParameter & iParameterList, int iNumOperatorId);

  //@nocgmitf
  void UpdateParameterWithSecondaryDM(CATDeclarativeManifold * iDM, CATDeclarativeManifold * iSecondaryDM);
  
  //@nocgmitf
  void CleanParameterSecondaryDM(CATDeclarativeManifold * iDM);

  //@nocgmitf
  CATDeclarativeManifold * GetParameterSecondaryDM(CATDeclarativeManifold * iDM);

  //@nocgmitf
  void SetSecondaryNumOperatorId(CATDeclarativeManifold * iDM, CATLONG32 iKey, int iSecondaryNumOperatorId);

  //@nocgmitf
  int SetSecondaryNumOperatorId(const ListPOfCATManifoldParameter & iParameterList, int iSecondaryNumOperatorId);

  //Only give changed parameters
  //@nocgmitf
  static void GetParameterList(const ListPOfCATManifoldParameter & iParameterList, CATDeclarativeManifold * iDM, CATLONG32 iKey, ListPOfCATManifoldParameter & oParameterList);

  // Filter by Key and Declarative
  //@nocgmitf
  static void FilterParamaterList(const ListPOfCATManifoldParameter & iParameterList, const CATManifold * ipManifold, CATLONG32 iKey, ListPOfCATManifoldParameter & oParameterList);

  // StreamParameters
  //@nocgmitf
  void StreamParameters(CATCGMStream & oStr, int iNumOpeId);
  void UnStreamParameters(CATCGMStream & iStr, int iNumOpeId, CATGeoFactory* iFactory, CATLiveBody* iLiveBody);

protected : 
  INLINE const ListPOfCATManifoldBaseParameter & GetParameterList() const;

private :
  void CheckParallelism() const;
  void InitSecondaryDMList();
  CATBoolean RightNumOperatorId(int iNumParam, int iNumOperatorId) const;

private :
  //Parameter list, parallel to operator list.
  ListPOfCATManifoldBaseParameter _ManifoldBaseParameterList;
  //Operator id list, parallel to Parameter list.
  CATListOfInt                    _OperatorIdList;
  //Secondary Operator id list, parallel to Parameter list.
  CATListOfInt                    _OperatorSecondIdList;
  
  // Il sera peut être necessaire de permettre N secondary ID
  // Pour chaque Parameters, la liste des operateurs autorisés.
  // ListPOfCATListOfInt[NumParap][ListOfOpeID]
  
  
  ListPOfCATDeclarativeManifold * _SecondaryDMList;
};


INLINE const ListPOfCATManifoldBaseParameter & CATGMSpecInfra::GetParameterList() const {
  return _ManifoldBaseParameterList; }


#endif
