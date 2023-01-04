#ifndef CATTopCGMAttributePropagatorEngine_H
#define   CATTopCGMAttributePropagatorEngine_H
// COPYRIGHT DASSAULT SYSTEMES  2009
//===========================================================================  
//  Class  CATTopCGMAttributePropagatorEngine  
//---------------------------------------------------------------------------  
//
//  Class to propagate CGM Attributes after the execution of a topological operator.
//
//  A CATTopCGMAttributePropagatorEngine allow propagation of CGM Attributes from input bodies 
//    to output bodies.
//
//  If an origin cell own a CGM Attribute, then under given conditions (user-defined)
//  the target cell will own a CGM Attribute.

//  The way how the new CGM attribute is defined depends on the specificity 
//  of the attribute, i.e  .....
//  The Cell Tracker which relies on CGM Journal of the Operator, is used 
//  to match pertinent output cells with input cells.
//  
//===========================================================================   
#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "CATListOfCATCells.h"
#include "CATMathInline.h"
//#include "CATCGMJournalList.h"
#include "ListPOfCATBody.h"
#include "ListVOfLong.h"
#include "CATErrorDefs.h"
#include "CATBody.h"
#include "CATCGMJournal.h"
#include "CATListOfCATCGMJournals.h"
#include "CATCollec.h"
#include "CATTopCGMAttributeLabel.h"
#include "CATTopHiddenSeamCellQuery.h"
#include "CATTopImprintAttributeServices.h"
//#include "CATTopCellWithCGMAttributesState.h"
#include "CATTopImprintCellServices.h"



class CATTopData;
class CATEdgeCurve;
class CATCurve;
class CATCell;
class CATDomain;
//class CATBody;
class CATTopOperator;
class CATCGMCellTrackerImp;
class CATCGMOutput;
class CATCGMJournal;
class CATCGMJournalList;
class CATCGMJournalItem;
class CATSoftwareConfiguration;
class CATCellHashTable;
class CATCGMHashTableWithAssoc;
class CATLISTP(CATCurve);
class CATLISTP(CATCGMJournal);
class CATTopCellWithCGMAttributesState;
class CATTopHashTableOfCellWithCGMAttributesState;

/** @nodoc @nocgmitf */
enum CATCGMKindOfCells
{
   CATCGMKindOfCells_InputCells,
   CATCGMKindOfCells_OutputCells
};

/** @nodoc @nocgmitf */
/**
* Interface Class to analyze and propagate CGM Attributes from input bodies to output bodies by using Cell Tracker.
* Class to propagate CGM Attributes after the execution of a topological operator.
*
* A CATTopCGMAttributePropagatorEngine allow propagation of CGM Attributes from input bodies 
* to output bodies.
*
* If a target cell an input cell as origin that a CGM Attribute, then under given conditions (user-defined)
* the target cell will own a CGM Attribute.

* The way how the new CGM attribute is defined depends on the specificity 
* of the attribute.
* The Cell Tracker which relies on CGM Journal of the Operator, is used 
* to match pertinent output cells with input cells.
*
*/



/** @nodoc @nocgmitf */
class ExportedByCATTopologicalObjects CATTopCGMAttributePropagatorEngine
{
public:
         
   /** @nodoc @nocgmitf */
   /** 
   * Method to create a CATTopCGMAttributePropagatorEngine without the context of a CATTopOperator
   *
   * <br><b>Role</b>: Method to create a CATTopCGMAttributePropagatorEngine without the context of a CATTopOperator
   *
   * @param piSoftConfig 
   * a pointer to a SoftwareConfigucration
   *
   * @param iListOfInputBody 
   * list of input bodies from where result bodies have been built.
   *
   * @param iListOfOutputBody
   * list of output bodies that have been built rom input bodies.
   *
   * @param piListOfCGMJournal 
   * list of CGM Journals that describe how output bodies have been built from input bodies.
   *   
   */
   static CATTopCGMAttributePropagatorEngine *CreateCATTopCGMAttributePropagatorEngine(CATSoftwareConfiguration * piSC,
                                                                                       ListPOfCATBody           & iListOfInputBody,
                                                                                       ListPOfCATBody           & iListOfOutputBody,
                                                                                       CATLISTP(CATCGMJournal)  & iListOfCGMJournal,
                                                                                       CATTopCGMAttributeLabel    iCGMAttributeFlags);

   /** @nodoc @nocgmitf */
   /**
   * Method to create a CATTopImprintCellManager with the context of a CATTopOperator
   *
   * <br><b>Role</b>: Method to create a CATTopCGMAttributePropagatorEngine with the context of a CATTopOperator
   *
   */
   static CATTopCGMAttributePropagatorEngine *CreateCATTopCGMAttributePropagatorEngine(CATTopOperator *piTopOperator,
                                                                                       CATTopCGMAttributeLabel iCGMAttributeFlags);
      
