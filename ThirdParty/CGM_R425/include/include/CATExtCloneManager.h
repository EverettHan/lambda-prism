#ifndef CATExtCloneManager_h_
#define CATExtCloneManager_h_
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//
//  INTERDICTION D'INCLURE DANS HEADER CAA
//
//  HEADER IMPLEMENTATION : PERMETTRE EVOLUTION VUE IMPLEMENTATIVE
//
//=============================================================================
// Jun. 03  CATBackTargetVersion pour CATBack                             HCN
// Jun. 18  Add Impprint Journal Reporting                                KY1    
//=============================================================================

#include "CATExtGeoOperator.h"
#include "CATCloneManager.h"
#include "CATExtClonableAttributes.h"
#include "YP00IMPL.h"
#include "CATListOfCATExtClonableAttributes.h"
#include "CATMathInline.h"
#include "CATListOfInt.h"
#include "CATCGMIndex.h"
#include "CATCGMAttrReframeDesignLimits.h"
#include "CATCGMObjectConvertAdapter.h"

class CATCGMMultiCopyPasteTransaction;
class CATMapGeoToAssoc;
class CATMathNonLinearTransformation;
class CATMathTransformation;
class oper_GeoFactoryContainer;
class oper_NewTopo;
class CATExtCloneExplicitAssoc;
class CATCGMObjectConvertAdapter;



//------------------------- 
// CATExtCloneManager
//------------------------- 
class ExportedByYP00IMPL CATExtCloneManager : public CATExtGeoOperator
{
public:
  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;

  //-------------------------------------------------------------------------------------------------------
  // ClonableAttribute
  //-------------------------------------------------------------------------------------------------------
  void TodoReportClonableAttribute(CATICGMObject* iOrigin, CATICGMObject* iDestination,
                                   CATLISTP(CATCGMAttribute) & ioAttributesList);

  void FlushTabClonableAttributes();

  INLINE CATLISTP(CATExtClonableAttributes) * GetClonableAttributes() const;

  /**
 * Writes the Imprint topological journal inside the Given Journal associated with 
 <tt>this</tt> CATCloneManager process.
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
#ifdef CATIACGMR421CAA
  void WriteImprintReport(CATCGMJournalList *&ioJournal, CATCGMJournal::Type iType , CATBoolean iAddInfo = CATBoolean(1)) const;
#endif
  //-------------------------------------------------------------------------------------------------------
  // Clone to identical
  //-------------------------------------------------------------------------------------------------------
  /** @nodoc
  * Use TRUE to communicate to CloneManager
  * that each IN object added to manager is identical (strict numerical identity of all parameters)
  * to the corresponding OUT.
  */
  void SetGeometriesAreIdentical(CATBoolean iGeometriesAreIdentical);

  /** @nodoc */
  INLINE short GetGeometriesAreIdentical() {return _GeometriesAreIdentical;}


  //-------------------------------------------------------------------------------------------------------
  // WriteInput
  //-------------------------------------------------------------------------------------------------------

  /** @nodoc */
  void WriteInput(CATCGMStream  & ioStream);
  /** @nodoc */
  void WriteOutput(CATCGMStream & ioStream);
  /** @nodoc */
  CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  /** @nodoc */
  static CATCGMOperator * CreateOrUpdate(CATCloneManager *iCloneManager, CATCGMStream &Str,const short LevelOfRuntime, const short VersionOfStream);
  /** @nodoc */
  void Dump( CATCGMOutput& os );
  
  // For common static method about Update after loaded
  virtual CATCGMOperator *CreateOrUpdate(CATCGMStream &Str,const short LevelOfRuntime, const short VersionOfStream);

  /** @nodoc */
  virtual void DumpMultipleRun( CATCGMStream &iStream, CATCGMOutput& os );

  //----------------------------------------------- 
  //  Extended Run() INTEGRATION 
  //----------------------------------------------- 

  // Reserved for Operator mandatory implement for integration
  virtual CATBoolean IsMultipleRun(); 
 
  //----------------------------------------------- 
  //  For Cache Management After each Run()
  //----------------------------------------------- 

  // Boolean RC : if AfterRun() should be called  
  virtual CATBoolean BeforeRun(int iDepth, int iDepthForChain);
  //  iOkRun : Value 1=Okay  0=Error
  //  iDepth : Depth of Operator
  virtual void AfterRun(int iOkRun, int iDepth,  int iDepthForChain);

  // Extended Run with variational parameters 
  void FullGenerationFromAssocList();

  //----------------------------------------------- 
  //  For Reverse Clone
  //-----------------------------------------------
  
  // Add reversed obj/image pair from AssocList into iCloneManager in param 
  void FillCloneWithReverseAssoc(CATCloneManager* iCloneManager);

//----------------------------------------------------------------------------------
//  MultiScale Management 
//----------------------------------------------------------------------------------

  INLINE CATBoolean                      FactoryScaleIsChanging() const ;
  INLINE CATCGMAttrReframeDesignLimits * GetReframeAnchorLink();
  void                                   SetReframeAnchorLink(CATCGMAttrReframeDesignLimits * iAnchorPtr );

  //------------------------------------------------------------------------------------------------------------- 
  //  For Fast Transform Face project : disable optimisation of face bounding box computation ( SpecialMode = 1 )
  //-------------------------------------------------------------------------------------------------------------
  
