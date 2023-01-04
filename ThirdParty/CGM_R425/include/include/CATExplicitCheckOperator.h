// COPYRIGHT DASSAULT SYSTEMES 2012
//===================================================================
//
// CATExplicitCheckOperator
// Launch a Check on a set of CGM Objects
//
//===================================================================
// 28 June 2012                                          Creation (KY1)                                      
// 
// 
//===================================================================

#ifndef CATExplicitCheckOperator_H
#define CATExplicitCheckOperator_H

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMOperator.h"
#include <CATListOfCATICGMObjects.h>
#include "CATPGMExplicitReport.h"
#include "ListPOfCATPGMExplicitReport.h"
#include "CATExplicitCheckSeverity.h"
#include "CATCXReport.h"
#include "CATMathInline.h"
#include "CATListOfInt.h"
#include "ListPOfCATBody.h"
#include "CATExplicitLabelParameter.h"

class CATICGMObject;
class CATSoftwareConfiguration;
class CATGeoOpTimer;
class CATExplicitCheck_SetOfAnomalies;
class CATCGMODTScaleManager;

/**
* Operator designed to achieve an Explicit Check on a CATICGMObject instance.
*<br>
* The CATExplicitCheckOperator allows you to perform an explicit check 
* on a set of CATICGMObject. It detects topological and/or geometrical 
* anomalies.
* An anomaly could be a Warning or an Error.
* 
* To use a CATExplicitCheckOperator class:
*<ul>
* <li>Create it with the <tt>CATCreateExplicitCheck</tt> global methods
* <li>Tune it with appropriate options, using the <tt>SetXxx</tt> 
*     or <tt>AddXxx<tt> methods.
* <li>Run it
* <li>Get the result(s) with the <tt>GetNbAnomalies</tt> method 
*     or <tt>GetListIfAnomalies</tt>
* <li><tt>delete</tt> it after use.
*</ul> 
*/
class ExportedByCATTopologicalObjects CATExplicitCheckOperator : public CATCGMOperator
{
	CATCGMVirtualDeclareClass(CATExplicitCheckOperator);
public:

	//-----------------------------------------------------------------------
	//- Ctors
	//-----------------------------------------------------------------------

	/** @nodoc */
	CATExplicitCheckOperator(CATGeoFactory * piFactory,CATSoftwareConfiguration *piSoftConfig);

	//-----------------------------------------------------------------------
	//- Dtor
	//-----------------------------------------------------------------------
	~CATExplicitCheckOperator();

	//-----------------------------------------------------------------------
	//- Public Methods
	//-----------------------------------------------------------------------  

	/**
	* Set List of objects to be Checked <tt>piCGMObject</tt> 
	* to the list of object to be checked
	* @param piCGMObject 
	*   an additional Object to be Checked.
	*/
	void SetListOfObjects(CATLISTP(CATICGMObject)& iListOfCATICGMObject);

	/**
	* Set the list of context bodies in which the specified anomalies 
	* will be checked.
	* Setting a Context Body (Bc), ensure that all CGM Objects involved in a detected 
	* « specific anomaly » are useful for the modele Bc.
	* Example : 
	*     - If user addd objects B1 and B2 to be checked (AddObject(B1),AddObject(B2))
	* There are 4 situations :
	*     1- No context bodies has been specified : anomalies that will be detected 
	*       could involve objects that are not useful for the modelisation 
	*       of B1 and B2
	*     2- Specify B1 as a context body : sub-objects that will checked 
	*       will be those belong to B1 and anomalies that will be detected will only
	*       concern objects that are useful for the context body B1
	*     3- Specify B2 as a context body : same effect as 2 but for B2
	*     4- Specify B1 and B2 as context bodies : anomalies that will detected 
	*       involve objects that are only useful for the modelisation 
	*       of B1 and B2.
	*
	* What objects useful for the model B mean ?
	*     
	*
	*  @param iListOfContextBodies 
	*   List of context bodies  
	*    
	*/
	void SetContextBodies(ListPOfCATBody& iListOfContextBodies);

	/**
	* Add the object to be Checked <tt>piCGMObject</tt> 
	* to the list of object to be checked
	* @param piCGMObject 
	*   an additional Object to be Checked.
	*/
	void AddObject(CATICGMObject * piCGMObject);

	/**
	* Add an anomaly to the list of anomalies to be checked
	* @param iLabelAnomaly 
	*   an additional Anomaly to be Checked.
	*
	* Rmk :  If no anomalies have been specified via the AddAnomaly service,
	*        the default behavior is to check the "CATCGMInternalAnomalies" 
	*        set of anomaly
	*/
	void AddAnomaly(CATCGMExplicitCheckAnomaly iLabelAnomaly);