   /** @nodoc @nocgmitf */
   /** 
   * Dtor  
   */
   virtual ~CATTopCGMAttributePropagatorEngine();
   
   /** @nodoc @nocgmitf */
   /**
   * Generic Run to propagate CGM Attributes from Input Bodies to Output Body through Cell Tracker
   * @return
   * <dl>
   * <dt><tt>S_OK</tt>     <dd>if it's succeeded
   * <dt><tt>FALSE</tt>    <dd>if failed
   * </dl>
   */
   HRESULT Run();
   
   /** @nodoc @nocgmitf */
   /** 
   * Set the Top Operator that build output bodies from input bodies.
   *
   * <br><b>Role</b>: Set the Top Operator that build output bodies from input bodies.
   *
   * @param piTopOperator 
   * the under scope Top Operator.
   *
   */
   INLINE void SetTopOperator(CATTopOperator *piTopOperator);

   /** @nodoc @nocgmitf */
   /** 
   * Set the Input Bodies from where CGM Attributes will be popagated.
   *
   * <br><b>Role</b>: Set the Input Bodies.
   *
   * @param iInputBodies 
   * the input bodies.
   *
   */
   INLINE void SetInputBodies(ListPOfCATBody& iInputBodies);

   /** @nodoc @nocgmitf */
   /** 
   * Set the Output Bodies to where the CGM attributes will be propagated.
   *
   * <br><b>Role</b>: Set the Output Bodies.
   *
   * @param iOutputBodies 
   * Set the output bodies.
   *
   */
   INLINE void SetOutputBodies(ListPOfCATBody& iOutputBodies);

   /** @nodoc @nocgmitf */
   /** 
   * Set the Kind of The attribute to be propagated
   *
   * <br><b>Role</b>: Set the Kind of The attribute to be propagated.
   *
   * @param iKindOfAttributes
   *  Kind of the CGM Attributes to be propagated.
   *
   */
   INLINE void SetCGMAttributeFlagsToManage(CATTopCGMAttributeLabel iKindOfAttributes);

   /** @nodoc @nocgmitf */
   /** 
   * Set the List of CGM Journals that described how Output Bodies have been 
   * built from Input bodies.
   *
   * <br><b>Role</b>: Set the List of CGM Journals that described how Output Bodies have been
   * built from Input bodies.
   *
   * @param piListOfCGMJournal 
   * Set the list of CGM Journals.
   *
   */
   INLINE void SetListOfCGMJounal(CATLISTP(CATCGMJournal)& iListOfCGMJournal);

   /** @nodoc @nocgmitf */
   /** 
   * Enable/Disable the option <tt>KeepCurrentCellTracker</tt>, which allow to use the same Cell Tracker for the next 
   * operation (Internal Use)
   *
   * <br><b>Role</b>: Set the List of CGM Journals that described how Output Bodies have been
   * built from Input bodies.
   *
   * @param iKeepCurrentCellTracker 
   * to activate/desactivate the option
   *
   */
   INLINE void SetKeepCurrentCellTracker(CATBoolean iKeepCurrentCellTracker);


   /** @nodoc @nocgmitf */
   /** 
   * Enable/Disable the option <tt>KeepCurrentCellTracker</tt>, which allow to use the same Cell Tracker for the next 
   * operation (Internal Use)
   *
   * <br><b>Role</b>: Set the List of CGM Journals that described how Output Bodies have been
   * built from Input bodies.
   *
   * @param iKeepCurrentCellTracker 
   * to activate/desactivate the option
   *
   */
   static CATTopCGMAttributeLabel GetHandledCGMAttributes(CATGeoFactory *iFactory);
   
   /** @nodoc @nocgmitf */
   /** 
   * 
   * 
   *
   * <br><b>Role</b>: 
   *
   * @param 
   *
   */
   INLINE void ForceTrackingOfCellInAllInputBodies(CATBoolean iOption);

   /** @nodoc @nocgmitf */
   /** 
   * Short role of the method.
   *
   * <br><b>Role</b>: Explain what this method does.
   *
   * @param iHiddenVertexIfIncidEdgesAreHidden [in]
   *   The parameter role...
   *
   * @return
   *   Explain return values
   *
   */
   INLINE void SetCheckIfCellIsSmartInOutputBody(CATBody *iBody, CATBoolean iCheckIfCellIsSmartInOutputBody);
      
   /** @nodoc @nocgmitf */   
   /**
   * Dump CGM Attributes of all input and output bodies
   *
   * @param ios 
   * the stream through where information are dumped.
   *
   */
   void Dump(CATCGMOutput& ios,const char *piWord);

