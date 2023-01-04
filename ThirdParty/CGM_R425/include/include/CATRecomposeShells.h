#ifndef __CATRecomposeShells_h__
#define __CATRecomposeShells_h__

// COPYRIGHT DASSAULT SYSTEMES  2003

/**
* @level Protected
* @usage U1
*/

#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"

#include "ListPOfCATShell.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATCell.h"

class CATCXRecomposeShells;
class CATShell;

/**  
* Class defining an operator that recomposes a multi-lump body from a list of 
* shells to be removed or a list of shells to be kept.
*/
class ExportedByCATTopologicalObjects CATRecomposeShells: public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATRecomposeShells);
public: 
    /**
    * @nodoc
    */
   CATRecomposeShells(CATGeoFactory * iFactory,
        CATTopData    * iData,
        CATBody       * iBodyToRecompose);
    
    /**
    * Destructor
    */
    virtual ~CATRecomposeShells();
    
    /**
    * Specifies the list of shells to be kept.
    */
    void SetShellsToKeep(CATLISTP(CATShell)& iShellsToKeep);
    /**
    * Specifies the list of shells to be removed.
    */
    void SetShellsToRemove(CATLISTP(CATShell)& iShellsToRemove);
    /**
    * Specifies the list of faces to be kept.
    */
    void SetShellsToKeep(CATLISTP(CATFace)& iShellsToKeep);
    /**
    * Specifies the list of faces to be removed.
    */
    void SetShellsToRemove(CATLISTP(CATFace)& iShellsToRemove);

    /**
    * Specifies the list of cells to be kept.
    */
    void SetCellsToKeep(CATLISTP(CATCell)& iCellsToKeep);
    /**
    * Specifies the list of cells to be removed.
    */
    void SetCellsToRemove(CATLISTP(CATCell)& iCellsToRemove);

    /**
    * Removes all the internal shells.
    */
    void RemoveInternalShells();
    
    /**
    * When the specification of the shells leads to a matter conflict, 
    * no result is generated and GetResult returns a NULL pointer. 
    * In this case, you can use GetConflictingShells to determine which 
    * shells are conflicting.
    * @param oIncludingShell
    * The including shell: can be either an external shell from 
    * the initial body or an internal shell removed from the initial body.
    * @param oIncludedShell
    * The included shell: external shell from the initial body and included 
    * the initial body or an internal shell removed from the initial body.
    * and included in oIncludingShell
    * @return
    * 0 (no conflict) - 1 (conflict has been detected).
    */
    int  GetConflictingShells(CATShell *& oIncludingShell, CATShell *& oIncludedShell) const;
    
    /**
    * Runs the operator.
    */ 
    virtual int Run();     
    
    /**
    * Retrieves the resulting body.
    */
    virtual CATBody * GetResult();
    
    /**
    * @nodoc @nocgmitf
    */
    virtual void Dump(ostream& iOutput) const;

#if  defined  (  CATIACGMV5R21  )
	//KY1 : 10-12-2010
//public:
//	/**	@nodoc @nocgmitf */ 
//	static const  CATString  *GetDefaultOperatorId();
#endif

#if  defined  (  CATIACGMV5R21  )
	//KY1 : 10-12-2010
	/**	@nodoc @nocgmitf */
	//int RunOperator();
protected:
	///**	@nodoc @nocgmitf */
	//static  CATString  _OperatorId;
	///**	@nodoc @nocgmitf */
	//const  CATString  *GetOperatorId();
	///**  @nodoc @nocgmitf */
	//void   RequireDefinitionOfInputAndOutputObjects();
#endif
    
protected: // lien vers l'implementation
    
    CATCXRecomposeShells   * _Implementation;
};

#endif
