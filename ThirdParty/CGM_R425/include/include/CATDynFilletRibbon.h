#ifndef CATDynFilletRibbon_h_
#define CATDynFilletRibbon_h_

//=============================================================================
// Copyright Dassault Systemes 2006-2011, all rights reserved
//=============================================================================

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATIACGMLevel.h"
#include "CATGMOperatorsInterfaces.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATShell.h"
#include "CATDynFilletRadius.h"
#include "CATMath.h"
#include "CATBody.h"
#include "CATCreateEndingShell.h"
#include "CATCreateShellForPunch.h"
#include "ListPOfCATBody.h"
#include "CATLISTP_CATMathVector.h"
#include "CATFilletReconfigFillFunction.h"
#include "CATCompositeLaw.h"
#include "CATCGMVirtual.h"
#include "CATFilletDefine.h"
class CATBlendParams;
 
/**
 * Defines the type of selected edge in a ribbon.
 * @param CATDynRolling
 * A rolling edge.
 */
enum CATDynEdgeCrossing
{
  CATDynRolling,
  CATDynRelimit
};

/**
 * Defines the construction mode of the resulting body.
 * @param CATDynTrim
 * The <tt>GetResult</tt> method returns a body inside which the input and ribbon are connected.
 * @param CATDynNoTrim
 * The <tt>GetResult</tt> method only returns a body containing the ribbon.
 */
enum CATDynSegmentationMode
{
  CATDynTrim,
  CATDynNoTrimWithTraceOnSupport,
  CATDynNoTrim
};

/**
 * Defines the type of relimitation on the input bodies.
 * <br>In case of a fillet between skins.
 * @param CATDynMax
 * The length of the ribbon is defined by the length of the largest face. In this case,
 * some options can be set with the <tt>CATDynMaxRelimitationOption</tt> enum
 * to precise the shape of the ribbon in the other direction.
 * @param CATDynMin
 * The length of the ribbon is defined by the length of the smallest face.
 */
enum CATDynRelimitationMode
{
  CATDynMax,
  CATDynMin
};

/**
 * Defines the shape of the ribbon on the free boundaries.
 * <br>In case of <tt>CATDynMax</tt> relimitation mode.
 * @param CATDynNone
 * The whole computed ribbon is used.
 * @param CATDynPline
 * The ribbon free boundaries are Plines on the ribbon surface, from the extremities of each face.
 * @param CATDynSpline
 * The ribbon free boundaries are splines on the ribbon surface, from the extremities of each face. In such case,
 * there is a tangential continuity.
 */
enum CATDynMaxRelimitationOption
{
  CATDynNone,
  CATDynPline,
  CATDynSpline
#if defined(CATIAV5R30) || defined(CATIACGMR424CAA)
  /** @nodoc */
  , CATDynSBdy
#endif
};

    /**
	 * Defines how the ribbon is seewed on the input skins.
	 * <br>In case of <tt>CATDynTrim</tt> mode.
	 * @param CATDynDefaultSide
     * The seewed edges are smooth.
	 * @param CATDynReverseSide
	 * The seewed egdes are sharp.
	 */
enum CATDynSewingOption
{
  CATDynDefaultSide,
  CATDynReverseSide
};

	/**
	 * Defines whether the internal ribbon edges are logged inside the journal.
     * @param CATDynDefaultEdgeReporting
     * The internal edges 
	 * of the ribbon (such as the common edge between the ribbon and the adjacent face)
	 * are not logged inside the journal.
	 * @param CATDynInternalEdgeReporting
	 * The internal edges 
	 * of the ribbon (such as the common edge between the ribbon and the adjacent face)
	 * are logged inside the journal.
	 */
enum CATDynEdgeReporting
{
  CATDynDefaultEdgeReporting,
  CATDynInternalEdgeReporting
};

/**
 * Defines the propagation behavior in case of a multiple automatic propagation ribbons.
 * @param CATDynDefaultPropagAutoMode
 * The ribbon is always propagated.
 * @param CATDynStopOnFilletPropagAutoMode
 * The ribbon is not propagated when it reaches another ribbon generated in the same operator. 
 * @param CATDynPropagManualMode
 * From V5R21: The ribbon is not propagated 
 */
enum CATDynPropagAutoMode
{
  CATDynDefaultPropagAutoMode,
  CATDynStopOnFilletPropagAutoMode,
  CATDynPropagManualMode
};

