#ifndef CATGMLiveFilletPiecesContainer_H
#define CATGMLiveFilletPiecesContainer_H

#include "CATIACGMLevel.h"

#ifdef CATIACGMV5R20
#include "CATGMModelInterfaces.h"
#else
#include "PersistentCell.h"
#endif

#include "ListPOfCATGMLiveFilletPiece.h"
#include "CATDRepSeedsContainer.h"

#ifdef CATIACGMV5R20
class ExportedByCATGMModelInterfaces CATGMLiveFilletPiecesContainer: public CATDRepSeedsContainer
#else
class ExportedByPersistentCell CATGMLiveFilletPiecesContainer: public CATDRepSeedsContainer
#endif 
{
public: 
  CATGMLiveFilletPiecesContainer(); 
  virtual ~CATGMLiveFilletPiecesContainer();

  void AddFilletPiece(CATGMLiveFilletPiece *iFilletPiece);
  void GetFilletPieces(ListPOfCATGMLiveFilletPiece &oFilletPieces);

private:
  ListPOfCATGMLiveFilletPiece _FilletPieces;
};


#endif