   /** @nodoc @nocgmitf */
   /**
   * Test if the env. var. taht enable CGMAttributeMannaged has been activated
   *   @return
   *     <dl>
   *     <dt><tt>TRUE</tt>      <dd>if the env. var. is activated
   *     <dt><tt>FALSE</tt>    <dd> otherwise
   *     </dl> 
   */
   INLINE static CATBoolean IsActive(CATGeoFactory *iInFactory,CATGeoFactory *iOutFactory);

   /** @nodoc @nocgmitf */
   INLINE void SetUseTassedJournalForCellTracker(CATBoolean iOption);

   /** @nodoc @nocgmitf */
   INLINE void SetAmbiguityTrackingByGeometry(CATBoolean iOption);

#ifdef CATIACGMR421CAA
   /** @nodoc @nocgmitf */
   INLINE void SetFilterChildrenCellsForSeamCases(CATBoolean iOption);
   /** @nodoc @nocgmitf */
   INLINE void SetCheckImprintOnVertex(CATBoolean iOption);
   /** @nodoc @nocgmitf */
   INLINE void SetPropagateImprintOnFaces(CATBoolean iOption);
   /** @nodoc @nocgmitf */
   INLINE void SetCorrectImprintJournal(CATBoolean iOption);
   /** @nodoc @nocgmitf */
   INLINE void SetInputBodiesInCopyMode(CATBoolean iOption);
      /** @nodoc @nocgmitf */
   INLINE void SetActivateImprintJournaling(CATBoolean iOption);
#endif

   
   /** @nodoc @nocgmitf */
   INLINE void SetPropagateFromImprintedVtxToEdge(CATBoolean iOption);
   /** @nodoc @nocgmitf */
   static int IsForceNoCellTracker();
   
   
   /** @nodoc @nocgmitf */
   static int IsAttributePropagationPCSActivated();

protected:

   /** @nodoc @nocgmitf */   
   /**
   * Scan A CGM Journal to extract pertinent cells under a given criteria :
   * if the de(a)scendant(s) of a cell (or its bounded cells) that belong 
   * to the target body has a CGM Attribute hence the cell is pertinent  
   *
   * <br><b>Role</b>: Dump CGM Attributes of all input and output bodies
   *
   * @param piTargetBody
   * the Body under scope, i.e in which pertinent cells are detected  
   * the stream through where information are dumped.
   *
   * @param iJournal
   * A CGM Journal that describe how the output body under scope has been built 
   * from the input bodies
   *
   * @param piHashTableOfCellsOfTargetBody
   * Hash Table that contains a part or all cells of the output body under scope
   *
   * @param pioHashTableOfCellsInJournal
   * An empty Hash Table that will filled with output cells referenced 
   * in CGM journal and belong to the output body under scope
   *
   * @param oListOfTargetCells
   * As result of the method, a list of pertinent output cells.
   *
   * @param oListOfNonSelectedCells
   * As result of the method, a list of non pertinent cells.
   *
   * @param iKindOfCells
   * Shows what kind of pertinent cells are we looking for, Input or Output Cells
   *
   */
   CATBoolean RetrievePertinentCellsFromJournal(CATBody                                     * piTargetBody,
                                                CATCGMJournalList                           * piJournal,
                                                CATCellHashTable                            * piHashTableOfCellsOfTargetBody, 
                                                CATCellHashTable                            * pioHashTableOfCellsInJournal,
                                                CATCellHashTable                            * pioHashTabOfModifiedAndDeletedInputCellsInJournal,
                                                CATCGMHashTableWithAssoc                    * pioHashTabOfOutputCellsWithItsBorders,
                                                CATTopHashTableOfCellWithCGMAttributesState * pioHashTab_OutputCellsWithCGMAttributesState,
                                                CATCGMKindOfCells                             iKindOfCells);
   
