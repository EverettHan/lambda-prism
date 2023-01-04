
#ifndef CATCloneManager_H
#define CATCloneManager_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "YP00IMPL.h"

#include "CATCGMOperator.h"
#include "CATCGMNewArray.h"

#include "CATMathDef.h" 
#include "CATCGMJournal.h"
#include "CATString.h"
#include "CATListOfCATICGMObjects.h"
#include "CATCGMStreamVersion.h"
#include "CATMathInline.h"

class CATGeoFactory;
class CATAssociation;
class CATICGMObject;
class CATCGMJournalList;
class CATMapGeoToAssoc;
class CATBody;
class CATSoftwareConfiguration;
class CATExtCloneManager;
class CATExtCloneExplicitAssoc;

/**
 * Defines the mode of the clone process.
 * @param CatCGMSingleDuplicate
 * Only duplicates the objects
 * that are <tt>Add</tt>ed to the CATCloneManager. This is the default value.
 * This value is only applicable in the case the objects are being copied within the same container.
 * @param CatCGMFullDuplicate
 * Duplicates the objects
 * that are <tt>Add</tt>ed to the CATCloneManager and the forward linked objects.
 * This value for <tt>CATCloneManagerType</tt>  should be used explicitly when full copy
 * is desired in the case of the objects being copied within the same container.
 * For copying objects to a different container this value is used internally
 * regardless of the value assigned to <tt>CATCloneManagerType</tt>. 
 * @param CatCGMUnknownDuplicate
 * Internal use.
 */
enum CATCloneManagerType {CatCGMSingleDuplicate = +1, CatCGMFullDuplicate = +100, CatCGMUnknownDuplicate = +101};

/**
 * Class representing the process of duplication of a CATICGMObject.<br>
 * <ul>
 * <li>The clone process takes the forward links into account
 * <li>A CATCloneManager can process several CATICGMObjects at the same time.
 * <li>A CATCloneManager has two modes of duplication:
 *<dl><dt>CatCGMSingleDuplicate</dt><dd>Only duplicates the objects
 * that are <tt>Add</tt>ed to the CATCloneManager.
 * This value is only applicable in the case the objects are being copied within the same container.
 * <dt>CatCGMFullDuplicate</dt><dd>Duplicates the objects
 * that are <tt>Add</tt>ed to the CATCloneManager and the forward linked objects.
 * This value for <tt>CATCloneManagerType</tt>  should be used explicitly when full copy
 * is desired in the case of the objects being copied within the same container.
 * For copying objects to a different container this value is used internally
 * regardless of the value assigned to <tt>CATCloneManagerType</tt>.
 *</dl>
 * <li>A CATCloneManager offers two types of methods:
 *<ul>
 * <li>"user methods" that are called by the application programmer 
 * to clone CATICGMObjects: <tt>Add</tt>, <tt>Run</tt>, <tt>ReadImage</tt>, 
 * <tt>WriteReport</tt>, <tt>GetFactory</tt>
 * <li>"object methods" that are called by the CATICGMObjects to
 * ask for the clone of their forward linked objects. 
 * These methods must not be normally called,
 * except in the <tt>CATICGMObject::Clone</tt> method, 
 * if you intend to create your own CATICGMObject class.
 *</ul>
 * <li>The objects of this class are transient and cannot be streamed
 * </ul>
 * code sample :
 * <pre>
 * CATCloneManager MyManager(MyGeoFactory);
 * MyManager.Add(MyCGMObject);
 * MyManager.Run();
 * CATICGMObject* ClonedObject=MyManager.ReadImage(MyCGMObject);
 * MyManager.WriteReport(MyJournal, CATCGMJournal::Modification);
 * </pre>
 */
class ExportedByYP00IMPL CATCloneManager : public CATCGMOperator
{
public:
   /** @nodoc */
  CATCGMNewClassArrayDeclare;

