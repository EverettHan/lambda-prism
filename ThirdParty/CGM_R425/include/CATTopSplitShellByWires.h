#ifndef __CATTopSplitShellByWires_h__
#define __CATTopSplitShellByWires_h__

// COPYRIGHT DASSAULT SYSTEMES  2006

#include "ExportedByCATTopologicalObjects.h"
#include "CATCreateSplitShellByWires.h"
#include "CATTopOperator.h"
#include "CATExtrapolFunction.h"

#include "ListPOfCATEdge.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATWire.h"
#include "ListPOfListPOfCATEdge.h"

class CATBody;
class CATWire;
class CATIPGMExtrapolTool;
class CATShell;
class CATListPtrCATShell;
class CATEdge;
class CATSoftwareConfiguration;
//class ListPOfListPOfCATEdge;

/**
 * Interface defining an operator to split a skin by a set of wires specified as 1D bodies. 
 * The result is a set of bodies. For each body resulting from the split operation, the operator provides 
 * you with a way to scan to boundaries. For each input wire, the operator provides you with a way to determine
 * what are the ajacent resulting bodies as well as the edges making up these bodies.
 * To use this operator:
 *<ul>
 * <li>Create it with the <tt>CATCreateSplitShellByWires</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
 * <li>Run it
 * <li>Get the resulting GetResultBodies method. If you do not want 
 * to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the 
 * geometric factory, after the operator deletion.
 *<li>delete it after use  with the usual C++ <tt>delete</tt> operator.
 *</ul> 
 */