   /** @nodoc @nocgmitf */
   /**
   * Analyze an Item of a CGM Journal to extract pertinent cells under 
   * the given criteria :
   * if the de(a)scendant(s) of a cell (or its bounded cells) that belong 
   * to the target body has a CGM Attribute hence the cell is pertinent  
   *
   * <br><b>Role</b>: Dump CGM Attributes of all input and output bodies
   *
   * @param piTargetBody
   * the Body under scope, i.e in which pertinent cells are detected  
   * the stream through where information are dumped.
   *
   * @param iJournal
   * A CGM Journal that describe how the output body under scope has been built 
   * from the input bodies
   *
   * @param piHashTableOfCellsOfTargetBody
   * Hash Table that contains a part or all cells of the output body under scope
   *
   * @param pioHashTableOfCellsInJournal
   * An empty Hash Table that will filled with output cells referenced 
   * in CGM journal and belong to the output body under scope
   *
   * @param oListOfTargetCells
   * As result of the method, a list of pertinent output cells.
   *
   * @param oListOfNonSelectedCells
   * As result of the method, a list of non pertinent cells.
   *
   * @param iKindOfCells
   * Shows what kind of pertinent cells are we looking for, Input or Output Cells
   *
   */
   CATBoolean RetrievePertinentCellsFromJournalItem(CATBody                                     * piTargetBody,
                                                    CATCGMJournalItem                           * iJournalItem,
                                                    CATCellHashTable                            * piHashTableOfCellsOfTargetBody, 
                                                    CATCellHashTable                            * pioHashTableOfCellsInJournal,
                                                    CATCellHashTable                            * pioHashTabOfModifiedAndDeletedInputCellsInJournal,
                                                    CATCGMHashTableWithAssoc                    * pioHashTabOfOutputCellsWithItsBorders, 
                                                    CATTopHashTableOfCellWithCGMAttributesState * pioHashTab_OutputCellsWithCGMAttributesState,
                                                    CATCGMKindOfCells                             iKindOfCells);


   /** @nodoc @nocgmitf */
   /**
   * 
   * 
   * 
   * 
   * <br><b>Role</b>: 
   *
   * @param piCell
   *
   * @param piCellHashTableOfBody
   *
   * @param ioListOfManagedAttributePerCell
   *
   */
   void GetLabelsOfManagedCGMAttributeOfCell(CATCell *piCell,
                                             CATCellHashTable *piCellHashTableOfBody,
                                             CATTopCGMAttributeLabel iCGMAttrFlagsRequested,
                                             CATListOfInt& iLisOfCGMAttrFlagRequested,
                                             CATTopCGMAttributeLabel& ioCGMAttrFlagsFound,
                                             CATListOfInt& ioLisOfCGMAttrFlagFound);

   /** @nodoc @nocgmitf */
   /**
   * 
   * 
   * 
   * 
   * <br><b>Role</b>: 
   *
   * @param piCell
   *
   * @param iListOfManagedKindAttributeForCell
   *
   */
   void UpdateTableOfPertinentCells(CATCellHashTable *piCellHashTable,
                                    CATBody *piBody,
                                    CATTopHashTableOfCellWithCGMAttributesState *pioHashTab_OutputCellsWithCGMAttributesState,
                                    CATTopCGMAttributeLabel iCGMAttrFlagsCandidate,
                                    CATListOfInt &iListOfCGMAttrFlagsCandidate,
                                    CATTopCGMAttributeLabel& ioCGMAttrFlagsEffective,
                                    CATListOfInt &ioListOfCGMAttrFlagsEffective);


   /** @nodoc @nocgmitf */
   /**
   * 
   * 
   * 
   * 
   * <br><b>Role</b>: 
   *
   * @param piCell
   *
   * @param iListOfManagedKindAttributeForCell
   *
   */
   void UpdateTableOfPertinentCells(CATCell                                     * piCell,
                                    CATBody                                     * piBody,
                                    CATTopHashTableOfCellWithCGMAttributesState * pioHashTab_OutputCellsWithCGMAttributesState,
                                    CATTopCGMAttributeLabel                       iCGMAttrFlagsCandidate,
                                    CATListOfInt                                & iListOfCGMAttrFlagsCandidate,
                                    CATTopCGMAttributeLabel                     & ioCGMAttrFlagsEffective,
                                    CATListOfInt                                & ioListOfCGMAttrFlagsEffective);

   /** @nodoc @nocgmitf */
   /**
   * 
   * 
   * 
   * 
   * <br><b>Role</b>: 
   *
   * @param piCell
   *
   * @param iListOfManagedKindAttributeForCell
   *
   */
   CATBoolean CalculateAttrFlagsForBoderedCells(CATCell *piSourceCell,
                                                CATCell *piOutputCell, 
                                                CATTopCGMAttributeLabel iCGMAttrFlagsRequested       , CATListOfInt &iListOfCGMAttrFlagsRequested,
                                                CATTopCGMAttributeLabel iCGMAttrFlagsOfSrcCell       , CATListOfInt &iListOfCGMAttrFlagsOfSrcCell,
                                                CATTopCGMAttributeLabel iCGMAttrFlagsOfOutCell       , CATListOfInt &iListOfCGMAttrFlagsOfOutCell,
                                                CATTopCGMAttributeLabel &ioCGMAttrFlagsForBorderCells, CATListOfInt &ioListOfCGMAttrFlagsForBorderCells,
                                                CATTopCGMAttributeLabel &ioCGMAttrFlagsForBorderOfBordersCells,CATListOfInt &ioListOfCGMAttrFlagsForBorderOfBordersCells,
                                                short &ioDeepDim);

