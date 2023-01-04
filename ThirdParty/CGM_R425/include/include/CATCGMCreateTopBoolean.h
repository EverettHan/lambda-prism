#ifndef CATCGMCreateTopBoolean_h_
#define CATCGMCreateTopBoolean_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
* @CAA2Level L1
* @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATHybDef.h"

class CATICGMHybSplit;
class CATGeoFactory;
class CATTopData;
class CATBody;
class CATICGMHybTrim;
class CATICGMHybDisconnect;


/**
* Constructs an operator that splits a CATShell domain by a CATShell or a CATWire domain.
* <br>The body to split and the cutting body must only contain 
* one shell domain and one (shell or wire) domain respectively.
* <br><b>Orientation</b>: The orientation of the resulting domain is the orientation
* of the domain to be split.
* <br><b>Journal</b>:
* <ul>
* <li>The faces that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The faces that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new edges are written as <tt>CATCGMJournal::Creation</tt>
* <li>The faces that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToCut
* A pointer to the body to cut. It must only contain one shell
* domain.
* @param iCuttingBody
* A pointer to the cutting body. It must only contain one (wire or shell)
* domain
* @param iSelectMode
* The selection of the resulting parts. Do not use BOTH_SIDES for a split operation.
* <ul>
* <li>Shell cut by a shell:
* <dl>
* <dt>POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE</dt>
* <dd>The partitions to keep are pointed to by the orientation of the splitting shell.</dd>
* <dt>NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE</dt>
* <dd>The partitions to remove are pointed to by the orientation of the splitting shell.</dd>
* <dt>BOTH_SIDES</dt>
* <dd>Do not use this value.</dd>
* </dl>
* </li>
* <li>Shell cut by a wire:
* <dl>
* <dt>POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE</dt>
* <dd>When standing along the shell orientation and watching in the direction of the wire
* leads to have the kept partitions to the left.</dd>
* <dt>NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE</dt>
* <dd>When standing along the shell orientation and watching in the direction of the wire
* leads to have the kept partitions to the right.</dd>
* <dt>BOTH_SIDES</dt>
* <dd>Do not use this value.</dd>
* </dl>
* </li>
* </ul>
* @param iExtrapolMode
* The extrapolation mode to specify when 
* the cutting body does not cut right along the body to cut.
* <ul>
* <li><tt>NO_EXTRAPOLATION</tt>: No extrapolation is performed. The operator cannot find a solution
* if the cutting body does not cut right along the body to cut.
* <li><tt>TANGENT_DIRECTION</tt>: If the cutting body does not cut right along the body to cut, the extrapolation is
* made tangentially to the scar at the last computed point.
* </ul>
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybSplit *CATCGMCreateTopSplitShell(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToCut,
	CATBody *iCuttingBody,
	CATHybSelectionMode iSelectMode = POSITIVE_POSITIVE_SIDE,
	CATHybExtrapolationMode iExtrapolMode = TANGENT_DIRECTION);

/**
* Constructs an operator that splits a CATShell domain by a CATShell or a CATWire domain.
* <br>The body to split and the cutting body must only contain 
* one shell domain and one (shell or wire) domain respectively.
* The cutting body does not have to be necessarily laid down on the support.
* The split operation completes as long as the distance to the support is smaller than the tolerance
* which is specified in the creation function. For example, if the maximum distance between the 
* wire and the support is 0.09, the split operation completes
* if the specified tolerance is greater than 0.09. 
* <br><b>Orientation</b>: The orientation of the resulting body is the orientation
* of the body to cut.
* <br><b>Journal</b>:
* <ul>
* <li>The faces that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The faces that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new edges are written as <tt>CATCGMJournal::Creation</tt>
* <li>The faces that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToCut
* A pointer to the body to cut. It must only contain one shell
* domain.
* @param iCuttingBody
* A pointer to the cutting body. It must only contain one (wire or shell)
* domain
* @param iSelectMode
* The selection of the resulting parts. Do not use BOTH_SIDES for a split operation.
* <ul>
* <li>Shell cut by a shell:
* <dl>
* <dt>POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE</dt>
* <dd>The partitions to keep are pointed to by the orientation of the splitting shell.</dd>
* <dt>NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE</dt>
* <dd>The partitions to remove are pointed to by the orientation of the splitting shell.</dd>
* <dt>BOTH_SIDES</dt>
* <dd>Do not use this value.</dd>
* </dl>
* </li>
* <li>Shell cut by a wire:
* <dl>
* <dt>POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE</dt>
* <dd>When standing along the shell orientation and watching in the direction of the wire
* leads to have the kept partitions to the left.</dd>
* <dt>NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE</dt>
* <dd>When standing along the shell orientation and watching in the direction of the wire
* leads to have the kept partitions to the right.</dd>
* <dt>BOTH_SIDES</dt>
* <dd>Do not use this value.</dd>
* </dl>
* </li>
* </ul>
* @param iExtrapolMode
* The extrapolation mode when the cutting body does not cut right along 
* the body to cut:
* <ul>
* <li><tt>NO_EXTRAPOLATION</tt>: No extrapolation is performed. The operator cannot find a solution
* if the cutting body does not cut right along the body to cut.
* <li><tt>TANGENT_DIRECTION</tt>: If the cutting body does not cut right along the body to cut, the extrapolation is
* made tangentially to the scar at the last computed point.
* </ul>
* @param iTol
* Defines the tolerance of the geometrically coincident elements. The split operation completes if 
* iTol is greater than the maximum distance between the cutting body and the support.
* The maximum value of iTol is 0.1 mm.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybSplit *CATCGMCreateTopSplitShell(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToCut,
	CATBody *iCuttingBody,
	CATHybSelectionMode iSelectMode,
	CATHybExtrapolationMode iExtrapolMode,
	double iTol);

/**
* Constructs an operator that splits a CATShell domain by a CATShell or a CATWire domain.
* <br>The body to split and the cutting body must only contain 
* one shell domain and one (shell or wire) domain respectively.
* The cutting body does not have to be necessarily laid down on the support.
* The split operation completes as long as the distance to the support is smaller than the tolerance
* which is specified in the creation function. For example, if the maximum distance between the 
* wire and the support is 0.09, the split operation completes
* if the specified tolerance is greater than 0.09. 
* <br><b>Orientation</b>: The orientation of the resulting body is the orientation
* of the body to cut.
* <br><b>Journal</b>:
* <ul>
* <li>The faces that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The faces that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new edges are written as <tt>CATCGMJournal::Creation</tt>
* <li>The faces that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToCut
* A pointer to the body to cut. It must only contain one shell
* domain.
* @param iCuttingBody
* A pointer to the cutting body. It must only contain one (wire or shell)
* domain
* @param iSelectMode
* The selection of the resulting parts. Do not use BOTH_SIDES for a split operation.
* <ul>
* <li>Shell cut by a shell:
* <dl>
* <dt>POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE</dt>
* <dd>The partitions to keep are pointed to by the orientation of the splitting shell.</dd>
* <dt>NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE</dt>
* <dd>The partitions to remove are pointed to by the orientation of the splitting shell.</dd>
* <dt>BOTH_SIDES</dt>
* <dd>Do not use this value.</dd>
* </dl>
* </li>
* <li>Shell cut by a wire:
* <dl>
* <dt>POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE</dt>
* <dd>When standing along the shell orientation and watching in the direction of the wire
* leads to have the kept partitions to the left.</dd>
* <dt>NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE</dt>
* <dd>When standing along the shell orientation and watching in the direction of the wire
* leads to have the kept partitions to the right.</dd>
* <dt>BOTH_SIDES</dt>
* <dd>Do not use this value.</dd>
* </dl>
* </li>
* </ul>
* @param iExtrapolMode
* The way of extrapolation if the cutting body does not cut right 
* along the body to cut.
* <ul>
* <li><tt>NO_EXTRAPOLATION</tt>: No extrapolation is performed. The operator cannot find a solution
* if the cutting body does not cut right along the body to cut.
* <li><tt>TANGENT_DIRECTION</tt>: If the cutting body does not cut right along the body to cut, the extrapolation is
* made tangentially to the scar at the last computed point.
* </ul>
* @param iTol
* Defines the tolerance of the geometrically coincident elements. The split operation completes if 
* iTol is greater than the maximum distance between the cutting body and the support.
* The maximum value of iTol is 0.1 mm.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybSplit *CATCGMCreateTopNewSplitShell(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToCut,
  CATBody *iCuttingBody,
  CATHybSelectionMode iSelectMode,
  CATHybExtrapolationMode iExtrapolMode,
  double iTol);

/**
* Constructs an operator that trims two CATShell domains.
* <br>Each body is split by the other one. Each body must only contain 
* one domain.
* <br><b>Orientation</b>: The orientation of the resulting body is the orientation
* of the first body.
* <br><b>Journal</b>:
* <ul>
* <li>The faces that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The faces that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new edges are written as <tt>CATCGMJournal::Creation</tt>
* <li>The faces that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToTrim
* A pointer to the first body to cut. It must contain only one shell domain.
* @param iTrimmingBody
* A pointer to the second body. It must contain only one shell domain.
* @param iSelectMode
* The selection of the resulting parts.
* @param iExtrapolMode
* The way of extrapolation if the cutting body does not cut right along the body to cut 
* or vice versa.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybTrim *CATCGMCreateTopTrimShell(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToTrim,
	CATBody *iTrimmingBody,
	CATHybSelectionMode iSelectMode = POSITIVE_POSITIVE_SIDE,
	CATHybExtrapolationMode iExtrapolMode = TANGENT_DIRECTION);

/**
* Constructs an operator that splits a CATWire domain by a CATShell,a CATWire or a
* CATVertexInVolume domain.
* <br>The body to split and the cutting body must only contain 
* one shell domain and one (shell, wire or vertexInVolume) domain respectively.
* <br><b>Orientation</b>: The orientation of the resulting body is the orientation
* of the body to cut.
* <br><b>Journal</b>:
* <ul>
* <li>The edges that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The edges that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new vertices are written as <tt>CATCGMJournal::Creation</tt>
* <li>The edges that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToCut
* A pointer to the body to cut. It must only contain one wire
* domain.
* @param iCuttingBody
* A pointer to the cutting body. It must only contain one (wire, shell or vertexInVolume)
* domain.
* @param iSelectMode
* Identifies which partitions of the split body are kept.
* <ul>
* <li>Wire cut by a shell:
* <dl>
* <dt>POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE</dt>
* <dd>The partitions to keep are pointed to by the shell orientation.</dd>
* <dt>NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE</dt>
* <dd>The partitions to remove are pointed to by the shell orientation.</dd>
* </dl>
* </li>
* <li>Wire cut by a wire. The split partitions are alternately assigned NEGATIVE and POSITIVE values,
* the first partition being NEGATIVE when moving along the wire direction 
* (going from the start vertex to the end vertex). The result is independent on
* the cutting wire orientation:
* <dl>
* <dt>POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE</dt>
* <dd>The POSITIVE partitions are kept.</dd>
* <dt>NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE</dt>
* <dd>The POSITIVE partitions are removed.</dd>
* </dl>
* </li>
* <li>Wire cut by a Vertex. The wire is split into two partitions. The NEGATIVE part is the first one in the wire 
* when moving along the wire direction (going from the start vertex to the end vertex).
* <dl>
* <dt>POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE</dt>
* <dd>The POSITIVE partitions are kept.</dd>
* <dt>NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE</dt>
* <dd>The POSITIVE partitions are removed.</dd>
* </dl>
* </li>
* </ul>
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybSplit *CATCGMCreateTopSplitWire(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToCut,
	CATBody *iCuttingBody,
	CATHybSelectionMode iSelectMode = POSITIVE_POSITIVE_SIDE);

/**
* Constructs an operator that splits a CATWire domain by a CATShell,a CATWire or a
* CATVertexInVolume domain.
* <br>The body to split and the cutting body must only contain 
* one shell domain and one (shell, wire or vertexInVolume) domain respectively.
* <br><b>Orientation</b>: The orientation of the resulting body is the orientation
* of the body to cut.
* <br><b>Journal</b>:
* <ul>
* <li>The edges that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The edges that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new vertices are written as <tt>CATCGMJournal::Creation</tt>
* <li>The edges that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToCut
* A pointer to the body to cut. It must only contain one wire
* domain.
* @param iCuttingBody
* A pointer to the cutting body. It must only contain one (wire, shell or vertexInVolume)
* domain.
* @param iSelectMode
* Identifies which partitions of the split body are kept.
* <ul>
* <li>Wire cut by a shell:
* <dl>
* <dt>POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE</dt>
* <dd>The partitions to keep are pointed to by the shell orientation.</dd>
* <dt>NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE</dt>
* <dd>The partitions to remove are pointed to by the shell orientation.</dd>
* </dl>
* </li>
* <li>Wire cut by a wire. The split partitions are alternately assigned NEGATIVE and POSITIVE values,
* the first partition being NEGATIVE when moving along the wire direction 
* (going from the start vertex to the end vertex). The result is independent on
* the cutting wire orientation:
* <dl>
* <dt>POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE</dt>
* <dd>The POSITIVE partitions are kept.</dd>
* <dt>NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE</dt>
* <dd>The POSITIVE partitions are removed.</dd>
* </dl>
* </li>
* <li>Wire cut by a Vertex. The wire is split into two partitions. The NEGATIVE part is the first one in the wire 
* when moving along the wire direction (going from the start vertex to the end vertex).
* <dl>
* <dt>POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE</dt>
* <dd>The POSITIVE partitions are kept.</dd>
* <dt>NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE</dt>
* <dd>The POSITIVE partitions are removed.</dd>
* </dl>
* </li>
* </ul>
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybSplit *CATCGMCreateTopNewSplitWire(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToCut,
  CATBody *iCuttingBody,
  CATHybSelectionMode iSelectMode = POSITIVE_POSITIVE_SIDE);

/**
* Constructs an operator that trims two CATWire domains.
* <br>Each body is split by the other one. Each body must only contain 
* one domain.
* <br><b>Orientation</b>: The orientation of the resulting body is the orientation
* of the first body.
* <br><b>Journal</b>:
* <ul>
* <li>The edges that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The edges that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new vertices are written as <tt>CATCGMJournal::Creation</tt>
* <li>The edges that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToTrim
* A pointer to the first body to cut.It must only contain one wire.
* @param iTrimmingBody
* A pointer to the second body. It must only contain one (wire, shell or vertexInVolume).
* @param iSelectMode
* The selection of the resulting parts: 
* <ul>
* <li><tt>BOTH_SIDES</tt>: Keeps all the domains
* <li><tt>POSITIVE_POSITIVE_SIDE</tt>: Keeps the domains that are to the right of the cut body and the cutting body. 
* <li><tt>NEGATIVE_POSITIVE_SIDE</tt>: Keeps the domains that are to the left of the cut body and to the right 
* of the cutting body. 
* <li><tt>POSITIVE_NEGATIVE_SIDE</tt>: Keeps the domains that are to the right of the cut body and to the left 
* of the cutting body. 
* <li><tt>NEGATIVE_NEGATIVE_SIDE</tt>: Keeps the domains that are to the left of the cut body and to the left 
* of the cutting body.
* </ul>
* <ul>
* <li>The right of a shell cut by another shell is the part of the cut shell that is
* pointed out by the orientation of the cutting shell.
* The left side is the other one.
* <li>The right of a shell cut by a wire is the part of the cut shell such that the 
* orientation of the shell, the orientation of the wire and the direction on the selected
* part is direct. 
* <li>The right of a wire cut by a shell, a wire or a vertex is the part of the wire 
* that is pointed out by the
* orientation of the wire.
* </ul>
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybTrim *CATCGMCreateTopTrimWire(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToTrim,
	CATBody *iTrimmingBody,
	CATHybSelectionMode iSelectMode = POSITIVE_POSITIVE_SIDE);

/**
* Constructs an operator that disconnects a CATWire.
* <br>Each body is split by the other one. Each body must only contain 
* one domain.
* <br><b>Orientation</b>: The orientation of the resulting body is the orientation
* of the first body.
* <br><b>Journal</b>:
* <ul>
* <li>The edges that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The edges that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new vertices are written as <tt>CATCGMJournal::Creation</tt>
* <li>The edges that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToDisconnect
* A pointer to the wire to be disconnected.
* @param iDisconnectingBody
* A pointer to the disconnecting body.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybDisconnect *CATCGMCreateTopDisconnectWire(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToDisconnect,
	CATBody *iDisconnectingBody);

/**
* Constructs an operator that disconnects a CATShell.
* <br>Each body is split by the other one. Each body must only contain 
* one domain.
* <br><b>Orientation</b>: The orientation of the resulting body is the orientation
* of the first body.
* <br><b>Journal</b>:
* <ul>
* <li>The edges that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The edges that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new vertices are written as <tt>CATCGMJournal::Creation</tt>
* <li>The edges that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToDisconnect
* A pointer to the shell to be disconnected.
* @param iDisconnectingBody
* A pointer to the disconnecting body.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybDisconnect *CATCGMCreateTopDisconnectShell(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToDisconnect,
	CATBody *iDisconnectingBody);

/**
* Constructs an operator that splits a CATShell domain by a CATShell or a CATWire domain.
* <br>The body to split and the cutting body must only contain 
* one shell domain and one (shell or wire) domain respectively.
* <br><b>Orientation</b>: The orientation of the resulting body is the orientation
* of the body to cut.
* <br><b>Journal</b>:
* <ul>
* <li>The faces that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The faces that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new edges are written as <tt>CATCGMJournal::Creation</tt>
* <li>The faces that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToCut
* A pointer to the body to cut. It must only contain one shell
* domain.
* @param iCuttingBody
* A pointer to the cutting body. It must only contain one (wire or shell)
* domain
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybSplit *CATCGMCreateTopSplitShellWithKeepRemove(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToCut,
	CATBody *iCuttingBody);

/**
* Constructs an operator that splits a CATShell domain by a CATShell or a CATWire domain.
* <br>The body to split and the cutting body must only contain 
* one shell domain and one (shell or wire) domain respectively.
* <br><b>Orientation</b>: The orientation of the resulting body is the orientation
* of the body to cut.
* <br><b>Journal</b>:
* <ul>
* <li>The faces that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The faces that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new edges are written as <tt>CATCGMJournal::Creation</tt>
* <li>The faces that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToCut
* A pointer to the body to cut. It must only contain one shell
* domain.
* @param iCuttingBody
* A pointer to the cutting body. It must only contain one (wire or shell)
* domain
* @param iExtrapolMode
* The extrapolation mode when the cutting body does not cut right along the body to cut, or
* vice versa in case of a trim operation: 
* <ul>
* <li><tt>NO_EXTRAPOLATION</tt>: No extrapolation is performed. The operator cannot find a solution
* if the cutting body does not cut right along the body to cut.
* <li><tt>TANGENT_DIRECTION</tt>: If the cutting body does not cut right along the body to cut, the extrapolation is
* made tangentially to the scar at the last computed point.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybSplit *CATCGMCreateTopSplitShellWithKeepRemove(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToCut,
	CATBody *iCuttingBody,
	CATHybExtrapolationMode iExtrapolMode);

/**
* Constructs an operator that splits a CATShell domain by a CATShell or a CATWire domain.
* <br>The body to split and the cutting body must only contain 
* one shell domain and one (shell or wire) domain respectively.
* <br><b>Orientation</b>: The orientation of the resulting body is the orientation
* of the body to cut.
* <br><b>Journal</b>:
* <ul>
* <li>The faces that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The faces that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new edges are written as <tt>CATCGMJournal::Creation</tt>
* <li>The faces that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToCut
* A pointer to the body to cut. It must only contain one shell
* domain.
* @param iCuttingBody
* A pointer to the cutting body. It must only contain one (wire or shell)
* domain
* @param iExtrapolMode
* The extrapolation mode when the cutting body does not cut right along the body to cut, or
* vice versa in case of a trim operation:
* <ul>
* <li><tt>NO_EXTRAPOLATION</tt>: No extrapolation is performed. The operator cannot find a solution
* if the cutting body does not cut right along the body to cut.
* <li><tt>TANGENT_DIRECTION</tt>: If the cutting body does not cut right along the body to cut, the extrapolation is
* made tangentially to the scar at the last computed point.
* </ul>
* @param iTol
* Defines the tolerance of the geometrically coincident elements to be taken 
* into acccount by <tt>this</tt> operator during the LayDown process.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybSplit *CATCGMCreateTopSplitShellWithKeepRemove(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToCut,
	CATBody *iCuttingBody,
	CATHybExtrapolationMode iExtrapolMode,
	double iTol);

/**
* Constructs an operator that trims two CATShell domains.
* <br>Each body is split by the other one. Each body must only contain 
* one domain.
* <br><b>Orientation</b>: The orientation of the resulting body is the orientation
* of the first body.
* <br><b>Journal</b>:
* <ul>
* <li>The faces that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The faces that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new edges are written as <tt>CATCGMJournal::Creation</tt>
* <li>The faces that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToTrim
* A pointer to the first body to cut. It must contain only one shell domain.
* @param iTrimmingBody
* A pointer to the second body. It must contain only one shell domain.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybTrim *CATCGMCreateTopTrimShellWithKeepRemove(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToTrim,
	CATBody *iTrimmingBody);

/**
* Constructs an operator that trims two CATShell domains.
* <br>Each body is split by the other one. Each body must only contain 
* one domain.
* <br><b>Orientation</b>: The orientation of the resulting body is the orientation
* of the first body.
* <br><b>Journal</b>:
* <ul>
* <li>The faces that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The faces that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new edges are written as <tt>CATCGMJournal::Creation</tt>
* <li>The faces that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToTrim
* A pointer to the first body to cut. It must contain only one shell domain.
* @param iTrimmingBody
* A pointer to the second body. It must contain only one shell domain.
* @param iExtrapolMode
* The extrapolation mode when the cutting body does not cut right along the body to cut, or
* vice versa in case of a trim operation:
* <ul>
* <li><tt>NO_EXTRAPOLATION</tt>: No extrapolation is performed. The operator cannot find a solution
* if the cutting body does not cut right along the body to cut.
* <li><tt>TANGENT_DIRECTION</tt>: If the cutting body does not cut right along the body to cut, the extrapolation is
* made tangentially to the scar at the last computed point.
* </ul>
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybTrim *CATCGMCreateTopTrimShellWithKeepRemove(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToTrim,
	CATBody *iTrimmingBody,
	CATHybExtrapolationMode iExtrapolMode);

/**
* Constructs an operator that splits a CATWire domain by a CATShell,a CATWire or a
* CATVertexInVolume domain.
* <br>The body to split and the cutting body must only contain 
* one shell domain and one (shell, wire or vertexInVolume) domain respectively.
* <br><b>Orientation</b>: The orientation of the resulting body is the orientation
* of the body to cut.
* <br><b>Journal</b>:
* <ul>
* <li>The edges that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The edges that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new vertices are written as <tt>CATCGMJournal::Creation</tt>
* <li>The edges that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToCut
* A pointer to the body to cut. It must only contain one wire
* domain.
* @param iCuttingBody
* A pointer to the cutting body. It must only contain one (wire, shell or vertexInVolume)
* domain
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybSplit *CATCGMCreateTopSplitWireWithKeepRemove(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToCut,
	CATBody *iCuttingBody);

/**
* Constructs an operator that trims two CATWire domains.
* <br>Each body is split by the other one. Each body must only contain 
* one domain.
* <br><b>Orientation</b>: The orientation of the resulting body is the orientation
* of the first body.
* <br><b>Journal</b>:
* <ul>
* <li>The edges that are kept and not cut are written as <tt>CATCGMJournal::Keep</tt>
* <li>The edges that are cut are written as <tt>CATCGMJournal::Subdivision</tt> 
* <li>The new vertices are written as <tt>CATCGMJournal::Creation</tt>
* <li>The edges that are neither cut, nor kept, are written as <tt>CATCGMJournal::Deletion</tt>
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyToTrim
* A pointer to the first body to cut.
* @param iTrimmingBody
* A pointer to the second body.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method afer use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMHybTrim *CATCGMCreateTopTrimWireWithKeepRemove(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToTrim,
	CATBody *iTrimmingBody);

#endif /* CATCGMCreateTopBoolean_h_ */
