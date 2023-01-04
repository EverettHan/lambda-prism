#ifndef CATAutoBaseSplitFaceSet_H
#define CATAutoBaseSplitFaceSet_H
//===================================================================
// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CATAutoBaseSplitFaceSet.h
// 		
//===================================================================
//  Oct 2003  Creation: JHG
//===================================================================

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATBoolean.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATCell.h"
#include "CATMathInline.h"

class CATShell;
class CATBody;
class CATCGMJournalList;
class CATSoftwareConfiguration;

class ExportedByPersistentCell CATAutoBaseSplitFaceSet
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATAutoBaseSplitFaceSet(ListPOfCATFace &iFaces, int iLocation, CATShell *iShell,
    int iSecondaryLocation, CATSoftwareConfiguration *iConfig);

  virtual ~CATAutoBaseSplitFaceSet();

  const ListPOfCATFace &GetFaceList(CATListOfInt *oOrientations = 0);
  int GetLocation();
  int GetSecondaryLocation();
  CATShell *ReadShell();
  void GetOrientations(CATListOfInt &oOrientations);

  void GetAllCells(ListPOfCATCell &oCells, int iDimension);
  
  INLINE CATAutoBaseSplitFaceSet &Deref() { return *this; }
  
  CATBoolean IsIntersectedBy(CATBody *iBody, CATCGMJournalList &iJournal);

private:

  ListPOfCATFace _Faces;
  int _Location;
  int _SecondaryLocation;
  CATShell *_Shell;
  CATSoftwareConfiguration *_Config;
};

#endif