   /** @nodoc @nocgmitf */
   /**
   * Clean Data 
   * 
   * <br><b>Role</b>: Clean Data
   *
   */
   void CleaningDataMembers();

   /** @nodoc @nocgmitf */
   /**
   * Return the dimension of the body under scope
   *
   * <br><b>Role</b>: Return the dimension of the body under scope.
   *
   * @param piBody
   * the body under scope
   *
   * @return
   * The dimension of the body
   */
   short GetDimBody(CATBody *piBody);

   /** @nodoc @nocgmitf */
   /**
   * Insert Cells referenced in the source hash table in the destination hash table
   *
   * <br><b>Role</b>: Insert Cells referenced in the sorce hash table in the destination hash table
   *
   * @param pioDestHashTableOfCells
   * A pointer to the destination hash table of cells
   *
   * @param piSourceHashTableOfCells
   * A pointer to the source hash table of cells
   *
   */
   static void InsertHashTable(CATCellHashTable *& pioDestHashTableOfCells, CATCellHashTable *&piSourceHashTableOfCells);

      /** @nodoc @nocgmitf */
   /**
   * Tune Cell Tracker for specific operators
   *
   * <br><b>Role</b>: Enable specific Cel Tracker options under specific operators
   *
   */
   void CellTrackerTunningForParticularOperators();

   /** @nodoc @nocgmitf */
   /**
   * Dump CGM Attributes of all input and output bodies
   *
   * @param piBody 
   * the body on which all CGM attributes that carried by its Cells
   * will be dumped
   *
   * @param os 
   * the stream through where information are dumped.
   *
   */
   void Dump(CATCGMOutput& os, CATBody *piBody);

   /** @nodoc @nocgmitf */
   /**
   * Dump CGM Attributes of all input and output bodies
   *
   * @param ios 
   * the stream through where information are dumped.
   *
   * @param piCell
   * the Cell on which CGM attribute carried by
   * will be dumped
   *
   * @param piBody
   * the Body to which the Cell belongs
   *
   */
   //void Dump(CATCGMOutput& os, CATCell *piCell, CATBody *piBody = NULL);

   /** @nodoc @nocgmitf */
   /**
   * Fill the HashTable of Cells with their bounded cells. 
   * Focus on cell of thegiven dimension 
   *
   * <br><b>Role</b>: Fill the HashTable of Cells with their bounded cells. 
   * Focus on cell of thegiven dimension 
   *
   * @param iListTargetCells
   * List of Cells that will be scanned to extract their bounded cells
   * Only Cells that have the given dimension
   *
   * @param iDimCell
   * Dimension of Cells that will taking into account
   *
   * @param pioHashTabOfTargetCellsWithItsBoundedCells
   * A pointer to the associative hash table that will be filled
   *
   */
   //CATBoolean InsertBoundedCellsOfCellsInHashTable(ListPOfCATCell   &iListTargetCells,
   //                                                short iDimCell, CATCGMHashTableWithAssoc* pioHashTabOfTargetCellsWithItsBoundedCells);


   /** @nodoc @nocgmitf */
   /**
   * Scan List of Cells to extract their bounded cells and inserted in hash tables 
   *
   * <br><b>Role</b>: Scan List of Cells to extract their bounded cells and inserted in hash tables.
   *
   * @param iListTargetCells
   * List of Cells that will be scanned to extract their bounded cells
   * Only Cells that have the given dimension
   *
   * @param iExcludeFaces
   * If FALSE, Faces that are referenced inn the List of Target Cells will not be taking into account
   *
   * @param pioHashTabOfTargetCellsWithItsBoundedCells
   * A pointer to the associative hash table that will be filled with a Cell and its Bounded Cells
   *
   * @param pioHashTableOfEdges
   * A pointer to the hash table of Edges, each edge of the list of target cells will be inserted
   *
   * @param pioHashTableOfVertices
   * A pointer to the hash table of Vertices, each Vertex of the list of target cells will be inserted
   *
   */
   //CATBoolean ExtractVerticesAndEdges(ListPOfCATCell &iListOfTargetCells,
   //                                   CATBoolean iExcludeFaces, CATCGMHashTableWithAssoc* pioHashTabOfOutputFacesWithItsBorderedEdges,
   //                                   CATCellHashTable *&pioHashTableOfEdges, CATCellHashTable *&pioHashTableOfVertices);



