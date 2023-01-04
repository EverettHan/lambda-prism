#ifndef CATICGMContainer_h
#define CATICGMContainer_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 
#include "CATIACGMLevel.h"

#include "CATICGMUnknown.h"
#include "CATGeometryType.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#include "CATBoolean.h"
#include "CATListOfCATICGMObjects.h"
#include "CATDataType.h"

#if defined (CATIAR417) && defined (CATIACGMR217CAA)
#include "CATCGMScaleCategoryDef.h"
#endif

class  CATICGMObject;
class  CATGeometry;
class  CATCGMJournalList;
class  CATBody;
class  CATTopData;

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATICGMContainer ;
#else
extern "C" const IID IID_CATICGMContainer ;
#endif

//CAA_Exposed CATIGemContainer
/**
 * Interface representing the container of all CGM elements.
 */
class ExportedByCATGMGeometricInterfaces CATICGMContainer : public CATICGMUnknown
{
  CATDeclareInterface;

  public:
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//CAA_Exposed 
/**
 * Defines the type of remove operation inside <tt>this</tt> CATICGMContainer.
 * @param CATICGMContainer::KeepDependancies
 * The objects that are pointed to are kept.
 * @param CATICGMContainer::RemoveDependancies
 * The objects that are pointed to are also removed. This mode is recommended.
 */ 
  enum CATRemovingDependancies { KeepDependancies, RemoveDependancies };

//CAA_Exposed 
 /**
 * Removes an object from <tt>this</tt> CATICGMContainer.
 * @param iObjectToRemove
 * A pointer to the object to remove from the factory. 
 * @param iHow
 * The type of remove operation. 
 * The default mode is <tt>CATICGMContainer::KeepDependancies</tt>, due to legacy reasons.
 * However, it is strongly recommended to use this method with <tt>CATICGMContainer::RemoveDependancies</tt> 
 * to enhance the memory management. The  <tt>CATICGMContainer::RemoveDependancies</tt> 
 * option automatically removes all the implicit objects that are no longer pointed to 
 * by other objects. You should only remove objects created by your application. There are
 * reference objects (reference planes for example) that cannot be removed. Trying to
 * remove such objects may lead to corrupted data.
 */
  virtual void Remove( CATICGMObject* iObjectToRemove, 
                 const CATICGMContainer::CATRemovingDependancies iHow= CATICGMContainer::KeepDependancies) = 0 ;

//CAA_Exposed 
/**
 * Retrieves an object contained in <tt>this</tt> CATICGMContainer from its tag.
 * @param iTag
 * The persistent tag of an object of <tt>this</tt> CATICGMContainer.
 * @param iType
 * The type of geometric object on which the search is done.
 * @return
 * A pointer to the corresponding object.
 */
  virtual CATICGMObject* FindObjectFromTag(CATULONG32  iTag, CATGeometricType iType = CATGeometryType) = 0;


//CAA_Exposed 
/**
 * Scans the geometric objects contained in the container.
 *<br> This method only works on explicit objects.
 * @param iCurrent
 * The pointer to the CATGeometry from which the search is initialized, 
 * may be <tt>NULL</tt> for retrieving the first object.
 * @param iType
 * The type of geometric object on which the search is done.
 * @return
 * A pointer to the CATGeometry created by the factory after
 * <tt>iCurrent</tt>.
 *<br><b>Sample</b>: Search of all explicit objects created by a factory.
 *<pre>
 * CATGeometry* Current = NULL ;
 * while ( Current = MyFactory->Next ( Current ) )
 * { ... process Current ...  } 
 *</pre>
 */
  virtual CATGeometry* Next ( CATGeometry* iCurrent , CATGeometricType iType = CATGeometryType) = 0 ;
  

#if defined (CATIAR417) && defined (CATIACGMR217CAA)
//CAA_Exposed 
/**
  * Retrieves the ScaleCategory associated with <tt>this</tt> CATICGMContainer
  * Note that the Extreme Scale capability is not available in V5. It is available in V6 from V6R417.
  * @return
  *   The geometric ScaleCategory associated with <tt>this</tt> CATICGMContainer.
  */
  virtual CATCGMScaleCategory GetScaleCategory () const = 0 ; 
  
#endif


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


 /**
 * @nodoc
 * Removes (with enhanced RemoveDependancies) an object from <tt>this</tt> CATICGMContainer.
 * @param iBody
 * A pointer to the object to remove from the factory. 
 * @param iTopData
 * The object defining the CATSoftwareConfiguration and the CATCGMJournalList.
 */
  virtual void Remove( CATBody* iBody,  CATTopData &iTopData) = 0 ;
 
 /**
 * @nodoc
 * Removes (with enhanced RemoveDependancies) an object from <tt>this</tt> CATICGMContainer.
 * @param iObjectToRemove
 * A pointer to the object to remove from the factory. 
 * @param iInReport
 * The pointer to a journal list inside which deletion item are reported. 
 * If <tt>NULL</tt>, no eletion item are reported.
 */
  virtual void Remove( CATICGMObject* iObjectToRemove, CATCGMJournalList* iInReport) = 0 ;


 /**
  * @nodoc
 */
  virtual void FindObjectsFromTag(const CATLONG32               iNbObject,
                                  const CATULONG32       iTags[],
                                  CATLISTP(CATICGMObject) &ioObjects ) = 0 ;
 /**
  * @nodoc
 */
  virtual void Tass() = 0 ;

 /**
  * @nodoc
  */
  virtual void *GetImplementCGM() const = 0;

 /**
  * @nodoc
  */
  virtual int IsImplementCGMRemoved(const CATGeometricType iTypeReference=CATGeometryType) const = 0;

 /**
  * @nodoc
  */
 virtual ULONG __stdcall CATAddRefFrom(void *iForDebug, CATBoolean iLockEquation = FALSE) = 0;

 /**
  * @nodoc
  */
 virtual ULONG __stdcall CATReleaseFrom(void *iForDebug, CATBoolean iLockEquation = FALSE) = 0;

  
/** @nodoc */
  virtual void PropagateQuery(CATICGMUnknown *iFrom, CATCGMQueryManager &iQuery ) = 0;
};
  
CATDeclareHandler(CATICGMContainer,CATICGMUnknown);

#endif
