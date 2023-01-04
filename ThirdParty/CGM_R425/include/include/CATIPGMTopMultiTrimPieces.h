#ifndef CATIPGMTopMultiTrimPieces_h_
#define CATIPGMTopMultiTrimPieces_h_

// COPYRIGHT DASSAULT SYSTEMES 2013

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATGeoFactory;
class CATTopData;
class CATLISTP(CATPieceToKeep);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopMultiTrimPieces;

//
//typedef struct 
//{
//  int JShellBodyInitial;// PieceBodyInitial is a support of iPiecebody
//  CATListOfInt  WireIndexIntial; // InitialSplittingbodyIndex bounded iPiecebody in JPieceBodyInitial
//  CATListOfInt  SideToKeep; //side to keep corresponding to  InitialSplittingbodies in JPieceBodyInitial (same index like PieceIndexIntersection)
//  CATListOfInt  ShellIndexIntersection;// beetwenJPieceBodyInitial (J si la boundary du Piece initial borde iShellbody )
//  CATListOfInt  SideToKeepIntersection ;//side to keep corresponding to   IntersectionSplittingbodies  JPieceBodyInitial (same index like PieceIndexIntersection)
//    //(synchronise with ShellIndexIntersection)
//  int indexMultipleSolution;// -1 pas d'indexation necessaire sinon de 0 a .. n-1
//}
//CATPieceToKeep;
//
////class CATBody;
/**
 *<ul>
 * <li>Create it with the <tt>CATCreateTrimMultiShellByWires</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
 * <li>Run it
 * <li>Get the resulting GetResultBodies method. If you do not want 
 * to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the 
 * geometric factory, after the operator deletion.
 *<li>delete it after use  with the usual C++ <tt>delete</tt> operator.
 *</ul> 
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopMultiTrimPieces: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopMultiTrimPieces();

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
      * The user choice the Pieces (Bodies) to keep
      */
  virtual void AddBodyToSplit(CATBody *iBodyToSplit) = 0;

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
      * <br> If this option is set to <tt>TRUE</tt>, the call of <tt>SetShellsToKeepInput</tt> will have no effect.
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
    CATBody *iPieceBodyInitial,
    CATLISTP(CATBody) &oResultBodies,
    CATLISTP(CATPieceToKeep) &oToKeep) = 0;

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
  virtual ~CATIPGMTopMultiTrimPieces(); // -> delete can't be called
};

/**
 * Creates a CATIPGMTopMultiTrimPieces operator.
 * @param iFactory
 * The pointer to the geometry factory. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iSplittingBodies
 * A list of bodies containing only one SplittingBody (a  mono-domain body)
 * each SplittingBody has only one PieceSupport.
 * @param iPieceBodies
 * The Piece-bodies to be split mutually  or split by iSplittingBodies liying on. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopMultiTrimPieces *CATPGMCreateMultiTrimPieces(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLISTP(CATBody) &iSplittingBodies,
  CATLISTP(CATBody) &iPieceBodies);

#endif /* CATIPGMTopMultiTrimPieces_h_ */