   /** @nodoc @nocgmitf */
   /**
   * Fill the assocciative hash table (Edge, IncidentFaces), in the context of a given body, with Incident Faces
   * by using information stored in the associative hash table that references (Face, Bouded Edges)
   *
   * <br><b>Role</b>: Fill the assocciative hash table (Edge, IncidentFaces), in the context of a given body, 
   * with Incident Faces by using information stored in the associative hash table that references 
   * (Face, Bouded Edges)
   *
   * @param piTargetBody
   * A pointer to the dbody under scope
   *
   * @param piHashTabOfOutputCellsWithItsBorders
   * A pointer to the associative hash table of (Face, Bordered Edges)
   *
   */
   void BuildPartialHashTableOfEdgesWithItsIncidFaces(CATBody *piTargetBody,
                                                      CATCGMHashTableWithAssoc* piHashTabOfOutputCellsWithItsBorders);

   /** @nodoc @nocgmitf */
   /**
   * 
   *
   * @param os 
   * the stream through where information are dumped.
   *
   */
   //void DumpInputs(CATCGMOutput& os);

   /** @nodoc @nocgmitf */
   /**
   * 
   *
   * @param os 
   * the stream through where information are dumped.
   *
   */
   void SaveModel(const char *pWord);

private:   

      /** @nodoc @nocgmitf */
   /** 
   * Method to create a CATTopCGMAttributePropagatorEngine without the context of a CATTopOperator
   *
   * <br><b>Role</b>: Method to create a CATTopCGMAttributePropagatorEngine without the context of a CATTopOperator
   *
   * @param piSoftConfig 
   * a pointer to a SoftwareConfigucration
   *
   * @param iListOfInputBody 
   * list of input bodies from where result bodies have been built.
   *
   * @param iListOfOutputBody
   * list of output bodies that have been built rom input bodies.
   *
   * @param piListOfCGMJournal 
   * list of CGM Journals that describe how output bodies have been built from input bodies.
   *   
   */
   CATTopCGMAttributePropagatorEngine(CATSoftwareConfiguration *piSC,
                                      ListPOfCATBody& iListOfInputBody,
                                      ListPOfCATBody& iListOfOutputBody,
                                      CATLISTP(CATCGMJournal)& iListOfCGMJournal,
                                      CATTopCGMAttributeLabel iCGMAttributeFlags);

   /** @nodoc @nocgmitf */
   /**
   * Method to create a CATTopImprintCellManager with the context of a CATTopOperator
   *
   * <br><b>Role</b>: Method to create a CATTopCGMAttributePropagatorEngine with the context of a CATTopOperator
   *
   */
   CATTopCGMAttributePropagatorEngine(CATTopOperator *piTopOperator,CATTopCGMAttributeLabel iCGMAttributeFlags);

   /** @nodoc @nocgmitf */
   /**
   * forbidden Default Ctor
   *
   * <br><b>Role</b>: Default ctor.
   *
   */
   CATTopCGMAttributePropagatorEngine();

   /** @nodoc @nocgmitf */
   void Init();

   /** @nodoc @nocgmitf */
   /**
   * forbidden Copy Ctor
   *
   * <br><b>Role</b>: Copy ctor.
   *
   */
   CATTopCGMAttributePropagatorEngine(const CATTopCGMAttributePropagatorEngine &iCopy);
   
   /** @nodoc @nocgmitf */
   /**
   * forbidden Equal Operator
   *
   * <br><b>Role</b>: Equal Operator
   *
   */
   CATTopCGMAttributePropagatorEngine& operator = (const CATTopCGMAttributePropagatorEngine &iCopy);

   /** @nodoc @nocgmitf */
   /**
   * Allows Activate CGMAttributeManager if env. var. has been tested once time
   *   @return
   *     <dl>
   *     <dt><tt>TRUE</tt>      <dd>if checking has been done
   *     <dt><tt>FALSE</tt>    <dd> otherwise
   *     </dl> 
   */
   //static void Define(CATGeoFactory *iFactory);

   /** @nodoc @nocgmitf */
   void CorrectImprintJournal(CATCGMJournalList*  pioCGMJournalList,
                              CATCellHashTable *  piHTabOfCellsOfOutputBody,
                              CATCellHashTable *& pioHTOfOutputCellsInJournal,
                              CATCellHashTable *& pioHTOfInputCellsInJournal);


   /** @nodoc @nocgmitf */
   // Private service : must be moved to another generic sevices class.
    static HRESULT GetCommonVertices(CATCell *pEdgeCell1,CATCell *pEdgeCell12,CATLISTP(CATCell) &ioListOfCommonVertices);
    static HRESULT GetCommonEdgesOfFaces(ListPOfCATCell &iAdjacentFaceList, ListPOfCATCell &ioCommonEdgeList);
    static HRESULT GetIncidCells(CATCell *piCell,CATBody *piBody,short iDimIncidCells,ListPOfCATCell &ioListOfIncidCells);
   /*************************** Data ***************************/
   //
   ListPOfCATBody                 _ListOfInputBody;
   CATLISTP(CATBody)              _ListOfOutputBody;
   CATLISTP(CATCGMJournal)        _ListOfCGMJournal;
   CATLISTP(CATBody)              _ListOfAllBodies;
   CATListOfInt                   _ListOfDimOfAllBodies;
   CATCGMHashTableWithAssoc *     _HashTabOfAllBodies;
   
