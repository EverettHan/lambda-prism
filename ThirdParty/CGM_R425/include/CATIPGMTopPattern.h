#ifndef CATIPGMTopPattern_h_
#define CATIPGMTopPattern_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATDynOperatorDef.h"

class CATBody;
class CATCGMJournalList;
class CATLISTP_CATCGMJournalInfo_;
class CATLISTP_CATMathTransformation_;
class CATMathTransformation;
class CATPlane;
class CATTopData;
class CATLISTP(CATFace);
class CATLISTP(CATCGMJournalInfo);
class CATLISTP(CATMathTransformation);
class CATLISTP(CATCGMJournal);
class CATTopPatternData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopPattern;

/**
* Class dedicated to pattern operations. 
* The pattern operation consists in creating multiple instances of an object
* according to a transformation. 
* A pattern can be a:
* <ul>
* <li>user pattern: the way the object is repeated is defined by a list of transformations
* which is specified in the operator creation function.
* <li>a rectangular pattern which is created by repeating an object along two directions. 
* <li>a circular pattern is created by repeating an object around an axis at various distances.
* </ul>
* <p>
* Whatever the pattern type, the list of tranformations is to be specified. 
* For rectangular and circular patterns, it is recommended to use the <tt>SetRectPattern<\tt>
* and <tt>SetCirPattern<\tt> settings in addition to the list of transformations passed to the creation function.
* This prevents the operator algorithm to launch useless computations. The performances are then enhanced.
* <p>
* The <tt>CATIPGMTopPattern</tt> operator follows the global frame of topological operators and satisfies the smart mechanism: 
* the input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input body.
* <ul>
* <li>A <tt>CATIPGMTopPattern</tt> operator is created with the <tt>CATPGMCreateTopPattern</tt> global method:
* It must be directly <tt>delete</tt>d after use. It is not streamable. 
* <li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method
* <li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory. 
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopPattern: public CATIPGMTopOperator
{
public:
	/**
	* Constructor
	*/
	CATIPGMTopPattern();

	/**
	* @nodoc
	* Defines the shape of the pattern. If the input iUpdateJournal is different from 0, the journal
	* will be updated.
	*/
	virtual CATBody *GetShape(int iUpdateJournal = 0) = 0;

	/**
	* Defines a canonical rectangular pattern. This method is to be used
	* in addition to the list of transformations (better performances).
	* @param NumberOfRows
	* The number of rows.
	* @param RowTransfo
	* The transformation to be applied to the object to pattern in the rows. It must not be
	* set to <tt>NULL</tt> except if there is only one row.
	* @param NumberOfColumns
	* The number of columns.
	* @param ColumnsTransfo
	* The transformation to be applied to the object to pattern in the columns. It must not be
	* set to <tt>NULL</tt> except if there is only one column.
	*/
	virtual void SetRectPattern(
		int NumberOfRows,
		CATMathTransformation *RowTransfo,
		int NumberOfColumns,
		CATMathTransformation *ColumnsTransfo) = 0;

	/**
	* Defines a canonical circular pattern. This method is to be used
	* in addition to the list of transformations (better performances).
	* @param NumberOfRows
	* The number of circular rows.
	* @param RowTransfo
	* The anguler transformation to be applied to the object to pattern in the circular rows. It must not be
	* set to <tt>NULL</tt> except if there is only one row.
	* @param NumberOfColumns
	* The number of columns. The columns are sets of instances located along the circle radii.
	* @param ColumnsTransfo
	* The radius transformation to be applied to the object to pattern. It must not be
	* set to <tt>NULL</tt> except if there is only one column.
	*/
	virtual void SetCirPattern(
		int NumberOfRows,
		CATMathTransformation *RowTransfo,
		int NumberOfColumns,
		CATMathTransformation *ColumnsTransfo) = 0;

#if defined (CATIACGMR214CAA)
  /**
	* @nodoc
	* Allows to compute all instances in case of pattern faces mode.
	* Without this option , operator works when faces can be sew in invariant geometric / topological mode.
	* With this option , additional boolean operation will be done on remaining instances.
	* @param iFullResultMode
	* The type of result mode can be : 
	* <dl>
	* <dt>0</dt><dd>Only invariant geometric / topological instances can be computed ( model duplication , default mode ).
	* <dt>1</dt><dd>All instances will be computed ( this is now the recommanded mode ).
	* </dl>
	* This option apply only and is the default mode for volumic bodies.
	*/
  virtual void SetPatternFacesResultMode(const int iFullResultMode) = 0;

#endif
#ifdef CATIACGMV5R23
  /**
	* Allows partial result in case of pattern faces mode.
	* In this case the result body may contain only the result of some transformation because 
	* transformation works only when faces can be sew in invariant geometric / topological mode.
	* Note : however , even in this mode , if all transformation failed , the operator will return an error.
	*/
  virtual void SetPartialResultAllowed() = 0;

  /**
	* Get the number of invalid transformation in case when partial result mode is active for pattern faces
	*
	* This service is useful after "Run" only in case of "SetPartialResultAllowed".
	* If partial result situation detected , the service the numbers of invalid transformation.
	*
	* @param oListTransfoStatus
	* The list will be filled for a value for each transformation :
	* <ul>
	* <li> CATPatternOKWithSewing      : if instance OK ( made by sewing , specific case ).
	* <li> CATPatternOKWithDuplication : if instance OK ( made by model duplication , standard case ).
	* <li> CATPatternKO                : if instance KO ( close to the body but in non isotopological / geometrical situation ).
	* <li> CATPatternKOAndFar          : if instance KO ( totally out of the body bounding box ).
	* <li> CATPatternOKWithBoolean     : if instance OK ( made by boolean , specific case for non isotopologicaul / geometrical situation in "FullResult" mode).
	* </ul>
	*/
  virtual int GetNumberOfInvalidTransformation(
    CATListOfInt &oListTransfoStatus) = 0;

