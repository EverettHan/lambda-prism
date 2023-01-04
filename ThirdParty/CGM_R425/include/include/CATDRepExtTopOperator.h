#ifndef CATDRepExtTopOperator_H
#define CATDRepExtTopOperator_H

#include "PersistentCell.h"
#include "CATExtTopOperator.h"
#include "CATXBooleanTrue.h"
#include "CATSysBoolean.h"
#include "CATMathInline.h"
#include "CATListOfCATPlanes.h"

class CATGeoFactory;
class CATBody;
// class CATDRepExtTopOperator;
class CATCGMOutput;
class CATLiveBody;
class CATTopOperator;
class CATCGMStream;
class CATPlane;
class CATTopData;
// class CATGMBaseInfra;
class CATPersistentExtTopOperator;
class CATAdvancedExtTopOperator;
// class CATlsoContext;
// class CATPersistentCellInfra;


// Pour les services LSO, utilisez la classe CATAdvancedExtTopOperator
// -------------------------------------------------------------------------
class ExportedByPersistentCell CATDRepExtTopOperator : public CATExtTopOperator
{
public:
  
  // Destructor
  virtual ~CATDRepExtTopOperator();
  // Surcharge du new/delete
  CATCGMNewClassArrayDeclare;

  //=======================================================================
  // RunDRepOperator
  //=======================================================================
  virtual int RunOperator();


  // ----------------------------------------------------------------------
  // Get Pulic Methodes
  // ----------------------------------------------------------------------
  INLINE CATBoolean  GetLiveBodyAllowed() const;

  // @nocgmitf (do not create phase 2 interface)
  CATLiveBody * GetLiveBodyCGM(CATBody * iBody) const;

  // Cast used to protect LiveBody (VB7)
  virtual INLINE CATDRepExtTopOperator * CastToCATDRepExtTopOperator();
  virtual INLINE CATPersistentExtTopOperator * GetAsPersistentExtTopOperator() const;
  virtual INLINE CATAdvancedExtTopOperator   * GetAsAdvancedExtTopOperator() const;


  // ----------------------------------------------------------------------
  // Set Methodes
  // ----------------------------------------------------------------------
  INLINE void SetLiveBodyAllowed(CATBoolean iLiveBodyAllowed);
  INLINE void SetListOfPlaneOfSymmetry(const CATLISTP(CATPlane) & ilistOfPlaneOfSymmetry);
  void AppendPlaneOfSymmetry(CATPlane * iPlaneOfSymmetry);

  virtual void SetTopData(const CATTopData& ioTopData); // For versioning of operator without extension  

  // ----------------------------------------------------------------------
  // Static Methods
  // ----------------------------------------------------------------------
  // Retrieve the DRep extension from a topOperator
  static CATDRepExtTopOperator * RetrieveDRepTopExtensible( CATTopOperator * iTopOpe );
  
  // Transfer access rights to the live bodies from a father topOperator to its son
  static void TransferLiveBodyAccessRights( CATTopOperator * iFatherOpe, CATTopOperator * iSonOpe );
  // Transfer the DRepBehaviour object from a father topOperator to its son
  static void TransferDRepBehaviour( CATTopOperator * iFatherOpe, CATTopOperator * iSonOpe );

protected:
 /** @nodoc 
  * cannot be called
  */
  CATDRepExtTopOperator(CATGeoFactory *ipFactory=NULL, CATSoftwareConfiguration *ipConfig=NULL);
  
  INLINE const CATLISTP(CATPlane) & GetListOfPlaneOfSymmetry() const;


public:

  // ----------------------------------------------------------------------
  // CGMReplay Methode
  // ----------------------------------------------------------------------
  static void ReadDRepInputData(CATDRepExtTopOperator & iOpe, CATCGMStream & ioStr, CATGeoFactory * iFactory);
  void WriteDRepInputData(CATCGMStream  & ioStr);
  virtual void Dump( CATCGMOutput& os ) ;
  virtual void DumpOutput(CATCGMOutput& os);
  void RequireDefinitionOfDRepInputData();

private:
  // ----------------------------------------------------------------------
  // Internal Methodes
  // ----------------------------------------------------------------------
  void InitDRepOperator(CATGeoFactory *iFactory=NULL, CATSoftwareConfiguration *iConfig=NULL);

  /** Forbiden call - copy contructor  **/
  CATDRepExtTopOperator (const CATDRepExtTopOperator &);
  /** Forbidden call : Equal operator  **/
  CATDRepExtTopOperator& operator=(const CATDRepExtTopOperator &);


  // ----------------------------------------------------------------------
  // Internal Data
  // ---------------------------------------------------------------------- 
  CATBoolean          _LiveBodyAllowed;
  CATLISTP(CATPlane)  _ListOfPlaneOfSymmetry;

};

INLINE void CATDRepExtTopOperator::SetLiveBodyAllowed(CATBoolean iLiveBodyAllowed) {
  _LiveBodyAllowed = iLiveBodyAllowed; }

INLINE CATBoolean CATDRepExtTopOperator::GetLiveBodyAllowed() const {
  return _LiveBodyAllowed; }

INLINE void CATDRepExtTopOperator::SetListOfPlaneOfSymmetry(const CATLISTP(CATPlane) & ilistOfPlaneOfSymmetry) {
  _ListOfPlaneOfSymmetry = ilistOfPlaneOfSymmetry; }

// --------------------------------------------------------------------------
INLINE const CATLISTP(CATPlane) & CATDRepExtTopOperator::GetListOfPlaneOfSymmetry() const {
  return _ListOfPlaneOfSymmetry; }

// --------------------------------------------------------------------------
INLINE CATDRepExtTopOperator * CATDRepExtTopOperator::CastToCATDRepExtTopOperator() {
  return this; }

// --------------------------------------------------------------------------
INLINE CATPersistentExtTopOperator * CATDRepExtTopOperator::GetAsPersistentExtTopOperator() const {
  return NULL; }

// --------------------------------------------------------------------------
INLINE CATAdvancedExtTopOperator * CATDRepExtTopOperator::GetAsAdvancedExtTopOperator() const {
  return NULL; }


#endif