   // Working Tables/Data Structure for Information Capitalisation
   CATCellHashTable            ** _TabHashTableOfCellsOfInputBodies;
   CATCellHashTable            ** _TabOfHashTableOfOutputCellsInJournal;
   // Will reference all input cells modified and/or deleted in the journal 
   CATCellHashTable            ** _TabOfHTabOfModifiedAndDeletedInputCellsInJournal;

   //Hash Table Assoc for input cells  : stores an input cell with labels of its CGM Attibute 
   CATTopHashTableOfCellWithCGMAttributesState  * _HashTab_InputCellsWithCGMAttributesState;

   //Hash Table Assoc for output cells : stores an output cell with its potential labels of CGM Attibute 
   CATTopHashTableOfCellWithCGMAttributesState ** _HashTab_OutputCellsWithCGMAttributesState;
   CATCGMHashTableWithAssoc    ** _TabOfHashTabOfOutputCellsWithItsBorders;
   CATCGMHashTableWithAssoc     * _TabOfHashTabOfInputCellsWithItsBorders;
   CATLISTP(CATCell)              _ListOfReferencedInputCellsInJournal;
   //
   CATTopOperator                *_pTopOperator;
   //
   CATSoftwareConfiguration      *_SC;
   //
   CATCGMCellTrackerImp          *_pCellTracker;
   short                          _KeepCurrentCellTracker;
   CATBoolean                     _CheckIfCellIsSmartInOutputBody;
   //   
   CATBoolean                     _CapitalizeIncidentFacesOfEdgesFromJournal;
   CATBoolean                     _ForceTrackingOfCellInAllInputBodies;
   //
   CATTopCGMAttributeLabel       _CGMAttributeFlags; // By default all CGM Attributes referenced in CATTopCGMAttributeLabel will be considered for propagation
   CATListOfInt                  _ListOfCGMAttributeFlag; 
   CATBoolean                    _ForceGetAllCellsOfOutputBody; 
   CATBoolean                    _UseTassedJournalForCellTracker;
   CATBoolean                    _AmbiguityTrackingByGeometry;
#ifdef CATIACGMR421CAA
   CATBoolean                    _CorrectImprintJournal;
   CATBoolean                    _IsInputBodiesInCopyMode; // By default it is considedered as in copy mode, probably this will be enhanced in the future
   CATBoolean                    _PropagateImprintOnFaces;
   CATBoolean                    _ActivateImprintJournaling; // By default it is activated 
   CATBoolean                    _CheckImprintOnVertex;
   CATBoolean                    _FilterChildrenCellsForSeamCases;
#endif
   CATBoolean                    _PropagateFromImprintedVtxToEdge; // Pour autoriser la propagation des imprint des Vertex Imprint vers les edges 
                                                                   // uniquement ds le context d'imrpint des edges seam sous var d'env
   //static CATBoolean _ForceNoCellTracker; 
   //
   //static CATBoolean           _IsDefined;
   //static CATBoolean            _IsActive;
};

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetTopOperator(CATTopOperator *piTopOperator)
{
   _pTopOperator = piTopOperator;
}

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetInputBodies(ListPOfCATBody& iInputBodies)
{
   int NbInputBodies = _ListOfInputBody.Size();
   int i = 1;
   for (i=1;i<=NbInputBodies;i++)
   {
      CATBody *pCurrBody=_ListOfInputBody[i];
      if (pCurrBody)    pCurrBody->Release();
   }

   _ListOfInputBody.RemoveAll(CATCollec::KeepAllocation);
   NbInputBodies = iInputBodies.Size();
   for (i = 1 ; i <= NbInputBodies; i++)
   {
      CATBody *pCurrBody = iInputBodies[i];
      if (pCurrBody)
      {
         pCurrBody->AddRef();
         _ListOfInputBody.Append(pCurrBody);
      }
   }
}

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetOutputBodies(ListPOfCATBody& iOutputBodies)
{
   int Idx = 0; 
   int NbResBody = _ListOfOutputBody.Size();

   for (Idx=1;Idx<=NbResBody;Idx++)
   {
      CATBody *pCurrResBody = _ListOfOutputBody[Idx];

      if (pCurrResBody)
      {
         pCurrResBody->Release();
      }
   }
   _ListOfOutputBody.RemoveAll(CATCollec::KeepAllocation);

   //
   int NbNewResBody = iOutputBodies.Size();
   for (Idx=1;Idx<=NbNewResBody;Idx++)
   {
      CATBody *pCurrResBody = iOutputBodies[Idx];
      if (pCurrResBody)
      {
         _ListOfOutputBody.Append(pCurrResBody);
         pCurrResBody->AddRef();
      }
   }
}

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetCGMAttributeFlagsToManage(CATTopCGMAttributeLabel iCGMAttributeFlags)
{
   _CGMAttributeFlags = iCGMAttributeFlags;
   _ListOfCGMAttributeFlag.RemoveAll();
}

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetListOfCGMJounal(CATLISTP(CATCGMJournal)& iListOfCGMJournal)
{
   int Idx = 0; 
   int NbJournaux = _ListOfCGMJournal.Size();

   for (Idx=1;Idx<=NbJournaux;Idx++)
   {
      CATCGMJournal *pCurrJournal = _ListOfCGMJournal[Idx];
      if (pCurrJournal)
      {
#if  defined  (  CATIACGMV5R21  )
         pCurrJournal->Release();
#else
         pCurrJournal->DecCounter();
#endif
         pCurrJournal = NULL;
      }
   }
   _ListOfCGMJournal.RemoveAll(CATCollec::KeepAllocation);
   int NbNewJournaux = iListOfCGMJournal.Size();
   for (Idx=1;Idx<=NbJournaux;Idx++)
   {
      CATCGMJournal *pCurrJournal = iListOfCGMJournal[Idx];
      if (pCurrJournal)
      {
         _ListOfCGMJournal.Append(pCurrJournal);
#if  defined  (  CATIACGMV5R21  )
         pCurrJournal->AddRef();
#else
         pCurrJournal->IncCounter();
#endif
      }
   }
#endif
}

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetKeepCurrentCellTracker(CATBoolean iKeepCurrentCellTracker)
{
   _KeepCurrentCellTracker = (iKeepCurrentCellTracker && (_KeepCurrentCellTracker==0)) ? 1 : _KeepCurrentCellTracker;
}

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetCheckIfCellIsSmartInOutputBody(CATBody *iBody, CATBoolean iCheckIfCellIsSmartInOutputBody)
{
   if (iBody) 
   {
      _CheckIfCellIsSmartInOutputBody = iCheckIfCellIsSmartInOutputBody;
   }
}

