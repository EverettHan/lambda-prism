// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATGMLiveShapeSelectFaceOpe.cpp
// Header definition of CATGMLiveShapeSelectFaceOpe
//
//===================================================================

//===================================================================
//
//  Jan 2016
//===================================================================
#ifndef CATGMLiveShapeSelectFaceBasicImpl_H
#define CATGMLiveShapeSelectFaceBasicImpl_H

#include "CATAdvancedExtTopOperator.h"
// #include "CATGMLiveShapeSelectFaceOpe.h"
#include "PersistentCell.h"
#include "CATGMLiveShapeSelectFacePropagateMode.h"
#include "CATMathInline.h"
#include "CATMathConstant.h"
#include "CATTopDefine.h"
#include "ListPOfCATContextualManifold.h"
#include "CATFaceHashTable.h"
#include "ListPOfCATDeclarativeManifold.h"

class CATCellHashTable;
class CATCell;
class CATShell;
class CATEdge;
class CATFace;
class CATLiveBody;
class CATContextualManifold;
class CATBoneChamfer;
class CATGMLiveShapeSelectFaceBasicImpl;
class CATlsoCellTree;
class CATDeclarativeManifoldHashTable;


// Pour appeler facilement fonction membre
typedef int (CATGMLiveShapeSelectFaceBasicImpl::*FSameSpecPropagation)(CATContextualManifold *ipRefCM, CATContextualManifold *ipCurCM, ListPOfCATContextualManifold &oPropagatedCMList);

class ExportedByPersistentCell CATGMLiveShapeSelectFaceBasicImpl : public CATAdvancedExtTopOperator
{

public:

  //==============================================================================
  // constructor: do not use, use CATCreateLiveSelectFaceOpe
  //==============================================================================
  /**
  * Constructor : do not use, use CATCreateLiveSelectFaceOpe.<br>
  * <b>Legal Values</b>:<br>
  *	<ul>
  *	  <li> <tt>iTopData</tt> : It represents the information about the configuration and
  *								the journal. If iTopData is NULL , the operator create it.<br>
  *	  <li> <tt>iBody</tt> : The body of the face selection<br>
  *   <li> <tt>iInputFaceList</tt> : The list of the fisrt faces selected<br>
  *   <li> <tt>iPropagationMode</tt> : The type of propagation :<br>
  *     <ul>
  *     <li> PointContinuityPropagationMode,<br>
  *     <li> TangencyContinuityPropagationMode,<br>
  *     <li> DepressionPropagationMode,<br>
  *     <li> ProtrusionPropagationMode,<br>
  *     <li> CellManifoldPropagationMode,<br>
  *     <li> NaturalLocalPropagationMode,<br>
  *     <li> NaturalExtendedPropagationMode,<br>
  *     <li> NaturalDepressionPropagationMode,<br>
  *     <li> NaturalProtrusionPropagationMode,<br>
  *	    </ul>
  *   <li> <tt>iStoppingFaces</tt> : It's optional. The list of the face not to pass through. (Ribbon faces for exemple)<br>
  *	</ul>
  **/   
  CATGMLiveShapeSelectFaceBasicImpl(CATGeoFactory                         & iFactory,
                                    CATBody                               & iBody,
                                    CATSoftwareConfiguration              * iConfig,
                                    const ListPOfCATFace                  & iInputFaceList,
                                    CATGMLiveShapeSelectFacePropagateMode   iPropagationMode,
                                    ListPOfCATFace                        * iStoppingFaces=NULL);

  CATGMLiveShapeSelectFaceBasicImpl(CATGeoFactory                         & iFactory,
                                    CATBody                               & iBody,
                                    CATSoftwareConfiguration              * iConfig,
                                    const ListPOfCATFace                  & iInputFaceList,
                                    CATGMLiveShapeSelectFacePropagateMode   iPropagationMode,
                                    const ListPOfCATCell                  * iStoppingCells);

