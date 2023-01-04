#ifndef CATIPGMTopTrimMultiWiresByVertices_h_
#define CATIPGMTopTrimMultiWiresByVertices_h_

// COPYRIGHT DASSAULT SYSTEMES 2016

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATPieceToKeep.h"

#include "CATListOfCATCGMJournalList.h"

class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopTrimMultiWiresByVertices;

//
//************************************************************************************************
//
// To use the multi-trim operator you need call two times the run in general cases
//
// The first run gives all pieces for each Wire resulting of trim with all wires,  and with all wires laying on wires.
// Each piece has its own signature CATPiecetoKeep.
//
// The Second run aims to find the ending result. So you should set the signature of all parts to be kept as input
// the result is the joined pieces of all selected part from all wires.
//
//---------------------------
// You can call one time the run
// if the KEEPALL option is equal TRUE or if the signatures list (list of CATPiecetoKeep ) is done in input(can be used during update)
// ====
//*************************************************************************************************
////************************************************
//// example of M U L T I   T R I M call
////************************************************
//{
//  CATLISTP(CATLISTP(CATBody))  ResultBodiesToDelete;
//
//  CATTry
//  {
//    //************************************************
//    // Creation
//    //************************************************
//    CATIPGMTopTrimMultiWiresByVertices * MultiTrimOperator = CATPGMCreateTrimMultiWiresByVertices(Factory,TopData, SplittingBodiesList, WireBodiesList);
//
//
//    //------------------
//
//    if (NULL != MultiTrimOperator )
//    {     
//      
//        //************************************************
//        // Run to create the pieces and signatures CATPieceToKeep
//        //************************************************
//
//        MultiTrimOperator->Run();
//
//
//        CATLISTP(CATPieceToKeep)  MosaicToKeep;
//
//        int ib, WireBodiesListSize(WireBodiesList.Size());
//        for (ib = 1; ib <= WireBodiesListSize; ib++)
//        {
//          CATBody * bodycur = WireBodiesList[ib];
//
//          CATLISTP(CATBody) ResultBodies;
//          CATLISTP(CATPieceToKeep)  AllSignatures;
//          MultiTrimOperator->GetResultPiecesBodies(bodycur, ResultBodies, AllSignatures);
//
//          //*********************************************************************
//          // select the pert to be kept (code from caller according to his own criterias)
//          //*********************************************************************
//          if (AllSignatures.Size()>0)
//          {
//            CATPieceToKeep * mosakee = AllSignatures[i_choose];//I_choose : piece index to keep
//            MosaicToKeep.Append(mosakee);
//          }
//          //-------------------------
//          if (ResultBodies.Size()>0)
//            ResultBodiesToDelete.Append(ResultBodies);
//        }
//
//        //************************************************
//        // set the pieces to be kept (selected) thanks to signatures (CATPieceToKeep)
//        //************************************************
//        int NbMosaToKeep = MosaicToKeep.Size();
//        if (NbMosaToKeep>0)
//        {
//          MultiTrimOperator->SetPiecesToKeepInput(MosaicToKeep); // we need CATPieceToKeep for update
//        }
//
//
//      //************************************************
//      // Run with result body assembly
//      //************************************************
//      MultiTrimOperator->Run();
//
//      //************************************************
//      // Get the expected Result for user
//      //************************************************
//
//      Result = MultiTrimOperator->GetResult();
//    }
//  }
//  CATCatch(CATError,error)
//  {
//    if (MultiTrimOperator)
//    { if (MultiTrimOperator) { (MultiTrimOperator)->Release(); MultiTrimOperator = 0; } }
//    MultiTrimOperator=NULL;
//
//    StockErr = error;
//  }
//  CATEndTry;
//
//  //*******************
//  // clean memory
//  //*******************
//  // clean mosaic bodies
//  if (ResultBodiesToDelete.Size() >0)
//  {
//    int imos = 1;
//    for (imos = 1 ; imos<=ResultBodiesToDelete.Size(); imos++)
//    {
//      CATLISTP(CATBody) BodiesToDelete = ResultBodiesToDelete[imos];
//
//      if (BodiesToDelete.Size() >0)
//      {
//        for (im = 1 ; im<=BodiesToDelete.Size(); im++)
//        {
//          CATBody * bodyf = BodiesToDelete[im];
//          if (bodyf)
//            Factory->Remove(bodyf,CATICGMContainer::RemoveDependancies);
//        }
//      }
//
//      if (ResultBodiesToDelete[imos])
//        ResultBodiesToDelete[imos].RemoveAll();
//      ResultBodiesToDelete[imos] = NULL;
//
//    }
//   
//    ResultBodiesToDelete.RemoveAll();
//    ResultBodiesToDelete = NULL;
//
//  }
//
//
//
//  if (StockErr)
//    CATThrow(StockErr);
//  return Result;
//}
//
//// END example
////=================================
//
//typedef struct 
//{
//  int JShellBodyInitial;// ShellBodyInitial is a support of iShellbody
//  CATListOfInt  WireIndexIntial; // InitialWiresIndex bounded iShellbody in JShellBodyInitial
//  CATListOfInt  SideToKeep; //side to keep corresponding to  InitialWires in JShellBodyInitial (same index like ShellIndexIntersection)
//  CATListOfInt  ShellIndexIntersection;// beetwenJShellBodyInitial (J si la boundary du Shell initial borde iShellbody )
//  CATListOfInt  SideToKeepIntersection ;//side to keep corresponding to   IntersectionWires  JShellBodyInitial (same index like ShellIndexIntersection)
//    //(synchronise with ShellIndexIntersection)
//  int indexMultipleSolution;// -1 pas d'indexation necessaire sinon de 0 a .. n-1
//}
//CATPieceToKeep;
//
////class CATBody;
/**
 *<ul>
 * <li>Create it with the <tt>CATCreateTrimMultiWiresByVertices</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
 * <li>Run it
 * <li>Get the resulting GetResultBodies method. If you do not want 
 * to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the 
 * geometric factory, after the operator deletion.
 *<li>delete it after use  with the usual C++ <tt>delete</tt> operator.
 *</ul> 
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopTrimMultiWiresByVertices: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopTrimMultiWiresByVertices();

  /**
      * @nodoc
      */
  virtual void SetExtrapolMode(CATBoolean iExtrapol) = 0;

  /** @nodoc
      * Activates simplify mode: operator tries to simplify result.
      * <br> This option is not activated by default.
      * @param yes_or_no
      * <br><b>Legal values</b>:
      * <dl><dt><tt>0</tt><dd> No simplification of result.
      *     <dt><tt>1</tt><dd> Simplification of result.</dl>
      */
  virtual void SetSimplifyMode(int yes_or_no = 1) = 0;

  /**
      * @nodoc
      * The user choice the PieceBodies to keep
      */
  virtual void AddBodyToSplit(CATBody *iWireToSplit) = 0;

  /**
      * @nodoc
      * The user choice the MosaicPieces to keep for Update
      */
  virtual void SetPiecesToKeepInput(const CATLISTP(CATPieceToKeep) &iToKeep) = 0;

  /**
      * @nodoc
      * The user choice to manage all mosaic bodies  // default all mosaic bodies are deleted by operator
      */
  virtual void SetKeepMosaicBodies(CATBoolean iKeepMosaicBodies) = 0;

  /**
      * @nodoc
      * KeepAll mode: all the results of the trim are kept in the result.
      * <br> This option is not activated by default.
      * <br> If this option is set to <tt>TRUE</tt>, the call of <tt>SetPiecesToKeepInput</tt> will have no effect.
      * @param iKeepAll
      * <br><b>Legal values</b>:
      * <dl><dt><tt>FALSE</tt><dd> KeepAll mode is not active.
      *     <dt><tt>TRUE</tt><dd> KeepAll mode is active.</dl>
      */
  virtual void SetKeepAll(CATBoolean iKeepAll) = 0;

  /**
      * @nodoc
      */
  virtual CATBody *GetResult() = 0;

  /**
      * @nodoc
      */
  virtual void GetResultPiecesBodies(
    CATBody *iWireBodyInitial,
    CATLISTP(CATBody) &oResultBodies,
    CATLISTP(CATPieceToKeep) &oToKeep,
    CATLISTP( CATCGMJournalList) * oPiecesjournal = NULL) = 0;

  /**
      * @nodoc
      */
  virtual CATBoolean ResultIsConnex() = 0;

  /**
      * @nodoc
      */
  virtual CATBoolean ResultIsManifold() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopTrimMultiWiresByVertices(); // -> delete can't be called
};

/**
 * Creates a CATIPGMTopTrimMultiWiresByVertices operator.
 * @param iFactory
 * The pointer to the geometry factory. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iSplittingBodies
 * A list of bodies containing only one domain
 * 
 * @param iWireBodies
 * The Wire bodies to be split by iSplittingBodies. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopTrimMultiWiresByVertices *CATPGMCreateTrimMultiWiresByVertices(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLISTP(CATBody) &iSplittingBodies,
  CATLISTP(CATBody) &iWiresBodies);

#endif /* CATIPGMTopTrimMultiWiresByVertices_h_ */
