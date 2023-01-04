#ifndef CATCGMDuplicateLyingOn_H
#define CATCGMDuplicateLyingOn_H

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

/**
 * Defines the state of a lying on link when a cell is duplicated (used in CATICGMSmartDuplicator)
 * @param CatCGMLyingOnNoCopy
 * A duplicated cell contains no lying on link.
 * @param CatCGMLyingOnDuplicated
 * Lying on links are duplicated on a duplicated cell
 * @param CatCGMLyingOnTransfered
 * Lying on links are transfered from an original cell to the duplicated cell
 */
enum CATCGMDuplicateLyingOn { CatCGMLyingOnNoCopy     = +0 ,
                              CatCGMLyingOnDuplicated = +1 ,
                              CatCGMLyingOnTransfered = +2 };

#endif
