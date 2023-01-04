#ifndef CATAdvancedExtTopOperator_H
#define CATAdvancedExtTopOperator_H

#include "PersistentCell.h"
#include "CATDRepExtTopOperator.h"
#include "CATXBooleanTrue.h"
#include "CATSysBoolean.h"
#include "CATMathInline.h"

class CATGeoFactory;
class CATBody;
class CATCGMOutput;
class CATCGMStream;
class CATTopData;
class CATGMBaseInfra;
class CATPersistentExtTopOperator;
class CATlsoContext;
class CATTolerance;


// Nouvelle classe mere des PersistentOperators.
// Interface : CATAdvancedTopOperator
class ExportedByPersistentCell CATAdvancedExtTopOperator : public CATDRepExtTopOperator
{
public:
  
  // Destructor
  virtual ~CATAdvancedExtTopOperator();
  // Surcharge du new/delete
  CATCGMNewClassArrayDeclare;

  //=======================================================================
  // RunDRepOperator
  //=======================================================================
  virtual int RunOperator();


  // ----------------------------------------------------------------------
  // Get Pulic Methodes
  // ----------------------------------------------------------------------
  INLINE ListPOfCATBody       GetInputBodies()  const;
  INLINE double               GetXScaleFactor() const;
  INLINE CATBoolean           IsInfraShared()   const;
  INLINE CATBoolean           IsInfraOwner()    const;

  int GetNumOperatorId() const;      


  // Cast used to protect LiveBody (VB7)
  virtual INLINE CATAdvancedExtTopOperator   * GetAsAdvancedExtTopOperator()   const;
  virtual INLINE CATPersistentExtTopOperator * GetAsPersistentExtTopOperator() const;
  virtual INLINE int GetNumberOfRun() const;

  // ----------------------------------------------------------------------
  // Set Methodes
  // ----------------------------------------------------------------------
  virtual void ReplaceBasicContext(CATlsoContext * iNewContext, CATBoolean iDeleteBasicContext=TRUE);

  // ------------------------------------------------------------
  // For Debug only
  // ------------------------------------------------------------
  INLINE void  SetXScaleFactor(const double iXScaleFactor);
  void         SetReadCGMReplayMode(CATBoolean iReadCGMReplayMode);
  

  // ----------------------------------------------------------------------
  // Static Methods
  // ----------------------------------------------------------------------
  // Retrieve the DRep extension from a topOperator
  // static CATAdvancedExtTopOperator * RetrieveDRepTopExtensible( CATTopOperator * iTopOpe );
  // Transfer access rights to the live bodies from a father topOperator to its son
  // static void TransferLiveBodyAccessRights( CATTopOperator * iFatherOpe, CATTopOperator * iSonOpe );
  // Transfer the DRepBehaviour object from a father topOperator to its son
  //static void TransferDRepBehaviour( CATTopOperator * iFatherOpe, CATTopOperator * iSonOpe );

protected:
 /** @nodoc 
  * cannot be called
  */
  // Constructor officiel 1 : sans body
  CATAdvancedExtTopOperator(CATGeoFactory &iFactory, CATSoftwareConfiguration *iConfig, CATGMBaseInfra *iBaseInfra=NULL);
  // Contructeur Officiel 2 - avec input body
  CATAdvancedExtTopOperator(CATGeoFactory &iFactory, CATBody *iInputBody, CATSoftwareConfiguration *iConfig, CATGMBaseInfra *iBaseInfra=NULL);
  // Contructeur Officiel 3 - avec input bodylist
  CATAdvancedExtTopOperator(CATGeoFactory &iFactory, const ListPOfCATBody &iInputBodies, CATSoftwareConfiguration *iConfig, CATGMBaseInfra *iBaseInfra=NULL);
  
  // ====================================================================================
  // Virtual Sub-Methods
  // ====================================================================================

  // Implementaion RunOperator (classe mere).
  // ------------------------------------------------------
  virtual int   RunAdvancedOperator() = 0; // devra devenir virtuelle pure.
  virtual int   BeforeRunAdvancedOperator();
  virtual int   AfterRunAdvancedOperator();

  // VB7 - transfert warning list from PersistentCellInfra to this operator
  void TransfertWarningList(); 
  virtual void CheckJournalForDebug(CATCGMJournalList * iJournal = NULL);
  virtual void DumpLiveOutput(CATCGMOutput &iOs);

  // ----------------------------------------------------------------------
  // Protected methods - for child operarators access.
  // ----------------------------------------------------------------------
  const ListPOfCATBody  & GetRefInputBodies() const;
  CATlsoContext         & GetContext()        const;  
  INLINE void             OwnTheInfra();
  INLINE CATBoolean       GetReadCGMReplayMode()  const;
  CATBody               * GetInputBodyWithCheck() const; // returns input body if it is unique
  CATBody               & GetMonoInputBody()      const; // return input mono body or throw     
  CATGMBaseInfra        & GetBaseInfra()          const; 

