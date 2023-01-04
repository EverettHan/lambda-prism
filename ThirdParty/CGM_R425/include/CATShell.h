#ifndef CATShell_H
#define CATShell_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATGMModelInterfaces.h"
#include "CATDomain.h"  
#include "ListPOfCATCell.h"
class CATBody;
class CATCGMJournalList;

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATShell ;
#else
extern "C" const IID IID_CATShell ;
#endif

/**
 * Interface representing a set of connected faces
 * of a body or a volume.
 *<br> A CATShell is created with the @href CATBody#CreateShell or @href CATBody#CreateDomain
 * methods and deleted with the 
 * @href CATICGMContainer#Remove method.
 */

class ExportedByCATGMModelInterfaces CATShell : public CATDomain
{
   CATDeclareInterface;
   public :

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/** 
 * Checks whether <tt>this</tt> shell is closed.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <tt>TRUE</tt> if <tt>this</tt> CATShell delimits an inside/outside partition of the 3D space,
 * <tt>FALSE</tt> otherwise.
 */
    virtual CATBoolean IsClosed() = 0;    

#ifdef CATIAR204_KO
/**
 * Replaces a CATCell by another in <tt>this</tt> CATDomain.
 * @param iCellToReplace
 * The pointer to the cell to replace.
 * @param iReplacementCell
 * The pointer to the replacement cell.
 * @param iOrientation
 * The replacement cell orientation, with regards to the domain orientation.
 */
    virtual void ReplaceCell(CATCell* iCellToReplace, CATCell* iReplacementCell, CATOrientation iReplacementOrientation=CATOrientationPositive)=0;

#endif
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * @nodoc
 * Do not use, See CATSmartDuplicator.
 */
   virtual CATShell* SmartDuplication(CATBody* iBody, CATLISTP(CATCell)& iCellsToDuplicate,CATCGMJournalList* iJournal=NULL, CATBody* iShellBody=NULL) = 0;
  /**
 * @nodoc
 * Do not use, See CATSmartDuplicator.
 */
	 virtual CATShell* EmptySmartDuplication(CATBody* iBody) = 0;
};

CATDeclareHandler(CATShell,CATDomain);

#endif