#endif

	/**
	* @nodoc
	* Defines the number of bodies of the set which intersect another body in the set. If the input <tt>IntersectedBodies</tt> is defined,
	* this CATListOfInt will be fullfilled with the position of clashed bodies in the list of transformations.
	* Returned value may less than 0 if problem happens during clash detection, is equal to 0 if no clash, 
	* and is superior than 1 if there is at least one clash.
	*/
	virtual int GetClashDetection(CATListOfInt *IntersectedBodies = 0) = 0;

	/**
	* Removes the internal faces between the body to be patterned and the support body. This operation
	* is performed prior to creating new instances.
	*/
	virtual void SimplifyTool() = 0;

	/**
	* @nodoc
	* Precise to the Operator that the Spacing is variable ...
	*/
	virtual void SetVariableSpacing(int yes_or_no = 1) = 0;

	/** 
	* @nodoc 
	* Get Performance information : this service is useful for performance verification
	* ( internal use only )
	*/
	virtual void GetPerformanceInformation(
		int &oNbSpeedCases,
		int &oNbOtherBooleanOperations) = 0;

#if defined (CATIACGMR214CAA)
  /**
  * @nodoc
	* Defines the Pattern Data Object for Clone and Sew Process
	*/
  virtual HRESULT  SetTopPatternData (CATTopPatternData * ipObject )=0;
  
#endif

#if defined (CATIACGMR216CAA)
  /**
  * @nodoc
  * To be used to specify that the simplification mode is not to be applied when operations are done
  * on created instances and part.
  * Notes : to desactivate the simplification mode can be useful to keep track of non simplified body to solve some
  * generic naming issue.
  */
  virtual void SetNoSimplificationMode() = 0;
#endif

protected:
	/**
	* Destructor
	*/
	virtual ~CATIPGMTopPattern(); // -> delete can't be called
};

/**
* Creates a CATIPGMTopPattern operator with a body to pattern.
* @param iFactory
* The factory of the geometry. 
* @param iData
* The pointer to the data containing the configuration and the journal.
* @param iOperation
* The type of operation: 
* <dl>
* <dt>CATBoolUnion</dt><dd>Pattern union.
* <dt>CATBoolRemoval</dt><dd><tt>iTool</tt> is subtracted to <tt>iPart</tt>.
* </dl>
* @param iPart
* The pointer to the body to pattern.
* @param iPlane
* The pointer to the plane of the pattern.
* @param iTool
* The pointer to the the first item of the pattern.
* @param iListTransfo
* The pointer to the list of tranformation of each occurrence of the pattern.
* @param iListJournalInfo
* The pointer to the list of journal "information". This list must have
* the same size as the list of transformations. The pattern journal
* is a list of orders:<br>
* <pre>
* [Face_A] - Creation -> [Face_A1] 
* [Face_A] - Creation -> [Face_A2]
* ...
* [Face_A] - Creation -> [Face_Ai]
* ...
* [Face_A] - Creation -> [Face_AN] 
* </pre>
* in which Face_A is a face belonging to the object to be patterned and Face_Ai
* the corresponding face in instance i. If N instances are created, there are N orders
* with Face_A as parent and basically no way to differentiate the faces Face_A1, Face_A2, Face_Ai, 
* ... , Face_AN.
* The iListJournalInfo argument is a way
* to add an "info" data to each journal order so that the equivalent faces can be differentiated
* in each instance.
* @return
* The pointer to the created operator. To <tt>Release</tt>d after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopPattern *CATPGMCreateTopPattern(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATDynBooleanType iOperation,
	CATBody *iPart,
	CATPlane *iPlane,
	CATBody *iTool,
	CATLISTP(CATMathTransformation) *iListTransfo,
	CATLISTP(CATCGMJournalInfo) *iListJournalInfo = NULL);

/**
* Creates a CATIPGMTopPattern operator from a set of faces to pattern.
* No boolean operation is carried out, the faces are simply transformed and inserted in the result body.
* To complete, each transformation must keep the same topology and same dimension as well.
* @param iFactory
* The factory of the geometry. 
* @param iData
* The pointer to the data containing the configuration and the journal.
* @param iPart
* The pointer to the body to pattern.
* @param iPlane
* The pointer to the plane of the pattern or NULL. Specifying the plane is recommended
* for better performances.
* @param iPatternFacesList
* List of faces of the body to pattern. Theses faces must belong to the "iPart" body.
* @param iListTransfo
* The pointer to the list of tranformations.
* @param iListJournalInfo
* The pointer to the list of journal "information". This list must have the
* same size as the list of transformations.
* @return
* The pointer to the created operator. To <tt>Release</tt>d after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopPattern *CATPGMCreateTopPattern(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iPart,
	CATPlane *iPlane,
	CATLISTP(CATFace) &iPatternFacesList,
	CATLISTP(CATMathTransformation) *iListTransfo,
	CATLISTP(CATCGMJournalInfo) *iListJournalInfo = NULL);

#endif /* CATIPGMTopPattern_h_ */