  // ----------------------------------------------------------------------
  // Tolerance - from Factory
  // ----------------------------------------------------------------------
  const CATTolerance    & GetTolerance() const;

  
  int         AppendInputBody(CATBody * iOneInputBody);
  void        DeleteContextWithCheck(CATlsoContext * iContext);
  CATBoolean  GetInterruptionRequested(const CATBoolean iThrowIfInterrupted=FALSE) const; 

  // Fast Run only 
  int         ReplaceInputBody(CATBody * iOneInputBody, int iNum=1);

public:

  // ----------------------------------------------------------------------
  // CGMReplay Methode
  // ----------------------------------------------------------------------
  virtual void Dump( CATCGMOutput& os ) ;
  virtual void DumpOutput(CATCGMOutput& os);

private:
  // ----------------------------------------------------------------------
  // Internal Methodes
  // ----------------------------------------------------------------------
  void InitAdvancedOperator(CATGeoFactory &iFactory, CATSoftwareConfiguration *iConfig);
  void ForceDRepBehavior_Debug();
  void StartRunTimerForCGMReplay();
  void GetRunTimeForCGMReplay();

  /** Forbiden call - copy contructor  **/
  CATAdvancedExtTopOperator (const CATAdvancedExtTopOperator &);
  /** Forbidden call : Equal operator  **/
  CATAdvancedExtTopOperator& operator=(const CATAdvancedExtTopOperator &);


  // ----------------------------------------------------------------------
  // Internal Data
  // ---------------------------------------------------------------------- 
  ListPOfCATBody      _InputBodies;
  CATGMBaseInfra    * _GMBaseInfra;
  CATBoolean          _SharedInfra;
  CATlsoContext     * _BasicContext;

  CATBoolean          _ReadCGMReplayMode; // For CGMReplay cleaning memory
  double              _XScaleFactor;
  CATTimerId          _RunTimer;          // CGMReplay mode only.

  int                 _NumOperatorId;    //VB7 05-18-2016

};

//INLINE void CATAdvancedExtTopOperator::SetLiveBodyAllowed(CATBoolean iLiveBodyAllowed) {
//  _LiveBodyAllowed = iLiveBodyAllowed; }
//
//INLINE CATBoolean CATAdvancedExtTopOperator::GetLiveBodyAllowed() const {
//  return _LiveBodyAllowed; }

//INLINE void CATAdvancedExtTopOperator::SetListOfPlaneOfSymmetry(const CATLISTP(CATPlane) & ilistOfPlaneOfSymmetry) {
//  _ListOfPlaneOfSymmetry = ilistOfPlaneOfSymmetry; }

// --------------------------------------------------------------------------
//INLINE const CATLISTP(CATPlane) & CATAdvancedExtTopOperator::GetListOfPlaneOfSymmetry() const {
//  return _ListOfPlaneOfSymmetry; }

// --------------------------------------------------------------------------
INLINE CATAdvancedExtTopOperator * CATAdvancedExtTopOperator::GetAsAdvancedExtTopOperator() const {
  return (CATAdvancedExtTopOperator * ) this; }

// --------------------------------------------------------------------------
INLINE CATPersistentExtTopOperator * CATAdvancedExtTopOperator::GetAsPersistentExtTopOperator() const {
  return NULL; }

INLINE int CATAdvancedExtTopOperator::GetNumberOfRun() const {
  return 1; }

//INLINE CATAdvancedExtTopOperator * CATAdvancedExtTopOperator::RetrieveDRepTopExtensible( CATTopOperator * iTopOpe ) {
//  CATExtTopOperator * topExt = ( iTopOpe ) ? ( iTopOpe -> GetTopExtensible() ) : ( NULL );
//  return ( ( topExt ) ? ( topExt -> CastToCATAdvancedExtTopOperator() ) : ( NULL ) ); }

// --------------------------------------------------------------------------
INLINE ListPOfCATBody CATAdvancedExtTopOperator::GetInputBodies() const {
  return _InputBodies; }

// --------------------------------------------------------------------------
INLINE CATBoolean CATAdvancedExtTopOperator::GetReadCGMReplayMode() const {
// --------------------------------------------------------------------------
  return _ReadCGMReplayMode; }

// --------------------------------------------------------------------------
INLINE double CATAdvancedExtTopOperator::GetXScaleFactor() const {
// --------------------------------------------------------------------------
  return _XScaleFactor; }

// --------------------------------------------------------------------------
INLINE void CATAdvancedExtTopOperator::SetXScaleFactor(const double iXScaleFactor) {
// --------------------------------------------------------------------------
  _XScaleFactor = iXScaleFactor; }

// --------------------------------------------------------------------------
INLINE CATBoolean CATAdvancedExtTopOperator::IsInfraShared() const {
  return _SharedInfra; }

// --------------------------------------------------------------------------
INLINE CATBoolean CATAdvancedExtTopOperator::IsInfraOwner() const {
  return !_SharedInfra; }

// --------------------------------------------------------------------------
INLINE void CATAdvancedExtTopOperator::OwnTheInfra() {
  _SharedInfra=FALSE; }


#endif