  // Constructeur avec HashTable
  CATGMLiveShapeSelectFaceBasicImpl(CATGeoFactory                         & iFactory,
                                    CATBody                               & iBody,
                                    CATSoftwareConfiguration              * iConfig,
                                    const CATFaceHashTable                & iInputFaceHT,
                                    CATGMLiveShapeSelectFacePropagateMode   iPropagationMode,
                                    const CATCellHashTable                * iStoppingCells);


  CATGMLiveShapeSelectFaceBasicImpl(CATGeoFactory                         & iFactory,
                                    CATBody                               & iBody,
                                    CATSoftwareConfiguration              * iConfig,
                                    const ListPOfCATFace                  & iInputFaceList,
                                    CATGMLiveShapeSelectFacePropagateMode   iPropagationMode,
                                    const ListPOfCATFace                  & iSubBodyFilterFaceList);


  //CATGMLiveShapeSelectFaceBasicImpl(CATGeoFactory                         & iFactory,
  //                                CATPersistentBody                       & iPersistentBody,
  //                                CATSoftwareConfiguration                * iConfig,
  //                                CATPersistentCellInfra                  & iPersistentInfra,
  //                                const ListPOfCATFace                    & iInputFaceList,
  //                                CATGMLiveShapeSelectFacePropagateMode     iPropagationMode,
  //                                ListPOfCATFace                          * iStoppingFaces);

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;

  //==============================================================================
  // destructor 
  //==============================================================================
  /**
  * Standard destructor.<br>
  **/
  virtual ~CATGMLiveShapeSelectFaceBasicImpl();

  //==============================================================================
  // Define propagation mode
  //==============================================================================
  // Les modes complementaire sont-ils a faire ?
  enum PropagationMode { POINT_CONTINUITY=0, TANGENCY_CONTINUITY, DEPRESSION, PROTRUSION, CELLMANIFOLD, NATURAL_LOCAL, NATURAL_EXTENDED,
    NATURAL_DEPRESSION, NATURAL_PROTRUSION};

  // For 2.3 degree, set 0.04 rad
  // For 0.5 degree, set 0.0087 rad
  // For 90  degree, set 1.57 rad
  INLINE void SetTangencyMaxRadAngle(CATAngle iRadAngle);
  INLINE void SetTangencyMaxRadAngleWithConvexity(CATAngle iRadConvexAngle, CATAngle iRadConcaveAngle);
  INLINE void SetTestTypeMode(CATBoolean iTestTypeMode);

 /**
  * Choose your own function to run the SelectFace propagation. 
  */
  HRESULT SetCustomPropagationFunction(CLSSFPropagationFunction   iFunct,
                                       const char               * iFunctionName = NULL /*cgmreplay purpose*/,
                                       const char               * iLibName      = NULL /*cgmreplay purpose*/); 

  void SetStoppingCellList(const ListPOfCATCell & iStoppingCellList);
  void SetStoppingCellList(const CATCellHashTable & iStoppingCellHT);

  //==============================================================================
  // Run
  //==============================================================================
  /**
  * Execute ComputConstraints, then RunOnSubBody onve for each SubBody, and then RunJoin.
  **/
  // int Run();

  //==============================================================================
  // GetFaceListResult
  //==============================================================================
  void GetFaceListResult(ListPOfCATFace & oResultFaceList) const;

  void GetFaceListResult(CATCellHashTable & oResultFaceHT) const;

  static const char * GetPropagationName(CATGMLiveShapeSelectFacePropagateMode iPropagationMode);


  //==============================================================================
  //
  // CGMREPLAY METHODES
  //
  //==============================================================================
  // Operator generic name for the CGMReplay
  static CATString _OperatorName;

  virtual void RequireDefinitionOfInputAndOutputObjects();
  virtual CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  virtual const CATString * GetOperatorId() const { return &_OperatorName; }
  static const CATString * GetDefaultOperatorId() { return &_OperatorName; }
  CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