  INLINE void SetSpecialMode(const int iSpecialMode) 
  {
    _SpecialMode = iSpecialMode;
  }

 
  INLINE int GetSpecialMode() 
  {
	return ( _SpecialMode );
  }

  // CATBack
  INLINE void SetCATCGMObjectConvertAdapter(CATCGMObjectConvertAdapter * iObjConvert);
  INLINE CATCGMObjectConvertAdapter * GetCATCGMObjectConvertAdapter();
  void AddObjectToConvert(CATICGMObject * iObject);
  void ConvertCATBackIncompatibleObjects(CATMapGeoToAssoc *& iAssocList);
  void ReplaceIncompatibleByCloneImage(CATMapGeoToAssoc *& iAssocList);


private :
  CATCGMAttrReframeDesignLimits        * CreateReframeAnchorLink();

protected :

  CATExtCloneManager(); 
  virtual ~CATExtCloneManager();

  void TestAndInitMultiCopyPaste( CATSoftwareConfiguration *  iVersion               ,
                                  CATGeoFactory            *  iInputImplicitFactory  ,
                                  CATGeoFactory            *  iOutputImplicitFactory , 
                                  CATMathTransformation    *  iMathTransformation    ,
                                  CATCloneManagerType         iCloneType             ,         
                                  short                    &  ioOnlyBodiesInInput    ,
                                  CATMapGeoToAssoc         *& ioAssocList            );

  void SetOnlyBodiesInInput ( short iOnlyBodiesInInput );

  void TestInterFactoryCompatibity ( const int                        iFirstAddition               ,
                                     CATGeoFactory                  * iOldFactory                  , 
                                     CATGeoFactory                  * iNewFactory                  , 
                                     CATICGMObject                  * iInputObject                 ,
                                     const CATBoolean                 iIsIdentity                  ,
                                     CATMathNonLinearTransformation * iMathNonLinearTransfo = NULL ,
                                     CATMathTransformation          * iMathTransfo          = NULL );

  // CATBack
  INLINE void SetCATBackTargetVersion(CATCGMStreamVersion iVersion);
  INLINE CATCGMStreamVersion GetCATBackTargetVersion() const;


  friend class CATCloneManager;
  friend class CATTransfoManager;
  friend class CATTransfoDuplicate;
  friend class CATSimplifyManager;

  friend class oper_GeoFactoryContainer;
  friend class oper_NewTopo;

//----------------------------------------------------------------------------------
//  Data 
//----------------------------------------------------------------------------------
protected:

  CATLISTP(CATICGMObject)         * _pVerticesWithSharpnessData;

  CATCGMMultiCopyPasteTransaction * _MultiCopyPasteTransaction; // multi COPY - PASTE

  int                               _InitialAssocListPosition; // multi COPY - PASTE

  CATCGMStreamVersion               _CATBackTargetVersion; // pour CATBack
  CATCGMObjectConvertAdapter *      _ObjectConvertAdapter; // CATBack convert


  CATLISTP(CATExtClonableAttributes) *  _ClonableAttributes;

  // Extended Run Management with Cache of explicit Association List management
  CATExtCloneExplicitAssoc           *  _CloneManagerVariationalCache;

private:
  CATCGMAttrReframeDesignLimits      * _ReframeAnchorLink;
  CATBoolean                           _FactoryScaleIsChanging; // Std Scale <-> BigScale

  short                                _GeometriesAreIdentical;

  int                                  _SpecialMode;
};

//----------------------------------------------------------------------------------
//  CATBack : SetCATBackTargetVersion
//----------------------------------------------------------------------------------
INLINE void CATExtCloneManager::SetCATBackTargetVersion(CATCGMStreamVersion iVersion)
{
  _CATBackTargetVersion = iVersion;
}

//----------------------------------------------------------------------------------
//  CATBack : GetCATBackTargetVersion
//----------------------------------------------------------------------------------
INLINE CATCGMStreamVersion CATExtCloneManager::GetCATBackTargetVersion() const
{
  return _CATBackTargetVersion;
}

//----------------------------------------------------------------------------------
//  CATBack : SetCATCGMObjectConvertAdapter
//----------------------------------------------------------------------------------
INLINE void CATExtCloneManager::SetCATCGMObjectConvertAdapter(CATCGMObjectConvertAdapter * iObjectConvertAdapter)
{
	_ObjectConvertAdapter = iObjectConvertAdapter;
}

INLINE CATCGMObjectConvertAdapter * CATExtCloneManager::GetCATCGMObjectConvertAdapter()
{
	return _ObjectConvertAdapter;
}

//-------------------------------------------------------------------------------------------------------
// GetClonableAttributes
//-------------------------------------------------------------------------------------------------------
INLINE CATLISTP(CATExtClonableAttributes) * CATExtCloneManager::GetClonableAttributes() const 
{ return _ClonableAttributes; }

//-------------------------------------------------------------------------------------------------------
// FactoryScaleIsChanging
//-------------------------------------------------------------------------------------------------------
INLINE CATBoolean CATExtCloneManager::FactoryScaleIsChanging() const 
{ return _FactoryScaleIsChanging; }

//-------------------------------------------------------------------------------------------------------
// GetReframeAnchorLink
//-------------------------------------------------------------------------------------------------------
INLINE CATCGMAttrReframeDesignLimits * CATExtCloneManager::GetReframeAnchorLink() 
{ return _ReframeAnchorLink?_ReframeAnchorLink:CreateReframeAnchorLink(); }

#endif