/**
* Defines whether keep edges (or rolling edges) are automatically 
* searched in the fillet process.
* @param CATDynDefaultKeepEdge
* Only explicit keep edges (defined by the user) are used 
* in the fillet process. 
* @param CATDynImplicitKeepEdge
* All possible keep edges are automatically used in the fillet process
* (priority is set to the keep edges defined by the user).
*/
enum CATDynKeepEdgeMode
{
  CATDynDefaultKeepEdgeMode,
  CATDynImplicitKeepEdgeMode
};

/**
 * Defines the geometric tool of the fillet.
 * @param CATFilletSphereTool
 * The fillet is created with a sphere.
 * @param CATFilletCircleTool
 * The fillet is created with a circle.
 */

enum CATFilletTool
{
  CATFilletSphereTool,
  CATFilletCircleTool
};

/**
 * Identifies a law
 * @param CATFilletRadiusLaw
 * Identifies a radius law
 */
enum CATFilletLawId
{
  CATFilletLawIdRadiusLaw
};

/** @nodoc */
enum CATDynKeepEdgeSameConvexityMode
{
  CATDynDefaultIgnoreKeepEdgeSameConvexity,
  CATDynRunOnKeepEdgeSameConvexity
};


/** 
 * From V5R21
 * Defines the multi-ribbon behaviour
 * @param CATDynDefaultNoMultiSolutionAllowed
 * No multi-ribbon is performed - default behaviour
 * @param CATDynMultiSolutionAllowed
 * Multi-ribbon is performed
 */
enum CATDynFilletFaceFaceInitMode
{
  CATDynDefaultNoMultiSolutionAllowed,
  CATDynMultiSolutionAllowed
};

/** @nodoc */
enum CATDynMinRelimitationOption
{
  CATDynMinNone,
  CATDynMinPunch
};
/** @nodoc */
enum CATDynFilletRibbonType
{
	CATDynEdgeFilletRibbonType,
	CATDynFaceFaceFilletRibbonType,
	CATDynRemoveFaceFilletRibbonType,
	CATDynChamferRibbonType
};

/**
 * Base class defining a fillet ribbon.
 * <br>A ribbon is an elementary process of the filleting operator.
 */
class ExportedByCATGMOperatorsInterfaces CATDynFilletRibbon : public CATCGMVirtual
{
public:
/**
 * Default constructor.
 */
  CATDynFilletRibbon();
  virtual ~CATDynFilletRibbon();
  
/**
 * Returns the construction mode of the resulting body.
 * @return
 * The construction mode.
 */
  CATDynSegmentationMode GetSegmentationMode (int iSupport=0) const ;

/**
 * Defines the construction mode of the resulting body.
 * @param iMode
 * The construction mode.
 */
  void SetSegmentationMode (CATDynSegmentationMode iMode,int iSupport=0);

/**
 * Returns the type of relimitation on the input bodies.
 * <br>In case of a fillet between skins.
 * @return
 * The relimitation mode.
 */
  CATDynRelimitationMode GetRelimitationMode (int iExtremite=0) const ;

/**
 * Defines the type of relimitation on the input bodies.
 * <br>In case of a fillet between skins.
 * @param iMode
 * The relimitation mode.
 */
  void SetRelimitationMode (CATDynRelimitationMode iMode, int iExtremite=0);


/**
 * Returns the type of the shape of the ribbon on the free boundaries.
 * <br>In case of <tt>CATDynMax</tt> relimitation mode.
 * @return
 * The shape mode.
 */
  CATDynMaxRelimitationOption GetMaxOption (int iExtremite=0) const ;

/**
 * Defines the type of the shape of the ribbon on the free boundaries.
 * <br>In case of <tt>CATDynMax</tt> relimitation mode.
 * @param iMode
 * The shape mode.
 */
  void SetMaxOption (CATDynMaxRelimitationOption iMode, int iExtremite=0);

/**
 * Returns how the ribbon is seewed on the input skins.
 * @return
 * The seewing mode.
 */
  CATDynSewingOption GetSewingOption () const ;

/**
 * Defines how the ribbon is seewed on the input skins.
 * @param iMode
 * The seewing mode.
 */
  void SetSewingOption (CATDynSewingOption iMode);

/**
 * Returns whether the internal ribbon edges are logged inside the journal.
 * @return
 * The report mode.
 */
  CATDynEdgeReporting GetEdgeReportingOption () const ;

/**
 * Defines whether the internal edges are logged inside the journal.
 * @param iMode
 * The report mode.
 */
  void SetEdgeReportingOption (CATDynEdgeReporting iMode);

/**
 * Returns the propagation behavior in case of a multiple automatic propagation ribbons.
 * @return
 * The propagation mode.
 */
  CATDynPropagAutoMode GetPropagAutoMode () const ;

/**
 * Defines the propagation behavior in case of a multiple automatic propagation ribbons.
 * @param iMode
 * The propagation mode.
 */
  void SetPropagAutoMode (CATDynPropagAutoMode iMode);

/**
 * Returns whether keep edges (or rolling edges) are automatically searched in the fillet process.
 * @return
 * The search mode.
 */
  CATDynKeepEdgeMode GetKeepEdgeMode () const ;

/**
 * Defines whether keep edges (or rolling edges) are automatically searched in the fillet process.
 * @param iMode
 * The search mode.
 */
  void SetKeepEdgeMode (CATDynKeepEdgeMode iMode);

