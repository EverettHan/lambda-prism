#ifndef CATFaceOrder_h
#define CATFaceOrder_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
// 
// Documentation : http://wikigm/mediawiki/index.php/CATFaceOrder
//==========================================================================
// Jun.  10 LD2 Creation                                           LD2 / WQO
// 18/06/19 NLD Ajout Init()
//==========================================================================
#include "ListPOfCATBody.h"
#include "ExportedByCATTopologicalObjects.h"
#include "CATMathInline.h"
#include "CATBoolean.h"

class CATBody;
class CATCGMJournalList;
class CATCGMHashTableWithAssoc;
class CellHashTableAssocList;
class CATCell;
class CATFace;
class CATSoftwareConfiguration;
class CATCXShell;
class CATShell;
class CATAdaptiveHashTable;
class CATCXFace;

class ExportedByCATTopologicalObjects CATFaceOrder
{
public:
  CATFaceOrder(CATSoftwareConfiguration * ipConfig          );
  CATFaceOrder(CATSoftwareConfiguration * ipConfig          ,
               CATLISTP(CATBody)        * ipListOfInputBody ,
               CATCGMJournalList        * ipJournal         , 
               CATBody                  * ipOutputBody      );

  // deprecated constructors
  CATFaceOrder();

  ~CATFaceOrder();

  void Reset();

  // Input data
  void AddInputBody       (CATBody           * ipInputBody       );
  void SetListOfInputBody (CATLISTP(CATBody) * ipListOfInputBody );
  void SetJournal         (CATCGMJournalList * ipJournal         );
  void SetOutputBody      (CATBody           * ipOutputBody      );

  // To index resulting faces which are not into inputs and orphaned of face in the journal
  // the following association allows to give a link between the result face and an input one
  // ex: EdgeI -C-> FaceR and SetAssoc(EdgeI, FaceI) => Index of FaceR := Index of FaceI
  void SetAssocForJournalIndexing(CATCell * ipFollowedCell, CATFace * ipInputFace);

  // This option allows to give a journal/result with orphaned resulting faces
  // These faces don t get indices (not into the inputs or the journal, 
  // or with a Create order without parent face) 
  // These faces are ordered according to their coordinates
  // This kind of situation is forbidden by default (throw)
  INLINE void SetAcceptOrphanedFace(CATBoolean iValue = TRUE) {_AcceptOrphanedFace = iValue;}

  //Calling SetAcceptFrozenBody(TRUE), you allow CATFaceOrder to treat a frozen ipOutputBody.
  //In this case you have to use GetResult() to get the body with ordered faces,
  //beacause it could be different from ipOutputBody.
  //Note that no object is removed from factory in any case: if a new body is created,
  //the old one is still in factory, and its lifecycle is under your responsability.
  INLINE void SetAcceptFrozenBody(CATBoolean iValue = TRUE) {_TreatFrozenBodies = iValue;}

  // Execution
  // - all in one
  void Run();
  // - or step by step
  void Run_IndexingOfInputs();
  void Run_IndexingOfJournal();
  void Run_OrderingSubstitution();

  //GetResult() returns the body with ordered faces.
  INLINE CATBody  * GetResult() {return _pResultBody;}

  static CATBody  * DuplicateAllShells(CATBody                    * iBody        ,
                                       CATSoftwareConfiguration   * ipConfig     = NULL);

  static CATShell * DuplicateShell    (CATShell                   * ipShell      ,
                                       CATBody                    * ipBodyCreator);

  double DiscretizeValue(double iValue);

private:
  // Internal services
 void Init                           (CATSoftwareConfiguration * ipConfig          = NULL,
                                      CATLISTP(CATBody)        * ipListOfInputBody = NULL,
                                      CATCGMJournalList        * ipJournal         = NULL,
                                      CATBody                  * ipOutputBody      = NULL);

  void Indexing                      (CATCXShell               & CurrentShell,
                                      CATCGMHashTableWithAssoc & TableOfIndices,
                                      int                      & CurrIndex);
  void GeometricSort                 (CATListPV                & CurrFaces);
  void Substitution                  (CATCXShell               & CurrentShell,
                                      CATListPV                & ListOfListOfNullToOrderFaces);
  void ResetIndexesForJournalChildren();
  void AddJournalChild               (CATCXFace                * iCxFace);

  // Internal data
  CATSoftwareConfiguration * _pConfig                 ;
  short                      _LevelToExecute          ;
  CATLISTP(CATBody)        * _pListOfInputBody        ;
  CATCGMJournalList        * _pJournal                ;
  CATBody                  * _pOutputBody             ;
  CATBody                  * _pResultBody             ;
  CATCGMHashTableWithAssoc * _pTableOfIndices         ;
  int                        _CurrIndex               ;
  int                        _nbIndex                 ;
  CATBoolean                 _TreatFrozenBodies       ;
  CATBoolean                 _AcceptOrphanedFace      ;
  CellHashTableAssocList   * _pTableAssocCellFace     ;
  CATAdaptiveHashTable     * _JournalChildrenCxFaces  ;
  short                      _DiscretizeValues        ;
  int                        _ExponentOfResolution    ;
};
#endif
