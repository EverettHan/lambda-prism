#ifndef CATGMLiveContextualFeatureFollower_H
#define CATGMLiveContextualFeatureFollower_H

#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATBoolean.h"

#include "ListPOfCATPersistentEdges.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "ListPOfCATPersistentFaces.h"
#include "IUnknown.h" // For HRESULT
#include "ListPOfCATPersistentCells.h"

class CATBoneFillet;
class CATPersistentBody;
class CATBody;
class CATPersistentCellInfra;
class CATGMLiveBoneFollower;
class CATGMLivePatternFollower;
class CATGMLiveOffsetFollower;
class CATGMLiveGroupFollower;
class CATGMLiveDraftFollower;
class CATExtTopOperator;
class CATCGMStream;
class CATGeoFactory;
class CATGMLiveHierarchicalGroupFollower;
class CATGMAdvancedStampFollower;
class CATGMLiveKeepTopFollower;

class ExportedByPersistentCell CATGMLiveContextualFeatureFollower 
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATGMLiveContextualFeatureFollower(CATPersistentCellInfra &iInfra, CATPersistentBody *iInitialBodyWithContextualFeature);

  // Copy Constructor
  CATGMLiveContextualFeatureFollower(CATGMLiveContextualFeatureFollower & iFollower);

  // Destructor
  virtual ~CATGMLiveContextualFeatureFollower();

  // Created Declarative Manifolds
  
  //To use for full DeclarativeManifolds or CreatedBoneSpecs
  void AppendCreatedDeclarativeManifold(CATDeclarativeManifold* iDeclarativeManifold,CATPersistentBody *iPersistentRedoResultBody);

  //To clean Empty DeclarativeManifolds
  void CleanEmptyDeclarativeManifold(ListPOfCATDeclarativeManifold iCreatedDeclarativeManifoldToClean);

  //Compute _CreatedDMs from _CreatedDMsPCells
  void GetCreatedDeclarativeManifoldsInContainer(const CATPersistentBody *iContainer, ListPOfCATDeclarativeManifold& oCreatedDMs); 

  // Get/Set Method
  void SetNumOperatorIdForFollowers(int iNumOperatorIDForFollower);
  int GetNumOperatorIdForFollowers() const;

  //Cleaning for MultiRun
  void CleanNoMultiRunDatas();

  // Merge
  virtual HRESULT Merge(CATGMLiveContextualFeatureFollower& iFollower);
 
  virtual CATGMLiveBoneFollower* GetAsBoneFollower(); 
  virtual CATGMLivePatternFollower* GetAsPatternFollower();
  virtual CATGMLiveOffsetFollower* GetAsOffsetFollower(); 
  virtual CATGMLiveGroupFollower *GetAsGroupFollower();
  virtual CATGMLiveHierarchicalGroupFollower *GetAsHierarchicalGroupFollower();
  virtual CATGMLiveDraftFollower *GetAsDraftFollower();
  virtual CATGMAdvancedStampFollower *GetAsAdvancedStampFollower();
  virtual CATGMLiveKeepTopFollower *GetAsKeepTopFollower();
  CATPersistentCellInfra *GetPersistentInfra() const;
  
  CATPersistentBody & GetInitialPersistentBodyWithContextualFeature() const;
  CATBody * GetInitialBodyWithContextualFeature() const;
  void SetInitialBodyWithoutContextualFeature(CATPersistentBody * iPersistentBody);
  CATPersistentBody & GetInitialPersistentBodyWithoutContextualFeature() const;
  CATBody * GetInitialBodyWithoutContextualFeature() const;
  virtual void Stream(CATCGMStream& ioStr,CATGeoFactory * iFactory) const;
  virtual void UnStream(CATCGMStream& ioStr,CATGeoFactory * iFactory);
  virtual void GetDeclarativeManifoldsInInputBody(ListPOfCATDeclarativeManifold &iInputDeclarativeManifolds) const =0;

  void SetSelectedPersistentFaces(const ListPOfCATPersistentFaces &iSelectedPersistentFaces);
  void GetSelectedPersistentFaces(ListPOfCATPersistentFaces  & oInternalPersistentFaces) const;

  INLINE CATBoolean GetUserEdition() const;
  INLINE int        GetRedoStatus() const;
  INLINE void       SetUserEdition(const CATBoolean iUserEdition);
  INLINE void       SetRedoStatus(int iRedoStatus);

protected:

  void SetInitialBodyWithContextualFeature(CATPersistentBody * iPersistentBody);

protected:
  CATPersistentCellInfra         * _Infra;
  int                              _NumOperatorIDForFollower;
  CATPersistentBody              * _InitialBodyWithContextualFeature;
  CATPersistentBody              * _InitialBodyWithoutContextualFeature;
  ListPOfCATPersistentFaces        _SelectedPersistentFaces;

private:
  ListPOfCATDeclarativeManifold    _CreatedDMSpecs;
  CATPersistentBody               *_CreatedDMSpecsContainer;
  ListPOfCATPersistentCells        _CreatedDMsPCells;

  //VB7 - IR 341116
  CATBoolean                _UserEdition;
  int                       _RedoStatus; // reserved to boneFollower with _UserEdition = TRUE
};


//int operator != (const CATGMLiveContextualFeatureFollower &iFollower1, const CATGMLiveContextualFeatureFollower &iFollower2);
//int operator == (const CATGMLiveContextualFeatureFollower &iFollower1, const CATGMLiveContextualFeatureFollower &iFollower2);

INLINE void CATGMLiveContextualFeatureFollower::SetUserEdition(const CATBoolean iUserEdition) {
  _UserEdition = iUserEdition; }

INLINE CATBoolean CATGMLiveContextualFeatureFollower::GetUserEdition() const {
  return _UserEdition; }

INLINE int CATGMLiveContextualFeatureFollower::GetRedoStatus() const {
  return _RedoStatus; }

INLINE void CATGMLiveContextualFeatureFollower::SetRedoStatus(int iRedoStatus) {
  _RedoStatus = iRedoStatus; }

#endif