  /** @nodoc */
  void SetKeepEdgeSameConvexityMode (const CATDynKeepEdgeSameConvexityMode iMode);

  /** @nodoc */
  void SetCATCreateEndingShell (CATCreateEndingShell CreateEndingShellFct, void* iAnyDataForEndingShellFct=NULL);

  /** @nodoc */
  void SetCATCreateShellForPunch (CATCreateShellForPunch CreateShellFct, void* iAnyDataForShellFct=NULL);

  /** @nodoc */
  virtual void GetSupportBodies(CATLISTP(CATBody) &oSupportBodies) const;

/** @nodoc */
  void SetReconfigFillFunction (CATFilletReconfigFillFunction iFillFct, 
                                const CATBoolean iEnableUseForInnerTwist=FALSE);

/** @nodoc */
  void NoSimplif();
 
/**
 * Returns the kept (or rolling) edges.
 * @return
 * The list of the pointers to the special edges.
 */
  const CATLISTP(CATEdge)& GetSpecialEdges() const;

/**
 * Reads the optional spine of <tt>this</tt> ribbon.
 * @return
 * The pointer to the body containing the spine. 
 */
  const CATBody * GetSpine() const;

  /**
  * Defines the geometric tool of <tt>this</tt> ribbon.
  * @param iToolType
  * The type of tool used for the fillet.
  */
  void SetFilletTool(CATFilletTool iToolType=CATFilletSphereTool);

  /**
 * Reads the geometric tool of <tt>this</tt> ribbon.
 * @return
 * The type of tool used for the fillet.
 */
  const CATFilletTool GetFilletTool() const;

 /**
 * Specifies the radius type. The fillet shape is affected by this parameter.
 */
  void SetFilletRadiusType(CATFilletRadiusType iRadiusType=CATFilletRadiusDefaultType);

 /**
 * Retrieves the radius type.
 */
  const CATFilletRadiusType GetRadiusType() const;

/**
  * Defines the shape of the fillet cross-section.
  * @param iSectionType
  * The section type.
  * @param iConicParameter
  * The tightness value for the conic arc if <tt>iSectionType<tt> is <tt>CATFilletConicalSection<tt>.
  * <br><b>Legal values</b>:
  * <tt>0.0 < iConicParameter < 1.0</tt>. If <tt>iSectionType<tt> is not <tt>CATFilletConicalSection<tt>
  * this parameter is not taken into account.
  */
  void SetFilletSectionType(CATFilletSectionType iSectionType, double iConicParameter=0.5);

  /**
  * Retrieves the shape of the fillet cross-section.
  * @return 
  * The section type.
  */
  CATFilletSectionType GetFilletSectionType() const;

  /**
  * Retrieves the tightness value of the fillet cross-section, if this one is conical.
  * @return 
  * The tightness value for the conic arc if the ribbon section type is <tt>CATFilletConicalSection<tt>.
  * If the section type is not <tt>CATFilletConicalSection<tt> the return value is not relevant.
  */
  double GetConicParameter() const;

  /** @nodoc */
  void GetOptions(CATBody* iPart, CATBlendParams & oBlendParams);

  /** @nodoc */
  void SetNotchRelimitationMode (CATDynRelimitationMode iMode);

