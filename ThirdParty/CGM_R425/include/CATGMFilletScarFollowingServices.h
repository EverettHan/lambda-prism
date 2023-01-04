/* -*-C++-*- */

#ifndef CATGMFilletScarFollowingServices_H
#define CATGMFilletScarFollowingServices_H
/*  
=============================================================================

RESPONSABLE  : V Bouvier

DESCRIPTION  : For Fillet Scar project
               
=============================================================================
*/

#include "CATPersistentCell.h"
#include "CATCGMVirtual.h"
#include "ListPOfCATEdge.h"
#include "CATListOfInt.h"
#include "ListPOfListPOfCATFace.h"
#include "ListPOfListPOfCATEdge.h"
#include "CATLISTP_CATMathTransformation.h"

class CATPersistentCellInfra;
class CATPersistentBody;
class CATCGMJournalList;
class CATEdge;
class CATMathTransformation;

/** @nodoc @nocgmitf */
class ExportedByPersistentCell CATGMFilletScarFollowingServices : public CATCGMVirtual
{
public:

  //Constructor
  CATGMFilletScarFollowingServices(CATPersistentCellInfra * iPCellInfra, CATBoolean iDuplicateMode);
  //Desctructor
  ~CATGMFilletScarFollowingServices();

  //@nocgmitf
  void RematchRelimitedPersistentBody(CATPersistentBody * iInputPersistentBody, CATPersistentBody * iFixedPBody, CATPersistentBody * iExtrapolatedPBody, CATPersistentBody * iTransformedPersistentBody, CATPersistentBody * ioPersistentBodyToRematch, CATCGMJournalList * iRelimJournal);

  //@nocgmitf
  void RematchAfterTopPattern(CATPersistentBody * iInputPersistentBody, CATPersistentBody * ioPersistentBodyToRematch, ListPOfCATFace & iInputFaceList, CATLISTP(CATMathTransformation) & iTransfoList, CATCGMJournalList * iJournal);

  //@nocgmitf
  void RematchAfterThick(CATPersistentBody * iInputPersistentBody, CATPersistentBody * ioPersistentBodyToRematch, ListPOfCATFace & iInputFaceList, CATLISTP(CATMathTransformation) & iTransfoList, CATCGMJournalList * iJournal);

  //@nocgmitf
  void RematchPersistentEdgesAfterXTrim(CATPersistentBody & iInputPBody, CATPersistentBody & iXTrimResultPersistentBody, CATCGMJournalList & iXTrimJournal, CATPersistentBody & iNotExtrapolatedPBody);

private:

  //RematchRelimitedPersistentBody methods
  void ComputeFreeBorderEdgesJournalForRematch(CATPersistentBody * iInputPersistentBody, CATPersistentBody * iFixedPBody, CATPersistentBody * iExtrapolatedPBody, CATPersistentBody * iTransformedPersistentBody, CATCGMJournalList * iRelimJournal, CATPersistentBody * iOutputPersistentBody, CATCGMJournalList *& oEdgeJournal);

  //RematchAfterTopPattern methods
  void GetLocalEdgeToFaces(ListPOfCATEdge & iEdgeList, CATCGMJournalList * iJournal, ListPOfListPOfCATFace & oEdgeToFaceList, CATListOfInt & oInfoExistenceList);
  CATCGMJournalList * GenerateEdgeJournal(ListPOfCATEdge & iInputEdgeList, ListPOfListPOfCATFace & iEdgeToFaceList, CATCGMJournalList * iJournal, CATListOfInt & iInfoExistenceList, ListPOfCATFace & iInputFaceList, CATLISTP(CATMathTransformation) & iTransfoList, CATPersistentBody & iPBodyToRematch);
  void UpdateInfoToEdge(ListPOfListPOfCATEdge & iInfoToImageEdgeList, ListPOfCATFace &iFaceList, CATLONG32 iInfo=0);
  void GenerateJournalFromInfoToEdgeList(CATEdge * iInputEdge, ListPOfListPOfCATEdge & iInfoToImageEdgeList, CATCGMJournalList * oEdgeJournal, CATLISTP(CATMathTransformation) & iTransfoList, CATPersistentBody & iPBodyToRematch);
  CATEdge * GetChildrenEdgeThroughTransfo(CATEdge * iEdge, ListPOfCATEdge & iEdgeList, CATMathTransformation & iMathTransfo);

  //RematchPersistentEdgesAfterXTrim methods
  void GetModifiedEdgeListAfterXTrim(CATPersistentBody & iNotExtrapolatedPBody, CATPersistentBody & iXTrimResultPersistentBody, ListPOfCATEdge & oEdgeList, ListPOfCATFace & oFaceList);

  //common methods
  double GetDistanceBetweenTwoEdges(CATEdge * iFirstEdge, CATEdge * iSecondEdge, CATMathTransformation * iMathTransfo=NULL);//iMathTransfo on iFirstEdge
  void EstimateRatioPoint(double iRatio, CATEdge & iEdge, CATMathPoint& oResult);
  void ComputeLinksBetweenEdges_Logical(CATPersistentBody & iInputPBody, 
                                        CATPersistentBody & iXTrimResultPersistentBody, 
                                        ListPOfCATEdge    & iXTrimResultEdgeList, 
                                        CATPersistentBody & iNotExtrapolatedPBody, 
                                        ListPOfCATEdge    & iNotExtrapolatedEdgeList, 
                                        CATCGMJournalList & iXTrimJournal, 
                                        CATListOfInt      & oLinkList);
  void ComputeLinksBetweenEdges_Logical_ForRelim(CATPersistentBody & iInputPBody,
                                               CATPersistentBody & iFixedPBody,
                                               CATPersistentBody & iResultPersistentBody, 
                                               ListPOfCATEdge    & iResultEdgeList,
                                               CATPersistentBody & iExtrapolatedPBody,
                                               CATPersistentBody & iTransformedPBody, 
                                               ListPOfCATEdge    & iTransformedEdgeList, 
                                               CATCGMJournalList & iRelimJournal, 
                                               CATListOfInt      & oLinkList);
  void ComputeLinksBetweenEdges_Numerical(CATPersistentBody & iRefPBody, ListPOfCATEdge & iRefEdgeList, ListPOfCATFace & iRefFaceList, CATPersistentBody & iToLinkWithPBody, ListPOfCATEdge & iToLinkWithEdgeList, ListPOfCATFace & iToLinkWithFaceList, CATListOfInt & ioLinkList, CATLISTP(CATMathTransformation) * iTransfoList=NULL);
  void ComputeJournalFromLinkList(ListPOfCATEdge & iInputEdgeList, CATPersistentBody & iInputPBody, ListPOfCATEdge & iOutputEdgeList, CATPersistentBody & iOutputPBody, CATListOfInt & iLinkList, CATCGMJournalList *& oEdgeJournal);//iOutputEdgeList parallel to linkList
  void DrawTrace(CATListOfInt & iLinkList);
  CATBoolean HasAlreadyAPersistentEdge(CATEdge & iEdge, CATPersistentBody & iPBody);

private :

  CATPersistentCellInfra * _PersistentCellInfra;

  CATBoolean               _DuplicateMode;

};

#endif
