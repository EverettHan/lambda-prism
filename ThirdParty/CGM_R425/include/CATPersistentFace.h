#ifndef CATPersistentFace_H
#define CATPersistentFace_H
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
#include "CATPersistentCell.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"

#include "ListPOfCATPersistentFaces.h"
#include "ListPOfCATFace.h"
#include "ListPOfListPOfCATPersistentFaces.h"
#include "ListPOfListPOfCATFace.h"

class CATFace;
class CATPersistentImplFace;
class CATFaceHashTable;

class ExportedByPersistentCell CATPersistentFace : public CATPersistentCell
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  DEFINE_ADVOP_CLASS_NAME("CATPersistentFace")

  CATPersistentFace(CATPersistentCellFactory &iFactory, CATPersistentImplCell *iImplCell);
  virtual ~CATPersistentFace();

// cas particulier de GetRepresentationInContainer quand this ne correspond qu'a une seule CATFace
// dans iContainer.
// renvoie la CATFace correspondante et NULL si plusieurs CATCell representent this
  CATFace *GetFaceRepresentation(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iContainer);

// Renvoie les representations CATFace de this dans iContainer
  void GetFaceRepresentationInContainer(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iContainer, ListPOfCATFace &oFaces,CATListOfInt *oTypes = NULL);

  static void GetListPOfPersistentFacesRepresentation(const CATAutoBaseThreadContext &iThreadContext, const ListPOfCATPersistentFaces &iListOfPersistentFaces, CATPersistentBody &iContainer,
    ListPOfCATFace &oListOfCATFaces);
  static void GetListPOfPersistentFacesRepresentation(const CATAutoBaseThreadContext &iThreadContext, const ListPOfCATPersistentFaces &iListOfPersistentFaces, CATPersistentBody &iContainer,
    CATFaceHashTable &oFaceHT);
  static void GetListPOfListPOfPersistentFacesRepresentation(const CATAutoBaseThreadContext &iThreadContext, ListPOfListPOfCATPersistentFaces &iListOfListOfPersistentFaces, CATPersistentBody &iContainer,
    ListPOfListPOfCATFace &oListOfListOfCATFaces);

  virtual CATPersistentFace   *GetAsPersistentFace();

  static void GetPersistentFaces(CATPersistentCellFactory *iPersistentCellFactory, const ListPOfCATFace &iFaces, ListPOfCATPersistentFaces &oPersistentFaces);

  static void GetPersistentFaceListFromCATFace(CATPersistentCellFactory *iPersistentCellFactory, 
    CATFace *iFace, ListPOfCATPersistentFaces &oPersistentFaces);
  static CATPersistentFace *GetUniquePersistentFaceFromCATFace(CATPersistentCellFactory *iPersistentCellFactory,
    CATCell *iFace, CATBoolean iAnyPersistentCellIsOk);
#ifdef ALLOW_GetPersistentCellFromCATCell
  static CATPersistentFace *GetPersistentFaceFromCATFace(CATPersistentCellFactory *iPersistentCellFactory, CATFace *iFace);
#endif

  virtual int GetDimension();

private:
};

#endif
