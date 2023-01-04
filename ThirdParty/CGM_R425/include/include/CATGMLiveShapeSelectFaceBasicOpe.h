// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : L. Marini 
//
// DESCRIPTION  : Face selection operator for CATIA Live Shape.
//                It detect logicaly the depresion and the protrusion.
//
//=============================================================================
// Creation LAP July 2007
//
//=============================================================================
#ifndef CATGMLiveShapeSelectFaceBasicOpe_H
#define CATGMLiveShapeSelectFaceBasicOpe_H

#include "PersistentCell.h" // pour access dans la dll

#include "CATGMLiveShapeSelectFacePropagateMode.h"
#include "CATAdvancedOperator.h"

#include "ListPOfCATFace.h"
#include "CATListOfCATCells.h"

class CATGMLiveShapeSelectFaceBasicImpl;
class CATSoftwareConfiguration;
class CATCellHashTable;


/**
* This class is used to select faces with.<br>
**/
class ExportedByPersistentCell CATGMLiveShapeSelectFaceBasicOpe : public CATAdvancedOperator
{
  CATCGMVirtualDeclareClass(CATGMLiveShapeSelectFaceBasicOpe);

public:

  //==============================================================================
  // constructor: do not use, use CATCreateLiveSelectFaceBasicOpe
  //==============================================================================
  /**
  * Constructor : do not use, use CATCreateLiveSelectFaceBasicOpe.<br>
  * <b>Legal Values</b>:<br>
  * <ul>
  *   <li> <tt>iTopData</tt> : It represents the information about the configuration and
  *            the journal. If iTopData is NULL , the operator create it.<br>
  *   <li> <tt>iBody</tt> : The body of the face selection<br>
  *   <li> <tt>iInputFaceList</tt> : The list of the fisrt faces selected<br>
  *   <li> <tt>iPropagationMode</tt> : The type of propagation :<br>
  *   <ul>
  *     <li> PointContinuityPropagationMode,<br>
  *     <li> TangencyContinuityPropagationMode,<br>
  *     <li> DepressionPropagationMode,<br>
  *     <li> ProtrusionPropagationMode,<br>
  *   </ul>
  *   <li> <tt>iStoppingFaces</tt> : It's optional. The list of the face not to pass through. (Ribbon faces for exemple)<br>
  *  </ul>
  **/
  // @nocgmitf
  CATGMLiveShapeSelectFaceBasicOpe(CATGeoFactory * iFactory,  CATTopData * iTopData, CATGMLiveShapeSelectFaceBasicImpl  * iImp);

  //==============================================================================
  // destructor 
  //==============================================================================
  /**
  * Standard destructor.<br>
  **/
  // @nocgmitf
  virtual ~CATGMLiveShapeSelectFaceBasicOpe();

  // @nocgmitf
  //==============================================================================
  // Modify the definition of smooth edge with a max rad angle.
  // It's designed for the mode CLSSF_TANGENCY_CONTINUITY
  // For 2.3 degree, set 0.04 rad
  // For 0.5 degree, set 0.0087 rad
  //==============================================================================
  // @nocgmitf
  void SetTangencyMaxRadAngle(CATAngle iRadAngle);
  // @nocgmitf
  void SetStoppingCellList(const ListPOfCATCell & iStoppingCellList);
  // @nocgmitf
  void SetStoppingCellList(const CATCellHashTable & iStoppingCellHT);


  /**
  * Choose your own function to run the SelectFace propagation. 
  * This operator must have been created with the mode CLSSF_CUSTOM_PROPAG_FUNCTION.
  * 
  * The function will be called on each face to be propagated. 
  * CLSSFPropagationFunction is defined in CATGMLiveShapeSelectFacePropagateMode.h,
  *   --> std::function<CATBoolean(CATBody *ipBody, CATEdge *iCurrEdge, CATFace * iCurrFace, CATFace *iNextFace, CATShell * iCurrShell)>
  * 
  * Function ordered @parameters
  *   - ipBody    : the operator input body (given at contructor step). 
  *   - iCurrEdge : the current bounding edge between iCurrFace and iNextFace. 
  *   - iCurrFace : the current face to propagate from. 
  *   - iNextFace : the candidate face to propagate to. 
  *   - iCurrShell : the shell owning iCurrFace and iNextFace. 
  *
  * Function @return
  *   - CATBoolean : if TRUE, propagation from iCurrFace to iNextFace is accomplished. 
  *                  if FALSE, propagation won't go beyond iNextFace. 
  *
  ** @nocgmitf */
  HRESULT SetCustomPropagationFunction(CLSSFPropagationFunction   iFunct                  /*defined in CATGMLiveShapeSelectFacePropagateMode.h*/,
                                       const char               * iFunctionName = NULL /*cgmreplay purpose*/,
                                       const char               * iLibName      = NULL/*cgmreplay purpose*/); 

