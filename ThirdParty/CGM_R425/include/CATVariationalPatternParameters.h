/* -*-C++-*- */

#ifndef CATVariationalPatternParameters_H
#define CATVariationalPatternParameters_H

#include "PersistentCell.h"
#include "ListPOfCATManifoldParameter.h"
#include "CATBoolean.h"
#include "CATListOfShort.h"
#include "CATLISTP_CATMathTransformation.h"
#include "CATPatternActivationStatus.h"
#include "CATHashTableWithIntListAssoc.h"
#include "CATErrorDef.h"


class CATDrawerCollector;
class CATCellManifoldGroup;
class CATManifoldParameter;
class CATBody;
class CATMathTransformation;
class CATLiveBody;
class CATMathVector;
class CATCGMHashTableWithAssoc;
class CATPersistentCellInfra;
class CATPersistentFace;
class CATCGMStream;
class CATGeoFactory;
class CATGlobalDRepModification;
class CATOneDRepModification;

//--------------------------------------------------------------------------
// @nocgmitf (do not create phase 2 interface)
class ExportedByPersistentCell CATVariationalPatternParameters
{

public : 
  CATVariationalPatternParameters(CATPersistentCellInfra * iPersistentCellInfra);
  ~CATVariationalPatternParameters();

  // Le set est necessaire !
  virtual void SetInputBody(CATBody * iInputBody);

  // Set des options du pattern.
  // Les parameters correspondants sont generes.
  //---------------------------------------------------------
  virtual void SetSecondaryTransfo(CATCellManifoldGroup  * iPattern, int iInstance, CATMathTransformation * iSecondaryTransfo);
  virtual void SetSecondaryTransfo(CATCellManifoldGroup  * iPattern, CATListOfShort & iInstanceNumbers, CATLISTP(CATMathTransformation) & iSecondaryTransformations);
  
  virtual void SetUnitaryTransfo(CATCellManifoldGroup  * iPattern, const CATMathTransformation * iUnitaryTransfo);
  virtual int  SetDRepModification(const CATGlobalDRepModification * ipGlobalDRepModif);
  virtual int  SetDRepModification(const CATOneDRepModification    * ipOneDRepModif);
  
  virtual void SetNewReference(CATCellManifoldGroup  * iPattern, CATLiveBody * iNewRefBody);

  /*virtual void SetNumberOfInstances(CATCellManifoldGroup  * iPattern, int iNbInstances);
  virtual void SetOrigineTranslation(CATCellManifoldGroup  * iPattern, CATMathVector * iVector);
  virtual void SetIsComplete(CATCellManifoldGroup  * iPattern, CATBoolean iIsComplete);
  virtual void SetActivationStatus(CATCellManifoldGroup  * iPattern, int iInstance, CATPatternActivationStatus iActivationStatus);
  virtual void SetActivationStatus(CATCellManifoldGroup  * iPattern, CATListOfShort & iInstanceNumbers, CATListOfShort & iActivationStatus);*/

  virtual HRESULT GetUnitaryTransfo(CATCellManifoldGroup  * iPattern, CATMathTransformation *& oUnitaryTransfo);

  // Acces directs aux parameters.
  //---------------------------------------------------------
  virtual void SetPatternParameter(CATCellManifoldGroup  * iPattern, CATManifoldParameter * iParameter);
  virtual void SetPatternParameters(CATCellManifoldGroup  * iPattern, ListPOfCATManifoldParameter & iParameters);
  void GetPatternParameters(CATCellManifoldGroup  * iPattern, ListPOfCATManifoldParameter & oParameters);

  void CleanData();

  // Pour utilisation elargie au sein du TranformFace
  //---------------------------------------------------------
  CATBoolean GetGeneratedByTransformFace();
  virtual void SetGeneratedByTransformFace(CATBoolean iValue);
  void Init();

  virtual void SetMovePatternTransfo(CATCellManifoldGroup  * iPattern, CATMathTransformation * iMoveTransfo);
  CATMathTransformation GetPatternMoveTransfo(CATCellManifoldGroup  * iPattern);

  void SetBeingCreatedPatternOutOfSupport(CATPersistentFace * iPersistentFace, int iInstanceNumber);
  void GetBeingCreatedPatternOutOfSupport(CATPersistentFace * iPersistentFace, CATListOfShort & oNewAssoc);

  void Stream(CATCGMStream& ioStr);
  void UnStream(CATCGMStream& ioStr, CATGeoFactory * iFactory, CATLiveBody *iInputLiveBody);

  INLINE CATPersistentCellInfra * GetPersistentCellInfra() const; 

protected : 

  CATDrawerCollector  * _PattenrAndParameters; // pour le proto, faire une structure plus dediee apres.
  CATBoolean            _GeneratedByTransformFace; //  a supprimer a terme.
  CATBody             * _InputBody;
  int                   _DebugTag; // Juste pour debug.
  void DeleteTable();

  CATCGMHashTableWithAssoc * _MovePatternTransfo;

  CATPersistentCellInfra * _PersistentCellInfra;

  CATHashTableWithIntListAssoc _PersistentCellWithOutOfSupportInstanceNumbers;

};

// --------------------------------------------------------------------------------------
// GetPersistentCellInfra
// --------------------------------------------------------------------------------------
INLINE CATPersistentCellInfra * CATVariationalPatternParameters::GetPersistentCellInfra() const {
  return _PersistentCellInfra; }


#endif