	/**
	* Set a parameter for a selected specific anomaly. 
	* Setting parameters of a specific anomaly allows to tune the desired behavior. 
	* Tunning parameters of an anomaly impact directly the obtained results of the Explicit Check.
	* @param iLabelAnomaly 
	*   the Specific Anomaly under scope.
	* @param iExplicitLabelParam
	*   the label of parameter to set.
	*   the parameter label describes the meaning of the parameter to set.
	*   Examples : if a parameter to set is the maximum polynomial degree allowed 
	*              for a surface or a curve then the parameter label will be : 
	*					CATExplicitLabelParameter_Max_Polyn_Deg 
	* @param iParam
	*   the parameter value to set.
	*
	* N.B : Please refers to the documentation of specific anomalies (see CATPGMExplicitReport intrface)
	*       It describes :
	*				- the meaning and scope of each specific anomaly, 
	*				- its parameters and their meaning and labels, 
	*				- the CGM Objects that are involved in the anomaly 
	*				- Numerical values that describe the anomaly
	*/
	void SetParameter(CATCGMExplicitCheckAnomaly iLabelAnomaly, CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/**
	* Set a parameter for a selected specific anomaly. 
	* Setting parameters of a specific anomaly allows to tune the desired behavior. 
	* Tunning parameters of an anomaly impact directly the obtained results of the Explicit Check.
	* @param iLabelAnomaly 
	*   the Specific Anomaly under scope.
	* @param iExplicitLabelParam
	*   the label of parameter to set.
	*   the parameter label describes the meaning of the parameter to set.
	*   Examples : if a parameter to set is the maximum polynomial degree allowed 
	*              for a surface or a curve then the parameter label will be : 
	*					CATExplicitLabelParameter_Max_Polyn_Deg 
	* @param iParam
	*   the parameter value to set.
	*
	* N.B : Please refers to the documentation of specific anomalies (see CATPGMExplicitReport intrface)
	*       It describes :
	*				- the meaning and scope of each specific anomaly, 
	*				- its parameters and their meaning and labels, 
	*				- the CGM Objects that are involved in the anomaly 
	*				- Numerical values that describe the anomaly
	*/
	void SetParameter(CATCGMExplicitCheckAnomaly iLabelAnomaly, CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/**
	* Set a parameter for a selected specific anomaly. 
	* Setting parameters of a specific anomaly allows to tune the desired behavior. 
	* Tunning parameters of an anomaly impact directly the obtained results of the Explicit Check.
	* @param iLabelAnomaly 
	*   the Specific Anomaly under scope.
	* @param iExplicitLabelParam
	*   the label of parameter to set.
	*   the parameter label describes the meaning of the parameter to set.
	*   Examples : if a parameter to set is the maximum polynomial degree allowed 
	*              for a surface or a curve then the parameter label will be : 
	*					CATExplicitLabelParameter_Max_Polyn_Deg 
	* @param iParam
	*   the parameter value to set.
	*
	* N.B : Please refers to the documentation of specific anomalies (see CATPGMExplicitReport intrface)
	*       It describes :
	*				- the meaning and scope of each specific anomaly, 
	*				- its parameters and their meaning and labels, 
	*				- the CGM Objects that are involved in the anomaly 
	*				- Numerical values that describe the anomaly
	*/
	void SetParameter(CATCGMExplicitCheckAnomaly iLabelAnomaly, CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	/**
	* Set parameters of Anomamlies
	*
	* @param piExplicitAnomaly_ParameterValues
	*   the Anomaly unde scope.
	*
	*/
	void SetExplicitCheck_SetOfAnomalies(CATExplicitCheck_SetOfAnomalies *piExplicitCheck_SetOfAnomalies);

   /**
	* Decrease severiy degree of a set of Internal anomalies in order to match CGM Check behavior
   * DO NOT USE (Only for internal & specifc usage)
	*/

   void ActivateCGMInternalAnomaliesBehavior();

	/**
	* Performs the Check process
	*/
	int Run();   

	/**
	* Compute the number of errors and warnings found after the Check.
	* @param NbErrors 
	*   Number of errors resulting from the Check operation
	* @param NbWarnings 
	*   Number of warnings resulting from the Check operation
	*/
	void GetNbAnomalies(int& NbErrors,int& NbWarnings);

	/**
	* Get the list of CATExplicitReport objects. Each one is a report 
	* which contains usefull information on a single anomaly. 
	* The size of the list corresponds to the number of the anomalies
	* founded on the analyzed object. The number of anomalies is simply
	* the sum of errors and warnings.
	* @param NbErrors 
	*   Number of errors resulting from the Check operation
	* @param NbWarnings 
	*   Number of warnings resulting from the Check operation
	*/
	void GetListIfAnomalies(ListPOfCATPGMExplicitReport &ioListOfExplicitReports);


	/**
	* Enable Or Disable the capability to Dump the result of the Explicit Check
	* in specific files :
	*      *.CATExplicitCheck : contains ID of anomalies prefixed with ERROR or WARNING word
	*      *.txt              : contains more details on each anomalies
	* @param iEnableDumpExplicitCheckResult 
	*  If TRUE its allow the Dump 
	* N.B : This capability is only available under ODT mode
	*/
	void EnableDumpOfCheckResult(CATBoolean iEnableDumpExplicitCheckResult);

	//========================================================================
	// Gestion CGMReplay
	//========================================================================

	//-----------------------------------------------------------------------
	//- Operator ID Handling
	//-----------------------------------------------------------------------  
	/** @nodoc @nocgmitf */
	const CATString * GetOperatorId();

	/** @nodoc @nocgmitf */
	static const CATString *GetDefaultOperatorId();
	//-----------------------------------------------------------------------
	//- timer Management
	//-----------------------------------------------------------------------  
	/** @nodoc @nocgmitf */
	CATGeoOpTimer *GetTimer();

	//-----------------------------------------------------------------------
	//- Record Mode Management
	//-----------------------------------------------------------------------  

	/** @nodoc @nocgmitf */
	CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
	/** @nodoc @nocgmitf */
	void WriteInput(CATCGMStream  & ioStream);
	/** @nodoc @nocgmitf */
	void WriteOutput(CATCGMStream & ioStream);
	/** @nodoc @nocgmitf */
	void ReadOutput(CATCGMStream & ioStream,ListPOfCATPGMExplicitReport &ioListOfExplicitReports,int &NbErrors,int &NbWarnings);
	/** @nodoc @nocgmitf */
	CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
	/** @nodoc @nocgmitf */
	void Dump( CATCGMOutput& os ) ;
	/** @nodoc @nocgmitf */
	void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
	/** @nodoc @nocgmitf */
	void DumpOutput(CATCGMOutput& os);
	/** @nodoc @nocgmitf */
	CATCGMOperator::CATCheckDiagnostic CheckInput(CATCGMOutput & ioStream);
	/** @nodoc @nocgmitf */
	CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & ioStream);

	//-----------------------------------------------------------------------
	//- Scale Management 
	//-----------------------------------------------------------------------  
	/** @nodoc @nocgmitf */
	void SetODTScaleManager(CATCGMODTScaleManager *pODTScaleManager);

	//=======================================================================
	//- Protected Data & Methods
	//=======================================================================
protected :

	CATSoftwareConfiguration *_pSoftConfig;

	// Gestion CGMReplay
	friend class CATGeoStreamFactory; 
	// private static data
	static CATString _OperatorId;
	static CATGeoOpTimer _Timer;

	/** @nodoc @nocgmitf */
	int RunOperator();

	//=======================================================================
	//- Private Data & Methods
	//=======================================================================
private  :

	/** @nodoc @nocgmitf*/
	void InterpretSelectedAnomalies();
	/** @nodoc @nocgmitf*/
	void DumpIntern(CATCGMOutput& os,ListPOfCATPGMExplicitReport& ioListOfExplicitReports,int &iNbErrors,int &iNbWarnings);
	
	//Data
   CATBoolean                                            _ActivateCGMInternalAnomaliesBehavior;
	CATBoolean                                            _EnableDumpExplicitCheckResult;
	CATLISTP(CATICGMObject)                               _ListOfCATICGMObject;
	CATLISTP(CATBody)                                     _ListOfContextBodies;
	CATListOfInt                                          _ListOfSelectedAnomalies;
	ListPOfCATPGMExplicitReport                           _ListOfExplicitReport;
	static char                                           _FileName1[256];
	static char                                           _FileName2[256];
	static int                                            _ODTExplicitCheckLog;

	// Transient Data
	// Data Struct for Anomalies Parameters Handling
	CATExplicitCheck_SetOfAnomalies *					  _pExplicitCheck_SetOfAnomalies;

	CATCGMODTScaleManager *_pODTScaleManager;

	//Methods 

	/** @nodoc */
	CATExplicitCheckOperator(const CATExplicitCheckOperator& iExplicitCheckOperator);
	/** @nodoc */
	void DumpAnomalies();
	/** @nodoc */
	void DumpDetailedAnomalies();
};

/** 
* Creates an ExplicitCheck Operator.
*
* <br><b>Role</b>: Creates an ExplicitCheck Operator instance.
* To delete with the usual C++ delete operator after use.
*
* @return [out, delete]
*/
ExportedByCATTopologicalObjects CATExplicitCheckOperator *CATCreateExplicitCheckOperator(CATGeoFactory * piFactory,CATSoftwareConfiguration *piConfig);

#endif