  /** @nodoc */
  void SetAutomaticKeepEdgeMode(CATBoolean iOn=TRUE);

/**
* Reads the type of this ribbon.
* @return
* <dl><dt><tt>1</tt></dt><dd>fillet ribbon along an edge.
* <dt><tt>2</tt></dt><dd>fillet ribbon between two faces.
* <dt><tt>3</tt></dt><dd>tri-tangent fillet ribbon.
* <dt><tt>4</tt></dt><dd>Chamfer ribbon.
* </dl>
*/
  virtual const short GetType()=0;

/** @nodoc*/
  CATDynMinRelimitationOption GetMinOption (int iExtremite=0, CATLISTP(CATFace)* oFacesForMinRelimitation= NULL) const ;

/** @nodoc*/
  void SetMinOption (CATDynMinRelimitationOption iMode, int iExtremite=0, const CATLISTP(CATFace)* iFacesForMinRelimitation=NULL );

/** @nodoc*/
  void SetEdgesForMaxRelimitation (const CATLISTP(CATEdge)& iEdges, CATDynMaxRelimitationOption iMode);

/** @nodoc*/
  const CATLISTP(CATEdge)& GetEdgesForMaxRelimitation(CATDynMaxRelimitationOption& oMode) const;

  /**
   * Returns the number of laws implemented for a fillet. 
   * @return
   * The number of laws.
   */
  int  GetNumberOfLaws() const;

  /**
   * Returns the mapping law corresponding to an index
   * @param iIndex
   * Index for which the mapping law is to be retrieved.
   * @return
   * The pointer to mapping law corresponding to the index.
   */
  const CATCompositeLaw*  GetMappingLaw(int iIndex) const;

  /**
   * Returns the distance law corresponding to an index
   * @param iIndex
   * Index for which the distance law is to be retrieved.
   * @return
   * The pointer to distance law corresponding to the index.
  */
  const CATCompositeLaw*  GetDistanceLaw(int iIndex) const;

  /**
   * Defines the smoothing option for the specified law
   * @param iLawId
   * Law identifier from enum CATFilletLawId 
   * @param iLawSmoothingOption
   * Smoothing option: CATTrue - smooth law, CATFalse - no smoothing
   */
  void SetLawSmoothingOption(CATFilletLawId iLawId, CATBoolean iLawSmoothingOption);

  /**
   * Defines the smoothing option for the specified law
   * @param iLawId
   * Law identifier from enum CATFilletLawId 
   * @return
   * Smoothing option: CATTrue - smooth law, CATFalse - no smoothing
   */
  CATBoolean GetLawSmoothingOption(CATFilletLawId iLawId) const;

/** @nodoc*/
  CATBoolean GetIsUpdated() const;
/** @nodoc*/
  void SetIsUpdated(const CATBoolean iIsUpdated);

#ifdef CATIACGMR421CAA
  /** @nodoc */
  void SetPreserveExtremitiesForSheetMetal();

  /** @nodoc */
  CATBoolean GetPreserveExtremitiesForSheetMetal();
#endif

private:

  CATDynKeepEdgeSameConvexityMode GetKeepEdgeSameConvexityMode () const ;
  CATCreateEndingShell GetCATCreateEndingShell (void* & oAnyDataForEndingShellFct) const;
  CATCreateShellForPunch GetCATCreateShellForPunch (void* & oAnyDataForShellFct) const;
  CATFilletReconfigFillFunction GetFilletReconfigFillFunction (CATBoolean &oEnableUseForInnerTwist) const;
  CATDynRelimitationMode  GetNotchRelimitationMode () const ;
  virtual void  GetInitialShells (CATTopData* iData, CATBody* InputBody, CATLISTP(CATShell) &InitialShells)=0;
  const CATBody * GetHoldBody() const;

  virtual void  UpdateInputs (CATTopData* iTopData, CATCGMJournalList& iJournal, CATBody* InputBody, CATBody* iCreationBody, CATCGMJournalList * iOffJournal = 0);
  virtual void  UpdateInputs (const CATLISTP(CATEdge) & iInitialEdges, CATLISTP(CATEdge) & iNewEdges);

  virtual void Dump(CATCGMOutput& os) ;
  virtual void Stream(CATGeoFactory *iFactory, CATCGMStream& os, short iVersion);
  virtual void UnStream(CATGeoFactory *iFactory, CATCGMStream& os, short iVersion, const double iXScaleFactor = 1.);
  CATBoolean GetSkinMode();
  void SetSkinMode(CATBoolean iMode);