  //==============================================================================
  // GetFaceListResult
  //==============================================================================
  // @nocgmitf
  void GetFaceListResult(ListPOfCATFace & oResultFaceList) const;
   // @nocgmitf
  void GetFaceListResult(CATCellHashTable & oResultFaceHT) const;
  // @nocgmitf
  static const char * GetPropagationName(CATGMLiveShapeSelectFacePropagateMode iPropagationMode);


  //==============================================================================
  // Bridage Propagation
  //==============================================================================
  // @nocgmitf
  static CATBoolean CheckAdmissiblePropagation(const CATGMLiveShapeSelectFacePropagateMode &iPropagationMode);

  //==============================================================================
  //
  // CGMREPLAY METHODES
  //
  //==============================================================================
  /** @nodoc @nocgmitf declaration integre au CGMReplay */
  void RequireDefinitionOfInputAndOutputObjects();
  /** @nodoc @nocgmitf */
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  virtual const CATString * GetOperatorId();
  /** @nodoc @nocgmitf */
  static const CATString * GetDefaultOperatorId();
  /** @nodoc @nocgmitf */
  void DumpOutput(CATCGMOutput &os);
  /** @nodoc @nocgmitf */
  virtual void WriteInput(CATCGMStream  & os);
  /** @nodoc @nocgmitf */
  virtual void ReadInput(CATCGMStream  & ioStream,int VersionOfStream, short & oNumReplayVersion);
  /** @nodoc @nocgmitf */
  virtual void Dump( CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  // virtual int RunOperator();

  // @nocgmitf
  void DumpOutput(CATCGMStream & Str , CATCGMOutput & os , int iVersionNumber=1);
  /** @nodoc @nocgmitf */
  CATBoolean ReadReferenceOutput(CATCGMStream &Str);
  /** @nodoc @nocgmitf */
  void WriteOutput(CATCGMStream & ioStream);
  /** @nodoc @nocgmitf */
  CATBoolean ValidateTopOutput(CATTopCheckJournal* iEquivalent, CATCGMOutput& os);
  // @nocgmitf
  CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
  // @nocgmitf
  CATBoolean ValidateOutput(CATCGMStream & Str, CATCGMOutput & os, int VersionNumber=1);
  // @nocgmitf
  void SetTestTypeMode(CATBoolean iTestTypeMode);

protected:
  CATGMLiveShapeSelectFaceBasicImpl * GetCATGMLiveShapeSelectFaceBasicImpl() const;


private :

  //==============================================================================
  // copy constructor
  //==============================================================================
  /**
  * Copy constructor: Not implemented. <br>
  **/
  CATGMLiveShapeSelectFaceBasicOpe (CATGMLiveShapeSelectFaceBasicOpe &);


  //==============================================================================
  // Equal operator
  //==============================================================================
  /**
  * Equal operator : Not implemented. <br>
  **/
  CATGMLiveShapeSelectFaceBasicOpe& operator=(CATGMLiveShapeSelectFaceBasicOpe&);


  //==============================================================================
  // Data
  //==============================================================================

};

//==============================================================================
// CATGMLiveShapeSelectFaces
//==============================================================================
/**
* static methode to get the directly the ResultFaceList<br>
* <b>Legal Values</b>:<br>
*  <ul>
*    <li> <tt>iBody</tt> : The body of the face selection<br>
*   <li> <tt>iInputFaceList</tt> : The list of the fisrt faces selected<br>
*   <li> <tt>iPropagationMode</tt> : The type of propagation :<br>
*     <ul>
*     <li> PointContinuityPropagationMode,<br>
*     <li> TangencyContinuityPropagationMode,<br>
*     <li> DepressionPropagationMode,<br>
*     <li> ProtrusionPropagationMode,<br>
*      </ul>
*   <li> <tt>oResultFaceList</tt> : It's the result The list of the faces selected after propagation<br>
*   <li> <tt>iStoppingFaces</tt> : It's optional. The list of the face not to pass through. (Ribbon faces for exemple)<br>
*  </ul>
**/   

ExportedByPersistentCell HRESULT CATGMLiveShapeSelectFacesBasic(
                             CATBody                                 * iBody,
                             const ListPOfCATFace                    & iInputFaceList,
                             CATGMLiveShapeSelectFacePropagateMode     iPropagationMode,
                             ListPOfCATFace                          & oResultFaceList,
                             ListPOfCATFace                          * iStoppingFaces/*=NULL*/,
                             CATBoolean                                iLiveBodyAllowed/*=TRUE*/,
                             CATSoftwareConfiguration                * iConfig/*=NULL*/,
                             CATBoolean                                iTestTypeMode=FALSE);// VB7 - for Protrusion or depression test. Throw an error if propagated faces are added to input face list.

ExportedByPersistentCell HRESULT CATGMLiveShapeSelectFacesBasic(
                             CATBody                                 * iBody,
                             const ListPOfCATFace                    & iInputFaceList,
                             CATGMLiveShapeSelectFacePropagateMode     iPropagationMode,
                             ListPOfCATFace                          & oResultFaceList,
                             ListPOfCATFace                          & iSubBodyFilterFaceList,
                             CATBoolean                                iLiveBodyAllowed/*=TRUE*/,
                             CATSoftwareConfiguration                * iConfig/*=NULL*/);


//==============================================================================
// CATGMLiveShapeSelectFacesWithAnglePropagation
// For 2.3 degree, set 0.04 rad
// For 0.5 degree, set 0.0087 rad
// For 90  degree, set 1.57 rad
//==============================================================================
ExportedByPersistentCell HRESULT CATGMLiveShapeSelectFacesWithAnglePropagationBasic(
                             CATBody                                 * iBody,
                             const ListPOfCATFace                    & iInputFaceList,
                             CATAngle                                  iPropagationMaxRadAngle,
                             ListPOfCATFace                          & oResultFaceList,
                             CATSoftwareConfiguration                * iConfig,
                             CATBoolean                                iLiveBodyAllowed=FALSE,
                             ListPOfCATFace                          * iSubBodyFilterFaceList=NULL);



//==============================================================================
// CATCreateLiveSelectFaceBasicOpe
//==============================================================================
/**
* Create operator, it call the constructor.<br>
* <b>Legal Values</b>:<br>
*  <ul>
*    <li> <tt>iTopData</tt> : It represents the information about the configuration and
*                the journal. If iTopData is NULL , the operator create it.<br>
*    <li> <tt>iBody</tt> : The body of the face selection<br>
*   <li> <tt>iInputFaceList</tt> : The list of the fisrt faces selected<br>
*   <li> <tt>iPropagationMode</tt> : The type of propagation :<br>
*     <ul>
*     <li> PointContinuityPropagationMode,<br>
*     <li> TangencyContinuityPropagationMode,<br>
*     <li> DepressionPropagationMode,<br>
*     <li> ProtrusionPropagationMode,<br>
*      </ul>
*   <li> <tt>iStoppingFaces</tt> : It's optional. The list of the face not to pass through. (Ribbon faces for exemple)<br>
*  </ul>
**/
// To be replaced by new constructor (I).
ExportedByPersistentCell CATGMLiveShapeSelectFaceBasicOpe * CATCreateLiveSelectFaceBasicOpe(
                             CATTopData                            * iTopData,
                             CATBody                               * iBody,
                             const ListPOfCATFace                  & iInputFaceList,
                             CATGMLiveShapeSelectFacePropagateMode   iPropagationMode,
                             ListPOfCATFace                        * iStoppingFaces=NULL);

// new constructor (I) with cells.
ExportedByPersistentCell CATGMLiveShapeSelectFaceBasicOpe * CATCreateLiveSelectFaceBasicOpe(
                             CATTopData                            * iTopData,
                             CATBody                               * iBody,
                             const ListPOfCATFace                  & iInputFaceList,
                             CATGMLiveShapeSelectFacePropagateMode   iPropagationMode,
                             const ListPOfCATCell                  * iStoppingCells); // could be edges or faces.

// with SubBodyFilterFaceList
// @nocgmitf
ExportedByPersistentCell CATGMLiveShapeSelectFaceBasicOpe * CATCreateLiveSelectFaceBasicOpe(
                             CATTopData                            * iTopData,
                             CATBody                               * iBody,
                             const ListPOfCATFace                  & iInputFaceList,
                             CATGMLiveShapeSelectFacePropagateMode   iPropagationMode,
                             const ListPOfCATFace                  & iSubBodyFilterFaceList);

// @nocgmitf
//ExportedByPersistentCell CATGMLiveShapeSelectFaceBasicOpe * CATCreateLiveSelectFaceBasicOpe(
//                              CATTopData                            * iTopData,
//                              CATPersistentBody                     * iPersistentBody,
//                              CATPersistentCellInfra                & iInfra,
//                              const ListPOfCATFace                  & iInputFaceList,
//                              CATGMLiveShapeSelectFacePropagateMode   iPropagationMode,
//                              ListPOfCATFace                        * iStoppingFaces);

#endif

