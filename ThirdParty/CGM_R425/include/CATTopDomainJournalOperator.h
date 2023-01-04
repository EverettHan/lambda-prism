#ifndef CATTopDomainJournalOperator_h_
#define CATTopDomainJournalOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2016



//#include "CATCGMOrm.h"
#include "CATTopOperator.h"
#include "CATCollec.h"

class CATBody;
class CATTopData;
class CATGeoFactory;
class CATExtTopOperator;
class CATCGMJournalList;
class CATLISTP(CATBody);
class CATExtTopDomainJournalOperator;


/** @nodoc @nocgmitf */
/** 
* Class representing the operator that compute the Journal of Domain from the
* a Journal of Cells, a list of input bodies and the output body.
* No result Body is supplied.
* A journal of Domain is returned.
* <br>To use the CATTopDomainJournalOperator:
* <ul><li>Create it the <tt>CATCreateTopDomainJournalOperator</tt> global function. 
* <li>If needed, tune some parameters with the <tt>SetXxx</tt> methods. 
* <li> <tt>Run</tt> the operator
* <li>Retrieve the journal of domain  with the <tt>GetJournalOfDomains</tt> method. 
* <li>Delete the operator with the <tt>delete</tt> operatir after use.</ul>
*/
/** @nodoc @nocgmitf */
class CATTopDomainJournalOperator: public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopDomainJournalOperator);
public:

  /** @nodoc @nocgmitf */
  void SetCellsJournal(CATCGMJournalList *piCGMCellJournal);
  
  /** @nodoc @nocgmitf */
  void SetInputBodies(CATLISTP(CATBody) &iListOfInputBodies);

  /** @nodoc @nocgmitf */
  void SetOutputBody(CATBody *pOutputBody);
    
  /** 
  * @nodoc @nocgmitf
  * Runs <tt>this</tt> operator.
  */
  int RunOperator();

  /** @nodoc @nocgmitf */
  CATCGMJournalList* GetJournalOfDomains();
  
  /**
  * @nodoc @nocgmitf
  */
  CATTopDomainJournalOperator(CATGeoFactory *piFactory, CATTopData *piTopData, CATExtTopDomainJournalOperator *piExtTopDomainJournalOperator);
  
  /**
  * Destructor
  */
  virtual ~CATTopDomainJournalOperator(); // -> delete can't be called

private:
    
  /**
  * @nodoc @nocgmitf
  * Default Constructor
  */
  CATTopDomainJournalOperator();

  /**
  * @nodoc @nocgmitf
  * Copy Constructor
  */
  CATTopDomainJournalOperator(const CATTopDomainJournalOperator& iTopOrmBuildSkeleton);

  /**
  * @nodoc @nocgmitf
  */
  void RequireDefinitionOfInputAndOutputObjects(); 
};

/**
* Creates an operator that compute the Journal of Domain.
* @param iFactory
* The pointer to the factory of the geometry.
* @param piTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside the
* configuration is <tt>NULL</tt>, it is not filled. 
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
CATTopDomainJournalOperator *CATCreateTopDomainJournalOperator(CATGeoFactory *piFactory,CATTopData *piTopData);

#endif