  void         DumpOutput (CATCGMOutput &os);
  virtual void WriteInput (CATCGMStream  & iStr);
  virtual void ReadInput  (CATCGMStream  & ioStream,int VersionOfStream, short & oNumReplayVersion);
  virtual void Dump       (CATCGMOutput& os) ;
  void         WriteOutput(CATCGMStream & ioStream);

  CATBoolean   ValidateTopOutput   (CATTopCheckJournal* iEquivalent, CATCGMOutput& os);
  CATBoolean   ValidateOutput      (CATCGMStream & Str, CATCGMOutput & os, int VersionNumber=1);
  CATBoolean   ReadReferenceOutput (CATCGMStream &Str);
  void         DumpOutput          (CATCGMStream & Str , CATCGMOutput & os , int VersionNumber);

  // virtual int RunPersistentOperator();

  static CATCGMOperator * CATLoadGMLiveShapeSelectFaceBasic(CATCGMStream & Str,
    const short iLevelOfRuntime,
    const short iVersionOfStream, int iOperatorId);
 

protected :

  //==============================================================================
  // copy constructor
  //==============================================================================
  /**
  * Copy constructor: Not implemented. <br>
  **/
  CATGMLiveShapeSelectFaceBasicImpl (const CATGMLiveShapeSelectFaceBasicImpl &);


  // For CGMReplay
  // -----------------------------------------------------------------------------
  void SetInputFaceList(const ListPOfCATFace & iInputFaceList);
  void SetPropagationMode(CATGMLiveShapeSelectFacePropagateMode iPropagationMode);
  void SetStoppingFacesList(const ListPOfCATFace & iStoppingFaces);
  INLINE void SetSubBodyFilterFaceList(const ListPOfCATFace & iSubBodyFilterFaceList);
  INLINE void SetReferenceInputFaceList(ListPOfCATFace & iRefResultFaceList);
  INLINE void SetTestTypeIsRight(CATBoolean iTestTypeIsRight);

  INLINE CATBody                * GetSelectInputBody() const;
  INLINE const CATFaceHashTable & GetInputFaceHT() const;
	INLINE const CATFaceHashTable & GetResultFaceHT() const { return _ResultFaceHashTable; }
  INLINE const ListPOfCATFace   & GetSubBodyFilterFaceList() const;
  INLINE CATBoolean               GetNoSharpEdgeMode() const;
  const ListPOfCATCell          & GetStoppingCellList() const;

  INLINE const CLSSFPropagationFunction & GetUserPropagFunction() const {
    return _UserPropagFunct; }
  INLINE const CATUnicodeString * GetUserPropFunctName() const { return _UserPropFunctName; }
  INLINE const CATUnicodeString * GetUserPropFunctLib()  const { return _UserPropFunctLib; }

  INLINE double GetTangencyMaxRadConvexAngle() const;
  INLINE double GetTangencyMaxRadConcaveAngle() const;

  int AppendResultFace (const CATFaceHashTable &iFaceHashTable);
  int AppendResultFace (const ListPOfCATFace &iListOfInputFaces);
  int AppendResultFace (CATFace * iFace);

  void CreateHashTable(const ListPOfCATFace &iListOfInputFaces);
  
  // ---------------------------------------------------------------------
  // Virtual methods 
  // ---------------------------------------------------------------------
  //======================================================================
  // Main Run
  //======================================================================
  virtual int RunAdvancedOperator();

  void InitBasicParameters();
  virtual int   Initialisation();

  void CellManifoldPropagation();
  void DeclarativePropagation(ListPOfCATDeclarativeManifold * oDeclarativeManifolds=NULL); 
  void DeclarativePropagation(ListPOfCATDeclarativeManifold & oDeclManifoldList, CATGeometricType *iCheckFilterType=NULL);
  void DeclarativePropagation(CATDeclarativeManifoldHashTable * oDeclarativeManifoldHT=NULL);

