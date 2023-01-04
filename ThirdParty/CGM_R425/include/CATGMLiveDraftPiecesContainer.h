#ifndef CATGMLiveDraftPiecesContainer_H
#define CATGMLiveDraftPiecesContainer_H

#include "CATIACGMLevel.h"

#ifdef CATIACGMV5R20
#include "CATGMModelInterfaces.h"
#else
#include "PersistentCell.h"
#endif

#include "ListPOfCATGMLiveDraftPiece.h"
#include "CATDRepSeedsContainer.h"

#ifdef CATIACGMV5R20
class ExportedByCATGMModelInterfaces CATGMLiveDraftPiecesContainer: public CATDRepSeedsContainer
#else
class ExportedByPersistentCell CATGMLiveDraftPiecesContainer: public CATDRepSeedsContainer
#endif 
{
public: 
  CATGMLiveDraftPiecesContainer(); 
  virtual ~CATGMLiveDraftPiecesContainer();

  void AddDraftPiece(CATGMLiveDraftPiece *iDraftPiece);
  void GetDraftPieces(ListPOfCATGMLiveDraftPiece &oDraftPieces);

private:
  ListPOfCATGMLiveDraftPiece _DraftPieces;
};


#endif

