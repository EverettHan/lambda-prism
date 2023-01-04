#ifndef CATPersistentCellFactory_H
#define CATPersistentCellFactory_H
//===================================================================
// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CATAutoFilletCATAutoFilletBuildStatus.h
// 		
//===================================================================
//  Feb 2004  Creation: JHG
//===================================================================

#include "PersistentCell.h"
#include "CATTopRibTraceObject.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"

#include "ListPOfCATPersistentCells.h"
#include "ListPOfCATPersistentBodies.h"
#include "ListPOfCATPersistentShells.h"
#include "CATPersistentCellAttributeManager.h"
#include "CATListOfCATGeoFactories.h"
#include "CATMathInline.h"

class CATGeoFactory;
class CATSoftwareConfiguration;

class CATPersistentVertex;
class CATPersistentEdge;
class CATPersistentFace;
class CATPersistentShell;
class CATPersistentSkin;
class CATAutoBaseThreadContext;

class CATBody;

class ExportedByPersistentCell CATPersistentCellFactory : public CATTopRibTraceObject
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  DEFINE_ADVOP_CLASS(CATPersistentCellFactory)

  CATPersistentCellFactory(CATSoftwareConfiguration *iConfig);
  virtual ~CATPersistentCellFactory();

// Cree un CATPersistentVertex vide
  CATPersistentVertex *CreatePersistentVertex();

// Cree un CATPersistentEdge vide
  CATPersistentEdge *CreatePersistentEdge();

// Cree un CATPersistentFace vide
  CATPersistentFace *CreatePersistentFace();

  CATPersistentCell *CreateUnionPersistentCell(ListPOfCATPersistentCells &iPersistentCells);

// Cree un CATPersistentShell vide
  CATPersistentShell *CreatePersistentShell();

// Cree un CATPersistentBody et lui attache son CATBody
  CATPersistentBody *CreatePersistentBody(const CATAutoBaseThreadContext &iThreadContext, CATBody *iBody, CATBoolean iModifiableBody);

  // Cree un CATPersistentBody et lui attache son CATBody sans buffer 
  CATPersistentBody *CreateFastPersistentBody(const CATAutoBaseThreadContext &iThreadContext, CATBody *iBody, CATBoolean iModifiableBody, int iNbCells=-1);

  CATPersistentBody *CreatePersistentBodyHelper(const CATAutoBaseThreadContext &iThreadContext, CATBody *iBody, CATBoolean iModifiableBody,
    CATBoolean iCreateFaces, CATBoolean iCreateEdges, CATBoolean iCreateVertices);

// Cree un CATPersistentSkin et lui attache son CATBody
  CATPersistentSkin *CreatePersistentSkin(const CATAutoBaseThreadContext &iThreadContext, CATBody *iBody, CATBoolean iModifiableBody);

// Cree un CATPersistentSkin a partir d'un Shell - duplique le shell et lui donne la bonne location
  CATPersistentSkin *CreatePersistentSkinFromCATShell(const CATAutoBaseThreadContext &iThreadContext, CATShell *iShell, CATBoolean iModifiableBody);

  void AttachPersistentCellToCATCell(CATPersistentCell &iPersistentCell, CATCell &iCell);

// Detruit un iBody, appelle le remove sur la CATGeoFactory sur
// le Body sur lequel il repose  si iRemoveUnderneathCATBody est mis a TRUE
  void RemoveBody(CATPersistentBody *iBody, CATBoolean iRemoveUnderneathCATBody = FALSE);

  void DeletePersistentCell(CATPersistentCell *iCellToDelete);

// Renvoie tous les CATPersistentBodies de la Factory
  void GetBodies(ListPOfCATPersistentBodies &oPersistentBodies);

  void CommitHighlight();

//  INLINE CATGeoFactory &GetGeoFactory() { return _Factory; }
  INLINE CATSoftwareConfiguration *GetSoftwareConfiguration() { return _Config; }

  INLINE CATPersistentCellAttributeManager &GetPersistentCellAttrManager() { return _PersistentCellAttrManager; }

  INLINE CATBoolean HasSomePersistentVertex();
  INLINE CATBoolean HasSomePersistentEdge();

  void Dump();
  void SynthesisDump(const CATAutoBaseThreadContext &iThreadContext);

private:

//  CATGeoFactory &_Factory;
  CATSoftwareConfiguration *_Config;

  CATLISTP(CATGeoFactory) _Factories;

  ListPOfCATPersistentCells  _PersistentCells;
  ListPOfCATPersistentBodies _PersistentBodies;
  ListPOfCATPersistentShells _PersistentShells;

  CATBoolean                 _SomePersistentVertex;
  CATBoolean                 _SomePersistentEdge;

  CATPersistentCellAttributeManager _PersistentCellAttrManager;
};

CATBody ExportedByPersistentCell *FreezeCATBody(CATBody *iBody);


INLINE CATBoolean CATPersistentCellFactory::HasSomePersistentVertex() {
 return _SomePersistentVertex; }

INLINE CATBoolean CATPersistentCellFactory::HasSomePersistentEdge() {
 return _SomePersistentEdge; }

#endif
