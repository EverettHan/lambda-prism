// COPYRIGHT DASSAULT SYSTEMES 2015
//=============================================================================
//
// CATMultiPAD: 
//  Set of CATPAD. (@See "CATPAD.h" for more information)
//  
//
//
//=============================================================================
//
// Usage notes: 
//
//
//=============================================================================
//  May 2015  Creation                                                   U29
//=============================================================================

#ifndef CATMultiPAD_H
#define CATMultiPAD_H

#include "CATListPV.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATPAD.h"
#include "CATListOfInt.h"

class CATTopology;

class ExportedByCATTopologicalObjects CATMultiPAD
{

public:

  //-------------------------------------------------------
  //              Creation and destruction methods
  //-------------------------------------------------------

  /**
  * Default Constructor
  */
  CATMultiPAD();

  /**
  * Destructor
  */
  ~CATMultiPAD();

  //-------------------------------------------------------
  //                   Operator methods
  //-------------------------------------------------------

  // Is it a persistent topology ?
  CATBoolean IsPersistent  (CATTopology * ipTopoObj, int * opInWhichBody=NULL);
  // Is it a appeared topology ?
  CATBoolean IsAppeared    (CATTopology * ipTopoObj, int * opInWhichBody=NULL);
  // Is it a disappeared topology ?
  CATBoolean IsDisappeared (CATTopology * ipTopoObj, int * opInWhichBody=NULL);
  // Is it a persistent, appeared or disappeared topology ?
  CATBoolean IsAnything    (CATTopology * ipTopoObj);

  //Option to handle shared faces between the two PAD or not.
  //It can be activated only if we have two PADs
  void SetSharingMode(CATBoolean iSharingMode);

  void GetAllPersistents(CATListPV& oElems, CATPAD_TopologyType iTopologyType, CATBoolean iDuplicate, int iIdxPAD);

  void GetAllAppearedOrAllDisappeared(CATListPV& oElems, CATPAD_TopologyType iTopologyType, 
    CATBoolean iDuplicate, int iIdxPAD, CATPAD_ComparisonType iComparaisonType);

  void GetAllCells(CATListPV& oElems, CATPAD_TopologyType iTopologyType, CATBoolean iDuplicate, 
    int iIdxPAD, CATPAD_ComparisonType iComparaisonType);

  CATBoolean Is(CATPAD_ComparisonType iComparisonType, 
    CATTopology         * ipTopoObj);

private:

  //-------------------------------------------------------
  //                   Internal Methods
  //-------------------------------------------------------

  CATBoolean IsPersistentInAtLeastOnePAD (CATTopology * ipTopoObj, int * opInWhichBody=NULL);
  CATBoolean IsAppearedInAtLeastOnePAD   (CATTopology * ipTopoObj, int * opInWhichBody=NULL);
  CATBoolean IsDisappearedInAtLeastOnePAD(CATTopology * ipTopoObj, int * opInWhichBody=NULL);

  //-------------------------------------------------------
  //                   Attributs
  //-------------------------------------------------------

public:

  CATListPV  _PADs;

private:

  //flag to handle shared faces between the two PAD or not
  CATBoolean _sharingMode;

};

#endif