  void NeighborhoodPropagation();
  void RibbonImpactPropagation();
  int  RibbonSameSpecPropagation();
  // Cette fonction utilise un pointeur sur function (dont le type est definit plus haut) comme argument.
  int  GenericSameSpecPropagation(FSameSpecPropagation ptr_function, CATGeometricType *iGeoFilterType=NULL);  
  
  CATBoolean CheckOneFaceHasRightConvexity(ListPOfCATFace iFaceList,const int  iDepProType);  // 0=>Depression, 1=>Protrusion
  
  // =============================================================================
  // Sub Run
  // =============================================================================
  int RunBasicSelectFace();

  // =============================================================================
  // Propagation
  // =============================================================================
  int        ClassicalPropagation();
  int        NoSharpPropagation();
  int        DealWithNoSharpEdgeMode(const CATFaceHashTable &iForbiddenFaceHT);
  int        Propagate(CATCell * iFace, CATShell* iCurrShell, CATCellHashTable *  &ioVisitedEdges);
  // NoSharp
  int        ExhaustivePropagate(CATFace * iFace, CATShell* iCurrShell, CATCellHashTable *  &ioVisitedEdges, CATFaceHashTable & oRefusedFaceHT);
  int        PropagationByTree(const CATFaceHashTable &iFaceHT, CATShell* iCurrShell, CATlsoCellTree & ioPropagCellTree, CATEdgeHashTable & ioVisitedEdges); // En test
  int        PropagationByTreeMin(CATFace * iFace, CATShell* iCurrShell, CATlsoCellTree & ioPropagCellTree, CATCellHashTable *& ioVisitedEdges);

  CATBoolean PropagationChoise(CATEdge  & iCurrEdge, CATFace  * iThisFace, CATFace  * iNextFace, CATShell * iCurrShell);

  int        PropagateSameRibbonSpec (CATContextualManifold *ipRefCM, CATContextualManifold * ipCMToPropagate, ListPOfCATContextualManifold &oPropagatedCMList);

  // Characteristic geometry - Visu - Selection the"best" face amont inputfaces
  // ---------------------------------------------------------------------------
  int        ChooseFaceForVisualization();

  //===================================================================
  // PropagationChoiseOnFilletFace
  // return TRUE if the face is a datum
  //                or
  //             if the face is not on live body
  //===================================================================
  CATBoolean PropagationChoiseOnLiveFilletFace(CATFace * iFace, CATFace * iNeighborSelectedFace=NULL);

  void RemoveJointFilletFromInputFacelist();
  void FillInResultFaceList();

  CATCellHashTable & GetFacePropHT() const;
  INLINE void SetNeedToContinue(CATBoolean iValue);
  INLINE CATGMLiveShapeSelectFacePropagateMode GetPropagationMode() const;

  //===================================================================
  // Runs CATTopGN_CommonEdges service
  // Only available with set CATSelectFace_TopGNCommonEdges=1
  // The current TopGNCommonEdges should also be activated via either 
  //  set NewCommonEdges=1                  for the 'new version' or
  //  set CATTopGN_CommonEdges_OldVersion=1 for the 'old version'
  // 
  // This method is temporary to test the service.
  // 
  // 1) Splits the list of selected faces into 3 sub lists
  // 2) Runs the CATIPGMTopGNCommonEdges on the sub lists (only a Dump of elements is done)
  // 3) Memory Cleaning
  //===================================================================
  void RunTopGNCommonEdges() const;

  // -----------------------------------------------------------------------------
  // Utilities 
  // -----------------------------------------------------------------------------
  void GetNeighborBoneChamfer(CATLiveBody *iLiveBody, const CATBoneChamfer *iBoneChamfer, ListPOfCATContextualManifold &oNeighborChamferList );
  CATBoolean HasSameSpec(const CATBoneChamfer *iBoneChamferA, const CATBoneChamfer *iBoneChamferB) const;