  //***************************************************************************
  //****** USER METHODS
  //***************************************************************************

/**
 * Constructs a CATCloneManager.
 * @param iFactory
 * The pointer to the factory of the resulting objects.
 * @param iType
 * The type of duplication. This is relevant when copying within the same container. 
 * CatCGMFullDuplicate is always used for copying into a different container.
 * @param  iConfig
 * The pointer to the configuration.Should not be <tt>NULL</tt> in case of topological objects.
 */
  CATCloneManager(CATGeoFactory            *iFactory                     ,
	                CATCloneManagerType       iType = CatCGMSingleDuplicate,
                  CATSoftwareConfiguration *iConfig = NULL);

/**
 * Adds a CATICGMObject to clone with <tt>this</tt> CATCloneManager.
 *<br>All the added objects must belong
 * to the same factory.
 * @param iObjectToClone
 * The pointer to the object to add to the CATCloneManager. 
 * @param iWhereToPaste
 * If not NULL, it forces the duplication of <tt>iObjectToClone</tt> to be
 * the object <tt>iWhereToPaste</tt>.  
 * This can be used to copy and paste objects from one container to another one.
 * Notice that there is no transformation here.
 */
  virtual void Add(CATICGMObject * iObjectToClone    ,
		   CATICGMObject * iWhereToPaste  = 0);

/**
 * Runs the CATCloneManager process.
 * This method should be called only once.
 */
  virtual int Run();

/**
 * Returns a pointer to the CATICGMObject (called "image") corresponding to the clone 
 * by <tt>this</tt> of a given <tt>iObject</tt>.
 * @param iObject
 * The pointer to the object which the image is asked for.
 * @return
 * The pointer to the image if it exists. <tt>0</tt> otherwise.
 */
  virtual CATICGMObject* ReadImage(CATICGMObject * iObject);

/**
 * Writes the topological journal associated with <tt>this</tt> CATCloneManager process.
 * <br>The journal follows the modifications of the topological
 * objects.
 * @param ioJournal
 * The pointer to the journal to fill
 * @param iType
 * The type of modification to be written.
 * The attribute to put to the face that have just been cloned.
 * <dl><dt><tt>CATCGMJournal::Creation</tt></dt><dd>All the duplicated faces are written
 * as created into the journal 
 *      <dt><tt>CATCGMJournal::Modification</tt></dt><dd>All the duplicated faces are written
 * as modified into the journal 
 *	  </dl>
 * @param iAddInfo
 * The activation of the journal info .
 * <br><b>Legal values</b>:
 * <tt>TRUE</tt> for the activation, <tt>FALSE</tt> otherwise.
 */
  virtual void WriteReport(CATCGMJournalList   * &ioJournal               , 
                           CATCGMJournal::Type    iType                   ,
                           CATBoolean             iAddInfo = CATBoolean(1)) const;

/**
 * Writes the topological journal for one object.
 * @param iObject
 * The pointer to the object to follow.
 * @param ioJournal
 * The pointer to the journal to fill
 * @param iType
 * The type of modification to be written.
 * The attribute to put to the face that have just been cloned.
 * <dl><dt><tt>CATCGMJournal::Creation</tt></dt><dd>All the duplicated faces are written
 * as created into the journal 
 *      <dt><tt>CATCGMJournal::Modification</tt></dt><dd>All the duplicated faces are written
 * as modified into the journal 
 *	  </dl>
 * @param iAddInfo
 * The activation of the journal info .
 * <br><b>Legal values</b>:
 * <tt>TRUE</tt> for the activation, <tt>FALSE</tt> otherwise.
 */
  virtual void WriteReport(CATICGMObject       *  iObject                 ,
                           CATCGMJournalList   * &ioJournal               , 
                           CATCGMJournal::Type    iType                   ,
                           CATBoolean             iAddInfo = CATBoolean(1)) const;

  //***************************************************************************
  //****** OBJECTS METHODS
  //***************************************************************************

/**
 * @nodoc
 * Processes the clone of a CATICGMObject. 
 *<br> "Object method": to be only called by the <tt>CATICGMObject::Clone</tt> method.
 * @param iObject
 * The object to clone 
 * @return
 * The pointer to the duplicated object.
 */
  virtual CATICGMObject* ComputeImage(CATICGMObject * iObject);

  virtual ~CATCloneManager();

  /** @nodoc */
  CATLONG32 OnlyBodiesInInput();

  /** @nodoc */
  CATLISTP(CATICGMObject)* GetVolatileVerticesWithSharpnessData(const CATBoolean AllocateIfNeeded = TRUE);

  /** @nodoc */
  CATBoolean AlreadyInListWithSharpnessData(CATICGMObject* ipVertex);

  /** @nodoc */
  void AddVertexWithSharpnessData(CATICGMObject* ipVertex);

  /** @nodoc */
  virtual CATSoftwareConfiguration* GetSoftwareConfiguration() const;

  /** @nodoc */
  virtual void Dump( CATCGMOutput& os ) ;

  /** @nodoc */
	virtual const CATString * GetOperatorId();

  /** @nodoc */
  CATBoolean FactoryScaleIsChanging() const;

  /** @nodoc */
  void SetCATBackTargetVersion(CATCGMStreamVersion iVersion);

  /** @nodoc */
  CATCGMStreamVersion GetCATBackTargetVersion() const;

protected:
  
  /** @nodoc */
  CATMapGeoToAssoc * _AssocList;

  /** @nodoc */
  CATCloneManagerType _CloneType;
  /** @nodoc */
  short               _FactoryIsExplicit;
  /** @nodoc */
  short               _OnlyBodiesInInput;

  /** @nodoc */
  CATCloneManager(CATExtCloneManager    *iExtensible, CATGeoFactory         *iFactory,
	                CATCloneManagerType    iType, CATSoftwareConfiguration *iConfig);

  /** @nodoc */
  INLINE CATExtCloneManager *GetExtCloneManager() const;

  /** @nodoc */
  CATSoftwareConfiguration *_Version;

  /** @nodoc */
  static CATString _OperatorId;
  /** @nodoc */
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc */
  void WriteInput(CATCGMStream  & ioStream);
  /** @nodoc */
  void WriteOutput(CATCGMStream & ioStream);
  /** @nodoc */
	CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  /** @nodoc */
  int RunOperator();

private:
  CATAssociation * AddInternal(CATICGMObject * iObjectToClone    ,
 		                           CATICGMObject * iWhereToPaste  = 0);
  void FindLinks(CATICGMObject * iIn);
  CATLONG32 CheckLinks(CATICGMObject* iIn);
  void AnalysisOfLinks(CATICGMObject* iIn);

  friend class CATExtCloneManager;
  friend class CATExtCloneExplicitAssoc;
};


//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================


INLINE CATExtCloneManager *CATCloneManager::GetExtCloneManager() const
{ return (CATExtCloneManager *) (void *) _Extensible; }


#endif
