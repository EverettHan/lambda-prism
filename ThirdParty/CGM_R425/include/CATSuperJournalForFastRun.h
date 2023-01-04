#ifndef CATSuperJournalForFastRun_h
#define CATSuperJournalForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
//==========================================================================

#include "ExportedByCATTopologicalObjects.h"

#include "CATCGMHashTable.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATBoolean.h"
#include "CATTopDefine.h"
#include "CATCGMJournalList.h"
#include "CATPAD.h"
class CATTopology;
class CATCGMJournalList;



class ExportedByCATTopologicalObjects CATSuperJournalForFastRun
{
  public :

    CATSuperJournalForFastRun(CATCGMJournalList * iOldJournal, CATPAD * iPAD, CATSoftwareConfiguration* ipConfig);
    virtual ~CATSuperJournalForFastRun();

    CATCGMHashTableWithAssoc * _J;
    CATCGMJournalList * _oldJournal;
    CATPAD * _PAD;

    void Compute(int iScenarioType);
    int AddJ(CATTopology * iTopo1, CATTopology * iTopo2);
    int ComputeJfromJournal(CATCGMJournalList * iJournal);
    CATBoolean ShareOneElement(CATTopology * iTopo1, CATTopology * iTopo2, int iLevel);
    int ComputeJ_Edges_BetweenLoops(CATTopology * iTopo1, CATTopology * iTopo2);
    int ComputeJ_Loop_BetweenFaces(CATTopology * iTopo1, CATTopology * iTopo2);
    int ComputeJ_Loop();
    int ComputeJ_Level(CATPAD_TopologyType iLevelType);

    CATBoolean LinkedElements(CATTopology * iTopo1, CATTopology * iTopo2, int iLevel);
    int LocateItem(CATTopology * iTopo, CATCGMHashTable *& result);

    // ---COPIE DE CONTEXT---
    int GetElements(CATTopology *iTopo, int iLevel, CATCGMHashTableWithAssoc *&oElements);
    int SetLocationPointer(CATLocation *& opLocation, CATLocation iLocation);
    int SetOrientationPointer(CATLocation *& opOrientation, CATLocation iOrientation);


    CATOrientation _CATOrientationNegative;
    CATOrientation _CATOrientationPositive;
    CATOrientation _CATOrientationUnknown;
    CATLocation _CATLocationInner;
    CATLocation _CATLocationNeutral;
    CATLocation _CATLocationOuter;
    CATLocation _CATLocationFull;
    CATLocation _CATLocationIn3DSpace;
    CATLocation _CATLocationIn2DSpace;
    CATLocation _CATLocationUnknown;

    CATCGMHashTableWithAssoc * _LoopDataCache;

    CATSoftwareConfiguration * _pConfig;

};
#endif