  //==============================================================================
  // Equal operator
  //==============================================================================
  /**
  * Equal operator : Not implemented. <br>
  **/
  CATGMLiveShapeSelectFaceBasicImpl& operator=(CATGMLiveShapeSelectFaceBasicImpl&);




  //==============================================================================
  // Data
  //==============================================================================
  CATBody         * _InputBody;
  CATFaceHashTable  _InputFaceHashTable; // New structure for inputfaces. For perfo.
//  ListPOfCATFace    _InputFaceList;      // To remove
  CATFaceHashTable  _ResultFaceHashTable; // New structure for inputfaces. For perfo.
  ListPOfCATCell    _StoppingCellList;    // Edges for now ( + Face ongoing ).
  ListPOfCATFace    _BorderRibbonFaceList;
  ListPOfCATFace    _JointFilletFaceList;
  ListPOfCATFace    _SubBodyFilterFaceList;
  ListPOfCATFace    _ReferenceResultFaceList;

  // CLSSFPropagationFunction -> std::function<CATBoolean(CATBody *ipBody, CATEdge *iCurrEdge, CATFace * iCurrFace, CATFace *iNextFace, CATShell * iCurrShell)>
  CLSSFPropagationFunction  _UserPropagFunct;
  CATUnicodeString        * _UserPropFunctName; // cgmreplay
  CATUnicodeString        * _UserPropFunctLib;  // cgmreplay

  
  CATGMLiveShapeSelectFacePropagateMode   _PropagationMode;

  CATCellHashTable  * _FacesProp;           // Faces for propagation.
  CATBoolean          _SharpnessProp;       // TRUE if sharpness propagation to do. (without smooth propagation)
  CATBoolean          _TangProp;            // TRUE if tangency propagation to do.
  CATBoolean          _PointProp;           // TRUE if point propagation to do.
  CATBoolean          _NoSharpEdge;         // for _TangProp. if TRUE, no sharp edge on result propagated faces.
  CATBoolean          _CellManifoldProp;    // TRUE if cell manifold propagation to do.
  CATTopConvexity     _PropagateOnSharpEdgesUsingConvexity; // if != UnknownConvexity, operator will also propagate
  // on sharp edges using stored convexity

  CATBoolean          _TangencyMaxRadAngleIsSet;
  CATAngle            _TangencyMaxRadAngle;
  CATBoolean          _TangencyMaxRadAngleWithConvexityIsSet;
  CATAngle            _TangencyMaxRadConvexAngle;
  CATAngle            _TangencyMaxRadConcaveAngle;

  CATBoolean          _TestTypeMode;
  CATBoolean          _TestTypeIsRight;
  CATBoolean          _NeedToContinue;

  CATLiveBody       * _LiveBody;
};



//==============================================================================
// CATCreateLiveSelectFaceBasicImp
//==============================================================================
/**
* Create operator, it call the constructor.<br>
* <b>Legal Values</b>:<br>
*	<ul>
*	  <li> <tt>iTopData</tt> : It represents the information about the configuration and
*								the journal. If iTopData is NULL , the operator create it.<br>
*	  <li> <tt>iBody</tt> : The body of the face selection<br>
*   <li> <tt>iInputFaceList</tt> : The list of the fisrt faces selected<br>
*   <li> <tt>iPropagationMode</tt> : The type of propagation :<br>
*     <ul>
*     <li> PointContinuityPropagationMode,<br>
*     <li> TangencyContinuityPropagationMode,<br>
*     <li> DepressionPropagationMode,<br>
*     <li> ProtrusionPropagationMode,<br>
*     <li> CellManifoldPropagationMode,<br>
*     <li> NaturalLocalPropagationMode,<br>
*     <li> NaturalExtendedPropagationMode,<br>
*     <li> NaturalDepressionPropagationMode,<br>
*     <li> NaturalProtrusionPropagationMode,<br>
*    </ul>
*   <li> <tt>iStoppingFaces</tt> : It's optional. The list of the face not to pass through. (Ribbon faces for exemple)<br>
*  </ul>
**/   
ExportedByPersistentCell CATGMLiveShapeSelectFaceBasicImpl * CATCreateLiveSelectFaceBasicImp(CATBody                            * iBody, 
                                                              ListPOfCATFace                      & iInputFaceList, 
                                                              CATGMLiveShapeSelectFacePropagateMode iPropagationMode, 
                                                              ListPOfCATFace                      * iStoppingFaces=NULL);