  CATBoolean IsAutomaticKeepEdgeModeON();

  CATBoolean _SkinMode;
  CATDynSegmentationMode        _SegmentationMode1;      //Trim/No Trim
  CATDynSegmentationMode        _SegmentationMode2;      //Trim/No Trim
  CATDynRelimitationMode        _StartRelimitationMode;  //Max/Min
  CATDynRelimitationMode        _EndRelimitationMode;    //Max/Min
  CATDynRelimitationMode        _NotchRelimitationMode;  //Max/Min
  
  CATDynMaxRelimitationOption     _StartMaxOption;           //None/Pline/Spline
  CATDynMaxRelimitationOption     _EndMaxOption;             //None/Pline/Spline
  CATDynMinRelimitationOption     _StartMinOption;           //None/Punch
  CATDynMinRelimitationOption     _EndMinOption;             //None/Punch

  CATLISTP(CATEdge)               _EdgesForMaxRelimitation;
  CATDynMaxRelimitationOption     _MaxOptionForEdges;        //None/Pline/Spline

  CATLISTP(CATFace)               _FacesForMinRelimitation;

  CATDynSewingOption              _SewingOption;             //Default/Reverse
  CATDynEdgeReporting             _EdgeReportingOption;      //Default/InternalEdgeReporting
  CATDynPropagAutoMode            _PropagAutoMode;           //Default/StopOnFillet
  CATDynKeepEdgeMode              _KeepEdgeMode;             //Default/Implicit
  CATDynKeepEdgeSameConvexityMode _KeepEdgeSameConvexityMode;//Default(Ignore/RunOn)
  CATCreateEndingShell            _CreateEndingShellFct; 
  void*                           _DataForEndingShellFct;

  CATCreateShellForPunch          _CreateShellForPunchFct;
   void*                          _DataForShellForPunchFct;
  CATFilletReconfigFillFunction   _ReconfigFillFct;
  CATBoolean                      _InnerTwistFill;
  CATBoolean                      _NoSimplif;
  CATBoolean                      _IsUpdated;
#ifdef CATIACGMR421CAA
  CATBoolean                      _PreserveExtremitiesForSheetMetal;
#endif
protected:
  CATBoolean WithNoSimplif();

  CATLISTP(CATEdge)               _special_edges;

  CATBody                       * _SpineBody;
  CATFilletTool                   _FilletToolType;
  CATFilletRadiusType             _RadiusType; 

  CATBody                       * _HoldBody;
  CATDomain                     * _HoldDomain;
  CATOrientation                  _HoldOrientation;

  int                             _NbLaws;
  CATCompositeLaw               **_MappingLaws;
  CATCompositeLaw               **_DistanceLaws;

  CATBoolean                    * _DistanceLawSmoothingOption;

  CATFilletSectionType            _FilletSectionType;
  double                          _ConicParameter;

  CATBoolean                      _IsAutomaticKeepEdgeModeON;

  // Methods for Chain : change the input body y a new one
  virtual void UpdateWithNewBody (CATBody* iOldBody, CATBody* iNewBody);
  CATUnicodeString       GetTypeName() ;
  virtual CATBoolean             IsA(CATDynFilletRibbonType  iRibbonType);  

  friend class CATDynRemoveFaceFilletRibbon;
  friend class CATDynFaceFaceFilletRibbon;
  friend class CATDynEdgeFilletRibbon;
  friend class CATDynChamferRibbon;
  friend class CATDynSolidFilletCGM;
  friend class CATDynSolidChamferCGM;
  friend class CATGMLiveShapeFilletImpl;
  friend class CATGMLiveShapeSingleFilletImpl;
  friend class CATCGMFilletUnit;
  friend class CATlsoRibbonContext;
  friend class CATDynFilletRibbonUtilities; // For implementing GetOptions()
};

/** 
 * @collection CATLISTP(CATDynFilletRibbon)
 * Collection class for pointers to fillet ribbons.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include <CATLISTP_Clean.h>
#include <CATLISTP_PublicInterface.h>
#include <CATLISTP_Declare.h>
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy    ExportedByCATGMOperatorsInterfaces
CATLISTP_DECLARE(CATDynFilletRibbon)

#include "CATDynEdgeFilletRibbon.h"
#include "CATDynFaceFaceFilletRibbon.h"
#include "CATDynRemoveFaceFilletRibbon.h"

#endif
