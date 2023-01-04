// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : L. Marini 
//
// DESCRIPTION  : Class to federate all operators which need DRep or Live behavior.
//
//=============================================================================
// Creation LAP March 2011
//
//=============================================================================
#ifndef CATDRepOperator_H
#define CATDRepOperator_H

#include "PersistentCell.h"
#include "CATTopOperator.h"
#include "CATBoolean.h"
#include "CATBodyFreezeMode.h"
#include "CATListOfCATPlanes.h"

class CATDRepExtTopOperator; 
class CATDRepBody;
class CATlsoDRepContext;
class CATPlane;
class CATCGMJournalList;
class CATLiveBody;
class CATPersistentOperator;
class CATAdvancedOperator;

/* 
------------------------------------------------------------------------------
--------------------------!!! CAA Interface !!!-------------------------------
------------------------------------------------------------------------------
Be very carreful, this has a CAA Interface created in 2013 by SolidWorks
 GMOperatorsInterfaces\PublicInterfaces\CATICGMDRepOperator.h
Don't forget : @nodoc @nocgmitf
------------------------------------------------------------------------------
*/


class ExportedByPersistentCell  CATDRepOperator : public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATDRepOperator);
public:

  /**
  * @nodoc @nocgmitf
  * Destructor
  */
  virtual ~CATDRepOperator();

  /** @nodoc @nocgmitf */
  virtual int RunOperator();

  /**
  * @nodoc @nocgmitf
  * Used For TrimByThick in ShM
  */
  virtual void SetLiveBodyAllowed(CATBoolean iLiveBodyAllowed);

  
  /** @nodoc @nocgmitf */
  CATBoolean GetLiveBodyAllowed();
  /** @nodoc @nocgmitf */
  CATLiveBody * GetLiveBodyCGM(CATBody * iBody);

  /** @nodoc @nocgmitf */
  // Define the plane of symmety
  // DO NOT USED : IT'S NOT FINISHED
  void SetListOfPlaneOfSymmetry(const CATLISTP(CATPlane) & iListOfPlaneOfSymmetry);
  /** @nodoc @nocgmitf */
  void AppendPlaneOfSymmetry(CATPlane * iPlaneOfSymmetry);

    /** @nodoc @nocgmitf */
  virtual CATPersistentOperator * GetAsPersistentOperator() const;
  /** @nodoc @nocgmitf */
  virtual CATAdvancedOperator   * GetAsAdvancedOperator() const;


protected :

  /** @nodoc @nocgmitf */
  CATDRepExtTopOperator * GetDRepOperatorImpl();

  /**
  * @nodoc @nocgmitf
  * Official Constructor
  * Cannot be called
  */
  CATDRepOperator(CATGeoFactory         * iFactory,
                  CATTopData            * iTopData, 
                  CATDRepExtTopOperator * iImpl);
  /** @nodoc @nocgmitf 
    Contructeur 2 
  */
  CATDRepOperator(CATGeoFactory         * iFactory,
                  CATTopData            * iTopData, 
                  CATBodyFreezeMode       iBodyFreezeMode=CATBodyFreezeOn,
                  CATDRepExtTopOperator * iImpl=NULL);
  /** @nodoc @nocgmitf 
    Contructeur 3 
  */
   CATDRepOperator(CATGeoFactory        * iFactory, 
                  CATCGMJournalList     * iJournal=NULL,
                  CATBodyFreezeMode       iBodyFreezeMode=CATBodyFreezeOn,
                  CATDRepExtTopOperator * iImpl=NULL);

private:
  /** Forbiden call - copy contructor  **/
  // @nodoc @nocgmitf
  CATDRepOperator (const CATDRepOperator &);
  /** Forbidden call : Equal operator  **/
  // @nodoc @nocgmitf
  CATDRepOperator& operator=(const CATDRepOperator &);

};

#endif