//==============================================================================
// Inline Methodes
//==============================================================================
INLINE CATBody * CATGMLiveShapeSelectFaceBasicImpl::GetSelectInputBody() const {
  return _InputBody; }

INLINE const CATFaceHashTable & CATGMLiveShapeSelectFaceBasicImpl::GetInputFaceHT() const {
  return _InputFaceHashTable; }

INLINE const ListPOfCATFace & CATGMLiveShapeSelectFaceBasicImpl::GetSubBodyFilterFaceList() const {
  return _SubBodyFilterFaceList; }

INLINE CATBoolean CATGMLiveShapeSelectFaceBasicImpl::GetNoSharpEdgeMode() const {
  return _NoSharpEdge; }

INLINE void CATGMLiveShapeSelectFaceBasicImpl::SetSubBodyFilterFaceList(const ListPOfCATFace & iSubBodyFilterFaceList) {
  _SubBodyFilterFaceList.Append(iSubBodyFilterFaceList); }

INLINE void CATGMLiveShapeSelectFaceBasicImpl::SetReferenceInputFaceList(ListPOfCATFace & iRefResultFaceList) {
  _ReferenceResultFaceList = iRefResultFaceList; }

INLINE void CATGMLiveShapeSelectFaceBasicImpl::SetTestTypeMode(CATBoolean iTestTypeMode) {
  _TestTypeMode = iTestTypeMode; }

INLINE void CATGMLiveShapeSelectFaceBasicImpl::SetTestTypeIsRight(CATBoolean iTestTypeIsRight) {
  _TestTypeIsRight = iTestTypeIsRight; }

INLINE void CATGMLiveShapeSelectFaceBasicImpl::SetNeedToContinue(CATBoolean iValue) {
  _NeedToContinue = iValue; }

INLINE CATGMLiveShapeSelectFacePropagateMode CATGMLiveShapeSelectFaceBasicImpl::GetPropagationMode() const {
  return _PropagationMode; }

INLINE double CATGMLiveShapeSelectFaceBasicImpl::GetTangencyMaxRadConvexAngle() const {
  return _TangencyMaxRadConvexAngle;
}

INLINE double CATGMLiveShapeSelectFaceBasicImpl::GetTangencyMaxRadConcaveAngle() const {
  return _TangencyMaxRadConcaveAngle;
}

// For 2.3 degree, set 0.04 rad
// For 0.5 degree, set 0.0087 rad
// For 90  degree, set 1.57 rad
INLINE void CATGMLiveShapeSelectFaceBasicImpl::SetTangencyMaxRadAngle(CATAngle iRadAngle) {
  _TangencyMaxRadAngle = iRadAngle; 
  _TangencyMaxRadAngleIsSet = TRUE; }


INLINE void CATGMLiveShapeSelectFaceBasicImpl::SetTangencyMaxRadAngleWithConvexity(CATAngle iRadConvexAngle, CATAngle iRadConcaveAngle) {
  _TangencyMaxRadConvexAngle = iRadConvexAngle;
  _TangencyMaxRadConcaveAngle = iRadConcaveAngle;
  _TangencyMaxRadAngleWithConvexityIsSet = TRUE; }

#endif