class ExportedByCATTopologicalObjects CATTopSplitShellByWires: public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopSplitShellByWires);
   protected:

   /**
   * @nodoc
   * Constructor - not to be used.
   */
      CATTopSplitShellByWires(CATGeoFactory * iFactory, CATTopData * iTopData);      

   public:
      /**
      * @nodoc
      * Destructor.
      */
      virtual ~CATTopSplitShellByWires();
      /**
      * Runs the operator.
      */
      virtual int  Run() = 0;
      /**
      * @nodoc @nocgmitf
      */
      void Dump(CATCGMOutput & iOutStream) = 0;

      /**
      * @nodoc
      */
      virtual void SetExtrapolTool(CATExtrapolTool * iExtrap) = 0;
      /**
      * @nodoc
      * @nocgmitf
      */
      virtual void SetExtrapolTool(CATIPGMExtrapolTool * iIExtrap) = 0;

      /**
      * @nodoc
      * Restricted use: reserved to CGMReplay
      */
      virtual CATBody* GetResult() = 0; 

      /**
      * @nodoc
      * Returns the list of skin bodies resulting from the split operation.
      * @param ioResultBodies
      * The list of bodies.
      */
      virtual void     GetResultBodies(CATLISTP(CATBody) & ioResultBodies,CATLISTP(ListPOfCATEdge) * EdgesNonDiconectintgResultBodies = NULL) = 0;

      /**
      * @nodoc
      * For each resulting body, retrieves:
      * <ul>
      * <li>the number of edges bounding the iBody body on a given wire  
      * <li>the list of edges bounding the iBody body on a given wire.
      * </ul>
      * iInitialWires, ioNbEdgesPerWire and ioBoundaries have the same number of elements.
      * If the iBody body is generated from the cut of the skin by two wires specified through the iInitialWires list,  
      * ioBoundaries is an array of two objects. Each object being itself an array of edges. 
      * This array of edges is made up of the edges which bound iBody on the corresponding wire. ioNbEdgesPerWire is an array of two items. 
      * Each object is the number of edges bounding iBody along the corresponding wire.
      * @param iBody
      * The body to be analyzed.
      * @param iInitialWires
      * The list of input wires.
      * @param ioNbEdgesPerWire
      * The array of array of number of edges.
      * @param ioBoundaries
      * The array of array of edges bounding iBody on the corresponding wire.
      */
      virtual void GetBoundaryComposition(CATBody * iBody, CATLISTP(CATWire) & iInitialWires, 
                                          int ** ioNbEdgesPerWire, CATEdge **** ioBoundaries) = 0;

      /**
      * @nodoc
      * For each cutting wire, retrieves:
      * <ul>
      * <li>the number of bodies bounded by iWire
      * <li>for each bounded body, the list of edges bounding the body along iWire.
      * <li>for each bounded body, the number of edges bounding it along iWire.
      * </ul>
      * ioBoundedBodies, ioNbEdgesPerBody and ioBoundaries have the same number of items.
      * If the iWire wire cuts the skin so that it generates two bodies (one from either side of the wire for example),
      * the ioBoundedBodies will contain two items. The array ioBoundaries will contain two items, 
      * each item of this array is itself an array of edges containing the set of edges bounding a body along the input wire.
      * @param iWire
      * The input wire.
      * @param ioBoundedBodies
      * The list of bodies bounded by iWire.
      * @param ioNbEdgesPerBody
      * The array of array of number of edges bounding a body along the input wire.
      * @param ioBoundaries
      * The array of array of edges bounding iBody on the corresponding wire.
      */
      virtual void IsBoundaryOf(CATWire * iWire, CATLISTP(CATBody) & ioBoundedBodies, int ** ioNbEdgesPerBody, CATEdge **** ioBoundaries) = 0;
  
      /**
      * @nodoc
      * Determines the list of bodies bounded by all the cutting wires. 
      * @param ioBoundedBodies
      * The output list of bodies.
      * @param iInitialBoundaryAuthorised
      * A parameter to restrict the number of output bodies.
      * <dl>
      * <dt>TRUE<dl>the output list contains the bodies which share a border with the skin to be split
      * <dt>FALSE<dl>the output list contains only the bodies which do not share a border with the skin to be split
      */
      virtual void GetBodiesBoundedByAllWires(CATLISTP(CATBody) & ioBoundedBodies, CATBoolean iInitialBoundaryAuthorised = FALSE) = 0;

      /**
      * @nodoc
      * Call SetComputeOrientations(TRUE) before run to be able to call
      * GetBoundaryComposition(CATShell*,CATLISTP(CATBody)&,CATListOfInt&,CATBoolean&,int&)
      * and
      * IsBoundaryOf(CATBody*,int,CATLISTP(CATShell)&)
      * later. Without calling SetComputeOrientations(TRUE), those methods will throw an error.
      */
      virtual void SetComputeOrientations(CATBoolean iCompute) = 0;

      /**
      * @nodoc
      * This method decides if extrapolations should continue until the shell border, or if they have
      * to stop as soon as they intersect each other.
      * Use TRUE (option by default) to stop extrapolations at first intersection.
      * Use FALSE to make all extrapolations reach the shell border.
      */
      virtual void SetStopExtrapolationsAtFirstIntersection(CATBoolean iStopExtrapolationsAtFirstIntersection) = 0;

      /**
      * @nodoc
      * This method is to be used only in cases with:
      * - an input shell with only 1 border
      * - input wires that are all closed
      * Information about the inclusion between resulting shells and input wires will be computed.
      */
      virtual void SetComputeShellWireInclusion(CATBoolean iComputeShellWireInclusion) = 0;

      /**
      * @nodoc
      * This method is to be used after Run, only if SetComputeShellWireInclusion(TRUE) was called before Run.
      * ioWirePositionsInInputList will contain the positions, in input splitting bodies list, of all bodies
      * surrounding the shell of iOneResultBody.
      */
      virtual void RetrieveShellWireInclusion(CATBody * iOneResultBody,  CATListOfInt & ioWirePositionsInInputList) = 0;

      /**
      * @nodoc
      * For output shell iShell, get initial bounding wires and relative orientations.
      * @param oInitialWireBodies
      * The bounding wires.
      * @param oSidesList
      * Relative orientations towards bounding wires. 
      * @param oIsInBorder
      * TRUE is iShell contains initial border. 
      * @param oOutputIndex
      * -1 if there is no other output shell having same oSidesList and oIsInBorder.
      * 1...N in other case, following a deterministic sorting algorithm
      */
      virtual void GetBoundaryComposition(CATShell * iShell,
                                          CATLISTP(CATBody) & oInitialWireBodies,
                                          CATListOfInt & oSidesList,
                                          CATBoolean & oIsInBorder,
                                          int & oOutputIndex) = 0;

      /**
      * @nodoc
      * For result body iBodyResult, fill ioJournal with appropriate orders.
      * The input skin body and all splitting wire bodies are in "copy" mode.
      * @param iBodyResult
      * One of the output shell bodies.
      * @param ioJournal
      * The journal to be filled. It must be empty.
      */
      virtual void GetJournalForOneBody(CATBody * iBodyResult, CATCGMJournalList & ioJournal) = 0;

      /**
      * @nodoc
      * For input wire body and orientation, gets all output shells associated.
      * @param iInitialWireBody
      * The input wire.
      * @param iSide
      * The input orientation.
      * @param ioBoundedShells
      * List containing associated output shells.
      */
      virtual void IsBoundaryOf(CATBody * iInitialWireBody, int iSide, CATLISTP(CATShell) & ioBoundedShells) = 0;

      /**
      * @nodoc
      * Tells the operator that some input wires must be considered as coming from an extrapolation.
      * @param iWireBeforeExtrapolation
      * One input wire.
      * @param iWireAfterExtrapolationDirectionStart
      * An input wire coming from the extrapolation of iWireBeforeExtrapolation towards its start.
      * @param iWireAfterExtrapolationDirectionEnd
      * An input wire coming from the extrapolation of iWireBeforeExtrapolation towards its end.
      */
      virtual void SetWiresAlreadyExtrapolated(CATWire * iWireBeforeExtrapolation,
                                               CATWire * iWireAfterExtrapolationDirectionStart,
                                               CATWire * iWireAfterExtrapolationDirectionEnd) = 0;

      /* @nodoc */
      virtual void DumpOrientationTable(CATCGMOutput & oOutput) = 0;

      /* @nodoc */
      virtual void SetForceCode(CATLONG32 iForceCode) = 0;

      /* @nodoc */
      virtual void DuplicateRunJournal(CATCGMJournalList & ioJournal) = 0;

      /** @nodoc @nocgmitf */
      static CATError * CheckSplittingBodies(CATLISTP(CATBody) & iSplittingBodies, CATSoftwareConfiguration * iConfig);

      /** @nodoc @nocgmit */
      virtual void SetVerifyWiresAreCompletelySplitting(CATBoolean iCheck) = 0; //U29

      // On arrete l'extrapolation au bord de la Face
      // possible (1 pour oui, 0 pour non).
      /** @nodoc @nocgmit */
      virtual void SetPartialExtrapol(short iOnOff) = 0;


};

#endif
