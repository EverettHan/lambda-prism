#ifndef CATVoBContactCheckUtilities_h
#define CATVoBContactCheckUtilities_h


#include "ExportedByCATTopologicalObjects.h"
#include "CATVoBContactCheck.h"

class CATCXVertex;
class CATSubdIntersectionVertex;
class CATSubdEdge;
class CATSubdFace;
class CATFace;
class CATEdge;
class CATVertex;
class CATMathPoint;
class CATCGMJournalList;
class CATTopData;
class CATGeoFactory;
class CATTopVoBOperator;
class CATTopOperator;
class CATExtTopOperator;
class CATTopologicalOperator;
class CATSubdArrayOccurenceP;
class CATLISTP(CATBody);

CATBoolean IsOneCellBoundingAnotherCell(CATCell* FirstCell, CATCell* SecondCell);
CATBoolean ProjectVertexOnFace(CATGeoFactory * iFactory, CATTopData *iLocalData, CATVertex * iVertex, CATFace * iFace, double Tolerance, CATBoolean AcceptOnBoundary);
CATBoolean CheckPointOnEdge(CATGeoFactory * iFactory, CATTopData * iLocalData, CATMathPoint& iMathPoint, CATEdge* iEdge, double Tolerance);
void ConvertSurParamBetweenTwoFaces(CATGeoFactory * iFactory, CATTopData * iLocalData, 
                                    CATLISTP(CATSurParam)* ioSurParamList, CATFace* OriginalFace, CATFace* ResultFace, double Tolerance);

void SaveVertexContactInfo(CATVoBContactCheck * VoBContactCheck, CATSubdFace* ThisFace, CATSubdIntersectionVertex * CurrentIV, CATCGMJournalList* Journal);
void SaveEdgeContactInfo(CATVoBContactCheck * VoBContactCheck, CATSubdFace* ThisFace, CATSubdEdge * ImpasseEdge, CATCGMJournalList* Journal);

// DLR6 - added for HF 824293
void UpdateEdgeInContactCells(CATVoBContactCheck * VoBContactCheck, CATEdge* ipCATEdgeToReplace, const CATSubdArrayOccurenceP& iCandidatesForEdgeReplacement);
void UpdateEdgeInVoBContact(ListPOfCATCell  * ipVoBContact,
                                       int    iIndEdgeInVoBcontact, CATEdge * ipCATEdgeToReplace, const CATCXVertex * ipEdgeExtremity,
              const CATSubdArrayOccurenceP   &iCandidatesForEdgeReplacement);
// QCN5 - added for IR 921528, also for 925458
void RemoveVertexInVoBContact(CATVoBContactCheck* VoBContactCheck);

// This method is created for DynSolidSplit, because the contact cells are detected in a inter operator (TopSplitBySkin), 
// and these cells are the intermediate result which could be removed after run of TopSplitBySkin. So for each contact cell, 
// it needs to find its original cell in input body of DynSolidSplit by using TopSplitBySkin's journal. 
ExportedByCATTopologicalObjects void CheckOriginalContactCell(CATTopOperator * iOperator, CATVoBContactCheck * iVoBContactCheck);

ExportedByCATTopologicalObjects CATBoolean CreateVoBForBooleanOperator(CATExtTopOperator * OpExt, CATTopologicalOperator* iBooleanOp, CATBoolean WarningModeActive = FALSE);

// WQO Sept. 13 Create the VoB operator which will be automatically launched after the RunOperator of ipOperatorExt
//              All the cells created by the considered operation (according to the journal of the operator) 
//              will be checked and if some non-manifold configurations are found, a Warning will be thrown by 
//              _AfterRun_Check with the non-manifold cells into a diagnosis body
//              The optional list of Bodies can be set to give additional input Bodies (ex: projection of a no-copy input)
//              used to identify the resulting cells which are created by the operation
ExportedByCATTopologicalObjects CATBoolean CreateVoBForNonManifoldWarning(CATExtTopOperator * ipOperatorExt, CATLISTP(CATBody) * ipInputBodiesToAdd = NULL);

#endif