//===========================================================================
//
//
//===========================================================================
INLINE CATBoolean CATTopCGMAttributePropagatorEngine::IsActive(CATGeoFactory *iInFactory, CATGeoFactory *iOutFactory) 
{
  //Define(iFactory);
   CATBoolean IsActive = FALSE;
   if (iOutFactory) 
   {
      IsActive =  CATTopHiddenSeamCellQuery::IsActive(iOutFactory)                     // Hidden Seam 
               || CATTopImprintAttributeServices::IsActive(iOutFactory)                // Imprint SWX : to be removed  
               || CATTopImprintCellServices::HasImprintAttribut(iOutFactory)
               || CATTopImprintCellServices::HasImprintAttribut(iInFactory);           // New Imprint : will replace SWX Imprint
   }
   return IsActive;
}

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::ForceTrackingOfCellInAllInputBodies(CATBoolean iOption)
{
   _ForceTrackingOfCellInAllInputBodies = iOption;
}

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetUseTassedJournalForCellTracker(CATBoolean iOption)
{
   _UseTassedJournalForCellTracker = iOption;
}

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetAmbiguityTrackingByGeometry(CATBoolean iOption)
{
   _AmbiguityTrackingByGeometry = iOption;
}




#ifdef CATIACGMR421CAA

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetFilterChildrenCellsForSeamCases(CATBoolean iOption)
{
   _FilterChildrenCellsForSeamCases = iOption;
}

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetCheckImprintOnVertex(CATBoolean iOption)
{
   _CheckImprintOnVertex = iOption;
}

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetPropagateImprintOnFaces(CATBoolean iOption)
{
   _PropagateImprintOnFaces = iOption;
}

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetCorrectImprintJournal(CATBoolean iOption)
{
   _CorrectImprintJournal = iOption;
}

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetInputBodiesInCopyMode(CATBoolean iOption)
{
   _IsInputBodiesInCopyMode = iOption;
}

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetActivateImprintJournaling(CATBoolean iOption)
{
   _ActivateImprintJournaling = iOption;
}
#endif

//===========================================================================
//
//
//===========================================================================
INLINE void CATTopCGMAttributePropagatorEngine::SetPropagateFromImprintedVtxToEdge(CATBoolean iOption)
{
   _PropagateFromImprintedVtxToEdge = iOption;
}



