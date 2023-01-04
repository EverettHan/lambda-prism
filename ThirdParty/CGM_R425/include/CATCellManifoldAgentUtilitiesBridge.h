#ifndef CATCellManifoldAgentUtilitiesBridge_H
#define CATCellManifoldAgentUtilitiesBridge_H

#include "CATErrorDef.h"

#include "CATCGMNewArray.h"

#include "PersistentCell.h"
#include "CATMathDef.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "ListPOfCATFace.h"
#include "CATListOfCATCells.h"

class CATCellManifoldAgentUtilitiesBridge;
class CATGeoFactory;
class CATBody;
class CATSoftwareConfiguration;
class CATDeclarativeManifold;
class CATCellManifoldPatternNavigator;
class CATlsoDataCache;
class CATCGMJournalList;
class CATFaceHashTable;

typedef CATCellManifoldAgentUtilitiesBridge*  (*CATCellManifoldAgentUtilitiesBridgeCreator) 
  ();

class ExportedByPersistentCell CATCellManifoldAgentUtilitiesBridge
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual ~CATCellManifoldAgentUtilitiesBridge() {};

  virtual CATBody * UnExtrapolateBody(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig, CATBody * iBody, CATLength iExtrapolationLength)=0;

  virtual CATBody * CallSplitShell(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig, CATBody * iToSplitBody, CATBody * iSplittingBody, CATBoolean iPositiveSide)=0;

  virtual CATBody * GetReferenceExtrapolatedBody(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig, CATBody * iOutputBody, CATCellManifoldPatternNavigator * iPatternNavigator)=0;

  virtual CATBody * GetReferenceExtrapolatedFaceBody(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig, CATlsoDataCache * iLSODataCache, int iNumRefFace, CATBody * iOutputBody, CATCellManifoldPatternNavigator * iPatternNavigator)=0;

  virtual CATLONG32 DefineExplicitType(ListPOfCATFace & iInstanceFaceList, CATBody * iRefBody, CATBody * iInputBody, CATSoftwareConfiguration * iConfig)=0;

  virtual CATBody * CallCompatible(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig, CATBody * iBody1, CATBody * iBody2, CATCGMJournalList *& ioJournal)=0;

  virtual CATBoolean CallIntersect(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig, CATBody * iBody1, CATBody * iBody2)=0;

  virtual HRESULT    CallNeutralDraftDetection (CATBody                                 * iBody,
                                                CATSoftwareConfiguration                * iConfig,
                                                const ListPOfCATFace                    & iDraftedFaceList,                                                
                                                const ListPOfCATFace                    & iNeutralCandidateList,
                                                ListPOfCATFace                          & oResultFaceList) = 0;

  virtual double    CallComputePerimeter (CATSoftwareConfiguration * iConfig, const CATFaceHashTable &iFaceHT) = 0;
  virtual double    CallComputeArea (CATSoftwareConfiguration * iConfig, const ListPOfCATFace &iFaces, double & oAbsoluteErrorEst) = 0;
  virtual double    CallDistanceMin(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig, ListPOfCATCell & iCellsList1, ListPOfCATCell & iCellsList2) = 0;

};

ExportedByPersistentCell CATCellManifoldAgentUtilitiesBridge * CATCreateCellManifoldAgentUtilitiesBridge();

#endif 

