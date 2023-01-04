#ifndef CATICGMObjectsPersistency_h
#define CATICGMObjectsPersistency_h
// COPYRIGHT DASSAULT SYSTEMES  1999
/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATListOfCATICGMObjects.h"
#include "CATMathDef.h"
#include "IUnknown.h"
#include "ExportedByGeometricObjects.h"
#include "CATIACGMLevel.h"
#include "CATCGMStreamVersion.h"
 
class CATICGMObject;
class CATCGMStream;
class CATGeoFactory;

enum CATCGMObjectsUnserialize
{
  CatCGMObjectsUnserialize_Full,
  CatCGMObjectsUnserialize_Partial,
  CatCGMObjectsUnserialize_Complementary
};


#if defined ( CATIACGMV5R22 ) 
// @nodoc  enum does not work for forward declaration
#define CATCGMObjectsVersion int 

enum CATICGMObjectsSaveDiagnosis
{
  NoError,
  UnknownError,
  NotEnoughMemory,
  IncompatibleData
};
#endif


/**
 * Symetric Save/Load to manage a set of geometrical objects belonging to the same CATGeoFactory.
 */

/**
 * Saves list of CGM Objects belonging to the same geofactory into a CATCGMStream .
 */
class ExportedByGeometricObjects CATICGMObjectsSave
{
public :
  /**
  * Constructs an CATICGMObjectsSave operator.
  * @param ioStreamArea
  *   The stream on which the factory is saved.
  */
  CATICGMObjectsSave(CATCGMStream & ioStreamArea);
   /** 
   * Destructor
   */
  ~CATICGMObjectsSave();

#if defined ( CATIACGMV5R22 ) 
  /** 
   * @nodoc
   *  To be used only as part of specific BackSave process
   */
  void SetTargetVersion(CATCGMStreamVersion & iTargetVersion);

  /** 
   * @nodoc
   *  Get Short enumeration of some usefull failures occuring during save attempt 
   */
  CATICGMObjectsSaveDiagnosis GetDiagnosis();

#endif


/**
 * Run Save.
 * @param iFullFederatorObjects
 *   Set of objects to Save. 
 *   Each Object must be a non null value and all objects must be contained in the same CATGeoFactory. 
 * @param iLightSubsetObjects
 *   Light subset of objects that may be loaded partially afterwards. 
 *   List may be empty. 
 *   Each Object must be a non null value and all objects must be contained in the same CATGeoFactory. 
 *   Each Object must be equals or contained in previous list of <tt>iFullFederatorObjects</tt>. 
 * @return
 * The result of the operation.
 * <br><b>Legal values</b>:
 * <dl>
 * <dt><tt>S_OK</tt>   <dd> if operation succeed.
 * <dt><tt>E_FAIL</tt> <dd> if operation fails.
 *</dl>
 */
  HRESULT   Save(const CATLISTP(CATICGMObject) & iFullFederatorObjects,
                 const CATLISTP(CATICGMObject) * iLightSubsetObjects = NULL);

private :
  CATCGMStream * _StreamArea;
#if defined ( CATIACGMV5R22 ) 
  CATCGMStreamVersion _TargetVersion;
  CATICGMObjectsSaveDiagnosis _Diagnosis;
#endif

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATICGMObjectsSave(const CATICGMObjectsSave &iCopy);
  CATICGMObjectsSave& operator=(const CATICGMObjectsSave &iCopy);
};


/**  
 * Load list of CGM Objects belonging to the same geofactory from a CATCGMStream .
 */
class ExportedByGeometricObjects CATICGMObjectsLoad
{
public :
  /**
  * Constructs an CATICGMObjectsLoad operator.
  * @param iStreamArea
 *   The stream from which the factory is read.
  */
  CATICGMObjectsLoad(CATCGMStream & iStreamArea);
   /** 
   * Destructor
   */
  ~CATICGMObjectsLoad();

/**
 * Run Load.
 * @param ioCATGeoFactory
 *   The pointer to the geometrical factory to be loaded.
 *   it must be defined as non null input if <tt>iHowToLoad</tt> is set to <tt>CatCGMObjectsUnserialize_Complementary</tt>.
 * @param ioFullFederatorObjects
 *   The set to the loaded federating geometrical objects.
 *   it is not defined if <tt>iHowToLoad</tt> is set to <tt>CatCGMObjectsUnserialize_Complementary</tt>.
 * @param iHowToLoad
 *    The pointer to the geometrical factory to be loaded.
 * @return
 * The result of the operation.
 * <br><b>Legal values</b>:
 * <dl>
 * <dt><tt>S_OK</tt>   <dd> if operation succeed.
 * <dt><tt>E_FAIL</tt> <dd> if operation fails.
 *</dl>
 */
  HRESULT   Load(CATGeoFactory           * & ioCATGeoFactory,
                 CATLISTP(CATICGMObject)   & ioFullFederatorObjects,
                 CATCGMObjectsUnserialize    iHowToLoad = CatCGMObjectsUnserialize_Full);

private :
  CATCGMStream * _StreamArea;
  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATICGMObjectsLoad(const CATICGMObjectsLoad &iCopy);
  CATICGMObjectsLoad& operator=(const CATICGMObjectsLoad &iCopy);
};

  

#endif
